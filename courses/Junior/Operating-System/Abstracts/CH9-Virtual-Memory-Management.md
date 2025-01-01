## **第九章重點整理：虛擬記憶體管理 (Virtual-Memory Management)** 

> **本章節介紹虛擬記憶體的優點、需求分頁 (Demand Paging)、頁面替換演算法 (Page Replacement Algorithms) 以及頁框配置 (Allocation of Frames) 等重要概念。**

### 一、虛擬記憶體 (Virtual Memory) 的優點：

*   程式碼不必全部載入記憶體即可執行，只需要部分程式碼即可 (Only part of the program needs to be in memory for execution)。
*   邏輯位址空間 (Logical address space) 可以比實體位址空間 (Physical address space) 大很多。
*   允許多個程序共用位址空間 (Allows address spaces to be shared by several processes)。
*   更有效率的程序建立 (Allows for more efficient process creation)。
*   更多程序可以同時執行 (More programs running concurrently)。
*   減少載入或交換程序所需的 I/O 操作 (Less I/O needed to load or swap processes)。
*   允許稀疏位址空間 (sparse address spaces)，可為增長、動態連結函式庫等預留空間 (holes)。

### 二、需求分頁 (Demand Paging)：

*   只在需要時才將頁面載入記憶體 (bring a page into memory only when it is needed)。
*   優點：
    *   減少 I/O 操作 (Less I/O needed)。
    *   減少記憶體需求 (Less memory needed)。
    *   更快的回應速度 (Faster response)。
    *   可容納更多使用者 (More users)。
*   頁面錯誤 (Page Fault)：當程式參照到尚未載入記憶體的頁面時，會觸發頁面錯誤。
*   處理頁面錯誤的步驟：
    1.  作業系統檢查頁面參照是否合法，並確定頁面在磁碟上的位置。
    2.  取得一個空的頁框 (free frame)。
    3.  透過排程的磁碟操作將頁面交換到頁框中。
    4.  更新頁表，將頁面的有效位元 (valid bit) 設為 v。
    5.  重新啟動造成頁面錯誤的指令。

### 三、頁面替換 (Page Replacement)：

*   當記憶體不足時，需要替換掉一些頁面，以騰出空間給新的頁面。
*   頁面替換演算法 (Page Replacement Algorithms)：決定要替換掉哪些頁面的演算法。
    *   先進先出 (FIFO) 演算法：替換掉最先載入記憶體的頁面。
        *   可能發生 Belady 異常現象 (Belady's Anomaly)：頁框數量增加反而導致更多頁面錯誤。
    *   最佳 (Optimal) 演算法：替換掉未來最長時間內不會使用的頁面。
        *   無法預測未來，僅用於評估其他演算法的效能。
    *   最近最少使用 (LRU) 演算法：替換掉最長時間內沒有被使用的頁面。
    *   LRU 近似演算法 (LRU Approximation Algorithms)：利用硬體提供的參考位元 (reference bit) 來近似 LRU 演算法。
        *   二次機會 (Second-chance) 演算法：結合 FIFO 和參考位元。
    *   計數演算法 (Counting Algorithms)：記錄每個頁面被參照的次數。
        *   最不常使用 (LFU) 演算法：替換掉參照次數最少的頁面。
        *   最常使用 (MFU) 演算法：替換掉參照次數最多的頁面。
*   頁面緩衝 (Page Buffering) 演算法：利用空閒頁框池 (free frame buffer pool) 來減少頁面錯誤的延遲。

### 四、頁框配置 (Allocation of Frames)：

*   決定每個程序可以分配到多少頁框。
*   固定配置 (Fixed Allocation)：每個程序分配到固定數量的頁框。
    *   平均分配 (Equal allocation)：所有程序分配到相同數量的頁框。
    *   比例分配 (Proportional allocation)：根據程序大小分配頁框。
*   優先權配置 (Priority Allocation)：根據程序的優先權分配頁框。
*   全域替換 (Global replacement)：從所有頁框中選擇要替換的頁框。
*   區域替換 (Local replacement)：每個程序只能從自己分配到的頁框中選擇要替換的頁框。
*   非均勻記憶體存取 (Non-Uniform Memory Access, NUMA)：記憶體的存取速度因位置而異。
    *   最佳效能來自於將記憶體分配到執行緒所排程的 CPU 附近。

### 考題預測：

*   虛擬記憶體的優點以及如何實現。
*   需求分頁的概念以及頁面錯誤的處理流程。
*   各種頁面替換演算法的比較，包括其優缺點、如何實現以及是否會發生 Belady 異常現象。
*   頁框配置的策略，包括固定配置、優先權配置、全域替換和區域替換等。
*   非均勻記憶體存取的概念以及如何最佳化效能。
