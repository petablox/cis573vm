#include <string>
#include <map>

enum Campaign { MutationA, MutationB, MutationC, NumCampaigns };

std::string mutate(std::string Origin, Campaign &FuzzCamp);

bool toCampaign(std::string Str, Campaign &FuzzCamp);
