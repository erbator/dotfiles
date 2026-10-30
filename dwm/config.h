/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    = 16;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 16;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int barpad             = 8;         /* extra bar height in pixels */
static const char *fonts[]          = { "DejaVu Sans Mono:size=10" };
static const char dmenufont[]       = "DejaVu Sans Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_gray5[]       = "#777777";
static const char col_gray6[]       = "#999999";
static const char col_cyan[]        = "#7fbbb3"; /* everforest blue, as in alacritty */
static const char col_dark[]        = "#272e33"; /* everforest bg, text on blue */
static const char col_blue[]        = "#7fbbb3";
static const char *colors[][3]      = {
	/*                   fg         bg         border   */
	[SchemeNorm]     = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]      = { col_dark,  col_cyan,  col_cyan  },
	[SchemeOcc]      = { col_gray4, col_gray1, col_gray2 }, /* tags with windows */
	[SchemeEmpty]    = { col_gray5, col_gray1, col_gray2 }, /* empty tags */
	/* status text colours, selected by the bytes \x01, \x02, ... in the status */
	[SchemeStatus]   = { col_gray6, col_gray1, col_gray2 }, /* \x01 brackets and labels */
	[SchemeStatus+1] = { col_gray4, col_gray1, col_gray2 }, /* \x02 values */
	[SchemeStatus+2] = { col_blue,  col_gray1, col_gray2 }, /* \x03 now playing */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance                  title  tags mask  iscentered  isfloating  noborder  monitor */
	{ "Gimp",                 NULL,                     NULL,  0,         0,          1,          0,        -1 },
	{ "com.mojang.minecraft", NULL,                     NULL,  0,         0,          0,          1,        -1 },
	{ NULL,                   "pavucontrol",            NULL,  0,         1,          1,          0,        -1 },
	{ NULL,                   "xdg-desktop-portal-gtk", NULL,  0,         1,          1,          0,        -1 },
	{ NULL,                   "satty",                  NULL,  0,         1,          1,          0,        -1 },
	{ NULL,                   "nsxiv",                  NULL,  0,         1,          1,          0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 60;   /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* volume commands; afterwards poke barstatus so the bar updates right away */
#define BARREFRESH "; kill -USR1 $(cat \"$XDG_RUNTIME_DIR/barstatus.pid\")"
#define VOLUP      SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%" BARREFRESH)
#define VOLDOWN    SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%" BARREFRESH)
#define VOLMUTE    SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle" BARREFRESH)

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_dark, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *filecmd[]  = { "thunar", NULL };

/* view the next/previous tag that has windows on it */
static void
shiftview(const Arg *arg)
{
	Client *c;
	unsigned int occ = 0, cur = selmon->tagset[selmon->seltags];
	int i, n = LENGTH(tags);
	Arg a;

	for (c = selmon->clients; c; c = c->next)
		occ |= c->tags;
	for (i = 1; i < n; i++) {
		a.ui = (arg->i > 0 ? cur << i | cur >> (n - i) : cur >> i | cur << (n - i)) & TAGMASK;
		if (a.ui & occ) {
			view(&a);
			return;
		}
	}
}

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$HOME/.local/bin/wallcycle") },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {.i = 1} }, /* restart */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_j,      zoom,           {0} },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.02} },
	{ MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_Up,     setcfact,       {.f = -0.10} },
	{ MODKEY|ShiftMask,             XK_Down,   setcfact,       {.f = +0.10} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* multimedia keys */
	{ 0, XF86XK_AudioRaiseVolume,  spawn, VOLUP },
	{ 0, XF86XK_AudioLowerVolume,  spawn, VOLDOWN },
	{ 0, XF86XK_AudioMute,         spawn, VOLMUTE },
	{ 0, XF86XK_AudioMicMute,      spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_AudioNext,         spawn, SHCMD("$HOME/.local/bin/mpris next") },
	{ 0, XF86XK_AudioPause,        spawn, SHCMD("$HOME/.local/bin/mpris play-pause") },
	{ 0, XF86XK_AudioPlay,         spawn, SHCMD("$HOME/.local/bin/mpris play-pause") },
	{ 0, XF86XK_AudioPrev,         spawn, SHCMD("$HOME/.local/bin/mpris previous") },
	{ 0,      XK_Print,            spawn, SHCMD("$HOME/.local/bin/qscreen") },     /* region to clipboard */
	{ MODKEY, XK_Print,            spawn, SHCMD("$HOME/.local/bin/screenshot") },  /* region into satty */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkStatusVol, ClkStatusMusic, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusVol,         0,              Button4,        spawn,          VOLUP },
	{ ClkStatusVol,         0,              Button5,        spawn,          VOLDOWN },
	{ ClkStatusVol,         0,              Button2,        spawn,          VOLMUTE },
	{ ClkStatusMusic,       0,              Button1,        spawn,          SHCMD("$HOME/.local/bin/mpris previous" BARREFRESH) },
	{ ClkStatusMusic,       0,              Button2,        spawn,          SHCMD("$HOME/.local/bin/mpris play-pause" BARREFRESH) },
	{ ClkStatusMusic,       0,              Button3,        spawn,          SHCMD("$HOME/.local/bin/mpris next" BARREFRESH) },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button4,        shiftview,      {.i = -1 } },
	{ ClkClientWin,         MODKEY,         Button5,        shiftview,      {.i = +1 } },
	{ ClkRootWin,           MODKEY,         Button4,        shiftview,      {.i = -1 } },
	{ ClkRootWin,           MODKEY,         Button5,        shiftview,      {.i = +1 } },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
