#include <iostream>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    std::string name;
    std::cin >> name;

    struct hostent *host;
    if ((host = gethostbyname(name.c_str())) == NULL)
    {
        std::cout << "Error: " << hstrerror(h_errno) << std::endl;
        return 1;
    }

    std::cout << "Name: " << host->h_name << std::endl;
    std::cout << "Aliases: " << std::endl;
    for (char **alias = host->h_aliases; *alias != NULL; alias++)
    {
        std::cout << "\t" << *alias << std::endl;
    }

    std::cout << "Address Type: " << host->h_addrtype << std::endl;
    std::cout << "Address Length: " << host->h_length << std::endl;
    std::cout << "Addresses: " << std::endl;
    for (char **address = host->h_addr_list; *address != NULL; address++)
    {
        std::cout << "\t" << inet_ntoa(*(struct in_addr *)*address) << std::endl;
    }

    return 0;
}