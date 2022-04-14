#include <iostream>
#include <string>
#include <arpa/inet.h>

using namespace std;

uint16_t parse_port(const std::string& str)
{
    uint16_t port;
    char buf[sizeof(in6_addr)];
    if (inet_pton(AF_INET, (str + ".0.0").c_str(), buf) == 1)
    {
        in_addr* p = (in_addr*)buf;
        // port = htons(ntohl(p->s_addr));
        port = p->s_addr;
    }
    else
    {
        return 0;
    }

    return port;
}


uint32_t parse_ip(std::string str)
{
    char buf[sizeof(in6_addr)];
    if (inet_pton(AF_INET, (str).c_str(), buf) == 1)
    {
        in_addr* p = (in_addr*)buf;
        return p->s_addr;
    }
    else
    {
        return 0;   
    }
}

int main()
{
    uint16_t port = parse_port("10.255");
    cout << "port = " << port << ", hex_port = " << hex << port << dec << endl;

    uint32_t ip = parse_ip("10.16.0.1");
    cout << "ip = " << ip << ", hex_ip = " << hex << ip << dec << endl;

    return 0;
}

