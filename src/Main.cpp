////////////////////////////////////////////////////////////////////////////////
//
// BinaryFileUtils (Generic)
//
// Desc: Main.cpp
// Main program file.
//
// 28/05/2025 (BGM)
// File inception.
//
////////////////////////////////////////////////////////////////////////////////

#include "Main.h"
#include "BinUtils.h"

////////////////////////////////////////////////////////////////////////////////
// Macros:
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Types:
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prototypes:
////////////////////////////////////////////////////////////////////////////////

void print_usage(const char* program_name);
int main(int argc, char* argv[]);

////////////////////////////////////////////////////////////////////////////////
// Globals:
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Procedures:
////////////////////////////////////////////////////////////////////////////////

void print_usage(const char* program_name) {
  printf("Binary File Utilities v1.0\n");
  printf("Usage: %s <command> [arguments]\n\n", program_name);
  printf("Commands:\n");
  printf("  convert <input.txt> <output.bin>        - Convert text file to binary\n");
  printf("  verify <input.bin>                      - Verify and display binary file contents\n");
  printf("  generate <output.txt> <count> <min> <max> - Generate random numbers to text file\n");
  printf("  help                                    - Show this help message\n\n");
  printf("Examples:\n");
  printf("  %s convert numbers.txt data.bin\n", program_name);
  printf("  %s verify data.bin\n", program_name);
  printf("  %s generate random.txt 1000 1 100\n", program_name);
  printf("  %s generate test.txt 50 500 2000\n", program_name);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "help") == 0) {
    print_usage(argv[0]);
    return 0;
  }
  else if (strcmp(argv[1], "convert") == 0) {
    if (argc != 4) {
      printf("Error: convert command requires input and output file names\n");
      printf("Usage: %s convert <input.txt> <output.bin>\n", argv[0]);
      return 1;
    }
    return ConvertTextToBinary(argv[2], argv[3]);
  }
  else if (strcmp(argv[1], "verify") == 0) {
    if (argc != 3) {
      printf("Error: verify command requires input file name\n");
      printf("Usage: %s verify <input.bin>\n", argv[0]);
      return 1;
    }
    return VerifyBinaryFile(argv[2]);
  }
  else if (strcmp(argv[1], "generate") == 0) {
    if (argc != 6) {
      printf("Error: generate command requires output file, count, min, and max values\n");
      printf("Usage: %s generate <output.txt> <count> <min> <max>\n", argv[0]);
      printf("Example: %s generate random.txt 1000 1 100\n", argv[0]);
      return 1;
    }

    int count = atoi(argv[3]);
    unsigned int min_val = (unsigned int)atoi(argv[4]);
    unsigned int max_val = (unsigned int)atoi(argv[5]);

    if (count <= 0) {
      printf("Error: Count must be a positive integer\n");
      return 1;
    }

    return GenerateRandomTXT(argv[2], count, min_val, max_val);
  }
  else {
    printf("Error: Unknown command '%s'\n", argv[1]);
    print_usage(argv[0]);
    return 1;
  }
}
