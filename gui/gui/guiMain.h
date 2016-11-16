/***************************************************************
 * Name:      guiMain.h
 * Purpose:   Defines Application Frame
 * Author:    Michael Wu ()
 * Created:   2016-10-27
 * Copyright: Michael Wu ()
 * License:
 **************************************************************/

#ifndef GUIMAIN_H
#define GUIMAIN_H



#include "guiApp.h"



#include "GUIDialog.h"

class guiDialog: public GUIDialog
{
    public:
        guiDialog(wxDialog *dlg);
        ~guiDialog();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};
#endif // GUIMAIN_H
