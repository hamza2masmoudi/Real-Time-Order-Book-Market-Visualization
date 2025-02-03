# **Real-Time Order Book & Market Visualization**

## **Overview**
**real-time order book** and **interactive market depth visualizer** built with **C++** and **Qt6**. It simulates a live trading environment where users can **place orders**, **view market depth**, and **monitor trade execution**. The project is designed for **quantitative finance** and **high-frequency trading (HFT) system simulation**, demonstrating your ability to handle performance-critical systems while delivering a polished user experience.

---

## **Features**
### **📊 Order Book & Market Visualization**
- Displays **live bid/ask price levels** using a **QtCharts-based depth chart**.
- Shows a **dynamic order book with real-time updates**.

### **⚡ High-Performance Matching Engine**
- Implements an **efficient limit order book** for order matching.
- Uses **multi-threading** for processing **buy/sell orders** in real time.

### **📈 Real-Time Order Simulation**
- Generates **random buy and sell orders** at different price levels.
- Simulates **market activity** with updates **every 500ms**.

### **🛠️ Interactive Trading Interface**
- **Users can manually place orders** through a form.
- **Input fields for price and quantity**, with a **buy/sell option**.
- **Real-time performance metrics** (processed orders counter).

### **🔍 Risk Management & Error Handling**
- **User input validation** prevents invalid trades.
- **Real-time error messages** for incorrect values.
- **Automatic cleanup of stale orders**.

---

## **Installation & Setup**

# 1️⃣ Install Dependencies

# For macOS (Homebrew)
brew install qt@6

# For Linux
sudo apt install qt6-base-dev qt6-charts-dev

# 2️⃣ Clone the Repository
git clone https://github.com/yourusername/QuantOrderFlow.git
cd orderbook-project

# 3️⃣ Build the Project
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@6 ..
make -j8

# 4️⃣ Run the Application
./orderbook

## Project Structure

- **backend/**
  - `orderbook.h` - Core data structures for order book
  - `orderbook.cpp` - Handles order placement and execution
  - `matching_engine.h` - Matching logic for buy/sell orders
  - `matching_engine.cpp` - Order matching logic

- **frontend/**
  - `mainwindow.h` - UI logic for interactive trading
  - `mainwindow.cpp` - Trading interface and order simulation
  - `chart_widget.h` - Handles QtCharts visualization
  - `chart_widget.cpp` - Manages chart rendering

- **Root Files:**
  - `main.cpp` - Entry point of the application
  - `CMakeLists.txt` - Build configuration
  - `README.md` - Project Documentation


## How It Works

1. **Matching Engine**
   - Maintains a **limit order book** with **efficient data structures**.
   - Matches **incoming buy/sell orders** using a **price-time priority system**.

2. **Real-Time Order Simulation**
   - Every **500ms**, a **random order** is generated and sent to the **matching engine**.
   - Orders are executed based on the **market state**.

3. **GUI & Order Visualization**
   - **QtCharts** is used to **plot market depth**.
   - Users can **place orders manually** or observe **automated order execution**.

## Potential Enhancements

- **📡 Live Market Data Integration** (Fetch real-time data from an API).
- **📉 Advanced Charting** (Candlestick charts, moving averages).
- **📊 Performance Optimization** (Leverage parallel processing for order execution).
- **🛠 API Support** (Expose endpoints for external bots to trade on the simulated order book).


**Hamza Masmoudi**  