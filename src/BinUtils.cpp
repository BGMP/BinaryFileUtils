////////////////////////////////////////////////////////////////////////////////
//
// BinaryFileUtils (Generic)
//
// Desc: BinUtils.cpp
// Binary Utils.
//
// 28/05/2025 (BGM)
// File inception.
//
////////////////////////////////////////////////////////////////////////////////

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

int ConvertTextToBinary(const char* input_file, const char* output_file);
int VerifyBinaryFile(const char* binary_file);
int GenerateRandomTXT(const char* output_file, int count, unsigned int min_val, unsigned int max_val);

////////////////////////////////////////////////////////////////////////////////
// Globals:
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Procedures:
////////////////////////////////////////////////////////////////////////////////

int ConvertTextToBinary(const char* input_file, const char* output_file) {
  FILE* input = fopen(input_file, "r");
  if (!input) {
    printf("Error: Cannot open input file '%s'\n", input_file);
    return 1;
  }

  FILE* output = fopen(output_file, "wb");
  if (!output) {
    printf("Error: Cannot create output file '%s'\n", output_file);
    fclose(input);
    return 1;
  }

  char line[256];
  int count = 0;
  unsigned int number;
  int line_number = 0;

  printf("Converting numbers from '%s' to binary format...\n", input_file);

  // Read each line from the text file
  while (fgets(line, sizeof(line), input)) {
    line_number++;

    // Skip empty lines
    if (line[0] == '\n' || line[0] == '\r') {
      continue;
    }

    // Convert string to unsigned integer
    if (sscanf(line, "%u", &number) == 1) {
      // Write the number in binary format
      if (fwrite(&number, sizeof(unsigned int), 1, output) != 1) {
        printf("Error: Failed to write number %u to output file\n", number);
        fclose(input);
        fclose(output);
        return 1;
      }
      count++;
      printf("  Line %d: %u\n", line_number, number);
    } else {
      printf("Warning: Line %d contains invalid number, skipping\n", line_number);
    }
  }

  fclose(input);
  fclose(output);

  printf("\nConversion complete!\n");
  printf("  Input file: %s\n", input_file);
  printf("  Output file: %s\n", output_file);
  printf("  Numbers converted: %d\n", count);
  printf("  Output size: %d bytes\n", count * (int)sizeof(unsigned int));

  return 0;
}

int VerifyBinaryFile(const char* binary_file) {
  FILE* f = fopen(binary_file, "rb");
  if (!f) {
    printf("Error: Cannot open binary file '%s'\n", binary_file);
    return 1;
  }

  // Get file size
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);

  long num_integers = size / sizeof(unsigned int);
  long remainder = size % sizeof(unsigned int);

  printf("Binary File Verification Report\n");
  printf("==============================\n");
  printf("File: %s\n", binary_file);
  printf("File size: %ld bytes\n", size);
  printf("Number of integers: %ld\n", num_integers);

  if (remainder != 0) {
    printf("Warning: File size is not a multiple of %zu bytes (incomplete integer at end)\n",
           sizeof(unsigned int));
  }

  if (num_integers == 0) {
    printf("File is empty or contains no complete integers.\n");
    fclose(f);
    return 0;
  }

  printf("\nContents:\n");
  printf("Index | Value\n");
  printf("------|----------\n");

  unsigned int number;
  int count = 0;

  while (fread(&number, sizeof(unsigned int), 1, f) == 1) {
    printf("%5d | %10u\n", count + 1, number);
    count++;

    // Limit output for very large files
    if (count >= 50) {
      long remaining = num_integers - count;
      if (remaining > 0) {
        printf("  ... (%ld more integers not shown)\n", remaining);
      }
      break;
    }
  }

  fclose(f);

  printf("\nVerification complete. File appears to be valid.\n");
  return 0;
}

int GenerateRandomTXT(const char* output_file, int count, unsigned int min_val, unsigned int max_val) {
  // Validate parameters
  if (count <= 0) {
    printf("Error: Count must be a positive number\n");
    return 1;
  }

  if (min_val > max_val) {
    printf("Error: Minimum value (%u) cannot be greater than maximum value (%u)\n", min_val, max_val);
    return 1;
  }

  FILE* output = fopen(output_file, "w");
  if (!output) {
    printf("Error: Cannot create output file '%s'\n", output_file);
    return 1;
  }

  // Initialize random seed
  srand((unsigned int)time(NULL));

  printf("Generating %d random numbers to '%s'...\n", count, output_file);
  printf("Range: %u to %u\n", min_val, max_val);

  unsigned int range = max_val - min_val + 1;

  // Generate and write random numbers
  for (int i = 0; i < count; i++) {
    unsigned int random_number;

    if (range == 1) {
      // Special case: min == max
      random_number = min_val;
    } else {
      // Generate random number in range [min_val, max_val]
      random_number = min_val + (rand() % range);
    }

    if (fprintf(output, "%u\n", random_number) < 0) {
      printf("Error: Failed to write number %u to output file\n", random_number);
      fclose(output);
      return 1;
    }

    if (count > 100 && (i + 1) % (count / 10) == 0) {
      printf("  Progress: %d/%d (%.1f%%)\n", i + 1, count, ((float)(i + 1) / count) * 100.0f);
    } else if (count <= 20) {
      printf("  Generated: %u\n", random_number);
    }
  }

  fclose(output);

  printf("\nGeneration complete!\n");
  printf("  Output file: %s\n", output_file);
  printf("  Numbers generated: %d\n", count);
  printf("  Range: %u to %u\n", min_val, max_val);

  return 0;
}
