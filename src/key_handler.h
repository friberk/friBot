#ifndef __KEY_HANDLER_H__
#define __KEY_HANDLER_H__

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

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