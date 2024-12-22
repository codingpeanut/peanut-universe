# 計算機韌體實驗

> 上課網址：  
高中生程式解題系統
www.zerojudge.tw

[ToC]

---
### week1
:::spoiler c039 3n + 1(易)、c007 TeX Quotes(易、模擬)

- [c039. 00100 - The 3n + 1 problem](https://zerojudge.tw/ShowProblem?problemid=c039)
```c++=
#include <bits/stdc++.h>
using namespace std;

int main() {
    int i, j;
	 
    while (cin >> i >> j) {
        int begin = min(i, j), stop = max(i, j), max_length = 1;

        for (int i = begin; i <= stop; i++) {
            int cycle_length = 1, n = i;

            while (n != 1) {
                if (n & 1) n = 3 * n + 1;
                else n = n / 2;
                cycle_length++;
            }

            max_length = max(max_length, cycle_length);
        }

        cout << i << ' ' << j << ' ' << max_length << "\n";
    }
	
    return 0;
}

```
https://www.mycompiler.io/view/AZ3C2cOFz04

- [c007. 00272 - TeX Quotes](https://zerojudge.tw/ShowProblem?problemid=c007)
```c++=
#include <iostream>
using namespace std;

int main() {
    char c;
    bool is_left = true;

    // TeX conversion
    while (cin.get(c)) {
        if (c == '\"') {
            cout << (is_left ? "``" : "''");
            is_left = !is_left;
        } else {
            cout << c;
        }
    }

    return 0;
}

```
https://www.mycompiler.io/view/JszmjZo4P7t
:::

---
### week2
:::spoiler c054 WERTYU(易、string(find))、e543 Palindromes(易、花時間、鏡像與迴文詞)
- [c054. 10082 - WERTYU](https://zerojudge.tw/ShowProblem?problemid=c054)
```c++=
#include <bits/stdc++.h>
using namespace std;

int main() {
    string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

    char c;
    while (cin.get(c)) {
        size_t key = keyboard.find(c);
        if (key != string::npos) {
            cout << keyboard[key - 1];
        } else {
            cout << c;
        }
    }
}

```
https://www.mycompiler.io/view/ChabdOgtNcy

- [e543. 00401 - Palindromes](https://zerojudge.tw/ShowProblem?problemid=e543)
```c++=
#include <bits/stdc++.h>
using namespace std;

bool is_palindrome(string s) {
    string s_rev = s;
    reverse(s_rev.begin(), s_rev.end());
    return s == s_rev;
}

bool is_mirrored(string s) {
    string mirrorable = "AEHIJLMOSTUVWXYZ12358";
    string mirrored = "A3HILJMO2TUVWXY51SEZ8";
    
    size_t mid = s.length() / 2;
    for (int i = 0; i < mid; i++) {
        int index = mirrorable.find(s[i]);
        if (index != string::npos)
            s[i] = mirrored[index];
    }

    string s_rev = s;
    reverse(s_rev.begin(), s_rev.end());
    return s == s_rev;
}

int main() {
    string s;

    while (cin >> s) {
        if (is_mirrored(s) && is_palindrome(s))
            cout << s << " -- is a mirrored palindrome.\n";
        else if (is_mirrored(s))
            cout << s << " -- is a mirrored string.\n";
        else if (is_palindrome(s))
            cout << s << " -- is a regular palindrome.\n";
        else
            cout << s << " -- is not a palindrome.\n";
    }
    
    return 0;
}

```
https://www.mycompiler.io/view/7HApWIIHi4t
:::



---
### week3
::: spoiler d132 Master-Mind Hints(難、寫程式碼要時間)、e558 Digit Generator(易、建表、一定要先看題目)
- [d132 00340 - Master-Mind Hints](https://zerojudge.tw/ShowProblem?problemid=d132)
```c++=
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1000

int main() {
    int N, game_label = 1;
    int guess[MAX_N], solution[MAX_N];
    bool matched[MAX_N], guessed[MAX_N];

    while (cin >> N && N != 0) {
        cout << "Game " << game_label++ << ":\n";

        for (int i = 0; i < N; i++) cin >> solution[i];

        while (true) {
            memset(matched, false, MAX_N);
            memset(guessed, false, MAX_N);
            int A = 0, B = 0, zero = 0;

            for (int i = 0; i < N; i++) {
                cin >> guess[i];
                if (guess[i] == 0) {
                    zero++;
                } else if (guess[i] == solution[i]) {    // A 是在同位置 match (先篩掉 A)
                    A++;
                    matched[i] = guessed[i] = true;
                }
            }

            if (zero == N) break;                        // 表示輸入結束

            for (int i = 0; i < N; i++) {
                if (guessed[i]) continue;                // 代表第 i 個已經在上一部分被 match 過了，跳過不處理
                for (int j = 0; j < N; j++) {            // 若第 j 個解被猜到，且沒被 match 過
                    if (guess[i] == solution[j] && !matched[j]) {
                        B++;
                        matched[j] = true;               // B 是在不同位置 match
                        break;
                    }
                }
            }

            cout << "    (" << A << "," << B << ")\n";
        }
    }

    return 0;
}

```
https://www.mycompiler.io/view/5ZpJWeGKeVy

- [e558. 01583 - Digit Generator](https://zerojudge.tw/ShowProblem?problemid=e558)
```c++=
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100000

int main() {
    int T, N;
    int generators[MAX_N + 1] = {0};         // 0 代表沒有 generator。記得陣列要開到 100001

    // 用 digit-sum 反推 generator。因為數字很大所以要建表
    for (int i = 1; i < MAX_N; i++) {
        int generator = i, digit_sum = i;    // 固定 i = generator
        while (generator) {
            digit_sum += generator % 10;     // 各位數的和
            generator /= 10;
        }
        if (!generators[digit_sum])
            generators[digit_sum] = i;       // i = 某 digit_sum 的 generator
    }

    cin >> T;
    while (T--) {
        cin >> N;
        cout << generators[N] << "\n";
    }

    return 0;
}

```
https://www.mycompiler.io/view/DQEfZ4c0bgn
:::



---
### week4
:::spoiler b123 最大矩形(中難、DP)、j121 Ancient Cipher(易、STL Sort)
- [b123. 最大矩形 (Area)](https://zerojudge.tw/ShowProblem?problemid=b123)
```c++=
#include <cstring>
#include <iostream>
using namespace std;

#define SIZE 201

int main() {
    int M, N;
    int matrix[SIZE][SIZE], height[SIZE];

    while (cin >> M >> N) {
        // 初始化矩陣和高度陣列
        memset(matrix, 0, sizeof(matrix));
        memset(height, 0, sizeof(height));

        // 讀取矩陣數據
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cin >> matrix[i][j];
            }
        }

        int maxArea = 0;

        // 遍歷每一行
        for (int i = 0; i < M; i++) {               // 最大矩形 = 最小高度 * 持續寬度
            // 更新當前行的高度陣列
            for (int j = 0; j < N; j++) {
                if (matrix[i][j])
                    height[j]++;                    // 如果有值，那該行累積高度 + 1
                else
                    height[j] = 0;                  // 若沒有值，該行累積高度歸零

                int minHeight = height[j];
                maxArea = max(maxArea, minHeight);  // 要考慮最小高度是否大於當前最大面積
                
                // 向左掃描，計算可能的最大矩形面積
                int left = j - 1;
                while (left >= 0 && matrix[i][left] == 1) {
                    minHeight = min(minHeight, height[left]);        // 更新最小高度
                    left--;
                    maxArea = max(maxArea, minHeight * (j - left));  // 最大矩形 = 最小高度 * 持續寬度
                }
            }
        }

        cout << maxArea << '\n';
    }
    return 0;
}

```
https://www.mycompiler.io/view/2DRkudeZhWL


- [j121. 01339 - Ancient Cipher](https://zerojudge.tw/ShowProblem?problemid=j121)
```c++=
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    string s1, s2;
    while (cin >> s1 >> s2) {
        if (s1.length() != s2.length()) {
            cout << "NO\n";
            continue;
        }

        vector<int> freq1(26, 0), freq2(26, 0);

        // Calculate frequency of each character in both strings
        for (char c : s1) {
            freq1[c - 'A']++;
        }
        for (char c : s2) {
            freq2[c - 'A']++;
        }

        // Sort the frequency arrays
        sort(freq1.begin(), freq1.end());
        sort(freq2.begin(), freq2.end());

        // Check if sorted frequency arrays are identical
        if (freq1 == freq2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}

```
https://www.mycompiler.io/view/65V1jLdCxOR
:::



---
### week5
:::spoiler e541 marble(易、sort、lowerbound)、c073 Blocks Problem(難、堆疊、模擬)
- [e541. 10474 - Where is the marble](https://zerojudge.tw/ShowProblem?problemid=e541)
```c++=
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 10000

int main() {
    int N, Q, caseNum = 0;
    int stone[MAX_N];
    
    while (cin >> N >> Q && (N || Q)) {
        cout << "CASE# " << ++caseNum << ":" << endl;

        for (int i = 0; i < N; ++i)
            cin >> stone[i];
        
        sort(stone, stone + N);

        while (Q--) {
            int query;
            cin >> query;

            int position = -1;
            for (int i = 0; i < N; i++) {
                if (stone[i] == query) {
                    position = i;
                    break;
                }
            }

            if (position != -1)
                cout << query << " found at " << position + 1 << endl;
            else
                cout << query << " not found" << endl;
        }
    }

    return 0;
}

```
https://www.mycompiler.io/view/6kthhlH6vJH

- [c073. 00101 - The Blocks Problem](https://zerojudge.tw/ShowProblem?problemid=c073)
```c++=
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b, pos[25];
    string s1, s2;
    vector<int> block[25];  // 用 vector 代替 stack，因為 stack 輸出比較麻煩

    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            block[i].clear();
            block[i].push_back(i);  // 將每個方塊放在自己的堆中
            pos[i] = i;             // 每個方塊的位置為其初始位置
        }

        while (cin >> s1) {
            if (s1 == "quit") break;

            cin >> a >> s2 >> b;
            int pA = pos[a], pB = pos[b];

            if (pA == pB) continue;  // 若 a 和 b 在同一堆，忽略該命令

            if (s2 == "onto") {
                int height = block[pB].size();
                for (int i = height - 1; i >= 0; i--) {
                    if (block[pB][i] == b) break;                 // 找到 b 之後停止
                    pos[block[pB][i]] = block[pB][i];             // 設置這些方塊的初始位置
                    block[block[pB][i]].push_back(block[pB][i]);  // 將這些方塊移回初始位置
                    block[pB].pop_back();                         // 從當前堆中移除這些方塊
                }
            }

            if (s1 == "move") {
                int height = block[pA].size();
                for (int i = height - 1; i >= 0; i--) {
                    if (block[pA][i] == a) {     // 找到 a 之後停止
                        pos[block[pA][i]] = pB;  // 設置 a 的新位置
                        block[pB].push_back(a);  // 將 a 移動到 b 的堆
                        block[pA].pop_back();    // 從 a 的原堆中移除
                        break;
                    }
                    // 將 a 上面的方塊還原初始位置
                    pos[block[pA][i]] = block[pA][i];
                    block[block[pA][i]].push_back(block[pA][i]);
                    block[pA].pop_back();
                }
            } else if (s1 == "pile") {
                int height = block[pA].size();
                for (int i = height - 1; i >= 0; i--) {
                    if (block[pA][i] == a) {                    // 找到 a 之後停止
                        for (int j = i; j < height; j++) {
                            pos[block[pA][j]] = pB;             // 設置 a 及其上方所有方塊的新位置
                            block[pB].push_back(block[pA][j]);  // 將 a 及其上方所有方塊移到 b 的堆
                        }
                        for (int j = height; j > i; j--) {
                            block[pA].pop_back();               // 從 a 的原堆中移除這些方塊
                        }
                        break;
                    }
                }
            }
        }

        // 輸出每個方塊堆的狀態
        for (int i = 0; i < n; i++) {
            cout << i << ":";         // 輸出堆的編號
            for (int j : block[i]) {  // 輸出堆中的每個方塊
                cout << " " << j;
            }
            cout << "\n";
        }
    }
}

```
https://www.mycompiler.io/view/JjQ5n7zHvNc
:::




---
### week6
:::spoiler e155 Throwing cards away(易、queue、要先看題目)、f166 傳送點(難、BFS)
- [e155. 10935 - Throwing cards away I](https://zerojudge.tw/ShowProblem?problemid=e155)
```c++=
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        queue<int> cards;
        vector<int> discarded;

        // 初始化牌堆
        for (int i = 1; i <= n; ++i) {
            cards.push(i);
        }

        // 模擬丟棄和移動操作
        while (cards.size() > 1) {
            // 丟棄頂牌
            discarded.push_back(cards.front());
            cards.pop();
            // 移動新頂牌到牌底
            cards.push(cards.front());
            cards.pop();
        }

        // 輸出結果
        cout << "Discarded cards:";
        if (!discarded.empty()) {
            cout << " " << discarded[0];
            for (size_t i = 1; i < discarded.size(); ++i) {
                cout << ", " << discarded[i];
            }
        }
        cout << "\nRemaining card: " << cards.front() << "\n";
    }
    return 0;
}

```
https://www.mycompiler.io/view/EdBJULiZVY9


- [f166. 傳送點](https://zerojudge.tw/ShowProblem?problemid=f166)
```c++=
#include <iostream>
#include <queue>
using namespace std;

#define MAX_N 1000000

int main(void) {
    int n, P, L, R;
    int transmit[MAX_N] = {0}; // 儲存每個格子的傳送點
    int distance[MAX_N] = {0}; // 儲存每個格子的距離
    
    queue<int> points;   // 儲存要處理的點

    // 讀取輸入
    cin >> n >> P >> L >> R;
    for (int i = 0; i < n; i++) cin >> transmit[i]; // 讀取每個格子的傳送點

    // 將起點加入佇列
    points.push(0);

    while (true) {
        // 如果佇列為空，表示無法到達目標位置 P
        if (points.empty()) {
            cout << -1;
            break;
        }
 		
        // 從佇列中取出一個節點
        int s = points.front();
        points.pop();
		
        // 如果已經到達目標位置 P，輸出結果並結束迴圈
        if (s == P) {
            cout << distance[s];
            break;
        }
        
        // 向左移動 L 步
        int pos = s - L;
        if (pos >= 0) {                                 // 確保不超出左邊界
            int tx = transmit[pos];                     // 根據傳送點找到新的位置
            if (0 <= tx && tx < n) {                    // 確保新的位置在合法範圍內
                if (distance[tx] == 0) {                // 如果新位置尚未拜訪過
                    distance[tx] = distance[s] + 1;     // 更新新位置的距離
                    points.push(tx);                    // 將新位置加入佇列
                }
            }
        }
	 	
        // 向右移動 R 步
        pos = s + R;
        if (pos < n) {                                  // 確保不超出右邊界
        int tx = transmit[pos];                         // 根據傳送點找到新的位置
            if (0 <= tx && tx < n) {                    // 確保新的位置在合法範圍內
                if (distance[tx] == 0) {                // 如果新位置尚未拜訪過
                    distance[tx] = distance[s] + 1;     // 更新新位置的距離，起點 s 步數 + 1步
                    points.push(tx);                    // 將新位置加入佇列
                }
            }
        }
    }
    return 0;
}

```
https://www.mycompiler.io/view/JDCkM940Nix
:::

---
### week7
:::spoiler b838 括號問題(易、注意輸出)、h028 砍樹(中難、模擬、花時間、要先看題目)
- [b838. 104北二2.括號問題](https://zerojudge.tw/ShowProblem?problemid=b838)
```c++=
#include <iostream>
#include <stack>
using namespace std;
 
int main() {
    int t;
    string str;
    
    cin >> t;
    while (t--) {
        int count = 0;
        stack<int> left;
        
        cin >> str;
        for (char c : str) {
            if (!left.empty() && left.top() == '(' && c == ')') {
                left.pop();
                count++;
            } else {
                left.push(c);
            }
        }

        if (!left.empty())
            cout << 0 << endl;
        else
            cout << count << endl;
    }
}

```
https://www.mycompiler.io/view/FFtCGzFcm21

- [h028. 202001_3 砍樹](https://zerojudge.tw/ShowProblem?problemid=h028)
```c++=
#include <bits/stdc++.h>

#define MAX_N 100000 + 10

using namespace std;

typedef struct Trees {
    int position;
    int height;
    int left;
    int right;
} Trees;

bool can_fall(const Trees trees[], int current) {
    // 如果(現在位置 - 樹高) >= 左鄰樹的位置，
    // 或  (現在位置 + 樹高) <= 右鄰樹的位置，代表可以砍
    return (trees[current].position - trees[current].height >= trees[trees[current].left].position ||
            trees[current].position + trees[current].height <= trees[trees[current].right].position);
}

int main() {
    int N, L;
    cin >> N >> L;

    int fall_trees = 0, max_height = 0;
    Trees trees[MAX_N];

    for (int i = 1; i <= N; i++)
        cin >> trees[i].position;

    for (int i = 1; i <= N; i++)
        cin >> trees[i].height;

    trees[0] = {0, 0, 0, 1};
    trees[N + 1] = {L, 0, N, N + 1};

    for (int i = 1; i <= N; i++) {
        trees[i].left = i - 1;
        trees[i].right = i + 1;
    }

    // cut tree
    int current = 1;
    while (1) {
        if (can_fall(trees, current)) {
            fall_trees++;
            // 紀錄 max height
            max_height = max(max_height, trees[current].height);
            // 移除鄰樹關係
            // 更新當前樹的左鄰樹的右鄰樹，指向當前樹的右鄰樹。
            trees[trees[current].left].right = trees[current].right;
            // 更新當前樹的右鄰樹的左鄰樹，指向當前樹的左鄰樹。
            trees[trees[current].right].left = trees[current].left;
            
            if (trees[current].left != 0)            // 決定下一棵需要檢查的樹
                current = trees[current].left;       // 如果當前樹的左鄰樹不是邊界樹，移動到左鄰樹
            else 
                current = trees[current].right;      // 否則移動到右鄰樹。
        } else {
            current = trees[current].right;          // 不能倒的話往右變走
        }
        if (current > N) break;                      // 直到遇到邊界
    }

    cout << fall_trees << "\n" << max_height << "\n";

    return 0;
}

```
https://www.mycompiler.io/view/8li9u6yAnd8
:::



---
### week8
:::spoiler d217 Hangman Judge(中、unordered_set)、f698 後序運算式求值(易、要先看題目)
- [d217. 00489 - Hangman Judge](https://zerojudge.tw/ShowProblem?problemid=d217)
```c++=
#include <iostream>
#include <unordered_set>
using namespace std;

string hangman_judge(const string &sol_str, const string &guess_str) {
    unordered_set<char> solution(sol_str.begin(), sol_str.end());
    unordered_set<char> guess;
    int wrong_count = 0;

    for (char c : guess_str) {
        if (guess.find(c) != guess.end()) continue; // Skip already guessed letters
        guess.insert(c);
        if (solution.find(c) != solution.end()) {
            solution.erase(c);
            if (solution.empty()) return "You win.";
        } else {
            wrong_count++;
            if (wrong_count == 7) return "You lose.";
        }
    }

    return "You chickened out.";
}

int main() {
    int n;
    while (cin >> n) {
        if (n == -1) break;
        string solution, guess;
        cin >> solution >> guess;
        cout << "Round " << n << "\n";
        cout << hangman_judge(solution, guess) << "\n";
    }
    return 0;
}

```
https://www.mycompiler.io/view/BG24lpPkjeI

- [f698. 後序運算式求值](https://zerojudge.tw/ShowProblem?problemid=f698)
```c++=
#include <bits/stdc++.h>
using namespace std;

int main() {
    string token;
    stack<int> operands;
    
    while (cin >> token) {
        if (token == "+" || token == "-" || token == "/" || token == "*") {
            int secondOperand = operands.top(); operands.pop();
            int firstOperand = operands.top(); operands.pop();
            
            if (token == "+") operands.push(firstOperand + secondOperand);
            if (token == "-") operands.push(firstOperand - secondOperand);
            if (token == "*") operands.push(firstOperand * secondOperand);
            if (token == "/") operands.push(firstOperand / secondOperand);
        } else {
            operands.push(stoi(token));
        }
    }
    
    cout << operands.top() << '\n';
    return 0;
}

```
https://www.mycompiler.io/view/9sRu7IBa4mq
:::




---
### week9
:::spoiler d244 一堆石頭(易、map)、e564 Team Queue(難、queue)
- [d244. 一堆石頭](https://zerojudge.tw/ShowProblem?problemid=d244)
```c++=
#include <bits/stdc++.h>
using namespace std;

int main() {
    map<int, int> stone;

    int n;
    while (cin >> n) stone[n]++;

    for (pair<int, int> s : stone) {
        if (s.second % 3 != 0) {
            cout << s.first << endl;
            break;
        }
    }

    return 0;
}

```
https://www.mycompiler.io/view/7c0rTasAujX

- [e564. 00540 - Team Queue](https://zerojudge.tw/ShowProblem?problemid=e564)
```c++=
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int scenario = 1;

    while (true) {
        int t;
        cin >> t;

        if (t == 0) break;

        unordered_map<int, int> personToTeam;
        vector<queue<int>> teamQueues(t);
        queue<int> teamOrder;
        unordered_map<int, bool> teamInQueue;

        // Read team members and map each person to their team
        for (int i = 0; i < t; ++i) {
            int n;
            cin >> n;
            for (int j = 0; j < n; ++j) {
                int person;
                cin >> person;
                personToTeam[person] = i;
            }
            teamInQueue[i] = false;
        }

        cout << "Scenario #" << scenario++ << endl;

        string command;
        while (cin >> command && command != "STOP") {
            if (command == "ENQUEUE") {
                int person;
                cin >> person;
                int team = personToTeam[person];
                
                if (!teamInQueue[team]) {
                    teamOrder.push(team);
                    teamInQueue[team] = true;
                }
                teamQueues[team].push(person);
            } else if (command == "DEQUEUE") {
                int frontTeam = teamOrder.front();
                int person = teamQueues[frontTeam].front();
                teamQueues[frontTeam].pop();
                
                cout << person << endl;

                if (teamQueues[frontTeam].empty()) {
                    teamOrder.pop();
                    teamInQueue[frontTeam] = false;
                }
            }
        }
        cout << endl;
    }

    return 0;
}

```
https://www.mycompiler.io/view/1nUaG0TGqtq
:::




---
### week10
:::spoiler e548 Guess DS(易、寫花時間)、d221 Add AI(易、priority queue)
- [e548. 11995 - I Can Guess the Data Structure!](https://zerojudge.tw/ShowProblem?problemid=e548)
```c++=
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main() {
    bool isStack, isQueue, isPriorityQueue;
    int commands, command, number, buffer;

    while (cin >> commands) {
        priority_queue<int> PQ;
        stack<int> S;
        queue<int> Q;

        isStack = isQueue = isPriorityQueue = true;
        while (commands--) {
            cin >> command >> number;
            if (command == 1)
                S.push(number), Q.push(number), PQ.push(number);
            else {
                if (S.empty() || S.top() != number)
                    isStack = false;
                else
                    S.pop();
                if (Q.empty() || Q.front() != number)
                    isQueue = false;
                else
                    Q.pop();
                if (PQ.empty() || PQ.top() != number)
                    isPriorityQueue = false;
                else
                    PQ.pop();
            }
        }

        if (!isPriorityQueue && !isQueue && !isStack)
            cout << "impossible\n";
        else if (isPriorityQueue + isQueue + isStack > 1)
            cout << "not sure\n";
        else if (isPriorityQueue)
            cout << "priority queue\n";
        else if (isQueue)
            cout << "queue\n";
        else
            cout << "stack\n";
    }
}

```
https://www.mycompiler.io/view/GgHkd5XatWG

- [d221. 10954 - Add Al](https://zerojudge.tw/ShowProblem?problemid=d221)
```c++=
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
 
int main() {
    int n, num, smallest1, smallest2;
    while (cin >> n){
        if (n == 0) break;
        priority_queue<int, vector<int>, greater<int>> pq;
        long long sum = 0;

        for (int i = 0; i < n; i++){
            cin >> num;
            pq.push(num);
        }

        for (int i = 0; i < n-1; i++){
            smallest1 = pq.top(); pq.pop();
            smallest2 = pq.top(); pq.pop();
            sum += smallest1 + smallest2;
            pq.push(smallest1 + smallest2);
        }

        cout << sum << endl;
    }
}

```
https://www.mycompiler.io/view/0KKAEs4CF5V
:::




---
### week11
:::spoiler h083 數位占卜(中、題目難懂)、f640 函數運算式求值(易、遞迴)
- [h083. 3. 數位占卜](https://zerojudge.tw/ShowProblem?problemid=h083)
```c++=
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int m, ans = 0;
    string s;
    unordered_set<string> unique;

    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        unique.insert(s);
    }

    for (string lot : unique) {
        int len = lot.length();
        // 檢查所有可能的前綴和後綴
        for (int i = 1; i <= len / 2; i++) {
            string prefix = lot.substr(0, i);
            string suffix = lot.substr(len - i, i);
            if (prefix == suffix) {
                string mid = lot.substr(i, len - 2 * i);
                if (unique.find(mid) != unique.end()) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}

```
https://www.mycompiler.io/view/DuBQW7oXWvR

- [f640. 函數運算式求值](https://zerojudge.tw/ShowProblem?problemid=f640)
```c++=
#include <iostream>
#include <string>
using namespace std;
 
int eval(){
    string input;            // 有可能 x = 1000，就要用 string ，不能用 char，
    cin >> input;
    if (input[0] == 'f') {
        int x = eval();
        return 2 * x - 3;
    } else if (input[0] == 'g') {
        int x = eval();
        int y = eval();
        return 2 * x + y - 7;
    } else if (input[0] == 'h') {
        int x = eval();
        int y = eval();
        int z = eval();
        return 3 * x - 2 * y + z;
    } else {
        return stoi(input);
    }
}

int main() {
    cout << eval() << endl;
    return 0;
}

```
https://www.mycompiler.io/view/BArFw7H9WbX
:::



---
### week12
:::spoiler f637 DF-expression(易、遞迴、要先看題目)、k733 磁軌移動序列(中難、模擬、要寫很久)
- [f637. DF-expression](https://zerojudge.tw/ShowProblem?problemid=f637)
```c++=
#include <iostream>
using namespace std;
 
int idx = -1;
string df_expr;
 
int countOnes(int width){
    idx++;
    if (df_expr[idx] == '0'){
        // 如果當前字元是 '0'，直接跳過
        return 0;
    } else if (df_expr[idx] == '1'){
        // 如果當前字元是 '1'，回傳當前區塊的面積
        return width * width;
    } else {
        // 當 df_expr[idx] == '2' 時，需要進一步分割
        int total_ones  = 0;
        for (int i = 0; i < 4; i++){
            total_ones += countOnes(width / 2);
        }
        return total_ones;
    }
}
 
int main() {
    int width;
    
    cin >> df_expr;
    cin >> width;
    
    cout << countOnes(width) << "\n";
}

```
https://www.mycompiler.io/view/2pWbcd4i5bh

- [k733. 3. 磁軌移動序列](https://zerojudge.tw/ShowProblem?problemid=k733)
```c++=
#include <iostream>
#include <string>
using namespace std;

int curr_index = 0; // 目前指令的索引

// 計算距離的函數，並回傳總距離以及頭尾位置
long long calc_distance(const string &instructions, int &head, int &tail) {
    long long total = 0, move;
    head = tail = -1; // 初始化頭尾位置為負數
    
    while (true) {
        // 如果當前索引超出指令長度，則回傳總距離
        if (curr_index >= instructions.length()) return total;
        
        // 如果是'T'指令，則解析移動距離，更新頭尾位置
        if (instructions[curr_index] == 'T') {
            move = stoi(instructions.substr(curr_index + 1, 2));
            curr_index += 3;                    // 移動到下一個指令位置
            
            if (tail < 0) head = move;          // 如果尾部位置還沒被設定，則設定頭部位置
            else total += abs(tail - move);     // 否則加上移動距離
            tail = move;
        } else if (instructions[curr_index] == 'L') {           // 如果是'L'指令
            int repeat = instructions[curr_index + 1] - '0';    // 解析重複次數
            curr_index += 2;                                    // 移動到下一個指令位置
            
            int loop_head, loop_tail;
            long long loop_distance = calc_distance(instructions, loop_head, loop_tail);    // 遞迴計算距離
            if (tail < 0) head = loop_head;                                                 // 如果尾部位置還沒被設定，則設定頭部位置
            else total += abs(tail - loop_head);                                            // 否則加上移動距離
            tail = loop_tail;
            total += loop_distance * repeat + abs(loop_head - loop_tail) * (repeat - 1);    // 加上迴圈移動距離
        } else {                // 如果是'E'指令
            curr_index += 1;    // 移動到下一個指令位置
            return total;       // 回傳總距離
        }
    }
}

int main() {
    string instructions;
    int head, tail;

    cin >> instructions; // 輸入指令
    long long total_distance = calc_distance(instructions, head, tail); // 計算總距離
    total_distance += abs(10 - head); // 加上頭部到10的距離
    
    cout << total_distance << endl; // 輸出總距離
    return 0;
}

```
https://www.mycompiler.io/view/GhEjyp4M4s5
:::