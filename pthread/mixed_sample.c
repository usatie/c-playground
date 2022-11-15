// die    400
// eat    200
// sleep  300
// think  0

#include <sys/time.h>

void	philo(int id)
{
	ts = gettimestamp();                // ts = 0           // ts = 1
	printf("%s %d is eating", ts, id);  // 0ms 1 is eaintg  // 1ms 2 is eating
	sleep(200);
	ts = gettimestamp();
	printf("%s %d is sleeping", ts, id);
	sleep(300)
	ts = gettimestamp();
	printf("%s %d is thinking", ts, id);
}
