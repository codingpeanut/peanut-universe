# CH3 - Precess Concept

### 一、程序概念 (Process Concept)

*   **程序的定義:** 程序是指**正在執行中的程式**。作業系統會執行各種程式，例如批次系統中的作業和分時系統中的使用者程式或任務。教科書中，作業和程序這兩個術語幾乎可以互換使用。
*   **程序的組成:** 程序包含以下部分：
    *   **程式碼段 (text section):** 存放程式的指令碼。
    *   **程式計數器 (program counter) 和暫存器內容:** 指示下一條要執行的指令的地址，以及 CPU 暫存器的值。
    *   **堆疊 (stack):** 存放暫時性資料，例如函數參數、返回地址和局部變數。
    *   **資料段 (data section):** 存放全域變數。
    *   **堆積 (heap):** 存放程式執行期間動態配置的記憶體。
*   **程序與程式的區別:** 程式是被動儲存在硬碟上的實體 (可執行檔)，而程序是主動的。當可執行檔被載入到記憶體中時，程式就變成了程序。
*   **程序的狀態:** 程序在執行過程中會改變狀態。程序的狀態包括：
    *   **新建 (new):** 程序正在被建立。
    *   **就緒 (ready):** 程序正在等待被分配到處理器。
    *   **執行 (running):** 指令正在被執行。
    *   **等待 (waiting):** 程序正在等待某些事件發生。
    *   **終止 (terminated):** 程序已完成執行。

### 二、程序控制區塊 (Process Control Block, PCB)

*   **PCB 的定義:** 每個程序在作業系統中都由一個 PCB 表示，也稱為任務控制區塊。
*   **PCB 的內容:** PCB 存放與每個程序相關的資訊，包括：
    *   **程序狀態:** 程序的當前狀態 (例如新建、就緒、執行、等待或終止)。
    *   **程式計數器:** 指示下一條要執行的指令的地址。
    *   **CPU 暫存器:** 所有程序相關暫存器的內容。
    *   **CPU 排程資訊:** 程序的優先級、排程佇列指標等。
    *   **記憶體管理資訊:** 分配給程序的記憶體。
    *   **帳戶資訊:** 程序已使用的 CPU 時間、程序開始後的經過時間、時間限制等。
    *   **輸入/輸出狀態資訊:** 分配給程序的輸入/輸出裝置、已開啟檔案的列表等。

### 三、程序排程 (Process Scheduling)

*   **程序排程的目的:** 程序排程的目的是最大化 CPU 使用率，並快速地將程序切換到 CPU 上進行分時處理。
*   **程序排程器的功能:** 程序排程器負責從可用的程序中選擇下一個要執行的程序，並將 CPU 分配給它。
*   **排程佇列:** 程序排程器維護著程序的排程佇列，包括：
    *   **作業佇列 (job queue):** 系統中所有程序的集合。
    *   **就緒佇列 (ready queue):** 存放所有駐留在主記憶體中，並且準備好執行等待執行的程序。
    *   **裝置佇列 (device queues):** 存放等待輸入/輸出裝置的程序。
*   **排程器類型:** 程序排程器主要分為三種類型：
    *   **長期排程器 (long-term scheduler):** 也稱為作業排程器，負責從作業池 (通常是硬碟) 中選擇程序，並將它們載入到記憶體中以供執行。長期排程器呼叫頻率較低，可以較慢。它控制著多道程式設計的程度 (記憶體中的程序數量)，並選擇適當的輸入/輸出密集型程序和 CPU 密集型程序組合。
    *   **短期排程器 (short-term scheduler):** 也稱為 CPU 排程器，負責選擇下一個要執行的程序，並將 CPU 分配給它。短期排程器呼叫頻率非常高，必須非常快。
    *   **中期排程器 (medium-term scheduler):** 如果需要降低多道程式設計的程度，則可以添加中期排程器。中期排程器負責將程序從記憶體中移除，儲存到硬碟上，然後再從硬碟中取出以繼續執行，這個過程稱為交換 (swapping)。中期排程器可以交換程序進出記憶體，以改善程序組合或釋放記憶體。

