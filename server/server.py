#!/usr/bin/env python3
"""
IoT Workshop 2026 – fælles server til underviseren.

Kører to ting på samme tid:
  * En TCP-server (port 5000), som elevernes ESP32'ere forbinder til.
  * En webside (port 8080), som vises på projektoren. Her kan man se
    beskederne, se hvem der er forbundet og sende svar/kommandoer.

Protokol (én tekstlinje pr. besked, afsluttet med '\n'):
  ESP -> server: Første linje er elevens navn.
                 "tekst"        vises på skærmen.
                 "@navn|tekst"  sendes videre til eleven med det navn
                                (og vises også på skærmen).
  server -> ESP: "afsender|tekst", fx "Server|BLINK" eller "Anna|Hej".

Kun Pythons standardbibliotek bruges, så der kræves ingen internetforbindelse.

Start:  python3 server.py
Computeren laver selv WiFi'et (accesspoint), som ESP'erne forbinder til, og
slukker det igen, når serveren stoppes med Ctrl+C.
Kræver Linux med NetworkManager (nmcli).
"""

import json
import signal
import socketserver
import subprocess
import sys
import threading
import time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

# WiFi'et, som computeren laver. Det er disse oplysninger, eleverne skal skrive i opgave 3.1.
WIFI_NAVN = "IoT-Workshop"
WIFI_KODE = "12345678"    # Mindst 8 tegn
HOTSPOT_FORBINDELSE = "IoT-Workshop-Hotspot"  # Navnet på forbindelsen i NetworkManager

TCP_PORT = 5000
WEB_PORT = 8080
MAX_MESSAGES = 200
VELKOMST = True       # Send automatisk en velkomstbesked, når en ESP forbinder
MAX_PR_SEKUND = 5     # Beskeder pr. sekund pr. ESP. Resten ignoreres (beskytter mod løkker, der sender uafbrudt)

lock = threading.Lock()
clients = {}   # id -> Client
messages = []  # {"t": tid, "fra": navn, "ip": ip, "tekst": tekst, "type": "elev"/"server"/"system"}
next_id = 1
msg_counter = 0


class Client:
    def __init__(self, cid, ip, sock):
        self.id = cid
        self.ip = ip
        self.sock = sock
        self.name = None
        self.connected_at = time.time()
        self.send_lock = threading.Lock()
        self.sendt = []        # tidspunkter for de seneste beskeder (rate limit)
        self.advaret = False

    def for_mange(self):
        nu = time.time()
        self.sendt = [t for t in self.sendt if nu - t < 1.0]
        if len(self.sendt) >= MAX_PR_SEKUND:
            return True
        self.sendt.append(nu)
        return False

    def send_line(self, text):
        data = (text.replace("\n", " ") + "\n").encode("utf-8")
        with self.send_lock:
            try:
                self.sock.sendall(data)
                return True
            except OSError:
                return False

    def label(self):
        return self.name or self.ip


def add_message(fra, ip, tekst, typ):
    global msg_counter
    with lock:
        msg_counter += 1
        messages.append({"n": msg_counter, "t": time.strftime("%H:%M:%S"), "fra": fra, "ip": ip, "tekst": tekst, "type": typ})
        del messages[:-MAX_MESSAGES]
    print(f"[{typ}] {fra} ({ip}): {tekst}")


def send_to(target, afsender, text):
    """target er 'alle' eller et klient-id (som tekst). Returnerer antal modtagere."""
    with lock:
        if target == "alle":
            targets = list(clients.values())
        else:
            c = clients.get(int(target)) if str(target).isdigit() else None
            targets = [c] if c else []
    return sum(1 for c in targets if c.send_line(f"{afsender}|{text}"))


def send_to_name(navn, afsender, text):
    """Sender til alle ESP'er med det navn (uden forskel på store/små bogstaver)."""
    navn = navn.strip().lower()
    with lock:
        targets = [c for c in clients.values() if c.name and c.name.lower() == navn]
    return sum(1 for c in targets if c.send_line(f"{afsender}|{text}"))


class EspHandler(socketserver.StreamRequestHandler):
    def handle(self):
        global next_id
        ip = self.client_address[0]
        with lock:
            cid = next_id
            next_id += 1
            client = Client(cid, ip, self.request)
            clients[cid] = client
        add_message("system", ip, f"Ny ESP forbundet fra {ip}", "system")
        try:
            for raw in self.rfile:
                line = raw.decode("utf-8", errors="replace").strip()
                if not line:
                    continue
                if client.name is None:
                    client.name = line.replace("|", "")[:30]
                    add_message("system", ip, f"{client.name} er forbundet (IP: {ip})", "system")
                    if VELKOMST:
                        client.send_line(f"Server|Velkommen {client.name}. Din IP-adresse er {ip}")
                    continue
                if client.for_mange():
                    if not client.advaret:
                        client.advaret = True
                        client.send_line("Server|Du sender for mange beskeder. Nogle bliver ignoreret.")
                        add_message("system", ip, f"{client.name} sender for mange beskeder", "system")
                    continue
                client.advaret = False
                line = line[:300]
                if line.startswith("@") and "|" in line:
                    modtager, tekst = line[1:].split("|", 1)
                    n = send_to_name(modtager, client.name, tekst)
                    if n:
                        add_message(f"{client.name} → {modtager.strip()}", ip, tekst, "privat")
                    else:
                        client.send_line(f"Server|Kunne ikke finde nogen ved navn {modtager.strip()}")
                else:
                    add_message(client.name, ip, line, "elev")
        except (ConnectionError, OSError):
            pass
        finally:
            with lock:
                clients.pop(cid, None)
            add_message("system", ip, f"{client.label()} har afbrudt forbindelsen", "system")


