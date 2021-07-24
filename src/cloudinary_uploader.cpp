#include "cloudinary_uploader.h"
#include <vector>

using namespace std;

CloudinaryUploader::CloudinaryUploader(SleepyDiscord::Attachment attachment) {
    attachmentUrl = attachment.url;
    attachmentFileName = attachment.filename;

    int lastindex = attachmentFileName.find_last_of(".");
    attachmentFileNameWithoutExt = attachmentFileName.substr(0, lastindex);

    epochTimestamp = getEpochTimestamp();
    uploadHelper();
}

void CloudinaryUploader::uploadHelper() {
    try {
        cpr::Response response = cpr::Post(
            cpr::Url{"https://api.cloudinary.com/v1_1/fribot/image/upload"},
            cpr::Payload{{"file", attachmentUrl},
                         {"timestamp", to_string(epochTimestamp)},
                         {"public_id", attachmentFileNameWithoutExt},
                         {"api_key", keyHandler.getCloudinaryKey()},
                         {"upload_preset", "yqjhng4z"}});

        apiResult = json::parse(response.text);

        if (apiResult["signature"].is_null() ||
            apiResult["signature"].empty()) {
            problematic = true;
        } else {
            uploadedImageUrl = apiResult["secure_url"];
            uploadedImagePublicId = apiResult["public_id"];
            uploadedImageSignature = apiResult["signature"];

            cout << apiResult.dump(4) << endl;
        }
    } catch (const exception &e) {
        cerr << "Request failed, error: " << e.what() << endl;
    }
}

void CloudinaryUploader::delImage(string public_id, string signature) {
    try {
        cpr::Response response = cpr::Post(
            cpr::Url{"https://api.cloudinary.com/v1_1/fribot/image/destroy"},
            cpr::Payload{{"api_key", keyHandler.getCloudinaryKey()},
                         {"invalidate", "true"},
                         {"timestamp", to_string(epochTimestamp)},
                         {"public_id", public_id},
                         {"signature", signature}});
    } catch (const exception &e) {
        cerr << "Request failed, error: " << e.what() << endl;
    }
}

int CloudinaryUploader::getEpochTimestamp() {
    time_t t = time(0);
    return t;
}

bool CloudinaryUploader::isProblematic() { return problematic; }

string CloudinaryUploader::getUploadedImageUrl() { return uploadedImageUrl; }

string CloudinaryUploader::getAttachmentFileName() {
    return attachmentFileName;
}

string CloudinaryUploader::getAttachmentFileNameWithoutExt() {
    return attachmentFileNameWithoutExt;
}

string CloudinaryUploader::getUploadedImagePublicId() {
    return uploadedImagePublicId;
}

string CloudinaryUploader::getUploadedImageSignature() {
    return uploadedImageSignature;
}
