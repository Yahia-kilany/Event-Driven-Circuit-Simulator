# Event-Driven Circuit Simulator

This project is an event-driven logic circuits simulator developed for the CSCE2301 Digital Design I course at the American University in Cairo (AUC) in Fall 2024. The simulator models the behavior of digital circuits based on user-defined inputs and events.

## Contributors
- **Yahia Kilany**
- **Mahmoud Refaie**
- **Seifeldin Elwan**

## Course
- **CSCE2301 - Digital Design I**
- **Instructor:** Dina Mahmoud
- **Semester:** Fall 2024

## Prerequisites
Ensure you have the following installed on your system:
- **C++ Compiler** (g++ with C++17 support)
- **Python** (for running `waveform.py`)

## Getting Started

1. **Clone the Repository**
   ```bash
   git clone https://github.com/Yahia-kilany/Event-Driven-Circuit-Simulator
   cd Event-Driven-Circuit-Simulator
   ```
2-**Navigate to the Source Directory**

```bash
cd Src
```
3- **Compile the Program**: Use the following command to compile the program:

```bash
g++ main.cpp -o main
```
4- **Run the Simulator** After successful compilation, run the program using:
```bash
./main
```
## Using the Waveform Generator
1-**Generate Waveform Data** After running the simulator, it will generate a .sim file containing the simulation results.

2-**Run the Waveform Script** To visualize the output, you can use the provided waveform.py script. Ensure you have Python installed, then run the script with the following command:

```bash
python waveform.py <output_file.sim>
```
Replace <output_file.sim> with the name of the generated simulation file.