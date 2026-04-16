#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include <mmsystem.h>
#include<conio.h>
void window_size(int width,int height) {
	SetConsoleTitle("Stone Paper Scissors By Reejul");
    HWND console=GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); 
    MoveWindow(console, r.left, r.top, width, height, TRUE);
    long style=GetWindowLong(console, GWL_STYLE);
    style&=~WS_MAXIMIZEBOX; 
    style&=~WS_THICKFRAME;  
    SetWindowLong(console,GWL_STYLE,style);
}
void set_font_size(int size) {
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.nFont=0;
    cfi.dwFontSize.X=0;   
    cfi.dwFontSize.Y=size;  
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_NORMAL;
    wcscpy(cfi.FaceName,L"Consolas");
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}
int main(){
	window_size(430, 300);
	set_font_size(24);
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	int user,computer,round,score,rounds,score2,i;
	char choice;
	
	mciSendString("open \"bg_music.mp3\" type mpegvideo alias bg_music", NULL, 0, NULL);
    mciSendString("open \"win.mp3\" type mpegvideo alias win_sound",NULL,0,NULL);
	mciSendString("open \"lose.mp3\" type mpegvideo alias lose_sound",NULL,0,NULL);
	mciSendString("open \"final_win.mp3\" type mpegvideo alias f_win",NULL,0,NULL);
	mciSendString("open \"final_lose.mp3\" type mpegvideo alias f_lose",NULL,0,NULL);
	mciSendString("open \"tie.mp3\" type mpegvideo alias tie_sound",NULL,0,NULL);
	mciSendString("open \"menu.mp3\" type mpegvideo alias menu_sound",NULL,0,NULL);
	mciSendString("open \"return_1.mp3\" type mpegvideo alias return_sound",NULL,0,NULL);
	
	do {score=0,score2=0;
	
	printf("LOADING ");
	SetConsoleTextAttribute(hConsole,9);
	
	printf("[=="); Sleep(400); printf("==="); Sleep(30); printf("=="); Sleep(30); printf("==="); 
	Sleep(400); printf("===="); Sleep(30); printf("=="); Sleep(400); printf("==="); Sleep(500); 
	printf("====]\n\n"); Sleep(1000);
	
	SetConsoleTextAttribute(hConsole,7);
	
	system("cls");
	mciSendString("play bg_music from 0 repeat", NULL, 0, NULL);
	Sleep(500);
	
	printf("Welcome to Stone Paper Scissors..\n");
	printf("Enter the number of rounds [Max: 30]: ");
	
	while (1) {
    if (scanf("%d",&rounds)==1){
        if (rounds>=1&&rounds<=30) {
        	while (getchar()!='\n'); 
            break;
        }else{
        	mciSendString("stop return_1.mp3", NULL, 0, NULL);
        	mciSendString("play return_1.mp3 from 0", NULL, 0, NULL);
        	SetConsoleTextAttribute(hConsole, 12); 
            printf("Please enter rounds from 1 to 30: ");
            while(getchar()!='\n'); 
            SetConsoleTextAttribute(hConsole, 7); 
        }
    } else {
        SetConsoleTextAttribute(hConsole, 12); 
        mciSendString("stop return_1.mp3", NULL, 0, NULL);
        mciSendString("play return_1.mp3 from 0", NULL, 0, NULL);
        printf("Only integers are allowed (from 1 to 30): ");
        while (getchar() != '\n'); 
        SetConsoleTextAttribute(hConsole, 7); 
    }
}

	mciSendString("stop menu_sound", NULL, 0, NULL);
	mciSendString("play menu.mp3 from 0", NULL, 0, NULL);
	
	for(round=1;round<=rounds;round++){
	SetConsoleTextAttribute(hConsole,2);
	printf("Press any key to continue...");
	getch();
	SetConsoleTextAttribute(hConsole,7);
	mciSendString("stop menu_sound", NULL, 0, NULL);
	mciSendString("play menu.mp3 from 0", NULL, 0, NULL);
	printf("\n");
	
	system("cls");
	
	SetConsoleTextAttribute(hConsole, 6);
	
    printf("="); Sleep(50); printf("="); Sleep(50); printf("="); Sleep(50); printf("=");Sleep(50);printf("="); Sleep(50); printf("="); 
	Sleep(50); printf("="); Sleep(50); printf("="); Sleep(50); printf(" "); Sleep(50); printf("R"); Sleep(50); printf("O"); 
	Sleep(50); printf("U"); Sleep(50); printf("N"); Sleep(50); printf("D"); Sleep(50); printf(" "); Sleep(50); printf("%d",round); 
	Sleep(50); printf(" "); Sleep(50); printf("="); Sleep(50); printf("="); Sleep(50); printf("="); Sleep(50); printf("="); 
	Sleep(50);	printf("="); Sleep(50); printf("="); Sleep(50); printf("="); Sleep(50); printf("="); Sleep(50);printf("="); 
	
	SetConsoleTextAttribute(hConsole, 7);
	
	printf("\n");
	
	printf("Enter 1 for stone, 2 for paper or 3 for scissors: ");
	while (1) {
    if (scanf("%d",&user)==1) {
        if (user>=1&&user<=3) {
        	while(getchar()!='\n'); 
            break;
        } else {
        	mciSendString("stop lose_sound", NULL, 0, NULL);
			mciSendString("play lose.mp3 from 0", NULL, 0, NULL);
        	SetConsoleTextAttribute(hConsole,12); 
            printf("Please enter 1, 2, or 3: ");
            while(getchar()!='\n'); 
            SetConsoleTextAttribute(hConsole, 7); 
        }
    } else {
        SetConsoleTextAttribute(hConsole,12); 
        mciSendString("stop lose_sound", NULL, 0, NULL);
		mciSendString("play lose.mp3 from 0", NULL, 0, NULL);
        printf("Only numbers allowed (1, 2 or 3): ");
        SetConsoleTextAttribute(hConsole,7); 
        mciSendString("play return_1.mp3 from 0", NULL, 0, NULL);
        while (getchar() != '\n'); 
    }
}
	printf("\n");
	mciSendString("stop menu_sound", NULL, 0, NULL);
	mciSendString("play menu.mp3 from 0", NULL, 0, NULL);

	computer=rand()%3+1;
    
    SetConsoleTextAttribute(hConsole,1);
    printf("Thinking");
    for(i=0;i<4;i++) {
    printf(".");
    Sleep(300);
}
    printf("\n");

    SetConsoleTextAttribute(hConsole,11);
    
    char* names[] = {"","Stone","Paper","Scissors"};
    printf("You chose: %s\n", names[user]);
    printf("I chose: %s\n\n", names[computer]);
    
    SetConsoleTextAttribute(hConsole,1);
    
    if (user==computer){
   	mciSendString("stop tie_sound", NULL, 0, NULL);
	mciSendString("play tie.mp3 from 0", NULL, 0, NULL);
	SetConsoleTextAttribute(hConsole, 3);
	printf("That is a tie!\n\n");
	SetConsoleTextAttribute(hConsole, 7);
	}
	else if ((user==1&&computer==3)||(user==2&&computer==1)||(user==3&&computer==2)){
		mciSendString("stop win_sound", NULL, 0, NULL);
		mciSendString("play win.mp3 from 0", NULL, 0, NULL);
		SetConsoleTextAttribute(hConsole, 10);
		printf("="); Sleep(100);printf("=");Sleep(100);printf("=");Sleep(100);printf("=");Sleep(100);
		printf("=");Sleep(100);printf(" Y");Sleep(100);printf("O");Sleep(100);printf("U");Sleep(100);
		printf(" ");Sleep(100);printf("W");Sleep(100);printf("I");Sleep(100);printf("N");Sleep(100);
		printf(" =");Sleep(100);printf("=");Sleep(100);printf("=");Sleep(100);printf("=");Sleep(100);
		printf("=\n\n");Sleep(100);
		SetConsoleTextAttribute(hConsole, 7);
		score++;
	}
	else{
		mciSendString("stop lose_sound", NULL, 0, NULL);
		mciSendString("play lose.mp3 from 0", NULL, 0, NULL);
		SetConsoleTextAttribute(hConsole, 12);
		printf("You lose!\n\n");
		SetConsoleTextAttribute(hConsole, 7);
		score2++;
	}
}
    
	Sleep(1000);
	printf("\n");
	
	system("cls");
	
	printf("=");Sleep(50);printf("=");Sleep(50);printf("=");Sleep(50);printf("= ");Sleep(50);
	printf("F");Sleep(50);printf("I");Sleep(50);printf("N");Sleep(50);printf("A");Sleep(50);
	printf("L");Sleep(50);printf(" ");Sleep(50);printf("S");Sleep(50);printf("C");Sleep(50);
	printf("O");Sleep(50);printf("R");Sleep(50);printf("E ");Sleep(50);printf("=");Sleep(50);
	printf("=");Sleep(50);printf("=");Sleep(50);printf("=");Sleep(50);
	
	printf("\n\n");
	Sleep(700);
	
	if(score>score2){
		mciSendString("play final_win.mp3 from 0", NULL, 0, NULL);
		SetConsoleTextAttribute(hConsole, 10);
		printf("You WIN! \n\nYou: %d \nMe: %d\n\n",score,score2);
		SetConsoleTextAttribute(hConsole, 7);
	} else if(score<score2){
		mciSendString("play final_lose.mp3 from 0", NULL, 0, NULL);
		SetConsoleTextAttribute(hConsole, 12);
		printf("You LOSE! \nYou: %d \nMe: %d\n\n",score,score2);
		SetConsoleTextAttribute(hConsole, 7);
	} else if(score==score2){
		mciSendString("play tie.mp3 from 0", NULL, 0, NULL);
		SetConsoleTextAttribute(hConsole, 11);
		printf("That's a TIE! \nYou: %d \nMe: %d\n\n",score,score2);
		SetConsoleTextAttribute(hConsole, 7);
	}

    SetConsoleTextAttribute(hConsole,7);
    printf("Press Y to play again or N to exit: ");
	scanf(" %c",&choice);
	mciSendString("stop menu_sound", NULL, 0, NULL);
	mciSendString("play menu.mp3 from 0", NULL, 0, NULL);
	while(getchar()!='\n');
	printf("\n");
	}while (choice=='y'||choice=='Y');
	
	Sleep(1000);

	printf("Thank you for playing!");
	printf("\n");
	Sleep(1000);
	
	SetConsoleTextAttribute(hConsole, 5);
	
	printf("M");Sleep(50);printf("A");Sleep(50);printf("D");Sleep(50);printf("E");Sleep(50);
	printf(" ");Sleep(50);printf("B");Sleep(50);printf("Y");Sleep(50);printf(" ");Sleep(50);
	printf("R");Sleep(50);printf("E");Sleep(50);printf("E");Sleep(50);printf("J");Sleep(50);
	printf("U");Sleep(50);printf("L");Sleep(50);printf(" ");Sleep(50);printf("K");Sleep(50);
	printf("A");Sleep(50);printf("N");Sleep(50);printf("T");Sleep(50);
	printf(" ");Sleep(50);printf("I");Sleep(50);printf("N");Sleep(50);printf(" ");Sleep(50);
	printf("D");Sleep(50);printf("E");Sleep(50);printf("V");Sleep(50);printf(" ");Sleep(50);
	printf("C");Sleep(50);printf("+");Sleep(50);printf("+");Sleep(50);printf(". ");Sleep(50);
	
	Sleep(1000);
	mciSendString("close all", NULL, 0, NULL);
	
	return 0;
}
