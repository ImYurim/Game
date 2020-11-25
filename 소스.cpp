#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include<cstdlib>
#include<ctime>




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
void giveCard();
void drawGame();
void playerKeyInput();
void RestOfCard();
void checkToGetCard(int);
void drawCard(int, int);
void giveCardToP1();
void giveCardToP2();
void cleanP1Card();
void cleanP2Card();

//전역 변수
//가지고 있는 카드 개수
int p1_card;
//종울렸나
int p1_ring;
//카드 뒤집었나
int p1_open = 0;
//처음에 할당 받은 카드
int p1_notshowed[60] = { 0 };
//몇 번째까지 뒤집었나
int p1_cardnum = 0;
//뒤집은 카드
int p1_showed[30] = { 0 };


int p2_card;
int p2_ring;
int p2_open = 0;
int p2_notshowed[60] = { 0 };
int p2_cardnum = 0;
int p2_showed[30] = { 0 };


char card[20] = { '*','*','*','*','*','^','^','^','^','^','@','@','@','@','@','&','&','&','&','&' };

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


//게임 화면크기, 게임 제목 설정
void init() {
	system("mode con cols=123 lines=30 | title 할리갈리게임");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//글자, 배경색 바꾸기
void setColor(int forground, int background) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

//메인화면 제목
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

//커서 옮기기
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

//메인 화면
int drawMenu() {
	int x = 55;
	int y = 16;
	gotoxy(x - 2, y);
	setColor(lightgreen, black);
	printf("> 게임시작");
	gotoxy(x, y + 2);
	setColor(white, black);
	printf("게임정보");
	gotoxy(x, y + 4);
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
			return y - 16;
		}
		}
	}
}

//key입력 정의
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
	else if (temp == 65 || temp == 97) return P1CARD;
	//D랑 d
	else if (temp == 68 || temp == 100) return P1RING;
	//4
	else if (temp == 52) return P2CARD;
	//6
	else if (temp == 54) return P2RING;

	else return 0;
}

//게임 정보
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

//게임시작
void startGame() {
	giveCard();
	p1_card = 30;
	p2_card = 30;
	drawGame();
	playerKeyInput();


}

//플레이어들에게 카드 할당
void giveCard() {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 30; i++)
	{
		p1_notshowed[i] = (rand() % 20);
		
	}
	for (int i = 0; i < 30; i++)
	{
		p2_notshowed[i] = (rand() % 20);
	}

}

//플레이어 카드 모양 그려주기
void drawGame() {
	system("cls");
	//p1 카드 그리기
	//아직 안 뒤집은 카드
	gotoxy(5, 3);
	setColor(yellow, black);
	printf("P1");

	setColor(white, black);
	gotoxy(5, 7);
	printf("┌───────┐");
	gotoxy(5, 8);
	printf("│       │");
	gotoxy(5, 9);
	printf("│       │");
	gotoxy(5, 10);
	printf("│       │");
	gotoxy(9, 10);
	printf("%d", p1_card);
	gotoxy(5, 11);
	printf("│       │");
	gotoxy(5, 12);
	printf("│       │");
	gotoxy(5, 13);
	printf("└───────┘");
	gotoxy(8, 6);
	printf("┌───────┐");
	gotoxy(16, 7);
	printf("│");
	gotoxy(16, 8);
	printf("│");
	gotoxy(16, 9);
	printf("│");
	gotoxy(16, 10);
	printf("│");
	gotoxy(16, 11);
	printf("│");
	gotoxy(14, 12);
	printf("──┘");

	//뒤집은 카드
	gotoxy(20, 7);
	printf("┌───────┐");
	gotoxy(20, 8);
	printf("│       │");
	gotoxy(20, 9);
	printf("│       │");
	gotoxy(20, 10);
	printf("│       │");
	gotoxy(20, 11);
	printf("│       │");
	gotoxy(20, 12);
	printf("│       │");
	gotoxy(20, 13);
	printf("└───────┘");
	gotoxy(23, 6);
	printf("┌───────┐");
	gotoxy(31, 7);
	printf("│");
	gotoxy(31, 8);
	printf("│");
	gotoxy(31, 9);
	printf("│");
	gotoxy(31, 10);
	printf("│");
	gotoxy(31, 11);
	printf("│");
	gotoxy(29, 12);
	printf("──┘");

	//p2 카드 그리기
	gotoxy(66, 3);
	setColor(purple, black);
	printf("P2");
	setColor(white, black);
	//안 뒤집은 카드
	gotoxy(66, 7);
	printf("┌───────┐");
	gotoxy(66, 8);
	printf("│       │");
	gotoxy(66, 9);
	printf("│       │");
	gotoxy(66, 10);
	printf("│       │");
	gotoxy(70, 10);
	printf("%d", p1_card);
	gotoxy(66, 11);
	printf("│       │");
	gotoxy(66, 12);
	printf("│       │");
	gotoxy(66, 13);
	printf("└───────┘");
	gotoxy(69, 6);
	printf("┌───────┐");
	gotoxy(77, 7);
	printf("│");
	gotoxy(77, 8);
	printf("│");
	gotoxy(77, 9);
	printf("│");
	gotoxy(77, 10);
	printf("│");
	gotoxy(77, 11);
	printf("│");
	gotoxy(75, 12);
	printf("──┘");


	//뒤집은 카드
	gotoxy(82, 7);
	printf("┌───────┐");
	gotoxy(82, 8);
	printf("│       │");
	gotoxy(82, 9);
	printf("│       │");
	gotoxy(82, 10);
	printf("│       │");
	gotoxy(82, 11);
	printf("│       │");
	gotoxy(82, 12);
	printf("│       │");
	gotoxy(82, 13);
	printf("└───────┘");
	gotoxy(85, 6);
	printf("┌───────┐");
	gotoxy(93, 7);
	printf("│");
	gotoxy(93, 8);
	printf("│");
	gotoxy(93, 9);
	printf("│");
	gotoxy(93, 10);
	printf("│");
	gotoxy(93, 11);
	printf("│");
	gotoxy(91, 12);
	printf("──┘");





}



