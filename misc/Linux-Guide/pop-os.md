# My Pop!_OS Installation Script

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

### Sources
[Debian/Ubuntu Packages](https://apt.syncthing.net/)  
[Starting Syncthing Automatically](https://docs.syncthing.net/users/autostart.html#linux)  
[Discord for Linux](https://discord.com/api/download?platform=linux&format=deb)  
[Vencord](https://vencord.dev/download/)  
