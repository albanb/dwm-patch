/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:pixelsize=10",
                                        "Siji:pixelsize=10"};
static const char dmenufont[]       = "xos4 Terminus:pixelsize=10";
static const char col_gray1[]       = "#CECECE";
static const char col_dark[]       = "#050505";
static const char col_blue1[]       = "#507CFF";
static const char col_blue2[]       = "#3A57D7";
static const char col_red1[]         = "#DC2F32";
static const char col_red2[]         = "#BE1919";
static const char col_yellow1[]      = "#DDB62B";
static const char col_yellow2[]      = "#B27D12";
static const char col_white[]       = "#ffffff";
static const char col_green1[]       = "#009900";
static const char col_green2[]       = "#00FF00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray1, col_dark, col_white },
	[SchemeSel]  = { col_blue2, col_dark,  col_blue1 },
    [SchemeWarn] =   { col_yellow2, col_dark, col_yellow1 },
    [SchemeUrgent]=  { col_red2, col_dark,    col_red1 },
    [SchemeFine]=  { col_green1, col_dark,    col_green2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "st-256color",  NULL, "Scratchpad", 1 << 8,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\uE002",      tile },    /* first entry is default */
	{ "\uE006",      NULL },    /* no layout function means floating behavior */
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_dark, "-nf", col_gray1, "-sb", col_dark, "-sf", col_blue2, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *termuxcmd[]  = { "st", "-e", "/home/alban/.bin/tmux-session.sh", NULL };
static const char *launcher[]  = { "/home/alban/.bin/launcher.bash", NULL };
static const char *audio[]  = { "st", "-e", "ncmpcpp", NULL };
static const char *audiopi[]  = { "st", "-e", "ncmpcpp", "-c", "/home/alban/.ncmpcpp/config-pi", NULL };
static const char *web[]  = { "firefox", NULL };
static const char *webalt[]  = { "chromium", NULL };
static const char *filemanager[]  = { "st", "-e", "ranger", NULL };
static const char *filemanagerpi[]  = { "/home/alban/.bin/gpg-agent.sh", "ssh", "-X", "pi@192.168.1.11", "st", "-e", "ranger", NULL };
static const char *printscreen[]  = { "scrot", "/home/alban/print-screen.jpeg", NULL };
static const char *printwindow[]  = { "scrot", "-s", "/home/alban/print-screen.jpeg", NULL };
static const char *lockscreen[]  = { "slock", NULL };
static const char *video[]  = { "vlc", "--quiet", NULL };
static const char *soundup[]  = { "/home/alban/.bin/sound.sh", "up", NULL };
static const char *sounddown[]  = { "/home/alban/.bin/sound.sh", "down", NULL };
static const char *soundmute[]  = { "/home/alban/.bin/sound.sh", "mute", NULL };
static const char *toggletouchpad[]  = { "/home/alban/.bin/toggletouchpad.sh", NULL };
static const char *musicplay[]  = { "/home/alban/.bin/music.sh", "play", NULL };
static const char *musicnext[]  = { "/home/alban/.bin/music.sh", "next", NULL };
static const char *musicprevious[]  = { "/home/alban/.bin/music.sh", "previous", NULL };
static const char *dmenubar[]  = { "/home/alban/.bin/power.bash", NULL };
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
	{ MODKEY, 	                	XK_Print,                 spawn,          {.v = printwindow } },
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
	{ MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

