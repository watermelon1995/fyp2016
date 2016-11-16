/***************************************************************
 * Name:      guiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Michael Wu ()
 * Created:   2016-10-27
 * Copyright: Michael Wu ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "guiApp.h"
#include "guiMain.h"

IMPLEMENT_APP(guiApp);

bool guiApp::OnInit()
{
    
    guiDialog* dlg = new guiDialog(0L);
    
    dlg->Show();
    return true;
}
