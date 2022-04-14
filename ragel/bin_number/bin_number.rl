#include <iostream>
#include <string>

using namespace std;

%%{
	machine bin_number;

    main := 0x11100000..0x11101111;	
}%%

void test(const char* data, size_t length)
{
	const char *p = data, *pe = data + length, *val_begin = data, *val_end = data;
    const char *eof = pe;
    const char *ts = data;
    const char *te = data;
    int act = 0;
    int cs = 0;

	%% write data;
    
    %% write init;
    %% write exec;
}

int main()
{
	test("XXX: 1", sizeof("XXX: 1"));
	test("XXX: 32145", sizeof("XXX: 32145"));
	
	return 0;
}
