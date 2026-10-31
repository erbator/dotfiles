cd ~

# 3840x2160 at 240Hz on the first connected output
if command -v xrandr >/dev/null; then
	out=$(xrandr --query | awk '/ connected/ { print $1; exit }')
	[ -n "$out" ] && xrandr --output "$out" --mode 3840x2160 --rate 240
fi
xrdb -merge ~/.Xresources
$HOME/.local/bin/wallcycle restore
# let systemd/dbus services (xdg-desktop-portal-gtk) open windows on this display
dbus-update-activation-environment --systemd DISPLAY XAUTHORITY
# Qt: fonts from gtk-3.0/settings.ini, style from Kvantum (MateriaDark)
export QT_QPA_PLATFORMTHEME=gtk3
export QT_STYLE_OVERRIDE=kvantum
~/.local/bin/barstatus --xroot &
exec dwm
