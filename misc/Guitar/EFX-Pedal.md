
# 吉他破音效果器設計方針  

> 資料來源:  
> 1. https://www.wamplerpedals.com/blog/uncategorized/2020/05/how-to-design-a-basic-overdrive-pedal-circuit/
> 2. https://www.taiwanaccess.com.tw/blog/posts/riversidesuset

> 破音效果器主要是由  
> 非反向放大器 + 二極體軟削波

## 主要有以下幾個部分

### 1. Input  
![input.png](https://github.com/codingpeanut/gist-images/blob/d9e2ef470d3fb793276ffb4b7f4fcdcadfc785a1/Note/Guitar/raw/input.png?raw=true)  
**用途:**  
接收來自吉他的輸入訊號，並濾除輸入訊號的雜訊。  
**原理:**  
利用限流電阻防止輸入電壓過大。再通過濾波電容濾除雜訊，避免後續雜訊被放大。  

### 2. Power  
![power.png](https://github.com/codingpeanut/gist-images/blob/d9e2ef470d3fb793276ffb4b7f4fcdcadfc785a1/Note/Guitar/raw/power.png?raw=true)  
**用途:**  
提供運算放大器穩定的工作電壓。  
**原理:**  
利用電阻組成分壓電路，以滿足運算放大器工作電壓。  
**作法:**  
- **電池（BAT1）**：電池為電路提供主要電源  
- **電容（C30 和 C27）**：濾除電池電壓的雜訊  
- **電阻（R32、R33 和 R41）**：限制電流並提供電壓  
	

### 3. Volume  
![volume-control.png](https://github.com/codingpeanut/gist-images/blob/d9e2ef470d3fb793276ffb4b7f4fcdcadfc785a1/Note/Guitar/raw/volume-control.png?raw=true)  
**用途:**  
控制音量大小  
**原理:**  
串接一顆大電容，以濾除高頻雜訊，並提升順態響應能力。再串聯可變電阻做一個可變分壓電路 (variable voltage divider)，控制輸出電壓。  
**作法:**  
`輸出電容`串聯`Volume旋鈕`  

### 4. Gain  
![gain-control.png](https://github.com/codingpeanut/gist-images/blob/d9e2ef470d3fb793276ffb4b7f4fcdcadfc785a1/Note/Guitar/raw/gain-control.png?raw=true)  
**用途:**  
調整增益大小  
**原理:**  
調整負回授的電阻大小，控制增益。  
**作法:**  
在負回授上加一顆可變電阻  
**備註:**  
為了使整個運算放大器電路更穩定、更安靜，最好將一個`大電容`、`二極體`和`Gain旋鈕`並聯，有助於控制一些削波信號的毛刺。  
`it’s good practice to put a small capacitor in parallel in parallel with the diodes and gain pot, as this helps sort of make the whole op amp circuit a little more stable, a little quieter, and controls some of the “fizz” inherent when clipping a signal.`  

### 5. Tone  
![tone-control.png](https://github.com/codingpeanut/gist-images/blob/d9e2ef470d3fb793276ffb4b7f4fcdcadfc785a1/Note/Guitar/raw/tone-control.png?raw=true)  
**用途:**  
控制高頻多寡，以調整聲音亮度  
**原理:**  
用電容+可變電阻做可變低通濾波器  
**作法:**  
在輸出`電容`和`Volume旋鈕`之間放一個`Tone旋鈕`+`小電容`  
	

## 原理補充

### 運算放大器 Operation Amplifier  
提供電壓增益 ，以提供足夠高的電壓進行削波，進而產生 Overdrive 或 Distortion。  

### 濾波電容  
$$Z_c = \frac{1}{jωC}$$
$Z_C$ 是電容的阻抗 (ohm)  
$j$ 是虛數單位 (imaginary unit)  
$ω$ 是角頻率 (rad/s)  
$C$ 是電容值 (Farad)  
分為旁路電容與去耦電容。主要目的是為了能夠迅速提供或吸收電荷，以幫助穩定電壓。  

**1. 電容的選擇**  
- **陶瓷電容**: 有較小的體積和良好的高頻特性，通常用於高頻應用。  
- **鋁電解電容**: 具有較大的電容值，適合用於低頻應用。  

**2. 電容值選擇**  
適當的電容值是很重要的。一般情況下，0.1μF到10μF的範圍是常見的選擇。  

**3. 電壓額定值選擇**  
濾波電容應具有比其工作電壓更高的額定電壓，以增加安全裕度。  

**4. 擺放技巧**  
- **擺放位置**  
在擺放濾波電容時，應注意不要將電容擺放得太遠，擺放得太遠會導致走線的ESL升高，而影響到濾波的效果。另一方面，走線過長也容易導致電磁干擾的訊號竄進走線裡，所以電容與IC本體越近越好。  

- **電容並聯**  
  - **更好的高頻響應**：使用兩顆電容，它們的有效面積和電容會增加，這可能提供更低的ESL與ESR，因此在高頻時有更好的濾波效果。  
  - **熱分散**：兩顆電容可以分散熱量，有助於降低局部溫度，進而提高可靠性。  
  - **冗餘性**：在故障情況下，如果一顆電容失效，另一顆仍然可以提供部分的濾波功能。  

- **增加小電容**  
  - **大電容的作用**：  
    大電容主要負責過濾低頻Noise。它可以儲存較多的能量，因此當電路需要突然增加的電流時，它可以迅速提供所需的能量。此外，它也有助於穩定DC電壓，防止電源線上的電壓波動。  
  - **小電容的作用**：  
    小電容主要負責過濾高頻Noise。由於其較小的值，它具有較低的阻抗，並且在高頻率下能更快地反應。這對於消除由快速切換元件（例如數位IC）引起的高頻Noise非常有效。

### 常見的濾波器: 
**1. 低通濾波器**  
$$ H_{lp}(f) = \frac{1}{1 + j\frac{f}{f_c}} $$
其中 $f_c = \frac{1}{2\pi RC}$ 為截止頻率。超過截止頻率的部分會被濾除。  

**步驟:**  
- `Step1` 決定截止頻率 $f_c$  
- `Step2` 決定電阻大小  
- `Step3` 利用 $f_c = \frac{1}{2\pi RC}$ 計算電容大小  
