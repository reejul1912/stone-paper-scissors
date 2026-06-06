/* 
(c) Reejul Kant, 2026
Just a little project made by me.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

#define BLUE            1   
#define GREEN           2    
#define CYAN            3    
#define PURPLE          5  
#define GOLD            6   
#define WHITE           7   
#define LIGHT_BLUE      9  
#define LIGHT_GREEN    10  
#define LIGHT_CYAN     11 
#define RED            12  

#pragma comment(lib, "winmm.lib")

static void play_sound(const char* alias)
{
    char stop_cmd[20], play_cmd[20];
    sprintf(stop_cmd, "stop %s", alias);
    sprintf(play_cmd, "play %s from 0", alias);
    mciSendString(stop_cmd, NULL, 0, NULL);
    mciSendString(play_cmd, NULL, 0, NULL);
}

static void window_size() // this was the hard part, I referred to microsofts's documentation and stackoverflow for this
{
    SetConsoleTitle("Stone - Paper - Scissors!");
    HANDLE win_size = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 58, 17};  
    COORD bufferSize = {58, 17};
    SetConsoleScreenBufferSize(win_size, bufferSize);
    SetConsoleWindowInfo(win_size, TRUE, &windowSize);
    HWND console = GetConsoleWindow();
    long style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_THICKFRAME;
    SetWindowLong(console, GWL_STYLE, style);
}

static void load_font_size_colour(int size)  // setting a fixed font size
{
    HANDLE text = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;   
    cfi.dwFontSize.Y = size;  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(text, FALSE, &cfi);
}

static void audio_init() // loading all sounds
{
    mciSendString("open \"bg_music.mp3\" type mpegvideo alias bg_music", NULL, 0, NULL);
    mciSendString("open \"win.mp3\" type mpegvideo alias win_sound", NULL, 0, NULL);
    mciSendString("open \"lose.mp3\" type mpegvideo alias lose_sound", NULL, 0, NULL);
    mciSendString("open \"final_win.mp3\" type mpegvideo alias f_win", NULL, 0, NULL);
    mciSendString("open \"final_lose.mp3\" type mpegvideo alias f_lose", NULL, 0, NULL);
    mciSendString("open \"tie.mp3\" type mpegvideo alias tie_sound", NULL, 0, NULL);
    mciSendString("open \"menu.mp3\" type mpegvideo alias menu_sound", NULL, 0, NULL);
    mciSendString("open \"return_1.mp3\" type mpegvideo alias return_sound", NULL, 0, NULL);
}

static void loading_bar() // loading bar animation using loop
{
    HANDLE text = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(text, LIGHT_BLUE);
    printf("\n\n\n\n\n\t   LOADING [");
    const char* loading = "========================]";
    int loadSize = strlen(loading);
    
    for(int i = 0; i < loadSize; i++)
    {
        printf("%c", loading[i]);
        Sleep(50);
    }
    printf("\n");
}

static void print_game_menu() 
{
    HANDLE text = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(text, LIGHT_BLUE);
    printf("\t\t     ____  ____   ____ \n");
    printf("\t\t    / ___||  _ \\ / ___|\n");
    printf("\t\t    \\___ \\| |_) |\\___ \\\n");
    printf("\t\t     ___) |  __/  ___) |\n");
    printf("\t\t    |____/|_|    |____/ \n\n");
    
    SetConsoleTextAttribute(text, LIGHT_GREEN);
    printf("\t\t    Stone Paper Scissors\n");
    
    SetConsoleTextAttribute(text, GOLD);
    printf(
        "      _______          _______            _______\n"
        "   ---'   ____)    ---'   ____)____   ---'   ____)____\n"
        "         (_____)             ______)            ______)\n"
        "         (_____)             _______)        __________)\n"
        "         (____)             _______)        (____)\n"
        "   ---.__(___)     ---.__________)    ---.__(___)\n"
    );
    
    SetConsoleTextAttribute(text, CYAN);
    printf("\n\t           [Press any key to play]");
    
    SetConsoleTextAttribute(text, WHITE);
    printf("\n\n\t       Version 1.3 [Made by Reejul Kant]");
    getch();
    
    play_sound("menu_sound");
    system("cls");
}

static void show_round(int current_round)
{
    char show_round_num[30];
    sprintf(show_round_num, " ======== ROUND %d ========", current_round);
    
    for(int i = 0; show_round_num[i] != '\0'; i++)
    {
        printf("%c", show_round_num[i]);
        fflush(stdout);
        Sleep(30);
    }
    printf("\n\n");
}

static void win_animation()
{
    const char* win = " ===== YOU WIN! =====";    
    int win_len = strlen(win);
    
    for(int i = 0; i < win_len; i++)
    {
        printf("%c", win[i]);
        fflush(stdout);
        Sleep(40);
    }
    printf("\n\n");
}

static void final_score_animation()
{
    const char* final = " ===== FINAL SCORE =====";
    int final_len = strlen(final);
    
    for(int i = 0; i < final_len; i++)
    {
        printf("%c", final[i]);
        fflush(stdout);
        Sleep(40);
    }
}

int main(void)
{
    HANDLE text = GetStdHandle(STD_OUTPUT_HANDLE);
    window_size();
    load_font_size_colour(24);
    srand(time(NULL));
    audio_init();
    
    int user = 0, computer = 0, total_rounds = 0, score = 0, current_round = 0, score2 = 0;
    char choice;
    
    do 
    {   
        score = 0; score2 = 0;
        loading_bar();
    
        SetConsoleTextAttribute(text, WHITE);
        system("cls");
        mciSendString("play bg_music from 0 repeat", NULL, 0, NULL);
        Sleep(500);
    
        print_game_menu();

        printf(" ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n");
        printf(" How many rounds would you like to play? [1 - 50]: ");
    
        while (1) 
        {
            if (scanf("%d", &total_rounds) == 1 && (total_rounds >= 1 && total_rounds <= 50)) 
            {
                break;
            } 
            else 
            {
                SetConsoleTextAttribute(text, RED); 
                play_sound("return_sound");
                printf(" Please enter the number of rounds between 1 and 50! ");
                while (getchar() != '\n'); 
                SetConsoleTextAttribute(text, WHITE); 
            }
        }

        play_sound("menu_sound");
    
        for(current_round = 1; current_round <= total_rounds; current_round++) 
        {
            SetConsoleTextAttribute(text, GREEN);
            printf(" Okay! Press any key to continue...");
            getch();
            SetConsoleTextAttribute(text, WHITE);
            play_sound("menu_sound");
            printf("\n");
    
            system("cls");
    
            SetConsoleTextAttribute(text, GOLD);
            show_round(current_round);
    
            SetConsoleTextAttribute(text, WHITE);
            printf(" [1] Stone \n [2] Paper \n [3] Scissors\n Enter respective number: ");
            
            while (1) 
            {
                if (scanf("%d", &user) == 1 && (user >= 1 && user <= 3)) 
                { 
                    break;
                } 
                else 
                {
                    SetConsoleTextAttribute(text, RED); 
                    play_sound("lose_sound");
                    printf(" Please enter 1, 2 or 3! "); 
                    play_sound("return_sound");
                    while (getchar() != '\n'); 
                }
            }
            
            printf("\n");
            play_sound("menu_sound");

            computer = rand() % 3 + 1;
    
            SetConsoleTextAttribute(text, BLUE);
            printf(" Thinking");
            for(int i = 0; i < 4; i++) 
            {
                printf(".");
                Sleep(300);
            }
            printf("\n\n");

            SetConsoleTextAttribute(text, LIGHT_CYAN);
            const char* names[] = {"", "Stone", "Paper", "Scissors"};
            printf(" You chose: %s\n", names[user]);
            printf(" I chose: %s\n\n", names[computer]);
    
            if (user == computer)
            {
                play_sound("tie_sound");
                SetConsoleTextAttribute(text, CYAN);
                printf(" That is a tie!\n\n");
                SetConsoleTextAttribute(text, WHITE);
            }
            else if ((user == 1 && computer == 3) || (user == 2 && computer == 1) || (user == 3 && computer == 2))
            {
                play_sound("win_sound");
                SetConsoleTextAttribute(text, LIGHT_GREEN);
                win_animation();
                SetConsoleTextAttribute(text, WHITE);
                score++;
            }
            else 
            {
                play_sound("lose_sound");
                SetConsoleTextAttribute(text, RED);
                printf(" YOU LOSE!\n\n");
                SetConsoleTextAttribute(text, WHITE);
                score2++;
            }
        }
        
        Sleep(1000);
        system("cls");
    
        SetConsoleTextAttribute(text, GOLD);
        final_score_animation();
    
        if(score > score2) 
        {
            play_sound("f_win");
            SetConsoleTextAttribute(text, LIGHT_GREEN);
            printf("\n\n You WIN! \n You: %d \n Me: %d\n\n", score, score2);
        } 
        else if(score < score2) 
        {
            play_sound("f_lose");
            SetConsoleTextAttribute(text, RED);
            printf("\n\n You LOSE! \n You: %d \n Me: %d\n\n", score, score2);
        }
        else 
        {
            play_sound("tie_sound");
            SetConsoleTextAttribute(text, LIGHT_CYAN);
            printf("\n\n That's a TIE! \n You: %d \n Me: %d\n\n", score, score2);
        }
        
        SetConsoleTextAttribute(text, WHITE);
        printf(" ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n");
        printf(" Enter Y to play again or N to exit: ");
        scanf(" %c", &choice);
        play_sound("menu_sound");
        while(getchar() != '\n');
        printf("\n");
        
    } while (choice == 'y' || choice == 'Y');
    
    Sleep(500);
    SetConsoleTextAttribute(text, CYAN);
    printf("Thank you for playing!\n");
    
    Sleep(1500);
    mciSendString("close all", NULL, 0, NULL);
    
    return 0;
}
