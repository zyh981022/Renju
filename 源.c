#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#define CENTER 40 //�ں������ϼ��ϸ�ֵ������ͼ������ͼ�м�
//��=1 ai ��=2 people
int qipan[15][15] ;
int needthink[15][15];

void SetPos(int x, int y);
void prmap();
void think();
void aido();
int victory();
int evaluate();
int ifkill();

void SetPos(int x, int y)
{
	COORD pos;
	HANDLE handle;
	pos.X = x;
	pos.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}
void prmap()  //��ӡ��ͼ
{
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
		{
			switch (qipan[j][i])
			{
			case 0:
				if (j == 0 && i != 14 && i != 0)
				{
					SetPos(2 * i+ CENTER, j);
					printf("��");
				}
				if (j == 14 && i != 0 && i != 14)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}
				if (i == 0 && j != 0 && j != 14)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}
				if (i == 14 && j != 14 && j != 0)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}
				if (i != 0 && i != 14 && j != 0 && j != 14)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}


				if (i == 0 && j == 0)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}
				if (i == 14 && j == 14)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}
				if (i == 0 && j == 14)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}
				if (i == 14 && j == 0)
				{
					SetPos(2 * i + CENTER, j);
					printf("��");
				}
				break;

			case 1:
				SetPos(2 * i+CENTER, j);
				printf("��");
				break;
			case 2:
				SetPos(2 * i + CENTER, j);
				printf("��");
				break;
			default:break;
			}
		}
}
void think()  //�ж���Ҫ���ǵĵ㣬̫Զ�ľͲ��ÿ����ˣ���һ����֦�������������
{
	int i, j,a,b,k;
	for (i = 0; i < 15; i++)  //ȥ�����µĵ�
	{
		for (j = 0; j < 15; j++)
		{
			if (qipan[j][i] != 0)
			{
				needthink[j][i] = 0;
			}
		}
	}
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			k = 0;
			for (a = i - 2; a <= i + 2; a++)
				for (b = j - 2; b <= j + 2; b++)
				{
					if (a < 15 && a >= 0 && b < 15 && b >= 0 && qipan[b][a] != 0 && qipan[j][i] == 0)
					{
						needthink[j][i] = 1;
						k++;

					}
				}
			if (k == 0)
			{
				needthink[j][i] = 0;
			}
		}
	}
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			for(a=i-1;a<=i+1;a++)
				for (b = j - 1; b <= j + 1; b++)
				{
					if (a < 15 && a >= 0 && b < 15 && b >= 0 && qipan[b][a] != 0&&qipan[j][i]==0)
					{
						needthink[j][i]++;
					}
				}
		}
	}

	
}
void aido()
{
	int a, b, i, j, k = 0, maxi = 0, maxj = 0,mini,minj, max = -1000000, min = 1000000, current;

	for (i = 0; i < 15; i++)//��ȫ�ֶ�û�е��Ե��ӣ������ڿ�������ĵط�
	{
		for (j = 0; j < 15; j++)
		{
			if (qipan[j][i] == 1)
			{
				k++;
			}
		}
	}
	if (k == 0)
	{
		think();
		for (i = 0; i<15; i++)
			for (j = 0; j < 15; j++)
			{
				if (needthink[j][i] == 2)
				{
					qipan[j][i] = 1;
					return;
				}
			}
	}
	if (ifkill())
	{
		return;
	}
	for (i = 0; i<15; i++)
		for (j = 0; j < 15; j++)
		{
			think();
			if (needthink[j][i] >=1)
			{
				qipan[j][i] = 1;//������һ����
				think();
				for (b = 0; b<15; b++)
					for (a = 0; a < 15;  a++)
					{
						if (needthink[b][a] >=1)
						{
							qipan[b][a] = 2;  //�Է�������һ����
							if (evaluate() <= min)
							{
								min = evaluate();
								mini = a;
								minj = b;//Ѱ�ҶԵ�����˵������͵ĵ�
							}
							qipan[b][a] = 0;
						}
					}
				qipan[minj][mini] = 2;
				current = evaluate();//������������ľ�������
				qipan[minj][mini] = 0;
				if (current>=max)
				{
					max = current;
					maxi = i;
					maxj = j;
				}
				qipan[j][i] = 0;
				min = 1000000;
			}

		}
	qipan[maxj][maxi] = 1;
}
int victory()   
{
	int i, j, k, sum = 0, ret = 0;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 11; j++)
		{
			for (k = j; k < j + 5; k++)
			{
				if (qipan[k][i] == 2)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 2;
			}
			sum = 0;
		}
	}//  5����

	for (j = 0; j< 15; j++)
	{
		for (i = 0; i < 11; i++)
		{
			//if (qipan[j][i] == 2&&qipan[j][i + 1]==2&& qipan[j][i + 2]==2&&qipan[j][i + 3]==2&&  qipan[j][i+4]==2);
			for (k = i; k < i + 5; k++)
			{
				if (qipan[j][k] == 2)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 2;
			}
			sum = 0;
		}
	}//  5���

	for (j = 0; j< 15; j++)
	{
		for (i = 0; i < 11; i++)
		{
			for (k = i; k < i + 5; k++)
			{
				if (qipan[j][k] == 1)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 1;
			}
			sum = 0;
		}
	}//  5���

	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 11; j++)
		{
			for (k = j; k < j + 5; k++)
			{
				if (qipan[k][i] == 1)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 1;
			}
			sum = 0;
		}
	}//  5����

	for (j = 0; j < 11; j++)
	{
		for (i = 0; i < 11; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i + k] == 2)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 2;
			}
			sum = 0;
		}
	} //5������б

	for (j = 0; j < 11; j++)
	{
		for (i = 0; i < 11; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i + k] == 1)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 1;
			}
			sum = 0;
		}
	} //5������б

	for (j = 0; j < 11; j++)
	{
		for (i = 4; i < 15; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i - k] == 2)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 2;
			}
			sum = 0;
		}
	} //5������б

	for (j = 0; j < 11; j++)
	{
		for (i = 4; i < 15; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i - k] == 1)
				{
					sum = sum + 1;
				}
				if (sum == 5)
					return 1;
			}
			sum = 0;
		}
	} //5������б
	return 0;
}
int evaluate()
{

	int i, j, k, count, countPEOPLE = 0, countAI = 0, sum=0;
	/*�Է�����1700�����ҷ�����1600���ڶԷ�����1500�������ǻ���1400*/
	/*�������鼰��ϵ����ģ������������ΪҪ�ж��ĸ����򣬷ֺڰ���*/
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 11; j++)
		{
			for (k = j; k < j + 5; k++)
			{
				if (qipan[k][i] == 2)
				{
					sum = sum + 1;
				}
				if (qipan[k][i] == 1)
				{
					sum--;
				}
			}
			if (sum == 5)
				countPEOPLE = countPEOPLE + 100000;
			if (sum == 4)
				countPEOPLE = countPEOPLE + 1700;

			sum = 0;
		}
	}//  5����
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 11; i++)
		{
			for (k = i; k < i + 5; k++)
			{
				if (qipan[j][k] == 2)
				{
					sum = sum + 1;
				}
				if (qipan[j][k] == 1)
				{
					sum--;
				}
			}
			if (sum == 5)
				countPEOPLE = countPEOPLE + 100000;//return 2;
			if (sum == 4)
				countPEOPLE = countPEOPLE + 1700;
			sum = 0;
		}
	}//  5���
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 11; i++)
		{
			for (k = i; k < i + 5; k++)
			{
				if (qipan[j][k] == 1)
				{
					sum = sum + 1;
				}
				if (qipan[j][k] == 2)
				{
					sum--;
				}
			}
			if (sum == 5)
				countAI = countAI + 100000;//return 1;
			if (sum == 4)
				countAI = countAI + 1600;//return 1;
			sum = 0;
		}
	}//  5���
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 11; j++)
		{
			for (k = j; k < j + 5; k++)
			{
				if (qipan[k][i] == 1)
				{
					sum = sum + 1;
				}
				if (qipan[k][i] == 2)
				{
					sum--;
				}
			}
			if (sum == 5)
				countAI = countAI + 100000;//return 1;
			if (sum == 4)
				countAI = countAI + 1600;
			sum = 0;
		}
	}//  5����
	for (j = 0; j < 11; j++)
	{
		for (i = 0; i < 11; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i + k] == 2)
				{
					sum = sum + 1;
				}
				if (qipan[j+k][i+k] == 1)
				{
					sum--;
				}
			}
			if (sum == 5)
				countPEOPLE = countPEOPLE + 100000;//return 2;
			if (sum == 4)
				countPEOPLE = countPEOPLE + 1700;
			sum = 0;
		}
	} //5������б
	for (j = 0; j < 11; j++)
	{
		for (i = 0; i < 11; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i + k] == 1)
				{
					sum = sum + 1;
				}
				if (qipan[j+k][i+k] == 2)
				{
					sum--;
				}
			}
			if (sum == 5)
				countAI = countAI + 100000;//return 1;
			if (sum == 4)
				countAI = countAI + 1600;
			sum = 0;
		}
	} //5������б
	for (j = 0; j < 11; j++)
	{
		for (i = 4; i < 15; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i - k] == 2)
				{
					sum = sum + 1;
				}
				if (qipan[j+k][i-k] == 1)
				{
					sum--;
				}
			}
			if (sum == 5)
				countPEOPLE = countPEOPLE + 100000;//return 2;
			if (sum == 4)
				countPEOPLE = countPEOPLE + 1700;
			sum = 0;
		}
	} //5������б
	for (j = 0; j < 11; j++)
	{
		for (i = 4; i < 15; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (qipan[j + k][i - k] == 1)
				{
					sum = sum + 1;
				}
				if (qipan[j+k][i-k] == 2)
				{
					sum--;
				}
			}
			if (sum == 5)
				countAI = countAI + 100000;//return 1;
			if (sum == 4)
				countAI = countAI + 1600;
			sum = 0;
		}
	} //5������б

	/*����,��һ,���������*/
	for (j = 0; j < 15; j++)  //AI�� 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j][i + k] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countAI = countAI + 10000;
					break;
				case 1: //��һ 
					countAI = countAI + 10;				
					break;
				case 3: //���� 
					countAI = countAI + 1400;				
					break;
				case 2: //��� 
					countAI = countAI + 100;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 0; j < 15; j++)//people�� 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j][i + k] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 10000;
					break;
				case 1: //��һ 
					countPEOPLE = countPEOPLE + 10;
					break;
				case 3: //���� 
					countPEOPLE = countPEOPLE + 1500;
					break;
				case 2: //��� 
					countPEOPLE = countPEOPLE + 100;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (i = 0; i <15; i++)//AI�� 
	{
		for (j = 0; j <= 9; j++)
		{
			if (qipan[j][i] == 0 && qipan[j+5][i] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j+k][i] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countAI = countAI + 10000;
					break;
				case 1: //��һ 
					countAI = countAI + 10;
					break;
				case 3: //���� 
					countAI = countAI + 1400;
					break;
				case 2: //��� 
					countAI = countAI + 100;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (i = 0; i <15; i++)//people�� 
	{
		for (j = 0; j <= 9; j++)
		{
			if (qipan[j][i] == 0 && qipan[j + 5][i ] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j + k][i ] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 10000;
					break;
				case 1: //��һ 
					countPEOPLE = countPEOPLE + 10;					
					break;
				case 3: //���� 
					countPEOPLE = countPEOPLE + 1500;				
					break;
				case 2: //��� 
					countPEOPLE = countPEOPLE + 100;					
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 0; j <=9; j++)  //AI����б 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j+5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j+k][i + k] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countAI = countAI + 10000;
					break;
				case 1: //��һ 
					countAI = countAI + 10;
					break;
				case 3: //���� 
					countAI = countAI + 1400;
					break;
				case 2: //��� 
					countAI = countAI + 100;
					break;
				default:break;
				}
				sum = 0;
				/*for (k = 1; k <= 4; k++)
				{
					if (qipan[j + 5 - k][i + 5 - k] == 1)
					{
						j = j + 5 - k;
						i = i + 5 - k;
						break;
					}
				}*/
			}
		}
	}
	for (j = 0; j <= 9; j++)  //people����б 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j + 5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j + k][i + k] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 10000;
					break;
				case 1: //��һ 
					countPEOPLE = countPEOPLE + 10;
					break;
				case 3: //���� 
					countPEOPLE = countPEOPLE + 1500;
					break;
				case 2: //��� 
					countPEOPLE = countPEOPLE + 100;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 5; j < 15; j++)  //AI����б 
	{
		for (i = 0; i <=9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j-5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j-k][i + k] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countAI = countAI + 10000;
					break;
				case 1: //��һ 
					countAI = countAI + 10;
					break;
				case 3: //���� 
					countAI = countAI + 1400;
					break;
				case 2: //��� 
					countAI = countAI + 100;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 5; j < 15; j++)  //people����б 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j - 5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j - k][i + k] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 10000;
					break; 
				case 1: //��һ 
					countPEOPLE = countPEOPLE + 10;
					break;
				case 3: //���� 
					countPEOPLE = countPEOPLE + 1500;
					break;
				case 2: //��� 
					countPEOPLE = countPEOPLE + 100;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}

	/*�����ĸ�������*/
	for (j = 0; j < 15; j++)  //AI�� 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0&&qipan[j][i+5]==2 || qipan[j][i + 5] == 2&&qipan[j][i+5]==0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j][i + k] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //����
					countAI = countAI + 1600;
					break;  
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 0; j < 15; j++)//people�� 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j][i + 5] == 1||qipan[j][i] == 1 && qipan[j][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j][i + k] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 1700;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (i = 0; i <15; i++)//AI�� 
	{
		for (j = 0; j <= 9; j++)
		{
			if (qipan[j][i] == 0 && qipan[j + 5][i] == 2||qipan[j][i] == 2 && qipan[j + 5][i] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j + k][i] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countAI = countAI + 1600;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (i = 0; i <15; i++)//people�� 
	{
		for (j = 0; j <= 9; j++)
		{
			if (qipan[j][i] == 0 && qipan[j + 5][i] == 1||qipan[j][i] == 1 && qipan[j + 5][i] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j + k][i] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 1700;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 0; j <= 9; j++)  //AI����б 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j + 5][i + 5] == 2||qipan[j][i] == 2 && qipan[j + 5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j + k][i + k] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countAI = countAI + 1600;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 0; j <= 9; j++)  //people����б 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j + 5][i + 5] == 1||qipan[j][i] == 1 && qipan[j + 5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j + k][i + k] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 1700;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 5; j < 15; j++)  //AI����б 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j - 5][i + 5] == 2||qipan[j][i] == 2 && qipan[j - 5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j - k][i + k] == 1)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countAI = countAI + 1600;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}
	for (j = 5; j < 15; j++)  //people����б 
	{
		for (i = 0; i <= 9; i++)
		{
			if (qipan[j][i] == 0 && qipan[j - 5][i + 5] == 1||qipan[j][i] == 1 && qipan[j - 5][i + 5] == 0)
			{
				for (k = 1; k <= 4; k++)
				{
					if (qipan[j - k][i + k] == 2)
					{
						sum++;
					}
				}
				switch (sum)
				{
				case 4: //���� 
					countPEOPLE = countPEOPLE + 1700;
					break;
				default:break;
				}
				sum = 0;
			}
		}
	}

	count = countAI - countPEOPLE;
	return count;
	
}
int ifkill()
{
	int a,b,i, j,k=0,sum=0;
	think();//ȷ����������
	/*��Ӯ�Ǿ�ֱ����*/
	for (b = 0; b < 15; b++)
	{
		for (a = 0; a < 15; a++)
		{
			if (needthink[b][a] >= 1)
			{
				qipan[b][a] = 1;
				if (victory()==1)
				{
					return 1;
				}
				qipan[b][a] = 0;
			}
		}
	}
	int prev, current;
	for (b = 0; b < 15; b++)
	{
		for (a = 0; a < 15; a++)
		{
			if (needthink[b][a] >= 1)
			{
				
				/*�ж϶Է��Ƿ�������*/
				/*��ϵ�*/
				for (i = 0; i < 15; i++)
				{
					for (j = 0; j < 11; j++)
					{
						for (k = j; k < j + 5; k++)
						{
							if (qipan[k][i] == 2)
							{
								sum = sum + 1;
							}
							if (qipan[k][i] == 1)
							{
								sum = sum--;
							}
						}
						if (sum == 4) {
							qipan[b][a] = 0;
							return 0;
						}
						sum = 0;
					}
				}//  5����
				for (j = 0; j < 15; j++)
				{
					for (i = 0; i < 11; i++)
					{
						for (k = i; k < i + 5; k++)
						{
							if (qipan[j][k] == 2)
							{
								sum = sum + 1;
							}
							if (qipan[j][k] == 1)
							{
								sum = sum--;
							}
						}
						if (sum == 4) {
							qipan[b][a] = 0;
							return 0;
						}
						sum = 0;
					}
				}//  5���
				for (j = 0; j < 11; j++)
				{
					for (i = 0; i < 11; i++)
					{
						for (k = 0; k < 5; k++)
						{
							if (qipan[j + k][i + k] == 2)
							{
								sum = sum + 1;
							}
							if (qipan[j+k][i+k] == 1)
							{
								sum = sum--;
							}
						}
						if (sum == 4) {
							qipan[b][a] = 0;
							return 0;
						}
						sum = 0;
					}
				} //5������б
				for (j = 0; j < 11; j++)
				{
					for (i = 4; i < 15; i++)
					{
						for (k = 0; k < 5; k++)
						{
							if (qipan[j + k][i - k] == 2)
							{
								sum = sum + 1;
							}
							if (qipan[j+k][i-k] == 1)
							{
								sum = sum--;
							}
						}
						if (sum == 4) {
							qipan[b][a] = 0;
							return 0;
						}
						sum = 0;
					}
				} //5������б
				/*������*/
				for (j = 0; j < 15; j++)//people�� 
				{
					for (i = 0; i <= 9; i++)
					{
						if (qipan[j][i] == 0 && qipan[j][i + 5] == 1 || qipan[j][i] == 1 && qipan[j][i + 5] == 0)
						{
							for (k = 1; k <= 4; k++)
							{
								if (qipan[j][i + k] == 2)
								{
									sum++;
								}
							}
							if (sum == 4) {
								qipan[b][a] = 0;
								return 0;
							}
							sum = 0;
						}
					}
				}
				for (i = 0; i <15; i++)//people�� 
				{
					for (j = 0; j <= 9; j++)
					{
						if (qipan[j][i] == 0 && qipan[j + 5][i] == 1 || qipan[j][i] == 1 && qipan[j + 5][i] == 0)
						{
							for (k = 1; k <= 4; k++)
							{
								if (qipan[j + k][i] == 2)
								{
									sum++;
								}
							}
							if (sum == 4) {
								qipan[b][a] = 0;
								return 0;
							}
							sum = 0;
						}
					}
				}
				for (j = 0; j <= 9; j++)  //people����б 
				{
					for (i = 0; i <= 9; i++)
					{
						if (qipan[j][i] == 0 && qipan[j + 5][i + 5] == 1 || qipan[j][i] == 1 && qipan[j + 5][i + 5] == 0)
						{
							for (k = 1; k <= 4; k++)
							{
								if (qipan[j + k][i + k] == 2)
								{
									sum++;
								}
							}
							if (sum == 4) {
								qipan[b][a] = 0;
								return 0;
							}
							sum = 0;
						}
					}
				}
				for (j = 5; j < 15; j++)  //people����б 
				{
					for (i = 0; i <= 9; i++)
					{
						if (qipan[j][i] == 0 && qipan[j - 5][i + 5] == 1 || qipan[j][i] == 1 && qipan[j - 5][i + 5] == 0)
						{
							for (k = 1; k <= 4; k++)
							{
								if (qipan[j - k][i + k] == 2)
								{
									sum++;
								}
							}
							if (sum == 4) {
								qipan[b][a] = 0;
								return 0;
							}
							sum = 0;
						}
					}
				}

				/*�жϼ����Ƿ�������ɱ*/
				prev = evaluate();
				qipan[b][a] = 1;
				current = evaluate();
				if (current - prev >= 3500)
				{
					return 1;
				}
				qipan[b][a] = 0;
			}
		}
	}
	return 0;
}

int main()
	{
		START:
		SetPos(16, 17);
		system("color f2");
		char begin;
		printf("��ӭ���� ���컢 ����������Ϸ,���ڿ���ѡ��Ծ�ģʽ�����컢�����밴2�������밴1");
		while (begin = _getch())
		{
			if (begin=='2')
			{
				qipan[6][7] = 1;
				system("cls");
				break;
			}
			if (begin == '1')
			{
				system("cls");
				break;
			}
		}
		SetPos(16, 17);
		printf("���¿ո����ӣ�����r���������¿�ʼ��Ϸ���������л���Ӣ�����뷨��");
		int x = 7, y = 7;//�����ʼ��λ�ӣ�����û������
		prmap();
		SetPos(x * 2 + CENTER, y);
		printf("��");  //��ʼ����ͼ
		char ch;
		while (ch = _getch())
		{
			if (ch == ' ')  //����
			{
				if (qipan[y][x] != 0)
					continue;
				qipan[y][x] = 2;
				aido();
				prmap();
			}
			if (ch == 'r')  //���¡�r���������¿�ʼ��Ϸ
			{
				int i, j;
				for (j = 0; j < 15; j++)
				{
					for (i = 0; i < 15; i++)
					{
						qipan[j][i] = 0;
						needthink[j][i] =0 ;
					}
				}
				system("cls");
				goto START;
			}
			if (ch == -32)
			{
				prmap();
				SetPos(x * 2 + CENTER, y);
				printf("��");

				switch (_getch())
				{
				case 72: //��
					if (y > 0)
					{
						y = y - 1;
					}
					prmap();
					SetPos(x * 2 + CENTER, y);
					printf("��");
					break;
				case 80: //��
					if (y < 14)
					{
						y = y + 1;
					}
					prmap();
					SetPos(x * 2 + CENTER, y);
					printf("��");
					break;
				case 75: //��
					if (x > 0)
					{
						x = x - 1;
					}
					prmap();
					SetPos(x * 2 + CENTER, y);
					printf("��");
					break;
				case 77: //��
					if (x < 14)
					{
						x = x + 1;
					}
					prmap();
					SetPos(x * 2 + CENTER, y);
					printf("��");
					break;
				}
			}
			if (victory() != 0)
				break;
		}

		SetPos(16, 18);   //��ӡʤ�� 
		if (victory() == 1)
		{
			puts("�� win �Բ��𣬰��컢˺������!");
		}
		else if (victory() == 2)
		{
			puts("�� win ������˰��컢�������ƽ��!");
		}
		system("pause");
		return 0;
	}


