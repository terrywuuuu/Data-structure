# 資料結構作業

本專案整理資料結構課程的 C++ 作業，包含樹、圖、堆疊與位元運算等練習。每個 `.cpp` 檔案都是獨立程式，請分別編譯與執行。

## 作業內容

| 檔案 | 主題 | 功能摘要 |
| --- | --- | --- |
| `Stack.cpp` | 堆疊 | 讀取名稱與數值，依輸入順序以每組最多三筆資料分組，並依數值排列輸出。輸入空白行結束。 |
| `RBtree.cpp` | 紅黑樹 | 以 `Insert` 插入節點，並以 `Print` 輸出樹的節點、左右子樹與顏色。 |
| `Huffman.cpp` | Huffman 樹 | 根據符號及權重建立 Huffman 樹，再使用輸入的 0/1 編碼解碼。 |
| `biTree.cpp` | 二元樹 | 從輸入建立二元樹，並輸出前序（`prefix`）、中序（`infix`）或後序（`postfix`）走訪結果。 |
| `bitCal.cpp` | 位元運算 | 將含有 `~`、`&`、`^`、`|` 的運算式轉為後序表示式並計算。 |
| `BFS.cpp` | 廣度優先搜尋概念 | 在矩陣中模擬相鄰格子的逐步擴散，輸出完成所需時間；無法完成時輸出 `-1`。 |
| `Bellman.cpp` | Bellman-Ford | 計算有向加權圖從指定起點到各頂點的最短距離，並檢查可到達的負權重迴圈。 |

## 編譯與執行

需要已安裝並設定好的 MinGW-w64 g++。在專案資料夾的 PowerShell 終端機中，將 `<檔名>` 替換成要執行的程式名稱（不含 `.cpp`）：

```powershell
g++ -std=c++11 -Wall -Wextra <檔名>.cpp -o <檔名>.exe
./<檔名>.exe
```

例如：

```powershell
g++ -std=c++11 -Wall -Wextra Bellman.cpp -o Bellman.exe
./Bellman.exe
```

程式從標準輸入讀取資料，請依各作業要求輸入。也可以在 VS Code 中開啟 `.cpp` 檔，使用預設建置工作（`Ctrl+Shift+B`）編譯目前檔案；偵錯設定會先建置目前檔案，再啟動 GDB。

## VS Code 環境

`.vscode/` 保存此專案的建置、偵錯與編輯器設定。預設設定使用 `C:\MinGW\bin\g++.exe` 與 `C:\MinGW\bin\gdb.exe`；若 MinGW 安裝在其他位置，請修改 `.vscode/tasks.json` 和 `.vscode/launch.json` 中的執行檔路徑。
