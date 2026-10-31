dotfiles - my dwm, dmenu and st setup
=====================================
My setup as I run it: 4K at 240Hz, 120 DPI.


Running
-------
    Super+Return                 terminal (st)
    Super+d                      dmenu
    Super+b                      hide / show bar
    Super+e                      file manager
    Super+w                      next wallpaper
    Super+F11                    webcam
    Super+q                      close window
    Super+arrows                 focus window
    Super+Shift+Left/Right       resize master area
    Super+Shift+Up/Down          resize window height
    Super+j                      swap with master
    Super+o / Super+Shift+o      more / fewer windows in master
    Super+Tab / Super+Shift+Tab  next / previous tag
    Super+1..9                   view tag
    Super+Shift+1..9             move window to tag
    Print                        screenshot to clipboard
    Super+Print                  screenshot to file and clipboard
    Super+Shift+r                restart dwm
    Super+Shift+x                quit dwm
    Super+Numpad Enter           play/pause
    Super+Numpad + / -           volume up / down
    Super+Numpad 7 / 9           previous / next track
    Shift+Up/Down, mouse wheel   scroll st
    Alt+Up/Down                  scroll st 10 lines
    Shift+PgUp/PgDn              scroll st one page
    Alt+Shift+Up/Down            st font bigger/smaller

dwm has no mouse bindings. Mouse is bloatware, if you cant do it on a kb
dont't do it.


Configuration
-------------
Wallpapers go in ~/Documents/Wallpapers, screenshots are saved to
~/Documents/Screen.

Patches (little overpatched, but goes smooth atleast):

    dwm    restartsig, preserveonrestart, vanitygaps, center, cfacts,
           fixborders, clientresizehints, status2d, bar-height-spacing,
           borderrule
    dmenu  lineheight
    st     scrollback, scrollback-mouse, scrollback-mouse-altscreen,
           clipboard
