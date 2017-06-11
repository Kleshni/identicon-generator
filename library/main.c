#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "identicon.h"

static const char *outer_shapes[16] = {
	"6 12 12 0 12 12",
	"6 0 12 0 6 12 0 12",
	"6 0 12 0 12 12 6 12 12 6",
	"0 6 6 0 12 6 6 12 6 6",
	"0 6 12 0 12 12 0 12 12 6",
	"12 0 12 12 6 12 12 6 6 6",
	"0 0 12 0 12 6 0 0 6 12 0 12",
	"0 0 6 0 12 6 6 12 0 12 6 6",
	"6 0 6 6 12 6 12 12 6 12 6 6 0 6",
	"0 0 12 0 6 6 12 6 6 12 6 6 0 12",
	"0 6 6 12 12 6 6 0 12 0 12 12 0 12",
	"6 0 12 0 12 12 6 12 12 9 6 6 12 3",
	"0 6 6 0 6 6 12 0 12 6 6 12 6 6 0 12",
	"0 0 12 0 12 12 0 12 12 6 6 3 6 9 0 6 6 3",
	"0 6 6 6 6 0 12 0 6 6 12 6 6 12 6 6 0 12",
	"0 0 12 0 6 6 6 0 0 6 12 6 6 12 6 6 0 12"
};

static const char *central_shapes[7] = {
	"0 0 12 0 12 12 0 12",
	"6 0 12 6 6 12 0 6",
	"0 0 12 0 12 12 0 12 0 6 6 12 12 6 6 0 0 6",
	"3 0 9 0 6 6 12 3 12 9 6 6 9 12 3 12 6 6 0 9 0 3 6 6",
	"0 0 6 3 12 0 9 6 12 12 6 9 0 12 3 6",
	"4 4 8 4 8 8 4 8",
	"0 0 4 0 4 4 8 4 8 0 12 0 12 4 8 4 8 8 12 8 12 12 8 12 8 8 4 8 4 12 0 12 0 8 4 8 4 4 0 4"
};

static const char *rotations[4] = {
	"",
	" transform = \"rotate(90 6 6)\"",
	" transform = \"rotate(180 6 6)\"",
	" transform = \"rotate(270 6 6)\""
};

void identicon_create(char *result, const uint8_t *ID) {
	int corner_shape_type = ID[0] >> 4;
	int side_shape_type = ID[0] & 0x0f;
	int center_shape_type = ID[1] >> 4 & 0x07;

	int corner_rotation = ID[1] & 0x03;
	int side_rotation = ID[2] >> 4 & 0x03;

	int corner_colour_red = ID[3];
	int corner_colour_green = ID[4];
	int corner_colour_blue = ID[5];

	int side_colour_red = ID[6];
	int side_colour_green = ID[7];
	int side_colour_blue = ID[8];

	int center_colour_red;
	int center_colour_green;
	int center_colour_blue;

	if ((ID[2] & 0x01) == 1 && (
		abs(corner_colour_red - side_colour_red) > 127 ||
		abs(corner_colour_green - side_colour_green) > 127 ||
		abs(corner_colour_blue - side_colour_blue) > 127
	)) {
		center_colour_red = side_colour_red;
		center_colour_green = side_colour_green;
		center_colour_blue = side_colour_blue;
	} else {
		center_colour_red = corner_colour_red;
		center_colour_green = corner_colour_green;
		center_colour_blue = corner_colour_blue;
	}

	char *current_character = result;
	int written_characters_count;

	sprintf(current_character, "%s%s%s%02x%02x%02x%s%s%s%s%s%02x%02x%02x%s%s%s%n",
		(
			"<?xml version = \"1.0\" encoding = \"UTF-8\" standalone = \"no\"?>\n"
			"\n"
			"<svg xmlns = \"http://www.w3.org/2000/svg\" xmlns:xlink = \"http://www.w3.org/1999/xlink\" version = \"1.1\" viewBox = \"0 0 36 36\">\n"
			"\t<defs>\n"
			"\t\t<path id = \"corner\" d = \"M "
		),
		outer_shapes[corner_shape_type],
		" z\" fill = \"#",
		corner_colour_red,
		corner_colour_green,
		corner_colour_blue,
		"\"",
		rotations[corner_rotation],
		(
			" />\n"
			"\t\t<path id = \"side\" d = \"M "
		),
		outer_shapes[side_shape_type],
		" z\" fill = \"#",
		side_colour_red,
		side_colour_green,
		side_colour_blue,
		"\"",
		rotations[side_rotation],
		(
			" />\n"
			"\t</defs>\n"
			"\n"
			"\t<rect width = \"100%\" height = \"100%\" fill = \"white\" />\n"
			"\t<use xlink:href = \"#corner\" />\n"
			"\t<use xlink:href = \"#corner\" transform = \"translate(24 0) rotate(90 6 6)\" />\n"
			"\t<use xlink:href = \"#corner\" transform = \"translate(24 24) rotate(180 6 6)\" />\n"
			"\t<use xlink:href = \"#corner\" transform = \"translate(0 24) rotate(270 6 6)\" />\n"
			"\t<use xlink:href = \"#side\" transform = \"translate(12 0) rotate(90 6 6)\" />\n"
			"\t<use xlink:href = \"#side\" transform = \"translate(24 12) rotate(180 6 6)\" />\n"
			"\t<use xlink:href = \"#side\" transform = \"translate(12 24) rotate(270 6 6)\" />\n"
			"\t<use xlink:href = \"#side\" transform = \"translate(0 12)\" />\n"
		),
		&written_characters_count
	);

	current_character += written_characters_count;

	if (center_shape_type != 0) {
		sprintf(current_character, "%s%s%s%02x%02x%02x%s%n",
			"\t<path id = \"center\" d = \"M ",
			central_shapes[center_shape_type - 1],
			" z\" fill = \"#",
			center_colour_red,
			center_colour_green,
			center_colour_blue,
			"\" transform = \"translate(12 12)\" />\n",
			&written_characters_count
		);

		current_character += written_characters_count;
	}

	sprintf(current_character, "%s",
		"</svg>"
	);
}
