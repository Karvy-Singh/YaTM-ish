#!/bin/bash

# Define variables
SCRIPT_NAME="windows.sh"
SERVICE_NAME="windows.service"
INSTALL_DIR="/usr/local/bin"
SERVICE_DIR="/etc/systemd/system"

echo "Installing $SCRIPT_NAME..."

# Copy the script to /usr/local/bin
sudo cp $SCRIPT_NAME $INSTALL_DIR/
sudo chmod +x $INSTALL_DIR/$SCRIPT_NAME

# Copy the service file to systemd
echo "Setting up systemd service..."
sudo cp $SERVICE_NAME $SERVICE_DIR/

# Enable and start the service
sudo systemctl enable $SERVICE_NAME
sudo systemctl start $SERVICE_NAME


echo "Reloading systemd daemon..."
sudo systemctl daemon-reload

echo "Installation complete. $SCRIPT_NAME will run on system startup."

