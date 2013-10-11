#include "DetailsResultWidget.h"
#include "ui_detailsresultwidget.h"

DetailsResultWidget::DetailsResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailsResultWidget)
{

    ui->setupUi(this);

}

DetailsResultWidget::~DetailsResultWidget()
{
    delete ui;
}

QString DetailsResultWidget::getProfileUrl() const
{
    return ui->urlField->text();
}

void DetailsResultWidget::setNameText(const QString &text)
{
    ui->nameField->setText(text);
}

void DetailsResultWidget::setSurnameText(const QString &text)
{
    ui->surnameField->setText(text);
}

void DetailsResultWidget::setPositionText(const QString &text)
{
    ui->positionField->setText(text);
}

void DetailsResultWidget::setUniversityText(const QString &text)
{
    ui->univercityFieldResult->setText(text);
}

void DetailsResultWidget::setCityText(const QString &text)
{
    ui->cityFieldResult->setText(text);
}

void DetailsResultWidget::setPhoneText(const QString &text)
{
    ui->phoneField->setText(text);
}

void DetailsResultWidget::setEmailText(const QString &text)
{
    ui->emailField->setText(text);
}

void DetailsResultWidget::setSkypeText(const QString &text)
{
    ui->skypeField->setText(text);
}

void DetailsResultWidget::setPrfileUrlText(const QString &text)
{
    ui->urlField->setText(text);
}
