#define COLOR_DARKBLUE	0x1
#define COLOR_DARKGREEN	0x2
#define COLOR_TEAL		0x3
#define COLOR_DARKRED	0x4
#define COLOR_MAGENTA	0x5
#define COLOR_DYELLOW	0x6
#define COLOR_DEFAULT	0x7
#define COLOR_GRAY		0x8
#define COLOR_BLUE		0x9
#define COLOR_GREEN		0xA
#define COLOR_CYAN		0xB
#define COLOR_RED		0xC
#define COLOR_PURPLE	0xD
#define COLOR_YELLOW	0xE
#define COLOR_WHITE		0xF


void CreateConsole(const char* Name)
{
	AllocConsole();
	FILE* fp;
	fp = freopen("CONOUT$", "w", stdout);

	SetConsoleTitleA(Name);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, COLOR_DEFAULT);
}
void print(std::string Message, ...)
{
	char buffer[1024];
	va_list vlist;
	va_start(vlist, Message);
	_vsnprintf(buffer, sizeof(buffer), Message.c_str(), vlist);
	va_end(vlist);

	printf("%s", buffer);
}
void printColor(int color,std::string Message, ...)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, color);
	char buffer[1024];
	va_list vlist;
	va_start(vlist, Message);
	_vsnprintf(buffer, sizeof(buffer), Message.c_str(), vlist);
	va_end(vlist);

	printf("%s", buffer);
	SetConsoleTextAttribute(hOut, COLOR_DEFAULT);
}
void printWarning(std::string Message, ...)
{
	printColor(COLOR_DARKRED, "[WARNING!] ");
	printColor(COLOR_RED, Message);
}