/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Part of IOMap stack handling tabs.
 *
 * @copyright Redalert++ is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */

#include "tab.h"
#include "ccfileclass.h"
#include "mixfile.h"


#ifndef RAPP_STANDALONE
void *&TabClass::TabShape = Make_Global<void *>(0x0068A4C0);
#else
void *TabClass::TabShape = nullptr;
#endif

TabClass::CreditClass::CreditClass(void) :
    Available(0),
    Credits(0),
    CreditToRedraw(false),
    CreditHasIncreased(false),
    CreditHasChanged(false),
    field_C(0)
{
    return;
}

TabClass::CreditClass::~CreditClass(void)
{
    return;
}

void TabClass::CreditClass::Graphic_Logic(bool a1)
{
#ifndef RAPP_STANDALONE
    void (*func)(const CreditClass *, bool) = reinterpret_cast<void (*)(const CreditClass *, bool)>(0x004ACBB8);
    func(this, a1);
#endif
}
void TabClass::CreditClass::AI(bool a1)
{
#ifndef RAPP_STANDALONE
    void (*func)(const CreditClass *, bool) = reinterpret_cast<void (*)(const CreditClass *, bool)>(0x004ACF04);
    func(this, a1);
#endif
}

TabClass::TabClass()
{
    // help
    /*
    #ifndef RAPP_STANDALONE
        void (*func)(const TabClass *) = reinterpret_cast<void (*)(const TabClass *)>(0x00553340);
        func(this);
    #endif
    */
}

void TabClass::One_Time()
{
    SidebarClass::One_Time();
    TabShape = MixFileClass<CCFileClass>::Retrieve("tabs.shp");
}

void TabClass::AI(KeyNumType &key, int mouse_x, int mouse_y)
{
#ifndef RAPP_STANDALONE
    void (*func)(const TabClass *, KeyNumType &, int, int) =
        reinterpret_cast<void (*)(const TabClass *, KeyNumType &, int, int)>(0x005538D0);
    func(this, key, mouse_x, mouse_y);
#endif
}

void TabClass::Draw_It(BOOL force_redraw)
{
#ifndef RAPP_STANDALONE
    void (*func)(const TabClass *, BOOL) = reinterpret_cast<void (*)(const TabClass *, BOOL)>(0x005533A0);
    func(this, force_redraw);
#endif
}

void TabClass::Flash_Money(void)
{
#ifndef RAPP_STANDALONE
    void (*func)(const TabClass *) = reinterpret_cast<void (*)(const TabClass *)>(0x00553A4C);
    func(this);
#endif
}

void TabClass::Draw_Credits_Tab(void)
{
#ifndef RAPP_STANDALONE
    void (*func)(const TabClass *) = reinterpret_cast<void (*)(const TabClass *)>(0x00553744);
    func(this);
#endif
}

void TabClass::Hilite_Tab(TabEnum tab)
{
#ifndef RAPP_STANDALONE
    void (*func)(TabEnum) = reinterpret_cast<void (*)(TabEnum)>(0x00553868);
    func(tab);
#endif
}

void TabClass::Set_Active(TabEnum tab)
{
    //It seems it might be feed minus values too....
    DEBUG_LOG("TabClass::Set_Active got %d\n", tab);
    // rewrote into a switch, as its cleaner. see binary
    switch (tab) {
        case TAB_OPTIONS:
            //Queue_Options();
            break;

        case TAB_SIDEBAR:
            //Map.Activate(); // Toggles the sidebar.
            break;

        default:
            break;
    }
}