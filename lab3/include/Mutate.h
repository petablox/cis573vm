#include <string>

enum Campaign { MutationA, MutationB, MutationC };

std::string mutate(std::string Origin, Campaign &FuzzCamp);

bool toCampaign(std::string Str, Campaign &FuzzCampaign);
