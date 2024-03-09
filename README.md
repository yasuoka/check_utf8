Check UTF-8
===========


```c
int check_utf8(const char *str, size_t strlen);
```

`check_utf8()` checks whether the str is in valid UTF-8 sequence.
It returns a non-zero value if the str is a valid UTF8 otherwise it
returns 0.

Example:

```bash
$ cc -o check_utf8_test check_utf8_test.c check_utf8.c
$
$ ./check_utf8_test
check_utf8("ほげほげ", 12) == 1 ... ok
check_utf8("\x82\xd9\x82\xb0\x82\xd9\x82\xb0", 8) == 0 ... ok
check_utf8("©", 2) == 1 ... ok
check_utf8("\xF0\x9F\x98\xB7", 4) == 1 ... ok
check_utf8("ふがふが", 11) == 0 ... ok
$
```
