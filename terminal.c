#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{

    EN_terminalError_t ret = TERMINAL_OK;
    if (NULL==termData)
    {
        ret = WRONG_DATE;
    }
    else
    {
        printf("what's the transaction date(type it in this formula-> dd/mm/yyyy [ex: 03/05/2022] ):  ");
        gets(termData->transactionDate);
        if((strlen(termData->transactionDate)<10)||(termData->transactionDate[2]!='/')||(termData->transactionDate[5]!='/'))
        {
            ret = WRONG_DATE;
        }

    }




    return ret;

}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    EN_terminalError_t ret = TERMINAL_OK;
    if (NULL==termData)
    {
        ret = EXPIRED_CARD;
    }
    else
    {
        uint8_t convert_dates[3];
        uint32_t curr_year,curr_month,ex_year,ex_month;
        memcpy(convert_dates, cardData->cardExpirationDate+3,2);
        ex_year=atoi(convert_dates);
        memcpy(convert_dates, cardData->cardExpirationDate,2);
        ex_month=atoi(convert_dates);
        memcpy(convert_dates,termData->transactionDate+3,2);
        curr_month=atoi(convert_dates);
        memcpy(convert_dates, termData->transactionDate+8,2);
        curr_year=atoi(convert_dates);
        if (curr_year<ex_year)
        {
            ret = TERMINAL_OK;
        }
        else
        {
            if(curr_month<ex_month)
            {
                ret = TERMINAL_OK;
            }
            else
            {
                ret = EXPIRED_CARD;
            }

        }
    }
    return ret;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t ret = TERMINAL_OK;
    if (NULL==termData)
    {
        ret = INVALID_AMOUNT;
    }
    else
    {
        printf("Enter the transaction amount : ");
        scanf("%f",&(termData->transAmount));

        if(termData->transAmount<=0)
        {
            ret = INVALID_AMOUNT;
        }
    }
    return ret;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t ret = TERMINAL_OK;
    if (NULL==termData)
    {
        ret = EXCEED_MAX_AMOUNT;
    }
    else
    {
        if(termData->maxTransAmount < termData->transAmount)
        {
            ret = EXCEED_MAX_AMOUNT;
        }
    }

    return ret;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    EN_terminalError_t ret = TERMINAL_OK;
    if (NULL==termData)
    {
        ret = INVALID_MAX_AMOUNT;
    }
    else
    {
        printf("Enter max amount: ");
        scanf("%f",&(termData->maxTransAmount));
        if(termData->maxTransAmount<=0)
        {
            ret = INVALID_MAX_AMOUNT;
        }
    }
    return ret;
}

