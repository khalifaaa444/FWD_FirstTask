#include "card.h"




EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    EN_cardError_t ret = CARD_OK;
    if (NULL==cardData)
    {
        ret = WRONG_NAME;
    }
    else
    {
        printf("Enter your card holder name: ");
        gets(cardData->cardHolderName);
        if ((strlen(cardData->cardHolderName)<20)||(strlen(cardData->cardHolderName)>23))
        {
            ret = WRONG_NAME;
        }
    }

    return ret;

}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    EN_cardError_t ret=CARD_OK;
    if (NULL==cardData)
    {
        ret = WRONG_EXP_DATE;
    }
    else
    {

        printf("what's the card expiry date(type it in this formula-> mm/yy [ex: 05/22]  ):  ");
        gets(cardData->cardExpirationDate);
        if((strlen(cardData->cardExpirationDate)<5)||(strlen(cardData->cardExpirationDate)>5)||(cardData->cardExpirationDate[2]!='/'))
        {
            ret = WRONG_EXP_DATE;
        }

    }

    return ret;
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    EN_cardError_t ret=CARD_OK;

    if (NULL==cardData)
    {
        ret = WRONG_PAN;
    }
    else
    {
        printf("Enter your card pan: ");
        gets(cardData->primaryAccountNumber);

        if ((NULL == cardData)||(strlen(cardData->primaryAccountNumber)<16)||(strlen(cardData->primaryAccountNumber)>19))
        {
            ret = WRONG_PAN;
        }
    }
    return ret;
}
