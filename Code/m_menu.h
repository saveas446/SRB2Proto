//   Menu widget stuff, episode selection and such.


#ifndef __M_MENU__
#define __M_MENU__

#include "d_event.h"
#include "command.h"


//
// MENUS
//
// Called by main loop,
// saves config file and calls I_Quit when user exits.
// Even when the menu is not displayed,
// this can resize the view and change game parameters.
// Does all the real work of the menu interaction.
boolean M_Responder (event_t *ev);


// Called by main loop,
// only used for menu (skull cursor) animation.
void M_Ticker (void);

// Called by main loop,
// draws the menus directly into the screen buffer.
void M_Drawer (void);

// Called by D_SRB2Main,
// loads the config file.
void M_Init (void);

// Called by intro code to force menu up upon a keypress,
// does nothing if menu is already up.
void M_StartControlPanel (void);


// Draws a box with a texture inside as background for messages
void M_DrawTextBox (int x, int y, int width, int lines);
// show or hide the setup for player 2 (called at splitscreen change)
void M_SwitchSplitscreen(void);

// the function to show a message box typing with the string inside
// string must be static (not in the stack)
// routine is a function taking a int in parameter
// if itemtype = false, is just displayed until the user do someting
//               true,  when the user press y is called with 'y' in param
//                                          n                'n'
//               2      the same of above but without 'y' or 'n' restriction
//                      and routine is void routine(event_t *)
void M_StartMessage ( char*         string,
                      void*         routine,
                      int           itemtype );

// Hacks to get time attack to work properly

typedef union
{
    struct menu_s* submenu;               // IT_SUBMENU
    consvar_t* cvar;                  // IT_CVAR
    void             (*routine)(int choice);  // IT_CALL, IT_KEYHANDLER, IT_ARROWS
} itemaction_t;

//
// MENU TYPEDEFS
//
typedef struct menuitem_s
{
    // show IT_xxx
    short       status;

    char* name;

    // FIXME: should be itemaction_t !!!
    void* itemaction;

    // hotkey in menu
    unsigned char   alphaKey;
} menuitem_t;

typedef struct menu_s
{
    char* menutitlepic;
    short           numitems;               // # of menu items
    struct menu_s* prevMenu;               // previous menu
    menuitem_t* menuitems;              // menu items
    void            (*drawroutine)(void);   // draw routine
    short           x;
    short           y;                      // x,y of menu
    short           lastOn;                 // last item user was on in menu
    boolean(*quitroutine)(void);   // called before quit a menu return true if we can
} menu_t;

extern menu_t* currentMenu;
extern menu_t TimeAttackDef;

// So we can modify it in g_game.c
extern int besttimes[32];

#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
