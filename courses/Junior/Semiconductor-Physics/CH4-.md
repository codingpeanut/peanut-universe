# CH4 - 

#### 1. **半導體的基本概念**
   - 電子與電洞：導電帶中的電子和價電帶中的電洞。
   - 載子濃度的計算：利用態密度函數和費米分佈函數進行推導。
   - 平衡載子濃度：電子和電洞濃度相等的條件。

#### 2. **熱平衡下的電子與電洞分佈**
   - 平衡態下電子與電洞的分佈公式：
     - 導電帶中的電子濃度:  
       - $n_0 = \int_{E_c}^{\infty} g_c(E) f_F(E) dE$  
         - $g_c(E)$：導電帶中的態密度函數  
         - $f_F(E)$：費米-狄拉克分佈函數  
     - 價電帶中的電洞濃度  
       - $p_0 = \int_{-\infty}^{E_v} g_v(E) [1 - f_F(E)] dE$  
         - $g_v(E)$：價電帶中的態密度函數  
   - 本質半導體的特性：  
     - 電子濃度 $n_i$ 與電洞濃度 $p_i$ 相等。
     - 本質費米能階 $E_{Fi}$位於帶隙的中間。
       - **本質載子濃度**  
       - $n_i = p_i = \sqrt{N_c N_v} \exp\left(-\frac{E_g}{2kT}\right)$
         - $N_c$：導電帶有效態密度  
         - $N_v$：價電帶有效態密度  
         - $E_g$：帶隙能量
       - **費米能級位置**  
       - **本質半導體的費米能級** $E_{Fi} $：  
         - $E_{Fi} = \frac{E_c + E_v}{2} + \frac{kT}{2} \ln\left(\frac{m_h^*}{m_e^*}\right)$  
         - $m_h^* $ 和 $m_e^* $ 分別為電洞和電子的有效質量。  

#### 3. **掺雜半導體**
   - n型與p型半導體：
     - n型：加入施體雜質（如磷），提供額外的電子。
       - **導電帶中的電子濃度（n型半導體）**  
         - $n_0 = N_c \exp\left(-\frac{E_c - E_F}{kT}\right)$
       - 
     - p型：加入受體雜質（如硼），提供額外的電洞。
       - **價電帶中的電洞濃度（p型半導體）**  
         - $p_0 = N_v \exp\left(-\frac{E_F - E_v}{kT}\right)$
   - 雜質離子化能量：利用玻爾模型計算施體電子或受體電洞的激發能。
   - **電中性條件**
     - $n_0 + N_A^- = p_0 + N_D^+$
     - $N_A^-$：受體離子濃度  
     - $N_D^+$：施體離子濃度  

#### 4. **費米能階位置**
   - 本質半導體：費米能階位於導帶與價帶之間。
   - 掺雜半導體：
     - n型：費米能階靠近導帶。
     - p型：費米能階靠近價帶。
   - 受溫度和雜質濃度影響的費米能階位置計算。

#### 5. **離子化與凍結效應**
   - 完全離子化：室溫下，幾乎所有的施體或受體雜質完全離子化。
   - 凍結效應：在低溫下，施體或受體不能完全離子化。

#### 6. **載流子濃度的計算與範例**
   - 熱平衡條件下的載流子濃度公式。
   - 舉例計算：
     - n型與p型半導體中，主載子與少數載子的濃度。
     - 本質載子濃度隨溫度變化的關係。

#### 7. **補償半導體**
   - 同時存在施體和受體雜質的條件下的載流子分佈。
   - 電中性條件：
     $n_0 + N_A^- = p_0 + N_D^+$

#### 8. **應用與實例**
   - 計算本質半導體和掺雜半導體的載子濃度。
   - 計算費米能階的位置與離子化程度。
   - 給定條件下，確定最小的施體或受體濃度。

#### 9. **數學推導與公式**
   - 電子、電洞濃度的推導公式。
   - 費米狄拉克分佈與玻爾茲曼近似。
   - 本質載子濃度的乘積關係： $n_0 \cdot p_0 = n_i^2$。

#### 10. **特別注意**
   - 熟悉每個公式的適用條件（例如：高溫下的玻爾茲曼近似失效）。
   - 熟練掌握典型計算步驟與範例題解法。

你可以根據以上列點進一步補充細節或指定某些部分作為重點複習。