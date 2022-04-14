#include <iostream>
#include <string>
#include <list>

using namespace std;

typedef list<int> EqualRangeType;

struct E {
    int					m_tKey;
    EqualRangeType		m_lResult;
};

struct I {
    int					m_tKey;
    int					m_tValue;
};

union U {
	int x;
	I	i;
	E	e;
	U() { x = 0; }
	~U() {}
};

int main()
{
    E e1 { 1, {1,2} }, e2;
    e2 = e1;
    
    I i1 {4,4}, i2;
    i2 = i1;
    
    EqualRangeType::const_iterator it_e1 = e1.m_lResult.begin(), it_e2 = e2.m_lResult.begin();
    
    cout << "e1: " << e1.m_tKey << ", (" << (*it_e1) << ", " << (*++it_e1) << ")" << endl
         << "e2: " << e2.m_tKey << ", (" << (*it_e2) << ", " << (*++it_e2) << ")" << endl
         << "i1: " << i1.m_tKey << ", " << i1.m_tValue << endl
         << "i2: " << i2.m_tKey << ", " << i2.m_tValue << endl;

	U u1, u2;
	u1.e = e1;
	u2 = u1;
	
    it_e1 = u1.e.m_lResult.begin(), it_e2 = u2.e.m_lResult.begin();
    
    cout << "u1: " << u1.e.m_tKey << ", (" << (*it_e1) << ", " << (*++it_e1) << ")" << endl
         << "u2: " << u2.e.m_tKey << ", (" << (*it_e2) << ", " << (*++it_e2) << ")" << endl;
	

    return 0;    
}