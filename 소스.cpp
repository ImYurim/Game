#include <stdio.h>
#include <windows.h>

//함수 선언
void init();
void drawTitle();
void gotoxy(int, int);
void drawMenu();

int main() {
	init();
	drawTitle();
	drawMenu();
	return 0;
}



void init() {
	system("mode con cols=123 lines=30 | title 할리갈리게임");
}

void drawTitle() {
	printf("\n\n\n\n\n");
	printf("      #      #        #        #        #        #####             #####           #        #        #        #####       \n");
	printf("      #      #       # #       #        #          #              #               # #       #        #          #         \n");
	printf("      ########      #   #      #        #          #              #              #   #      #        #          #         \n");
	printf("      #      #     #######     #        #          #              #   #####     #######     #        #          #         \n");
	printf("      #      #    #       #    #        #          #              #     #      #       #    #        #          #         \n");
	printf("      #      #   #         #   #######  #######  #####             #####      #         #   #######  #######  #####       \n");

}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void drawMenu() {
	gotoxy(50 - 2, 16);
	printf("> 게임시작");
	gotoxy(50, 18);
	printf("게임정보");
	gotoxy(50, 20);
	printf("종료");
}
