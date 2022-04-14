#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <arpa/inet.h>
#include "string_utils.h"

using namespace std;


void parse_ipport(const std::string& ipport_str)
{
	cout << "parse_ipport(str = \"" << ipport_str << "\")" << endl;

	std::regex re_port("\\d+\\.\\d+$");
	std::smatch sm_port;
	if (!std::regex_search(ipport_str, sm_port, re_port))
	{
		cout << " Could'nt `regex_search` port" << endl;
		return;
	}

	std::string port_str = ipport_str.substr(sm_port.position());
	cout << "  port_str = \"" << port_str << "\"" << endl;

	std::string ip_str = ipport_str.substr(0, sm_port.position() - 1);
	cout << "  ip_str = \"" << ip_str << "\"" << endl;

	char buf[sizeof(in6_addr)];
	if (inet_pton(AF_INET, ip_str.c_str(), buf) == 1)
	{
		in_addr* p = (in_addr*)buf;
		cout << "  inet4_addr: " << hex << p->s_addr << endl;
	}
	else if (inet_pton(AF_INET6, ip_str.c_str(), buf) == 1)
	{
		in6_addr* p = (in6_addr*)buf;
		char str[INET6_ADDRSTRLEN];
		

		if (inet_ntop(AF_INET6, buf, str, INET6_ADDRSTRLEN))
		{
			cout << "  inet6_addr: " << str << endl;
		}
	}
	else
	{
		cout << "  Could'nt parse ipaddr" << endl; 
	}

	if (inet_pton(AF_INET, ("0.0." + port_str ).c_str(), buf))
	{
		in_addr* p = (in_addr*)buf;
		uint16_t port = ntohl(p->s_addr);
		port = htons(port);
		cout << "  port: " << dec << port << " (hex: " << hex << port << ")" << endl;
		cout << "  ntohs(port): " << dec << ntohs(port) << " (hex: " << hex << ntohs(port) << ")" << endl;
	}
	else
	{
		cout << "  Could'nt parse port" << endl;
	}
}

int main()
{
	parse_ipport("192.68.2.55.23.1");
	parse_ipport("AF:F:30:CD:BF:1A:A:25.1.23");
	parse_ipport("AF:F:30:CD:BF:55:23.25.192.2.0.1");
	parse_ipport("AF:F:30:CD:92.68.2.55.1.0");

	return 0;
}
