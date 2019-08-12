#include <cstdlib>
#include <string>
#include <unistd.h>

#include "Utils.h"

/*
 * Implement your CBI report generator. (Lab 9)
 */
void generateReport(std::string &Scheme) {}


// ./CBI [exe file] [scheme] [fuzzer output dir]
int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Invalid usage\n");
    return 1;
  }

  struct stat Buffer;
  if (stat(argv[1], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[1]);
    return 1;
  }

  if (stat(argv[3], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[2]);
    return 1;
  }

  std::string Scheme(argv[2]);
  if (Scheme != "branch" && Scheme != "return") {
    fprintf(stderr, "Invalid scheme\n");
    return 1;
  }

  std::string Target(argv[1]);
  std::string OutDir(argv[3]);

  generateLogFiles(Target, Scheme, OutDir);
  generateReport(Scheme);
  printReport();
  return 0;
}
