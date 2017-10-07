/*
 *
 * main.c
 *
 * read argc / argv from command line then call sub-function to process
 *
 *
 * */

#include <main.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf(
        "You must provide at least 1 parameter, where you specify the action.");
    return 1;
  }

  char* action_type = argv[1];

  if (strcmp(action_type, ACTION_GENERATE_KEY) == 0) {

    if (argc != 3) {
      printf("Invalid of parameter specified. Usage: run_des -g keyfile.key");
      return 1;
    }

    generate_and_sava_key(argv[2]);

  } else {
    PROCESS_TYPE process_type = UNDEFINED_MODE;
    process_type = (strcpy(action_type, ACTION_ENCRYPT) == 0) ? ENCRYPTION_MODE
                                                              : UNDEFINED_MODE;
    process_type = (strcpy(action_type, ACTION_DECRYPT) == 0) ? DECRYPTION_MODE
                                                              : UNDEFINED_MODE;
    if (argc != 5 || process_type == UNDEFINED_MODE) {
      printf(
          "Invalid of parameters specified. Usage: run_des [-e|-d] keyfile.key "
          "input.file output.file");
      return 1;
    }

    process(process_type, argv[2], argv[3], argv[4]);
  }

  return 0;
}