# MD5
MD5 algorithm implemented in C.

## Overview

The MD5 algorithm is a widely used hash function producing a 128-bit hash value. Although MD5 was initially designed to be used as a cryptographic hash function, it has been found to suffer from extensive vulnerabilities. It can still be used as a checksum to verify data integrity, but only against unintentional corruption.

## Compilation & Installation

1. Please Make sure you have C Language environment, for example `gcc` and `make`
2. Compilation using:
  ```
  make
  ```
  Then you can find the `md5` executable file in  folder.

## Usage

you can use it like this

```
./md5 file_name
```

## Reference

[RFC1321](https://www.ietf.org/rfc/rfc1321.txt)

[pod32g/MD5](https://github.com/pod32g/MD5)

[VinaLx/code-fragments/md5](https://github.com/VinaLx/code-fragments/tree/master/md5)