#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QCheckBox>
#include <QFormLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QCloseEvent>
#include <QSettings>
#include <QMenu>
#include <QCompleter>

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Gui/Dialogs/ProgramSettingsDialog.h"
#include "Core/ResultDisplay.h"
#include "Core/Models/DisplayHistoryColumn.h"
#include "Core/Models/UniqueColumnProxyModel.h"
#include "Core/Models/HistroyProxyModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    resultModel(nullptr),
    mainWindowSettingsReaded(false)
{
    ui->setupUi(this);
    createDialogs();
    createConnections();
    initUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    countryCompleter = new QCompleter(this);
    cityCompleter = new QCompleter(this);
    knowledgeCompleter = new QCompleter(this);

    countryCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    countryCompleter->setMaxVisibleItems(10);
    cityCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    cityCompleter->setMaxVisibleItems(10);
    knowledgeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    knowledgeCompleter->setMaxVisibleItems(10);

    ui->countryField->setCompleter(countryCompleter);
    ui->cityField->setCompleter(cityCompleter);
    ui->knowledgeField->setCompleter(knowledgeCompleter);

    ui->tabWidget->setCurrentIndex(kSearchTabIndex);
    ui->resultListView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->historyTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->filterWidget->setVisible(false);
    ui->resultStackedWidget->setCurrentWidget(ui->resultListViewPage);

}

void MainWindow::createFilterComboBoxModels()
{
    createComboBoxModel(ui->knowledgeCmb, HistoryModelData::Knowledge);
    createComboBoxModel(ui->cityCmb, HistoryModelData::City);
    createComboBoxModel(ui->countryCmb, HistoryModelData::Country);
    createComboBoxModel(ui->universityCmb, HistoryModelData::University);
    createComboBoxModel(ui->resourceNameCmb, HistoryModelData::ResourceName);
}

void MainWindow::createComboBoxModel(QComboBox* comboBox, const int column)
{
    delete comboBox->model();

    UniqueColumnProxyModel *uniqueProxyModel = new UniqueColumnProxyModel(this,
                                                                          column);
    uniqueProxyModel->setSourceModel(queryHistoryModel);
    comboBox->setModel(uniqueProxyModel);
    comboBox->setModelColumn(column);
}

void MainWindow::createConnections()
{
    connect(ui->actionSettings, &QAction::triggered, settingsDialog,
            &ProgramSettingsDialog::show);
    connect(ui->resultListView, &QTableView::clicked,
            this, &MainWindow::setResultData);
    connect(this, &MainWindow::setPluginsList, settingsDialog,
            &ProgramSettingsDialog::setPluginsList);
//    connect(settingsDialog, &SettingsDialog::addNewPluginPath,
//            this, &MainWindow::addNewPlugin);
    connect(ui->countryField, &QLineEdit::textChanged,
            this, &MainWindow::countryFieldChanged);
    connect(ui->cityField, &QLineEdit::textChanged,
            this, &MainWindow::cityFieldChanged);
    connect(ui->knowledgeField, &QLineEdit::textChanged,
            this, &MainWindow::knowledgeFieldChanged);

    connect(ui->historyTableView, &QTableView::doubleClicked,
            this, &MainWindow::openQueryResult);
    connect(ui->tabWidget, &QTabWidget::currentChanged,
            this, &MainWindow::changeMenuBarButtonVisibility);
}

