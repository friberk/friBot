#ifndef __CLOUDINARY_UPLOADER_H__
#define __CLOUDINARY_UPLOADER_H__

#include <ctime>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "sleepy_discord/attachment.h"
#include "key_handler.h"

using json = nlohmann::json;

class CloudinaryUploader {
public:
    CloudinaryUploader(SleepyDiscord::Attachment attachment);
    void uploadHelper();
    void delImage(std::string public_id, std::string signature);
    int getEpochTimestamp();
    bool isProblematic();
    std::string getAttachmentFileName();
    std::string getAttachmentFileNameWithoutExt();
    std::string getUploadedImageUrl();
    std::string getUploadedImagePublicId();
    std::string getUploadedImageSignature();

private:
    bool problematic;

    std::string attachmentUrl;
    std::string attachmentFileName;
    std::string attachmentFileNameWithoutExt;
    std::string uploadedImageUrl;
    std::string uploadedImagePublicId;
    std::string uploadedImageSignature;
    int epochTimestamp;

    json apiResult;

    std::ifstream keyFile{"../api_keys.json"};
    KeyHandler keyHandler{keyFile};
};

#endif // __CLOUDINARY_UPLOADER_H__