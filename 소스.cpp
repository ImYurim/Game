#include <stdio.h>
#include <conio.h>
#include <windows.h>


#define UP 1
#define DOWN 2
#define SUBMIT 3
#define EXIT 4
#define P1CARD 5
#define P1RING 6
#define P2CARD 7
#define P2RING 8

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
void startGame();
void drawGame();
void playerKeyInput();

int main() {
	init();
	while (1) {
		drawTitle();
		int selectMenu = drawMenu();
		if (selectMenu == 0) {
			startGame();
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
	//A랑 a
	else if (temp == 65|| temp==97) return P1CARD;
	//D랑 d
	else if (temp == 68 || temp == 100) return P1RING;
	//4
	else if (temp == 52) return P2CARD;
	//6
	else if (temp == 54) return P2RING;

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


void startGame() {
	drawGame();
	playerKeyInput();
}

void drawGame() {
	system("cls");
	//p1 카드 그리기
	//아직 안 뒤집은 카드
	gotoxy(5, 3);
	setColor(yellow, black);
	printf("P1");

	setColor(white, black);
	gotoxy(5,7);
	printf("┌─────┐");
	gotoxy(5, 8);
	printf("│     │");
	gotoxy(5, 9);
	printf("│     │");
	gotoxy(5, 10);
	printf("│     │");
	gotoxy(5, 11);
	printf("└─────┘");
	gotoxy(8, 6);
	printf("┌─────┐");
	gotoxy(14, 7);
	printf("│");
	gotoxy(14, 8);
	printf("│");
	gotoxy(14, 9);
	printf("│");
	gotoxy(12, 10);
	printf("──┘");

	//뒤집은 카드
	gotoxy(20, 7);
	printf("┌─────┐");
	gotoxy(20, 8);
	printf("│     │");
	gotoxy(20, 9);
	printf("│     │");
	gotoxy(20, 10);
	printf("│     │");
	gotoxy(20, 11);
	printf("└─────┘");
	gotoxy(23, 6);
	printf("┌─────┐");
	gotoxy(29, 7);
	printf("│");
	gotoxy(29, 8);
	printf("│");
	gotoxy(29, 9);
	printf("│");
	gotoxy(27, 10);
	printf("──┘");

	//p2 카드 그리기
	gotoxy(66, 3);
	setColor(purple, black);
	printf("P2");
	setColor(white, black);
	//안 뒤집은 카드
	gotoxy(66, 7);
	printf("┌─────┐");
	gotoxy(66, 8);
	printf("│     │");
	gotoxy(66, 9);
	printf("│     │");
	gotoxy(66, 10);
	printf("│     │");
	gotoxy(66, 11);
	printf("└─────┘");
	gotoxy(69, 6);
	printf("┌─────┐");
	gotoxy(75, 7);
	printf("│");
	gotoxy(75, 8);
	printf("│");
	gotoxy(75, 9);
	printf("│");
	gotoxy(73, 10);
	printf("──┘");

	//뒤집은 카드
	gotoxy(82, 7);
	printf("┌─────┐");
	gotoxy(82, 8);
	printf("│     │");
	gotoxy(82, 9);
	printf("│     │");
	gotoxy(82, 10);
	printf("│     │");
	gotoxy(82, 11);
	printf("└─────┘");
	gotoxy(85, 6);
	printf("┌─────┐");
	gotoxy(91, 7);
	printf("│");
	gotoxy(91, 8);
	printf("│");
	gotoxy(91, 9);
	printf("│");
	gotoxy(89, 10);
	printf("──┘");




	
}

void playerKeyInput() {
	//플레이어 키 입력
	while (1) {
		int key = keyControl();
		if (key == EXIT) {
			break;
		}
		else if (key == P1RING) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("d입력 p1이 종을 울렸다.");
		}
		else if (key == P1CARD) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("a입력 p1이 카드를 뒤집었다.");
		}
		else if (key == P2CARD) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("4입력 p2이 카드를 뒤집었다.");
		}
		else if (key == P2RING) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("6입력 p2이 종을 울렸다.");
		}
	}
}
