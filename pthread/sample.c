#include <pthread.h>
#include <stdio.h>

int	x = 0;
//pthread_mutex_t mutex;

void	*f(void* arg)
{
	int i = 0;

	(void)arg;
	while (i < 1000000)
	{
		//pthread_mutex_lock(&mutex);
		//              t1: x = 500        // t2: x = 1000
		int tmp = x; // t1: tmp = 500      // t2: tmp = 1000
		tmp++;       // t1: tmp = 501      // t2: tmp = 1001
		x = tmp;     // t1: x = 501        // t2: x = 1001
		//pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int main(void)
{
	/*
	pthread_t	t1, t2;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, f, NULL);
	pthread_create(&t2, NULL, f, NULL);
	pthread_join(t1, NULL); // wait t1
	pthread_join(t2, NULL); // wait t2
	*/
	f(NULL);
	printf("x = %d\n", x);
	return (0);
}
