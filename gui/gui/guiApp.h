/***************************************************************
 * Name:      guiApp.h
 * Purpose:   Defines Application Class
 * Author:    Michael Wu ()
 * Created:   2016-10-27
 * Copyright: Michael Wu ()
 * License:
 **************************************************************/

#ifndef GUIAPP_H
#define GUIAPP_H

#include <wx/app.h>

class guiApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // GUIAPP_H
