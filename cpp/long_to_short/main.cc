#include <iostream>
#include <iomanip>
#include <arpa/inet.h>

using namespace std;


int main()
{
	uint32_t n32 = 0xFF000000;
	uint16_t n16 = ntohl(n32);
	n16 = htons(n16);

	cout << hex << n16 << endl;

	return 0;
}
