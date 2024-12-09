### **第五章重點整理：CPU 排程 (CPU Scheduling)**

#### **1. 核心概念**

- **CPU 與 I/O 爆發循環 (CPU-I/O Burst Cycle)**:

  - 程序執行由**CPU 爆發 (CPU Burst)**（計算密集）和**I/O 爆發 (I/O Burst)**（等待密集）交替組成。
  - 排程目標：提升 CPU 利用率 (CPU Utilization)，讓 CPU 保持忙碌。

- **CPU 排程點 (CPU Scheduling Points)**:
  CPU 排程的切換情境：

  - **非搶占式 (Non-preemptive Scheduling)**：
    - 僅在進程主動進入等待 (Waiting) 或終止 (Termination) 狀態時進行排程。
  - **搶占式 (Preemptive Scheduling)**：
    - 排程點包括以下狀態切換：
      1.  **執行轉等待 (Switch from Running to Waiting)**。
      2.  **執行轉就緒 (Switch from Running to Ready)**。
      3.  **等待轉就緒 (Switch from Waiting to Ready)**。
      4.  **進程終止 (Process Termination)**。

- **調度器 (Scheduler)**
  - **短期調度器 (Short-Term Scheduler)**：決定哪個進程從就緒隊列 (Ready Queue) 分配到 CPU 執行。
  - **分派器 (Dispatcher)**：負責實際切換進程，包括：
    1.  切換上下文 (Context Switching)。
    2.  切換到用戶模式 (User Mode)。
    3.  跳轉到進程的適當位置執行。

---

#### **2. 排程標準 (Scheduling Criteria)**

- **CPU 利用率 (CPU Utilization)**：CPU 保持忙碌的時間比例，目標接近 100%。
- **吞吐量 (Throughput)**：每單位時間完成的進程數。
- **周轉時間 (Turnaround Time)**：從進程提交到完成所需的總時間。
- **等待時間 (Waiting Time)**：進程在就緒隊列中等待的總時間。
- **響應時間 (Response Time)**：從進程提交到首次響應的時間。

---

#### **3. 排程演算法與挖空考點 (Scheduling Algorithms and Key Points)**

1. **先到先服務 (First-Come, First-Served, FCFS)**:

   - **特點 (Characteristics)**：
     - 按進程到達順序執行，簡單但可能產生**隊伍效應 (Convoy Effect)**。
   - **考點 (Key Points)**：
     - Gantt 圖的生成。
     - 計算等待時間 (Waiting Time) 和周轉時間 (Turnaround Time)。
   - 示例：
     ```text
     到達順序 (Arrival Order)：P1 (24ms), P2 (3ms), P3 (3ms)
     Gantt圖: | P1 | P2 | P3 |
               0   24   27   30
     平均等待時間 (Average Waiting Time) = (0 + 24 + 27) / 3 = 17ms
     ```

2. **最短作業優先 (Shortest-Job-First, SJF)**:

   - **特點 (Characteristics)**：
     - 優先執行執行時間最短的進程。
     - 搶占式版本稱為**最短剩餘時間優先 (Shortest-Remaining-Time-First, SRTF)**。
   - **考點 (Key Points)**：
     - 如何預測下一次 CPU 爆發時間（**指數平滑法 (Exponential Averaging)**）。
     - SJF 是最小化平均等待時間的最優排程。
   - 示例：
     ```text
     到達順序 (Arrival Order)：P1 (6ms), P2 (8ms), P3 (7ms), P4 (3ms)
     Gantt圖: | P4 | P1 | P3 | P2 |
               0    3    9   16   24
     平均等待時間 = (0 + 3 + 9 + 16) / 4 = 7ms
     ```

3. **優先權排程 (Priority Scheduling)**:

   - **特點 (Characteristics)**：
     - 優先數字越小，優先級越高。
     - 可能產生**飢餓 (Starvation)**，可用**老化 (Aging)** 解決。
   - **考點 (Key Points)**：
     - Gantt 圖及等待時間計算。
     - 飢餓問題的解決方法。

4. **輪轉 (Round-Robin, RR)**:
   - **特點 (Characteristics)**：
     - 每進程分配固定時間片 (Time Quantum)。
   - **考點 (Key Points)**：
     - 時間片大小如何影響性能（**時間片太小 (Small Time Quantum)** 導致過多上下文切換）。
     - Gantt 圖及等待時間計算。
   - 示例：
     ```text
     時間片 (Time Quantum) = 4ms
     到達順序：P1 (24ms), P2 (3ms), P3 (3ms)
     Gantt圖: | P1 | P2 | P3 | P1 | P1 | P1 |
               0    4    7   10   14   18   22   26   30
     ```
