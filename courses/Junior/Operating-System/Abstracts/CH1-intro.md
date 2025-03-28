# CH1 - Introduction

### 1. 什麼是作業系統 (What is an Operating System)？

*   **定義**: 作業系統是一個作為電腦使用者和電腦硬體之間的中介程式的程式。
*   **功能**:
    *   資源管理器(Resource Allocator)：管理所有資源，並在資源使用衝突時做出決策，以確保資源的有效和公平使用。
    *   控制程式(Control Program)：控制程式的執行，以防止錯誤和不當使用電腦。
*   **目標**:
    *   執行使用者程式並簡化使用者解決問題的過程。
    *   使電腦系統使用起來更方便。
    *   有效地使用電腦硬體。
*   **組成**: 現代作業系統通常包括中介軟體(middleware)，它為應用程式開發人員提供額外的服務，例如資料庫、多媒體和圖形。

### 2. 電腦系統結構 (Computer System Structure)

*   **組成**: 電腦系統可分為四個組成部分：
    *   硬體(Hardware)：提供基本的運算資源，如 CPU、記憶體和 I/O 設備。
    *   作業系統(Operating System)：控制和協調各種應用程式和使用者之間的硬體使用。
    *   應用程式(Application Program)：定義使用系統資源來解決使用者計算問題的方法，例如文字處理器、編譯器、網路瀏覽器、資料庫系統和電玩遊戲。
    *   使用者(Users)：人、機器或其他電腦。
*   **運作**:
    *   一個或多個 CPU 和設備控制器透過共用匯流排連接，以提供對共用記憶體的存取。
    *   CPU 和設備會競爭記憶體週期，並發執行。

### 3. 中斷處理 (Interrupt Handling)

*   **中斷**: I/O 設備透過中斷通知 CPU 其操作已完成。
*   **中斷處理**:
    *   作業系統透過儲存暫存器和程式計數器來儲存 CPU 的狀態。
    *   透過輪詢或向量中斷系統確定發生的中斷類型。
    *   不同的程式碼區段會根據中斷類型決定要採取的動作。
*   **陷阱 (Trap)** 或 **異常 (Exception)**: 軟體產生的中斷，由錯誤或使用者請求引起。

### 4. I/O 結構 (I/O Structure)

*   **同步 I/O**: CPU 在 I/O 完成之前會一直等待，無法同時處理其他任務。
*   **非同步 I/O**: CPU 在 I/O 啟動後立即返回使用者程式，允許同時進行 I/O 處理。
*   **設備狀態表 (Device-Status Table)**: 包含每個 I/O 設備的類型、地址和狀態，作業系統透過它來確定設備狀態並修改表項以包含中斷資訊。

### 5. 儲存結構 (Storage Structure)

*   **主記憶體 (Main Memory)**: CPU 唯一可以直接存取的大容量儲存媒體，通常是揮發性記憶體，以動態隨機存取記憶體 (DRAM) 的形式出現。
*   **次要儲存體 (Secondary Storage)**: 主記憶體的延伸，提供大容量的非揮發性儲存空間。
    *   硬碟 (HDD)：由覆蓋著磁性記錄材料的剛性金屬或玻璃盤片組成，磁碟表面在邏輯上劃分為磁軌，磁軌又細分為扇區。
    *   非揮發性記憶體 (NVM) 設備：速度比硬碟快，非揮發性，隨著容量和效能的提升以及價格的下降，正變得越來越流行。
