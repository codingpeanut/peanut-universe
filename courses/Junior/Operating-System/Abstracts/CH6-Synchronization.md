### **第六章重點整理：進程同步 (Process Synchronization)**

#### **1. 核心概念 (Core Concepts)**

- **競態條件 (Race Condition)**：
  - 當多進程同時訪問共享數據，執行順序影響結果。
  - 解法：需透過同步機制實現**互斥 (Mutual Exclusion)**。
- **關鍵區域問題 (Critical Section Problem)**：
  - 每個進程有關鍵區域 (Critical Section) 需獨佔執行。
  - 滿足條件：
    1. **互斥 (Mutual Exclusion)**。
    2. **進度 (Progress)**。
    3. **有界等待 (Bounded Waiting)**。

---

#### **2. 經典同步問題與解法 (Classic Synchronization Problems and Solutions)**

1. **有界緩衝區問題 (Bounded-Buffer Problem)**:

   - Producer:
     ```c
     do {
         wait(empty);
         wait(mutex);
         // add item to buffer
         signal(mutex);
         signal(full);
     } while (true);
     ```
   - Consumer:
     ```c
     do {
         wait(full);
         wait(mutex);
         // remove item from buffer
         signal(mutex);
         signal(empty);
     } while (true);
     ```

2. **哲學家進餐問題 (Dining Philosophers Problem)**:

   - 基本解法：
     ```c
     do {
         wait(chopstick[i]);
         wait(chopstick[(i+1)%5]);
         // eat
         signal(chopstick[i]);
         signal(chopstick[(i+1)%5]);
         // think
     } while (true);
     ```
   - **考點 (Key Points)**：
     - 死鎖 (Deadlock)：如「所有哲學家同時拿起一隻筷子」。
     - 飢餓 (Starvation)：哲學家長期無法用餐。

3. **Peterson 解法 (Peterson's Algorithm)**:
   - 雙進程同步：
     ```c
     do {
         flag[i] = true;
         turn = j;
         while (flag[j] && turn == j);
         // critical section
         flag[i] = false;
     } while (true);
     ```
   - **考點 (Key Points)**：
     - 如何滿足互斥、進度、有界等待條件。
