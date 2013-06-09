/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "-*-stlarch-medium-r-*-*-10-*-*-*-*-*-*-*" "," "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
#define NUMCOLORS 5
static const char colors[NUMCOLORS][ColLast][9] = {
	// border    foreground background
	{ "#AEAEAE", "#E6E6E6", "#090C19" },	//normal
	{ "#4D79FF", "#4957F3", "#090C19" },	//selected
	{ "#DC2C2C", "#B32323", "#090C19" },	//urgent
	{ "#E6CB29", "#FF9F3E", "#090C19" },	//error
	{ "#5DCE33", "#1AAA13", "#090C19" },	//back to normal
};
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",         NULL,         NULL,         0,            True,        -1 },
	{ "st-256color",  "Scratchpad", "Scratchpad", 1 << 8,       True         -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

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

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termuxcmd[]  = { "st", "-e", "/home/alban/bin/tmux-session.sh", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *launcher[]  = { "interrobang", NULL };
static const char *audio[]  = { "st", "-e", "mocp", "-M", "/home/alban/.config/moc", NULL };
static const char *web[]  = { "dwb", NULL };
static const char *webalt[]  = { "firefox", NULL };
static const char *filemanager[]  = { "st", "-e", "ranger", NULL };
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
static const char *dmenubar[]  = { "/home/alban/bin/menu-dwm.bash", NULL };
static const char *scratchpadcmd[] = { "st", "-t", "Scratchpad", "-g", "540x150+540+24", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_x,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_c,                     spawn,          {.v = termuxcmd } },
	{ MODKEY|ShiftMask,             XK_c,                     spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_x,                     spawn,          {.v = launcher } },
	{ MODKEY,                       XK_a,                     spawn,          {.v = audio } },
	{ MODKEY,                       XK_w,                     spawn,          {.v = web } },
	{ MODKEY|ShiftMask,             XK_w,                     spawn,          {.v = webalt } },
	{ MODKEY,                       XK_n,                     spawn,          {.v = filemanager } },
	{ 0,                            XK_Print,                 spawn,          {.v = printscreen } },
	{ MODKEY, 	                XK_Print,                 spawn,          {.v = printwindow } },
	{ MODKEY,                       XK_s,                     spawn,          {.v = lockscreen } },
	{ MODKEY,                       XK_v,                     spawn,          {.v = video } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = soundup} },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = sounddown} },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = soundmute} },
	{ 0,                            XF86XK_TouchpadToggle,    spawn,          {.v = toggletouchpad } },
	{ 0,                            XF86XK_AudioPlay,         spawn,          {.v = musicplay } },
	{ 0,                            XF86XK_AudioNext,         spawn,          {.v = musicnext } },
	{ 0,                            XF86XK_AudioPrev,         spawn,          {.v = musicprevious } },
	{ MODKEY,                       XK_o,                     spawn,          {.v = dmenubar } },
	{ MODKEY,                       XK_p,                     spawn,          {.v = scratchpadcmd } },
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
	TAGKEYS(                        XK_egrave,                6)
	TAGKEYS(                        XK_underscore,            7)
	TAGKEYS(                        XK_ccedilla,              8)
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

