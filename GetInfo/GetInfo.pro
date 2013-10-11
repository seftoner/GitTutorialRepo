#-------------------------------------------------
#
# Project created by QtCreator 2013-07-09T11:30:24
#
#-------------------------------------------------

QT       += core gui sql

unix{
QMAKE_CXXFLAGS += -std=c++11
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GetInfoProject

QMAKE_PROJECT_NAME = GetInfo

win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/
    CONFIG(release, release|debug):DESTDIR = ../release/
} else {
    DESTDIR    = ../
}

target.path = $$OUT_PWD/../GetInfoProject/
INSTALLS = target

SOURCES += main.cpp\
    Core/Models/ResultModel.cpp \
    Core/Core.cpp \
    MainWindow.cpp \
    Core/PluginProcessor.cpp \
    Core/InputValidator.cpp \
    Core/Models/ResultProxyModel.cpp \
    Gui/Widgets/DetailsResultWidget.cpp \
    Core/DB/SqliteDB.cpp \
    Core/DB/DataBaseFactory.cpp \
    Core/Models/HistoryModel.cpp \
    Core/Models/HistroyProxyModel.cpp \
    Core/Models/UniqueColumnProxyModel.cpp \
    Core/ProgramInit.cpp \
    Gui/Dialogs/ProgramSettingsDialog.cpp \
    Core/DB/CountryCityModelGenerator.cpp \
    Core/DB/KnowledgeModelGenerator.cpp \
    Core/CompletionChecker.cpp

HEADERS  += \
    Core/ResultDisplay.h \
    Core/Models/ResultModel.h \
    Core/Items/ResultItem.h \
    Core/Items/SearchParameters.h \
    Core/Core.h \
    MainWindow.h \
    Core/PluginProcessor.h \
    Core/IInputValidator.h \
    Core/InputValidator.h \
    Core/Models/ResultProxyModel.h \
    Core/DB/IDataBase.h \
    Gui/Widgets/DetailsResultWidget.h \
    Core/DB/SqliteDB.h \
    Core/DB/DataBaseFactory.h \
    Core/Models/HistoryModel.h \
    Core/DB/SqliteQuery.h \
    Core/Items/HistoryItem.h \
    Core/Models/HistroyProxyModel.h \
    Core/Models/DisplayHistoryColumn.h \
    Core/Models/UniqueColumnProxyModel.h \
    Core/ProgramInit.h \
    Gui/Dialogs/ProgramSettingsDialog.h \
    Core/Items/PluginInfoItem.h \
    Core/PluginInterface.h \
    Core/DB/CountryCityModelGenerator.h \
    Core/DB/KnowledgeModelGenerator.h \
    Core/CompletionChecker.h

FORMS    += mainwindow.ui \
    Gui/Widgets/detailsresultwidget.ui \
    Gui/Delegates/Widgets/PluginListItemWidget.ui \
    Gui/Dialogs/ProgramSettingsDialog.ui

RESOURCES += \
    Icons.qrc
