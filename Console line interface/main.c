#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include <identicon.h>

int main(int argc, char **argv) {
	if (argc != 2 || strlen(argv[1]) != IDENTICON_ID_LENGTH * 2) {
		fprintf(stderr, "%s: %s\n", argv[0], "Invalid command line arguments");

		return EXIT_FAILURE;
	}

	uint8_t ID[IDENTICON_ID_LENGTH];

	for (size_t i = 0; i < IDENTICON_ID_LENGTH * 2; ++i) {
		if (!isxdigit(argv[1][i])) {
			fprintf(stderr, "%s: %s\n", argv[0], "Invalid ID");

			return EXIT_FAILURE;
		}

		unsigned int digit;

		sscanf(argv[1] + i, "%1x", &digit);

		ID[i / 2] <<= 4;
		ID[i / 2] |= digit;
	}

	char identicon[IDENTICON_MAXIMUM_LENGTH];

	identicon_create(identicon, ID);

	puts(identicon);

	return EXIT_SUCCESS;
}
