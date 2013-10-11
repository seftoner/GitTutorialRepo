#include "InputValidator.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>

InputValidator::InputValidator() : QObject(nullptr)
{
    qDebug() << "Validation Constructor";
}

InputValidator::~InputValidator()
{
    qDebug() << "Validation Destructor";
}

QString InputValidator::getErrorMessage()
{
    qDebug() << "--> InputValidator::getErrorMessage()";
    return errorMessage;
}

void InputValidator::validateText(const QString &text)
{
    qDebug() << "InputValidator::validateText()";
    if (!isValidData(text,1))
    {
        emit showValidateError(getErrorMessage());
    }
    else
    {
        emit showNoValidateError();
    }
}

bool InputValidator::isValidData(const QString &inputText, int minimumLength = 0)
{
    qDebug() << "--> InputValidator::isValidData()";
    auto trimedText = inputText.trimmed();
    if (isTooSmall(trimedText, minimumLength))
    {
        return false;
    }
    return true;
}

bool InputValidator::hasIncorrectSymbols(QString& inputText)
{
    qDebug() << "--> InputValidator::hasIncorrectSymbols()";
    QRegExp rx("^[а-яА-ЯіІїЇєЄэЭъЪыЫёЁa-zA-Z0-9 -]+$");
    if(rx.exactMatch(inputText))
    {
        return false;
    }
    errorMessage = QString("Found incorrect symbol in input text");
    return true;
}

bool InputValidator::isTooSmall(QString& inputText, int& minimumLength)
{
    qDebug() << "--> InputValidator::isTooSmall()";
    if (inputText.length() >= minimumLength)
    {
        return false;
    }
    errorMessage = "Too small input text. Minimum length is " + QString::number(minimumLength);
    return true;
}

