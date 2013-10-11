#include <QDebug>
#include <QAbstractItemModel>
#include "InputValidator.h"
#include "PluginProcessor.h"

#include "ProgramInit.h"

ProgramInit::ProgramInit(QObject *parent) :
    QObject(parent), isRunnable(true)
{
    qDebug() << "GetInfoInit Constructor";
    try
    {
        core = new Core();
        core->init();
        mainWindow = new MainWindow();
        connectCoreAndGui();
        updateMainWindowData();
    } catch (...)
    {
        qDebug() << "Bad init";
        isRunnable = false;
    }
}

ProgramInit::~ProgramInit()
{
    qDebug() << "GetInfoInit Destructor";
    delete core;
    delete mainWindow;
}

bool ProgramInit::execute()
{
    qDebug() << "--> GetInfoInit::execute()";
    if (!isRunnable)
    {
        return false;
    }
    mainWindow->show();
    return true;
}

void ProgramInit::connectCoreAndGui()
{
    qDebug() << "--> GetInfoInit::connectAll()";

    connect(mainWindow, &MainWindow::searchParameters, core, &Core::search);
    connect(mainWindow, &MainWindow::addNewPlugin, core, &Core::addNewPlugin);
    connect(mainWindow, SIGNAL(textValidation(QString)), core->inputValidator.data(), SLOT(validateText(QString)));
    connect(mainWindow, &MainWindow::getQueryResultTable, core, &Core::getQueryResultModel);
    connect(mainWindow, &MainWindow::deleteHistoryRow, core, &Core::deleteHistoryRow);

    connect(mainWindow, &MainWindow::countryFieldChanged, core, &Core::setCurrentCountry);
    connect(mainWindow, &MainWindow::cityFieldChanged, core, &Core::updateCityModel);
    connect(mainWindow, &MainWindow::knowledgeFieldChanged, core, &Core::updateKnowledgeModel);

    connect(core, &Core::setResultModel, mainWindow , &MainWindow::setSearchResultModel);
    connect(core, &Core::setPluginList, mainWindow, &MainWindow::setupSearchResourcesCheckBoxes);
    connect(core->inputValidator.data(), &InputValidator::showValidateError, mainWindow, &MainWindow::showStatusBarMessage);
    connect(core->inputValidator.data(), &InputValidator::showNoValidateError, mainWindow, &MainWindow::clearStatusBarMessage);
    connect(core, &Core::setResultModel, mainWindow, &MainWindow::setQueryResultModel);
    connect(core, &Core::setPluginErrorMessage,
            mainWindow, &MainWindow::showErrorMessageFromPlugin);
    connect(core->getPluginProcessor(), &PluginProcessor::pluginsResultFinished, mainWindow, &MainWindow::closeProgressBar);
}

void ProgramInit::updateMainWindowData()
{
    mainWindow->setupSearchResourcesCheckBoxes(core->getPluginList());

    mainWindow->setCountryCompleteModel(core->getCountryModel());
    mainWindow->setCityCompleteModel(core->getCityModel());
    mainWindow->setKnowledgeCompleteModel(core->getKnowledgeModel());

    mainWindow->setQueryHistoryModel(core->getQueryHistoryModel());
}

