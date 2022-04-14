#include <string>
#include <iostream>
#include <sstream>

using namespace std;

template <typename T, typename OUT_T = uint8_t> 
OUT_T extract_bits(T bits, uint8_t pos, uint8_t end)
{
    bits = bits << pos;
 
    return (OUT_T)(bits >> (sizeof(bits) * 8 - (end - pos) - 1));
}

std::string nbns_compress(const std::string& name)
{
	std::stringstream ss_res;
	const uint8_t* p = reinterpret_cast<const uint8_t*>(name.c_str());
	const uint8_t* p_end = p + name.length();

	for(; p != p_end; ++p)
	{
		ss_res 	<< (char)('A' + extract_bits(*p, 0, 3)) 
				<< (char)('A' + extract_bits(*p, 4, 7));
	}
	
	return ss_res.str();
}

std::string nbns_decompress(const std::string& name)
{
	size_t len = name.length();
	if (len % 2 != 0)
		return "";

	std::stringstream ss_res;
	const uint8_t* p = reinterpret_cast<const uint8_t*>(name.c_str());
	const uint8_t* p_end = p + name.length();

	char sym;
	for(; p != p_end; p += 2)
	{
		char *p_sym = &sym;
		sym = (*p - 'A') << 4;
		sym +=  ((*(p + 1)) - 'A');
		
		ss_res << sym;
	}
	
	return ss_res.str();
}

int main()
{
	std::string name("EGFCEFEECACACACACACACACACACACACA"),
				initial_name = name;

	cout << "initial name:        " << name << endl; 

	name = nbns_decompress(name);
	cout << "decompressed_name:   " << name << endl;

	name = nbns_compress(name);
	cout << "compressed name:     " << name << endl;

	cout << "initial and compressed name is " << (initial_name == name ? "equal" : "not equal") << endl;  

	return 0;
}
