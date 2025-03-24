# COEN 320 — Air Traffic Control System

An embedded Air Traffic Control (ATC) simulation project built on the **QNX Real-Time Operating System (RTOS)** using **C++** and POSIX threads.

## 🚀 Overview

This project simulates a 3D controlled airspace where multiple aircraft operate as independent threads. The ATC system monitors aircraft positions, detects potential safety violations, and allows operator intervention via real-time commands.

The system meets real-time constraints for:
- Aircraft position updates
- Safety separation enforcement
- Operator command logging
- Historical data logging

---

## 🧱 Architecture

- **Aircraft Threads:** Each aircraft is implemented as a periodic POSIX thread using QNX timers. They update their position every second based on velocity.
- **Airspace Module:** Central registry that holds references to all aircraft for monitoring, logging, and display.
- **Logger Module:** Responsible for periodic logging of airspace state and operator commands.
- **Operator Command Parser:** Parses textual commands entered by the operator and structures them for use by the system.
- **Main Controller:** The `COEN320_ATC` program handles aircraft initialization, logging scheduling, and operator command interaction.

---

## 🧩 Key Features

- ✅ Real-time simulation with 1-second aircraft update interval
- ✅ Aircraft logging to `airspace_log.csv` every 20 seconds
- ✅ Operator command logging to `operator_log.txt` with timestamps
- ✅ Command parser supporting:
  - `SET_SPEED <ID> <Vx> <Vy> <Vz>`
  - `SET_ALT <ID> <Z>`
  - `CHANGE_POS <ID> <X> <Y> <Z>`
- ✅ Display of aircraft state every 5 seconds
- ✅ Clean modular code with clear responsibilities

---

## 🛠️ Build Instructions (QNX)

1. Ensure you are on the **QNX development environment**
2. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/<repo-name>.git
   cd <repo-name>

