#include <stdio.h>
#include "card.h"
#define _CRT_sECURE_NO_WARNINGS
#pragma warning(disable:4996)
int notAlpha = 0;
int numberProblem = 0;
int alphaProblem = 0;
int nullProblem = 0;
int testModes = 0;
int notDigProblem = 0;
int formatProblem = 0;
int digitProblem = 0;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	int length = 0;
	if (testModes == 0) {
		printf("Enter name ");
		gets(cardData->cardHolderName);
	}
	printf("Input Data = %s\n", cardData->cardHolderName);
	length = strlen(&cardData->cardHolderName);
	printf("length =  %d\n", length);
	//check alphabetic or not 
	notAlpha = alphaORnot(cardData->cardHolderName);
	if (length < 20 || length >24) {
		numberProblem = 1;
	}
	if (notAlpha == 1) {
		alphaProblem = 1;
	}
	if (cardData->cardHolderName == NULL) {
		nullProblem = 1;
	}

	if (length < 20 || length > 24 || cardData->cardHolderName == NULL || notAlpha == 1)
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}
void getCardHolderNameTest(ST_cardData_t* cardDatatest) {
	char expectedVar[5];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : getCardHolderName \n");
	printf("Please enter the Expected Output wrong or ok:  ");
	gets(&expectedVar);

	gets(&expectedVar);
	//scanf(" %s",&expectedVar);
	printf("Enter name ");
	scanf("%[^\n]s",&cardDatatest->cardHolderName);
	//gets(cardDatatest->cardHolderName);
	testModes = 1;
	printf("Test Case 1: Alphabetic or not ?\n");
	errorName = getCardHolderName(cardDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorName == CARD_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorName == WRONG_NAME) {
		printf("Actual Result: wrong \n");
	}
	if (alphaProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		alphaProblem = 0;
	}

	printf("Test Case 2: Is Number Of Character is right ? \n");
	/*errorName = getCardHolderName(cardDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorName == CARD_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorName == WRONG_NAME) {
		printf("Actual Result: wrong \n");
	}
	*/
	if (numberProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		numberProblem == 0;
	}

	printf("Test Case 3: Is Name is null ? \n");
	/*errorName = getCardHolderName(cardDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorName == CARD_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorName == WRONG_NAME) {
		printf("Actual Result: wrong \n");
	}
	*/
	if (nullProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		nullProblem = 0;
	}
	testModes = 0;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	int panlength;
	int digitFlag = 0;
	if (testModes == 0) {
		printf("Enter pan ");
		scanf("%s", &cardData->primaryAccountNumber);
	}
	printf("the pan you enter = %s\n", cardData->primaryAccountNumber);
	panlength = strlen(cardData->primaryAccountNumber);
	printf("pan length =  %d\n", panlength);
	char* poi = &cardData->primaryAccountNumber;
	while (*poi) {
		if (isdigit(*poi++) == 0) {
			digitFlag = 1;
			break;
		}
	}
	if ((panlength > 20) || (panlength == 0) || (panlength < 16)) { numberProblem = 1; }
	if ((digitFlag == 1)) { digitProblem = 1; }
	if (cardData->cardHolderName == NULL) { nullProblem = 1; }

	if ((panlength > 20) || (panlength == 0) || (panlength < 16) || (digitFlag == 1) || (cardData->cardHolderName == NULL))
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}
}


