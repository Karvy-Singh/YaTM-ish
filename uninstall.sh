
#!/bin/bash

# Define variables
SCRIPT_NAME="windows.sh"
SERVICE_NAME="windows.service"
INSTALL_DIR="/usr/local/bin/$SCRIPT_NAME"
SERVICE_DIR="/etc/systemd/system/$SERVICE_NAME"

echo "Uninstalling $SCRIPT_NAME..."

# Stop the service
echo "Stopping the service..."
sudo systemctl stop $SERVICE_NAME

# Disable the service
echo "Disabling the service..."
sudo systemctl disable $SERVICE_NAME

# Remove the systemd service file
if [ -f "$SERVICE_DIR" ]; then
    echo "Removing systemd service file..."
    sudo rm -f "$SERVICE_DIR"
else
    echo "Service file not found: $SERVICE_DIR"
fi

# Reload the systemd daemon
echo "Reloading systemd daemon..."
sudo systemctl daemon-reload

# Remove the script from /usr/local/bin
if [ -f "$INSTALL_DIR" ]; then
    echo "Removing the script from $INSTALL_DIR..."
    sudo rm -f "$INSTALL_DIR"
else
    echo "Script file not found: $INSTALL_DIR"
fi

echo "Uninstallation complete. $SCRIPT_NAME and its service have been removed."

