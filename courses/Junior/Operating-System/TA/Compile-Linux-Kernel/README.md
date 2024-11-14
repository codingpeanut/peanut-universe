# Linux Kernel 編譯與安裝步驟

## 1. 查看當前 kernel 版本
```bash
uname -r
```

## 2. 檢查模組目錄
```bash
ll /lib/modules/
```

## 3. 更新與安裝所需套件
```bash
sudo apt update
sudo apt upgrade -y
sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev -y
```

## 4. 下載並解壓 kernel 原始碼
```bash
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.tar.xz
tar -xvf linux-6.1.tar.xz
cd linux-6.1
```

## 5. 進行 kernel 設定
```bash
make menuconfig
s <enter>
t <enter>
<space><enter>
< Save >
< Ok >
< Exit >
< Exit >
< Exit >
```

## 6. 編輯 `.config` 文件
使用 `vim` 編輯 `.config` 文件，刪除以下兩行：
```bash
vim .config
:g/CONFIG_SYSTEM_TRUSTED_KEYS="debian\/canonical-certs.pem"/d
:g/CONFIG_SYSTEM_REVOCATION_KEYS="debian\/canonical-revoked-certs.pem"/d
:wq
```


## 7. 編譯 kernel
```bash
make -j$(nproc)
```

## 8. 編譯 module
```bash
make modules -j$(nproc)
```

## 9. 安裝模組與 kernel
```bash
sudo make modules_install
sudo make install
```

## 10. 更新 GRUB 選單
```bash
sudo update-grub
```

## 11. 重啟系統
```bash
sudo reboot
```

## 12. 切換 kernel
- 開機時按 `F4` 進入 GRUB 選單
在選單中依序選擇
1. `Advanced options for Ubuntu`
2. 選擇要開機的 kernel。這裡選 `Ubuntu, with Linux 6.1.0`

## 13. 驗證是否切換成功
```bash
uname -r
```

https://phoenixnap.com/kb/build-linux-kernel
https://www.cyberciti.biz/faq/debian-redhat-linux-delete-kernel-command/
