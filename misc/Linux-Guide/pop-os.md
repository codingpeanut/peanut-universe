# My Pop!_OS Installation Script

### Pop Shell
```bash
sudo apt install git node-typescript make gnome-shell-extension-prefs
git clone https://github.com/pop-os/shell.git
cd shell
git checkout master_noble
make local-install
```

### Pop Launcher
- launcher
```bash
sudo apt install cargo just
cd ~
git clone https://github.com/pop-os/launcher.git
cd launcher
just build-release # Build
just install # Install locally
```
- cosmic launcher
```bash
cd ~
sudo apt install cargo just intltool appstream-util desktop-file-utils libxkbcommon-dev pkg-config desktop-file-utils
sudo apt install rustup
rustup update stable
git clone https://github.com/pop-os/cosmic-launcher.git
cd cosmic-launcher
just
sudo just install
```
- onagre
```bash
cd ~
git clone https://github.com/oknozor/onagre.git
cd onagre
cargo build --release --locked
sudo mv target/release/onagre /usr/bin/onagre
```

<!--
### Gnome Shell Extensions
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install gnome-shell-extensions gnome-tweaks -y
# Install Dash to Dock, User Themes and Sound Input & Output Device Chooser
gnome-extensions install https://extensions.gnome.org/extension/307/dash-to-dock/
gnome-extensions install https://extensions.gnome.org/extension/750/user-themes/
gnome-extensions install https://extensions.gnome.org/extension/906/sound-output-device-chooser/
# Enable Extensions
gnome-extensions enable dash-to-dock@micxgx.gmail.com
gnome-extensions enable user-themes@gnome-shell-extensions.gcampax.github.com
gnome-extensions enable sound-output-device-chooser@kgshank.net
```
-->

### Chewing
```bash
sudo apt update
sudo apt install ibus-chewing
```
```bash
sudo apt install language-pack-zh-hant language-pack-gnome-zh-hant
sudo dpkg-reconfigure locales
locale
```

### Nerdfont

1. Download the Font
```bash
mkdir -p ~/.local/share/fonts
cd ~/.local/share/fonts
curl -fLo "JetBrainsMono.zip" https://github.com/ryanoasis/nerd-fonts/releases/latest/download/JetBrainsMono.zip
unzip JetBrainsMono.zip && rm JetBrainsMono.zip
```

2. Refresh the Font Cache
```bash
fc-cache -fv
```

### Neovim
```bash
curl -LO https://github.com/neovim/neovim/releases/latest/download/nvim.appimage
chmod u+x nvim.appimage
sudo mv nvim.appimage /usr/bin/nvim
export PATH="/usr/bin/nvim:$PATH"
```

### Lazyvim
```bash
git clone https://github.com/codingpeanut/lazy.nvim ~/.config/nvim
rm -rf ~/.config/nvim/.git
```

### Syncthing
```bash
sudo mkdir -p /etc/apt/keyrings
sudo curl -L -o /etc/apt/keyrings/syncthing-archive-keyring.gpg https://syncthing.net/release-key.gpg
sudo apt-get update
sudo apt-get install syncthing
```
```bash
mkdir ~/.config/autostart/
cp /usr/share/applications/syncthing-start.desktop ~/.config/autostart/
```

### Discord
```bash
wget -O discord.deb "https://discord.com/api/download?platform=linux&format=deb"
sudo apt install ./discord.deb
rm discord.deb
```

### Vencord
```bash
sh -c "$(curl -sS https://raw.githubusercontent.com/Vendicated/VencordInstaller/main/install.sh)"
```

### Chrome
```bash
sudo apt install wget
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo dpkg -i google-chrome-stable_current_amd64.deb
```

### Sources
[Debian/Ubuntu Packages](https://apt.syncthing.net/)  
[Starting Syncthing Automatically](https://docs.syncthing.net/users/autostart.html#linux)  
[Discord for Linux](https://discord.com/api/download?platform=linux&format=deb)  
[Vencord](https://vencord.dev/download/)  
[Pop Shell](https://github.com/pop-os/shell)
[Chewing](https://medium.com/@scofield44165/ubuntu-20-04%E4%B8%AD%E6%96%B0%E5%A2%9E%E6%96%B0%E9%85%B7%E9%9F%B3%E8%BC%B8%E5%85%A5%E6%B3%95-add-chinese-chewing-in-ubuntu-20-04-5ce78563638b)
