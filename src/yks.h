#ifndef __YKS_H__
#define __YKS_H__

#include "../deps/json/single_include/nlohmann/json.hpp"
#include "../deps/sleepy-discord/deps/cpr/include/cpr/cpr.h"
#include <string>
#include <vector>

using json = nlohmann::json;

class Yks {
public:
    Yks(int diploma, /*bool kirikOBP*/ int ttd, int tmd, int tsd, int tfd,
        int tty, int tmy, int tsy, int tfy, int md, int fd, int kd, int bd,
        int my, int fy, int ky, int by);

    Yks(std::string str);

    // Math-Science methods
    std::string getPlacementRanking() const;
    std::string getPlacementRankingByYear(int year) const;
    std::string getPureRanking() const;
    std::string getPureRankingByYear(int year) const;
    std::string getPlacementPoint() const;
    std::string getPurePoint() const;

    // Only TYT
    std::string getTytPlacementRanking() const;
    std::string getTytPlacementRankingByYear(int year) const;
    std::string getTytPureRanking() const;
    std::string getTytPureRankingByYear(int year) const;
    std::string getTytPlacementPoint() const;
    std::string getTytPurePoint() const;

    // Low level stuff & some helper methods
    bool isProblematic();
    bool isNumeric(const std::string &s);
    void parseExamArgs(const std::string &s);
    void parseCourseArgs();

private:
    bool problematic;

    std::string placementRanking;
    std::string pureRanking;
    std::string placementPoint;
    std::string purePoint;
    std::string TytPlacementRanking;
    std::string TytPureRanking;
    std::string TytPlacementPoint;
    std::string TytPurePoint;

    json apiResult;

    std::vector<std::string> examArgs;
    std::vector<std::string> courseArgs;
};

#endif // __YKS_H__