//플레이어들 키 입력 시 변화
void playerKeyInput() {

	while (1) {


		if (p1_card-p1_cardnum == 0) {
			gotoxy(0, 20);
			printf("p1의 카드가 모두 소진되었습니다. p2의 승리입니다.");
			Sleep(2000);
			break;

		}
		else if (p2_card-p2_cardnum == 0) {
			gotoxy(0, 20);
			printf("p2의 카드가 모두 소진되었습니다. p1의 승리입니다.");
			Sleep(2000);
			break;

		}

		int key = keyControl();
		if (key == EXIT) {
			break;
		}
		else if (key == P1RING && p2_ring==0 && (p1_cardnum == p2_cardnum)) {
			gotoxy(0 , 20);
			printf("                               ");
			gotoxy(3, 20);
			setColor(yellow, black);
			printf("p1이 종을 울렸습니다.");
			setColor(white, black);
			p1_ring = 1;
			checkToGetCard(1);
		}
		else if (key == P1CARD && p1_open == 0 ) {
			gotoxy(3, 23);
			printf("                            ");
			gotoxy(0, 20);
			printf("                                 ");
			gotoxy(61, 23);
			printf("                            ");
			gotoxy(59, 20);
			printf("                                 ");
			gotoxy(3, 20);
			printf("p1이 카드를 뒤집었습니다.");
			drawCard(p1_notshowed[p1_cardnum], 1);
			p1_open = 1;
			p1_cardnum++;
			p1_ring = 0;

		}
		else if (key == P2CARD && p2_open == 0) {
			gotoxy(3, 23);
			printf("                            ");
			gotoxy(0, 20);
			printf("                                 ");
			gotoxy(61, 23);
			printf("                            ");
			gotoxy(59, 20);
			printf("                                 ");
			gotoxy(61, 20);
			printf("p2이 카드를 뒤집었습니다.");
			drawCard(p2_notshowed[p2_cardnum], 2);
			p2_open = 1;
			p2_cardnum++;
			p2_ring = 0;

		}
		else if (key == P2RING && p1_ring==0 && (p1_cardnum==p2_cardnum)) {
			gotoxy(59, 20);
			printf("                                ");
			gotoxy(61, 20);
			setColor(purple, black);
			printf("p2이 종을 울렸습니다.");
			setColor(white, black);
			p2_ring = 1;
			checkToGetCard(2);
		}
		RestOfCard();
		if (p1_open == 1 && p2_open == 1) {
			p1_open = 0;
			p2_open = 0;
		}


	}


}

