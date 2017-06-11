Identicon generator 1.0.0
=========================

[Identicon](https://en.wikipedia.org/wiki/Identicon) generator.

It's compatible with the [Identicon5](https://github.com/FrancisShanahan/Identicon5) library with two exceptions: it doesn't understand the `"test"` ID and doesn't have the `rotate` option (behaving like it's set to `true`).

Usage
-----

```
identicon <ID>
```

Generates an identicon from an ID. Writes the SVG code to the standard output.

The ID must be a string of 18 hexadecimal digits.

It's easy to forge an identicon if the ID can be freely manipulated by the attacker. It's recommended to use output of a cryptographic hash function.
