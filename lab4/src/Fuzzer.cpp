#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "RefMutate.h"
#include "Mutate.h"
#include "Utils.h"

/*
 * Implement your feedback-directed seed update algorithm.
 */

void updateSeedInputs(std::string &Target, std::string &Mutated, bool Success) { }

int Freq = 1000000;
int Count = 0; 

bool test(std::string &Target, std::string &Input, std::string &OutDir) { 
  Count++;
  int ReturnCode = runTarget(Target, Input);
  switch (ReturnCode) {
  case 0:
    if (Count % Freq == 0)
      storePassingInput(Input, OutDir);
    return true;
  case 256:
    fprintf(stderr, "%d crashes found\n", failureCount);
    storeCrashingInput(Input, OutDir);
    return false;
  case 127:
    fprintf(stderr, "%s not found\n", Target.c_str());
    exit(1);
  }
}

// ./fuzzer [exe file] [seed input dir] [output dir]
int main(int argc, char **argv) {
  if (argc < 4) {
    printf("Invalid usage\n");
    return 1;
  }

  struct stat Buffer;
  if (stat(argv[1], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[1]);
    return 1;
  }

  if (stat(argv[2], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[2]);
    return 1;
  }

  if (stat(argv[3], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[3]);
    return 1;
  }

  if (argc >= 5) {
    Freq = strtol(argv[4],NULL,10); 
  } 

  std::string Target(argv[1]);
  std::string SeedInputDir(argv[2]);
  std::string OutDir(argv[3]);

  initialize(OutDir);

  if (readSeedInputs(SeedInputDir)) {
    fprintf(stderr, "Cannot read seed input directory\n");
    return 1;
  }

  while (true) {
    for (auto i = 0; i < SeedInputs.size(); i++) {
      auto I = SeedInputs[i];

      /* If you want to use your own muation function, change this line */
      std::vector<std::string> Mutants = refMutate(I);

      for (auto Mutant : Mutants) {
        bool Success = test(Target, Mutant, OutDir);
        updateSeedInputs(Target, Mutant, Success);
      }
    }
  }
  return 0;
}
