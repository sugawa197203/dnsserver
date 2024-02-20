#include <iostream>
#include <fstream>
#include <vector>
#include <curl/curl.h>
#include <cstring>

size_t onReceive(char* ptr, size_t size, size_t nmemb, void* stream) {
    // stream��CURLOPT_WRITEDATA�Ŏw�肵���o�b�t�@�ւ̃|�C���^
    std::vector<char>* recvBuffer = (std::vector<char>*)stream;
    const size_t sizes = size * nmemb;
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr + sizes);
    return sizes;
}

int main(int argc, const char * argv[]) {
    // curl�̃Z�b�g�A�b�v
    CURL *curl = curl_easy_init();
    if (curl == nullptr) {
        curl_easy_cleanup(curl);
        return 1;
    }
    // ���X�|���X�f�[�^�̊i�[��
    std::vector<char> responseData;
    // �ڑ���URL
    curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
    // �T�[�o��SSL�ؖ����̌��؂����Ȃ�
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    // ���X�|���X�̃R�[���o�b�N
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onReceive);
    // �������݃o�b�t�@���w��
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    // �ʐM���s
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return 1;
    }

    int statusCode;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
    std::cout << "Status code: " << statusCode << std::endl;
    if (statusCode == 301){
        char* location;
        curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &location);
        std::cout << "Redirect to: " << location << std::endl;
        std::cout << std::endl;
    }

    // ��n��
    curl_easy_cleanup(curl);

    std::ofstream ofs;
    ofs.open("tmp.html", std::ios::out);
    if (ofs.is_open()) {
        ofs << responseData.data() << std::endl;
    }
    return 0;
}
