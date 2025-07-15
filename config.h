/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "MartianMono Nerd Font:size=11" };
static const char dmenufont[]       = "MartianMono Nerd Font:size=11";
static const char col_gray1[]       = "#222222"; /* background color */
static const char col_gray2[]       = "#2b2f33"; /* inactive window border color */
static const char col_gray3[]       = "#d0d0d0"; /* font color */
static const char col_gray4[]       = "#f0f0f0"; /* current tag and current window font color */
static const char col_cyan[]        = "#bd93f9"; /* top bar second color */
static const char act_win_bord[]    = "#bd93f9"; /* active window border color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan, act_win_bord  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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

/* high priority apps for dmenu */
static const char dmenuhpapps[] = "librewolf,brave-bin,torbrowser-launcher,signal-desktop,logseq-desktop-bin";

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-hp", dmenuhpapps, NULL };
static const char *termcmd[]       = { "alacritty", NULL }; /* Default terminal emulator for dwm */
static const char *rangercmd[]     = { "alacritty", "-e", "ranger", NULL};
static const char *yazicmd[]       = { "alacritty", "-e", "yazi", NULL};
static const char *brupcmd[]       = { "xbacklight", "-inc", "5", NULL};
static const char *brdowncmd[]     = { "xbacklight", "-dec", "5", NULL};
static const char *kbdbrupcmd[]    = { "kbdbacklight", "-inc", "5", NULL};
static const char *kbdbrdowncmd[]  = { "kbdbacklight", "-dec", "5", NULL};
static const char *volupcmd[]      = { "amixer", "set", "Master", "2%+", NULL};
static const char *voldowncmd[]    = { "amixer", "set", "Master", "2%-", NULL};
static const char *volmutecmd[]    = { "amixer", "set", "Master", "0%", NULL};
static const char *sscmd[]         = { "scrot", "-fs", NULL };

#include "shiftview.c"

static Key keys[] = {
    /* modifier             key                         function        argument */
	{ 0,                    XF86XK_MonBrightnessUp,     spawn,          {.v = brupcmd } },
	{ 0,                    XF86XK_MonBrightnessDown,   spawn,          {.v = brdowncmd } },
        { 0,                    XF86XK_KbdBrightnessUp,     spawn,          {.v = kbdbrupcmd } },
	{ 0,                    XF86XK_KbdBrightnessDown,   spawn,          {.v = kbdbrdowncmd } },
	{ 0,                    XF86XK_AudioRaiseVolume,    spawn,          {.v = volupcmd } },
	{ 0,                    XF86XK_AudioLowerVolume,    spawn,          {.v = voldowncmd } },
	{ 0,                    XF86XK_AudioMute,           spawn,          {.v = volmutecmd } },
	{ MODKEY,               XK_p,                       spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY,               XK_r,                       spawn,          {.v = rangercmd } },
	{ MODKEY,               XK_e,                       spawn,          {.v = yazicmd } },
	{ MODKEY|ShiftMask,     XK_s,                       spawn,          {.v = sscmd } },
	{ MODKEY,               XK_b,                       togglebar,      {0} },
	{ MODKEY,               XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY,               XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,               XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,               XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_Return,                  zoom,           {0} },
	{ MODKEY,               XK_Tab,                     view,           {0} },
	{ MODKEY,               XK_c,                       killclient,     {0} },
	{ MODKEY,               XK_t,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_f,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_m,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               XK_space,                   setlayout,      {0} },
	{ MODKEY|ShiftMask,     XK_space,                   togglefloating, {0} },
	{ MODKEY,               XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,               XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,                  tagmon,         {.i = +1 } },
	{ MODKEY,               XK_minus,                   setgaps,        {.i = -1 } },
	{ MODKEY,               XK_equal,                   setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_equal,                   setgaps,        {.i = 0  } },
	{ MODKEY,               XK_Left,                    shiftview,      {.i = -1 } },
	{ MODKEY,               XK_Right,                   shiftview,      {.i = +1 } },
	TAGKEYS(                XK_1,                                        0)
	TAGKEYS(                XK_2,                                        1)
	TAGKEYS(                XK_3,                                        2)
	TAGKEYS(                XK_4,                                        3)
	TAGKEYS(                XK_5,                                        4)
	TAGKEYS(                XK_6,                                        5)
	TAGKEYS(                XK_7,                                        6)
	TAGKEYS(                XK_8,                                        7)
	{ MODKEY|ShiftMask,     XK_q,                       quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

