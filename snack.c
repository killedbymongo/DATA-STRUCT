#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

//MAXWIDTH��MAXHEIGHT��INITLEN ���ַ���
#define MAXWIDTH (30)
#define MAXHEIGHT MAXWIDTH
#define INITLEN (3)  //̰���ߵĳ�ʼ����

//�������õ��ĸ����ַ����Լ����ǵ���ɫ�����ͣ������ֱ�ʾ��
struct{
    char *ch;
    int color;
    char type;
}
charBorder = {"��", 4, 1},  //�߿�
charBg = {"��", 2, 2},  //����
charSnake = {"��", 0xe, 3},  //̰���߽ڵ�
charFood = {"��", 0xc, 4};  //ʳ��

//��һ���ṹ�����鱣���ͼ�еĸ�����
struct{
    char type;
    int index;
}globalMap[MAXWIDTH][MAXHEIGHT];

//̰������Ч���Χ��ͼ������
struct{
    int x;
    int y;
} snakeMap[ (MAXWIDTH-2)*(MAXHEIGHT-2) ], scoresPostion;

int scores = 0;  //�÷�
int snakeMapLen = (MAXWIDTH-2)*(MAXHEIGHT-2);
int headerIndex, tailIndex;  //��ͷ��β��Ӧ��snakeMap�е��������±꣩
HANDLE hStdin;  //����̨���

// ���ù��λ�ã�xΪ�У�yΪ��
void setPosition(int x, int y){
    COORD coord;
    coord.X = 2*y;
    coord.Y = x;
    SetConsoleCursorPosition(hStdin, coord);
}

// ������ɫ
void setColor(int color){
    SetConsoleTextAttribute(hStdin, color);
}

//����ʳ��
void createFood(){
    int index, rang, x, y;
    //�����������ȷ�� snakeMap ���������
    srand((unsigned)time(NULL));
    if(tailIndex<headerIndex){
        rang = headerIndex-tailIndex-1;
        index = rand()%rang + tailIndex + 1;
    }else{
        rang = snakeMapLen - (tailIndex - headerIndex+1);
        index = rand()%rang;
        if(index>=headerIndex){
            index += (tailIndex-headerIndex+1);
        }
    }

    x = snakeMap[index].x;
    y = snakeMap[index].y;
    setPosition(x, y);
    setColor(charFood.color);
    printf("%s", charFood.ch);
    globalMap[x][y].type=charFood.type;
}

//����
void die(){
    int xCenter = MAXHEIGHT%2==0 ? MAXHEIGHT/2 : MAXHEIGHT/2+1;
    int yCenter = MAXWIDTH%2==0 ? MAXWIDTH/2 : MAXWIDTH/2+1;

    setPosition(xCenter, yCenter-5);
    setColor(0xC);

    printf("You die! Game Over!");
    getch();
    exit(0);
}

// ���ƶ�
void move(char direction){
    int newHeaderX, newHeaderY;  //����ͷ������
    int newHeaderPreIndex;  //����ͷ������ǰ��Ӧ������
    int newHeaderPreX, newHeaderPreY;  //����ͷ��������ǰ��Ӧ������
    int newHeaderPreType;  //����ͷ��ǰ������
    int oldTailX, oldTailY;  //����β����
    // -----------------------------------------------
    //����ͷ������
    switch(direction){
        case 'w':
            newHeaderX = snakeMap[headerIndex].x-1;
            newHeaderY = snakeMap[headerIndex].y;
            break;
        case 's':
            newHeaderX = snakeMap[headerIndex].x+1;
            newHeaderY = snakeMap[headerIndex].y;
            break;
        case 'a':
            newHeaderX = snakeMap[headerIndex].x;
            newHeaderY = snakeMap[headerIndex].y-1;
            break;
        case 'd':
            newHeaderX = snakeMap[headerIndex].x;
            newHeaderY = snakeMap[headerIndex].y+1;
            break;
    }
    //����ͷ������
    headerIndex = headerIndex==0 ? snakeMapLen-1 : headerIndex-1;
    // -----------------------------------------------
    //����ͷ������ǰ��Ӧ������
    newHeaderPreIndex = globalMap[newHeaderX][newHeaderY].index;
    //����ͷ��������ǰ��Ӧ������
    newHeaderPreX = snakeMap[headerIndex].x;
    newHeaderPreY = snakeMap[headerIndex].y;

    //˫�������ͷ����������Ķ�Ӧ��ϵ
    snakeMap[headerIndex].x = newHeaderX;
    snakeMap[headerIndex].y = newHeaderY;
    globalMap[newHeaderX][newHeaderY].index = headerIndex;

    //˫�����ǰ������������Ķ�Ӧ��ϵ
    snakeMap[newHeaderPreIndex].x = newHeaderPreX;
    snakeMap[newHeaderPreIndex].y = newHeaderPreY;
    globalMap[newHeaderPreX][newHeaderPreY].index = newHeaderPreIndex;

    //����ͷ��ǰ������
    newHeaderPreType = globalMap[newHeaderX][newHeaderY].type;
    //��������ͷ����
    globalMap[newHeaderX][newHeaderY].type = charSnake.type;
    // �ж��Ƿ�����ײ���Լ�
    if(newHeaderPreType==charBorder.type || newHeaderPreType==charSnake.type ){
        die();
    }
    //�������ͷ
    setPosition(newHeaderX, newHeaderY);
    setColor(charSnake.color);
    printf("%s", charSnake.ch);
    //�ж��Ƿ�Ե�ʳ��
    if(newHeaderPreType==charFood.type){  //�Ե�ʳ��
        createFood();
        //���ķ���
        setPosition(scoresPostion.x, scoresPostion.y);
        printf("%d", ++scores);
    }else{
        //����β����
        oldTailX = snakeMap[tailIndex].x;
        oldTailY = snakeMap[tailIndex].y;
        //ɾ����β
        setPosition(oldTailX, oldTailY);
        setColor(charBg.color);
        printf("%s", charBg.ch);
        globalMap[oldTailX][oldTailY].type = charBg.type;
        tailIndex = (tailIndex==0) ? snakeMapLen-1 : tailIndex-1;
    }
}

