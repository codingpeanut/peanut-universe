### 1. **準備工作**
- **輸入資料：**
  包括每個進程的 **到達時間 (Arrival Time, AT)**、**執行時間 (Burst Time, BT)**、**優先權 (Priority, 若適用)**。
- **輸出結果：**
  - 每個進程的完成時間 (Completion Time, CT)
  - 周轉時間 (Turnaround Time, TAT = CT - AT)
  - 等待時間 (Waiting Time, WT = TAT - BT)
  - 平均周轉時間和平均等待時間。

---

### 2. **排程演算法的步驟**

#### (1) **FCFS (First-Come, First-Served)**
- 按到達時間排序。
- 依次執行進程，無需搶占。
- 若 CPU 空閒，等待到下一個進程到達。

#### (2) **SJF (Shortest Job First, Non-preemptive)**
- 按到達時間排序。
- 在進程到達後，選擇最短執行時間的進程。
- 如果有進程尚未到達，等待其到達後再選擇。

#### (3) **SRTF (Shortest Remaining Time First)**
- 隨時選擇剩餘執行時間最短的進程執行（搶占式）。
- 若有新進程到達，檢查其剩餘執行時間是否更短，若是則搶占當前進程。

#### (4) **Preemptive Priority**
- 隨時選擇優先級最高（數字最小）的進程執行（搶占式）。
- 若新進程的優先級比當前進程更高，則搶占。

#### (5) **RR (Round Robin)**
- 使用時間片 (Time Quantum) = 3。
- 按到達順序執行，進程執行時間減少 3 後切換到隊列尾部（若未完成）。
- 若執行時間小於等於 3，則直接完成。
