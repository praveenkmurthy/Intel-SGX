#include "Enclave2_t.h"
#include <stdlib.h>
#include "sgx_trts.h"

#include <string.h>
void foo(char *buf, size_t len)
{
	const char *secret = "Hello Enclave2!";
	char *str;
	//char *str2;
	/* Initial memory allocation */
   //str = (char *) malloc(0x5997000);
   //str = (char *) malloc(0x1000000);
   str = "HELLO ENCLAVE";
	if (len > strlen(str)) {
		memcpy(buf, str, strlen(str) + 1);
	}
}
