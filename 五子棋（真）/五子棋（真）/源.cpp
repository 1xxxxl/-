#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>		
#pragma comment ( lib, "Winmm.lib" )
#define  white 1
#define  black 2
/*0*/int mainpage();
/*1*/int play(int n);//n=0cxk��n=1
/*2*/void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
/*3*/void outtext(char a[], int left, int top, int width, int height);//���������֣����У�
int main()
{
	initgraph(630, 500);
	int result = 0;
	int choose = 0;
	result = mainpage();
	choose = result;
	result = play(result);
	if (result == 1)
	{
		char winner1[10] = "you lose!";
		settextstyle(70, 0, "Բ��");
		setbkmode(TRANSPARENT);
		settextcolor(RGB(0, 255, 255));
		outtext(winner1, 208.3, 208.3, 83.33, 83.33);
		if (choose == 0)
		{
			mciSendString("open ./ziyiweishi.mp3 alias bk1", 0, 0, 0);
			mciSendString("play bk1", 0, 0, 0);
		}
		else if (choose == 1)
		{
			mciSendString("open ./wazhende.mp3 alias bk2", 0, 0, 0);
			mciSendString("play bk2", 0, 0, 0);
		}
	}
	else if (result == 2)
	{
		char winner2[10] = "you win!";
		settextstyle(70, 0, "Բ��");
		setbkmode(TRANSPARENT);
		settextcolor(RGB(0, 255, 255));
		outtext(winner2, 208.3, 208.3, 83.33, 83.33);
		if (choose == 0)
		{
			mciSendString("open ./wazhende.mp3 alias bk1", 0, 0, 0);
			mciSendString("play bk1", 0, 0, 0);
		}
		else if (choose == 1)
		{
			mciSendString("open ./ziyiweishi.mp3 alias bk2", 0, 0, 0);
			mciSendString("play bk2", 0, 0, 0);
		}
	}
	getchar();
	return 0;
}
/*0*/int mainpage()
{
	IMAGE bk;
	loadimage(&bk, "./bk.png", 630, 500);
	putimage(0, 0, &bk);
	int choose = 0;
	MOUSEMSG msg;
	int message = 0;
	while (!message)
	{
		if (MouseHit())
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				float x = msg.x;
				float y = msg.y;
				if (x > 46.6 && x < 194 && y>420 && y < 457)
				{
					choose = 0;
					message = 1;
					break;
				}
				else if (x > 460 && x < 610 && y>420 && y < 457)
				{
					choose = 1;
					message = 1;
					break;
				}
			}
		}
	}
	return choose;
}
/*1*/int play(int n)//n=0cxk��n=1
{
	IMAGE img;
	loadimage(&img, "./qipan.png", 500, 500);
	putimage(0, 0, &img);
	IMAGE cxk, ckf;
	loadimage(&cxk, "./cxk1.png", 130, 250);
	loadimage(&ckf, "./ckf1.png", 130, 250);
	putimagePNG(500, 0, &cxk);
	putimagePNG(500, 250, &ckf);


	//��ӡ����

	int chess[15][15];
	int i = 0, j = 0;
	for (i = 0;i < 15;i++)
	{
		for (j = 0;j < 15;j++)
		{
			chess[i][j] = 0;
		}
	}

	//��ʼ����ά����

	IMAGE img1, img2;//1��2��
	if (n == 0)
	{
		loadimage(&img1, "./youbing.png", 32.705, 32.705);
		loadimage(&img2, "./dachang.png", 32.705, 32.705);
	}
	else if (n == 1)
	{
		loadimage(&img1, "./dachang.png", 32.705, 32.705);
		loadimage(&img2, "./youbing.png", 32.705, 32.705);
	}

	//�ڰ���

	srand((int)time(NULL));
	int canplay = 0;
	int turn = rand()%2;

	while (!canplay)
	{
		turn++;
		int who = turn % 2 + 1;
		float x=0, y=0;
		int xx = 0, yy = 0;
		if (who == black)
		{
			MOUSEMSG msg;
			int message = 0;
			while (!message)
			{
				if (MouseHit())
				{
					msg = GetMouseMsg();
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						x = msg.x;
						y = msg.y;
						x = (x - 4.1875) / 32.705;
						y = (y - 4.1875) / 32.705;
						xx = (int)x, yy = (int)y;
						if (chess[xx][yy] == 0)
						{
							chess[xx][yy] = black;
							message = 1;
						}
					}
				}
			}
		}

		//��ȡ�����Ϣ�����£�

		else if (who == white)
		{
			Sleep(100);
			srand((int)time(NULL));
			int putx[4], puty[4];
			for (i = 0;i < 4;i++)
			{
				putx[i] = puty[i] = -1;
			}
			for (i = 0;i < 15;i++)
			{
				for (j = 0;j < 15;j++)
				{
					if (turn == 2 || turn == 1)
					{
						if (chess[7][8] == 0)
						{
							putx[0] = 7, puty[0] = 8;
							break;
						}
					}
					if (turn == 4 || turn == 3)
					{
						if (chess[i][j] == white)
						{
							int choose = rand() % 8;
							switch (choose)
							{
							case(0):
								if (i < 14 && j < 14 && chess[i + 1][j + 1] == 0)
								{
									putx[3] = i + 1, puty[3] = j + 1;
									break;
								}
							case(1):
								if (i < 14 && j>0 && chess[i + 1][j - 1] == 0)
								{
									putx[3] = i + 1, puty[3] = j - 1;
									break;
								}
							case(2):
								if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
								{
									putx[3] = i - 1, puty[3] = j - 1;
									break;
								}
							case(3):
								if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
								{
									putx[3] = i - 1, puty[3] = j + 1;
									break;
								}
							case(4):
								if (i < 14 && chess[i + 1][j] == 0)
								{
									putx[3] = i + 1, puty[3] = j;
									break;
								}
							case(5):
								if (i > 0 && chess[i - 1][j] == 0)
								{
									putx[3] = i - 1, puty[3] = j;
									break;
								}
							case(6):
								if (j < 14 && chess[i][j + 1] == 0)
								{
									putx[3] = i, puty[3] = j + 1;
									break;
								}
							case(7):
								if (j > 0 && chess[i][j - 1] == 0)
								{
									putx[3] = i, puty[3] = j - 1;
									break;
								}
							}
							break;
						}
						else if (chess[i][j] != white)
							continue;
					}
					if (chess[i][j] == 0)
						continue;
					if (j < 12 && chess[i][j] == white && chess[i][j + 1] == white && chess[i][j + 2] == white && chess[i][j + 3] == white)
					{
						if (j > 0 && chess[i][j - 1] == 0)
						{
							putx[0] = i, puty[0] = j - 1;
						}
						else if (j < 11 && chess[i][j + 4] == 0)
						{
							putx[0] = i, puty[0] = j + 4;
						}
					}
					else if (i < 12 && chess[i][j] == white && chess[i + 1][j] == white && chess[i + 2][j] == white && chess[i + 3][j] == white)
					{
						if (i > 0 && chess[i - 1][j] == 0)
						{
							putx[0] = i - 1, puty[0] = j;
						}
						else if (i < 11 && chess[i + 4][j] == 0)
						{
							putx[0] = i + 4, puty[0] = j;
						}
					}
					else if (i < 12 && j < 12 && chess[i][j] == white && chess[i + 1][j + 1] == white && chess[i + 2][j + 2] == white && chess[i + 3][j + 3] == white)
					{
						if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
						{
							putx[0] = i - 1, puty[0] = j - 1;
						}
						else if (i < 11 && j < 11 && chess[i + 4][j + 4] == 0)
						{
							putx[0] = i + 4, puty[0] = j + 4;
						}
					}
					else if (i < 12 && j > 2 && chess[i][j] == white && chess[i + 1][j - 1] == white && chess[i + 2][j - 2] == white && chess[i + 3][j - 3] == white)
					{
						if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
						{
							putx[0] = i - 1, puty[0] = j + 1;
						}
						else if (i < 11 && j>3 && chess[i + 4][j - 4] == 0)
						{
							putx[0] = i + 4, puty[0] = j - 4;
						}
					}
					else if (i < 11 && chess[i][j] == white && chess[i + 1][j] == white && chess[i + 2][j] == white && chess[i + 4][j] == white)
					{
						if (chess[i + 3][j] == 0)
							putx[0] = i + 3, puty[0] = j;
					}
					else if (i < 11 && chess[i][j] == white && chess[i + 1][j] == white && chess[i + 3][j] == white && chess[i + 4][j] == white)
					{
						if (chess[i + 2][j] == 0)
							putx[0] = i + 2, puty[0] = j;
					}
					else if (i < 11 && chess[i][j] == white && chess[i + 2][j] == white && chess[i + 3][j] == white && chess[i + 4][j] == white)
					{
						if (chess[i + 1][j] == 0)
							putx[0] = i + 1, puty[0] = j;
					}
					else if (j < 11 && chess[i][j] == white && chess[i][j + 1] == white && chess[i][j + 2] == white && chess[i][j + 4] == white)
					{
						if (chess[i][j + 3] == 0)
						{
							putx[0] = i, puty[0] = j + 3;
						}
					}
					else if (j < 11 && chess[i][j] == white && chess[i][j + 1] == white && chess[i][j + 3] == white && chess[i][j + 4] == white)
					{
						if (chess[i][j + 2] == 0)
						{
							putx[0] = i, puty[0] = j + 2;
						}
					}
					else if (j < 11 && chess[i][j] == white && chess[i][j + 2] == white && chess[i][j + 3] == white && chess[i][j + 4] == white)
					{
						if (chess[i][j + 1] == 0)
						{
							putx[0] = i, puty[0] = j + 1;
						}
					}
					else if (i < 11 && j < 11 && chess[i][j] == white && chess[i + 1][j + 1] == white && chess[i + 2][j + 2] == white && chess[i + 4][j + 4] == white)
					{
						if (chess[i + 3][j + 3] == 0)
						{
							putx[0] = i + 3, puty[0] = j + 3;
						}
					}
					else if (i < 11 && j < 11 && chess[i][j] == white && chess[i + 1][j + 1] == white && chess[i + 3][j + 3] == white && chess[i + 4][j + 4] == white)
					{
						if (chess[i + 2][j + 2] == 0)
						{
							putx[0] = i + 2, puty[0] = j + 2;
						}
					}
					else if (i < 11 && j < 11 && chess[i][j] == white && chess[i + 2][j + 2] == white && chess[i + 3][j + 3] == white && chess[i + 4][j + 4] == white)
					{
						if (chess[i + 1][j + 1] == 0)
						{
							putx[0] = i + 1, puty[0] = j + 1;
						}
					}
					else if (i < 11 && j > 3 && chess[i][j] == white && chess[i + 1][j - 1] == white && chess[i + 2][j - 2] == white && chess[i + 4][j - 4] == white)
					{
						if (chess[i + 3][j - 3] == 0)
						{
							putx[0] = i + 3, puty[0] = j - 3;
						}
					}
					else if (i < 11 && j > 3 && chess[i][j] == white && chess[i + 1][j - 1] == white && chess[i + 3][j - 3] == white && chess[i + 4][j - 4] == white)
					{
						if (chess[i + 2][j - 2] == 0)
						{
							putx[0] = i + 2, puty[0] = j - 2;
						}
					}
					else if (i < 11 && j > 3 && chess[i][j] == white && chess[i + 2][j - 2] == white && chess[i + 3][j - 3] == white && chess[i + 4][j - 4] == white)
					{
						if (chess[i + 1][j - 1] == 0)
						{
							putx[0] = i + 1, puty[0] = j - 1;
						}
					}
					//���Ⱦ�ɱ
					else if (j < 12 && chess[i][j] == black && chess[i][j + 1] == black && chess[i][j + 2] == black && chess[i][j + 3] == black)
					{
						if (j > 0 && chess[i][j - 1] == 0)
						{
							putx[0] = i, puty[0] = j - 1;
						}
						else if (j < 11 && chess[i][j + 4] == 0)
						{
							putx[0] = i, puty[0] = j + 4;
						}
					}
					else if (i < 12 && chess[i][j] == black && chess[i + 1][j] == black && chess[i + 2][j] == black && chess[i + 3][j] == black)
					{
						if (i > 0 && chess[i - 1][j] == 0)
						{
							putx[0] = i - 1, puty[0] = j;
						}
						else if (i < 11 && chess[i + 4][j] == 0)
						{
							putx[0] = i + 4, puty[0] = j;
						}
					}
					else if (i < 12 && j < 12 && chess[i][j] == black && chess[i + 1][j + 1] == black && chess[i + 2][j + 2] == black && chess[i + 3][j + 3] == black)
					{
						if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
						{
							putx[0] = i - 1, puty[0] = j - 1;
						}
						else if (i < 11 && j < 11 && chess[i + 4][j + 4] == 0)
						{
							putx[0] = i + 4, puty[0] = j + 4;
						}
					}
					else if (i < 12 && j > 2 && chess[i][j] == black && chess[i + 1][j - 1] == black && chess[i + 2][j - 2] == black && chess[i + 3][j - 3] == black)
					{
						if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
						{
							putx[0] = i - 1, puty[0] = j + 1;
						}
						else if (i < 11 && j>3 && chess[i + 4][j - 4] == 0)
						{
							putx[0] = i + 4, puty[0] = j - 4;
						}
					}
					else if (i < 11 && chess[i][j] == black && chess[i + 1][j] == black && chess[i + 2][j] == black && chess[i + 4][j] == black)
					{
						if (chess[i + 3][j] == 0)
							putx[0] = i + 3, puty[0] = j;
					}
					else if (i < 11 && chess[i][j] == black && chess[i + 1][j] == black && chess[i + 3][j] == black && chess[i + 4][j] == black)
					{
						if (chess[i + 2][j] == 0)
							putx[0] = i + 2, puty[0] = j;
					}
					else if (i < 11 && chess[i][j] == black && chess[i + 2][j] == black && chess[i + 3][j] == black && chess[i + 4][j] == black)
					{
						if (chess[i + 1][j] == 0)
							putx[0] = i + 1, puty[0] = j;
					}
					else if (j < 11 && chess[i][j] == black && chess[i][j + 1] == black && chess[i][j + 2] == black && chess[i][j + 4] == black)
					{
						if (chess[i][j + 3] == 0)
						{
							putx[0] = i, puty[0] = j + 3;
						}
					}
					else if (j < 11 && chess[i][j] == black && chess[i][j + 1] == black && chess[i][j + 3] == black && chess[i][j + 4] == black)
					{
						if (chess[i][j + 2] == 0)
						{
							putx[0] = i, puty[0] = j + 2;
						}
					}
					else if (j < 11 && chess[i][j] == black && chess[i][j + 2] == black && chess[i][j + 3] == black && chess[i][j + 4] == black)
					{
						if (chess[i][j + 1] == 0)
						{
							putx[0] = i, puty[0] = j + 1;
						}
					}
					else if (i < 11 && j < 11 && chess[i][j] == black && chess[i + 1][j + 1] == black && chess[i + 2][j + 2] == black && chess[i + 4][j + 4] == black)
					{
						if (chess[i + 3][j + 3] == 0)
						{
							putx[0] = i + 3, puty[0] = j + 3;
						}
					}
					else if (i < 11 && j < 11 && chess[i][j] == black && chess[i + 1][j + 1] == black && chess[i + 3][j + 3] == black && chess[i + 4][j + 4] == black)
					{
						if (chess[i + 2][j + 2] == 0)
						{
							putx[0] = i + 2, puty[0] = j + 2;
						}
					}
					else if (i < 11 && j < 11 && chess[i][j] == black && chess[i + 2][j + 2] == black && chess[i + 3][j + 3] == black && chess[i + 4][j + 4] == black)
					{
						if (chess[i + 1][j + 1] == 0)
						{
							putx[0] = i + 1, puty[0] = j + 1;
						}
					}
					else if (i < 11 && j > 3 && chess[i][j] == black && chess[i + 1][j - 1] == black && chess[i + 2][j - 2] == black && chess[i + 4][j - 4] == black)
					{
						if (chess[i + 3][j - 3] == 0)
						{
							putx[0] = i + 3, puty[0] = j - 3;
						}
					}
					else if (i < 11 && j > 3 && chess[i][j] == black && chess[i + 1][j - 1] == black && chess[i + 3][j - 3] == black && chess[i + 4][j - 4] == black)
					{
						if (chess[i + 2][j - 2] == 0)
						{
							putx[0] = i + 2, puty[0] = j - 2;
						}
					}
					else if (i < 11 && j > 3 && chess[i][j] == black && chess[i + 2][j - 2] == black && chess[i + 3][j - 3] == black && chess[i + 4][j - 4] == black)
					{
						if (chess[i + 1][j - 1] == 0)
						{
							putx[0] = i + 1, puty[0] = j - 1;
						}
					}
					//��η���ɱ

					//����Ϊ���������ӵ�����
					if (putx[0] == -1 && putx[1] == -1)
					{
						if (i < 12 && j < 12 && chess[i][j] == white && chess[i + 1][j + 1] == white && chess[i + 3][j + 3] == white)
						{
							if (chess[i + 2][j + 2] == 0)
							{
								putx[1] = i + 2, puty[1] = j + 2;
							}
						}
						else if (i < 12 && j < 12 && chess[i][j] == white && chess[i + 2][j + 2] == white && chess[i + 3][j + 3] == white)
						{
							if (chess[i + 1][j + 1] == 0)
							{
								putx[1] = i + 1, puty[1] = j + 1;
							}
						}
						else if (i < 12 && j>2 && chess[i][j] == white && chess[i + 1][j - 1] == white && chess[i + 3][j - 3] == white)
						{
							if (chess[i + 2][j - 2] == 0)
							{
								putx[1] = i + 2, puty[1] = j - 2;
							}
						}
						else if (i < 12 && j>2 && chess[i][j] == white && chess[i + 2][j - 2] == white && chess[i + 3][j - 3] == white)
						{
							if (chess[i + 1][j - 1] == 0)
							{
								putx[1] = i + 1, puty[1] = j - 1;
							}
						}
						else if (j < 12 && chess[i][j] == white && chess[i][j + 1] == white && chess[i][j + 3] == white)
						{
							if (chess[i][j + 2] == 0)
							{
								putx[1] = i, puty[1] = j + 2;
							}
						}
						else if (j < 12 && chess[i][j] == white && chess[i][j + 2] == white && chess[i][j + 3] == white)
						{
							if (chess[i][j + 1] == 0)
							{
								putx[1] = i, puty[1] = j + 1;
							}
						}
						else if (i < 12 && chess[i][j] == white && chess[i + 1][j] == white && chess[i + 3][j] == white)
						{
							if (chess[i + 2][j] == 0)
							{
								putx[1] = i + 2, puty[1] = j;
							}
						}
						else if (i < 12 && chess[i][j] == white && chess[i + 2][j] == white && chess[i + 3][j] == white)
						{
							if (chess[i + 1][j] == 0)
							{
								putx[1] = i + 1, puty[1] = j;
							}
						}
						else if (i < 13 && j < 13 && chess[i][j] == white && chess[i + 1][j + 1] == white && chess[i + 2][j + 2] == white)
						{
							if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
							{
								putx[1] = i - 1, puty[1] = j - 1;
							}
							else if (i < 12 && j < 12 && chess[i + 1][j + 1] == 0)
							{
								putx[1] = i + 1, puty[1] = j + 1;
							}
							/*else if (chess[i][j + 2] == 0)
							{
								putx[2] = i, puty[2] = j + 2;
							}
							else if (chess[i + 2][j] == 0)
							{
								putx[2] = i + 2, puty[2] = j;
							}*/
						}
						else if (i < 13 && j>1 && chess[i][j] == white && chess[i + 1][j - 1] == white && chess[i + 2][j - 2] == white)
						{
							if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
							{
								putx[1] = i - 1, puty[1] = j + 1;
							}
							else if (i < 12 && j>2 && chess[i + 3][j - 3] == 0)
							{
								putx[1] = i + 3, puty[1] = j - 3;
							}
							/*else if (chess[i][j - 2] == 0)
							{
								putx[2] = i, puty[2] = j - 2;
							}
							else if (chess[i + 2][j] == 0)
							{
								putx[2] = i + 2, puty[2] = j;
							}*/
						}
						else if (j < 13 && chess[i][j] == white && chess[i][j + 1] == white && chess[i][j + 2] == white)
						{
							if (j > 0 && chess[i][j - 1] == 0)
							{
								putx[1] = i, puty[1] = j - 1;
							}
							else if (j < 12 && chess[i][j + 3] == 0)
							{
								putx[1] = i, puty[1] = j + 3;
							}
						}
						else if (i < 13 && chess[i][j] == white && chess[i + 1][j] == white && chess[i + 2][j] == white)
						{
							if (i > 0 && chess[i - 1][j] == 0)
							{
								putx[1] = i - 1, puty[1] = j;
							}
							else if (i < 12 && chess[i + 3][j] == 0)
							{
								putx[1] = i + 3, puty[1] = j;
							}
						}
						//����
						else if (i < 12 && j < 12 && chess[i][j] == black && chess[i + 1][j + 1] == black && chess[i + 3][j + 3] == black)
						{
							if (chess[i + 2][j + 2] == 0)
							{
								if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0 && i < 11 && j < 11 && chess[i + 4][j + 4] == 0)
								{
									putx[1] = i + 2, puty[1] = j + 2;
								}
								else
								{
									putx[2] = i + 2, puty[2] = j + 2;
								}
							}
						}
						else if (i < 12 && j < 12 && chess[i][j] == black && chess[i + 2][j + 2] == black && chess[i + 3][j + 3] == black)
						{
							if (chess[i + 1][j + 1] == 0)
							{
								if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0 && i < 11 && j < 11 && chess[i + 4][j + 4] == 0)
								{
									putx[1] = i + 1, puty[1] = j + 1;
								}
								else
								{
									putx[2] = i + 1, puty[2] = j + 1;
								}
							}
						}
						else if (i < 12 && j>2 && chess[i][j] == black && chess[i + 1][j - 1] == black && chess[i + 3][j - 3] == black)
						{
							if (chess[i + 2][j - 2] == 0)
							{
								if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0 && i < 11 && j > 3 && chess[i + 4][j - 4] == 0)
								{
									putx[1] = i + 2, puty[1] = j - 2;
								}
								else
								{
									putx[2] = i + 2, puty[2] = j - 2;
								}
							}
						}
						else if (i < 12 && j>2 && chess[i][j] == black && chess[i + 2][j - 2] == black && chess[i + 3][j - 3] == black)
						{
							if (chess[i + 1][j - 1] == 0)
							{
								if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0 && i < 11 && j > 3 && chess[i + 4][j - 4] == 0)
								{
									putx[1] = i + 1, puty[1] = j - 1;
								}
								else
								{
									putx[2] = i + 1, puty[2] = j - 1;
								}
							}
						}
						else if (j < 12 && chess[i][j] == black && chess[i][j + 1] == black && chess[i][j + 3] == black)
						{
							if (chess[i][j + 2] == 0)
							{
								if (j > 0 && chess[i][j - 1] == 0 && j < 11 && chess[i][j + 4] == 0)
								{
									putx[1] = i, puty[1] = j + 2;
								}
								else
								{
									putx[2] = i, puty[2] = j + 2;
								}
							}
						}
						else if (j < 12 && chess[i][j] == black && chess[i][j + 2] == black && chess[i][j + 3] == black)
						{
							if (chess[i][j + 1] == 0)
							{
								if (j > 0 && chess[i][j - 1] == 0 && j < 11 && chess[i][j + 4] == 0)
								{
									putx[1] = i, puty[1] = j + 1;
								}
								else
								{
									putx[2] = i, puty[2] = j + 1;
								}
							}
						}
						else if (i < 12 && chess[i][j] == black && chess[i + 1][j] == black && chess[i + 3][j] == black)
						{
							if (chess[i + 2][j] == 0)
							{
								if (i > 0 && chess[i - 1][j] == 0 && i < 11 && chess[i + 4][j] == 0)
								{
									putx[1] = i + 2, puty[1] = j;
								}
								else
								{
									putx[2] = i + 2, puty[2] = j;
								}
							}
						}
						else if (i < 12 && chess[i][j] == black && chess[i + 2][j] == black && chess[i + 3][j] == black)
						{
							if (chess[i + 1][j] == 0)
							{
								if (i > 0 && chess[i - 1][j] == 0 && i < 11 && chess[i + 4][j] == 0)
								{
									putx[1] = i + 1, puty[1] = j;
								}
								else
								{
									putx[2] = i + 1, puty[2] = j;
								}
							}
						}
						else if (i < 13 && j < 13 && chess[i][j] == black && chess[i + 1][j + 1] == black && chess[i + 2][j + 2] == black)
						{
							int choose = rand() % 2;
							switch (choose)
							{
							case(0):
								if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
								{
									if (i < 12 && j < 12 && chess[i + 3][j + 3] == 0)
									{
										putx[1] = i - 1, puty[1] = j - 1;
									}
								}
								break;
							case(1):
								if (i < 12 && j < 12 && chess[i + 3][j + 3] == 0)
								{
									if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
									{
										putx[1] = i + 3, puty[1] = j + 3;
									}
								}
								break;
							}
						}
						else if (i < 13 && j>1 && chess[i][j] == black && chess[i + 1][j - 1] == black && chess[i + 2][j - 2] == black)
						{
							int choose = rand() % 2;
							switch (choose)
							{
							case(0):
								if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
								{
									if (i < 12 && j>2 && chess[i + 3][j - 3] == 0)
									{
										putx[1] = i - 1, puty[1] = j + 1;
									}
								}
								break;
							case(1):
								if (i < 12 && j>2 && chess[i + 3][j - 3] == 0)
								{
									if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
									{
										putx[1] = i + 3, puty[1] = j - 3;
									}
								}
								break;
							}
						}
						else if (j < 13 && chess[i][j] == black && chess[i][j + 1] == black && chess[i][j + 2] == black)
						{
							int choose = rand() % 2;
							switch (choose)
							{
							case(0):
								if (j > 0 && chess[i][j - 1] == 0)
								{
									if (j < 12 && chess[i][j + 3] == 0)
									{
										putx[1] = i, puty[1] = j - 1;
									}
								}
								break;
							case(1):
								if (j < 12 && chess[i][j + 3] == 0)
								{
									if (j > 0 && chess[i][j - 1] == 0)
									{
										putx[1] = i, puty[1] = j + 3;
									}
								}
								break;
							}
						}
						else if (i < 13 && chess[i][j] == black && chess[i + 1][j] == black && chess[i + 2][j] == black)
						{
							int choose = rand() % 2;
							switch (choose)
							{
							case(0):
								if (i > 0 && chess[i - 1][j] == 0)
								{
									if (i < 12 && chess[i + 3][j] == 0)
									{
										putx[1] = i - 1, puty[1] = j;
									}
								}
								break;
							case(1):
								if (i < 12 && chess[i + 3][j] == 0)
								{
									if (i > 0 && chess[i - 1][j] == 0)
									{
										putx[1] = i + 3, puty[1] = j;
									}
								}
								break;
							}
						}
						//����
					}
					//��������������
					if (putx[0] == -1 && putx[1] == -1 && putx[2] == -1)
					{
						if (i < 13 && j < 13 && chess[i][j] == white && chess[i + 2][j + 2] == white)
						{
							if (chess[i + 1][j + 1] == 0)
							{
								putx[2] = i + 1, puty[2] = j + 1;
							}
						}
						else if (i < 13 && j >1 && chess[i][j] == white && chess[i + 2][j - 2] == white)
						{
							if (chess[i + 1][j - 1] == 0)
							{
								putx[2] = i + 1, puty[2] = j - 1;
							}
						}
						else if (i < 14 && j >0 && chess[i][j] == white && chess[i + 1][j - 1] == white)
						{
							if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
							{
								putx[2] = i - 1, puty[2] = j + 1;
							}
							else if (i < 13 && j>1 && chess[i + 2][j - 2] == 0)
							{
								putx[2] = i + 2, puty[2] = j - 2;
							}
							else if (chess[i][j - 1] == 0)
							{
								putx[2] = i, puty[2] = j - 1;
							}
							else if (chess[i + 1][j] == 0)
							{
								putx[2] = i + 1, puty[2] = j;
							}
						}
						else if (j < 13 && chess[i][j] == white && chess[i][j + 2] == white)
						{
							if (chess[i][j + 1] == 0)
							{
								putx[2] = i, puty[2] = j + 1;
							}
						}
						else if (i < 13 && chess[i][j] == white && chess[i + 2][j] == white)
						{
							if (chess[i + 1][j] == 0)
							{
								putx[2] = i + 1, puty[2] = j;
							}
						}
						else if (i < 14 && j < 14 && chess[i][j] == white && chess[i + 1][j + 1] == white)
						{
							if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
							{
								putx[2] = i - 1, puty[2] = j - 1;
							}
							else if (j > 13 && i > 13 && chess[i + 2][j + 2] == 0)
							{
								putx[2] = i + 2, puty[2] = j + 2;
							}
							else if (chess[i + 1][j] == 0)
							{
								putx[2] = i + 1, puty[2] = j;
							}
							else if (chess[i][j + 1] == 0)
							{
								putx[2] = i, puty[2] = j + 1;
							}
						}
						else if (j < 14 && chess[i][j] == white && chess[i][j + 1] == white)
						{
							if (j > 0 && chess[i][j - 1] == 0)
							{
								putx[2] = i, puty[2] = j - 1;
							}
							else if (j < 13 && chess[i][j + 2] == 0)
							{
								putx[2] = i, puty[2] = j + 2;
							}
						}
						else if (i < 14 && chess[i][j] == white && chess[i + 1][j] == white)
						{
							if (i > 0 && chess[i - 1][j] == 0)
							{
								putx[2] = i - 1, puty[2] = j;
							}
							else if (i < 13 && chess[i + 2][j] == 0)
							{
								putx[2] = i + 2, puty[2] = j;
							}
						}
						//����
						/*
						else if (i < 13 && j < 13 && chess[i][j] == black && chess[i + 2][j + 2] == black)
						{
							if (chess[i + 1][j + 1] == 0)
							{
								putx[2] = i + 1, puty[2] = j + 1;
							}
							else if (chess[i][j + 2] == 0)
							{
								putx[2] = i, puty[2] = j + 2;
							}
							else if (chess[i + 2][j] == 0)
							{
								putx[2] = i + 2, puty[2] = j;
							}
						}
						else if (i < 14 && j >0 && chess[i][j] == black && chess[i + 1][j - 1] == black)
						{
							if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
							{
								putx[2] = i - 1, puty[2] = j + 1;
							}
							else if (i < 13 && j>1 && chess[i + 2][j - 2] == 0)
							{
								putx[2] = i + 2, puty[2] = j - 2;
							}
							else if (chess[i][j - 1] == 0)
							{
								putx[2] = i, puty[2] = j - 1;
							}
							else if (chess[i + 1][j] == 0)
							{
								putx[2] = i + 1, puty[2] = j;
							}
						}
						else if (i < 13 && j >1 && chess[i][j] == black && chess[i + 2][j - 2] == black)
						{
							if (chess[i + 1][j - 1] == 0)
							{
								putx[2] = i + 1, puty[2] = j - 1;
							}
							else if (chess[i][j - 2] == 0)
							{
								putx[2] = i, puty[2] = j - 2;
							}
							else if (chess[i + 2][j] == 0)
							{
								putx[2] = i + 2, puty[2] = j;
							}
						}
						else if (j < 13 && chess[i][j] == black && chess[i][j + 2] == black)
						{
							if (chess[i][j + 1] == 0)
							{
								putx[2] = i, puty[2] = j + 1;
							}
						}
						else if (i < 13 && chess[i][j] == black && chess[i + 2][j] == black)
						{
							if (chess[i + 1][j] == 0)
							{
								putx[2] = i + 1, puty[2] = j;
							}
						}
						else if (i < 14 && j < 14 && chess[i][j] == black && chess[i + 1][j + 1] == black)
						{
							if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
							{
								putx[2] = i - 1, puty[2] = j - 1;
							}
							else if (j > 13 && i > 13 && chess[i + 2][j + 2] == 0)
							{
								putx[2] = i + 2, puty[2] = j + 2;
							}
							else if (chess[i + 1][j] == 0)
							{
								putx[2] = i + 1, puty[2] = j;
							}
							else if (chess[i][j + 1] == 0)
							{
								putx[2] = i, puty[2] = j + 1;
							}
						}
						else if (j < 14 && chess[i][j] == black && chess[i][j + 1] == black)
						{
							if (j > 0 && chess[i][j - 1] == 0)
							{
								putx[2] = i, puty[2] = j - 1;
							}
							else if (j < 13 && chess[i][j + 2] == 0)
							{
								putx[2] = i, puty[2] = j + 2;
							}
						}
						else if (i < 14 && chess[i][j] == black && chess[i + 1][j] == black)
						{
							if (i > 0 && chess[i - 1][j] == 0)
							{
								putx[2] = i - 1, puty[2] = j;
							}
							else if (i < 13 && chess[i + 2][j] == 0)
							{
								putx[2] = i + 2, puty[2] = j;
							}
						}
						*/
						//����
					}
					//����Ϊ����
					if (putx[0] == -1 && putx[1] == -1 && putx[2] == -1 && putx[3] == -1)
					{
						if (chess[i][j] == white)
						{
							int choose = rand() % 8;
							switch (choose)
							{
							case(0):
								if (i < 14 && j < 14 && chess[i + 1][j + 1] == 0)
								{
									putx[3] = i + 1, puty[3] = j + 1;
									break;
								}
							case(1):
								if (i < 14 && j>0 && chess[i + 1][j - 1] == 0)
								{
									putx[3] = i + 1, puty[3] = j - 1;
									break;
								}
							case(2):
								if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
								{
									putx[3] = i - 1, puty[3] = j - 1;
									break;
								}
							case(3):
								if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
								{
									putx[3] = i - 1, puty[3] = j + 1;
									break;
								}
							case(4):
								if (i < 14 && chess[i + 1][j] == 0)
								{
									putx[3] = i + 1, puty[3] = j;
									break;
								}
							case(5):
								if (i > 0 && chess[i - 1][j] == 0)
								{
									putx[3] = i - 1, puty[3] = j;
									break;
								}
							case(6):
								if (j < 14 && chess[i][j + 1] == 0)
								{
									putx[3] = i, puty[3] = j + 1;
									break;
								}
							case(7):
								if (j > 0 && chess[i][j - 1] == 0)
								{
									putx[3] = i, puty[3] = j - 1;
									break;
								}
							}
						}
						//����
						/*
						else if (chess[i][j] == black)
						{
							int choose = rand() % 8;
							switch (choose)
							{
							case(0):
								if (i < 14 && j < 14 && chess[i + 1][j + 1] == 0)
								{
									putx[3] = i + 1, puty[3] = j + 1;
									break;
								}
							case(1):
								if (i < 14 && j>0 && chess[i + 1][j - 1] == 0)
								{
									putx[3] = i + 1, puty[3] = j - 1;
									break;
								}
							case(2):
								if (i > 0 && j > 0 && chess[i - 1][j - 1] == 0)
								{
									putx[3] = i - 1, puty[3] = j - 1;
									break;
								}
							case(3):
								if (i > 0 && j < 14 && chess[i - 1][j + 1] == 0)
								{
									putx[3] = i - 1, puty[3] = j + 1;
									break;
								}
							case(4):
								if (i < 14 && chess[i + 1][j] == 0)
								{
									putx[3] = i + 1, puty[3] = j;
									break;
								}
							case(5):
								if (i > 0 && chess[i - 1][j] == 0)
								{
									putx[3] = i - 1, puty[3] = j;
									break;
								}
							case(6):
								if (j < 14 && chess[i][j + 1] == 0)
								{
									putx[3] = i, puty[3] = j + 1;
									break;
								}
							case(7):
								if (j > 0 && chess[i][j - 1] == 0)
								{
									putx[3] = i, puty[3] = j - 1;
									break;
								}
							}
						}
						*/
						//����
					}
				}
			}
			for (i = 0;i < 4;i++)
			{
				if (putx[i] != -1)
				{
					chess[putx[i]][puty[i]] = white;
					break;
				}
			}
		}

		//������

		for (i = 0;i < 15;i++)
		{
			for (j = 0;j < 15;j++)
			{
				if (chess[i][j] == 2)
					putimagePNG(4.1875 + i * 32.705, 4.1875 + j * 32.705, &img1);
				else if (chess[i][j] == 1)
					putimagePNG(4.1875 + i * 32.705, 4.1875 + j * 32.705, &img2);
			}
		}

		//��ӡ�ڰ���

		if (who==black&&
			((chess[xx+1][yy]==white&&chess[xx + 2][yy] == white&& chess[xx + 3][yy] == white&& chess[xx + 4][yy] == white)
			|| (xx > 0 && chess[xx + 1][yy] == white && chess[xx + 2][yy] == white && chess[xx + 3][yy] == white && chess[xx - 1][yy] == white)
			|| (xx > 1 && chess[xx + 1][yy] == white && chess[xx + 2][yy] == white && chess[xx - 2][yy] == white && chess[xx - 1][yy] == white)
			|| (xx > 2 && chess[xx + 1][yy] == white && chess[xx - 3][yy] == white && chess[xx - 2][yy] == white && chess[xx - 1][yy] == white)
			|| (xx > 3 && chess[xx - 4][yy] == white && chess[xx - 3][yy] == white && chess[xx - 2][yy] == white && chess[xx - 1][yy] == white)
			|| (chess[xx][yy + 1] == white && chess[xx][yy + 2] == white && chess[xx][yy + 3] == white && chess[xx][yy + 4] == white)
			|| (yy > 0 && chess[xx][yy + 1] == white && chess[xx][yy + 2] == white && chess[xx][yy + 3] == white && chess[xx][yy - 1] == white)
			|| (yy > 1 && chess[xx][yy + 1] == white && chess[xx][yy + 2] == white && chess[xx][yy - 2] == white && chess[xx][yy - 1] == white)
			|| (yy > 2 && chess[xx][yy + 1] == white && chess[xx][yy - 3] == white && chess[xx][yy - 2] == white && chess[xx][yy - 1] == white)
			|| (yy > 3 && chess[xx][yy - 4] == white && chess[xx][yy - 3] == white && chess[xx][yy - 2] == white && chess[xx][yy - 1] == white)
			|| (chess[xx + 1][yy + 1] == white && chess[xx + 2][yy + 2] == white && chess[xx + 3][yy + 3] == white && chess[xx + 4][yy + 4] == white)
			|| (xx > 0 && yy > 0 && chess[xx + 1][yy + 1] == white && chess[xx + 2][yy + 2] == white && chess[xx + 3][yy + 3] == white && chess[xx - 1][yy - 1] == white)
			|| (xx > 1 && yy > 1 && chess[xx + 1][yy + 1] == white && chess[xx + 2][yy + 2] == white && chess[xx - 2][yy - 2] == white && chess[xx - 1][yy - 1] == white)
			|| (xx > 2 && yy > 2 && chess[xx + 1][yy + 1] == white && chess[xx - 3][yy - 3] == white && chess[xx - 2][yy - 2] == white && chess[xx - 1][yy - 1] == white)
			|| (xx > 3 && yy > 3 && chess[xx - 4][yy - 4] == white && chess[xx - 3][yy - 3] == white && chess[xx - 2][yy - 2] == white && chess[xx - 1][yy - 1] == white)
			|| (chess[xx + 1][yy - 1] == white && chess[xx + 2][yy - 2] == white && chess[xx + 3][yy - 3] == white && chess[xx + 4][yy - 4] == white)
			|| (xx > 0 && yy < 14 && chess[xx + 1][yy - 1] == white && chess[xx + 2][yy - 2] == white && chess[xx + 3][yy - 3] == white && chess[xx - 1][yy + 1] == white)
			|| (xx > 1 && yy < 13 && chess[xx + 1][yy - 1] == white && chess[xx + 2][yy - 2] == white && chess[xx - 2][yy + 2] == white && chess[xx - 1][yy + 1] == white)
			|| (xx > 2 && yy < 12 && chess[xx + 1][yy - 1] == white && chess[xx - 3][yy + 3] == white && chess[xx - 2][yy + 2] == white && chess[xx - 1][yy + 1] == white)
			|| (xx > 3 && yy < 11 && chess[xx - 4][yy + 4] == white && chess[xx - 3][yy + 3] == white && chess[xx - 2][yy + 2] == white && chess[xx - 1][yy + 1] == white)))
		{
			if (n==0)
			{
				loadimage(&ckf, "./ckf2.png", 130, 250);
				putimagePNG(500, 250, &ckf);
				mciSendString("close bk3", 0, 0, 0);
				mciSendString("open ./guyide.mp3 alias bk3", 0, 0, 0);
				mciSendString("play bk3", 0, 0, 0);
				Sleep(500);
				loadimage(&ckf, "./ckf1.png", 130, 250);
				putimagePNG(500, 250, &ckf);
			}
			else if (n==1)
			{
				loadimage(&cxk, "./cxk2.png", 130, 250);
				putimagePNG(500, 0, &cxk);
				mciSendString("close bk4", 0, 0, 0);
				mciSendString("open ./niganma.mp3 alias bk4", 0, 0, 0);
				mciSendString("play bk4", 0, 0, 0);
				Sleep(500);
				loadimage(&cxk, "./cxk1.png", 130, 250);
				putimagePNG(500, 0, &cxk);
			}
		}

		//��������

		for (i = 0;i < 15;i++)
		{
			for (j = 0;j < 15;j++)
			{
				if (j<11&&chess[i][j] != 0 && chess[i][j] == chess[i][j + 1] && chess[i][j] == chess[i][j + 2] && chess[i][j] == chess[i][j + 3] && chess[i][j] == chess[i][j + 4])
				{
					canplay = chess[i][j];
					break;
				}
				else if (i<11&&chess[i][j] != 0 && chess[i][j] == chess[i + 1][j] && chess[i][j] == chess[i + 2][j] && chess[i][j] == chess[i + 3][j] && chess[i][j] == chess[i + 4][j])
				{
					canplay = chess[i][j];
					break;
				}
				else if (i<11&&j<11&&chess[i][j] != 0 && chess[i][j] == chess[i + 1][j + 1] && chess[i][j] == chess[i + 2][j + 2] && chess[i][j] == chess[i + 3][j + 3] && chess[i][j] == chess[i + 4][j + 4])
				{
					canplay = chess[i][j];
					break;
				}
				else if (i<11&&j>4&&chess[i][j] != 0 && chess[i][j] == chess[i + 1][j - 1] && chess[i][j] == chess[i + 2][j - 2] && chess[i][j] == chess[i + 3][j - 3] && chess[i][j] == chess[i + 4][j - 4])
				{
					canplay = chess[i][j];
					break;
				}
			}
		}

		//�ж��Ƿ������Ϸ
	}
	return canplay;
}
/*2*/void putimagePNG(int  picture_x, int picture_y, IMAGE* picture)
{
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
/*3*/void outtext(char a[], int left, int top, int width, int height)
{
	int x_buff = 0, y_buff = 0;
	x_buff = (width - textwidth(a)) / 2;
	y_buff = (height - textheight(a)) / 2;
	outtextxy(left + x_buff, top + y_buff, a);
}