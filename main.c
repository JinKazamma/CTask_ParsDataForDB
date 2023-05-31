 #include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>

void hashing(const char* strForHash, size_t len, unsigned char hash[SHA256_DIGEST_LENGTH])
{
    SHA256((const unsigned char *)strForHash, len, hash);
}

int main() 
{
    const char* strForHash = "hello world";
    unsigned char hash[SHA256_DIGEST_LENGTH];
    hashing(strForHash,strlen(strForHash),hash);
    char hashStr[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(&hashStr[i * 2], "%02x", hash[i]);
    }

    printf("Hash value for '%s' is '%s'\n", strForHash, hashStr);
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "Testuser";
    const char *password = "13243546Aa@";
    const char* database = "Base4Test";

    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    else 
    printf("Entered in %s\n",database);


    char query[256];
    sprintf(query,"INSERT INTO HashTable (hash, string) VALUES ('%s','%s')",hashStr,strForHash);
    if (mysql_query(conn, query)) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    else 
    printf("Hash inserted successfully\n");

    mysql_close(conn);
    exit(0);




    return 0;
}