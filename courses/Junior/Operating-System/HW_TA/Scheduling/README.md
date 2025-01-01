### **Waiting Time (WT)**、**Turnaround Time (TAT)** 和 **Response Time (RT)** 的公式整理：

---

### **1. Turnaround Time (TAT, 周轉時間)**  
$$ 
\text{Turnaround Time} = \text{Completion Time} - \text{Arrival Time}
$$     
- **Completion Time** 是作業完成的時間點。
- **Arrival Time** 是作業到達的時間點。

---

### **2. Waiting Time (WT, 等待時間)**  
$$ 
\text{Waiting Time} = \text{Turnaround Time} - \text{Burst Time}
$$     
- **Burst Time** 是作業的執行時間。

---

### **3. Response Time (RT, 回應時間)**  
$$ 
\text{Response Time} = \text{First Execution Time} - \text{Arrival Time}
$$     
- **First Execution Time** 是作業首次開始執行的時間點。

---

### 總結  

| 指標             | **公式**                                           | 說明                                       |
|------------------|---------------------------------------------------|------------------------------------------|
| **Waiting Time** | $WT = TAT - \text{Burst Time}$               | 作業等待的時間，不包括執行時間。             |
| **Turnaround Time** | $TAT = \text{Completion Time} - \text{Arrival Time}$| 作業從到達到完成的總時間。                  |
| **Response Time** | $RT = \text{First Execution Time} - \text{Arrival Time}$| 作業從到達到首次執行的時間，衡量系統反應速度。 |
