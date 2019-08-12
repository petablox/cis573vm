#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <streambuf>
#include <string>
#include <sys/stat.h>

std::string readOneFile(std::string &Path) {
  std::ifstream SeedFile(Path);
  std::string Line((std::istreambuf_iterator<char>(SeedFile)),
                   std::istreambuf_iterator<char>());
  return Line;
}

int runTarget(std::string &Target, std::string &Input) {
  std::string Cmd = Target + " > /dev/null 2>&1";
  FILE *F = popen(Cmd.c_str(), "w");
  fprintf(F, "%s\n", Input.c_str());
  return pclose(F);
}

std::set<std::string> SeedInputs;

int readSeedInputs(std::string &SeedInputDir) {
  DIR *Directory;
  struct dirent *Ent;
  if ((Directory = opendir(SeedInputDir.c_str())) != NULL) {
    while ((Ent = readdir(Directory)) != NULL) {
      if (!(Ent->d_type == DT_REG))
        continue;
      std::string Path = SeedInputDir + "/" + std::string(Ent->d_name);
      std::string Line = readOneFile(Path);
      SeedInputs.insert(Line);
    }
    closedir(Directory);
    return 0;
  } else {
    return 1;
  }
}

int successCount = 1;
int failureCount = 1;

void initialize(std::string &OutDir) {
  int Status;
  std::string SuccessDir = OutDir + "/success";
  std::string FailureDir = OutDir + "/failure";
  mkdir(SuccessDir.c_str(), 0755);
  mkdir(FailureDir.c_str(), 0755);
}

void storePassingInput(std::string &Input, std::string &OutDir) {
  std::string Path = OutDir + "/success/input" + std::to_string(successCount++);
  std::ofstream OutFile(Path);
  OutFile << Input;
  OutFile.close();
}

void storeCrashingInput(std::string &Input, std::string &OutDir) {
  std::string Path = OutDir + "/failure/input" + std::to_string(failureCount++);
  std::ofstream OutFile(Path);
  OutFile << Input;
  OutFile.close();
}

std::set<std::string> SuccessLogs;
std::set<std::string> FailureLogs;
std::map<std::string, double> F;
std::map<std::string, double> S;
std::map<std::string, double> Failure;
std::map<std::string, double> Context;
std::map<std::string, double> Increase;

void printMap(std::map<std::string, double> &Map) {
  for (auto &Entry : Map) {
    std::cout << Entry.first << " : " << Entry.second << std::endl;
  }
}

void printReport() {
  std::cout << "== Failure(P) ==" << std::endl;
  printMap(Failure);
  std::cout << "== Context(P) ==" << std::endl;
  printMap(Context);
  std::cout << "== Increase(P) ==" << std::endl;
  printMap(Increase);
}

void generateLogFiles(std::string &Target, std::string &Scheme,
                      std::string &LogDir) {
  struct dirent *Ent;
  DIR *Directory;
  std::string SuccessDir = LogDir + "/success/";
  std::string FailureDir = LogDir + "/failure/";

  Directory = opendir(SuccessDir.c_str());
  if (Directory == NULL) {
    fprintf(stderr, "%s directory not found\n", SuccessDir.c_str());
    exit(1);
  }

  std::regex Reg("input[0-9]+");

  while ((Ent = readdir(Directory)) != NULL) {
    if (!(Ent->d_type == DT_REG))
      continue;
    std::string Input(Ent->d_name);
    if (std::regex_match(Input, Reg)) {
      runTarget(Target, Input);
      std::string LogFile = Target + ".cbi." + Scheme;
      std::string Dst = SuccessDir + "/" + Input + ".cbi." + Scheme;
      rename(LogFile.c_str(), Dst.c_str());
      SuccessLogs.insert(Dst);
    }
  }
  closedir(Directory);

  Directory = opendir(FailureDir.c_str());
  if (Directory == NULL) {
    fprintf(stderr, "%s directory not found\n", FailureDir.c_str());
    exit(1);
  }

  while ((Ent = readdir(Directory)) != NULL) {
    if (!(Ent->d_type == DT_REG))
      continue;
    std::string Input(Ent->d_name);
    if (std::regex_match(Input, Reg)) {
      runTarget(Target, Input);
      std::string LogFile = Target + ".cbi." + Scheme;
      std::string Dst = FailureDir + "/" + Input + ".cbi." + Scheme;
      rename(LogFile.c_str(), Dst.c_str());
      FailureLogs.insert(Dst);
    }
  }
  closedir(Directory);
}