void MainWindow::setupSearchResourcesCheckBoxes(const QList<QSharedPointer<PluginInfoItem> >&
                                                searchResList)
{
    qDebug() << "setupResourcesView: " << searchResList.count();

    clearSearchResourcesCheckBoxes();
    resNameCheckBxsLayout = new QVBoxLayout(ui->activeResourceWidget);

    for (auto searchRes : searchResList)
    {
        QCheckBox *chkBox = new QCheckBox(searchRes->pluginName, this);

        if (!searchRes->isReady)
        {
            chkBox->setEnabled(false);
            chkBox->setText(searchRes->pluginName + "(" + tr("unautorized") + ")");
        }

        resourceNameCheckBoxes.append(chkBox);
        resNameCheckBxsLayout->addWidget(chkBox);
    }
    resNameCheckBxsLayout->addItem(new  QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    if(!mainWindowSettingsReaded)
    {
        readSettings();
    }

    emit setPluginsList(searchResList);
}

void MainWindow::createDialogs()
{
    settingsDialog =  new ProgramSettingsDialog(this);
    settingsDialog->setWindowFlags(settingsDialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
   // settingsDialog->setPluginsList();
    settingsDialog->setModal(true);
}

void MainWindow::on_actionSearch_triggered()

{
    qDebug("search btn pressed");
    auto searchParam = getEnteredSearchParameters();
    emit searchParameters(searchParam);
    ui->resultStackedWidget->setCurrentWidget(ui->resultProgressBarPage);
    ui->tabWidget->setCurrentIndex(kResultTabIndex);
}

void MainWindow::setSearchResultModel(QAbstractItemModel* model)
{
    resultModel = model;
    ui->resultListView->setModel(model);
}

void MainWindow::setResultData(const QModelIndex& index)
{
    //find addresses of the base model

    auto* proxyModel = static_cast<QSortFilterProxyModel*>(resultModel);
    auto& mapIndex = proxyModel->mapToSource(index);
    auto* resModel = proxyModel->sourceModel();
    ui->detailsResultWidget->setNameText(resModel->index(mapIndex.row(), Name).data().toString());
    ui->detailsResultWidget->setSurnameText(resModel->index(mapIndex.row(), Surname).data().toString());
    ui->detailsResultWidget->setPositionText(resModel->index(mapIndex.row(), Position).data().toString());
    ui->detailsResultWidget->setCityText(resModel->index(mapIndex.row(), City).data().toString());
    ui->detailsResultWidget->setUniversityText(resModel->index(mapIndex.row(), University).data().toString());
    ui->detailsResultWidget->setPhoneText(resModel->index(mapIndex.row(), Phone).data().toString());
    ui->detailsResultWidget->setEmailText(resModel->index(mapIndex.row(), Email).data().toString());
    ui->detailsResultWidget->setSkypeText(resModel->index(mapIndex.row(), Skype).data().toString());
    ui->detailsResultWidget->setPrfileUrlText(resModel->index(mapIndex.row(), ProfileUrl).data().toString());
}

void MainWindow::setQueryHistoryModel(QAbstractItemModel *model)
{
    queryHistoryModel = model;
    proxyQueryHistoryModel = new HistroyProxyModel(this);
    proxyQueryHistoryModel->setSourceModel(queryHistoryModel);
    ui->historyTableView->setModel(proxyQueryHistoryModel);
    ui->historyTableView->hideColumn(0);
    createFilterComboBoxModels();
    connectFilterSettingsWithProxyModel();
}

void MainWindow::connectFilterSettingsWithProxyModel()
{
    connect(ui->knowledgeCmb, &QComboBox::currentTextChanged,
            proxyQueryHistoryModel, &HistroyProxyModel::setKnowledge);
    connect(ui->cityCmb, &QComboBox::currentTextChanged,
            proxyQueryHistoryModel, &HistroyProxyModel::setCity);
    connect(ui->universityCmb, &QComboBox::currentTextChanged,
            proxyQueryHistoryModel, &HistroyProxyModel::setUniversity);
    connect(ui->countryCmb, &QComboBox::currentTextChanged,
            proxyQueryHistoryModel, &HistroyProxyModel::setCountry);

    connect(ui->dateFrom, &QDateTimeEdit::dateTimeChanged, proxyQueryHistoryModel,
            &HistroyProxyModel::setDateFrom);
    connect(ui->dateTo, &QDateTimeEdit::dateTimeChanged, proxyQueryHistoryModel,
            &HistroyProxyModel::setDateTo);
    connect(ui->resourceNameCmb, &QComboBox::currentTextChanged, proxyQueryHistoryModel,
            &HistroyProxyModel::setResourceName);
}

void MainWindow::readSettings()
{
    QSettings settings("Eleks", "GetInfo");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    if (settings.value("maximized", false).toBool())
    {
        showMaximized();
    }
    settings.beginGroup("Plugins");
    for (QCheckBox *currentCheckBox: resourceNameCheckBoxes)
    {
        currentCheckBox->setChecked(settings.value(currentCheckBox->text(), false).toBool());
        qDebug() << currentCheckBox->text() << currentCheckBox->isChecked();
    }
    settings.endGroup(); // Plugins
    settings.beginGroup("Search Parameters");
    ui->countryField->setText(settings.value("Country", "").toString());
    ui->cityField->setText(settings.value("City", "").toString());
    ui->univercityField->setText(settings.value("University", "").toString());
    ui->knowledgeField->setText(settings.value("Knowledge", "").toString());
    settings.endGroup(); // Search Parameters
    ui->splitter->restoreState(settings.value("SearchSplitter", QByteArray(200,200)).toByteArray());
    ui->splitter_2->restoreState(settings.value("ResultSplitter", QByteArray(200,200)).toByteArray());
    settings.endGroup(); // MainWindow

    emit countryFieldChanged(ui->countryField->text());
    emit cityFieldChanged(ui->cityField->text());
    emit knowledgeFieldChanged(ui->knowledgeField->text());
    mainWindowSettingsReaded = true;
}

void MainWindow::writeSettings()
{
    QSettings settings("Eleks", "GetInfo");

    settings.beginGroup("MainWindow");
    settings.setValue("maximized", isMaximized());
    if (!isMaximized())
    {
        settings.setValue("size", size());
        settings.setValue("pos", pos());
    }
    settings.beginGroup("Plugins");
    for (QCheckBox *currentCheckBox: resourceNameCheckBoxes)
    {
        settings.setValue(currentCheckBox->text(), currentCheckBox->isChecked());
        qDebug() << currentCheckBox->text() << currentCheckBox->isChecked();
    }
    settings.endGroup(); // Plugins
    settings.beginGroup("Search Parameters");
    settings.setValue("Country", ui->countryField->text());
    settings.setValue("City", ui->cityField->text());
    settings.setValue("University", ui->univercityField->text());
    settings.setValue("Knowledge",  ui->knowledgeField->text());
    settings.endGroup(); // Search Parameters
    settings.setValue("SearchSplitter", ui->splitter->saveState());
    settings.setValue("ResultSplitter", ui->splitter_2->saveState());
    settings.endGroup(); // MainWindow
}

void MainWindow::clearSearchResourcesCheckBoxes()
{
    if (/*!resNameCheckBxsLayout &&*/
            resourceNameCheckBoxes.size() > 0)
    {
        delete resNameCheckBxsLayout;
        qDeleteAll(resourceNameCheckBoxes);
        resourceNameCheckBoxes.clear();
    }
}

SearchParameters MainWindow::getEnteredSearchParameters()
{
    const SearchParameters enteredParameters(
                ui->univercityField->text(),
                ui->knowledgeField->text(),
                ui->cityField->text(),
                ui->countryField->text(),
                getActivatedSearchRes()
                );

    return enteredParameters;
}

QStringList MainWindow::getActivatedSearchRes()
{
    QStringList result;

    for (int index = 0; index < resourceNameCheckBoxes.count(); ++index)
    {
        if (resourceNameCheckBoxes[index]->isEnabled() &&
                resourceNameCheckBoxes[index]->isChecked())
        {
            result << resourceNameCheckBoxes[index]->text();
        }
    }
    return result;
}

void MainWindow::on_countryField_editingFinished()
{
    updateStatusBar(ui->countryField);
    emit countryFieldChanged(ui->countryField->text());
}

void MainWindow::on_cityField_editingFinished()
{
    updateStatusBar(ui->cityField);
}

void MainWindow::updateStatusBar(QLineEdit* currentLineEdit)
{
    qDebug() << "--->> MainWindow::updateStatusBar(QLineEdit* currentLineEdit)";
    emit textValidation(currentLineEdit->text());
}

void MainWindow::showStatusBarMessage(const QString& text)
{
    qDebug() << "--->> MainWindow::showMessage(QString& message)";
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::red);
    ui->statusBar->setPalette(palette);
    ui->statusBar->showMessage(text);
    // TODO fix program crash on setfocus in some situations
    //currentLineEdit->setFocus();
    ui->searchBtn->setEnabled(false);
}

void MainWindow::showErrorMessageFromPlugin(const QString& errorMsg)
{
    QMessageBox errorMsgBox;
    errorMsgBox.setText(errorMsg);
    errorMsgBox.exec();
}

void MainWindow::setQueryResultModel(QAbstractItemModel *model)
{
    queryResultModel = model;
    ui->resultListView->setModel(queryResultModel);
    ui->tabWidget->setCurrentIndex(kResultTabIndex);
}

void MainWindow::setCountryCompleteModel(QAbstractItemModel* model)
{
    countryCompleter->setModel(model);
    QTreeView *treeView = new QTreeView(this);
    countryCompleter->setPopup(treeView);
    treeView->setRootIsDecorated(false);
    treeView->header()->hide();
    treeView->header()->setStretchLastSection(false);
    treeView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

void MainWindow::setCityCompleteModel(QAbstractItemModel* model)
{
    cityCompleter->setModel(model);
}

void MainWindow::setKnowledgeCompleteModel(QAbstractItemModel* model)
{
    knowledgeCompleter->setModel(model);
}

void MainWindow::closeProgressBar()
{
    ui->resultStackedWidget->setCurrentWidget(ui->resultListViewPage);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int closeRetCode = QMessageBox::question(this, tr("Get Info"),
                                             tr("Do you want to end a program 'Get Info', and exit ?"),
                                             QMessageBox::Ok | QMessageBox::Cancel,
                                             QMessageBox::Ok);
    if (closeRetCode == QMessageBox::Ok)
    {
        writeSettings();
        this->close();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::clearStatusBarMessage()
{
    ui->statusBar->clearMessage();
    ui->searchBtn->setEnabled(true);
}

void MainWindow::on_openProfile_clicked()
{
    QDesktopServices::openUrl(QUrl(ui->detailsResultWidget->getProfileUrl()));
}

void MainWindow::on_bookMrkBtn_clicked()
{
    //TODO Add current user profile info to data base
}

void MainWindow::openQueryResult(const QModelIndex &index)
{
    int id = proxyQueryHistoryModel->index(index.row(), 0).data().toInt();
    emit getQueryResultTable(id);
}

void MainWindow::deleteQueryResult(const QModelIndex &index)
{
    int id = proxyQueryHistoryModel->index(index.row(), 0).data().toInt();
    proxyQueryHistoryModel->removeRow(index.row());

    if (resultModel)
    {
        resultModel->removeRows(0, resultModel->rowCount());
    }

    emit deleteHistoryRow(id);
}

void MainWindow::changeMenuBarButtonVisibility(const int &currentTabIndex)
{
    ui->actionEnable_filter->setDisabled(currentTabIndex != kHistoryTabIndex);
}

void MainWindow::on_actionEnable_filter_triggered()
{
    ui->filterWidget->setVisible(!ui->filterWidget->isVisible());
    if (!filterEnabled)
    {
        ui->actionEnable_filter->setText(tr("Enable filter"));
        filterEnabled = true;
        proxyQueryHistoryModel->clearFilter();
    }
    else
    {
        ui->actionEnable_filter->setText(tr("Disable filter"));
        filterEnabled = false;
    }
}

void MainWindow::on_historyTableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu historyContextMenu(ui->historyTableView);
    historyContextMenu.addAction(ui->actionOpenSearchResults);
    historyContextMenu.addAction(ui->actionDeleteHistoryRecord);

    ui->actionOpenSearchResults->setData(pos);
    ui->actionDeleteHistoryRecord->setData(pos);

    historyContextMenu.exec(ui->historyTableView->mapToGlobal(pos));
}

void MainWindow::on_actionOpenSearchResults_triggered()
{
    auto pos = ui->actionOpenSearchResults->data().toPoint();
    auto index = ui->historyTableView->indexAt(pos);
    openQueryResult(index);
}

void MainWindow::on_actionDeleteHistoryRecord_triggered()
{
    auto pos = ui->actionOpenSearchResults->data().toPoint();
    auto index = ui->historyTableView->indexAt(pos);
    deleteQueryResult(index);
}
