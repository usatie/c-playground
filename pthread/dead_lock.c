//A <-1-> B <-2-> C <-3-> A

// philo A : left(3), right(1)
// philo B : 1, 2
// philo C : 2, 3

void *philo(void *arg)
{
	lock(left);
	lock(right);
}

int	main(void)
{
	pthread_create(a);
	pthread_create(b);
}
