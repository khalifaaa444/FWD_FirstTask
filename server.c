#include "server.h"

void server_side_accounts_database (ST_accountsDB_t *acc,uint32_t SIZE)
{
    uint8_t arr[10][20]=
    {"2479485789034872",
    "2389504987364586",
    "3847586938284950",
    "1284950495865439",
    "4896098320958694",
    "2938409873258475",
    "29058743209586;99",
    "4675890324385768",
    "3875909879843285",
    "890543989543214"};
    EN_accountState_t arr2[10]={RUNNING,RUNNING,RUNNING,RUNNING,RUNNING,RUNNING,BLOCKED,BLOCKED,BLOCKED,BLOCKED};
    uint32_t count=0;
    for(count=0;count<SIZE;count++)
    {
        strcpy(acc->primaryAccountNumber,arr[count]);
        acc->balance = 2000 + count*200;
        acc->state = arr2[count];
        acc++;
    }
}

EN_transState_t recieveTransactionData(ST_transaction *transData)
{
    EN_transState_t ret = APPROVED;
    uint32_t i=0;
    if (NULL == transData)
    {
        ret=INTERNAL_SERVER_ERROR;
    }
    else
    {
    while (i==10)
    {
        uint8_t result=strcmp(transData->cardHolderData.primaryAccountNumber,accountsDB[i].primaryAccountNumber )
        if(result == 0)
        {
            if(transData->terminalData.transAmount <= accountsDB[i].balance)
            {
                if(accountsDB[i].state == BLOCKED)
                {
                    ret=DECLINED_STOLEN_CARD;
                }
                else
                {
                    ret = APPROVED;
                    accountsDB[i].balance = accountsDB[i].balance - transData->terminalData.transAmount ;
                }

            }
            else
            {
                ret = DECLINED_INSUFFECIENT_FUND;
            }

        }
        else
        {
            if(i<10)
            {
                i++;
            }
            else
            {
                ret=FRAUD_CARD;
            }

        }

    }
    }
    return ret;
}


EN_serverError_t saveTransaction(ST_transaction *transData)
{



}






