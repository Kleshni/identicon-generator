Identicon generator library
===========================

See the CLI [documentation](../Console line interface/Documentation.md).

`identicon.h`
-------------

The main header file. Requires `stdint.h` to be already included.

`identicon_create`
------------------

``` C
void identicon_create(char *result, const uint8_t *ID);
```

Creates an identicon from the ID. Places the SVG code with a null character into the `result` buffer, which must be at least `IDENTICON_MAXIMUM_LENGTH` bytes in size.

The ID must be an array of `IDENTICON_ID_LENGTH` bytes.
