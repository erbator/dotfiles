# dotfiles

dwm, dmenu, a status bar and the few programs they call.

```
dwm/        dwm 6.8 source with config.h
dmenu/      dmenu source with config.h
bar/        status bar (barstatus) and media control (mpris)
scripts/    screenshots, wallpaper cycling, webcam
alacritty/  terminal config
xinitrc     session startup
Xresources  nsxiv colors
```

## Install (Arch)

1. Install the programs:

```sh
sudo pacman -S --needed git base-devel libx11 libxft libxinerama \
	xorg-server xorg-xinit xorg-xprop xorg-xrdb libpulse \
	alacritty picom xwallpaper maim xclip nsxiv thunar mpv \
	ttf-dejavu ttf-gohu-nerd
```

2. Download this repo:

```sh
git clone https://github.com/erbator/dotfiles
cd dotfiles
```

3. Build and install dwm and dmenu:

```sh
sudo make -C dwm install
sudo make -C dmenu install
```

4. Copy the configs to where the programs read them:

```sh
mkdir -p ~/.config/alacritty ~/.local/bin \
	~/Documents/Screen ~/Documents/Wallpapers
cp alacritty/alacritty.toml ~/.config/alacritty/
cp bar/* scripts/* ~/.local/bin/
cp xinitrc ~/.xinitrc
cp Xresources ~/.Xresources
```

5. Log in on a TTY and start dwm:

```sh
startx
```

Put wallpapers in `~/Documents/Wallpapers`.

## Keys

| Key | Action |
|---|---|
| Super+Return | alacritty |
| Super+d | dmenu |
| Super+e | thunar |
| Super+w | next wallpaper |
| Super+F11 | webcam |
| Super+q | close window |
| Super+arrows | focus window |
| Super+Shift+Left/Right | resize master area |
| Super+Shift+Up/Down | resize window height |
| Super+j | swap with master |
| Super+o / Super+Shift+o | more / fewer windows in master |
| Super+1..9 | view tag |
| Super+Shift+1..9 | move window to tag |
| Print | screenshot region to clipboard |
| Super+Print | screenshot region to ~/Documents/Screen and clipboard |
| Super+Shift+r | restart dwm |
| Super+Shift+x | quit dwm |

## dwm patches

restartsig, preserveonrestart, vanitygaps, center, cfacts, fixborders, clientresizehints,
status2d, bar-height-spacing, borderrule; dmenu: lineheight.
Also: window title in the bar, CJK size and baseline in the bar, layout reset when a
window opens, no mouse bindings.
