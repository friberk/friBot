#ifndef __KEY_HANDLER_H__
#define __KEY_HANDLER_H__

#include "../deps/json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

class KeyHandler {
public:
    KeyHandler(std::ifstream &ifile);
    std::string getDiscordKey();
    std::string getCloudinaryKey();

private:
    json keys;

    std::string discordKey;
    std::string cloudinaryKey;
};

#endif // __KEY_HANDLER_H__