#!/bin/bash

# Define variables
SCRIPT_NAME="windows.sh"
SERVICE_NAME="windows.service"
INSTALL_DIR="$(pwd)/$SCRIPT_NAME"
SERVICE_DIR="/etc/systemd/system/$SERVICE_NAME"

echo "Installing $SCRIPT_NAME..."

echo "[Unit]
Description=Run windows.sh at startup
After=

[Service]
ExecStart=/usr/bin/nohup $INSTALL_DIR
Restart=always
WorkingDirectory=$(pwd)

[Install]
WantedBy=multi-user.target
" | sudo tee $SERVICE_DIR

# Copy the script to /usr/local/bin
sudo chmod +x $INSTALL_DIR

# Enable and start the service
sudo systemctl enable $SERVICE_NAME
sudo systemctl start $SERVICE_NAME


echo "Reloading systemd daemon..."
sudo systemctl daemon-reload

echo "Installation complete. $SCRIPT_NAME will run on system startup."