//카드 같은 모양에 개수 5개 일치하는지 확인한 후 종 울린사람이 맞추면 상대방 카드 뺏어오기
void checkToGetCard(int player) {
	// * 카드
		if ((p1_notshowed[p1_cardnum-1] == 0 && p2_notshowed[p2_cardnum-1] == 3 )||(p1_notshowed[p1_cardnum-1] == 3 && p2_notshowed[p2_cardnum-1] == 0)) {
			//p1이 먼저 맞춤 p2 카드를 p1한테 줌
			if (player == 1) {
				giveCardToP1();

				return;
			}

			else {
				//P2가 맞춤 
				giveCardToP2();
				return;
			}
		}


		else if ((p1_notshowed[p1_cardnum-1] == 1 && p2_notshowed[p2_cardnum-1] == 2)||(p1_notshowed[p1_cardnum-1] == 2 && p2_notshowed[p2_cardnum-1] == 1)) {
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
				
				giveCardToP2();
				return;
			}
		}

		else if ((p1_notshowed[p1_cardnum-1] == 4 && p2_notshowed[p2_cardnum-1] != 0 && p2_notshowed[p2_cardnum-1] != 1 && p2_notshowed[p2_cardnum-1] != 2 && p2_notshowed[p2_cardnum-1] != 3 && p2_notshowed[p2_cardnum - 1] != 4) || (p2_notshowed[p2_cardnum-1] == 4 && p1_notshowed[p1_cardnum-1] != 0 && p1_notshowed[p1_cardnum-1] != 1 && p1_notshowed[p1_cardnum-1] != 2 && p1_notshowed[p1_cardnum-1] != 3 && p1_notshowed[p1_cardnum - 1] != 4)) {
				if (player == 1) {
					giveCardToP1();
					return;
				}

				else {
			
					giveCardToP2();
					return;
				}
		}


		//^ 카드
		else if ((p1_notshowed[p1_cardnum-1] == 5 && p2_notshowed[p2_cardnum-1] == 8)||(p1_notshowed[p1_cardnum-1] == 8 && p2_notshowed[p2_cardnum-1] == 5)) {
			//p2 카드를 p1한테 줌
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
				
				giveCardToP2();
				return;
			}
		}

		else if ((p1_notshowed[p1_cardnum-1] == 6 && p2_notshowed[p2_cardnum-1] == 7)||(p1_notshowed[p1_cardnum-1] == 7 && p2_notshowed[p2_cardnum-1] == 6)) {
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
			
				giveCardToP2();
				return;
			}
		}
		else if ((p1_notshowed[p1_cardnum-1] == 9 && p2_notshowed[p2_cardnum-1] != 5 && p2_notshowed[p2_cardnum-1] != 6 && p2_notshowed[p2_cardnum-1] != 7 && p2_notshowed[p2_cardnum-1] != 8 && p2_notshowed[p2_cardnum - 1] != 9)||(p2_notshowed[p2_cardnum-1] == 9 && p1_notshowed[p1_cardnum-1] != 5 && p1_notshowed[p1_cardnum-1] != 6 && p1_notshowed[p1_cardnum-1] != 7 && p1_notshowed[p1_cardnum-1] != 8 && p1_notshowed[p1_cardnum - 1] != 9)) {
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {

				giveCardToP2();
				return;
			}
		}

		//@ 카드
		else if ((p1_notshowed[p1_cardnum-1] == 10 && p2_notshowed[p2_cardnum-1] == 13)||(p1_notshowed[p1_cardnum-1] == 13 && p2_notshowed[p2_cardnum-1] == 10)) {
			//p2 카드를 p1한테 줌
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
				
				giveCardToP2();
				return;
			}
		}
		else if ((p1_notshowed[p1_cardnum-1] == 11 && p2_notshowed[p2_cardnum-1] == 12)||(p1_notshowed[p1_cardnum-1] == 12 && p2_notshowed[p2_cardnum-1] == 11)) {
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
			
				giveCardToP2();
				return;
			}
		}
		else if ((p1_notshowed[p1_cardnum-1] == 14 && p2_notshowed[p2_cardnum-1] != 10 && p2_notshowed[p2_cardnum-1] != 11 && p2_notshowed[p2_cardnum-1] != 12 && p2_notshowed[p2_cardnum-1] != 13 && p2_notshowed[p2_cardnum - 1] != 14)||(p2_notshowed[p2_cardnum-1] == 14 && p1_notshowed[p1_cardnum-1] != 10 && p1_notshowed[p1_cardnum-1] != 11 && p1_notshowed[p1_cardnum-1] != 12 && p1_notshowed[p1_cardnum-1] != 13 && p1_notshowed[p1_cardnum - 1] != 14)) {
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
			
				giveCardToP2();
				return;
			}
		}

		//& 카드
		else if ((p1_notshowed[p1_cardnum-1] == 15 && p2_notshowed[p2_cardnum-1] == 18)||(p1_notshowed[p1_cardnum-1] == 18 && p2_notshowed[p2_cardnum-1] == 15)) {
			//p2 카드를 p1한테 줌
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
			
				giveCardToP2();
				return;
			}
		}
		else if ((p1_notshowed[p1_cardnum-1] == 16 && p2_notshowed[p2_cardnum-1] == 17)||(p1_notshowed[p1_cardnum-1] == 17 && p2_notshowed[p2_cardnum-1] == 16)) {
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {
			
				giveCardToP2();
				return;
			}
		}
		else if ((p1_notshowed[p1_cardnum-1] == 19 && p2_notshowed[p2_cardnum-1] != 15 && p2_notshowed[p2_cardnum-1] != 16 && p2_notshowed[p2_cardnum-1] != 17 && p2_notshowed[p2_cardnum-1] != 18 && p2_notshowed[p2_cardnum-1]!=19)|| (p2_notshowed[p2_cardnum-1] == 19 && p1_notshowed[p1_cardnum-1] != 15 && p1_notshowed[p1_cardnum-1] != 16 && p1_notshowed[p1_cardnum-1] != 17 && p1_notshowed[p1_cardnum-1] != 18 && p1_notshowed[p1_cardnum - 1] != 19)) {
			if (player == 1) {
				giveCardToP1();
				return;
			}

			else {

				giveCardToP2();
				return;
			}
		}

		else {
			if (player == 1) {
				giveCardToP2();
				return;
			}

			else {

				giveCardToP1();
				return;
			}
		}

}

