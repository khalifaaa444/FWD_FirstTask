#include "server.h"
#include <string.h>
#include <stdio.h>
#include "card.h"
#include "terminal.h"
int referNumber = 0;
int testModeserv = 0;

ST_accountsDB_t accountsDB[255] = { {2000.0, RUNNING, "12345678912345678"} ,{200000.0, BLOCKED, "22345678912345672"},
									{3000.0, BLOCKED, "32345678912345673"} ,{400000.0, RUNNING, "42345678912345674"} ,
									{5000.0, RUNNING, "52345678912345675"} ,{600000.0, BLOCKED, "62345678912345676"} ,
									{8000.0, BLOCKED, "82345678912345678"} ,{800000.0, RUNNING, "82345678912345678"} ,
									{9000.0, RUNNING, "92345678912345679"} ,{100000.0, BLOCKED, "02345678912345670"} ,
};

ST_transaction transHistoryDB[255] = { 0 };


int newSequence = 0;


EN_transStat_t recieveTransactionData(ST_transaction* transData) {

	isValiderror = isValidAccount(&transData->cardHolderData, &accountsDB);
	isAmAvailableerror = isAmountAvailable(&transData->terminalData, &accountsDB);
	isBlockederror = isBlockedAccount(&accountsDB[referNumber]);

	//printf("server check 1 \n ");
	if (isValiderror == ACCOUNT_NOT_FOUND) {
		transData->transState = FRAUD_CARD;
		//printf("acc not found Fraud \n ");
		return FRAUD_CARD;
	}
	//printf("server check 2 \n ");
	else if (isAmAvailableerror == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if (isBlockederror == BLOCKED_ACCOUNT) {
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else {
		transData->transState = APPROVED;
	}

	/*save the new balance to the database*/
	float oldBalance = accountsDB[referNumber].balance;
	float newBalance = transData->terminalData.transAmount;
	float currentBalance = oldBalance - newBalance;
	accountsDB[referNumber].balance = currentBalance;
	/*Save the transaction details to the database and print transaction details*/
	saveTransactionerror = saveTransaction(transData);

	if (saveTransactionerror == SAVING_FAILED) {
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}

	return APPROVED;
}


void recieveTransactionDataTest(ST_transaction*  transData) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : recieveTransactionData \n");
	printf("Please enter the Expected Output according to last data wrong or ok:   ");
	//gets(&expectedVar);
	gets(&expectedVar);

	serverError=recieveTransactionData(&transData);
	printf("Test Case 1: \n");
	printf("Expected Result: %s\n",expectedVar);
	if (serverError == DECLINED_INSUFFECIENT_FUND) { 
		printf("Actual Result: wrong \n");
		printf("Not Pass test 1 \n");
	}
	else if (serverError == DECLINED_STOLEN_CARD) {
		printf("Pass test 1\n");
		printf("Actual Result: wrong \n");
		printf("Not Pass test 2 \n");
	}
	else if (serverError == FRAUD_CARD) {
		printf("Pass test 2\n");
		printf("Actual Result: wrong \n");
		printf("Not Pass test 3 \n");
	}
	else if (serverError == INTERNAL_SERVER_ERROR) { 
		printf("Pass test 3\n");
		printf("Actual Result: wrong \n");
		printf("Not Pass test 4 \n");
	}
	else {
		printf("Pass test 4\n");
		printf("Actual Result: ok \n");
	}

}


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	int x = 0;

	for (x = 0; x <= 255; x++) {
		int cmpCheck = strcmp(cardData->primaryAccountNumber, accountRefrence[x].primaryAccountNumber);
		if (cmpCheck == 0) {
			referNumber = x;
			//break;
			return SERVER_OK;
		}
	}
	return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : isValidAccount \n");
	printf("Please enter the Expected Output according to last data wrong or ok:   ");
	gets(expectedVar);
	serverError=isValidAccount(cardData,accountRefrence);
	printf("Expected Result: %s\n", expectedVar);

	if (serverError == ACCOUNT_NOT_FOUND) {
		printf("Actual Result :wrong \n");
	}
	else
	{
		printf("Actual Result :ok \n");
	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {

	if (accountRefrence[referNumber].state == RUNNING) {
		return SERVER_OK;
	}
	else if (accountRefrence[referNumber].state == BLOCKED) {
		return BLOCKED_ACCOUNT;
	}
	else { return ACCOUNT_NOT_FOUND; }
}

void isBlockedAccountTest(ST_accountsDB_t* accountRefrence){
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : isBlockedAccount \n");
	printf("Please enter the Expected Output according to last data wrong or ok:   ");
//	gets(&expectedVar);
	gets(&expectedVar);

	serverError = isBlockedAccount(&accountRefrence[referNumber]);
	printf("Expected Result: %s\n", expectedVar);

	if (serverError == BLOCKED_ACCOUNT || serverError == ACCOUNT_NOT_FOUND) {
		printf("Actual Result :wrong \n");
	}
	else
	{
		printf("Actual Result: ok\n");
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {

	if ((termData->transAmount) > (accountRefrence[referNumber].balance)) {
		return LOW_BALANCE;
	}
	else {
		return SERVER_OK;
	}
}

void isAmountAvailableTest(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : isAmountAvailable \n");
	printf("Please enter the Expected Output according to last data wrong or ok:   ");
//	gets(&expectedVar);
	gets(&expectedVar);

	serverError = isAmountAvailable(termData,accountRefrence);
	printf("Expected Result: %s\n", expectedVar);

	if (serverError == LOW_BALANCE) {
		printf("Actual Result :wrong \n");
	}
	else
	{
		printf("Actual Result: ok\n");
	}


}
EN_serverError_t saveTransaction(ST_transaction* transData) {
	
	newSequence++;
	transData->transactionSequenceNumber = newSequence;
	if (testModeserv==0) {
		listSavedTransactions(transData);
	}
	//Save the Card changes To the Database
	transHistoryDB[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
	//Save the terminal changes To the Database
	transHistoryDB[transData->transactionSequenceNumber].terminalData = transData->terminalData;
	//Save the state changes To the Database
	transHistoryDB[transData->transactionSequenceNumber].transState = transData->transState;
	//Save the sequence number of this transaction To the Database
	transHistoryDB[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;

	if (transData->transactionSequenceNumber >= 255) {
		return SAVING_FAILED;
	}
	else {
		return SERVER_OK;
	}
}

void saveTransactionTest(ST_transaction* transData) {
	char expectedVar[6];
	printf("Tester name : ebrahem mostafa ebrahem \n");
	printf("Function name : saveTransaction \n");
	printf("Please enter the Expected Output according to last data wrong or ok:   ");
	//gets(&expectedVar);
	gets(&expectedVar);
	testModeserv = 1;
	serverError = saveTransaction(transData);
	printf("Expected Result: %s\n", expectedVar);
	testModeserv = 0;
	if (serverError == SAVING_FAILED) {
		printf("Actual Result :wrong \n");
	}
	else
	{
		printf("Actual Result: ok\n");
	}

}

void listSavedTransactions(ST_transaction* transData) {
	printf("###############################\n");
	printf("Transaction Sequence Number: %d \n", transData->transactionSequenceNumber);
	printf("Transaction Date: %s \n", transData->terminalData.transactionDate);
	printf("Transaction Amount: %f \n", transData->terminalData.transAmount);
	if (transData->transState == RUNNING) {
		printf("Transaction State: RUNNING\n");
	}
	else {
		printf("Transaction State: BLOCKED\n");
	}
	printf("Transaction Max Amount: %f \n", transData->terminalData.maxTransAmount);
	printf("Card Holder Name: %s \n", transData->cardHolderData.cardHolderName);
	printf("PAN %s \n", transData->cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s \n", transData->cardHolderData.cardExpirationDate);
	printf("Your Current Balance: %f \n", accountsDB[referNumber].balance);
	printf("###############################\n");
}

EN_serverError_t isValiderror = SERVER_OK;
EN_serverError_t isBlockederror = SERVER_OK;
EN_serverError_t isAmAvailableerror = SERVER_OK;
EN_serverError_t  saveTransactionerror = SERVER_OK;