#pragma once

#include "IInputValidator.h"

class InputValidator : public QObject
{
    Q_OBJECT
public:
    InputValidator();
    virtual ~InputValidator();

public:
    bool isValidData(const QString &inputText, int minimumLength);
    QString getErrorMessage();

public slots:
    void validateText(const QString &text);

signals:
    void showValidateError(const QString& text);
    void showNoValidateError();

private:
    bool isTooSmall(QString& inputText, int& minimumLength);
    bool hasIncorrectSymbols(QString& inputText);

private:
    QString errorMessage;
};
