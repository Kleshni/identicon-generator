#ifndef IDENTICON_H
	#define IDENTICON_H

	#include <stdint.h>

	#define IDENTICON_MAXIMUM_LENGTH 1238
	#define IDENTICON_ID_LENGTH 9

	void identicon_create(char *result, const uint8_t *ID);
#endif
