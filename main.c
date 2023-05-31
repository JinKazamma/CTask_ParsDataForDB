#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>
#define SIZE_OF_QUERY 1000

void hashing(const char* strForHash, size_t len, unsigned char hash[SHA256_DIGEST_LENGTH])
{
    SHA256((const unsigned char *)strForHash, len, hash);
}
void ConnectToSQL(MYSQL *mySQL)
{
    const char *server = "localhost";
    const char *user = "Testuser";
    const char *password = "13243546Aa@";
    const char *database = "Base4Test";

    if(!mysql_real_connect(mySQL,server,user,password,database,0,NULL,0))
    {
        fprintf(stderr, "%s\n", mysql_error(mySQL));
        mysql_close(mySQL);
        exit(1);
    }
    else 
    printf("Entered in %s\n",database);
}
void CheckQuery(MYSQL *mySQL, MYSQL_RES *res, char hashStr[SHA256_DIGEST_LENGTH * 2 + 1])
{
    char CheckQuery[SIZE_OF_QUERY];
    sprintf(CheckQuery, "SELECT hash FROM HashTable WHERE hash='%s'", hashStr);

    if(mysql_query(mySQL, CheckQuery))
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
            printf("Hash already exists in table\n");
            mysql_free_result(res);
            mysql_close(mySQL);
            exit(1);
        }
        mysql_free_result(res);
    }
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

    mysql_close(mySQL);
    exit(0);
}
int main() 
{
    char strForHash[SIZE_OF_QUERY];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    printf("Enter string for hashing: ");
    scanf("%s", strForHash);
    hashing(strForHash,strlen(strForHash),hash);
    char hashStr[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(&hashStr[i * 2], "%02x", hash[i]);
    }
    printf("Hash value for '%s' is '%s'\n", strForHash, hashStr);
    MYSQL *mySQL = mysql_init(NULL);
    MYSQL_RES *res;
    MYSQL_ROW row;
    ConnectToSQL(mySQL);
    CheckQuery(mySQL,res,hashStr);
    Query(mySQL,res,hashStr,strForHash);
    return 0;
}