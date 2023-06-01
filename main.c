#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>
#define QUERYSTRING_SIZE 51
#define SIZE_OF_STRING 500
#define SIZE_OF_QUERY SHA256_DIGEST_LENGTH*2+1+SIZE_OF_STRING+QUERYSTRING_SIZE

void hashing(const char* strForHash, size_t len, unsigned char hash[SHA256_DIGEST_LENGTH])
{
    SHA256((const unsigned char *)strForHash, len, hash);
}


void ConnectToSQL(MYSQL *mySQL)
{
    const char *const server = "localhost";
    const char *const user = "Testuser";
    const char *const password = "13243546Aa@";
    const char *const database = "Base4Test";

    if(!mysql_real_connect(mySQL,server,user,password,database,0,NULL,0))
    {
        fprintf(stderr, "%s\n", mysql_error(mySQL));
    }
    else 
    printf("Entered in %s\n",database);
}


bool CheckQuery(MYSQL *mySQL, MYSQL_RES *res, char hashStr[SHA256_DIGEST_LENGTH * 2 + 1])
{
    char StringCheckQuery[SIZE_OF_QUERY];
    sprintf(StringCheckQuery, "SELECT hash FROM HashTable WHERE hash='%s'", hashStr);

    if(mysql_query(mySQL, StringCheckQuery))
    {
        fprintf(stderr, "%s\n", mysql_error(mySQL));
        mysql_close(mySQL);
        exit(1);
    }
    res = mysql_store_result(mySQL);
    if(res)
    {
        unsigned int num_rows = mysql_num_rows(res);
        if(num_rows > 0)
        {
            mysql_free_result(res);
            return true;
        }
        else
        {
            mysql_free_result(res);
        }
    }
    return false;
}


void Query(MYSQL *mySQL, MYSQL_RES *res, char hashStr[SHA256_DIGEST_LENGTH * 2 + 1],char strForHash[SIZE_OF_QUERY])
{
    char query[SIZE_OF_QUERY];
    sprintf(query,"INSERT INTO HashTable (hash, string) VALUES ('%s','%s')",hashStr,strForHash);
    if (mysql_query(mySQL, query)) 
    {
        fprintf(stderr, "%s\n", mysql_error(mySQL));
        mysql_close(mySQL);
        exit(1);
    }
    else 
    printf("Hash inserted successfully\n");
}

int main() 
{
    char strForHash[SIZE_OF_STRING];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    MYSQL *mySQL = mysql_init(NULL);
    MYSQL_RES *res;
    ConnectToSQL(mySQL);
    while(true)
    {
        printf("Enter string for hashing: ");
        fgets(strForHash,sizeof(strForHash),stdin);
        strForHash[strcspn(strForHash, "\n")] = 0;
        hashing(strForHash,strlen(strForHash),hash);
        char hashStr[SHA256_DIGEST_LENGTH * 2 + 1];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) 
            {
                sprintf(&hashStr[i * 2], "%02x", hash[i]);
            }
        printf("Hash value for '%s' is '%s'\n", strForHash, hashStr);
    
        if(CheckQuery(mySQL,res,hashStr))
            {
                printf("Hash already exists in table\n");
            }
        else
            {
            Query(mySQL,res,hashStr,strForHash);
            }
    }
    return 0;
}