#ifndef DATAGATHER_H
#define DATAGATHER_H

//Anthony Scaglione
//
//this file includes all the functions necessary to pull raw data from the league of legends API
//and then sort them into the correct files

#include <iostream>
#include <jsonfmcpp/nlohmann_json.hpp>
#include <fstream>
#include <string>
#include <chrono>
#include <windows.h>
#include <vector>
#include <sstream>
#include <dirent.h>
#include <curl/curl.h>

//define rate limit to protect against 403 error
int RATE = 1.3 * 1000;
//key for accessing API
std::string KEY = "RGAPI-40d6fff4-cc4c-467b-8c06-96ac90878ae4";

using json = nlohmann::json;

void getMasterPlayerIDs();
void getSeedPlayers();
void callAPI(std::string, std::string);
std::string IntToString(int);
void getMatchData();
void createBlank();
void parseRawData();

//this function takes in raw match data and sorts it, then averages it out in the champMatchStats.json file
void parseRawData(){
    json champions;
    std::ifstream i("./data/champion/champMatchStats.json");
    i >> champions;//holds the overall champ data
    json matches;//holds the current match file
    int champion;//holds current champion of player
    for(int n = 1; n <= 1000; ++n){
        std::cout << n << std::endl;
        std::ifstream j("./data/raw/matches/matches" + IntToString(n) + ".json");
        if(!j)
            break; //makes sure file exists, if it doesnt it breaks the loop
        j >> matches;
        for(int m = 0; m < 100; ++m){ //file will always contain 100 matches
            for(int p = 0; p < 10; ++p){ //always 10 players per match
                champion = matches["matches"][m]["participants"][p]["championId"];
                //increase total games for champion
                champions[IntToString(champion)]["matchStats"]["gameTotal"] = champions[IntToString(champion)]["matchStats"]["gameTotal"].get<int>() + 1;
                //handle total wins and losses
                if(matches["matches"][m]["participants"][p]["stats"]["winner"]){
                    champions[IntToString(champion)]["matchStats"]["cumulative"]["wins"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["wins"].get<int>() + 1;
                }else{
                    champions[IntToString(champion)]["matchStats"]["cumulative"]["losses"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["losses"].get<int>() + 1;
                }
                //calculate cumulative stats for each champion
                champions[IntToString(champion)]["matchStats"]["cumulative"]["assists"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["assists"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["assists"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["crowdcontroldealt"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["crowdcontroldealt"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["totalTimeCrowdControlDealt"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["deaths"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["deaths"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["deaths"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["doublekills"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["doublekills"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["doubleKills"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["goldearned"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["goldearned"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["goldEarned"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["goldspent"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["goldspent"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["goldSpent"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["healingdone"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["healingdone"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["totalHeal"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["kills"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["kills"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["kills"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["largestcriticalstrike"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["largestcriticalstrike"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["largestCriticalStrike"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["magicdamagedealt"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["magicdamagedealt"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["magicDamageDealt"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["magicdamagedealttochamps"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["magicdamagedealttochamps"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["magicDamageDealtToChampions"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["magicdamagetaken"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["magicdamagetaken"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["magicDamageTaken"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["minionkills"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["minionkills"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["minionsKilled"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["pentakills"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["pentakills"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["pentaKills"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["physicaldamagedealt"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["physicaldamagedealt"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["physicalDamageDealt"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["physicaldamagedealttochamps"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["physicaldamagedealttochamps"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["physicalDamageDealtToChampions"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["physicaldamagetaken"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["physicaldamagetaken"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["physicalDamageTaken"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["quadrakills"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["quadrakills"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["quadraKills"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["totaldamagedealt"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["totaldamagedealt"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["totalDamageDealt"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["totaldamagetochamps"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["totaldamagetochamps"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["totalDamageDealtToChampions"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["towerkills"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["towerkills"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["towerKills"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["triplekills"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["triplekills"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["tripleKills"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["truedamagedealt"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["truedamagedealt"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["trueDamageDealt"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["truedamagedealttochamps"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["truedamagedealttochamps"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["trueDamageDealtToChampions"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["truedamagetaken"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["truedamagetaken"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["trueDamageTaken"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["wardsplaced"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["wardsplaced"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["wardsPlaced"].get<int>();
                champions[IntToString(champion)]["matchStats"]["cumulative"]["wardskilled"] = champions[IntToString(champion)]["matchStats"]["cumulative"]["wardskilled"].get<int>() + matches["matches"][m]["participants"][p]["stats"]["wardsKilled"].get<int>();
            }
        //handle the six bans per match
        for(int i = 0; i <= 1; ++i){
            for(int j = 0; j <= 2; ++j){
                champions[IntToString(matches["matches"][m]["teams"][i]["bans"][j]["championId"].get<int>())]["matchStats"]["cumulative"]["bans"] =
                    champions[IntToString(matches["matches"][m]["teams"][i]["bans"][j]["championId"].get<int>())]["matchStats"]["cumulative"]["bans"].get<int>() + 1;
            }
        }
        }
    }

    //calculate average stats for each champion
    for (json::iterator it = champions.begin(); it != champions.end(); ++it) {
        champions[it.key()]["matchStats"]["average"]["assists"] = champions[it.key()]["matchStats"]["cumulative"]["assists"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["crowdcontroldealt"] = champions[it.key()]["matchStats"]["cumulative"]["crowdcontroldealt"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["deaths"] = champions[it.key()]["matchStats"]["cumulative"]["deaths"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["doublekills"] = champions[it.key()]["matchStats"]["cumulative"]["doublekills"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["goldearned"] = champions[it.key()]["matchStats"]["cumulative"]["goldearned"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["goldspent"] = champions[it.key()]["matchStats"]["cumulative"]["goldspent"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["healingdone"] = champions[it.key()]["matchStats"]["cumulative"]["healingdone"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["kills"] = champions[it.key()]["matchStats"]["cumulative"]["kills"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["largestcriticalstrike"] = champions[it.key()]["matchStats"]["cumulative"]["largestcriticalstrike"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["magicdamagedealt"] = champions[it.key()]["matchStats"]["cumulative"]["magicdamagedealt"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["magicdamagedealttochamps"] = champions[it.key()]["matchStats"]["cumulative"]["magicdamagedealttochamps"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["magicdamagetaken"] = champions[it.key()]["matchStats"]["cumulative"]["magicdamagetaken"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["minionkills"] = champions[it.key()]["matchStats"]["cumulative"]["minionkills"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["pentakills"] = champions[it.key()]["matchStats"]["cumulative"]["pentakills"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["physicaldamagedealt"] = champions[it.key()]["matchStats"]["cumulative"]["physicaldamagedealt"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["physicaldamagedealttochamps"] = champions[it.key()]["matchStats"]["cumulative"]["physicaldamagedealttochamps"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["physicaldamagetaken"] = champions[it.key()]["matchStats"]["cumulative"]["physicaldamagetaken"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["quadrakills"] = champions[it.key()]["matchStats"]["cumulative"]["quadrakills"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["totaldamagedealt"] = champions[it.key()]["matchStats"]["cumulative"]["totaldamagedealt"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["totaldamagetochamps"] = champions[it.key()]["matchStats"]["cumulative"]["totaldamagetochamps"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["towerkills"] = champions[it.key()]["matchStats"]["cumulative"]["towerkills"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["triplekills"] = champions[it.key()]["matchStats"]["cumulative"]["triplekills"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["truedamagedealt"] = champions[it.key()]["matchStats"]["cumulative"]["truedamagedealt"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["truedamagedealttochamps"] = champions[it.key()]["matchStats"]["cumulative"]["truedamagedealttochamps"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["truedamagetaken"] = champions[it.key()]["matchStats"]["cumulative"]["truedamagetaken"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["wardsplaced"] = champions[it.key()]["matchStats"]["cumulative"]["wardsplaced"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["wardskilled"] = champions[it.key()]["matchStats"]["cumulative"]["wardskilled"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["winrate"] = champions[it.key()]["matchStats"]["cumulative"]["wins"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();
        champions[it.key()]["matchStats"]["average"]["banrate"] = champions[it.key()]["matchStats"]["cumulative"]["bans"].get<int>() / (double)champions[it.key()]["matchStats"]["gameTotal"].get<int>();

    }
    std::ofstream o("./data/champion/champMatchStats.json");
    o << std::setw(4) << champions << std::endl;
}

//this function creates a blank champMatchStats.json file to add data to. Essentially a
//modification of the champInGameStats.json file but with the stats object addeed
void createBlank(){
    json champions;
    std::ifstream i("./data/champion/champInGameStats.json");
    json stats;
    i >> stats;
    for (json::iterator it = stats["data"].begin(); it != stats["data"].end(); ++it){
        champions[it.key()] = it.value();
        champions[it.key()]["matchStats"]["gameTotal"] = 0;
        champions[it.key()]["matchStats"]["average"]["winrate"] = 0;
        champions[it.key()]["matchStats"]["average"]["banrate"] = 0;
        champions[it.key()]["matchStats"]["average"]["kills"] = 0;
        champions[it.key()]["matchStats"]["average"]["deaths"] = 0;
        champions[it.key()]["matchStats"]["average"]["assists"] = 0;
        champions[it.key()]["matchStats"]["average"]["doublekills"] = 0;
        champions[it.key()]["matchStats"]["average"]["triplekills"] = 0;
        champions[it.key()]["matchStats"]["average"]["quadrakills"] = 0;
        champions[it.key()]["matchStats"]["average"]["pentakills"] = 0;
        champions[it.key()]["matchStats"]["average"]["minionkills"] = 0;
        champions[it.key()]["matchStats"]["average"]["totaldamagedealt"] = 0;
        champions[it.key()]["matchStats"]["average"]["totaldamagetochamps"] = 0;
        champions[it.key()]["matchStats"]["average"]["physicaldamagedealt"] = 0;
        champions[it.key()]["matchStats"]["average"]["physicaldamagedealttochamps"] = 0;
        champions[it.key()]["matchStats"]["average"]["magicdamagedealt"] = 0;
        champions[it.key()]["matchStats"]["average"]["magicdamagedealttochamps"] = 0;
        champions[it.key()]["matchStats"]["average"]["truedamagedealt"] = 0;
        champions[it.key()]["matchStats"]["average"]["truedamagedealttochamps"] = 0;
        champions[it.key()]["matchStats"]["average"]["physicaldamagetaken"] = 0;
        champions[it.key()]["matchStats"]["average"]["magicdamagetaken"] = 0;
        champions[it.key()]["matchStats"]["average"]["truedamagetaken"] = 0;
        champions[it.key()]["matchStats"]["average"]["healingdone"] = 0;
        champions[it.key()]["matchStats"]["average"]["crowdcontroldealt"] = 0;
        champions[it.key()]["matchStats"]["average"]["largestcriticalstrike"] = 0;
        champions[it.key()]["matchStats"]["average"]["firstbloodassist"] = 0;
        champions[it.key()]["matchStats"]["average"]["firstbloodkill"] = 0;
        champions[it.key()]["matchStats"]["average"]["firstinhibitorassist"] = 0;
        champions[it.key()]["matchStats"]["average"]["firstinhibitorkill"] = 0;
        champions[it.key()]["matchStats"]["average"]["firsttowerassist"] = 0;
        champions[it.key()]["matchStats"]["average"]["firsttowerkill"] = 0;
        champions[it.key()]["matchStats"]["average"]["goldearned"] = 0;
        champions[it.key()]["matchStats"]["average"]["goldspent"] = 0;
        champions[it.key()]["matchStats"]["average"]["towerkills"] = 0;
        champions[it.key()]["matchStats"]["average"]["wardskilled"] = 0;
        champions[it.key()]["matchStats"]["average"]["wardsplaced"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["wins"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["bans"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["losses"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["kills"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["deaths"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["assists"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["doublekills"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["triplekills"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["quadrakills"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["pentakills"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["minionkills"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["totaldamagedealt"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["totaldamagetochamps"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["physicaldamagedealt"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["physicaldamagedealttochamps"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["magicdamagedealt"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["magicdamagedealttochamps"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["truedamagedealt"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["truedamagedealttochamps"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["truedamagedealttochamps"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["physicaldamagetaken"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["magicdamagetaken"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["truedamagetaken"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["healingdone"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["crowdcontroldealt"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["largestcriticalstrike"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["firstbloodassist"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["firstbloodkill"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["firstinhibitorassist"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["firstinhibitorkill"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["firsttowerassist"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["firsttowerkill"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["goldearned"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["goldspent"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["towerkills"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["wardskilled"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["wardsplaced"] = 0;
        champions[it.key()]["matchStats"]["cumulative"]["damagetaken"] = 0;



    }
    std::ofstream o("./data/champion/champMatchStats.json");
    o << std::setw(4) << champions << std::endl;
}

//collects match data from the summoner IDs gathered with getSeedPlayers();
//always collects matches from the current time to three days ago
void getMatchData(){
    int tEnd = static_cast<int>(std::time(nullptr)) * 1000;
    int tStart = tEnd - 259200000;
    std::ifstream userIn("./data/raw/summoners/seedIDcopy.json");
    json users;
    userIn >> users;
    json rawMatchData;
    rawMatchData["matches"] = {};
    int matchJsonIndex = 0; //keeps track of where in the json object it goes
    int index = 1; //keeps track of what number to attach to the filename

    for(int j = 0; j < (int)users["ID"].size(); ++j){
        std::string URL = "https://na.api.riotgames.com/api/lol/NA/v2.2/matchlist/by-summoner/" + IntToString(users["ID"][j]) + "?endTime=" + IntToString(tEnd) + "^&rankedQueues=TEAM_BUILDER_RANKED_SOLO^&beginTime=" + IntToString(tStart) + "^&api_key=" + KEY;
        std::string output = "./data/raw/summoners/summMatchHistory.json";
        std::cout << "\nPulling down match history of summoner " << IntToString(users["ID"][j]) << "..." << std::endl;
        callAPI(URL, output);
        std::ifstream matchesIn(output);
        json matches;
        matchesIn >> matches;
        if(matches.count("status") == 0){
            for(int i = 0; i < (int)matches["matches"].size(); ++i){
                unsigned int matchId = matches["matches"][i]["matchId"];
                URL = "https://na.api.riotgames.com/api/lol/NA/v2.2/match/" + IntToString(matchId) + "?api_key=" + KEY;
                output = "./data/raw/summoners/tempMatch.json";
                std::cout << "\nPulling down match from summoner " << IntToString(users["ID"][j]) << std::endl;
                callAPI(URL, output);
                std::ifstream matchIn(output);
                json tempData;
                matchIn >> tempData;
                std::cout << "Put " << rawMatchData["matches"].size() << " matches into json object." << std::endl;
                if(tempData.count("status") == 0){
                    rawMatchData["matches"][matchJsonIndex] = tempData;
                    ++matchJsonIndex;
                    tempData.clear();
                    if(rawMatchData["matches"].size() == 100){
                        std::cout << "Adding 100 matches to match data json file..." << std::endl;
                        std::ofstream o("./data/raw/matches/matches" + IntToString(index) + ".json");
                        o << std::setw(4) << rawMatchData << std::endl;
                        ++index;
                        matchJsonIndex = 0;
                        rawMatchData["matches"].clear();
                    }
                }
            }
        }
    }
}

//pulls a list of player IDs based on a single summoner
void getSeedPlayers(){
    std::string initSeed = "43241041";
    std::vector<int> idNums;
    json seedsummoners;
    seedsummoners["ID"] = {};

    while(idNums.size() <= 10000){
        std::string URL = "https://na.api.riotgames.com/api/lol/NA/v2.2/matchlist/by-summoner/" + initSeed + "?endTime=1491847011000^&rankedQueues=TEAM_BUILDER_RANKED_SOLO^&beginTime=1491354424000^&api_key=" + KEY;
        std::string output = "./data/raw/summoners/summMatchHistory.json";
        std::cout << "\nPulling down match history of seed summoner " << initSeed << "..." << std::endl;
        callAPI(URL, output);
        std::ifstream in(output);
        json match;
        in >> match;
        if(match.count("status") == 0){//checks for validity. Status indicates failed file
            unsigned int matchId = match["matches"][rand()%(match["matches"].size())]["matchId"];
            //pull a random match from seed player to get the next batch
            URL = "https://na.api.riotgames.com/api/lol/NA/v2.2/match/" + IntToString(matchId) + "?api_key=" + KEY;
            output = "./data/raw/summoners/tempMatch.json";
            std::cout << "\nPulling down match from seed summoner..." << std::endl;
            callAPI(URL, output);
            std::ifstream i(output);
            json players;
            i >> players;
            if(players.count("status") == 0){//checks for validity. Status indicates failed file
                //push the IDs of the players in this game to a vector
                for(int i = 0; i < (int)players["participantIdentities"].size(); ++i){
                    idNums.push_back((players["participantIdentities"][i]["player"]["summonerId"]));
                }

                //checks if the last value is the same as the initial seed value so it does not loop
                if(IntToString(idNums[idNums.size()-1]) == initSeed)
                    idNums.pop_back();
            }
        }
        std::cout << "\nTotal players pulled (before duplicate removal): " << idNums.size() << std::endl;
        initSeed = IntToString(idNums.back());
    }
    //remove duplicates
    std::cout << "\nRemoving duplicates..." << std::endl;
    std::sort(idNums.begin(), idNums.end() );
    idNums.erase(unique(idNums.begin(), idNums.end() ), idNums.end());
    std::cout << "\nTotal players pulled: " << idNums.size() << std::endl;
    //push the values in the vector into the json object
    for(auto element : idNums){
        seedsummoners["ID"].push_back(element);
    }
    //pretty print json to file
    std::ofstream o("./data/raw/summoners/seedID2.json");
    o << std::setw(4) << seedsummoners << std::endl;
}

//gathers the summoner IDs from everyone in master tier. I will likely not use this
void getMasterPlayerIDs(){

    //request the master tier json from RIOT API
    std::string URL = "https://na.api.riotgames.com/api/lol/NA/v2.5/league/master?type=RANKED_SOLO_5x5^&api_key=" + KEY;
    std::string output = "./data/raw/summoners/master.json";
    callAPI(URL, output);
    std::ifstream i(output);
    json masters;
    i >> masters;

    std::ofstream x("./data/raw/summoners/prettymasterSeedId.json");
    x << std::setw(4) << masters << std::endl;

    //pull summoner IDs from master tier data
    json seedsummoners;
    seedsummoners["ID"] = {};
    int index = 0;
    for(auto p : masters["entries"]){
        seedsummoners["ID"][index] = p["playerOrTeamId"];
        ++index;
    }
    //std::cout << masters["entries"][1]["playerOrTeamId"] << std::endl;

    //add to the json file
    std::ofstream o("./data/raw/summoners/masterSeedId.json");
    o << std::setw(4) << seedsummoners << std::endl;
}

//system is hacky and bad but its the only thing that worked so ¯\_(ツ)_/¯
void callAPI(std::string url, std::string output){
    std::string sysIn = "curl " + url + " -o " + output;
    const char* sysInChar = sysIn.c_str();
    Sleep(RATE); // this is also hacky and bad but it works for now
    system(sysInChar);

}

//converts an int to a string. I know to_string exists but it kept giving me errors
//that I did not have time to resolve
std::string IntToString ( int number )
{
    char str[20];
    sprintf(str, "%u", number);
    return str;
}


#endif // DATAGATHER_H
