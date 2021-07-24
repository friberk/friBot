#include "cloudinary_uploader.h"
#include "key_handler.h"
#include "sleepy_discord/sleepy_discord.h"
#include "yks.h"
#include <fstream>
#include <string>

class FribotClientClass : public SleepyDiscord::DiscordClient {
public:
    using SleepyDiscord::DiscordClient::DiscordClient;

    void onMessage(SleepyDiscord::Message message) override {
        if (message.channelID.number() == 838515196153823242) {
            deleteMessage(message.channelID, message.ID);
        }

        if (message.startsWith("fb?test")) {
            sendMessage(message.channelID,
                        "Hello " + message.author.username +
                            ", friBot is using C++ from now on.");
        }

        else if (message.startsWith("fb?yks")) {
            Yks yks(message.content);
            if (yks.isProblematic() != true) {
                sendMessage(message.channelID,
                            "Yerleştirme puanınız: " + yks.getPlacementPoint() +
                                ", 2020 YKS'ye göre SAY sıralamanız: " +
                                yks.getPlacementRanking() + "\n" +
                                "Ham puanınız: " + yks.getPurePoint() +
                                ", 2019 YKS'ye göre SAY sıralamanız: " +
                                yks.getPlacementRankingByYear(2019));
            } else {
                sendMessage(message.channelID,
                            "Hatalı parametre girdiniz. Lütfen diploma notu ve "
                            "doğru-yanlış "
                            "bilgilerinizi kontrol ediniz. Mesaj içeriğinde "
                            "gereksiz -fazla- "
                            "ögelerin olmamasına dikkat ediniz.");
            }
        }

        else if (message.startsWith("fb?up")) {
            CloudinaryUploader uploader(message.attachments.at(0));
            if (uploader.isProblematic() != true) {
                sendMessage(message.channelID,
                            "Your image ``" + uploader.getAttachmentFileName() +
                                "`` has been uploaded successfully, with "
                                "Public ID: ``" +
                                uploader.getUploadedImagePublicId() +
                                "`` and Signature: ``" +
                                uploader.getUploadedImageSignature() + "``\n<" +
                                uploader.getUploadedImageUrl() + ">");
            } else {
                sendMessage(
                    message.channelID,
                    "Upload failed. There may be a server-related problem or "
                    "you may have tried to upload an unsupported file type.");
            }
        }
    }

    void onReady(SleepyDiscord::Ready ready_data) override {
        updateStatus("berkcakar.dev 👋", 0, SleepyDiscord::online, false);
    }
};

int main() {
    std::ifstream keyFile{"api_keys.json"};
    KeyHandler keyHandler{keyFile};

    FribotClientClass client(keyHandler.getDiscordKey(),
                             SleepyDiscord::USER_CONTROLED_THREADS);
    client.setIntents(SleepyDiscord::Intent::SERVER_MESSAGES,
                      SleepyDiscord::Intent::SERVER_VOICE_STATES);
    client.run();
}
