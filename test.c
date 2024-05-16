#include <libc.h>
#include <sys/time.h>

int main()
{
	struct timeval tv;
	struct timezone tz;

	int time  = gettimeofday(&tv, &tz);
	printf("%ld\n", tv.tv_sec * 1000 + tv.tv_usec / 1000);

	return 0;
}
