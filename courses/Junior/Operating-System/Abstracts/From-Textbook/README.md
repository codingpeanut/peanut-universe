# Textbook Abstracts

### 第一章：簡介 (Introduction)

*   **作業系統 (Operating System) 的目標和功能**: 作業系統的目標是為使用者提供一個方便操作的介面，並有效地管理系統資源。這包括管理計算機系統的各種組成元件，例如 CPU、記憶體 (Memory)、儲存裝置 (Storage devices) 和輸入輸出裝置 (Input/output devices) 等等。
    *   作業系統的功能包含處理程序管理 (Process management)、記憶體管理 (Memory management)、檔案系統 (File system) 和安全性 (Security) 等等。
*   **作業系統的類型**: 作業系統依其功能和設計目標可分為不同類型，包含批次處理系統 (Batch processing systems)、多程式設計系統 (Multiprogramming systems)、分時系統 (Time-sharing systems)、即時系統 (Real-time systems) 以及分散式系統 (Distributed systems) 等等。
    *   **分散式系統** (Distributed systems) 讓多台計算機得以協同工作，進而提供高可用性 (High availability) 和容錯能力 (Fault tolerance)。
        *   Hadoop 即為一個分散式系統的例子，它可以用來處理大量的資料。
*   **作業系統架構 (Operating system structures)**: 作業系統的架構描述了它的組成部分以及它們之間的關係。常見的架構包括單體式架構 (Monolithic structure)、分層式架構 (Layered approach)、微核心架構 (Microkernel) 等等。
    *   每種架構都有其優缺點。例如，單體式架構簡單易於實現，但擴展性和可維護性較差。
*   **計算機系統的組成元件**: 計算機系統由許多不同的組成元件所構成，包含 CPU (Central Processing Unit)、處理器 (Processor)、核心 (Core)、多核心 (Multicore)、多處理器 (Multiprocessor) 等等。
    *   幾乎所有系統現在都是多核心的，CPU 指的是計算機系統的單一計算單元，而核心和多核心則專指 CPU 上的一個或多個核心。
*   **位元圖 (Bitmaps)**: 位元圖是一個由 n 個二進位位元組成的字串，可以用來表示 n 個項目的狀態。例如，假設我們有幾個資源，每個資源的可用性由一個二進位位元的值表示：0 表示資源可用，而 1 表示資源不可用（反之亦然）。
    *   位元圖在表示大量資源的可用性時非常有用。例如，一個中等大小的磁碟機可能被分成數千個單獨的單元，稱為磁碟區塊 (Disk blocks)。位元圖可以用來表示每個磁碟區塊的可用性。

### 第二章：作業系統結構 (Operating-System Structures)

*   **作業系統服務**: 作業系統提供各種服務，例如程序管理 (Process management)、記憶體管理 (Memory management)、檔案系統 (File system)、輸入輸出管理 (Input/output management)、安全性 (Security) 等等，為使用者和應用程式提供方便的環境。
    *   這些服務可以分為程式執行 (Program execution)、輸入/輸出操作 (I/O operations)、檔案系統操作 (File-system manipulation)、通訊 (Communications) 以及錯誤偵測 (Error detection) 等類別。
*   **系統呼叫 (System calls)**: 系統呼叫是使用者程式與作業系統核心 (Kernel) 互動的介面，允許使用者程式請求作業系統提供的服務。
*   **作業系統結構 (Operating system structures)**: 作業系統可以採用不同的結構，例如單體式結構 (Monolithic structure)、分層式結構 (Layered approach)、微核心結構 (Microkernel) 等等。
    *   了解作業系統結構的優缺點可以幫助你更好地理解作業系統的設計和實現。
        *   例如，Android 作業系統採用分層式結構，最底層是 Linux 核心 (Linux kernel)，上層是各種系統服務和應用程式。
        *   Windows 10 則採用混合架構，提供子系統 (Subsystems) 來模擬不同的作業系統環境。
*   **單工 (Single-tasking) 和多工 (Multitasking) 系統**: 單工系統一次只能執行一個任務，而多工系統可以同時執行多個任務。
    *   Arduino 是一個單工系統的例子，一次只能執行一個程式草稿 (Sketch)。

### 第三章：處理程序 (Processes)

