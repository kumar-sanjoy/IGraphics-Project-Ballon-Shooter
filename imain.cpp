#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#include "stdlib.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define playerNameLength 20
#define textBoxWidth 300
#define textBoxHeight 80
#define color1 (0, 0, 200);    // // blue
#define color2 (0, 200, 0);    // // green
#define color3 (200, 0, 0);    // // red
#define color4 (60, 200, 110); // // malachite
#define color5 (140, 140, 30); // // olive

#define youCanMissOnEasy 14
#define youCanMissOnMedium 24
#define youCanMissOnHard 39

int maxPlayTime = 60; // // playtime in seconds

char playerName[playerNameLength + 1] = "";
typedef struct
{
    int easy;
    int medium;
    int hard;
} missedBallon;
missedBallon ballonMissed = {0, 0, 0};

bool isTextBoxActive = 0;
int timerCall = 0, timeCount = 0; // // for timer
int gameOverPage = 0;
bool soundOn = true;
bool ballonPopSound = false;

// gloabal variables: (mostly balloon's co ordinates)
// int playerX = 0, playerY = 0;
float bal1x = 200, bal1y = 0, radius1 = 20;
float bal2x = 500, bal2y = 0, radius2 = 22;
float bal3x = 800, bal3y = 0, radius3 = 24;
float bal4x = 600, bal4y = 0, radius4 = 21;
float bal5x = 400, bal5y = 0, radius5 = 25;

int score = 0;
int mouseClickX, mouseClickY;

// function prototypes:
void drawHomePage();
int homePage = 1;

void drawStartPage();
int startPage = 0;
void startPageClickHandler();

void drawInstructionsPage();
int instructionsPage = 0;
void instructionsPageClickHandler();

void drawCreditsPage();
int creditsPage = 0;
void creditsPageClickHandler();

void drawScorePage();
int scorePage = 0;
void scorePageClickHandler();

void backButtonClickHandler();
void backButtonToStartPageHandler();

void drawEasyPage();
int easyPage = 0;
void easyPageClickHandler();

void drawMediumPage();
int mediumPage = 0;
void mediumPageClickHandler();

void drawHardPage();
int hardPage = 0;
void hardPageClickHandler();

void collision1(int, int);
void collision2(int, int);
void collision3(int, int);
void collision4(int, int);
void collision5(int, int);

void drawGameOverPage();
void gameOverHandler();

void timeCounter();
void drawScoreNRemainingTime();
void saveScore();
void loadScore();

/*
    function iDraw() is called again and again by the system.
*/
void iDraw()
{

    iClear();

    if (homePage == 1)
        drawHomePage();
    else if (startPage == 1)
        drawStartPage();
    else if (instructionsPage == 1)
        drawInstructionsPage();
    else if (creditsPage == 1)
        drawCreditsPage();
    else if (easyPage == 1)
    {
        drawEasyPage();
        timerCall = 1;
    }
    else if (mediumPage == 1)
        drawMediumPage();
    else if (hardPage == 1)
        drawHardPage();
    else if (scorePage == 1)
        drawScorePage();
    else if (gameOverPage == 1)
        drawGameOverPage();
}

/*
    function iMouseMove() is called when the user presses and drags the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouseMove(int mx, int my)
{
    // printf("x = %d, y= %d\n", mx, my);
    // place your codes here
}

/*
    function iMouse() is called when the user presses/releases the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouse(int button, int state, int mx, int my)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseClickX = mx, mouseClickY = my;
        // printf("%d %d\n", mouseClickX, mouseClickY);
        // printf("score: %d\n", score);
        // projectile and collition
        if (homePage == 1 && (mx > 415 && mx < 585) && (my > 500 && my < 566))
            startPageClickHandler();
        else if (homePage == 1 && (mx > 415 && mx < 585) && (my > 400 && my < 466))
            instructionsPageClickHandler();
        else if (homePage == 1 && (mx > 415 && mx < 585) && (my > 300 && my < 366))
            creditsPageClickHandler();
        else if (homePage == 1 && (mx > 415 && mx < 585) && (my > 200 && my < 266))
            scorePageClickHandler();
        else if ((startPage == 1 || instructionsPage == 1 || creditsPage == 1 || scorePage == 1) && (mx >= 830 && mx <= 1000) && (my > 534 && my <= 600))
            backButtonClickHandler();
        else if (startPage == 1 && (mx > 415 && mx < 585) && (my > 400 && my < 466))
        {
            score = 0;
            easyPageClickHandler();
        }
        else if (startPage == 1 && (mx > 415 && mx < 585) && (my > 300 && my < 366))
        {
            score = 0;
            mediumPageClickHandler();
        }
        else if (startPage == 1 && (mx > 415 && mx < 585) && (my > 200 && my < 266))
        {
            score = 0;
            hardPageClickHandler();
        }
        else if ((easyPage == 1 || mediumPage == 1 || hardPage == 1) && (mx >= 0 && mx <= 170) && (my > 534 && my <= 600))
            backButtonToStartPageHandler();
        else if (gameOverPage == 1)
        {
            gameOverHandler();
            if ((mx > 400 && mx < 700) && (my > 200 && my < 280))
                isTextBoxActive = true;
            else if (mx > 830 && mx < 1000 && my > 0 && my < 60)
            {
                backButtonClickHandler();
                // // strcpy(playerName, "");
            }
        }
    }
}

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
    */