void getCardPANTest(ST_cardData_t* cardDatatest) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : getCardPAN \n");
	printf("Please enter the Expected Output wrong or ok:   ");
	gets(&expectedVar);
	gets(&expectedVar);
	printf("Enter PAN:  ");
	gets(&cardDatatest->primaryAccountNumber);
	testModes = 1;
	printf("Test Case 1: All  digits or not ?\n");
	errorPan = getCardPAN(cardDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorName == CARD_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorName == WRONG_PAN) {
		printf("Actual Result: wrong \n");
	}

	printf("Test Case 2: Is Format is digits ? \n");

	if (digitProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		digitProblem = 0;
	}

	printf("Test Case 2: Is Number Of Character is right ? \n");
	/*errorName = getCardPAN(cardDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorName == CARD_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorName == WRONG_PAN) {
		printf("Actual Result: wrong \n");
	}
	*/
	if (numberProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		numberProblem == 0;
	}

	printf("Test Case 3: Is PAN is null ? \n");
	/*errorName = getCardPAN(cardDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorName == CARD_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorName == WRONG_PAN) {
		printf("Actual Result: wrong \n");
	}
	*/
	if (nullProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		nullProblem = 0;
	}
	testModes = 0;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int datelength;
	int monthNumber;
	int notDigit = 0;
	if (testModes == 0) {
		printf("Enter Expiry Date in the Form MM/YY : ");
		scanf("%s", &cardData->cardExpirationDate);
	}
	printf("the expiry date you enter is %s\n", cardData->cardExpirationDate);
	datelength = strlen(cardData->cardExpirationDate);
	notDigit = DigitCheck(cardData->cardExpirationDate);
	monthNumber = expdatetoint(cardData->cardExpirationDate, 2);
	if ((datelength > 5) || (datelength < 5)) { numberProblem = 1; }
	if ((cardData->cardExpirationDate == NULL)) { nullProblem == 1; }
	if ((cardData->cardExpirationDate[2] != '/') || (monthNumber > 12) || (monthNumber < 1)) { formatProblem = 1; }
	if (notDigit == 1) { digitProblem = 1; }

	if ((datelength > 5) || (datelength < 5) || (cardData->cardExpirationDate == NULL) || (cardData->cardExpirationDate[2] != '/') || (monthNumber > 12) || (monthNumber < 1) || (notDigit == 1)) {
		return WRONG_EXP_DATE;
	}
	else {
		return CARD_OK;
	}
}

void getCardExpiryDateTest(ST_cardData_t* cardDatatest) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : getCardExpiryDate \n");
	printf("Please enter the Expected Output wrong or ok:   ");
	gets(&expectedVar);
	//gets(&expectedVar);
	printf("Enter Exp Date in format mm/yy ");
	gets(cardDatatest->cardExpirationDate);
	testModes = 1;
	errorDate = getCardExpiryDate(cardDatatest);
	printf("Expected Result: %s\n", expectedVar);
	if (errorDate == CARD_OK) {
		printf("Actual Result: ok \n");
	}
	else if (errorDate == WRONG_EXP_DATE) {
		printf("Actual Result: wrong \n");
	}
	printf("Test Case 1: Format right or not ?\n");

	if (formatProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		formatProblem = 0;
	}

	printf("Test Case 2: Is the expiry data digits are right ? \n");

	if (digitProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		digitProblem = 0;
	}

	printf("Test Case 3: Is EXP date is null ? \n");

	if (nullProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		nullProblem == 0;
	}
	printf("Test Case 4: Is number of char entered is right ? \n");

	if (numberProblem == 0) {
		printf("Pass Test Successfly \n");
	}
	else {
		printf("Not Pass the test \n");
		numberProblem == 0;
	}
	testModes = 0;
}
int alphaORnot(unsigned char cardHolderName[]) {
	int l = 0;
	int notAlphas = 0;
	for (l = 0; cardHolderName[l] != '\0'; l++)
	{
		if (isalpha(cardHolderName[l]) == 0 && cardHolderName[l] != ' ') {
			notAlphas = 1;
			break;
		}
		else {
			notAlphas = 0;
		}
	}
	return notAlphas;
}
// Function to turn string number to int 
int expdatetoint(unsigned char* enterdate, int flags) {
	char* stringInput = enterdate, * point = stringInput;
	float arrays[10];
	int val = 0;
	while (*point) {
		if (isdigit(*point)) {
			val = strtol(point, &point, 10);
			if (flags == 2) { break; }
			flags++;
		}
		else { point++; }
	}
	return val;
}


// Function check if the entered value is number or not 

int DigitCheck(unsigned char cardExpirationDate[]) {
	int notDigits = 0;
	int r = 0;
	for (r = 0; cardExpirationDate[r] != '\0'; r++)
	{
		if (r != 2) {
			if (isdigit(cardExpirationDate[r]) == 0) {
				notDigits = 1;
				break;
			}
		}
	}
	return notDigits;
}
errorName = CARD_OK;
errorPan = CARD_OK;
errorDate = CARD_OK;

