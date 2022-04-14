#include <chrono>
#include <iostream>

using namespace std;

typedef std::chrono::high_resolution_clock 					ClockType;
typedef std::chrono::nanoseconds 							DurationType;
typedef std::chrono::time_point<ClockType>					TimeType;

DurationType::rep timePointToInteger(const TimeType& tTime)
{
	return std::chrono::duration_cast<DurationType>(tTime.time_since_epoch()).count();
}

int main()
{
	TimeType t1 = ClockType::now(), t2;

	t2 = t1 + DurationType(1);

	cout << timePointToInteger(t1) << endl << timePointToInteger(t2) << endl;
	
	return 0;
}
