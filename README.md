# dotfiles

My dwm setup as I run it: 4K at 240Hz, 120 DPI.

## Install

On Arch:

```sh
sudo pacman -S --needed git base-devel libx11 libxft libxinerama \
	xorg-server xorg-xinit xorg-xprop xorg-xrdb libpulse \
	xwallpaper maim xclip nsxiv thunar mpv \
	ttf-dejavu ttf-martian-mono-nerd noto-fonts-cjk xorg-xrandr \
	chromium kvantum papirus-icon-theme

git clone https://github.com/erbator/dotfiles
cd dotfiles
sudo make -C dwm install
sudo make -C dmenu install
sudo make -C st install

mkdir -p ~/.local/bin ~/Documents/Screen ~/Documents/Wallpapers
cp -r fontconfig gtk-3.0 xdg-desktop-portal mimeapps.list chromium-flags.conf ~/.config/
cp bar/* scripts/* ~/.local/bin/
cp xinitrc ~/.xinitrc
cp Xresources ~/.Xresources
```

run `startx`.

Wallpapers go in `~/Documents/Wallpapers`, screenshots are saved to `~/Documents/Screen`.

## Keys

| Key | Action |
|---|---|
| Super+Return | terminal (st) |
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
| Super+Shift+Space | toggle floating |
| Super+1..9 | view tag |
| Super+Shift+1..9 | move window to tag |
| Print | screenshot to clipboard |
| Super+Print | screenshot to file and clipboard |
| Super+Shift+r | restart dwm |
| Super+Shift+x | quit dwm |
| Shift+Up/Down, mouse wheel | scroll st |
| Alt+Up/Down | scroll st 10 lines |
| Alt+Shift+Up/Down | st font bigger/smaller |

dwm has no mouse bindings. Mouse is bloatware, if you cant do it on a kb dont't do it.

## Patches (Little overpatched, but goes smooth atleast.)

dwm: restartsig, preserveonrestart, vanitygaps, center, cfacts, fixborders,
clientresizehints, status2d, bar-height-spacing, borderrule.
dmenu: lineheight.
st: scrollback, scrollback-mouse, scrollback-mouse-altscreen, clipboard.
