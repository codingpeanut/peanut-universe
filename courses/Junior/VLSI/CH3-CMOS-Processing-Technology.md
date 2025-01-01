# CH3 - CMOS Processing Technology

### 1. 矽氧化物 (SiO₂) 的成長
- **氧化速率**:
  $$  
  R_{oxidation} = k \cdot (P_{O_2})^n
  $$  
  其中，$R_{oxidation}$ 是氧化速率，$P_{O_2}$ 是氧氣壓力，$k$ 和 $n$ 是常數。

### 2. 雜質擴散 (Diffusion)
- **擴散方程**:
  $$  
  J = -D \frac{dC}{dx}
  $$  
  其中，$J$ 是擴散通量，$D$ 是擴散係數，$C$ 是濃度。

### 3. 雜質注入 (Ion Implantation)
- **注入濃度**:
  $$  
  N(x) = N_0 \cdot e^{-\frac{x}{\lambda}}
  $$  
  其中，$N(x)$ 是深度 $x$ 處的濃度，$N_0$ 是表面濃度，$\lambda$ 是衰減長度。

### 4. CMOS 技術參數
- **閾值電壓 $V_T$**:
  $$  
  V_T' = V_T + \gamma \left(\sqrt{V_{SB} + \phi_F} - \sqrt{\phi_F}\right)
  $$  
  其中，$\gamma$ 是Body Effect系數，$\phi_F$ 是費米電位。

### 5. 電流-電壓特性
- **NMOS 電流方程 (飽和區)**:
  $$  
  I_D = \frac{1}{2} \beta \frac{W}{L} (V_{GS} - V_T)^2
  $$  

- **PMOS 電流方程 (飽和區)**:
  $$  
  I_D = \frac{1}{2} \beta \frac{W}{L} \left[|V_{GS}| - |V_T|\right]^2
  $$  
