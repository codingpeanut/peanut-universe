# HOMEWORK II

### Programming Problem: Multithread Programming (Linux pthread / POSIX pthread)

- **Objective**:  
   Read data from a given file, use threads to sort the numbers and calculate summations, and finally, write the results to an output file.  
   *(從檔案讀入資料，利用 thread 將資料排序與相加，最後將結果輸出到另一個檔案)*

#### Example Data Format:
Each number in the file is separated by commas, with n rows and 4 columns. Refer to input.txt for an example.  
*(檔案內容範例如下，每個數字以逗點分開，一共 n 列 4 行，請參考附件 input.txt)*

1, 3, 7, 9
2, 4, 4, 11
15, 23, 24, 25
11, 22, 33, 44
...
...


---

### Requirements:

1. **Source File Input**:
   - Prompt the user to enter the source file name. If the file doesn’t exist, the user should be allowed to re-enter the file name or abort the execution.  
   *(讓使用者輸入來源檔案的檔名，若檔案不存在，則讓使用者重新輸入或選擇離開程式)*

2. **Destination File Output**:
   - Prompt the user to enter the destination file name. If a file with the same name already exists, the user should be able to:
     - (a) Enter a new file name
     - (b) Overwrite the existing file
     - (c) Exit the program  
     *(讓使用者輸入目的檔案的檔名，若有相同的檔名存在，則讓使用者選擇 (a) 重新輸入 (b) 覆蓋目的檔案 (c) 離開程式)*

3. **Threading**:
   - Create four pthreads. Each pthread should:
     - Sort one column of numbers from the file.
     - Calculate the summation of that column.
     - Write the sorted data and summation result to the output file, labeled with the thread number.  
     *(需產生 4 條 pthread，每一條 pthread 負責將一行資料排序並加總，且將排序完成的資料與加總的結果輸出，寫入檔案，並註明 thread 編號，格式請參考附件 output.txt)*

4. **Merging**:
   - Create a fifth pthread to merge the sorted results from the four threads, ensuring all numbers are in sequence.
   - Output the merged list to the output file with 40 numbers per line, each separated by a comma.  
   *(需產生 1 條 pthread 負責所有排序資料的整合 (merge)，將完整排序的資料輸出至檔案中，輸出格式為每 40 個數字一列，每個數字由逗號區隔，檔名由使用者指定，輸出格式請參考附件)*

   Example Output:
   
1, 2, 3, 4, 4, 7, 9, 11, 11, 15, 22, 23, 24, 25, 33, 44


---

### Compiler:
- Use **GNU gcc or g++** (Linux compatible)

### File Naming:
- **Source code**: s+StudentIDHW2.c
- **Executable**: s+StudentIDHW2.exe
  - Example: s400123123HW2.c, s400123123HW2.exe

---

### Notes:

- Late submissions will be accepted until **2024/12/30, 11:59 pm** with a penalty:
  - 1% deduction per day late, up to the deadline.
- **Do not copy others’ work**. Violations will result in a zero score.
