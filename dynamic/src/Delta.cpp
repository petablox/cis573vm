#include <iostream>

#include "Utils.h"

/*
 * Implement the delta-debugging algorithm. (Lab 10)
 */
std::string delta(std::string &Target, std::string &Input) { return Input; }

// ./delta [exe file] [crashing input file]
int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Invalid usage\n");
    return 1;
  }

  std::string Target(argv[1]);
  std::string InputFile(argv[2]);
  std::string Input = readOneFile(InputFile);
  if (!runTarget(Target, InputFile)) {
    fprintf(stderr, "Sanity check failed: the program does not crash with the "
                    "initial input\n");
    return 1;
  }

  std::string DeltaOutput = delta(Target, Input);

  std::string Path = InputFile + ".delta";
  std::ofstream OutFile(Path);
  OutFile << DeltaOutput;
  OutFile.close();

  return 0;
}
