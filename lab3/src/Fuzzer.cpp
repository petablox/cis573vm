#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Mutate.h"
#include "Utils.h"

int Freq = 1000000;
int Count = 0;

bool test(std::string &Target, std::string &Input, std::string &CampaignStr, std::string &OutDir) {
  Count++;
  int ReturnCode = runTarget(Target, Input);
  switch (ReturnCode) {
  case 0:
    if (Count % Freq == 0)
      storePassingInput(Input, CampaignStr, OutDir);
    return true;
  case 256:
    fprintf(stderr, "%d crashes found\n", failureCount);
    storeCrashingInput(Input, CampaignStr, OutDir);
    return false;
  case 127:
    fprintf(stderr, "%s not found\n", Target.c_str());
    exit(1);
  }
}

// ./fuzzer [exe file] [seed input dir] [output dir]
int main(int argc, char **argv) { 
  if (argc < 5) { 
    printf("usage %s [exe file] [seed input dir] [output dir] [campaign]\n", argv[0]);
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

  if (argc >= 6) {
    Freq = strtol(argv[5],NULL,10); 
  } 

  std::string Target(argv[1]);
  std::string SeedInputDir(argv[2]);
  std::string OutDir(argv[3]);

  std::string CampaignStr(argv[4]);
  Campaign FuzzCampaign;
  if (!toCampaign(CampaignStr, FuzzCampaign)) {
    return 1;
  }

  initialize(OutDir);

  if (readSeedInputs(SeedInputDir)) {
    fprintf(stderr, "Cannot read seed input directory\n");
    return 1;
  }

  while (true) {
    for (auto i = 0; i < SeedInputs.size(); i++) {
      auto I = SeedInputs[i];
      std::string Mutant = mutate(I, FuzzCampaign);
      test(Target, Mutant, CampaignStr, OutDir);
      SeedInputs.push_back(Mutant);
    }
  }
  return 0;
}
