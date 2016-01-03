#include "frmghostit.h"
#include "ui_frmghostit.h"

#include <windows.h>
#include <QDebug>

FrmGhostIt::FrmGhostIt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmGhostIt)
{
    ui->setupUi(this);
    transparency = 100;
    hotkeyRegistered = RegisterHotKey( NULL,
        GHOST_HOTKEY,
        MOD_CONTROL | MOD_ALT | MOD_WIN,
        0x47
    );

    if (!hotkeyRegistered){
        qDebug() << "Error registering CTRL+ALT+WIN G as a hotkey. Already taken.";
    }
    qDebug() << "Hotkey Registered: " << hotkeyRegistered << endl;
}

FrmGhostIt::~FrmGhostIt()
{
    delete ui;
}

bool FrmGhostIt::IsGhosted(HWND__* hwnd){
   exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
   if (exStyle & (WS_EX_LAYERED | WS_EX_TRANSPARENT)) {
      return true;
   }else{
       return false;
   }
}

void FrmGhostIt::GhostIt(HWND__* hwnd){
    exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    newExStyle = exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT;
    ::SetWindowLong(hwnd, GWL_EXSTYLE, newExStyle);
    ::SetLayeredWindowAttributes(hwnd, 0, transparency, LWA_ALPHA);
    ::SetWindowPos(hwnd, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);

    SetForegroundWindow(GetWindow(GetDesktopWindow(), GW_HWNDPREV));
    //GetForegroundWindow()
    lstGhost.append((HWND__**)hwnd);// Add((void*)hwnd);
}

void FrmGhostIt::UnGhostIt(HWND__* hwnd){
    exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
     newExStyle = exStyle & (!(WS_EX_LAYERED | WS_EX_TRANSPARENT));
     ::SetWindowLong(hwnd, GWL_EXSTYLE, newExStyle);
     ::SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
     ::SetWindowPos(hwnd, HWND_NOTOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
     SetForegroundWindow(hwnd);
     lstGhost.removeAt(lstGhost.indexOf((HWND__**)hwnd));// Delete(lstGhost->IndexOf((void*) hwnd));
}

void FrmGhostIt::UnGhostAll(){
    for (int i = lstGhost.size() -1; i >= 0; i--) {
        UnGhostIt((HWND__*)lstGhost.at(i));
    }
}

void FrmGhostIt::IncreaseTransparency(HWND__* hwnd, int howmuch){

}

void FrmGhostIt::EnumerateWindows(){

}
