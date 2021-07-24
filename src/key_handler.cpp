#include "key_handler.h"

using namespace std;

KeyHandler::KeyHandler(ifstream &ifile) {
    keys = json::parse(ifile);

    discordKey = keys["discord_key"];
    cloudinaryKey = keys["cloudinary_key"];
}

string KeyHandler::getDiscordKey() { return discordKey; }

string KeyHandler::getCloudinaryKey() { return cloudinaryKey; }
