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
void giveCard();
void drawGame();
void playerKeyInput();
void RestOfCard();
void checkToGetCard(int);
void drawCard(int,int);

//전역 변수
//가지고 있는 카드 개수
int p1_card;
//종울렸나
int p1_ring;
//카드 뒤집었나
int p1_open = 0;
//처음에 할당 받은 카드
int p1_notshowed[30] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,1,2,3,4,5,6,7,8,9 };
//몇 번째까지 뒤집었나
int p1_cardnum = 0;
//뒤집은 카드
int p1_showed[30] = { 0 };


int p2_card;
int p2_ring;
int p2_open = 0;
int p2_notshowed[30] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,1,2,3,4,5,6,7,8,9 };
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
void setColor(int forground,int background){
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
	else if (temp == 65|| temp==97) return P1CARD;
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

	p1_card = 30;
	p2_card = 30;
	drawGame();
	playerKeyInput();


}

//플레이어들에게 카드 할당
void giveCard() {

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
	gotoxy(5,7);
	printf("┌─────┐");
	gotoxy(5, 8);
	printf("│     │");
	gotoxy(5, 9);
	printf("│     │");
	gotoxy(8, 9);
	printf("%d", p1_card);
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
	gotoxy(69, 9);
	printf("%d", p2_card);
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



//플레이어들 키 입력 시 변화
void playerKeyInput() {

	while (1) {


		if (p1_card == 0) {
			gotoxy(0, 20);
			printf("p1의 카드가 모두 소진되었습니다. p2의 승리입니다.");
			Sleep(2000);
			break;

		}
		else if (p2_card == 0) {
			gotoxy(0, 20);
			printf("p2의 카드가 모두 소진되었습니다. p1의 승리입니다.");
			Sleep(2000);
			break;

		}

		int key = keyControl();
		if (key == EXIT) {
			break;
		}
		else if (key == P1RING) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("d입력 p1이 종을 울렸다.");
			checkToGetCard(1);
		}
		else if (key == P1CARD && p1_open==0) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("a입력 p1이 카드를 뒤집었다.");
			drawCard(p1_notshowed[p1_cardnum], 1);
			p1_open = 1;
			p1_cardnum++;
			p1_card--;
		}
		else if (key == P2CARD && p2_open==0) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("4입력 p2이 카드를 뒤집었다.");
			drawCard(p2_notshowed[p2_cardnum], 2);
			p2_open = 1;
			p2_cardnum++;
			p2_card--;
		}
		else if (key == P2RING) {
			gotoxy(0, 20);
			printf("                            ");
			gotoxy(0, 20);
			printf("6입력 p2이 종을 울렸다.");
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
	if (player == 1) {
		if (p1_notshowed[p1_cardnum] == 1) {
			if (p2_notshowed[p2_cardnum] == 4) {
				//p2 카드를 p1한테 줌
			}
			else {
				//틀렸으니 p1 카드를 p2한테 줌
			}
		}
	}

}

//플레이어들의 남은 카드
void RestOfCard() {
	gotoxy(8,9);
	printf("  ");
	gotoxy(8, 9);
	printf("%d", p1_card);
	gotoxy(69,9);
	printf("  ");
	gotoxy(69, 9);
	printf("%d", p2_card);
}

//뒤집혀진 카드 그리기
void drawCard(int cardnum, int player) {




	switch (cardnum) {
		//1개
	case 0:
	case 5:
	case 10:
	case 15:
	{
		if (player == 1) {
			gotoxy(22, 8);
			printf("   ");
			gotoxy(22, 9);
			printf("   ");
			gotoxy(22, 10);
			printf("   ");
			gotoxy(23, 9);
		}
		else if(player==2) {
			gotoxy(84, 8);
			printf("   ");
			gotoxy(84, 9);
			printf("   ");
			gotoxy(84, 10);
			printf("   ");
			gotoxy(85,9);
		}
		printf("%c",card[cardnum]);

	}
	break;
	//2개
	case 1: 
	case 6:
	case 11:
	case 16:
	{
		if (player == 1) {
			gotoxy(22, 8);
			printf("   ");
			gotoxy(22, 9);
			printf("   ");
			gotoxy(22, 10);
			printf("   ");
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(24,10);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			gotoxy(84, 8);
			printf("   ");
			gotoxy(84, 9);
			printf("   ");
			gotoxy(84, 10);
			printf("   ");
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(86, 10);
			printf("%c", card[cardnum]);
		}

	}break;

	case 2:
	case 7:
	case 12:
	case 17:
	{
		if (player == 1) {
			gotoxy(22, 8);
			printf("   ");
			gotoxy(22, 9);
			printf("   ");
			gotoxy(22, 10);
			printf("   ");
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(23, 9);
			printf("%c", card[cardnum]);
			gotoxy(24, 10);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			gotoxy(84, 8);
			printf("   ");
			gotoxy(84, 9);
			printf("   ");
			gotoxy(84, 10);
			printf("   ");
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(85, 9);
			printf("%c", card[cardnum]);
			gotoxy(86, 10);
			printf("%c", card[cardnum]);

		}

	}break;
	case 3:
	case 8:
	case 13:
	case 18:
	{
		if (player == 1) {
			gotoxy(22, 8);
			printf("   ");
			gotoxy(22, 9);
			printf("   ");
			gotoxy(22, 10);
			printf("   ");
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(24, 8);
			printf("%c", card[cardnum]);
			gotoxy(22, 10);
			printf("%c", card[cardnum]);
			gotoxy(24, 10);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			gotoxy(84, 8);
			printf("   ");
			gotoxy(84, 9);
			printf("   ");
			gotoxy(84, 10);
			printf("   ");
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(86, 8);
			printf("%c", card[cardnum]);
			gotoxy(84, 10);
			printf("%c", card[cardnum]);
			gotoxy(86, 10);
			printf("%c", card[cardnum]);
		}
	}
	break;
	case 4:
	case 9:
	case 14:
	case 19:
	{
		if (player == 1) {
			gotoxy(22, 8);
			printf("   ");
			gotoxy(22, 9);
			printf("   ");
			gotoxy(22, 10);
			printf("   ");
			gotoxy(22, 8);
			printf("%c", card[cardnum]);
			gotoxy(24, 8);
			printf("%c", card[cardnum]);
			gotoxy(23, 9);
			printf("%c", card[cardnum]);
			gotoxy(22, 10);
			printf("%c", card[cardnum]);
			gotoxy(24, 10);
			printf("%c", card[cardnum]);
		}
		else if (player == 2) {
			gotoxy(84, 8);
			printf("   ");
			gotoxy(84, 9);
			printf("   ");
			gotoxy(84, 10);
			printf("   ");
			gotoxy(84, 8);
			printf("%c", card[cardnum]);
			gotoxy(86, 8);
			printf("%c", card[cardnum]);
			gotoxy(85, 9);
			printf("%c", card[cardnum]);
			gotoxy(84, 10);
			printf("%c", card[cardnum]);
			gotoxy(86, 10);
			printf("%c", card[cardnum]);
		}
	}
	break;




	}

}