void iKeyboard(unsigned char key)
{
    if (isTextBoxActive)
    {
        if (key == '\r')
            isTextBoxActive = false;
        else if (key == '\b')
        {
            int len = strlen(playerName);
            if (len > 0)
                playerName[len - 1] = '\0';
        }
        else if (strlen(playerName) < playerNameLength)
        {
            const char ch = (char)key;
            strncat(playerName, &ch, 1);
            // printf("%s\n", playerName);
        }
    }
    if (key == 'q')
        exit(0);
    else if (key == 'm' && (easyPage == 1 || mediumPage == 1 || hardPage == 1))
    {
        if (soundOn)
        {
            soundOn = false;
            PlaySound(0, 0, 0);
        }
        else if (!soundOn)
        {
            soundOn = true;
            PlaySound(TEXT("sounds\\menumusic.wav"), NULL, SND_ASYNC);
        }
    }
    // // b to turn on balloon pop sound
    else if (key == 'b' && (easyPage == 1 || mediumPage == 1 || hardPage == 1))
    {
        if (ballonPopSound)
        {
            ballonPopSound = false;
            PlaySound(0, 0, 0);
        }
        else
        {
            ballonPopSound = true;
            PlaySound(TEXT("sounds\\popSound.wav"), NULL, SND_ASYNC);
        }
    }
    // place your codes for other keys here
}

/*
    function iSpecialKeyboard() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
    */
void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
    // place your codes for other keys here
}
void collision1(int mouseX, int mouseY)
{
    int distance = (mouseX - bal1x) * (mouseX - bal1x) + (mouseY - bal1y) * (mouseY - bal1y);
    if (distance <= radius1 * radius1)
    {
        bal1y = 0;
        score += radius1;
        bal1x = 100 + rand() % 700;
        mouseClickX = 1100, mouseClickY = 700; // to avoid the double click functionality
        if (ballonPopSound)
        {
            ballonPopSound = true;
            PlaySound(TEXT("sounds\\popSound.wav"), NULL, SND_ASYNC);
        }
    }
}
void collision2(int mouseX, int mouseY)
{
    int distance = (mouseX - bal2x) * (mouseX - bal2x) + (mouseY - bal2y) * (mouseY - bal2y);
    if (distance <= radius2 * radius2)
    {
        bal2y = 0;
        score += radius2;
        bal2x = 200 + rand() % 700;
        mouseClickX = 1100, mouseClickY = 700;
        if (ballonPopSound)
        {
            ballonPopSound = true;
            PlaySound(TEXT("sounds\\popSound.wav"), NULL, SND_ASYNC);
        }
    }
}
void collision3(int mouseX, int mouseY)
{
    int distance = (mouseX - bal3x) * (mouseX - bal3x) + (mouseY - bal3y) * (mouseY - bal3y);
    if (distance <= radius3 * radius3)
    {
        bal3y = 0;
        score += radius3;
        bal3x = 150 + rand() % 800;
        mouseClickX = 1100, mouseClickY = 700;
        if (ballonPopSound)
        {
            ballonPopSound = true;
            PlaySound(TEXT("sounds\\popSound.wav"), NULL, SND_ASYNC);
        }
    }
}
void collision4(int mouseX, int mouseY)
{
    int distance = (mouseX - bal4x) * (mouseX - bal4x) + (mouseY - bal4y) * (mouseY - bal4y);
    if (distance <= radius4 * radius4)
    {
        bal4y = 0;
        score += radius4;
        bal4x = 120 + rand() % 700;
        mouseClickX = 1100, mouseClickY = 700; // to avoid the double click functionality
        if (ballonPopSound)
        {
            ballonPopSound = true;
            PlaySound(TEXT("sounds\\popSound.wav"), NULL, SND_ASYNC);
        }
    }
}
void collision5(int mouseX, int mouseY)
{
    int distance = (mouseX - bal5x) * (mouseX - bal5x) + (mouseY - bal5y) * (mouseY - bal5y);
    if (distance <= radius5 * radius5)
    {
        bal5y = 0;
        score += radius5;
        bal5x = 240 + rand() % 700;
        mouseClickX = 1100, mouseClickY = 700; // to avoid the double click functionality
        if (ballonPopSound)
        {
            ballonPopSound = true;
            PlaySound(TEXT("sounds\\popSound.wav"), NULL, SND_ASYNC);
        }
    }
}

