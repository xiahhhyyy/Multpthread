//
// Created by Xhy_m on 2022/7/12.
//

#include "pthread.h"
#include "string"
#include "iostream"
#include "unistd.h"
#include "vector"
#include "algorithm"
#include "json/json.h"
#include "unordered_set"


using namespace std;

void helper(unordered_set<int> &setWeek, vector<vector<string>> &arrTime, const string &sPolicy)
{
    Json::Value jsonRoot;
    Json::Reader Reader;
    Json::FastWriter jsonWriter;

    Reader.parse(sPolicy, jsonRoot);

    if(jsonRoot.isMember("effective_period") && jsonRoot["effective_period"].isArray())
    {
        for(int i=0; i<jsonRoot["effective_period"].size(); ++i){
            if(jsonRoot["effective_period"][i].isInt()){
                setWeek.insert (jsonRoot["effective_period"][i].asInt());
            }
        }
    }

    if(jsonRoot.isMember("effective_time") && jsonRoot["effective_time"].isArray()){
        for(int i=0; i<jsonRoot["effective_time"].size(); ++i){
            if(jsonRoot["effective_time"][i].isArray()){
                vector<string> tmp;
                for(int j=0; j<jsonRoot["effective_time"][i].size(); ++j){
                    tmp.push_back(jsonRoot["effective_time"][i][j].asString());
                }
                arrTime.push_back(tmp);
            }
        }
    }
    sort(arrTime.begin(), arrTime.end());
}

bool test(const string &s)
{
    bool bRet = false;
    unordered_set<int> setWeek;
    vector<vector<string>>arrTime;
    helper(setWeek, arrTime, s);

    time_t timeCur = time(NULL);
    tm *tm = localtime(&timeCur);
    char tmp[32] = {0};
    snprintf(tmp, sizeof tmp, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    string sCurTime = tmp;
    cout << sCurTime << endl;

    for(int i=0; i<arrTime.size(); ++i){
        if(sCurTime >= arrTime[i][0] && sCurTime <= arrTime[i][1]){
            bRet = true;
            break;
        }
    }

    if(setWeek.count(tm->tm_wday) == 0){
        bRet = false;
    }
    return bRet;

}

int main(){

    string s = "{\"effective_period\": [0, 1, 2, 4, 5, 6],\"effective_time\": [[\"13:00:00\", \"16:14:00\"], [\"00:00:00\", \"08:00:00\"]]}";

    clock_t start = clock();
    test(s);
    clock_t end = clock();
    CLOCKS_PER_SEC;


    cout << end - start << endl;
    return 0;
}