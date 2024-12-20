#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <string>
#include <fstream>
#include <sstream>

// Callback function to write data into a string
size_t WriteStringCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Callback function to write data into a file
size_t WriteFileCallback(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

// Function to download JSON data as a string
std::string downloadJson(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteStringCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
    }

    return readBuffer;
}

// Function to download a binary file
bool downloadFile(const std::string& url, const std::string& outFilename) {
    CURL* curl;
    CURLcode res;
    FILE* outFile;

    curl = curl_easy_init();
    if (curl) {
        outFile = fopen(outFilename.c_str(), "wb");  // Open the file in binary mode
        if (outFile) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, outFile);
            res = curl_easy_perform(curl);
            fclose(outFile);

            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                return false;
            }
        } else {
            std::cerr << "Failed to open file for writing: " << outFilename << std::endl;
            return false;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize curl" << std::endl;
        return false;
    }

    return true;
}

// Function to check if an update is available
bool isUpdateAvailable(const std::string& currentVersion, const std::string& latestVersion) {
    return currentVersion < latestVersion;  // Simplified comparison
}

int main() {
    std::string currentVersion = "0.0.1";
    std::string jsonData = downloadJson("https://nathandsanta.github.io/ChurchManager/version.json");

    // Parse JSON data
    Json::CharReaderBuilder reader;
    Json::Value root;
    std::string errs;
    std::istringstream sstr(jsonData);
    if (!Json::parseFromStream(reader, sstr, &root, &errs)) {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return 1;
    }

    std::string latestVersion = root["version"].asString();
    std::string updateUrl = root["url"].asString();

    if (isUpdateAvailable(currentVersion, latestVersion)) {
        std::cout << "Update available! Current version: " << currentVersion << ", Latest version: " << latestVersion << std::endl;
        // Download and install update
        if (downloadFile(updateUrl, "latest-version.zip")) {
            std::cout << "Update downloaded successfully!" << std::endl;
        } else {
            std::cerr << "Failed to download update." << std::endl;
        }
    } else {
        std::cout << "You have the latest version." << std::endl;
    }

    return 0;
}