//�´��ƶ��ķ���
char nextDirection(char ch, char directionOld){
    int sum = ch+directionOld;
    ch = tolower(ch);
    if( (ch=='w' || ch=='a' || ch=='s' || ch=='d') && sum!=197 && sum!=234 ){
        return ch;
    }else{
        return directionOld;
    }
}

//��ͣ
char pause(){
    return getch();
}

// ��ʼ��
void init(){
    // ������ر���
    int x, y, i, index;
    int xCenter = MAXHEIGHT%2==0 ? MAXHEIGHT/2 : MAXHEIGHT/2+1;
    int yCenter = MAXWIDTH%2==0 ? MAXWIDTH/2 : MAXWIDTH/2+1;
    CONSOLE_CURSOR_INFO cci;  //����̨�����Ϣ

    //�ж���������Ƿ����
    if(MAXWIDTH<16){
        printf("'MAXWIDTH' is too small!");
        getch();
        exit(0);
    }

    //���ô��ڴ�С
    system("mode con: cols=96 lines=32");

    //���ع��
    hStdin = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdin, &cci);
    cci.bVisible = 0;
    SetConsoleCursorInfo(hStdin, &cci);

    //��ӡ����
    for(x=0; x<MAXHEIGHT; x++){
        for(y=0; y<MAXWIDTH; y++){
            if(y==0 || y==MAXWIDTH-1 || x==0 || x==MAXHEIGHT-1){
                globalMap[x][y].type = charBorder.type;
                setColor(charBorder.color);
                printf("%s", charBorder.ch);
            }else{
                index = (x-1)*(MAXWIDTH-2)+(y-1);
                snakeMap[index].x= x;
                snakeMap[index].y= y;
                globalMap[x][y].type = charBg.type;
                globalMap[x][y].index = index;

                setColor(charBg.color);
                printf("%s", charBg.ch);
            }
        }
        printf("\n");
    }

    //��ʼ��̰����
    globalMap[xCenter][yCenter-1].type = globalMap[xCenter][yCenter].type = globalMap[xCenter][yCenter+1].type = charSnake.type;

    headerIndex = (xCenter-1)*(MAXWIDTH-2)+(yCenter-1) - 1;
    tailIndex = headerIndex+2;
    setPosition(xCenter, yCenter-1);
    setColor(charSnake.color);
    for(y = yCenter-1; y<=yCenter+1; y++){
        printf("%s", charSnake.ch);
    }
    //����ʳ��
    createFood();

    //���ó�����Ϣ
    setPosition(xCenter-1, MAXWIDTH+2);
    printf("   Apples : 0");
    setPosition(xCenter, MAXWIDTH+2);
    printf("   Author : xiao p");
    setPosition(xCenter+1, MAXWIDTH+2);
    printf("Copyright : c.biancheng.net");
    scoresPostion.x = xCenter-1;
    scoresPostion.y = MAXWIDTH+8;
}

int main(){
    char charInput, direction = 'a';
    init();

    charInput = tolower(getch());
    direction = nextDirection(charInput, direction);

    while(1){
        if(kbhit()){
            charInput = tolower(getch());
            if(charInput == ' '){
                charInput = pause();
            }
            direction = nextDirection(charInput, direction);
        }
        move(direction);
        Sleep(500);
    }
}
