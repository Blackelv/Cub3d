
#include "cub3D.h"

void	fps_check(void)
{
	static struct timeval	start;
	static int				frame_count;
	struct timeval			now;
	double					elapsed;

	if (start.tv_sec == 0 && start.tv_usec == 0)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - start.tv_sec) + (now.tv_usec - start.tv_usec) / 1e6;
	frame_count++;
	if (elapsed >= 5.0)
	{
		printf("Average FPS: %.2f\n", frame_count / elapsed);
		exit(0);
	}
}

void	fps_check_constant(void)
{
	static struct timeval	start;
	static struct timeval	last_print;
	static int				frame_count;
	struct timeval			now;
	double					elapsed;
	double					print_elapsed;

	if (start.tv_sec == 0 && start.tv_usec == 0)
	{
		gettimeofday(&start, NULL);
		gettimeofday(&last_print, NULL);
	}
	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - start.tv_sec) + (now.tv_usec - start.tv_usec) / 1e6;
	print_elapsed = (now.tv_sec - last_print.tv_sec) + (now.tv_usec
			- last_print.tv_usec) / 1e6;
	frame_count++;
	if (print_elapsed >= 1.0)
	{
		printf("Average FPS: %.2f\n", frame_count / elapsed);
		gettimeofday(&last_print, NULL);
	}
}
