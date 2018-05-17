/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Part of IOMap stack handling mouse input.
 *
 * @copyright Redalert++ is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */

#include "gmouse.h"
#include "ccfileclass.h"
#include "mixfile.h"
#include "tab.h"
#include "mouseshape.h"

#ifndef RAPP_STANDALONE
void *&GameMouseClass::MouseShapes = Make_Global<void *>(0x00685160);
#else
void *GameMouseClass::MouseShapes = nullptr;
#endif

//
//
//
// Frame, Count, Rate, Small, HotSpotX, HotSpotY
GameMouseClass::MouseStruct GameMouseClass::MouseControl[MOUSE_COUNT] = {
    { 0, 1, 0, 80, 0, 0 }, // 0		//Arrow
    { 1, 1, 0, -1, 14, 0 }, // 1		//ScrollN
    { 2, 1, 0, -1, 29, 0 }, // 2		//ScrollNE
    { 3, 1, 0, -1, 29, 11 }, // 3		//ScrollE
    { 4, 1, 0, -1, 29, 23 }, // 4		//ScrollSE
    { 5, 1, 0, -1, 14, 23 }, // 5		//ScrollS
    { 6, 1, 0, -1, 0, 23 }, // 6		//ScrollSW
    { 7, 1, 0, -1, 0, 11 }, // 7		//ScrollW
    { 8, 1, 0, -1, 0, 0 }, // 8		//ScrollNW
    { 124, 1, 0, -1, 14, 0 }, // 9		//NoScrollN
    { 125, 1, 0, -1, 29, 0 }, // 10	//NoScrollNE
    { 126, 1, 0, -1, 29, 11 }, // 11	//NoScrollE
    { 127, 1, 0, -1, 29, 23 }, // 12	//NoScrollSE
    { 128, 1, 0, -1, 14, 23 }, // 13	//NoScrollS
    { 129, 1, 0, -1, 0, 23 }, // 14	//NoScrollSW
    { 130, 1, 0, -1, 0, 11 }, // 15	//NoScrollW
    { 131, 1, 0, -1, 0, 0 }, // 16	//NoScrollNW
    { 14, 1, 0, 33, 14, 11 }, // 17	//NoMove
    { 10, 4, 4, 29, 14, 11 }, // 18	//NotAllowed		//guessed name
    { 113, 3, 4, 142, 14, 11 }, // 19	//Enter
    { 59, 9, 4, -1, 14, 11 }, // 20	//Deploy
    { 15, 6, 4, -1, 14, 11 }, // 21	//Select
    { 21, 8, 4, 134, 14, 11 }, // 22	//Harvest
    { 68, 12, 2, -1, 14, 11 }, // 23	//Sell
    { 148, 12, 2, -1, 14, 11 }, // 24	//SellUnit
    { 35, 24, 2, -1, 14, 11 }, // 25	//Repair
    { 120, 1, 0, -1, 14, 11 }, // 26	//NoRepair
    { 119, 1, 0, -1, 14, 11 }, // 27	//NoSell
    { 81, 1, 0, 145, 14, 11 }, // 28	//
    { 90, 7, 4, -1, 14, 11 }, // 29	//NukeBomb
    { 82, 8, 2, 213, 14, 11 }, // 30	//Airstrike
    { 116, 3, 4, 121, 14, 11 }, // 31	//Sabotage
    { 147, 1, 0, 146, 14, 11 }, // 32	//GuardArea
    { 160, 4, 4, 194, 14, 11 }, // 33	//Heal
    { 164, 3, 4, 167, 14, 11 }, // 34	//Damage
    { 170, 24, 2, -1, 14, 11 }, // 35	//GRepair
    { 195, 8, 4, 203, 14, 11 }, // 36	//Attack
    { 211, 1, 0, -1, 14, 11 }, // 37	//NoDeploy
    { 212, 1, 0, -1, 14, 11 }, // 38	//NoEnter
    { 213, 1, 0, -1, 14, 11 }, // 39	//NoGRepair
    { 97, 8, 3, -1, 14, 11 }, // 40	//Chronosphere
    { 105, 8, 2, -1, 14, 11 }, // 41	//Chrono2
    { 211, 1, 0, 80, 0, 0 } // 42	//EditorBrush
};

GameMouseClass::GameMouseClass()
{
#ifndef RAPP_STANDALONE
    void (*func)(const GameMouseClass *) = reinterpret_cast<void (*)(const GameMouseClass *)>(0x004D2270);
    func(this);
#endif
}

void GameMouseClass::One_Time()
{
    TabClass::One_Time();
    MouseShapes = MixFileClass<CCFileClass>::Retrieve("mouse.shp");
}

void GameMouseClass::Init_Clear()
{
    HelpClass::Init_Clear();
    MouseShape = MOUSE_POINTER;
    MouseInRadar = false;
}

void GameMouseClass::AI(KeyNumType &key, int mouse_x, int mouse_y)
{
#ifndef RAPP_STANDALONE
    DEFINE_CALL(func, 0x0050329C, void, (const GameMouseClass *, KeyNumType &, int, int));
    func(this, key, mouse_x, mouse_y);
#endif
}

void GameMouseClass::Set_Default_Mouse(MouseType mouse, BOOL a2)
{
    if (mouse != MOUSE_NONE && mouse < MOUSE_COUNT) {
        MouseShape = mouse;
        Override_Mouse_Shape(mouse, a2);
    }
}

BOOL GameMouseClass::Override_Mouse_Shape(MouseType mouse, BOOL a2)
{
#ifndef RAPP_STANDALONE
    DEFINE_CALL(func, 0x0050316C, BOOL, (GameMouseClass *, MouseType, BOOL));
    return func(this, mouse, a2);
#endif
}

void GameMouseClass::Revert_Mouse_Shape()
{
    Override_Mouse_Shape(PreviousMouseShape);
}

void GameMouseClass::Mouse_Small(BOOL use_small_frame)
{
    if (MouseInRadar != use_small_frame) {
        if (use_small_frame) {
            if (MouseControl[PreviousMouseShape].Small == -1) {
                //
                //
                //
                g_mouse->Set_Cursor(MouseControl[MOUSE_POINTER].HotSpotX,
                    MouseControl[MOUSE_POINTER].HotSpotY,
                    Extract_Shape(MouseShapes, 0));
            } else {
                //
                //
                //
                g_mouse->Set_Cursor(MouseControl[MouseShape].HotSpotX,
                    MouseControl[MouseShape].HotSpotY,
                    Extract_Shape(MouseShapes, MouseControl[MouseShape].Small + MouseFrame));
            }
        } else {
            //
            //
            //
            g_mouse->Set_Cursor(MouseControl[MouseShape].HotSpotX,
                MouseControl[MouseShape].HotSpotY,
                Extract_Shape(MouseShapes, MouseControl[MouseShape].Frame + MouseFrame));
        }
    }
}

MouseType GameMouseClass::Get_Mouse_Shape(void) const
{
    return MouseShape;
}

BOOL GameMouseClass::Load(Straw &straw)
{
    return false; // TODO
}

BOOL GameMouseClass::Save(Pipe &pipe) const
{
    return false; // TODO
}