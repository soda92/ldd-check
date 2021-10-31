#include <fmt/core.h>

#ifdef WIN32
#include <conio.h>
#else
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>	 //STDIN_FILENO

void _getch()
{
	int c;
	static struct termios oldt, newt;

	/*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
	tcgetattr(STDIN_FILENO, &oldt);
	/*now the settings will be copied*/
	newt = oldt;

	/*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
	newt.c_lflag &= ~(ICANON | ECHO);

	/*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	c = getchar();

	/*restore the old settings*/
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	// https://stackoverflow.com/a/1798833/12291425
}
#endif

int main()
{
	fmt::print("Hello World!\n");
	_getch();
	return 0;
}
