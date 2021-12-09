/* see LICENSE for copyright and license */

#ifndef CONFIG_H
#define CONFIG_H

/** modifiers **/
#define ALT             Mod1Mask    /* ALT key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */
#define SUPER           Mod4Mask    /* Super/Windows key */

/** generic settings **/
#define ATTACH_ASIDE    True      /* False means new window is master */
#define BORDER_WIDTH    5         /* window border width */
#define CLICK_TO_FOCUS  True      /* focus an unfocused window when clicked  */
#define DEFAULT_DESKTOP 0         /* the desktop to focus initially */
#define DEFAULT_MODE    MONOCLE   /* initial layout/mode: TILE MONOCLE BSTACK GRID FLOAT */
#define DESKTOPS        5         /* number of desktops - edit DESKTOPCHANGE keys to suit */
#define FOCUS           "#34a1eb" /* focused window border color    */
#define FOCUS_BUTTON    Button3   /* mouse button to be used along with CLICK_TO_FOCUS */
#define FOLLOW_MOUSE    False     /* focus the window the mouse just entered */
#define FOLLOW_WINDOW   False     /* follow the window when moved to a different desktop */
#define MASTER_SIZE     0.50
#define MINWSZ          50        /* minimum window size in pixels  */
#define PANEL_HEIGHT    0         /* 0 for no space for panel, thus no panel */
#define SHOW_PANEL      False     /* show panel by default on exec */
#define TOP_PANEL       True      /* False means panel is on bottom */
#define UNFOCUS         "#000000" /* unfocused window border color  */
#define USELESSGAP      8         /* the size of the useless gap in pixels */

/**
 * open applications to specified desktop with specified mode.
 * if desktop is negative, then current is assumed
 */
static const AppRule rules[] = { \
    /*  class     desktop  follow  float */
    { "MPlayer",     3,    True,   False },
    { "ttyclock",    -1,   True,   True  },
    /* { "Gimp",        0,    False,  True  }, */
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/**
 * custom commands
 * must always end with ', NULL };'
 */
static const char *termcmd[] = { "alacritty",     NULL };
static const char *menucmd[] = { "dmenu_run", NULL };

#define DESKTOPCHANGE(K,N) \
    {  SUPER,             K,              change_desktop, {.i = N}}, \
    {  SUPER|ShiftMask,   K,              client_to_desktop, {.i = N}},

/**
 * keyboard shortcuts
 */
static Key keys[] = {
    /* modifier          key            function           argument */
    {  SUPER,             XK_BackSpace,  focusurgent,       {NULL}},
    {  SUPER,             XK_Return,     spawn,             {.com = termcmd}},
    {  SUPER,             XK_Tab,        last_desktop,      {NULL}},
    {  SUPER,             XK_b,          spawn,             SHCMD("google-chrome-stable")},
    {  SUPER,             XK_c,          spawn,             SHCMD("alacritty -t 'Clock' --class 'ttyclock' -e /usr/local/bin/clock")},
    {  SUPER,             XK_f,          switch_mode,       {.i = FLOAT}},
    {  SUPER,             XK_g,          switch_mode,       {.i = GRID}},
    {  SUPER,             XK_h,          rotate_filled,     {.i = -1}},
    {  SUPER,             XK_i,          rotate,            {.i = +1}},
    {  SUPER,             XK_j,          next_win,          {NULL}},
    {  SUPER,             XK_k,          prev_win,          {NULL}},
    {  SUPER,             XK_l,          rotate_filled,     {.i = +1}},
    {  SUPER,             XK_m,          switch_mode,       {.i = MONOCLE}},
    {  SUPER,             XK_n,          spawn,             SHCMD("alacritty -e nvim")},
    {  SUPER,             XK_o,          spawn,             SHCMD("alacritty -e htop")},
    {  SUPER,             XK_r,          spawn,             {.com = menucmd}},
    {  SUPER,             XK_t,          switch_mode,       {.i = TILE}},
    {  SUPER,             XK_u,          rotate,            {.i = -1}},
    {  SUPER,             XK_v,          switch_mode,       {.i = BSTACK}},
    {  SUPER,             XK_x,          killclient,        {NULL}},
    {  SUPER,             XK_z,          spawn,             SHCMD("alacritty -e vifm +only")},

    {  SUPER|CONTROL,     XK_h,          moveresize,        {.v = (int []){ -25,   0,   0,   0 }}}, /* move left  */
    {  SUPER|CONTROL,     XK_j,          moveresize,        {.v = (int []){   0,  25,   0,   0 }}}, /* move down  */
    {  SUPER|CONTROL,     XK_k,          moveresize,        {.v = (int []){   0, -25,   0,   0 }}}, /* move up    */
    {  SUPER|CONTROL,     XK_l,          moveresize,        {.v = (int []){  25,   0,   0,   0 }}}, /* move right */

    {  SUPER|CONTROL|ALT, XK_h,          moveresize,        {.v = (int []){   0,   0, -25,   0 }}}, /* width shrink  */
    {  SUPER|CONTROL|ALT, XK_j,          moveresize,        {.v = (int []){   0,   0,   0,  25 }}}, /* height grow   */
    {  SUPER|CONTROL|ALT, XK_k,          moveresize,        {.v = (int []){   0,   0,   0, -25 }}}, /* height shrink */
    {  SUPER|CONTROL|ALT, XK_l,          moveresize,        {.v = (int []){   0,   0,  25,   0 }}}, /* width grow    */
    {  SUPER|CONTROL|ALT, XK_o,          resize_stack,      {.i = -10}}, /* shrink   size in px */
    {  SUPER|CONTROL|ALT, XK_p,          resize_stack,      {.i = +10}}, /* grow     size in px */
    {  SUPER|CONTROL|ALT, XK_u,          resize_master,     {.i = +10}}, /* increase size in px */
    {  SUPER|CONTROL|ALT, XK_y,          resize_master,     {.i = -10}}, /* decrease size in px */

    {  SUPER|SHIFT,       XK_h,          rotate_client,     {.i = -1}},
    {  SUPER|SHIFT,       XK_j,          move_down,         {NULL}},
    {  SUPER|SHIFT,       XK_k,          move_up,           {NULL}},
    {  SUPER|SHIFT,       XK_l,          rotate_client,     {.i = +1}},
    {  SUPER|SHIFT,       XK_m,          swap_master,       {NULL}},
    {  SUPER|SHIFT,       XK_q,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  SUPER|SHIFT,       XK_r,          quit,              {.i = 0}}, /* quit with exit value 0 */

       DESKTOPCHANGE(     XK_1,                             0)
       DESKTOPCHANGE(     XK_2,                             1)
       DESKTOPCHANGE(     XK_3,                             2)
       DESKTOPCHANGE(     XK_4,                             3)
       DESKTOPCHANGE(     XK_5,                             4)
};

/**
 * mouse shortcuts
 */
static Button buttons[] = {
    {  SUPER,    Button1,     mousemotion,   {.i = MOVE}},
    {  SUPER,    Button3,     mousemotion,   {.i = RESIZE}},
    {  SUPER,    Button3,     spawn,         {.com = menucmd}},
};
#endif

/* vim: set expandtab ts=4 sts=4 sw=4 : */
