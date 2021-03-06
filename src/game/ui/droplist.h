/**
 * @file
 *
 * @author OmniBlade
 * @author CCHyper
 *
 * @brief Class for representing a droppable lists of selectable options.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef DROPLIST_H
#define DROPLIST_H

#include "always.h"
#include "edit.h"
#include "list.h"
#include "shapebtn.h"

class DropListClass : public EditClass
{
public:
    DropListClass(int id, char *text_buff, int text_size, TextPrintType style, int x, int y, int w, int h,
        void *up_btn_shape, void *down_btn_shape);
    DropListClass(DropListClass &that);
    virtual ~DropListClass() {}

    virtual LinkClass &Add(LinkClass &link) override;
    virtual LinkClass &Add_Tail(LinkClass &link) override;
    virtual LinkClass &Add_Head(LinkClass &link) override;
    virtual void Zap() override;
    virtual GadgetClass *Remove() override;
    virtual void Flag_To_Redraw() override;
    virtual void Peer_To_Peer(unsigned flags, KeyNumType &key, ControlClass &peer) override;
    virtual void Clear_Focus() override;
    virtual void Set_Position(int x, int y) override;
    virtual int Add_Item(const char *string);
    virtual const char *Current_Item() const;
    virtual int Current_Index();
    virtual void Set_Selected_Index(int string_index);
    virtual void Set_Selected_Index(const char *string);
    virtual int Count() const;
    virtual const char *Get_Item(int const string_index) const;

    DropListClass &operator=(DropListClass &that);

    void Expand();
    void Collapse();

protected:
#ifndef CHRONOSHIFT_NO_BITFIELDS
    // Union/Struct required to get correct packing when compiler packing set to 1.
    union
    {
        struct
        {
            bool IsExpanded : 1; // & 1
        };
        int m_dropListFlags;
    };
#else
    bool IsExpanded;
#endif
    int DropHeight;
    ShapeButtonClass DropButton;
    ListClass DropList;
};

inline DropListClass &DropListClass::operator=(DropListClass &that)
{
    if (this != &that) {
        EditClass::operator=(that);
        IsExpanded = that.IsExpanded;
        DropHeight = that.DropHeight;
        DropButton = that.DropButton;
        DropList = that.DropList;
        DropButton.Make_Peer(*this);
        DropList.Make_Peer(*this);
    }

    return *this;
}

#endif // DROPLIST_H