void giveCardToP1() {
	//p2가 준 카드 받기
	for (int i = 0; i < p2_cardnum; i++) {
		p1_card++;
		p1_notshowed[p1_card] = p2_notshowed[i];
	}
	//p1이 공개했던 카드 다시 맨뒤로 보내기
	for (int i = 0; i < p1_cardnum; i++) {
		p1_notshowed[p1_card+1+i] = p1_notshowed[i];
	}
	//p1공개했던 카드 배열에서 삭제
	for (int i = p1_cardnum ; i < p1_card; i++) {
		p1_notshowed[i - p1_cardnum] = p1_notshowed[i];
	}
	p1_cardnum = 0;
	//p2는 p1에게 준 카드 배열에서 삭제
	for (int i = p2_cardnum; i < p2_card; i++) {
		p2_notshowed[i - p2_cardnum] = p2_notshowed[i];
	}
	p2_card = p2_card - p2_cardnum;
	p2_cardnum = 0;

	gotoxy(3, 23);
	printf("                            ");
	gotoxy(3, 23);
	setColor(yellow, black);
	printf("p1이 카드를 얻었습니다.");
	setColor(white, black);
}

void giveCardToP2() {
	for (int i = 0; i < p1_cardnum; i++) {
		p2_card++;
		p2_notshowed[p2_card] = p1_notshowed[i];
	}
	//p2이 공개했던 카드 다시 맨뒤로 보내기
	for (int i = 0; i < p2_cardnum; i++) {
		p2_notshowed[p2_card+1+i] = p2_notshowed[i];
	}
	for (int i = p2_cardnum; i <= p2_card; i++) {
		p2_notshowed[i - p2_cardnum] = p2_notshowed[i];
	}
	p2_cardnum = 0;
	//p1은 p2에게 준 카드 배열에서 삭제
	for (int i = p1_cardnum; i <= p1_card; i++) {
		p1_notshowed[i - p1_cardnum] = p1_notshowed[i];

	}
	p1_card = p1_card - p1_cardnum;
	p1_cardnum = 0;

	gotoxy(61, 23);
	printf("                            ");
	gotoxy(61, 23);
	setColor(purple, black);
	printf("p2이 카드를 얻었습니다.");
	setColor(white, black);
}

//플레이어들의 남은 카드
void RestOfCard() {
	gotoxy(9, 10);
	printf("  ");
	gotoxy(9, 10);
	printf("%d", p1_card-p1_cardnum);
	gotoxy(25, 16);
	printf("%d", p1_cardnum);

	gotoxy(70, 10);
	printf("  ");
	gotoxy(70, 10);
	printf("%d", p2_card-p2_cardnum);
	gotoxy(86, 16);
	printf("%d", p2_cardnum);
}

