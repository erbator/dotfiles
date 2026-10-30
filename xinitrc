cd ~

xrdb -merge ~/.Xresources
$HOME/.local/bin/wallcycle restore
# let systemd/dbus services (xdg-desktop-portal-gtk) open windows on this display
dbus-update-activation-environment --systemd DISPLAY XAUTHORITY
~/.local/bin/barstatus --xroot &
picom --config /dev/null --backend glx --vsync --unredir-if-possible &
exec dwm
