#ifndef FRMGHOSTIT_H
#define FRMGHOSTIT_H

#include <QDialog>
#include <windows.h>
#include <vector>
#include <QList>


#define GHOST_HOTKEY 0x0001 //0x0000 through 0xBFFF are valid

using namespace std;


namespace Ui {
class FrmGhostIt;
}

class FrmGhostIt : public QDialog
{
    Q_OBJECT

public:
    explicit FrmGhostIt(QWidget *parent = 0);
    ~FrmGhostIt();

    void GhostIt(HWND__* hwnd);
    void UnGhostIt(HWND__* hwnd);
    bool IsGhosted(HWND__* hwnd);
    void UnGhostAll();
    void IncreaseTransparency(HWND__* hwnd, int howmuch = 10);
    void EnumerateWindows();

    std::vector<HWND__*> windows;
    QList<HWND*> lstGhost;
    int transparency;
    bool hotkeyRegistered;

private:
    Ui::FrmGhostIt *ui;
    DWORD lastStyle;
    DWORD exStyle, newExStyle;
    HWND* hwnd;
};

BOOL CALLBACK EnumWindowsProc(HANDLE hWnd, LPARAM lparam);

#endif // FRMGHOSTIT_H
