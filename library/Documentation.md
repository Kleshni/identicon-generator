Identicon generator library 2.0.0
=================================

See the CLI [documentation](../tool/Documentation.md).

`identicon.h`
-------------

The main header file. Contains an include guard `IDENTICON_H`.

`identicon_create`
------------------

``` C
void identicon_create(char *result, const uint8_t *ID);
```

Creates an identicon from an ID.

Places the resulting SVG code with a null character into the `result` buffer, which must be at least `IDENTICON_MAXIMUM_LENGTH` bytes in size.

The ID must be an array of `IDENTICON_ID_LENGTH` bytes.
