//#include <cstdint>

#ifndef CARD_H
#define CARD_H

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

int expdatetoint(unsigned char* enterdate, int flags);

typedef struct ST_cardData_t
{
	unsigned char  cardHolderName[25];
	unsigned char primaryAccountNumber[20];
	unsigned char cardExpirationDate[6];

}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN

}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

EN_cardError_t errorName;
EN_cardError_t errorPan;
EN_cardError_t errorDate;


#endif	