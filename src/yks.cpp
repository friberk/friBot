#include "yks.h"
#include <iostream>
#include <sstream>

using namespace std;

Yks::Yks(int diploma, /*bool kirikOBP*/ int ttd, int tsd, int tmd, int tfd,
         int tty, int tsy, int tmy, int tfy, int md, int fd, int kd, int bd,
         int my, int fy, int ky, int by) {
    try {
        const cpr::Response response =
            cpr::Post(cpr::Url{"http://puango.net/api/hesaplama.php"},
                      cpr::Payload{{"diploma", to_string(diploma)},
                                   {"kirikOBP", "true"},
                                   {"ttd", to_string(ttd)},
                                   {"tsd", to_string(tsd)},
                                   {"tmd", to_string(tmd)},
                                   {"tfd", to_string(tfd)},
                                   {"tty", to_string(tty)},
                                   {"tsy", to_string(tsy)},
                                   {"tmy", to_string(tmy)},
                                   {"tfy", to_string(tfy)},
                                   {"md", to_string(md)},
                                   {"fd", to_string(fd)},
                                   {"kd", to_string(kd)},
                                   {"bd", to_string(bd)},
                                   {"my", to_string(my)},
                                   {"fy", to_string(fy)},
                                   {"ky", to_string(ky)},
                                   {"by", to_string(by)}});

        apiResult = json::parse(response.text);

        //   std::string placementRanking;
        //   std::string pureRanking;
        //   std::string placementPoint;
        //   std::string purePoint;
        //   std::string TytPlacementRanking;
        //   std::string TytPureRanking;
        //   std::string TytPlacementPoint;
        //   std::string TytPurePoint;

        placementRanking = apiResult["yks_s_say_yer"].dump();
        pureRanking = apiResult["yks_s_say_ham"].dump();
        placementPoint = apiResult["yks_say_yer"].dump();
        purePoint = apiResult["yks_say_ham"].dump();
        TytPlacementRanking = apiResult["tyt_s_yer"].dump();
        TytPureRanking = apiResult["tyt_s_ham"].dump();
        TytPlacementPoint = apiResult["tyt_yer"].dump();
        TytPurePoint = apiResult["tyt_ham"].dump();

    } catch (const exception &e) {
        cerr << "Request failed, error: " << e.what() << endl;
    }
}

Yks::Yks(string str) {
    try {
        parseExamArgs(str);
        parseCourseArgs();

        for (int i = 0; i < courseArgs.size(); i++) {
            if (isNumeric(courseArgs.at(i)) == false) {
                problematic = true;
                break;
            }
        }

        // Definetly requires a *better* solution.
        if (stoi(courseArgs.at(0)) < 0 || stoi(courseArgs.at(0)) > 100 ||
            stoi(courseArgs.at(1)) < 0 || stoi(courseArgs.at(1)) > 40 ||
            stoi(courseArgs.at(2)) < 0 || stoi(courseArgs.at(2)) > 40 ||
            stoi(courseArgs.at(1)) + stoi(courseArgs.at(2)) > 40 ||
            stoi(courseArgs.at(3)) < 0 || stoi(courseArgs.at(3)) > 20 ||
            stoi(courseArgs.at(4)) < 0 || stoi(courseArgs.at(4)) > 20 ||
            stoi(courseArgs.at(3)) + stoi(courseArgs.at(4)) > 20 ||
            stoi(courseArgs.at(5)) < 0 || stoi(courseArgs.at(5)) > 40 ||
            stoi(courseArgs.at(6)) < 0 || stoi(courseArgs.at(6)) > 40 ||
            stoi(courseArgs.at(5)) + stoi(courseArgs.at(6)) > 40 ||
            stoi(courseArgs.at(7)) < 0 || stoi(courseArgs.at(7)) > 20 ||
            stoi(courseArgs.at(8)) < 0 || stoi(courseArgs.at(8)) > 20 ||
            stoi(courseArgs.at(7)) + stoi(courseArgs.at(8)) > 20 ||
            stoi(courseArgs.at(9)) < 0 || stoi(courseArgs.at(9)) > 40 ||
            stoi(courseArgs.at(10)) < 0 || stoi(courseArgs.at(10)) > 40 ||
            stoi(courseArgs.at(9)) + stoi(courseArgs.at(10)) > 40 ||
            stoi(courseArgs.at(11)) < 0 || stoi(courseArgs.at(11)) > 14 ||
            stoi(courseArgs.at(12)) < 0 || stoi(courseArgs.at(12)) > 14 ||
            stoi(courseArgs.at(11)) + stoi(courseArgs.at(12)) > 14 ||
            stoi(courseArgs.at(13)) < 0 || stoi(courseArgs.at(13)) > 13 ||
            stoi(courseArgs.at(14)) < 0 || stoi(courseArgs.at(14)) > 13 ||
            stoi(courseArgs.at(13)) + stoi(courseArgs.at(14)) > 13 ||
            stoi(courseArgs.at(15)) < 0 || stoi(courseArgs.at(15)) > 13 ||
            stoi(courseArgs.at(16)) < 0 || stoi(courseArgs.at(16)) > 13 ||
            stoi(courseArgs.at(15)) + stoi(courseArgs.at(16)) > 13) {
            problematic = true;
        }

        if (problematic != true) {
            const cpr::Response response =
                cpr::Post(cpr::Url{"http://puango.net/api/hesaplama.php"},
                          cpr::Payload{{"diploma", courseArgs.at(0)},
                                       {"kirikOBP", "true"},
                                       {"ttd", courseArgs.at(1)},
                                       {"tsd", courseArgs.at(3)},
                                       {"tmd", courseArgs.at(5)},
                                       {"tfd", courseArgs.at(7)},
                                       {"tty", courseArgs.at(2)},
                                       {"tsy", courseArgs.at(4)},
                                       {"tmy", courseArgs.at(6)},
                                       {"tfy", courseArgs.at(8)},
                                       {"md", courseArgs.at(9)},
                                       {"fd", courseArgs.at(11)},
                                       {"kd", courseArgs.at(13)},
                                       {"bd", courseArgs.at(15)},
                                       {"my", courseArgs.at(10)},
                                       {"fy", courseArgs.at(12)},
                                       {"ky", courseArgs.at(14)},
                                       {"by", courseArgs.at(16)}});

            apiResult = json::parse(response.text);

            placementRanking = apiResult["yks_s_say_yer"].dump();
            pureRanking = apiResult["yks_s_say_ham"].dump();
            placementPoint = apiResult["yks_say_yer"].dump();
            purePoint = apiResult["yks_say_ham"].dump();
            TytPlacementRanking = apiResult["tyt_s_yer"].dump();
            TytPureRanking = apiResult["tyt_s_ham"].dump();
            TytPlacementPoint = apiResult["tyt_yer"].dump();
            TytPurePoint = apiResult["tyt_ham"].dump();
        }

    } catch (const exception &e) {
        cerr << "Request failed, error: " << e.what() << endl;
    }
}

