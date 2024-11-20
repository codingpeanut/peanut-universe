# t-test
### **股票回報率比較**
   在金融市場中，T 檢定可以用來比較兩個股票或基金的回報率，檢查它們之間是否有顯著的差異。投資者可以使用 T 檢定來分析不同的投資策略、資產組合或基金表現。

   **例子**：比較兩個基金的年回報率是否存在顯著差異，從而幫助投資者做出選擇。

   ```python
   # 基金A和基金B的年回報率數據
   fund_A_returns = np.array([0.05, 0.06, 0.04, 0.07, 0.08, 0.05, 0.06, 0.07, 0.05, 0.06])
   fund_B_returns = np.array([0.04, 0.05, 0.03, 0.06, 0.07, 0.04, 0.05, 0.06, 0.04, 0.05])

   # 執行雙樣本T檢定
   t_stat, p_value = stats.ttest_ind(fund_A_returns, fund_B_returns)

   print(f"T統計量: {t_stat}")
   print(f"P值: {p_value}")

   # 判斷是否拒絕原假設
   alpha = 0.05
   if p_value < alpha:
       print("拒絕原假設：兩個基金的回報率有顯著差異")
   else:
       print("不能拒絕原假設：兩個基金的回報率無顯著差異")
   ```
