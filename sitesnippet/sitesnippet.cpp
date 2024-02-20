#include <regex>
#include "sitesnippet.hpp"

size_t onReceive(char *ptr, size_t size, size_t nmemb, void *stream)
{
    auto *recvBuffer = (std::vector<char> *)stream;
    const size_t sizes = size * nmemb;
    recvBuffer->insert(recvBuffer->end(), (char *)ptr, (char *)ptr + sizes);
    return sizes;
}

std::string SiteSnippet::getSnippetText(const std::string& url, int maxRedirect)
{
    CURL *curl = curl_easy_init();
    int statusCode;
    char *location;

    if (curl == nullptr)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    std::vector<char> responseData;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onReceive);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return "";
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
    std::cerr << "Status code: " << statusCode << std::endl;
    std::cerr << "Max redirect: " << maxRedirect << std::endl;
    if (statusCode == 301)
    {
        curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &location);
        std::cerr << "Redirect to: " << location << std::endl;
        if (maxRedirect > 0)
        {
            return getSnippetText(location, maxRedirect - 1);
        }
    }

    if (statusCode != 200)
    {
        curl_easy_cleanup(curl);
        return "";
    }

    curl_easy_cleanup(curl);
    std::string responseDataStr(responseData.begin(), responseData.end());
    std::string snippet;

    std::regex metaRegex("<meta (.*?)>");
    std::smatch match;
    std::string nameDescription = "name=\"description\"";
    std::regex contentRegex("content=\"(.*?)\"");
    std::string contentText = "content=\"";
    for(int maxSearch = 256; maxSearch != 0; maxSearch--) {
        std::regex_search(responseDataStr, match, metaRegex);
        std::string meta = match.str();
        std::cerr << "Meta: " << meta << std::endl;
        if (meta.find(nameDescription) != std::string::npos) {
            std::regex_search(meta, match, contentRegex);
            std::string content = match.str();
            snippet = content.substr(contentText.size(), content.size() - contentText.size() - 1);
            return snippet;
        }
        responseDataStr = match.suffix();
    }

    return "";
}