//카드 다시 그리기 전 이전 그림 삭제
void cleanP1Card() {
	setColor(white, black);
	gotoxy(22, 8);
	printf(" ");
	gotoxy(27, 8);
	printf(" ");
	gotoxy(25, 10);
	printf(" ");
	gotoxy(22, 12);
	printf(" ");
	gotoxy(27, 12);
	printf(" ");
}

void cleanP2Card() {
	setColor(white, black);
	gotoxy(84, 8);
	printf(" ");
	gotoxy(89, 8);
	printf(" ");
	gotoxy(87, 10);
	printf(" ");
	gotoxy(84, 12);
	printf(" ");
	gotoxy(89, 12);
	printf(" ");

}


//뒤집혀진 카드 그리기
void drawCard(int cardnum, int player) {




	switch (cardnum) {
		//1개
	case 0: {

		if (player == 1) {
			cleanP1Card();
			setColor(blue, blue);
			gotoxy(25, 10);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(blue, blue);
			gotoxy(87, 10);
		}
		printf("%c", card[cardnum]);
		setColor(white, black);
		break;
	}
	case 5: {

		if (player == 1) {
			cleanP1Card();
			setColor(green, green);
			gotoxy(25, 10);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(green, green);
			gotoxy(87, 10);
		}
		printf("%c", card[cardnum]);
		setColor(white, black);
		break;
	}
	case 10: {

		if (player == 1) {
			cleanP1Card();
			setColor(red, red);
			gotoxy(25, 10);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(red, red);
			gotoxy(87, 10);
		}
		printf("%c", card[cardnum]);
		setColor(white, black);
		break;
	}
	case 15:
	{

		if (player == 1) {
			cleanP1Card();
			setColor(brown, brown);
			gotoxy(25, 10);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(brown, brown);
			gotoxy(87, 10);
		}
		printf("%c", card[cardnum]);
		setColor(white, black);
		break;
	}
	//2개
	case 1:
	{

		if (player == 1) {
			cleanP1Card();
			setColor(blue, blue);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(blue, blue);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	case 6: {

		if (player == 1) {
			cleanP1Card();
			setColor(green, green);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(green, green);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	case 11: {

		if (player == 1) {
			cleanP1Card();
			setColor(red, red);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(red, red);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	case 16:
	{

		if (player == 1) {
			cleanP1Card();
			setColor(brown, brown);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(brown, brown);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	//3개
	case 2: {

		if (player == 1) {
			cleanP1Card();
			setColor(blue, blue);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(blue, blue);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);

		}
		setColor(white, black);
		break;
	}
	case 7: {

		if (player == 1) {
			cleanP1Card();
			setColor(green, green);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(green, green);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);

		}
		setColor(white, black);
		break;
	}
	case 12:
	{

		if (player == 1) {
			cleanP1Card();
			setColor(red, red);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(red, red);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);

		}
		setColor(white, black);
		break;
	}
	case 17:
	{

		if (player == 1) {
			cleanP1Card();
			setColor(brown, brown);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(brown, brown);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);

		}
		setColor(white, black);
		break;
	}

	//4개
	case 3: {

		if (player == 1) {
			cleanP1Card();
			setColor(blue, blue);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(blue, blue);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}

	case 8: {

		if (player == 1) {
			cleanP1Card();
			setColor(green, green);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(green, green);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}

	case 13: {

		if (player == 1) {
			cleanP1Card();
			setColor(red, red);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(red, red);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}

	case 18:
	{

		if (player == 1) {
			cleanP1Card();
			setColor(brown, brown);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(brown, brown);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	//5개
	case 4: {

		if (player == 1) {
			cleanP1Card();
			setColor(blue, blue);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(blue, blue);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	case 9: {

		if (player == 1) {
			cleanP1Card();
			setColor(green, green);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(green, green);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	case 14: {

		if (player == 1) {
			cleanP1Card();
			setColor(red, red);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(red, red);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}
	case 19:
	{

		if (player == 1) {
			cleanP1Card();
			setColor(brown, brown);
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(27, 8);
			printf("%c", card[cardnum]);
			gotoxy(25, 10);
			printf("%c", card[cardnum]);
			gotoxy(22, 12);
			printf("%c", card[cardnum]);
			gotoxy(27, 12);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			cleanP2Card();
			setColor(brown, brown);
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(89, 8);
			printf("%c", card[cardnum]);
			gotoxy(87, 10);
			printf("%c", card[cardnum]);
			gotoxy(84, 12);
			printf("%c", card[cardnum]);
			gotoxy(89, 12);
			printf("%c", card[cardnum]);
		}
		setColor(white, black);
		break;
	}





	}

}
