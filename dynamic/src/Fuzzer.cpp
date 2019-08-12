#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Utils.h"

/*
 * Implement your mutation algorithm. (Lab 4)
 */
std::string mutate(std::string &Origin) { return Origin; }

/*
 * Implement your feedback-directed seed update algorithm. (Lab 5)
 */
void updateSeedInputs() {}

int Freq = 1000;
int Count = 0;

void test(std::string &Target, std::string &Input, std::string &OutDir) {
  Count++;
  int ReturnCode = runTarget(Target, Input);
  switch (ReturnCode) {
  case 0:
    if (Count % Freq == 0)
      storePassingInput(Input, OutDir);
    break;
  case 256:
    fprintf(stderr, "%d crashes found\n", failureCount);
    storeCrashingInput(Input, OutDir);
    updateSeedInputs();
    break;
  case 127:
    fprintf(stderr, "%s not found\n", Target.c_str());
    exit(1);
  }
}

// ./fuzzer [exe file] [seed input dir] [output dir]
int main(int argc, char **argv) {
  if (argc != 4) {
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

  std::string Target(argv[1]);
  std::string SeedInputDir(argv[2]);
  std::string OutDir(argv[3]);

  initialize(OutDir);

  if (readSeedInputs(SeedInputDir)) {
    fprintf(stderr, "Cannot read seed input directory\n");
    return 1;
  }

  while (true) {
    for (auto I : SeedInputs) {
      std::string Input = mutate(I);
      test(Target, Input, OutDir);
    }
  }
  return 0;
}
