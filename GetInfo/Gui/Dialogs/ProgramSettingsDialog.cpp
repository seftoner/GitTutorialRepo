#include "ProgramSettingsDialog.h"
#include "ui_ProgramSettingsDialog.h"
#include "../../Core/Items/PluginInfoItem.h"

#include <QDebug>

ProgramSettingsDialog::ProgramSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgramSettingsDialog)
{
    ui->setupUi(this);
    emptyWidget = new QWidget();
    plugins = new QTreeWidgetItem(ui->treeWidget);
    plugins->setText(0, "Plugins");
    ui->stackedWidget->addWidget(emptyWidget);
    ui->treeWidget->expandAll();
}

ProgramSettingsDialog::~ProgramSettingsDialog()
{
    delete ui;
}

void ProgramSettingsDialog::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous)
    qDebug() << current->text(0);
    bool flag = true;

    for (auto currentPluginInfo : pluginsInfoList)
    {
        if(currentPluginInfo->pluginName == current->text(0))
        {
            if (currentPluginInfo->pluginSettingsWidget)
            {
                ui->stackedWidget->setCurrentWidget(currentPluginInfo->pluginSettingsWidget);
                flag = false;
            }
        }
    }
    if (flag)
    {
        ui->stackedWidget->setCurrentWidget(emptyWidget);
    }
}

void ProgramSettingsDialog::clearPluginList()
{
    for(auto child : pluginList)
    {
        plugins->removeChild(child);
    }
    if (pluginList.size() > 0)
    {
        qDeleteAll(pluginList);
        pluginList.clear();
    }
}

void ProgramSettingsDialog::setPluginsList(const QList<QSharedPointer<PluginInfoItem> >& pluginsInfo)
{
    //FIXME after re-calling the function list plugin is duplicated
    clearPluginList();

    this->pluginsInfoList = pluginsInfo;

    for(auto plugin : pluginsInfo)
    {
        QTreeWidgetItem *currentTreeItem = new QTreeWidgetItem(plugins, QStringList(plugin->pluginName));
        currentTreeItem->setIcon(0,plugin->pluginIcon);
        pluginList.append(currentTreeItem);
        if (plugin->pluginSettingsWidget != nullptr)
        {
            qDebug() << "not null";
            QWidget *currentWidget = plugin->pluginSettingsWidget;
            ui->stackedWidget->addWidget(currentWidget);
        }
    }
    plugins->addChild(plugins);
    ui->treeWidget->expandAll();
}
