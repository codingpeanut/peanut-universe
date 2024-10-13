
- TigerVNC Server
```bash
sudo vi /etc/systemd/system/vncserver@1.service


[Unit]
Description=Remote desktop service (VNC)
After=syslog.target network.target

[Service]
Type=simple
User="your username"
PAMName="your username"
PIDFile=/home/pi/.vnc/%H%i.pid
ExecStart=/usr/bin/tigervncserver :10
ExecStop=/usr/bin/tigervncserver -kill%i

[Install]
WantedBy=multi-user.target


sudo systemctl enable vncserver@1.service
sudo systemctl start vncserver@1.service
```

- Connect to the TigerVNC Server
For example: 
```
192.168.0.1:5901
```

- Credits
[startup](https://groups.google.com/g/tigervnc-users/c/2_--QTgJmjA/m/J_w1TQNgAwAJ)