*   **程序 (Process) 的概念**: 程序是執行中程式的實例 (Instance)，包含程式碼 (Code)、資料 (Data)、執行狀態 (Execution state) 等等。程序是作業系統的基本執行單元 (Basic unit of execution)。
*   **程序狀態 (Process state)**: 程序在執行過程中會處於不同的狀態，例如新建 (New)、執行 (Running)、等待 (Waiting)、就緒 (Ready)、終止 (Terminated) 等等。了解程序狀態及其轉換是理解程序管理 (Process management) 的基礎。
*   **程序控制塊 (Process control block, PCB)**: PCB 是儲存程序相關資訊的資料結構，包含程序 ID (Process ID, PID)、程序狀態、程序計數器 (Program counter)、CPU 暫存器 (CPU registers) 等等。PCB 是作業系統管理程序的重要依據。
*   **程序建立 (Process creation) 和終止 (Process termination)**: 作業系統提供了系統呼叫 (System calls) 來建立和終止程序。了解程序建立和終止的步驟是理解程序管理的基礎。
    *   在 UNIX 系統中，子程序 (Child process) 會自動繼承父程序 (Parent process) 建立的管道 (Pipes)，但 Windows 則需要程式設計師指定子程序要繼承的屬性。
    *   當一個程序終止時，它的資源會被作業系統回收。然而，它在程序表 (Process table) 中的項目必須保留到父程序呼叫 wait() 為止，因為程序表中包含程序的退出狀態 (Exit status)。一個已經終止但其父程序尚未呼叫 wait() 的程序稱為殭屍程序 (Zombie process)。所有程序在終止時都會轉變為這個狀態，但通常它們只會短暫地以殭屍程序的形式存在。一旦父程序呼叫 wait()，殭屍程序的程序 ID 和它在程序表中的項目就會被釋放。
*   **程序間通訊 (Interprocess communication, IPC)**: IPC 是程序之間交換資訊的機制，常見的 IPC 機制包括共享記憶體 (Shared memory)、訊息傳遞 (Message passing)、管道 (Pipes) 等等。了解不同的 IPC 機制及其優缺點是設計和實現多程序應用程式的關鍵。
    *   訊息傳遞 (Message passing) 提供了一種機制，允許程序在不共享相同地址空間的情況下進行通訊和同步動作。它在分散式環境中特別有用，在這種環境中，通訊程序可能駐留在透過網路 (Network) 連接的不同計算機上。
        *   在使用訊息傳遞時，訊息可以透過直接 (Direct communication) 或間接通訊 (Indirect communication) 傳遞。此外，訊息佇列 (Message queue) 的大小可以是有界的 (Bounded capacity) 或無界的 (Unbounded capacity)。
        *   Mach 訊息傳遞系統是訊息傳遞的一種實現，它使用端口 (Ports) 和端口權限 (Port rights) 來管理程序間的通訊。
    *   共享記憶體 (Shared memory) 允許程序透過共享一個共同的記憶體區域來進行通訊。
        *   POSIX (Portable Operating System Interface) 提供了一組標準的 API (Application Programming Interface) 來建立和管理共享記憶體物件。
*   **執行緒 (Thread)**: 執行緒是程序內部的執行單元，可以共享程序的資源。執行緒可以提高程序的執行效率，特別是在多核心處理器 (Multicore processors) 上。
    *   一個執行緒包含執行緒 ID (Thread ID, TID)、程式計數器 (Program counter, PC)、暫存器組 (Register set) 和堆疊 (Stack)。它與屬於同一個程序的其他執行緒共享其程式碼區段 (Code section)、資料區段 (Data section) 和其他作業系統資源，例如打開的檔案和訊號 (Signals)。
    *   Java 語言提供了 `Runnable` 介面來建立執行緒。

### 其他重要概念

*   **安全性 (Security)**: 系統安全涉及保護計算機資源免遭未經授權的訪問、惡意破壞或更改，以及意外引入的不一致性。
    *   作業系統安全功能是一個快速發展的研究和實施領域。
*   **保護 (Protection)**: 保護是指控制程序和使用者對計算機系統所定義資源的訪問的一系列機制。


**請注意：** 以上重點整理僅供參考，實際考試範圍可能有所不同。建議您仔細閱讀教科書和上課筆記，並多做練習題以加深理解。
