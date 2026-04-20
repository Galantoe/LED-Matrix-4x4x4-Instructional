<img width="1920" height="1032" alt="image" src="https://github.com/user-attachments/assets/95a08817-0a59-4488-bb64-f04a9f6cfd03" />
# LED-Matrix-4x4x4-Instructional
LED matrix prototype developed for Automation and Engineering Academy (AEA) to demonstrate multiplexing, shift register logic (MBI5026), and 3D coordinate mapping in embedded systems.

### 📖 Overview
This project was developed at the **Automation & Engineering Academy (AEA)** as a primary teaching aid for undergraduate and vocational students. The goal was to visualize spatial logic and hardware-software synchronization through a 64-node LED cube.

### 🛠️ Technical Specifications
* **Microcontroller:** Arduino Nano / ATmega328P
* **Driver IC:** MBI5026 / MG150 (Constant Current LED Driver)
* **Architecture:** 4 Layers (anodes) x 16 Columns (cathodes)
* **Power:** 5V DC regulated input with bypass decoupling for switching noise.

### 💻 Simulation vs. Physical Hardware
<img width="1920" height="1032" alt="image" src="https://github.com/user-attachments/assets/c1e01075-aa12-42e9-b4cb-b6a6461155c1" />
Because the **MBI5026** constant-current driver is not available in the standard **Proteus** component library, the simulation schematic utilizes a combination of **two 74HC595 shift registers** and **two ULN2803 Darlington arrays**. 
* This hybrid setup effectively mimics the **sinking logic** of the MBI5026, allowing for full validation of the software's 3D coordinate mapping and SPI communication before physical fabrication.


### ⚠️ Practical Construction Notes
While the simulation may run with direct connections for simplicity, the following resistors **must** be added during practical assembly to ensure component longevity:
1. **Transistor Protection:** Add **1kΩ resistors** to the **base** of each layer-switching transistor to limit current from the Arduino pins.
2. **Current Limiting:** When using the 74HC595/ULN2803 replacement combo in a physical build, add **220Ω - 330Ω resistors** to each **LED cathode** (column). 
   * *Note: These are not required if using the MBI5026, as it features internal constant-current regulation.*

### 🎓 Educational Value
I designed this prototype specifically to teach students:
1. **Multiplexing:** How to control 64 individual LEDs using only a handful of MCU pins.
2. **Array Manipulation:** Mapping 3D (x, y, z) coordinates into a linear 1D data stream for the shift registers.

### ⚙️ Fabrication
* **Method:** Hand-soldered jig-aligned matrix for structural integrity.
* **Logic:** Custom C++ library for pattern generation including "rain," "expansion," and "plane-sweep" effects.
