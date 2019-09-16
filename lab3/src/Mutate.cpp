#include "Mutate.h"

#include <cstring>
#include <map>

std::map<std::string, Campaign> to_campaign = 
  {{"MutationA", MutationA}, {"MutationB", MutationB}, {"MutationC", MutationC}};

bool toCampaign(std::string Str, Campaign& FuzzCampaign) {
  auto I = to_campaign.find(Str);
  if (I == to_campaign.end()) {
    fprintf(stderr, "\"%s\" not a valid fuzz campaign, choice options are: ", Str.c_str());
    for (auto &I2 : to_campaign) {
      fprintf(stderr, "%s ", I2.first.c_str());
    }
    fprintf(stderr, "\n");
    return false;
  }
  FuzzCampaign = I->second;
  return true;
}

/*
 * Implement your mutation algorithms.
 */

std::string mutateA(std::string Origin) {
  return Origin;
}

std::string mutateB(std::string Origin) {
  return Origin;
}

std::string mutateC(std::string Origin) {
  return Origin;
}

std::string mutate(std::string Origin, Campaign& FuzzCampaign) {
  std::string Mutant;
  switch (FuzzCampaign) {
    case MutationA:
        return mutateA(Origin);
    case MutationB:
        return mutateB(Origin);
    case MutationC:
        return mutateC(Origin);
  }
}