string Yks::getPlacementRanking() const { return placementRanking; }

string Yks::getPlacementRankingByYear(int year) const {
    if (year == 2020) {
        return placementRanking;
    }

    else if (year == 2019) {
        return apiResult["yks_s_say_yer_1"].dump();
    }

    else if (year == 2018) {
        return apiResult["yks_s_say_yer_2"].dump();
    }

    else {
        return "Invalid parameter.";
    }
}

string Yks::getPureRanking() const { return pureRanking; }

string Yks::getPureRankingByYear(int year) const {
    if (year == 2020) {
        return pureRanking;
    }

    else if (year == 2019) {
        return apiResult["yks_s_say_ham_1"].dump();
    }

    else if (year == 2018) {
        return apiResult["yks_s_say_ham_2"].dump();
    }

    else {
        return "Invalid parameter.";
    }
}

string Yks::getPlacementPoint() const { return placementPoint; }

string Yks::getPurePoint() const { return purePoint; }

string Yks::getTytPlacementRanking() const { return TytPlacementRanking; }

string Yks::getTytPlacementRankingByYear(int year) const {
    if (year == 2020) {
        return TytPlacementRanking;
    }

    else if (year == 2019) {
        return apiResult["tyt_s_yer_1"].dump();
    }

    else if (year == 2018) {
        return apiResult["tyt_s_yer_2"].dump();
    }

    else {
        return "Invalid parameter.";
    }
}

string Yks::getTytPureRanking() const { return TytPureRanking; }

string Yks::getTytPureRankingByYear(int year) const {
    if (year == 2020) {
        return TytPlacementRanking;
    }

    else if (year == 2019) {
        return apiResult["tyt_s_ham_1"].dump();
    }

    else if (year == 2018) {
        return apiResult["tyt_s_ham_2"].dump();
    }

    else {
        return "Invalid parameter.";
    }
}

string Yks::getTytPlacementPoint() const { return TytPlacementPoint; }

string Yks::getTytPurePoint() const { return TytPurePoint; }

bool Yks::isProblematic() { return problematic; }

bool Yks::isNumeric(const string &s) {
    auto result = double();
    auto i = istringstream(s);

    i >> result;

    return !i.fail() && i.eof();
}

void Yks::parseExamArgs(const string &s) {
    stringstream ss(s);
    string item;

    while (getline(ss, item, ' ')) {
        examArgs.push_back(item);
    }
}

void Yks::parseCourseArgs() {
    for (int i = 1; i < examArgs.size(); i++) {
        const string &s = examArgs.at(i);
        stringstream ss(s);
        string item;

        while (getline(ss, item, '?')) {
            courseArgs.push_back(item);
        }
    }
}
