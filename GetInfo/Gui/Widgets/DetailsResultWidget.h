#ifndef DETAILSRESULTWIDGET_H
#define DETAILSRESULTWIDGET_H

#include <QWidget>

namespace Ui {
class DetailsResultWidget;
}

class DetailsResultWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DetailsResultWidget(QWidget *parent = 0);
    ~DetailsResultWidget();

    QString getProfileUrl() const;

    void setNameText(const QString& text);
    void setSurnameText(const QString& text);
    void setPositionText(const QString& text);
    void setUniversityText(const QString& text);
    void setCityText(const QString& text);
    void setPhoneText(const QString& text);
    void setEmailText(const QString& text);
    void setSkypeText(const QString& text);
    void setPrfileUrlText(const QString& text);

private:
    Ui::DetailsResultWidget *ui;
};

#endif // DETAILSRESULTWIDGET_H
