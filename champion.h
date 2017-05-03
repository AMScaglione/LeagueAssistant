#ifndef CHAMPION_H
#define CHAMPION_H

#ifndef CHAMPION_H_INCLUDED
#define CHAMPION_H_INCLUDED

#include <jsonfmcpp/nlohmann_json.hpp>
#include <string>

class champion{
    private:
        json j;
        std::string IntToString(int);
        std::string DblToString(double);
    public:
        champion(std::string);
        std::string getBlurb(){
            return j["blurb"];
        }
        std::string getTitle(){
            return j["title"];
        }
        std::string getArmor(){
            return DblToString(j["stats"]["armor"]);
        }
        std::string getArmorPerLevel(){
            return DblToString(j["stats"]["armorperlevel"]);
        }
        std::string getAttackDamage(){
            return DblToString(j["stats"]["attackdamage"]);
        }
        std::string getAttackDamagePerLevel(){
            return DblToString(j["stats"]["attackdamageperlevel"]);
        }
        std::string getAttackRange(){
            return DblToString(j["stats"]["attackrange"]);
        }
        std::string getAttackSpeedOffset(){
            return DblToString(j["stats"]["attackspeedoffset"]);
        }
        std::string getAttackSpeedPerLevel(){
            return DblToString(j["stats"]["attackspeedperlevel"]);
        }
        std::string getHP(){
            return DblToString(j["stats"]["hp"]);
        }
        std::string getHPPerLevel(){
            return DblToString(j["stats"]["hpperlevel"]);
        }
        std::string getHPRegen(){
            return DblToString(j["stats"]["hpregen"]);
        }
        std::string getHPRegenPerLevel(){
            return DblToString(j["stats"]["hpregenperlevel"]);
        }
        std::string getMoveSpeed(){
            return DblToString(j["stats"]["movespeed"]);
        }
        std::string getMP(){
            return DblToString(j["stats"]["mp"]);
        }
        std::string getMPPerLevel(){
            return DblToString(j["stats"]["mpperlevel"]);
        }
        std::string getMPRegen(){
            return DblToString(j["stats"]["mpregen"]);
        }
        std::string getMPRegenPerLevel(){
            return DblToString(j["stats"]["mpregenperlevel"]);
        }
        std::string getSpellBlock(){
            return DblToString(j["stats"]["spellblock"]);
        }
        std::string getSpellBlockPerLevel(){
            return DblToString(j["stats"]["spellblockperlevel"]);
        }
        std::string getGameTotal(){
            return DblToString(j["matchStats"]["gameTotal"]);
        }
        std::string getAssists(){
            return DblToString(j["matchStats"]["average"]["assists"]);
        }
        std::string getBanRate(){
            return DblToString(j["matchStats"]["average"]["banrate"]);
        }
        std::string getCrowdControlDealt(){
            return DblToString(j["matchStats"]["average"]["crowdcontroldealt"]);
        }
        std::string getDeaths(){
            return DblToString(j["matchStats"]["average"]["deaths"]);
        }
        std::string getDoubleKills(){
            return DblToString(j["matchStats"]["average"]["doublekills"]);
        }
        std::string getGoldEarned(){
            return DblToString(j["matchStats"]["average"]["goldearned"]);
        }
        std::string getGoldSpent(){
            return DblToString(j["matchStats"]["average"]["goldspent"]);
        }
        std::string getHealingDone(){
            return DblToString(j["matchStats"]["average"]["healingdone"]);
        }
        std::string getKills(){
            return DblToString(j["matchStats"]["average"]["kills"]);
        }
        std::string getLargestCriticalStrike(){
            return DblToString(j["matchStats"]["average"]["largestcriticalstrike"]);
        }
        std::string getMagicDamageDealt(){
            return DblToString(j["matchStats"]["average"]["magicdamagedealt"]);
        }
        std::string getMagicDamageDealtToChamps(){
            return DblToString(j["matchStats"]["average"]["magicdamagedealttochamps"]);
        }
        std::string getMagicDamageTaken(){
            return DblToString(j["matchStats"]["average"]["magicdamagetaken"]);
        }
        std::string getMinionKills(){
            return DblToString(j["matchStats"]["average"]["minionkills"]);
        }
        std::string getPentaKills(){
            return DblToString(j["matchStats"]["average"]["pentakills"]);
        }
        std::string getPhysicalDamageDealt(){
            return DblToString(j["matchStats"]["average"]["physicaldamagedealt"]);
        }
        std::string getPhysicalDamageDealtToChamps(){
            return DblToString(j["matchStats"]["average"]["physicaldamagedealttochamps"]);
        }
        std::string getPhysicalDamageTaken(){
            return DblToString(j["matchStats"]["average"]["physicaldamagetaken"]);
        }
        std::string getQuadraKills(){
            return DblToString(j["matchStats"]["average"]["quadrakills"]);
        }
        std::string getTotalDamageDealt(){
            return DblToString(j["matchStats"]["average"]["totaldamagedealt"]);
        }
        std::string getTotalDamageDealtToChamps(){
            return DblToString(j["matchStats"]["average"]["totaldamagedealttochamps"]);
        }
        std::string getTowerKills(){
            return DblToString(j["matchStats"]["average"]["towerkills"]);
        }
        std::string getTripleKills(){
            return DblToString(j["matchStats"]["average"]["triplekills"]);
        }
        std::string getTrueDamageDealt(){
            return DblToString(j["matchStats"]["average"]["truedamagedealt"]);
        }
        std::string getTrueDamageDealtToChamps(){
            return DblToString(j["matchStats"]["average"]["truedamagedealttochamps"]);
        }
        std::string getTrueDamageTaken(){
            return DblToString(j["matchStats"]["average"]["truedamagetaken"]);
        }
        std::string getWardsKilled(){
            return DblToString(j["matchStats"]["average"]["wardskilled"]);
        }
        std::string getWardsPlaced(){
            return DblToString(j["matchStats"]["average"]["wardsplaced"]);
        }
        std::string getWinRate(){
            return DblToString(j["matchStats"]["average"]["winrate"].get<float>()*100);
        }
        std::string getPlayRate(){
            return DblToString((j["matchStats"]["gameTotal"].get<int>()/98500.0)*100);
        }



};

//constructor, pulls the correct data from json file
champion::champion(std::string name){
    std::ifstream i("./data/champion/champMatchStats.json");
    json stats;
    i >> stats;
    for (json::iterator it = stats.begin(); it != stats.end(); ++it) {
        json temp = it.value();
        if(temp["id"] == name)
            j = it.value();
    }
}

std::string champion::DblToString ( double number )
{
    std::ostringstream strs;
    strs << number;
    std::string str = strs.str();
    return str;
}

std::string champion::IntToString ( int number )
{
    char str[20];
    sprintf(str, "%u", number);
    return str;
}

#endif // CHAMPION_H_INCLUDED


#endif // CHAMPION_H