### 四、程序操作 (Operations on Processes)

*   **程序建立:** 父程序可以建立子程序，子程序又可以建立其他的程序，形成一個程序樹。程序通常透過程序識別碼 (PID) 進行識別和管理。
*   **資源共享:** 父程序和子程序之間可以共享資源。常見的資源共享方式包括：
    *   父程序和子程序共享所有資源。
    *   子程序共享父程序資源的子集。
    *   父程序和子程序不共享任何資源。
*   **執行方式:** 父程序和子程序可以同時執行，或者父程序等待子程序終止後再繼續執行。
*   **地址空間:** 子程序可以複製父程序的地址空間，或者載入新的程式。
*   **程序終止:** 程序執行完最後一條語句後，會請求作業系統將其刪除 (exit)。作業系統會回收程序的資源。
*   **父程序終止子程序:** 父程序可以終止子程序的執行 (abort)。常見的原因包括：
    *   子程序超出了分配的資源。
    *   分配給子程序的任務不再需要。
    *   父程序正在退出。
*   **殭屍程序和孤兒程序:** 如果沒有父程序等待子程序，則終止的子程序會變成殭屍程序。如果父程序終止，則子程序會變成孤兒程序。

### 五、執行緒 (Threads)

*   **執行緒的概念:** 執行緒是程序中的一個執行單元，允許程序在單一程序中同時執行多個任務。
*   **多執行緒的優點:** 多執行緒可以提高程序的效率和效能，例如可以同時處理多個使用者請求或執行多個計算任務。

### 六、程序在 Linux 中的表示

*   **task\_struct 結構體:** 在 Linux 中，程序由 C 語言結構體 `task_struct` 表示。該結構體包含程序的各種資訊，例如程序識別碼 (PID)、程序狀態、排程資訊、父程序、子程序、已開啟檔案列表和地址空間等。

### 七、多工處理在行動系統中的應用

*   **iOS 的多工處理:** 由於螢幕空間和使用者介面限制，iOS 提供以下多工處理方式：
    *   單一前景程序：透過使用者介面控制。
    *   多個背景程序：駐留在記憶體中，正在執行，但不在螢幕上顯示，並且有限制。
    *   限制包括：單一、短期任務，接收事件通知，特定長期執行任務，例如音訊播放。
*   **Android 的多工處理:** Android 執行前景和背景程序，限制較少。
    *   背景程序使用服務來執行任務。
    *   即使背景程序被暫停，服務也可以繼續執行。
    *   服務沒有使用者介面，記憶體使用量較小。

### 八、上下文切換 (Context Switch)

*   **上下文切換的定義:** 當 CPU 切換到另一個程序時，系統必須儲存舊程序的狀態，並載入新程序的已儲存狀態，這個過程稱為上下文切換。
*   **上下文切換的開銷:** 上下文切換時間是系統開銷，系統在切換過程中沒有執行任何有用的工作。作業系統和 PCB 越複雜，上下文切換的時間就越長。
*   **硬體支援:** 上下文切換時間還取決於硬體支援。某些硬體為每個 CPU 提供多組暫存器，允許同時載入多個上下文。

### 九、瀏覽器 (Browser)

*   **單程序瀏覽器 (Single process Browser:** 許多早期的網頁瀏覽器以單一程序執行 (有些仍然如此)。如果一個網站出現問題，整個瀏覽器可能會掛起或崩潰。
*   **多程序瀏覽器 (Multiprocess Browser):** Google Chrome 瀏覽器是多程序的，具有三種類型的程序：
    *   瀏覽器程序：管理使用者介面、磁碟和網路輸入/輸出。
    *   渲染程序：渲染網頁，處理 HTML、Javascript，每個開啟的網站都有一個新的渲染程序。
    *   外掛程序：每種類型的外掛都有一個外掛程序。
*   **沙箱技術 (Sandbox):** 渲染程序在沙箱中執行，限制其磁碟和網路輸入/輸出，最大限度地減少安全漏洞的影響。