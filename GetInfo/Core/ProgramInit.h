#ifndef GETINFOINIT_H
#define GETINFOINIT_H

#include <QObject>
#include <QSharedPointer>

#include "../MainWindow.h"
#include "../Gui/Dialogs/ProgramSettingsDialog.h"
#include "Core.h"

class ProgramInit : public QObject
{
    Q_OBJECT
public:
    explicit ProgramInit(QObject *parent = 0);
    ~ProgramInit();
    bool execute();

private:
    void connectCoreAndGui();
    void updateMainWindowData();

private:
    MainWindow *mainWindow;
    ProgramSettingsDialog *settingsDialog;
    Core *core;
    bool isRunnable;
    
};

#endif // GETINFOINIT_H
