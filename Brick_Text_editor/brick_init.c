#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <brick_init.h>
#include <brick_core.h>
#include <brick_termios.h>

Brick brick;

int main(int argc, char *argv[])
{
	terminos_raw(&brick);
	get_terminos_property(&brick);
	brick_core_init(brick);
	
	while(1)
	{
		brick_refresh_screen();
		brick_core_inloop();
	}
	
	return 0;
}