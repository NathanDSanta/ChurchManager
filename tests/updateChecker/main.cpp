  #include <iostream>
#include <curl/curl.h>
#include <json/json.h>  // Requires jsoncpp library
#include <string>
#include <fstream>
#include <sstream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string downloadFile(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

bool isUpdateAvailable(const std::string& currentVersion, const std::string& latestVersion) {
    return currentVersion < latestVersion;  // Simplified comparison
}

int main() {
    std::string currentVersion = "0.0.1";
    std::string versionJson = downloadFile("https://nathandsanta.github.io/ChurchManager/version.json");

    // Parse JSON
    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errs;
    std::istringstream sstr(versionJson);
    if (!Json::parseFromStream(reader, sstr, &root, &errs)) {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return 1;
    }

    std::string latestVersion = root["version"].asString();
    std::string updateUrl = root["url"].asString();

    if (isUpdateAvailable(currentVersion, latestVersion)) {
        std::cout << "Update available! Current version: " << currentVersion << ", Latest version: " << latestVersion << std::endl;
        // Download and install update
        std::string updateFile = downloadFile(updateUrl);
        std::ofstream outFile("latest-version.zip", std::ios::binary);
        outFile << updateFile;
        outFile.close();
        std::cout << "Update downloaded!" << std::endl;
    } else {
        std::cout << "You have the latest version." << std::endl;
    }

    return 0;
}

