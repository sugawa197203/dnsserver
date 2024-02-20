#pragma once
#include <string>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <atomic>
#include <iostream>
#include <curl/curl.h>
#include <vector>

class SiteSnippet
{
public:
    /**
     * @brief Get the Snippet text from the given URL
     * @param url
     * @return std::string
     */
    static std::string getSnippetText(const std::string& url, int maxRedirect = 10);
};