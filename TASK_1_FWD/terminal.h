#pragma once
#ifndef TERMINAL_H
#define TERMINAL_H

#include "card.h"
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void setMaxAmountTest(void);
void isBelowMaxAmountTest(void);

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    unsigned char transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional

EN_terminalError_t errorTransDate;
EN_terminalError_t errorTransAmount;
EN_terminalError_t errorMaxAmount;
EN_terminalError_t errorUnsuffecient;
EN_terminalError_t errorUnsuffecient;
EN_terminalError_t errorExpired;

#endif


