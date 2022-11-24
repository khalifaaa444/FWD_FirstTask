
#include "terminal.h"
#include "card.h"
#include <stdio.h>
#define _CRT_sECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include<time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int numberProblemterm = 0;
int nullProblemterm = 0;
int testModesterm = 0;
int transProblemAmount = 0;
int maxProblemAmount = 0;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	char datearr[11];
	char monchar[11];
	char daychar[11];
	time_t my_time;
	struct tm* timeinfo;
	time(&my_time);
	timeinfo = localtime(&my_time);
	//printf("%s \n", asctime(timeinfo));
	itoa(timeinfo->tm_mday, datearr, 10);
	itoa(timeinfo->tm_mon + 1, monchar, 10);
	itoa(timeinfo->tm_year + 1900, daychar, 10);

	//itoa(timeinfo->tm_mday, daychar, 10);
	strcat(datearr, "/");
	strcat(datearr, monchar);
	strcpy(termData->transactionDate, datearr);
	printf("Today is %s\n", datearr);
	strcat(datearr, "/");
	strcat(datearr, daychar);
	printf("Today is %s\n", datearr);
	strcpy(termData->transactionDate, datearr);
	//*termData->transactionDate = datearr;

	int datelength = strlen(termData->transactionDate);
	if (datelength < 8) { numberProblemterm = 1; }
	if (termData->transactionDate == NULL) { nullProblemterm = 1; }

	if (termData->transactionDate == NULL || datelength < 8) {
		return WRONG_DATE;
	}
	else {

		return TERMINAL_OK;
	}
}
void getTransactionDateTest(ST_terminalData_t* termDatatest) {

	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : getTransactionDateTest \n");
	testModesterm = 1;
	printf("Test Case 1: Right Format or not ?\n");
	errorTransDate = getTransactionDate(termDatatest);
	printf("Expected Result: Today Date\n");
	if (errorTransDate == TERMINAL_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorTransDate == WRONG_DATE) {
		printf("Actual Result: wrong \n");
	}
	if (numberProblemterm == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		numberProblemterm = 0;
	}
	printf("Test Case 2: Null or not ?\n");


	if (nullProblemterm == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		numberProblemterm = 0;
	}

}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {

	printf("card data = %s \n", cardData->cardExpirationDate);
	int currentMonth = expdatetoint(termData->transactionDate, 1);
	int currentYear = expdatetoint(termData->transactionDate, 0);
	currentYear = currentYear - 2000;
	int expMonth = expdatetoint(cardData->cardExpirationDate, 2);
	int expYear = expdatetoint(cardData->cardExpirationDate, 1);
	//printf("current month = %d    current year = %d \n exp month  = %d   esp year = %d \n", currentMonth, currentYear, expMonth, expYear);


	if (expYear < currentYear || (expYear == currentYear && expMonth < currentMonth)) {

		return EXPIRED_CARD;
	}
	else
	{
		return TERMINAL_OK;
	}
}
void isCardExpriedTest(ST_terminalData_t* cardDatatest, ST_terminalData_t* termDatatest) {
	char expectedVar[6];
	printf("Tester name : Abdelrahman Mohamed Amir \n");
	printf("Function name : isCardExpriedTest \n");
	printf("Please enter the Expected Output wrong or ok: ");
	gets(&expectedVar);
	testModesterm = 1;
	printf("Test Case 1: Right Format or not ?\n");
	errorExpired = isCardExpired(cardDatatest, termDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorExpired == TERMINAL_OK) {
		printf("Actual Result: ok \n");
	}
	else {
		printf("Actual Result: wrong \n");
	}
	if (((errorExpired == TERMINAL_OK) && (strcmp(expectedVar, "ok") == 0)) || ((errorExpired == EXPIRED_CARD) && (strcmp(expectedVar, "wrong") == 0))) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass Test \n");
	}
	testModesterm = 0;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

	if (testModesterm == 0) {
		printf("Please enter your transaction amount ");
		scanf("%f", &termData->transAmount);
	}
	printf("transaction amount equal %f :\n", termData->transAmount);

	if (termData->transAmount <= 0) {
		transProblemAmount = 1;
		return INVALID_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}
