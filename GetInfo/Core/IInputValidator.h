#pragma once

#include "../Core/Items/SearchParameters.h"

class IInputValidator

{
public:
    virtual ~IInputValidator(){}

    virtual bool isValidData(QString& inputText, int minimumLength) = 0;
    virtual QString getErrorMessage() = 0;

public slots:
    virtual void validateText(QString &text) = 0;
};

