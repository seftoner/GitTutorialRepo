#ifndef PROGRAMSETTINGSDIALOG_H
#define PROGRAMSETTINGSDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class ProgramSettingsDialog;
}

class PluginInfoItem;

class ProgramSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProgramSettingsDialog(QWidget *parent = 0);
    ~ProgramSettingsDialog();

public slots:
    void setPluginsList(const QList<QSharedPointer<PluginInfoItem> >& pluginsInfo);

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::ProgramSettingsDialog* ui;
    QList<QSharedPointer<PluginInfoItem> > pluginsInfoList;
    QList<QTreeWidgetItem *> pluginList;
    QWidget* emptyWidget;
    QTreeWidgetItem* plugins;

private:
    void clearPluginList();
};

#endif // PROGRAMSETTINGSDIALOG_H