class ThreadingTCPServer(socketserver.ThreadingTCPServer):
    allow_reuse_address = True
    daemon_threads = True


PAGE = (Path(__file__).parent / "projektor.html").read_text(encoding="utf-8")


class WebHandler(BaseHTTPRequestHandler):
    def log_message(self, *args):
        pass  # hold terminalen ren

    def _send(self, code, body, ctype):
        data = body.encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(data)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(data)

    def do_GET(self):
        if self.path == "/":
            self._send(200, PAGE, "text/html; charset=utf-8")
        elif self.path == "/api/state":
            with lock:
                state = {
                    "clients": [{"id": c.id, "navn": c.label(), "ip": c.ip} for c in clients.values()],
                    "messages": messages,
                    "server": {"ip": SERVER_IP, "port": TCP_PORT,
                               "wifi_navn": WIFI_NAVN, "wifi_kode": WIFI_KODE},
                }
                body = json.dumps(state)
            self._send(200, body, "application/json")
        else:
            self._send(404, "Ikke fundet", "text/plain")

    def do_POST(self):
        if self.path != "/api/send":
            self._send(404, "Ikke fundet", "text/plain")
            return
        length = int(self.headers.get("Content-Length", 0))
        try:
            payload = json.loads(self.rfile.read(length) or b"{}")
        except json.JSONDecodeError:
            self._send(400, "Ugyldig JSON", "text/plain")
            return
        text = str(payload.get("tekst", "")).strip()
        target = str(payload.get("til", "alle"))
        if not text:
            self._send(400, "Tom besked", "text/plain")
            return
        n = send_to(target, "Server", text)
        modtager = "alle" if target == "alle" else next(
            (c.label() for c in list(clients.values()) if str(c.id) == target), "?")
        add_message("Server", "", f"→ {modtager}: {text}", "server")
        self._send(200, json.dumps({"sendt_til": n}), "application/json")


SERVER_IP = None  # Sættes af start_hotspot()


def nmcli(*args):
    return subprocess.run(["nmcli", *args], capture_output=True, text=True)


def start_hotspot():
    """Laver et 2,4 GHz-accesspoint med NetworkManager og returnerer computerens IP på det."""
    enheder = nmcli("-t", "-f", "DEVICE,TYPE", "device").stdout.splitlines()
    wifi = next((l.split(":")[0] for l in enheder if l.split(":")[1:] == ["wifi"]), None)
    if wifi is None:
        sys.exit("Fandt intet WiFi-kort. Er nmcli installeret?")
    print(f"Starter hotspot '{WIFI_NAVN}' på {wifi} (computeren mister sin nuværende WiFi-forbindelse)...")
    nmcli("connection", "delete", HOTSPOT_FORBINDELSE)  # Fjern evt. gammel udgave
    r = nmcli("device", "wifi", "hotspot", "ifname", wifi, "con-name", HOTSPOT_FORBINDELSE,
              "ssid", WIFI_NAVN, "band", "bg", "password", WIFI_KODE)
    if r.returncode != 0:
        sys.exit("Kunne ikke starte hotspot:\n" + r.stderr.strip())
    for _ in range(20):
        ip = nmcli("-g", "IP4.ADDRESS", "device", "show", wifi).stdout.strip().split("/")[0]
        if ip:
            return ip
        time.sleep(0.5)
    sys.exit("Hotspot startede, men fik ingen IP-adresse.")


def stop_hotspot():
    print("Stopper hotspot...")
    nmcli("connection", "down", HOTSPOT_FORBINDELSE)
    nmcli("connection", "delete", HOTSPOT_FORBINDELSE)


def afbryd(*_):
    raise KeyboardInterrupt


def main():
    global SERVER_IP
    # Sluk også hotspottet, hvis terminalen bliver lukket eller processen bliver stoppet
    signal.signal(signal.SIGTERM, afbryd)
    signal.signal(signal.SIGHUP, afbryd)
    SERVER_IP = start_hotspot()
    try:
        tcp = ThreadingTCPServer(("0.0.0.0", TCP_PORT), EspHandler)
        web = ThreadingHTTPServer(("0.0.0.0", WEB_PORT), WebHandler)
        threading.Thread(target=tcp.serve_forever, daemon=True).start()
        print("=" * 60)
        print("  Skriv dette på tavlen (opgave 3.1):")
        print(f"    WIFI_NAVN   = \"{WIFI_NAVN}\"")
        print(f"    WIFI_KODE   = \"{WIFI_KODE}\"")
        print(f"    SERVER_IP   = \"{SERVER_IP}\"")
        print(f"    SERVER_PORT = {TCP_PORT}")
        print()
        print(f"  Projektor-side: http://localhost:{WEB_PORT}")
        print("  Stop serveren og hotspottet med Ctrl+C.")
        print("=" * 60)
        try:
            web.serve_forever()
        except KeyboardInterrupt:
            print("\nLukker ned...")
        finally:
            tcp.shutdown()
            web.server_close()
    finally:
        stop_hotspot()


if __name__ == "__main__":
    main()
