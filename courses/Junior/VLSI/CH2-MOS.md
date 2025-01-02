# CH2 - The Metal – Oxide – Semiconductor ( MOS ) Transistor

### 1. NMOS 工作模式
- **截止區**:  
  $$I_D = 0$$  

- **線性區** (Triode Mode):  
  $$I_D = \beta \frac{W}{L} \left[(V_{GS} - V_T)V_{DS} - \frac{V_{DS}^2}{2}\right]$$  

- **飽和區** (Saturation Mode):  
  $$I_D = \frac{1}{2} \beta \frac{W}{L} (V_{GS} - V_T)^2$$  

### 2. MOSFET 參數
- **氧化層電容**:  
  $$C_{ox} = \frac{\varepsilon_{ox}}{t_{ox}}$$  

### 3. 閾值電壓 $V_T$ 的影響因素
- **Body Effect**:  
  $$V_T' = V_T + \gamma \left(\sqrt{V_{SB} + \phi_F} - \sqrt{\phi_F}\right)$$  

其中，$\gamma$ 是Body Effect系數，$\phi_F$ 是費米電位。

### 4. 電流-電壓特性
- **PMOS 線性區**:  
  $$I_D = \beta \frac{W}{L} \left[|V_{GS}| - |V_T|\right]|V_{DS}|$$  

- **PMOS 飽和區**:  
  $$I_D = \frac{1}{2} \beta \frac{W}{L} \left[|V_{GS}| - |V_T|\right]^2$$  
