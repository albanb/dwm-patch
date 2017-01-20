/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char *fonts[] = {
        "Terminus:style=Regular",
        "Stlarch:style=Regular"
};
static const char dmenufont[]       = "terminus:pixelsize=10";

enum { ColBorder, ColFG, ColBG, ColLast };              /* color */
#define NUMCOLORS 5
static const char colors[NUMCOLORS][ColLast][9] = {
	// border    foreground background
	{ "#FFFFFF", "#CECECE", "#050505" },	//normal
	{ "#507CFF", "#3A57D7", "#050505" },	//selected
	{ "#DC2F32", "#BE1919", "#050505" },	//urgent
	{ "#DDB62B", "#B27D12", "#050505" },	//error
	{ "#FFFFFF", "#050505", "#CECECE" },	//inverted
};
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",         NULL,         NULL,         0,            True,        -1 },
	{ "st-256color",  NULL, "Scratchpad", 1 << 8,       True         -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\uE002",       tile },    /* first entry is default */
	{ "\uE006",       NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,    	        KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termuxcmd[]  = { "st", "-e", "/home/alban/bin/tmux-session.sh", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *launcher[]  = { "/home/alban/bin/launcher.bash", NULL };
static const char *audio[]  = { "st", "-e", "ncmpcpp", NULL };
static const char *audiopi[]  = { "st", "-e", "ncmpcpp", "-c", "/home/alban/.ncmpcpp/config-pi", NULL };
static const char *web[]  = { "qutebrowser", "--backend", "webengine", NULL };
static const char *webalt[]  = { "firefox", NULL };
static const char *filemanager[]  = { "st", "-e", "ranger", NULL };
static const char *filemanagerpi[]  = { "/home/alban/bin/gpg-agent.sh", "ssh", "-X", "pi@192.168.1.11", "st", "-e", "ranger", NULL };
static const char *printscreen[]  = { "scrot", "/home/alban/print-screen.jpeg", NULL };
static const char *printwindow[]  = { "scrot", "-s", "/home/alban/print-screen.jpeg", NULL };
static const char *lockscreen[]  = { "slock", NULL };
static const char *video[]  = { "vlc", "--quiet", NULL };
static const char *soundup[]  = { "/home/alban/bin/sound.sh", "up", NULL };
static const char *sounddown[]  = { "/home/alban/bin/sound.sh", "down", NULL };
static const char *soundmute[]  = { "/home/alban/bin/sound.sh", "mute", NULL };
static const char *toggletouchpad[]  = { "/home/alban/bin/toggletouchpad.sh", NULL };
static const char *musicplay[]  = { "/home/alban/bin/music.sh", "play", NULL };
static const char *musicnext[]  = { "/home/alban/bin/music.sh", "next", NULL };
static const char *musicprevious[]  = { "/home/alban/bin/music.sh", "previous", NULL };
static const char *dmenubar[]  = { "/home/alban/bin/power.bash", NULL };
static const char *scratchpadcmd[] = { "st", "-t", "Scratchpad", "-g", "100x20+540+24", NULL };
static const char *passmancmd[] = { "passmgt.bash", "--type", NULL };
static const char *passmancmdlp[] = { "passmgt.bash", NULL };
static const char *clipsynccmd[] = { "xcmenu", "-spc", NULL };
static const char *clipboardcmd[] = { "xcmenuctrl", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_x,                     spawn,          {.v = launcher } },
	{ MODKEY|ShiftMask,             XK_x,                     spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_x,                     spawn,          {.v = dmenubar } },
	{ MODKEY,                       XK_c,                     spawn,          {.v = termuxcmd } },
	{ MODKEY|ShiftMask,             XK_c,                     spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_c,                     spawn,          {.v = scratchpadcmd } },
	{ MODKEY,                       XK_a,                     spawn,          {.v = audio } },
	{ MODKEY|ShiftMask,             XK_a,                     spawn,          {.v = audiopi } },
	{ MODKEY,                       XK_v,                     spawn,          {.v = video } },
	{ MODKEY,                       XK_w,                     spawn,          {.v = web } },
	{ MODKEY|ShiftMask,             XK_w,                     spawn,          {.v = webalt } },
	{ MODKEY,                       XK_r,                     spawn,          {.v = filemanager } },
	{ MODKEY|ShiftMask,             XK_r,                     spawn,          {.v = filemanagerpi } },
	{ MODKEY,                       XK_p,                     spawn,          {.v = passmancmd } },
	{ MODKEY|ShiftMask,             XK_p,                     spawn,          {.v = passmancmdlp } },
	{ MODKEY,                       XK_s,                     spawn,          {.v = lockscreen } },
	{ MODKEY|ShiftMask,             XK_s,                     spawn,          {.v = clipboardcmd } },
	{ MODKEY|ControlMask,           XK_s,                     spawn,          {.v = clipsynccmd } },
	{ MODKEY, 	              	XK_Print,                 spawn,          {.v = printwindow } },
	{ 0,                            XK_Print,                 spawn,          {.v = printscreen } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = soundup} },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = sounddown} },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = soundmute} },
	{ 0,                            XF86XK_AudioPlay,         spawn,          {.v = musicplay } },
	{ 0,                            XF86XK_AudioNext,         spawn,          {.v = musicnext } },
	{ 0,                            XF86XK_AudioPrev,         spawn,          {.v = musicprevious } },
	{ 0,                            XF86XK_TouchpadToggle,    spawn,          {.v = toggletouchpad } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                zoom,           {0} },
	{ MODKEY,                       XK_Tab,                   view,           {0} },
	{ MODKEY,                       XK_q,                     killclient,     {0} },
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                 setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_agrave,                view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,                tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon,             focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon,             tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Right,                 shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_Left,                  shiftview,      {.i = -1 } },
	TAGKEYS(                        XK_ampersand,             0)
	TAGKEYS(                        XK_eacute,                1)
	TAGKEYS(                        XK_quotedbl,              2)
	TAGKEYS(                        XK_apostrophe,            3)
	TAGKEYS(                        XK_parenleft,             4)
	TAGKEYS(                        XK_minus,                 5)
//	TAGKEYS(                        XK_egrave,                6)
//	TAGKEYS(                        XK_underscore,            7)
//	TAGKEYS(                        XK_ccedilla,              8)
	{ MODKEY|ShiftMask,             XK_q,                     quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = dmenubar } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

