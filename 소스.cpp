#include <stdio.h>
#include <conio.h>
#include <windows.h>


#define UP 1
#define DOWN 2
#define SUBMIT 3

//함수 선언
void init();
void drawTitle();
void gotoxy(int, int);
int drawMenu();
int keyControl();
void drawInfo();

int main() {
	init();
	while (1) {
		drawTitle();
		int selectMenu = drawMenu();
		if (selectMenu == 0) {
			//게임시작
		}
		else if (selectMenu == 2) {
			drawInfo();
		}
		else if (selectMenu == 4) {
			return 0;
		}
		system("cls");
	}

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

int drawMenu() {
	int x = 50;
	int y = 16;
	gotoxy(x - 2, y);
	printf("> 게임시작");
	gotoxy(x, y+2);
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
				printf(">");
				y = y - 2;
			}
			break;
		}
		case DOWN: {
			if (y < 20) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y + 2);
				printf(">");
				y = y + 2;
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
	else if (temp == 13) { 
		return SUBMIT; 
	}
	else return 0;
}

void drawInfo() {
	system("cls");
	gotoxy(55, 3);
	printf("[ 조작법 ]");
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
	printf("엔터를 누르면 메인화면으로 이동합니다.\n");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}
