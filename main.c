#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

void hashing(const char* strForHash, size_t len, unsigned char hash[SHA256_DIGEST_LENGTH])
{
    SHA256((const unsigned char *)strForHash, len, hash);
}

int main() 
{
    const char* strForHash = "hello world";
    unsigned char hash[SHA256_DIGEST_LENGTH];
    hashing(strForHash,strlen(strForHash),hash);
    printf("Hash: ");
    for(int i=0; i< SHA256_DIGEST_LENGTH; i++)
    { 
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;
}