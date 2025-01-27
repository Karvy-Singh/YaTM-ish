
#!/bin/bash

# Define variables
SCRIPT_NAME="windows.sh"
SERVICE_NAME="windows.service"
INSTALL_DIR="/usr/local/bin/$SCRIPT_NAME"
SERVICE_DIR="/etc/systemd/system/$SERVICE_NAME"

echo "Installing $SCRIPT_NAME..."

# Copy the script to /usr/local/bin
sudo cp "$(pwd)/$SCRIPT_NAME" "$INSTALL_DIR"
sudo chmod +x "$INSTALL_DIR"

# Create the systemd service file
echo "[Unit]
Description=Run windows.sh at startup
After=graphical.target

[Service]
ExecStart=/bin/bash $INSTALL_DIR
Restart=always
WorkingDirectory=/usr/local/bin
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/karvys/.Xauthority
StandardOutput=journal
StandardError=journal

[Install]
WantedBy=multi-user.target
" | sudo tee $SERVICE_DIR

# Reload systemd, enable and start the service
echo "Reloading systemd daemon..."
sudo systemctl daemon-reload
sudo systemctl enable $SERVICE_NAME
sudo systemctl start $SERVICE_NAME

echo "Installation complete. $SCRIPT_NAME will run on system startup."


