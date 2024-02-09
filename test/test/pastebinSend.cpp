#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <cstring>

const std::string API_DEV_KEY = "your_pastebin_api_key";

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t realsize = size * nmemb;
    std::string* response = (std::string*)userdata;
    response->append(ptr, realsize);
    return realsize;
}

bool sendFileToPastebin(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::string postdata = "api_dev_key=" + API_DEV_KEY + "&api_option=paste&api_paste_code=" + fileContent;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://pastebin.com/api/api_post.php");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            std::cout << "Pastebin Response: " << response << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "curl_easy_init() failed" << std::endl;
        return false;
    }

    curl_global_cleanup();

    return true;
}
