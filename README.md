# dotfiles

My dwm setup: dwm, dmenu, a status bar and the scripts they use.

## Install

On Arch:

```sh
sudo pacman -S --needed git base-devel libx11 libxft libxinerama \
	xorg-server xorg-xinit xorg-xprop xorg-xrdb libpulse \
	alacritty xwallpaper maim xclip nsxiv thunar mpv \
	ttf-dejavu ttf-gohu-nerd

git clone https://github.com/erbator/dotfiles
cd dotfiles
sudo make -C dwm install
sudo make -C dmenu install

mkdir -p ~/.config/alacritty ~/.local/bin ~/Documents/Screen ~/Documents/Wallpapers
cp alacritty/alacritty.toml ~/.config/alacritty/
cp bar/* scripts/* ~/.local/bin/
cp xinitrc ~/.xinitrc
cp Xresources ~/.Xresources
```

run `startx`.

Wallpapers go in `~/Documents/Wallpapers`, screenshots are saved to `~/Documents/Screen`.

## Keys

| Key | Action |
|---|---|
| Super+Return | terminal |
| Super+d | dmenu |
| Super+e | file manager |
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
| Print | screenshot to clipboard |
| Super+Print | screenshot to file and clipboard |
| Super+Shift+r | restart dwm |
| Super+Shift+x | quit dwm |

There are no mouse bindings. Mouse is bloatware, if you cant do it on a kb dont't do it.

## Patches (Little overpatched, but goes smooth atleast.)

dwm: restartsig, preserveonrestart, vanitygaps, center, cfacts, fixborders,
clientresizehints, status2d, bar-height-spacing, borderrule.
dmenu: lineheight.
