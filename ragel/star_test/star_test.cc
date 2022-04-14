
#line 1 "star_test.rl"
#include <iostream>
#include <string>

using namespace std;


#line 35 "star_test.rl"


void test(const char* data, size_t length)
{
	const char *p = data, *pe = data + length, *val_begin = data, *val_end = data;
    const char *eof = pe;
    const char *ts = data;
    const char *te = data;
    int act = 0;
    int cs = 0;

	
#line 23 "star_test.cc"
static const char _star_test_actions[] = {
	0, 1, 0, 1, 2, 1, 3, 1, 
	5, 2, 1, 4, 3, 0, 1, 4
	
};

static const char _star_test_key_offsets[] = {
	0, 0, 1, 2, 3, 4, 7, 9, 
	13
};

static const char _star_test_trans_keys[] = {
	88, 88, 58, 32, 88, 48, 57, 48, 
	57, 100, 103, 105, 116, 100, 103, 105, 
	116, 0
};

static const char _star_test_single_lengths[] = {
	0, 1, 1, 1, 1, 1, 0, 4, 
	4
};

static const char _star_test_range_lengths[] = {
	0, 0, 0, 0, 0, 1, 1, 0, 
	0
};

static const char _star_test_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 11, 13, 
	18
};

static const char _star_test_trans_targs[] = {
	2, 0, 3, 0, 4, 0, 7, 0, 
	1, 6, 0, 6, 5, 5, 5, 5, 
	5, 8, 5, 5, 5, 5, 8, 5, 
	5, 5, 0
};

static const char _star_test_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 7, 12, 12, 12, 
	12, 1, 9, 9, 9, 9, 0, 7, 
	12, 9, 0
};

static const char _star_test_to_state_actions[] = {
	0, 0, 0, 0, 0, 3, 0, 0, 
	0
};

static const char _star_test_from_state_actions[] = {
	0, 0, 0, 0, 0, 5, 0, 0, 
	0
};

static const char _star_test_eof_trans[] = {
	0, 0, 0, 0, 0, 0, 24, 25, 
	26
};

static const int star_test_start = 5;
static const int star_test_first_final = 5;
static const int star_test_error = 0;

static const int star_test_en_main = 5;


#line 47 "star_test.rl"
    
    
#line 95 "star_test.cc"
	{
	cs = star_test_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 49 "star_test.rl"
    
#line 105 "star_test.cc"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_acts = _star_test_actions + _star_test_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 3:
#line 1 "NONE"
	{ts = p;}
	break;
#line 126 "star_test.cc"
		}
	}

	_keys = _star_test_trans_keys + _star_test_key_offsets[cs];
	_trans = _star_test_index_offsets[cs];

	_klen = _star_test_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _star_test_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _star_test_trans_targs[_trans];

	if ( _star_test_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _star_test_actions + _star_test_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 10 "star_test.rl"
	{
		val_begin = p;
		cout << "action `bgn` at pos: " << p - data << endl;
	}
	break;
	case 1:
#line 16 "star_test.rl"
	{
		val_end = p;
		cout << "action `end` at pos: " << p - data << endl;
	}
	break;
	case 4:
#line 22 "star_test.rl"
	{te = p;p--;{
		cout << "action `f`, got string: " << std::string(val_begin, val_end - val_begin) << endl;
	}}
	break;
	case 5:
#line 27 "star_test.rl"
	{te = p;p--;{
		cout << "empty action" << endl;
	}}
	break;
#line 217 "star_test.cc"
		}
	}

_again:
	_acts = _star_test_actions + _star_test_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 2:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 230 "star_test.cc"
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _star_test_eof_trans[cs] > 0 ) {
		_trans = _star_test_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	_out: {}
	}

#line 50 "star_test.rl"
}

int main()
{
	test("XXX: 1", sizeof("XXX: 1"));
	test("XXX: 32145", sizeof("XXX: 32145"));
	
	return 0;
}
