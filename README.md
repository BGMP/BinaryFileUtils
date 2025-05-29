Binary File Utilities
===

A command-line tool for converting text files containing integers to binary format and verifying binary files.

This project was built to prepare data for DACs (Directly Addressable Codes).

Features:
  - Convert: Transform text files (one integer per line) to binary format
  - Verify: Inspect and validate binary files, showing contents and statistics

### Usage
Create test data
```shell
echo -e "1\n2\n3\n4\n5" > test.txt
```

Convert and verify
```shell
./bin/Release/BinGenerator convert test.txt test.bin
./bin/Release/BinGenerator verify test.bin
```