// // drawing pages:
void drawHomePage()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, 1000, 600);
    iShowBMP(0, 0, "images\\homePage.bmp");
    iShowBMP(415, 500, "images\\button1.bmp");
    iShowBMP(415, 400, "images\\button1.bmp");
    iShowBMP(415, 300, "images\\button1.bmp");
    iShowBMP(415, 200, "images\\button1.bmp");
    iSetColor(255, 255, 255);
    iText(475, 525, "Play", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(438, 425, "Instructions", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(460, 325, "Credits", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(470, 225, "Score", GLUT_BITMAP_TIMES_ROMAN_24);
}
void drawStartPage()
{
    iFilledRectangle(0, 0, 1000, 600);
    iSetColor(0, 255, 0);
    iShowBMP(0, 0, "images\\startPage.bmp");
    iShowBMP(415, 500, "images\\button1.bmp");
    iShowBMP(415, 400, "images\\button1.bmp");
    iShowBMP(415, 300, "images\\button1.bmp");
    iShowBMP(415, 200, "images\\button1.bmp");
    iSetColor(255, 255, 255);
    iText(470, 525, "Select", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(475, 425, "Easy", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(460, 325, "Medium", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(475, 225, "Hard", GLUT_BITMAP_TIMES_ROMAN_24);
    iShowBMP(830, 534, "images\\backButton.bmp");
}
void drawInstructionsPage()
{
    iFilledRectangle(0, 0, 1000, 600);
    iShowBMP(0, 0, "images\\instructionsPage.bmp");
    iShowBMP(830, 534, "images\\backButton.bmp");
}
void drawCreditsPage()
{
    iFilledRectangle(0, 0, 1000, 600);
    iShowBMP(0, 0, "images\\creditsPage.bmp");
    iShowBMP(830, 534, "images\\backButton.bmp");
}
void drawScorePage()
{
    iSetColor(208, 255, 250);
    iShowBMP(0, 0, "images\\scorePage.bmp");
    iShowBMP(830, 534, "images\\backButton.bmp");
    iSetColor(255, 255, 255);
    loadScore();
}
// drawing balloon 1:
void drawbal1(double x, double y, double rad, int slice)
{
    iSetColor color1
        iFilledCircle(x, y, rad, slice);
    iLine(x, y, x, y - 4 * rad); // // the balloon ribbon
    iSetColor(255, 255, 255);
    char balloonPoint[10];
    sprintf(balloonPoint, "%.0lf", rad);
    iText(x - 10, y - 8, balloonPoint, GLUT_BITMAP_TIMES_ROMAN_24);
    collision1(mouseClickX, mouseClickY);
}
// drawing balloon 2:
void drawbal2(double x, double y, double rad, int slice)
{
    iSetColor color2
        iFilledCircle(x, y, rad, slice);
    iLine(x, y, x, y - 4 * rad); // // the balloon ribbon
    iSetColor(255, 255, 255);
    char balloonPoint[10];
    sprintf(balloonPoint, "%.0lf", rad);
    iText(x - 10, y - 8, balloonPoint, GLUT_BITMAP_TIMES_ROMAN_24);
    collision2(mouseClickX, mouseClickY);
}
// drawing balloon 3:
void drawbal3(double x, double y, double rad, int slice)
{
    iSetColor color3
        iFilledCircle(x, y, rad, slice);
    iLine(x, y, x, y - 4 * rad); // // the balloon ribbon
    iSetColor(255, 255, 255);
    char balloonPoint[10];
    sprintf(balloonPoint, "%.0lf", rad);
    iText(x - 10, y - 8, balloonPoint, GLUT_BITMAP_TIMES_ROMAN_24);
    collision3(mouseClickX, mouseClickY);
}
// drawing balloon 4:
void drawbal4(double x, double y, double rad, int slice)
{
    iSetColor color4
        iFilledCircle(x, y, rad, slice);
    iLine(x, y, x, y - 4 * rad); // // the balloon ribbon
    iSetColor(255, 255, 255);
    char balloonPoint[10];
    sprintf(balloonPoint, "%.0lf", rad);
    iText(x - 10, y - 8, balloonPoint, GLUT_BITMAP_TIMES_ROMAN_24);
    collision4(mouseClickX, mouseClickY);
}
// drawing balloon 5:
void drawbal5(double x, double y, double rad, int slice)
{
    iSetColor color5
        iFilledCircle(x, y, rad, slice);
    iLine(x, y, x, y - 4 * rad); // // the balloon ribbon
    iSetColor(255, 255, 255);
    char balloonPoint[10];
    sprintf(balloonPoint, "%.0lf", rad);
    iText(x - 10, y - 8, balloonPoint, GLUT_BITMAP_TIMES_ROMAN_24);
    collision5(mouseClickX, mouseClickY);
}
void drawEasyPage()
{
    iResumeTimer(0); // // timer resume here to turn on counting
    iFilledRectangle(0, 0, 1000, 600);
    iShowBMP(0, 0, "images\\easyPage.bmp");
    iShowBMP(0, 534, "images\\backButton.bmp");
    drawScoreNRemainingTime();
    iText(856, 530, "Missed:", GLUT_BITMAP_TIMES_ROMAN_24);
    char noOfBallonMissed[10];
    itoa(ballonMissed.easy, noOfBallonMissed, 10);
    iText(940, 530, noOfBallonMissed, GLUT_BITMAP_TIMES_ROMAN_24);

    // 3 ball drawing.
    drawbal1(bal1x, bal1y, radius1, 100);
    bal1y += 1.5;
    if (bal1y >= 600)
    {
        ballonMissed.easy++;
        bal1y = 0;
        bal1x = 100 + rand() % 700;
    }
    drawbal2(bal2x, bal2y, radius2, 100);
    bal2y += 2.2;
    if (bal2y >= 600)
    {
        ballonMissed.easy++;
        bal2y = 0;
        bal2x = 200 + rand() % 700;
    }
    drawbal3(bal3x, bal3y, radius3, 100);
    bal3y += 3;
    if (bal3y >= 600)
    {
        ballonMissed.easy++;
        bal3y = 0;
        bal3x = 150 + rand() % 750;
    }
}
void drawMediumPage()
{
    iResumeTimer(0); // // timer resume here to turn on counting

    iFilledRectangle(0, 0, 1000, 600);
    iSetColor(0, 255, 255);
    iFilledRectangle(0, 0, 1000, 600);
    iShowBMP(0, 0, "images\\mediumPage.bmp");
    iShowBMP(0, 534, "images\\backButton.bmp");
    drawScoreNRemainingTime();
    iText(856, 530, "Missed:", GLUT_BITMAP_TIMES_ROMAN_24);
    char noOfBallonMissed[10];
    itoa(ballonMissed.medium, noOfBallonMissed, 10);
    iText(940, 530, noOfBallonMissed, GLUT_BITMAP_TIMES_ROMAN_24);

    // 3 ball drawing.we
    drawbal1(bal1x, bal1y, radius1, 100);
    bal1y += 1.5;
    if (bal1y >= 600)
    {
        ballonMissed.medium++;
        bal1y = 0;
        bal1x = 100 + rand() % 700;
    }
    drawbal2(bal2x, bal2y, radius2, 100);
    bal2y += 2.2;
    if (bal2y >= 600)
    {
        ballonMissed.medium++;
        bal2y = 0;
        bal2x = 200 + rand() % 700;
    }
    drawbal3(bal3x, bal3y, radius3, 100);
    bal3y += 3;
    if (bal3y >= 600)
    {
        ballonMissed.medium++;
        bal3y = 0;
        bal3x = 150 + rand() % 750;
    }
    drawbal4(bal4x, bal4y, radius4, 100);
    bal4y += 3.8;
    if (bal4y >= 600)
    {
        ballonMissed.medium++;
        bal4y = 0;
        bal4x = 150 + rand() % 750;
    }
}
void drawHardPage()
{
    iResumeTimer(0); // // timer resume here to turn on counting
    iFilledRectangle(0, 0, 1000, 600);
    iSetColor(0, 255, 255);
    iFilledRectangle(0, 0, 1000, 600);
    iSetColor(0, 255, 255);
    iFilledRectangle(0, 0, 1000, 600);
    iShowBMP(0, 0, "images\\hardPage.bmp");
    iShowBMP(0, 534, "images\\backButton.bmp");
    iSetColor(0, 0, 0);
    drawScoreNRemainingTime();
    iText(856, 530, "Missed:", GLUT_BITMAP_TIMES_ROMAN_24);
    char noOfBallonMissed[10];
    itoa(ballonMissed.hard, noOfBallonMissed, 10);
    iText(940, 530, noOfBallonMissed, GLUT_BITMAP_TIMES_ROMAN_24);

    // 3 ball drawing.
    drawbal1(bal1x, bal1y, radius1, 100);
    bal1y += 1.5;
    if (bal1y >= 600)
    {
        ballonMissed.hard++;
        bal1y = 0;
        bal1x = 100 + rand() % 700;
    }
    drawbal2(bal2x, bal2y, radius2, 100);
    bal2y += 2.2;
    if (bal2y >= 600)
    {
        ballonMissed.hard++;
        bal2y = 0;
        bal2x = 200 + rand() % 700;
    }
    drawbal3(bal3x, bal3y, radius3, 100);
    bal3y += 3;
    if (bal3y >= 600)
    {
        ballonMissed.hard++;
        bal3y = 0;
        bal3x = 150 + rand() % 750;
    }
    drawbal4(bal4x, bal4y, radius4, 100);
    bal4y += 3.5;
    if (bal4y >= 600)
    {
        ballonMissed.hard++;
        bal4y = 0;
        bal4x = 150 + rand() % 750;
    }
    drawbal5(bal5x, bal5y, radius5, 100);
    bal5y += 2.8;
    if (bal5y >= 600)
    {
        ballonMissed.hard++;
        bal5y = 0;
        bal5x = 150 + rand() % 750;
    }
}

// ScoreEntry topScores[NUM_TOP_SCORES];
void drawGameOverPage()
{
    iShowBMP(0, 0, "images\\gameOverPage.bmp");
    iSetColor(103, 217, 10);
    iFilledRectangle(400, 250, textBoxWidth, textBoxHeight);
    iSetColor(0, 0, 0);
    iText(425, 300, "Player Name???", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(425, 275, playerName, GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255, 255, 255);
    iFilledRectangle(830, 0, 1000, 60);
    iSetColor(0, 0, 0);
    iText(845, 20, "Save & Return", GLUT_BITMAP_TIMES_ROMAN_24);
    // printf("%s\t %d\n", playerName, score);
}
// function to show score in pages:
void drawScoreNRemainingTime() // // will draw the score in every level;
{
    iSetColor(255, 255, 255);
    if (hardPage == 1)
        iSetColor(0, 0, 0);
    iText(872, 500, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
    char scoreStr[20];
    sprintf(scoreStr, "%d", score);
    iText(940, 500, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
    char time[100];
    int timeRemaining = 60 - timeCount;
    itoa(timeRemaining, time, 10);
    iText(760, 560, "Time Remaining:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(940, 560, time, GLUT_BITMAP_TIMES_ROMAN_24);
}

void timeCounter()
{
    timeCount++;
    if (timeCount > maxPlayTime || (easyPage == 1 && ballonMissed.easy > youCanMissOnEasy) || (mediumPage == 1 && ballonMissed.medium > youCanMissOnMedium) || (hardPage == 1 && ballonMissed.hard > youCanMissOnHard))
    {
        gameOverHandler();
        timeCount = 0;
        iPauseTimer(0);
    }
    // printf("Time Count: %d\n", timeCount);
}

void saveScore()
{
    FILE *ptr;
    ptr = fopen("topScores.txt", "r");
    int fileScore;
    char filePlayerName[20];
    fscanf(ptr, "%[^\n]", &filePlayerName);
    fscanf(ptr, "%d", &fileScore);
    // printf("###%s %d\n",filePlayerName,fileScore);
    fclose(ptr);

    ptr = fopen("topScores.txt", "w");
    if (score > fileScore)
    {
        fprintf(ptr, "%s\n", playerName);
        fprintf(ptr, "%d", score);
        // printf("####name: %s score: %d",playerName,score);
    }
    else
    {
        fprintf(ptr, "%s\n", filePlayerName);
        fprintf(ptr, "%d", fileScore);
    }
    fclose(ptr);
}
void loadScore()
{
    FILE *ptr;
    ptr = fopen("topScores.txt", "r");
    int fileScore;
    char filePlayerName[20];
    fscanf(ptr, "%[^\n]", &filePlayerName);
    fscanf(ptr, "%d", &fileScore);
    char showingScore[1000];
    sprintf(showingScore, "%d", fileScore);
    iText(450, 300, "PlayerName: ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(450, 260, filePlayerName, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(450, 200, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(550, 200, showingScore, GLUT_BITMAP_TIMES_ROMAN_24);
    // // printf("%s %d\n",playerName,score);
    fclose(ptr);
}

// // The handlers: these help to navigate.
void startPageClickHandler()
{
    homePage = 0;
    startPage = 1;
    gameOverPage = 0;
}
void instructionsPageClickHandler()
{
    homePage = 0;
    startPage = 0;
    instructionsPage = 1;
    gameOverPage = 0;
}
void creditsPageClickHandler()
{
    homePage = 0;
    startPage = 0;
    instructionsPage = 0;
    creditsPage = 1;
    gameOverPage = 0;
}
void scorePageClickHandler()
{
    homePage = 0;
    startPage = 0;
    instructionsPage = 0;
    creditsPage = 0;
    easyPage = 0;
    mediumPage = 0;
    hardPage = 0;
    scorePage = 1;
    saveScore();
}
void backButtonClickHandler()
{
    homePage = 1;
    startPage = 0;
    instructionsPage = 0;
    creditsPage = 0;
    scorePage = 0;
    gameOverPage = 0;
}
void backButtonToStartPageHandler()
{
    homePage = 0;
    instructionsPage = 0;
    creditsPage = 0;
    scorePage = 0;
    gameOverHandler();
    mouseClickX = 1100;
    mouseClickY = 700;
}
void easyPageClickHandler()
{
    timeCount = 0;
    homePage = 0;
    startPage = 0;
    instructionsPage = 0;
    creditsPage = 0;
    scorePage = 0;
    easyPage = 1;
    gameOverPage = 0;
    ballonMissed.easy = 0;
}
void mediumPageClickHandler()
{
    timeCount = 0;
    homePage = 0;
    startPage = 0;
    instructionsPage = 0;
    creditsPage = 0;
    scorePage = 0;
    easyPage = 0;
    mediumPage = 1;
    gameOverPage = 0;
    ballonMissed.medium = 0;
}
void hardPageClickHandler()
{
    timeCount = 0;
    homePage = 0;
    startPage = 0;
    instructionsPage = 0;
    creditsPage = 0;
    scorePage = 0;
    easyPage = 0;
    mediumPage = 0;
    hardPage = 1;
    gameOverPage = 0;
    ballonMissed.hard = 0;
}
void gameOverHandler()
{
    homePage = 0;
    startPage = 0;
    instructionsPage = 0;
    creditsPage = 0;
    scorePage = 0;
    easyPage = 0;
    mediumPage = 0;
    hardPage = 0;
    gameOverPage = 1;
    // printf("%s %d\n", playerName, score);
}
int main()
{
    iSetTimer(1000, timeCounter); // Set the timer for every 1000 milliseconds (1 second)
    iPauseTimer(0);
    if (startPage == 1 | soundOn == true)
        PlaySound(TEXT("sounds\\menumusic.wav"), NULL, SND_ASYNC | SND_LOOP); // // loop dile project build na hoyei sound cholte thake tai snd loop | snd async
    if ((ballonPopSound == true))
        PlaySound(TEXT("sounds\\popSound.wav"), NULL, SND_ASYNC);
    iInitialize(1000, 600, "Balloon Shooter");
    return 0;
}

// // let's build and run