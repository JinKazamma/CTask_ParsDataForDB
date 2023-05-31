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


    return 0;
}