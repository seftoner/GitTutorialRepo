#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

#include "Core/Items/SearchParameters.h"
#include "Core/Items/PluginInfoItem.h"


namespace Ui {
class MainWindow;
}

class ProgramSettingsDialog;
class QModelIndex;
class QAbstractItemModel;
class QSortFilterProxyModel;
class QCheckBox;
class QComboBox;
class HistroyProxyModel;
class QVBoxLayout;
class QCompleter;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void on_actionSearch_triggered();
    void setSearchResultModel(QAbstractItemModel *model);
    void setResultData(const QModelIndex &index);
    void setQueryHistoryModel(QAbstractItemModel *model);

    void on_countryField_editingFinished();
    void on_cityField_editingFinished();
    void setupSearchResourcesCheckBoxes(const QList<QSharedPointer<PluginInfoItem> >& pluginsList);
    void clearStatusBarMessage();
    void showStatusBarMessage(const QString &text);
    void showErrorMessageFromPlugin(const QString &errorMsg);
    void setQueryResultModel(QAbstractItemModel *model);

    void setCountryCompleteModel(QAbstractItemModel *model);
    void setCityCompleteModel(QAbstractItemModel *model);
    void setKnowledgeCompleteModel(QAbstractItemModel *model);
    void closeProgressBar();

protected:
    void closeEvent(QCloseEvent * event);

private:
    Ui::MainWindow *ui;
    ProgramSettingsDialog *settingsDialog;
    QAbstractItemModel *resultModel;
    QAbstractItemModel *queryHistoryModel;
    HistroyProxyModel *proxyQueryHistoryModel;
    QAbstractItemModel *queryResultModel;
    QAbstractItemModel *queryHistoryWithFakeRowModel;
    QVector<QCheckBox*> resourceNameCheckBoxes;
    QVBoxLayout* resNameCheckBxsLayout;

    QCompleter* countryCompleter;
    QCompleter* cityCompleter;
    QCompleter* knowledgeCompleter;

    bool filterEnabled;
    bool mainWindowSettingsReaded;

    static const int kSearchTabIndex = 0;
    static const int kResultTabIndex = 1;
    static const int kHistoryTabIndex = 2;

private:
    void createDialogs();
    void createConnections();
    void updateStatusBar(QLineEdit* currentLineEdit);
    SearchParameters getEnteredSearchParameters();
    QStringList getActivatedSearchRes();
    void initUi();
    void createFilterComboBoxModels();
    void createComboBoxModel(QComboBox *comboBox, const int column);
    void connectFilterSettingsWithProxyModel();
    void readSettings();
    void writeSettings();
    void clearSearchResourcesCheckBoxes();

signals:
    void searchParameters(const SearchParameters& parameters);
    void addNewPlugin(const QString& path);
    void textValidation(const QString &currentLineText);
    void getQueryResultTable(const int& id);
    void setPluginsList(const QList<QSharedPointer<PluginInfoItem> >& pluginsList);
    void deleteHistoryRow(const int& id);

    void countryFieldChanged(const QString& text);
    void cityFieldChanged(const QString& text);
    void knowledgeFieldChanged(const QString& text);

private slots:
    void on_openProfile_clicked();
    void on_bookMrkBtn_clicked();
    void openQueryResult(const QModelIndex& index);
    void deleteQueryResult(const QModelIndex& index);
    void changeMenuBarButtonVisibility(const int& currentTabIndex);
    void on_actionEnable_filter_triggered();
    void on_historyTableView_customContextMenuRequested(const QPoint &pos);
    void on_actionOpenSearchResults_triggered();
    void on_actionDeleteHistoryRecord_triggered();
};

#endif // MAINWINDOW_H
