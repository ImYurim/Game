#include <stdio.h>
#include <conio.h>
#include <windows.h>


#define UP 1
#define DOWN 2
#define SUBMIT 3
#define EXIT 4
#ifndef __COLOR_LIST_
#define __COLOR_LIST_
enum {
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};
#endif
//함수 선언
void init();
void drawTitle();
void gotoxy(int, int);
int drawMenu();
int keyControl();
void drawInfo();
void setColor(int, int);
void drawGame();

int main() {
	init();
	while (1) {
		drawTitle();
		int selectMenu = drawMenu();
		if (selectMenu == 0) {
			drawGame();
		}
		else if (selectMenu == 2) {
			drawInfo();
		}
		else if (selectMenu == 4) {
			printf("\n");
			return 0;
		}
		system("cls");
	}

	return 0;
}



void init() {
	system("mode con cols=123 lines=30 | title 할리갈리게임");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void setColor(int forground,int background){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

void drawTitle() {
	printf("\n\n\n\n\n");
	gotoxy(6, 6);
	setColor(yellow, black);
	printf("#      #        #        #        #        #####");
	gotoxy(6, 7);
	printf("#      #       # #       #        #          #");
	gotoxy(6, 8);
	printf("########      #   #      #        #          #");
	gotoxy(6, 9);
	printf("#      #     #######     #        #          #");
	gotoxy(6, 10);
	printf("#      #    #       #    #        #          #");
	gotoxy(6, 11);
	printf("#      #   #         #   #######  #######  #####");
	setColor(purple, black);
	gotoxy(67, 6);
	printf("#####           #        #        #        #####");
	gotoxy(66, 7);
	printf("#               # #       #        #          #");
	gotoxy(66, 8);
	printf("#              #   #      #        #          #");
	gotoxy(66, 9);
	printf("#   #####     #######     #        #          #");
	gotoxy(66, 10);
	printf("#     #      #       #    #        #          #");
	gotoxy(67, 11);
	printf("#####      #         #   #######  #######  #####");
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int drawMenu() {
	int x = 55;
	int y = 16;
	gotoxy(x - 2, y);
	setColor(lightgreen, black);
	printf("> 게임시작");
	gotoxy(x, y+2);
	setColor(white, black);
	printf("게임정보");
	gotoxy(x, y+4);
	printf("  종료  ");

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 16) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y - 2);
				setColor(lightgreen, black);
				printf(">");
				y = y - 2;
				gotoxy(x, y);
				if (y == 16) {
					printf("게임시작");
					gotoxy(x, y + 2);
					setColor(white, black);
					printf("게임정보");
					gotoxy(x, y + 4);
					printf("  종료  ");
				}
				else if (y == 18) {
					printf("게임정보");
					gotoxy(x, y - 2);
					setColor(white, black);
					printf("게임시작");
					gotoxy(x, y + 2);
					printf("  종료  ");
				}
				else {
					printf("  종료  ");
					setColor(white, black);
					gotoxy(x, y - 4);
					printf("게임시작");
					gotoxy(x, y - 2);
					printf("게임정보");
				}
				setColor(white, black);
			}
			break;
		}
		case DOWN: {
			if (y < 20) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y + 2);
				setColor(lightgreen, black);
				printf(">");
				y = y + 2;
				gotoxy(x, y);
				if (y == 16) {
					printf("게임시작");
					gotoxy(x, y + 2);
					setColor(white, black);
					printf("게임정보");
					gotoxy(x, y + 4);
					printf("  종료  ");
				}
				else if (y == 18) {
					printf("게임정보");
					gotoxy(x, y - 2);
					setColor(white, black);
					printf("게임시작");
					gotoxy(x, y + 2);
					printf("  종료  ");
				}
				else {
					printf("  종료  ");
					setColor(white, black);
					gotoxy(x, y - 4);
					printf("게임시작");
					gotoxy(x, y - 2);
					printf("게임정보");
				}
				setColor(white, black);
			}
 			break;
		}

		case SUBMIT: {
			return y-16;
		}
		}
	}
}

int keyControl() {
	int temp = getch();

	if (temp == 224) {
		temp = getch();
		switch (temp) {
		case 72:

			return UP;

		case 80:

			return DOWN;
		}

	}
	//엔터
	else if (temp == 13) return SUBMIT; 
	//백스페이스
	else if (temp == 8) return EXIT;
	else return 0;
}

void drawInfo() {
	system("cls");
	gotoxy(55, 3);
	setColor(yellow, black);
	printf("[ 조작법 ]");
	setColor(white, black);
	gotoxy(53, 7);
	printf("1. 카드 뒤집기");
	gotoxy(55, 8);
	printf("p1 : 'a' ");
	gotoxy(55, 9);
	printf("p2 : '6' ");
	gotoxy(53, 11);
	printf("2. 종 울리기");
	gotoxy(55, 12);
	printf("p1 : 'd' ");
	gotoxy(55, 13);
	printf("p2 : '4' ");
	gotoxy(52, 20);
	printf("개발자 : 임유림");
	gotoxy(40, 24);
	setColor(lightgreen, black);
	printf("\'엔터\'");
	setColor(white, black);
	printf("를 누르면 메인화면으로 이동합니다.\n");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

void drawGame() {
	system("cls");
	printf("게임화면 할리갈리");
	while (1) {
		if (keyControl() == EXIT) {
			break;
		}
	}
}
