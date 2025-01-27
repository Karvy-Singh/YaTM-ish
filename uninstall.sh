#!/bin/bash

# Variables
SERVICE_NAME="windows.service"
SERVICE_PATH="/etc/systemd/system/$SERVICE_NAME"
SCRIPT_PATH="/usr/local/bin/windows.sh" # Replace with the path to your script

# Stop the service
echo "Stopping the service..."
sudo systemctl stop $SERVICE_NAME

# Disable the service
echo "Disabling the service..."
sudo systemctl disable $SERVICE_NAME

# Remove the service file
if [ -f "$SERVICE_PATH" ]; then
    echo "Removing service file..."
    sudo rm "$SERVICE_PATH"
else
    echo "Service file not found at $SERVICE_PATH"
fi

# Remove the script
if [ -f "$SCRIPT_PATH" ]; then
    echo "Removing script..."
    rm "$SCRIPT_PATH"
else
    echo "Script not found at $SCRIPT_PATH"
fi

# Reload systemd daemon to apply changes
echo "Reloading systemd daemon..."
sudo systemctl daemon-reload

# Confirm uninstallation
echo "Uninstallation complete. Service and script have been removed."

