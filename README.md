# LED-Matrix-4x4x4-Instructional
LED matrix prototype developed for Automation and Engineering Academy (AEA) to demonstrate multiplexing, shift register logic (MBI5026), and 3D coordinate mapping in embedded systems.

### 📖 Overview
This project was developed at the **Automation & Engineering Academy (AEA)** as a primary teaching aid for undergraduate and vocational students. The goal was to visualize spatial logic and hardware-software synchronization through a 64-node LED cube.

### 🛠️ Technical Specifications
* **Microcontroller:** Arduino Nano / ATmega328P
* **Driver IC:** MBI5026 / MG150 (Constant Current LED Driver)
* **Architecture:** 4 Layers (Cathodes) x 16 Columns (Anodes)
* **Power:** 5V DC regulated input with bypass decoupling for switching noise.

### 🎓 Educational Value
I designed this prototype specifically to teach students:
1. **Multiplexing:** How to control 64 individual LEDs using only a handful of MCU pins.
2. **Persistence of Vision (POV):** Calculating refresh rates ($>60Hz$) to ensure flicker-free visualization.
3. **Array Manipulation:** Mapping 3D (x, y, z) coordinates into a linear 1D data stream for the shift registers.

### ⚙️ Fabrication
* **Method:** Hand-soldered jig-aligned matrix for structural integrity.
* **Logic:** Custom C++ library for pattern generation including "rain," "expansion," and "plane-sweep" effects.
