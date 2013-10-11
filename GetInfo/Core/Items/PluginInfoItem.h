#ifndef PLUGININFOITEM_H
#define PLUGININFOITEM_H

#include <QWidget>
#include <QIcon>

class PluginInfoItem
{
public:
    PluginInfoItem(): pluginSettingsWidget(nullptr), isReady(false) {}
    PluginInfoItem(const QString pluginName, const QIcon pluginIcon, bool isReady,
                   QWidget* pluginSettingsWidget = nullptr) :
        pluginName(pluginName), pluginIcon(pluginIcon), isReady(isReady),
        pluginSettingsWidget(pluginSettingsWidget){}

public:
    QString pluginName;
    QIcon pluginIcon;
    bool isReady;
    QWidget* pluginSettingsWidget;
};

#endif // PLUGININFOITEM_H

