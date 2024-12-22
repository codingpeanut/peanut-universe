# Linux Kernel 編譯與安裝步驟

## 1. 查看當前 kernel 版本
```bash
sudo uname -r
```

## 2. 檢查模組目錄
```bash
ll /lib/modules/
```

## 3. 更新與安裝所需套件
```bash
sudo apt update
sudo apt install gcc make libncurses-dev flex bison libssl-dev libelf-dev initramfs-tools-bin
```

## 4. 下載並解壓 kernel 原始碼
```bash
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.2.7.tar.xz
tar -xvf linux-6.2.7.tar.xz
cd linux-6.2.7
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
make -j 4
```

## 8. 安裝模組與 kernel
```bash
sudo make modules_install
sudo make install
```

## 9. 重啟系統
```bash
sudo reboot
```

Source: 
- [Build linux kernel](https://phoenixnap.com/kb/build-linux-kernel)
- [Delete linux kernel](https://www.cyberciti.biz/faq/debian-redhat-linux-delete-kernel-command/)