void getTransactionAmountTest(ST_terminalData_t* termDatatest) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem  \n");
	printf("Function name : getTransactionAmount \n");
	printf("Please enter the Expected Output wrong or ok: ");
	//	gets(expectedVar);
	scanf("%s", &expectedVar);

	printf("Please enter your transaction amount ");
	scanf("%f", &termDatatest->transAmount);
	testModesterm = 1;
	printf("Test Case 1: Valid Amount or not ?\n");
	errorTransAmount = getTransactionAmount(termDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorTransAmount == TERMINAL_OK) {
		printf("Actual Result: ok \n");
	}
	else {
		printf("Actual Result: wrong \n");
	}
	if (transProblemAmount == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass Test \n");
		transProblemAmount = 0;
	}
	testModesterm = 0;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	if (testModesterm == 0) {
		printf("Please enter your max amount ");
		scanf("%f", &termData->maxTransAmount);
	}
	printf("Max transaction amount is %f \n ", termData->maxTransAmount);

	if (termData->maxTransAmount <= 0) {
		maxProblemAmount = 1;
		return INVALID_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}

}

void setMaxAmountTest(ST_terminalData_t* termDatatest) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem  \n");
	printf("Function name : setMaxAmountTest \n");
	printf("Please enter the Expected Output wrong or ok: ");
	gets(&expectedVar);
	gets(&expectedVar);

//	scanf("%s", &expectedVar);
	printf("Please enter your Max amount  ");
	scanf("%f", &termDatatest->maxTransAmount);
	//gets(termDatatest->maxTransAmount);
	testModesterm = 1;
	//printf("Please enter your Max amount  \n ");

	printf("Test Case 1: Max Amount is < or = zero ?\n");
	errorMaxAmount = setMaxAmount(termDatatest, 0);
	printf("Expected Result: %s\n", expectedVar);
	if (errorMaxAmount == TERMINAL_OK) {
		printf("Actual Result: ok \n");
	}
	else {
		printf("Actual Result: wrong \n");
	}
	if (maxProblemAmount == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass Test \n");
		maxProblemAmount = 0;
	}
	testModesterm = 0;

}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {

	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}
void isBelowMaxAmountTest(ST_terminalData_t* termDatatest) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem  \n");
	printf("Function name : isBelowMaxAmount \n");
	printf("Please enter the Expected Output wrong or ok: ");
	gets(&expectedVar);
	gets(&expectedVar);

	testModesterm = 1;
	printf("Test Case 1:Acceptacle transaction  or not ?\n");
	errorUnsuffecient = isBelowMaxAmount(termDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorUnsuffecient == TERMINAL_OK) {
		printf("Actual Result: ok \n");
	}
	else {
		printf("Actual Result: wrong \n");
	}
	if (((errorUnsuffecient == TERMINAL_OK) && (strcmp(expectedVar, "ok") == 0)) || ((errorUnsuffecient == EXCEED_MAX_AMOUNT) && (strcmp(expectedVar, "wrong") == 0))) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass Test \n");
	}
	testModesterm = 0;


}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	unsigned char panArray[4][20] = { "12345678912345678","12345678912345670","12345678912345671","12345678912345671" };
	int flag = 0;
	int i = 0;
	printf("Pan number is %s\n", &cardData->primaryAccountNumber);
	for (i = 0; i < 4; i++) {
		//print("%s\n", panArray +i);
		//printf("%d\n", strcmp(&cardData->primaryAccountNumber, panArray[i]));
		if (strcmp(&cardData->primaryAccountNumber, panArray[i]) == 0) {
			flag = 0;
			//printf(" equal \n");
			return CARD_OK;
			break;
		}
		else {
			//printf("are not equal \n");
		}
	}
	return INVALID_CARD;

}
EN_terminalError_t errorTransDate = TERMINAL_OK;
EN_terminalError_t errorTransAmount = TERMINAL_OK;
EN_terminalError_t errorMaxAmount = TERMINAL_OK;
EN_terminalError_t errorUnsuffecient = TERMINAL_OK;
EN_terminalError_t errorExpired = TERMINAL_OK;


