# REAL-TIME ORDER BOOK & MARKET VISUALIZATION

## OVERVIEW

This project is a real-time trading simulation that demonstrates:

1. **A multi-threaded matching engine (C++)**, which handles buy/sell orders, computes trades, and maintains an order book.  
2. **A polished Qt-based GUI (C++)**, featuring:
   - Live order book depth chart  
   - Advanced candlestick chart with a moving average  
   - Interactive metrics dashboard (latency, throughput)  
   - Trade history table  
3. **Simulated market data** (both limit and market orders), so the system feels “live.”

It is designed to show performance-critical multi-threading, user interface design (Qt), basic financial logic (limit/market orders), trade recording, and real-time metrics.

---

## FEATURES

### 1. MULTI-THREADED MATCHING ENGINE
- Processes incoming orders via a thread-safe queue.  
- Supports limit orders (price-based matching) and market orders (immediate fill).  
- Tracks partial and full matches; unmatched remainder is added to the order book.  
- Records latency from order submission to final processing.  
- Calculates throughput (orders per second) since engine startup.

### 2. ORDER BOOK & TRADE HISTORY
- Maintains aggregated bid/ask volumes at each price.  
- “Trade” events are recorded when orders are matched; a history is displayed in a Qt table.  
- Simulated buy/sell orders arrive periodically (limit or market), reflecting market movement.

### 3. ADVANCED CHARTING
- **Order Book Depth Chart:**  
  Shows aggregated bids (line) and asks (line), updated in real time.  
- **Candlestick Chart:**  
  Displays randomized open-high-low-close (OHLC) data, plus a moving average overlay.  
- **Zooming & Panning:**  
  Charts support mouse-based zoom, interactive tooltips, and dragging.

### 4. LIVE METRICS DASHBOARD
- **Latency:** Average time (ms) from submission to final matching in the engine.  
- **Throughput:** Orders per second processed since engine start.  
- UI uses progress bars for a quick glance, plus numeric labels for precise values.

### 5. SIMULATION & USER INTERACTION
- **Automatic “live market data” feed:** Market orders at random intervals (e.g., every 300ms).  
- **Automatic limit order feed:** Limit orders at random intervals (e.g., every 500ms).  
- **Manual Order Submission:**  
  A form (price, quantity, side: buy/sell, order type: limit/market/etc.) to place custom orders.

### 6. ROBUST LOGGING (using spdlog if installed)
- Logs order submissions, partial/fill events, errors, and engine lifecycle to the console (or a file, if configured).  
- Simplifies debugging and performance analysis.
---

## HOW TO BUILD & RUN

### 1. INSTALL DEPENDENCIES  
   - Qt6 (Core, Gui, Widgets, Charts). On macOS with Homebrew:  
     ```bash
     brew install qt@6
     ```  
   - (Optional) spdlog for robust logging. Example:  
     ```bash
     brew install spdlog
     ```
     or on Ubuntu:
     ```bash
     sudo apt-get install libspdlog-dev
     ```
   
### 2. CLONE & PREPARE  
   ```bash
   cd /path/to/projects
   git clone project link
   cd orderbook-project
   ```

### 3. BUILD  
   ```bash
   mkdir build && cd build
   cmake -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@6 ..
   make -j8
   ```

### 4. RUN  
   ```bash
   ./orderbook
   ```
   A window appears with:
   - (a) “Metrics Dashboard” for latency & throughput  
   - (b) “Order Submission” panel  
   - (c) Real-time depth chart & candlestick chart  
   - (d) Trade history table

---

## QUICK DEMO (OPTIONAL)

1. Launch the app:  
   ```bash
   ./orderbook
   ```
2. Observe:
   - Random limit orders arrive ~every 500ms (`simulateOrder`).  
   - Random market orders arrive ~every 300ms (`simulateLiveMarketData`).  
   - The depth chart updates with aggregated Bids/Asks.  
   - The candlestick chart shows random OHLC data plus a moving average overlay.  
   - The trade history table populates each time a match event occurs (partial or full fill).  
   - The metrics dashboard progress bars + labels reflect average latency and throughput.

---

## POSSIBLE EXTENSIONS
- More advanced order types (stop-loss, iceberg).  
- Historical data playback / backtesting.  
- Real-time feed from an external API.  
- Finer performance instrumentation (more detailed metrics, event logs).  
- REST/WebSocket API to let external apps interact with the engine.

---

## NOTES
- If **spdlog** is not found during CMake, the engine logs to `std::cerr` instead.  
- The “simulateLiveMarketData” approach is purely for demonstration. A real feed might parse data from a socket or CSV file.


**Hamza Masmoudi**  
