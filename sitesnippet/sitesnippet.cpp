#include "sitesnippet.hpp"

size_t onReceive(char* ptr, size_t size, size_t nmemb, void* stream) {
    // streamはCURLOPT_WRITEDATAで指定したバッファへのポインタ
    std::vector<char>* recvBuffer = (std::vector<char>*)stream;
    const size_t sizes = size * nmemb;
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr + sizes);
    return sizes;
}

std::string SiteSnippet::getSnippet(std::string url)
{
    CURL *curl = curl_easy_init();
    int statusCode;
    char* location;

    if (curl == nullptr) {
        curl_easy_cleanup(curl);
        return "";
    }

    std::vector<char> responseData;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onReceive);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return "";
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);

    if (statusCode == 301){
        curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &location);
        std::cerr << "Redirect to: " << location << std::endl;
    }

    curl_easy_cleanup(curl);

    return std::string(responseData.begin(), responseData.end());
}