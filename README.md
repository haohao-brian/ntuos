## 在64位元Ubuntu上安裝xv6，請遵循以下步驟：

安裝必要的開發工具和依賴項：
```
sudo apt install build-essential git gdb qemu-system
sudo apt install gcc-riscv64-linux-gnu g++-riscv64-linux-gnu binutils-riscv64-linux-gnu
```
下載xv6源碼：(下載我的xv6-riscv-riscv.zip也行)
```
git clone https://github.com/mit-pdos/xv6-riscv.git
```
切換到下載的xv6源碼目錄：
```
cd xv6-riscv
```
編譯xv6：
```
make
```
使用QEMU運行xv6：
```
make qemu
```
這將在QEMU模擬器中啟動xv6操作系統。您應該能夠看到xv6的提示符以及一些系統信息。

現在您已經在64位元的Ubuntu環境中安裝並運行了xv6。

## git by ssh
2. 設定 Git 的使用者名稱和電子郵件
在終端中，使用以下命令設定你的 Git 使用者名稱和電子郵件地址。 這些資訊將用於你的提交記錄：
```
git config --global user.name "你的名字"
git config --global user.email "你的郵件地址"
```
將 “你的名字” 和 “你的郵件地址” 換成你在 GitHub 上的使用者名稱和電子郵件地址。

 

3. 產生 SSH 密鑰

執行以下命令產生一個新的 SSH 密鑰，用於 GitHub：
```
ssh-keygen -t rsa -b 4096 -C “你的郵件地址”
```
請按照提示進行操作。 你可以設定密碼或直接按 Enter 鍵留空（不設定密碼）。 這將在 ~/.ssh 目錄下產生 id_rsa（私鑰）和 id_rsa.pub（公鑰）檔案。

 

4. 將 SSH 密鑰新增至 ssh-agent
首先，啟動 ssh-agent：
```
eval "$(ssh-agent -s)"
```
接著加入你的私鑰到 ssh-agent：
```
ssh-add -K ~/.ssh/id_rsa
```
5. 將 SSH 公鑰加入 GitHub

打開 ~/.ssh/id_rsa.pub 文件，並複製其內容。 你可以使用以下指令直接金鑰複製到剪貼簿。
```
cat ~/.ssh/id_rsa.pub | pbcopy
 ```

到 GitHub 網站登錄到你的帳戶後台。
前往設置（Settings）> SSH 和 GPG keys。
點擊 “New SSH key” 或 “Add SSH key”。
在 “Title” 欄位中輸入一個標籤，例如 “我的  Macbook Pro”。
在 “Key” 文字方塊中貼上你的公鑰。

點選 “Add SSH key” 儲存。
完成這些步驟後，你的 Mac 應該已經成功設定了 Git 和 SSH 密鑰，可以安全地連接到 GitHub 進行代碼的推送和拉取操作。
