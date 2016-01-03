#include "frmghostit.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrmGhostIt w;
    w.show();

    QApplication::processEvents();

    MSG msg;
     while(GetMessage(&msg,NULL,0,0)){
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         //poor man's method of doing a hotkey
         /*
         if (GetAsyncKeyState(VK_CONTROL) < 0){
                if (GetAsyncKeyState('G') < 0){
                    qDebug() << "CTRL + G Pressed ";
                }
         }*/

         if (msg.message == WM_HOTKEY){
             if (msg.wParam == GHOST_HOTKEY){

                 qDebug() << "Hot Key activated : WIN + ALT + G";
                 HWND__* hwnd; // = GetForegroundWindow();

                 POINT point;
                 GetCursorPos(&point);
                 //hwnd = ChildWindowFromPoint(//WindowFromPoint(*point);
                 //hwnd = ChildWindowFromPoint(GetDesktopWindow(), point); //WindowFromPoint(point);
                 //TODO: use ChildWindowFromPointEx and pass over hidden windows
                 hwnd = RealChildWindowFromPoint(GetDesktopWindow(), point);

                 qDebug() << hwnd;

                 if (w.IsGhosted(hwnd)){
                     w.UnGhostIt(hwnd);
                     qDebug() << "Unghosting";
                 }else{
                     w.GhostIt(hwnd);

                     qDebug() << "Ghosting";
                 }

             }
         }
     }
    return a.exec();
}
