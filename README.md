# dotfiles

dwm, dmenu, a status bar and the few programs they call.

```
dwm/        dwm 6.8 source with config.h
dmenu/      dmenu source with config.h
bar/        status bar (barstatus) and media control (mpris)
scripts/    dmenu app list, screenshots, wallpaper cycling
alacritty/  terminal config
satty/      screenshot editor config
xinitrc     session startup
Xresources  nsxiv colors
```

## Install (Arch)

```sh
sudo pacman -S --needed base-devel libx11 libxft libxinerama \
	xorg-server xorg-xinit xorg-xprop xorg-xrdb libpulse python \
	alacritty picom xwallpaper maim xclip satty nsxiv thunar \
	ttf-dejavu ttf-gohu-nerd

sudo make -C dwm install
sudo make -C dmenu install

mkdir -p ~/.config/alacritty ~/.config/satty ~/.local/bin \
	~/Documents/Screen ~/Documents/Wallpapers
cp alacritty/alacritty.toml ~/.config/alacritty/
cp satty/config.toml ~/.config/satty/
cp bar/* scripts/* ~/.local/bin/
cp xinitrc ~/.xinitrc
cp Xresources ~/.Xresources

startx
```

Put wallpapers in `~/Documents/Wallpapers`. Edit the app list in `~/.local/bin/dmenu_apps`.

## Keys

| Key | Action |
|---|---|
| Super+Return | alacritty |
| Super+d | dmenu app list |
| Super+e | thunar |
| Super+w | next wallpaper |
| Super+q | close window |
| Super+arrows | focus window |
| Super+Shift+Left/Right | resize master area |
| Super+Shift+Up/Down | resize window height |
| Super+j | swap with master |
| Super+1..9 | view tag |
| Super+Shift+1..9 | move window to tag |
| Print | screenshot region to clipboard |
| Super+Print | screenshot region into satty |
| Super+Shift+r | restart dwm |
| Super+Shift+x | quit dwm |

Scroll or middle-click the volume in the bar to change or mute it; click the song to go back, pause or skip.

## dwm patches

restartsig, preserveonrestart, vanitygaps, center, cfacts, fixborders.
Also: window title in the bar, coloured and clickable status, per-rule `noborder`,
CJK size and baseline in the bar, layout reset when a window opens.
