# YaTM-ish (Yet Another Tiling Manager-ish)
A very rough imitation of "Snap-Layout" feature (-of Windows) in Linux (as a tiling manager)

### Note: Cloning the repo and and running intsall.sh will trigger a bash script which will always run in background since system start-up. To uninstall just run uninstall.sh

https://github.com/user-attachments/assets/ef355f34-1551-4d2a-af5a-517de2c6469f



To Setup and run-
```bash
git clone https://github.com/Karvy-Singh/YATM-ish.git
cd YATM-ish
```
```bash
chmod +x install.sh
./install.sh
chmod +x run.sh
#to be done only for the initial setup
```
```bash
./run.sh        # use it everytime to trigger the TM
```
# Requirements-
install the following libraries:
* SDL2
* SDL2_image
* SDL2_ttf (ensure you have fonts already present)
* X11
