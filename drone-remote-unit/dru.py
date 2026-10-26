import tkinter as tk
import serial, threading, time

try:
    ard = serial.Serial('COM3', 9600, timeout=1)
    connesso = True
except:
    ard, connesso = None, False

def cmd(c):
    if connesso: ard.write((c + '\n').encode('utf-8'))

def read():
    while connesso:
        try:
            if ard.in_waiting: #buffer
                l = ard.readline().decode('utf-8').strip()
                if l.startswith("DIST:"):
                    l_dist.config(text=f"Distanza: {l.split(':')[1]} cm")
                elif l.startswith("STATE:"):
                    l_stato.config(text=f"Stato: {l.split(':')[1]}")
                elif l.startswith("Temperatura:"):
                    temp = l.split(':')[1].strip().split()[0]
                    l_temp.config(text=f"Temperatura: {temp} °C")
        except:
            break
        time.sleep(0.1)

root = tk.Tk()
root.title("DRU")
root.geometry("400x450")

FONT_BASE = ("", 18)
FONT_TITOLO = ("", 22, "bold")

tk.Label(root, text="DRU", font=FONT_TITOLO).pack(pady=20)

tk.Button(root, text="TAKE OFF", font=FONT_BASE, command=lambda: cmd("TAKEOFF")).pack(pady=10, fill="x", padx=50)
tk.Button(root, text="LANDING", font=FONT_BASE, command=lambda: cmd("LAND")).pack(pady=10, fill="x", padx=50)

l_stato = tk.Label(root, text="Stato: IN ATTESA", font=FONT_BASE)
l_stato.pack(pady=15)

l_dist = tk.Label(root, text="Distanza: -- cm", font=FONT_BASE)
l_dist.pack(pady=5)

l_temp = tk.Label(root, text="Temperatura: -- °C", font=FONT_BASE)
l_temp.pack(pady=5)

if connesso:
    threading.Thread(target=read, daemon=True).start()

root.mainloop()