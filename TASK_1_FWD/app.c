
#include "terminal.h"
#include "card.h"
#include "server.h"
void appStart(void) {

	ST_terminalData_t customer;
	ST_cardData_t customer2;
	ST_transaction customer3;

	int testMode = 0;
	int tryagain = 0;
	int serverMaxFlag = 0;
	printf("For Testing Mode press 1: \n");
	scanf("%d", &testMode);
	//gets(&testMode);


	/*************************** Testing Card  Module ***************************/
	if (testMode == 1) {
		printf("Testing Mode Activated \n");

		//while (scanf("%d", &tryagain) == 1) {

		getCardHolderNameTest(&customer2);
		printf("\n");

		getCardPANTest(&customer2);
		printf("\n");

		getCardExpiryDateTest(&customer2);
		printf("\n");

		getTransactionDateTest(&customer);
		printf("\n");

		isCardExpriedTest(&customer2, &customer);

		printf("\n");

		getTransactionAmountTest(&customer);
		printf("\n");

		setMaxAmountTest(&customer);
		printf("\n");

		isBelowMaxAmountTest(&customer);
		printf("\n");

		
		isValidAccountTest(&customer3);
		printf("\n");

		isBlockedAccountTest(&customer3);
		printf("\n");

		isAmountAvailableTest(&customer);
		printf("\n");

		recieveTransactionDataTest(&customer3);
		printf("\n");

		saveTransactionTest(&customer3);
		printf("Thank You \n");

		//tryagain = 0;
	//}
	}


	else {
		/*************************** Get Card Holder Name ***************************/

		errorName = getCardHolderName(&customer2);
		while (errorName == WRONG_NAME) {   // or if
			printf("Name is not valid \n");
			errorName = getCardHolderName(&customer2);

			if (errorName == CARD_OK) {
				break;
			}
		}

		printf("NAME IS  valid \nHello Mr.%s\n", customer2.cardHolderName);

		/*************************** Get Card PAN Number ***************************/

		errorPan = getCardPAN(&customer2);
		while (errorPan == WRONG_PAN) {          //or if 
			printf("PAN be is not valid \n");
			errorPan = getCardPAN(&customer2);

			if (errorPan == CARD_OK) {
				break;
			}
		}
		printf("PAN is valid \n");

		/*************************** Get Card Expiry Date ***************************/
		errorDate = getCardExpiryDate(&customer2);
		while (errorDate == WRONG_EXP_DATE) {                // or if 
			printf("Expiry date IS not valid \n");
			errorDate = getCardExpiryDate(&customer2);
			if (errorDate == CARD_OK) {
				break;
			}
		}
		printf("expiry date IS  valid %s\n", customer2.cardExpirationDate);


		/*************************** Terminal  ***************************/

		if (getTransactionDate(&customer) == WRONG_DATE) {
			printf("Wrong Date Format\n");
		}
		else {
			printf("Date is %s \n", customer.transactionDate);
		}
		if (isCardExpired(&customer2, &customer) == EXPIRED_CARD) {
			printf("Card Is Expired \n");
			return 0;
		}
		else {
			printf("Card is Valid \n");
		}

		errorTransAmount = getTransactionAmount(&customer);
		if (errorTransAmount == INVALID_AMOUNT) { // while
			printf("NOT Valid Amount \n");
		}
		//	errorTransAmount = getTransactionAmount(&customer);
		else if (errorTransAmount == TERMINAL_OK) {
			//break;
			printf("Valid Amount \n");

		}
		//	}
		printf("Valid Amount \n");



		errorMaxAmount = setMaxAmount(&customer, 0);
		if (errorMaxAmount == INVALID_MAX_AMOUNT) { //while
			printf("NOT Valid Amount \n");
		}
		//errorMaxAmount = setMaxAmount(&customer, 0);
		else if (errorMaxAmount == TERMINAL_OK) {
			//break;
			//printf("Valid Amount \n");
		}
		//	}

		//printf("Valid Max  AMount \n");

		errorUnsuffecient = isBelowMaxAmount(&customer);
		if (isBelowMaxAmount(&customer) == EXCEED_MAX_AMOUNT) { //while
			printf("Exceed Max Amount \n");
			return 0;
		}
		//errorUnsuffecient = isBelowMaxAmount(&customer);
		else if (errorUnsuffecient == TERMINAL_OK) {
			//		break;
			printf("sufficient balance  \n");
		}

		/************************************  server  **********************************/

		customer3.cardHolderData = customer2;
		customer3.terminalData = customer;

		serverError = recieveTransactionData(&customer3);
		if (serverError == DECLINED_INSUFFECIENT_FUND) { printf("Insufficient Balance\n"); }
		else if (serverError == DECLINED_STOLEN_CARD) { printf("Stolen Card\n"); }
		else if (serverError == FRAUD_CARD) { printf("Fraud Card\n"); }
		else if (serverError == INTERNAL_SERVER_ERROR) { printf("Internal Server Error\n"); }
		else { printf("Approved\n"); }

	}
	return 0;
}