*   **儲存階層 (Storage Hierarchy)**: 儲存系統按速度、成本和揮發性分層組織。
    *   快取 (Caching)：將資訊複製到更快的儲存系統中；主記憶體可以被視為次要儲存體的快取。
      ![](https://github.com/codingpeanut/peanut-universe/blob/6a1f5ae95c4a0be0480f312b5330afa6c306723b/courses/Junior/Operating-System/Abstracts/assets/IMG_2778.jpeg)
*   **直接記憶體存取 (Direct Memory Access, DMA)**: 允許高速 I/O 設備在沒有 CPU 干預的情況下將資料直接傳輸到主記憶體，減少 CPU 的執行負擔。
    ![](https://github.com/codingpeanut/peanut-universe/blob/948acbe44ab82bbff851b1f4038504ac8e80d9a5/courses/Junior/Operating-System/Abstracts/assets/IMG_2787.jpeg)

### 6. 電腦系統架構 (Computer System Architecture)

*   **多處理器系統 (Multiprocessor Systems)**: 使用越來越廣泛，也越來越重要，也稱為平行系統或緊密耦合系統。
*   **多處理器系統的優點**:
    *   提高吞吐量。
    *   規模經濟。
    *   提高可靠性：優雅降級或容錯。
*   **多處理器系統的類型**:
    *   非對稱多處理 (Asymmetric Multiprocessing)：每個處理器被分配特定的任務。
    *   對稱多處理 (Symmetric Multiprocessing)：每個處理器執行所有任務。
*   **叢集系統 (Clustered Systems)**: 多個系統協同工作，通常透過儲存區域網路 (SAN) 共用儲存體，提供高可用性服務。

### 7. 作業系統操作 (Operating System Operations)

*   **開機程式 (Bootstrap Program)**: 在開機或重新開機時載入，初始化系統的所有方面，並載入作業系統核心並開始執行。
*   **作業系統核心**: 載入後啟動系統守護程式 (在核心外部提供的服務)。
*   **中斷驅動**: 作業系統是中斷驅動的，中斷可以來自硬體或軟體。
    *   硬體中斷：由其中一個設備產生。
    *   軟體中斷 (異常或陷阱)：
        *   軟體錯誤 (例如除以零)。
        *   作業系統服務請求 (系統呼叫)。
        *   其他程序問題，包括無限迴圈、程序修改彼此或作業系統。
*   **多程式設計 (Multiprogramming)** 和 **多工處理 (Multitasking)**: 為了提高效率，作業系統會使用多程式設計和多工處理。

### 8. 雙模式和多模式操作 (Dual-mode and Multimode Operation)

*   **雙模式操作**: 允許作業系統保護自身和其他系統組件，包括使用者模式和核心模式。
    *   模式位 (Mode bit) 由硬體提供，用於區分系統是執行使用者程式碼還是核心程式碼。
    *   某些指令被指定為特權指令，只能在核心模式下執行。
    *   系統呼叫會將模式更改為核心模式，從呼叫返回後會將其重置為使用者模式。
*   **多模式操作**: CPU 支援多種操作模式，例如虛擬機器管理器 (VMM) 模式，用於管理虛擬機器。

### 9. 虛擬化 (Virtualization)

*   **虛擬化**: 允許作業系統在其他作業系統中執行應用程式。
    *   模擬 (Emulation) 用於源 CPU 類型與目標類型不同時，例如 PowerPC 到 Intel x86。
    *   虛擬化是指作業系統和客戶作業系統都以原生方式編譯，例如 VMware 在原生 WinXP 主機作業系統上執行 WinXP 客戶機。
*   **虛擬機器管理器 (Virtual Machine Manager, VMM)**: 提供虛擬化服務。
*   **虛擬化的應用**: 包括在筆記型電腦和桌上型電腦上執行多個作業系統以進行探索或相容性測試、在沒有多個系統的情況下為多個作業系統開發應用程式、執行 QA 測試，以及在資料中心內執行和管理運算環境。
![](https://github.com/codingpeanut/peanut-universe/blob/00662920baa72d284dd0ae083f0672cba5ae808f/courses/Junior/Operating-System/Abstracts/assets/IMG_2788.jpeg)
![](https://github.com/codingpeanut/peanut-universe/blob/00662920baa72d284dd0ae083f0672cba5ae808f/courses/Junior/Operating-System/Abstracts/assets/IMG_2789.jpeg)

### 10. 核心資料結構 (Kernel Data Structures)

*   核心使用許多類似於標準程式設計資料結構的資料結構，例如：
    *   單向鏈結串列
    *   雙向鏈結串列
    *   環狀鏈結串列
    *   二元搜尋樹
    *   雜湊表
    *   位元圖 (Bitmap)

### 11. 運算環境 (Computing Environments)

*   **傳統運算環境**:
    *   獨立的通用機器。
    *   行動設備，如智慧型手機和平板電腦等。
*   **客戶端-伺服器運算 (Client-Server Computing)**: 瘦客戶機被智慧型個人電腦取代，許多系統現在都是伺服器，響應客戶端產生的請求。
*   **點對點 (Peer-to-Peer, P2P)**: 所有節點都被視為對等體，每個節點都可以充當客戶端、伺服器或兩者。
*   **雲端運算 (Cloud Computing)**: 透過網路將運算、儲存甚至應用程式作為服務交付，是虛擬化的邏輯延伸。
    *   雲端運算的類型：
        *   公有雲：任何願意付費的人都可以透過網際網路使用。
        *   私有雲：由公司為自身使用而運行。
        *   混合雲：包括公有雲和私有雲組件。
        *   軟體即服務 (SaaS)：透過網際網路提供一個或多個應用程式。
        *   平台即服務 (PaaS)：透過網際網路提供可供應用程式使用的軟體堆疊。
        *   基礎架構即服務 (IaaS)：透過網際網路提供伺服器或儲存體。
*   **即時嵌入式系統 (Real-Time Embedded Systems)**: 最普遍的電腦形式，種類繁多，包括特殊用途、有限用途的作業系統和即時作業系統。
    *   即時作業系統具有明確的固定時間限制，處理必須在限制內完成，只有滿足限制才能正確操作。
    *   即時系統可以是硬體即時或軟體即時。
        *   硬體即時：保證關鍵任務按時完成。
        *   軟體即時：關鍵的即時任務比其他任務具有更高的優先級，並保留該優先級直到完成。

### 12. 自由和開放原始碼作業系統 (Free and Open-Source Operating Systems)

*   **自由和開放原始碼軟體**: 以原始碼格式提供，而不是封閉原始碼和專有軟體。
*   **起源**: 由自由軟體基金會 (FSF) 發起，該基金會擁有「著作左」的 GNU 通用公共授權條款 (GPL)。
*   **例子**: GNU/Linux、BSD UNIX (包括 Mac OS X 的核心) 等等。

