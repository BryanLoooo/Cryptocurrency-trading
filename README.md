# 🧾 OOP Mid-Term Project – Candlestick Data Visualizer  

## 📘 Overview  
This C++ console-based program simulates a trading data visualization tool. It allows users to select trading pairs (e.g., ETH/BTC), compute candlestick data, and display price movements using text-based graphs.  

The project demonstrates a solid understanding of **Object-Oriented Programming (OOP)** principles through modular functions, data encapsulation, and method abstraction.

---

## ⚙️ Features  

### 🧮 Part 1 – Compute Candlestick Data
- Accepts user-input trading pairs with validation.  
- Retrieves and maps time-stamped order data.  
- Computes average, lowest, and highest prices for each time period.  
- Stores results in a structured candlestick vector.  

### 📊 Part 2 – Text-Based Candlestick Plot
- Generates a console chart using ASCII symbols.  
- Represents open-close differences with `+` and `-` signs.  
- Rounds decimal values to enhance readability.  
- Displays visually distinct high and low values using `|` bars.  

### 📈 Part 3 – Plot Additional Trading Data
- Reads external trading files, splits, and stores data into maps.  
- Iterates through maps to populate new candlestick vectors.  
- Performs symbol-based graphical comparison of trading trends.  

---

## 🧩 Technical Details  
- **Language:** C++  
- **Key Concepts Used:** Classes, Vectors, Maps, Iterators, File Handling, Validation, Conditional Logic  
- **Data Flow:**  
Input → Validation → Computation → Vector Storage → Text Visualization

---

## 🧠 Learning Outcomes  
- Reinforced understanding of modular OOP design.  
- Applied real-world logic for handling market-like data.  
- Practiced precision rounding, error handling, and ASCII visualization.  

---

## ▶️ How to Run  
1. Compile using a C++ compiler (e.g., `g++ main.cpp -o main`).  
2. Run the program:  
 ```bash
 ./main
 ```
