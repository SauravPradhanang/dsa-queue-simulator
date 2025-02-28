# Traffic Queue Simulator
🚦 **Four-Way Junction Traffic Management System**

This project simulates vehicles in a four way intersection. The traffic flow is controlled based on traffic light.

![image](https://github.com/SauravPradhanang/dsa-queue-simulator/blob/main/Traffic_Simulation.gif)


**📋 Project Overview**

This project simulates vehicles using queue data structure. The vehicles are elements with properties which are placed in a queue.<br>

Key Features<br>

🚌 **Vehicle Queue Management:** The vehicles in each lane are managed in queues. Vehicles in each lane is released periodically.<br>

🏃 **Priority Based System:** A priority lane is defined where its vehicles are released as soon as it 10 vehicles accumulate.<br>

📺 **Real time visualization:** The simulation is rendered using SDL for a graphical display.<br>

# Prerequisites
To run this the requirements are:

1. G++ or GCC compiler
2. SDL2 Library


### On Windows
1. Clone the reopsitory
   ```bash
   git clone https://github.com/SauravPradhanang/dsa-queue-simulator.git
   cd dsa-queue-simulator
   ```
2. Compile and run the program using the following command
   ```bash
   g++ -Iinclude -Llib -o bin/main.exe src/main.c src/traffic_simulation.c -lmingw32 -lSDL2main -lSDL2
   ./bin/main.exe
   ```
# References
1. SDL2 Documentation: https://wiki.libsdl.org/




