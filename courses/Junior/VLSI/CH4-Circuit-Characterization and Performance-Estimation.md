# CH4 - Circuit Characterization and Performance Estimation

## 電阻估算
1. **矩形形狀的電阻**：  
   $$R = \frac{L}{\sigma A}$$
   其中 $L$ 是導體長度， $\sigma$ 是導體的導電率， $A$ 是截面積。  

2. **MOS晶體管通道電阻**：  
   $$R_{on} = \frac{V_{GS} - V_T}{I_D}$$  
   其中 $V_{GS}$ 是閘極至源極電壓， $V_T$ 是閾值電壓， $I_D$ 是漏極電流。

## 電容估算
1. **閘極電容**：  
   $$C_g = C_{gb} + C_{gs} + C_{gd}$$  
   其中 $C_{gb}$ 是閘極至基板電容，$C_{gs}$ 和 $C_{gd}$ 分別是閘極至源極和漏極的電容。  

2. **總電容**：  
   $$C_{total} = C_w + C_{db1} + C_{db2}$$  
   其中 $C_w$ 是布線電容， $C_{db1}$ 和 $C_{db2}$ 是源/漏接面電容。

## 開關特性
1. **傳播延遲時間**：  
   $$t_{PHL} = t_{PLH} = R_{total} \cdot C_{load}$$  
   其中 $R_{total}$ 是總負載電阻， $C_{load}$ 是負載電容。

2. **上升和下降時間**：  
   $$t_r = t_f = 0.85 \cdot R \cdot C$$  
   其中 $R$ 是驅動器的輸出阻抗， $C$ 是負載電容。

## 功耗
1. **靜態功耗**：  
   $$P_{static} = I_{leakage} \cdot V_{DD}$$  

2. **動態功耗**：  
   $$P_{dynamic} = \alpha C_L V^2 f$$  
   其中  $\alpha$ 是切換因子， $C_L$ 是負載電容， $f$ 是頻率。
