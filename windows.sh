#!/bin/bash

# File to log focus events
log_file="./focus_events.txt"
> "$log_file" # Clear the log file

# Maximum number of lines to keep in the log file
max_lines=20

# Track monitored windows
monitored_windows="./monitored_windows.txt"
> "$monitored_windows"

# Function to start `xev` for a new window
start_xev_for_window() {
  local window_id=$1
  echo "Starting xev for window ID: $window_id"
  echo "$window_id" >> "$monitored_windows"

  # Start xev and log FocusIn events with window name
  {
    window_name=$(xdotool getwindowname "$window_id")
    LC_ALL=C XMODIFIERS=@im=none xev -id "$window_id" -event focus | grep --line-buffered "FocusIn" | while read -r event; do
      echo "Window Name: $window_name, Window ID: $window_id, Event: $event" >> "$log_file"

      # Keep log size fixed by deleting old entries
       current_lines=$(wc -l < "$log_file")
       if [[ $current_lines -gt $max_lines ]]; then
        # Keep only the last $max_lines lines
        tail -n "$max_lines" "$log_file" > "${log_file}.tmp"
        mv "${log_file}.tmp" "$log_file"
       fi
        sleep 1
        done
  } &
}

# Function to monitor new windows
monitor_windows() {
  while true; do
    current_windows=$(xdotool search --onlyvisible .)

    for window_id in $current_windows; do
      if ! grep -q "$window_id" "$monitored_windows"; then
        start_xev_for_window "$window_id"
      fi
    done

    sleep 5 # Check for new windows every 5 seconds
  done
}

# Start monitoring windows
monitor_windows &

echo "Focus tracking started. Logs are being saved to $log_file."
echo "Press Ctrl+C to stop."

# Wait for user to terminate the script
wait

