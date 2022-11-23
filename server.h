
#ifndef _SERVER_H_
#define _SERVER_H_
#include <string.h>
#include "std_types.h"
#include "card.h"
#include "terminal.h"

typedef enum EN_transState_t
{
     APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
     EN_transState_t transState;
     uint32_t transactionSequenceNumber;
}ST_transaction;

typedef enum EN_serverError_t
{
     SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
void server_side_accounts_database (ST_accountsDB_t *acc,uint32_t SIZE);
EN_transState_t recieveTransactionData(ST_transaction *transData);
//EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
//EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
//EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
//EN_serverError_t saveTransaction(ST_transaction *transData);
//void listSavedTransactions(void);

/////////////////////////////////////////////////////////////////////////
ST_accountsDB_t accountsDB[255];
ST_transaction DB_Test[255]={0};

/////////////////////////////////////////////////////////////////////////

#endif // _SERVER_H_
