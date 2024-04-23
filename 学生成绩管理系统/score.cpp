#define  _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <windows.h>
#define   MAX_LEN 40                        //��ַ�
#define   STU_NUM 300                       // ����ѧ������
#define   COURSE_NUM 12                     // ���Ŀ��Կ�Ŀ��
#define   STU_MES	"a"
#define   COU_MES   "רҵ-------�༶��-------ѧ��-------����-------�γ̺�-------�γ���-------�ܷ�-----ѧ��----����----�ο���ʦ-------�γ�����"
int   n = 0, m = 0;					//ѧ������\�γ���

struct courseInf {
	char courseID[10];		//�γ̺�
	char courseName[20];	//�γ���
	float  credit;			//ѧ��			
	float corecredit;		//����			4/90-100  3.7/85-90  3.3/82-85  3.0/78-82  2.7/75-78  2.3/72-75  2.0/68-72  1.5/64-68  1.0/60-64  0/0-60
	float usual_score;		//ƽʱ�ɼ�
	float midterm_score;	//���гɼ�
	float fina_score;		//��ĩ�ɼ�
	float make_up_score=-1;	//�����ɼ�
	float exp_score;		//ʵ��ɼ�
	float total_score;		//�γ������ɼ�		//��ĩ�ɼ�*0.6+ƽʱ�ɼ�*0.4  ����Ϊ1.0
	int term;				//����ѧ��
	char teacher[20]="��";	//�ο���ʦ
	int type;				//�γ�����
};

//ѧ����Ϣ��� N�ſγ�

typedef struct student {
	char studentID[20];				//ѧ��
	char studentName[20];			//����
	char major[12];					//רҵ
	char className[12];				//�༶��
	char gender[10];				//�Ա�
	char nation[20] = "��";			//����
	char native[20] = "��";			//����
	struct courseInf course[COURSE_NUM];	//�ṹ�����������ɿγ���ϸ��Ϣ
	float totalscore=0;				//�ܳɼ�
	float totalCredit = 0;			//��ѧ��
	float totalCoreCredit = 0;		//�ܼ���
	float totalDegreeScore = 0;		//ѧλ���ܷ�
	float totalRequiredScore = 0;	//���޿��ܷ�
	float totalDegreeCredit = 0;	//ѧλ��ѧ��
	float totalRequiredCredit = 0;	//���޿�ѧ��
	float totalDegreeCoreCredit = 0;//ѧλ�μ���
	float totalRequiredCoreCredit = 0;//���޿μ���
	float avgscore = 0;				//ƽ���ɼ�
	float avgCredit = 0;			//ƽ��ѧ��
	float avgCoreCredit = 0;		//ƽ������
	float avgDegreeScore = 0;		//ѧλ��ƽ����
	float avgRequiredScore = 0;		//���޿�ƽ����
	float avgDegreeCredit = 0;		//ѧλ��ƽ��ѧ��
	float avgRequiredCredit = 0;	//���޿�ƽ��ѧ��
	float avgDegreeCoreCredit = 0;	//ѧλ��ƽ������
	float avgRequiredCoreCredit = 0;//���޿�ƽ������
	float avgOfCoreCredit = 0;		//ѧ��ƽ������   (����*ѧ��)�ܺ�/ѧ���ܺ�
	float GaokaoScore=-1;			//�߿��ɼ�
	char  brief_introduct[1000] = "��";//���
	int age=-1;						//����
}STU;

char make_up[STU_NUM][20];			//��������
int make_up_idx=0;					

char Coursetype[6][30] = {" ", "ѧλ��","רҵ���޿�","רҵѡ�޿�","�������޿�","����ѡ�޿�" };

//�����ܺ���
int   Menu(void);												//�˵�
void  ReadScore(STU stu[]);										//¼��ɼ�
void  DeleteStudent(STU stu[]);									//ɾ��ѧ����Ϣ
void  FixedStudentMessage(STU stu[]);							//�޸�ѧ����Ϣ
void  FixedStudentCourse(STU stu[]);							//�޸�ѧ���ɼ�
void  SearchbyNum(STU stu[]);									//ѧ�Ų���
void  SearchbyName(STU stu[]);									//��������
void  SearchbyClass(STU stu[]);									//�༶����
void  SortbyID(STU stu[], int l, int r);						//ѧ������
void  SortbyScoreUp(STU stu[], int l, int r);					//�ܷ���������
void  SortbyScoreDown(STU stu[], int l, int r);					//�ֽܷ�������
void  SortbyCourseScore(STU stu[], int l, int r,char couse[20]);//���γ�����
void  SortbyavgCoreCredit(STU stu[], int l, int r);				//��ѧ��ƽ����������
void  SortbyDegreeScore(STU stu[], int l, int r);				//��ѧλ���ܷ�����
void  SortbyRequiredScore(STU stu[], int l, int r);				//�����޿��ܷ�����
void  SortbyDegreeCoreCredit(STU stu[], int l, int r);			//��ѧλ��ƽ����������
void  SortbyRequiredCoreCredit(STU stu[], int l, int r);		//�����޿�ƽ����������
void  SortbyClassAvgCoreCredit(STU stu[], int l, int r);		//���༶ѧ��ƽ����������
void  SortbyName(STU stu[], int l, int r);						//�������ֵ���������
void  StaticScore(STU stu[]);									//ͳ�Ƽ����ʡ�������
void  StaticMakeUpList(STU stu[]);								//ͳ�Ʋ�������
void  RecodeMake_Up_Score(STU stu[]);							//¼�벹���ɼ�

//�������ܺ���
int   inputInt(int low, int high, const char description[30]);   //���������Ƿ�����
void  PrintStudentMessage(STU stui);							//�����һ��ѧ����Ϣ
void  PrintStudentAllMessage(STU stui);							//���һ����������Ϣ
void  PrintScore(STU stu[], char coursename[20]);				//��������˵��Ƴɼ�
void  PrintStudentbasicMessage(STU stu[]);						//��������˵Ļ�����Ϣ
void  CalculateScore(STU &stui,int i);							//����ɼ���ѧ�֡����㡢ƽ��ѧ�ּ���
void  SwapStudentMessage(STU &stui, STU &stuj);					//��������ѧ����Ϣ
float findscore(STU stui, char n[20]);						//�ҿγ̳ɼ�
int   findId(STU stu[], char name[20]);							//��ѧ��
void  test(STU stu[]);

int   main(void)
{
	STU stu[STU_NUM];
	int choice;
	test(stu);
	while (1)
	{
		choice = Menu();						// ��ʾ�˵�������ȡ�û����� 
		switch (choice)	
		{
		case 1:
			ReadScore(stu);						//¼��ѧ��������Ϣ�ͳɼ�
			break;
		case 2:
			DeleteStudent(stu);					//ɾ��ѧ��������Ϣ
			break;
		case 3:
			FixedStudentMessage(stu);			//�޸�ѧ����Ϣ
			break;
		case 4:
			FixedStudentCourse(stu);			//�޸�ѧ���γ�
			break;
		case 5:
			SearchbyNum(stu);					//��ѧ�Ų���ѧ��
			break;
		case 6:
			SearchbyName(stu);					//����������ѧ��
			break;
		case 7:
			SearchbyClass(stu);					//���༶����ѧ��
			break;
		case 8:
			SortbyID(stu, 0, n-1);				//��ѧ������
			PrintStudentbasicMessage(stu);
			break;
		case 9:
			SortbyScoreUp(stu, 0, n - 1);			//���ܷ���������
			PrintStudentbasicMessage(stu);
			break;
		case 10:
			SortbyScoreDown(stu, 0, n - 1);			//���ֽܷ�������
			PrintStudentbasicMessage(stu);
			break;
		case 11:
			char mes[20];
			strcpy(Coursetype[0], mes);
			SortbyCourseScore(stu, 0, n - 1 ,mes);	//���γ�����
			PrintStudentbasicMessage(stu);
			break;
		case 12:
			SortbyavgCoreCredit(stu, 0, n - 1);		//��ƽ��ѧ�ּ�������
			PrintStudentbasicMessage(stu);
			break;
		case 13:
			SortbyDegreeScore(stu, 0, n - 1);		//��ѧλ���ܷ�����
			PrintStudentbasicMessage(stu);
			break;
		case 14:
			SortbyRequiredScore(stu, 0, n - 1);		//�����޿��ܷ�����
			PrintStudentbasicMessage(stu);
			break;
		case 15:
			SortbyDegreeCoreCredit(stu, 0, n - 1);	//��ѧλ��ƽ����������
			PrintStudentbasicMessage(stu);
			break;
		case 16:
			SortbyRequiredCoreCredit(stu, 0, n - 1);//�����޿�ƽ����������
			PrintStudentbasicMessage(stu);
			break;
		case 17:
			SortbyClassAvgCoreCredit(stu, 0, n - 1);//���༶ƽ��ѧ�ּ�������
			break;
		case 18:
			SortbyName(stu, 0, n - 1);				//�������ֵ���������
			PrintStudentbasicMessage(stu);
			break;
		case 19:
			StaticScore(stu);						//ͳ�Ƽ����ʣ�������
			break;
		case 20:
			StaticMakeUpList(stu);					//ͳ�Ʋ�������
			break;
		case 21:
			RecodeMake_Up_Score(stu);				//¼�벹���ɼ�
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			break;
		case 0:
			printf("�������!");
			exit(0);
		default:
			printf("��������!");
		}
		system("pause");
		system("cls");
	}
	return 0;
}
//  �������ܣ���ʾ�˵�������û����������ѡ��
int   Menu(void)
{
	int itemSelected;
	printf("  ----------------------------------------------------------------------------------------------------------------------\n");
	printf("  |						ѧ���ɼ�����ϵͳ��%3d/%3d��																			|\n", n, STU_NUM);
	printf("  |--------------------------------------------------------------------------------------------------------------------|\n");
	printf("  |																												|\n");
	printf("  |		1.¼��ѧ��������Ϣ�ͳɼ�					15.��ѧλ��ƽ����������									|\n");
	printf("  |		2.ɾ��ѧ��������Ϣ						16.�����޿�ƽ����������				|\n");
	printf("  |		3.�޸�ѧ��������Ϣ						17.���༶ƽ��ѧ�ּ�������				|\n");
	printf("  |		4.�޸�ѧ���γ���Ϣ						18.�������ֵ���������				|\n");
	printf("  |		5.����ѧ��--����						19.ͳ�Ƽ����ʡ�������				|\n");
	printf("  |		6.����ѧ��--ѧ��						20.ͳ�Ʋ�������				|\n");
	printf("  |		7.����ѧ��--�༶						21.¼�벹���ɼ�				|\n");
	printf("  |		8.��ѧ������							22.����ÿ�ſγ̵�ƽ���֡���߷ֺ���ͷ�					|\n");
	printf("  |		9.���ܷ���������						23.¼��ѧ������������Ϣ				|\n");
	printf("  |		10.���ֽܷ�������						24.���ѧ������������Ϣ				|\n");
	printf("  |		11.��ÿ�ſγ̳ɼ�����						25.ȡ�����ļ�						|\n");
	printf("  |		12.��ѧ��ƽ����������						26.д�뱾���ļ�									|\n");
	printf("  |		13.��ѧλ���ܷ����� 																|\n");
	printf("  |		14.�����޿��ܷ����� 																|\n");
	printf("  |										0.�˳�													|\n");
	printf("  |																														|\n");
	printf("  ----------------------------------------------------------------------------------------------------------------------\n");
	printf("���������ѡ��:");
	itemSelected = inputInt(0, 25, "ѡ�����"); 	// �����û����룬�Ϸ�����
	if ((m == 0 || n==0)&& itemSelected!=24)
	{
		printf("--�����б�Ϊ�ջ���뱾���ļ��⣬����󲻿��޸�!--\n");
		printf("����ѧ���γ���(�γ���<=%d):", COURSE_NUM);
		m = inputInt(1, COURSE_NUM, "�γ���");
	}
	if (n == 0&& itemSelected!=1 && itemSelected != 25 && itemSelected != 24 && itemSelected != 0)
	{
		printf("----------�ɼ���Ϊ�գ���¼��ѧ��-------\n");
		return -1;
	}
	return itemSelected;
}
// �������ܣ�����n��ѧ����m�ſγɼ�
void  ReadScore(STU stu[])
{
	int i, j,num ;
	printf("¼������(0<����<%d)��",STU_NUM);
	num = inputInt(0, STU_NUM-n, "����");
	for (int i = 0; i < num; n++,i++)
	{
		printf("�����%d��ѧ����ѧ�ţ�",i+1);
		scanf("%s",stu[i].studentID);
		printf("�����%d��ѧ����������", i + 1);
		scanf("%s", stu[i].studentName);
		printf("����ѧ��'%s'��רҵ��", stu[i].studentName);
		scanf("%s", stu[i].major);
		printf("����ѧ��'%s'�İ༶��", stu[i].studentName);
		scanf("%s", stu[i].className);
		printf("����ѧ��'%s'���Ա�", stu[i].studentName);
		scanf("%s", stu[i].gender);
		for (int j = 0; j < m; j++)
		{
			printf("�����%d�ſγ̵Ŀ���ѧ�ڣ�", j + 1);
			scanf("%d", &stu[i].course[j].term);
			printf("�����%d�ſγ̵Ŀγ̺�:",j+1);
			scanf("%s", stu[i].course[j].courseID);
			printf("�����%d�ſγ̵Ŀγ�����", j + 1);
			scanf("%s",stu[i].course[j].courseName);
			printf("����γ�%s���ο���ʦ��", stu[i].course[j].courseName);
			scanf("%s", stu[i].course[j].teacher);
			printf("����γ�%s��ѧ�֣�", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].credit);
			printf("����γ�%s��ƽʱ�֣�", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].usual_score);
			printf("����γ�%s�����гɼ���", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].midterm_score);
			printf("����γ�%s����ĩ�ɼ���", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].fina_score);
			printf("����γ�%s��ʵ��ɼ���", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].exp_score);
			printf("����γ�%s�Ŀγ������ɼ���", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].total_score);
			printf("�γ�����--��1ѧλ�Σ�2רҵ���޿Σ�3רҵѡ�޿Σ�4�������޿Σ�5����ѡ�޿�)\n");
			printf("����γ�%s�Ŀγ����� 0<num<6:", stu[i].course[j].courseName);
			stu[i].course[j].type = inputInt(1, 5, "�γ�����");
		}
		CalculateScore(stu[i],i);
		printf("-------------¼��ɹ���%3d/%3d��--------\n", n+1, STU_NUM);
		if (n + 1 >= STU_NUM) { 
		printf("-------------��������-------------------\n"); break; }
	}
	
}
//�������ܣ�ɾ��ѧ����Ϣ
void  DeleteStudent(STU stu[])
{
	int num;
	char ch;
	printf("����ɾ��ѧ����������");
	num = inputInt(0, n, "ɾ������");
	while (num--)
	{
		int same[STU_NUM], idx = 0;
		char mes[20];
		printf("����ѧ����ѧ�Ż�����ɾ��ѧ��");
		scanf("%s", mes);
		getchar();
		for (int i = 0; i < n; i++)
		{
			if (strcmp(mes, stu[i].studentID) == 0 || strcmp(mes, stu[i].studentName) == 0)
			{
				PrintStudentMessage(stu[i]);
				same[idx++] = i;
			}
		}
		int choice = same[0];
		if (idx > 1)
		{
			printf("��ѯ��%d����ͬ'%s'��Ϣѧ����ѡ���������еڣ�������ѧ����", idx, mes);
			choice = same[inputInt(1, idx, "���")-1];
		}
		else if (idx == 0)
		{
			printf("-------����ʧ�ܣ���������ȷ��Ϣ!--------\n");
			continue;
		}
		printf("����Yȷ��ɾ���������ȡ������");
		ch = getchar();
		if (ch == 'Y' || ch == 'y')
		{
			for (int j = choice; j < n - 1; j++) {
				stu[j] = stu[j + 1];
			}
			n--;
		}
			printf("----------------ɾ���ɹ�!--------------\n");

	}
}
//�������ܣ��޸�ѧ����Ϣ
void  FixedStudentMessage(STU stu[])
{
	int num;
	printf("�����޸�ѧ����������");
	num = inputInt(0, n, "�޸�����");
	while (num--)
	{
		int same[STU_NUM], idx = 0;
		char mes[20];
		printf("����ѧ����ѧ�Ż�������");
		scanf("%s", mes);
		getchar();
		for (int i = 0; i < n; i++)
		{
			if (strcmp(mes, stu[i].studentID) == 0 || strcmp(mes, stu[i].studentName) == 0)
			{
				PrintStudentMessage(stu[i]);
				same[idx++] = i;
			}
		}
		int choice = same[0];
		if (idx > 1)
		{
			printf("��ѯ��%d����ͬ'%s'��Ϣѧ����ѡ���������еڣ�������ѧ����", idx, mes);
			choice = same[inputInt(1, idx, "���")-1];
		}
		else if (idx == 0)
		{
			printf("-------����ʧ�ܣ���������ȷ��Ϣ!--------\n");
			continue;
		}
		printf("ԭ��Ϣ��\n");
		int i = choice;
		printf("ѧ�ţ�%s ������%s רҵ��%s �༶��%s �Ա�%s\n",stu[i].studentID , stu[i].studentName, stu[i].major, stu[i].className, stu[i].gender);
		printf("�޸�ѧ����ѧ�ţ�");
		scanf("%s", stu[i].studentID);
		printf("�޸�ѧ����������");
		scanf("%s", stu[i].studentName);
		printf("�޸�ѧ��%s��רҵ��", stu[i].studentName);
		scanf("%s", stu[i].major);
		printf("�޸�ѧ��%s�İ༶��", stu[i].studentName);
		scanf("%s", stu[i].className);
		printf("�޸�ѧ��%s���Ա�", stu[i].studentName);
		scanf("%s", stu[i].gender);
		printf("�޸ĺ���Ϣ��\n");
		printf("ѧ�ţ�%s ������%s רҵ��%s �༶��%s �Ա�%s\n", stu[i].studentID, stu[i].studentName, stu[i].major, stu[i].className,stu[i].gender);
			printf("--------------------�޸ĳɹ�!-------------\n");
	}
}
//�������ܣ��޸�ѧ���γ���Ϣ
void  FixedStudentCourse(STU stu[])
{

	int num;
	printf("�����޸�ѧ����������");
	num = inputInt(0, n, "�޸�����");
	while (num--)
	{
		int same[STU_NUM], idx = 0;
		char mes[20];
		printf("����ѧ����ѧ�Ż�������");
		scanf("%s", mes);
		for (int i = 0; i < n; i++)
		{
			if (strcmp(mes, stu[i].studentID) == 0 || strcmp(mes, stu[i].studentName) == 0)
			{
				PrintStudentMessage(stu[i]);
				same[idx++] = i;
			}
		}
		int choice = same[0];
		if (idx > 1)
		{
			printf("��ѯ��%d����ͬ'%s'��Ϣѧ����ѡ���������еڣ�������ѧ����", idx, mes);
			choice = same[inputInt(1, idx, "���") - 1];
		}
		else if (idx == 0)
		{
			printf("----------����ʧ�ܣ���������ȷ��Ϣ!----------\n");
			continue;
		}
		printf("�����޸ĵĿγ̺Ż�γ�����");
		scanf("%s", mes);
		for (int j = 0,i=choice; j < m; j++)
		{
			if (strcmp(mes, stu[i].course[j].courseID) == 0 || strcmp(mes, stu[i].course[j].courseName) == 0)
			{
				printf("�޸Ŀγ̵Ŀ���ѧ�ڣ�");
				scanf("%d", &stu[i].course[j].term);
				printf("�޸Ŀγ̵Ŀγ̺�:");
				scanf("%s", stu[i].course[j].courseID);
				printf("�޸Ŀγ̵Ŀγ�����");
				scanf("%s", stu[i].course[j].courseName);
				printf("�޸Ŀγ�%s���ο���ʦ��", stu[i].course[j].courseName);
				scanf("%s", stu[i].course[j].teacher);
				printf("�޸Ŀγ�%s��ѧ�֣�", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].credit);
				printf("�޸Ŀγ�%s��ƽʱ�֣�", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].usual_score);
				printf("�޸Ŀγ�%s�����гɼ���", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].midterm_score);
				printf("�޸Ŀγ�%s����ĩ�ɼ���", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].fina_score);
				printf("�޸Ŀγ�%s��ʵ��ɼ���", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].exp_score);
				printf("�޸Ŀγ�%s�Ŀγ������ɼ���", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].total_score);
				printf("�γ�����--��1ѧλ�Σ�2רҵ���޿Σ�3רҵѡ�޿Σ�4�������޿Σ�5����ѡ�޿�)\n");
				printf("�޸Ŀγ�%s�Ŀγ����� 0<num<6:", stu[i].course[j].courseName);
				stu[i].course[j].type = inputInt(1, 5, "�γ�����");
				printf("----------------�޸ĳɹ���-------------------\n");
				break;
			}
		}
	}
}
//�������ܣ���ѧ�Ų���ѧ����Ϣ
void  SearchbyNum(STU stu[])
{
	int num,i;
	printf("�������ѧ���Ĵ�����");
	num = inputInt(0, n, "�޸�����");
	while (num--)
	{
		char mes[20];
		printf("����ѧ����ѧ�ţ�");
		scanf("%s", mes);
		for (i = 0; i < n; i++)
		{
			if (strcmp(mes, stu[i].studentID) == 0 )
			{
				PrintStudentAllMessage(stu[i]);
				break;
			}
		}
		if (i == n)printf("-------------����ʧ�ܣ���������ȷ��Ϣ!--------\n");
	}
}
//�������ܣ�����������ѧ����Ϣ
void  SearchbyName(STU stu[])
{
	int num,i;
	printf("�������ѧ���Ĵ�����");
	num = inputInt(0, n, "�޸�����");
	while (num--)
	{
		char mes[20];
		printf("����ѧ����ѧ�ţ�");
		scanf("%s", mes);
		getchar();
		for (i = 0; i < n; i++)
		{
			if (strcmp(mes, stu[i].studentName) == 0)
			{
				PrintStudentAllMessage(stu[i]);
				break;
			}
		}
		if (i == n)printf("--------����ʧ�ܣ���������ȷ��Ϣ!------\n");
	}
}
//�������ܣ����༶����ѧ����Ϣ
void  SearchbyClass(STU stu[])
{
	char mes[20];
	int clas[STU_NUM],idx=0;
	printf("����༶����");
	scanf("%s", mes);
	getchar();
	for (int i = 0; i < n; i++)
	{
		if (strcmp(mes, stu[i].className) == 0)
		{
			PrintStudentMessage(stu[i]);
			clas[idx++] = i;
			break;
		}
	}
	if(idx==0)printf("----------����ʧ�ܣ���������ȷ��Ϣ------\n");
}
//�������ܣ���ѧ������
void  SortbyID(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1,j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j&&strcmp(stu[mid].studentID,stu[i].studentID)>0);
		do j--; while (i < j && strcmp(stu[mid].studentID, stu[j].studentID) <= 0);
		if(i<j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyID(stu, l, j);
	SortbyID(stu, j + 1, r);
}
//�������ܣ����ܷ���������
void  SortbyScoreUp(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && stu[mid].totalscore > stu[i].totalscore);
		do j--; while (i < j && stu[mid].totalscore <= stu[j].totalscore);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyScoreUp(stu, l, j);
	SortbyScoreUp(stu, j + 1, r);
}
//�������ܣ����ֽܷ�������
void  SortbyScoreDown(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && stu[mid].totalscore < stu[i].totalscore);
		do j--; while (i < j && stu[mid].totalscore >= stu[j].totalscore);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyScoreDown(stu, l, j);
	SortbyScoreDown(stu, j + 1, r);
}
//�������ܣ���ÿ�ſγ̳ɼ�����
void  SortbyCourseScore(STU stu[],int l,int r,char coursename[20])
{
	while (l == 0 &&r==n-1&& strcmp(coursename, Coursetype[0]) == 0)
	{
		printf("����γ̺Ž�������");
		scanf("%s", coursename);
		if (strcmp(coursename, Coursetype[0]) == 0)printf("��������հ׿γ̺�!\n");
	}
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		float m_s, i_s, j_s;
		m_s = findscore(stu[mid],coursename);
		do i++, i_s = findscore(stu[i], coursename); while (i < j && i_s<m_s);
		do j--, j_s = findscore(stu[j], coursename); while (i < j && j_s>=m_s);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyCourseScore(stu, l, j, coursename);
	SortbyCourseScore(stu, j + 1, r, coursename);

}
//�������ܣ���ƽ��ѧ�ּ�������
void  SortbyavgCoreCredit(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && stu[mid].avgOfCoreCredit> stu[i].avgOfCoreCredit);
		do j--; while (i < j && stu[mid].avgOfCoreCredit<= stu[j].avgOfCoreCredit);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyID(stu, l, j);
	SortbyID(stu, j + 1, r);
}
//�������ܣ���ѧλ���ܷ�����
void  SortbyDegreeScore(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && stu[mid].totalDegreeScore > stu[i].totalDegreeScore);
		do j--; while (i < j && stu[mid].totalDegreeScore <= stu[j].totalDegreeScore);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyScoreUp(stu, l, j);
	SortbyScoreUp(stu, j + 1, r);
}
//�������ܣ������޿��ܷ�����
void  SortbyRequiredScore(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && stu[mid].totalRequiredScore > stu[i].totalRequiredScore);
		do j--; while (i < j && stu[mid].totalRequiredScore <= stu[j].totalRequiredScore);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyScoreUp(stu, l, j);
	SortbyScoreUp(stu, j + 1, r);
}
//�������ܣ���ѧλ��ƽ����������
void  SortbyDegreeCoreCredit(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && stu[mid].avgDegreeCoreCredit > stu[i].avgDegreeCoreCredit);
		do j--; while (i < j && stu[mid].avgDegreeCoreCredit <= stu[j].avgDegreeCoreCredit);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyScoreUp(stu, l, j);
	SortbyScoreUp(stu, j + 1, r);
}
//�������ܣ������޿�ƽ����������
void  SortbyRequiredCoreCredit(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && stu[mid].avgRequiredCoreCredit > stu[i].avgRequiredCoreCredit);
		do j--; while (i < j && stu[mid].avgRequiredCoreCredit <= stu[j].avgRequiredCoreCredit);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyScoreUp(stu, l, j);
	SortbyScoreUp(stu, j + 1, r);
}
//�������ܣ��������ֵ���������
void  SortbyName(STU stu[], int l, int r)
{
	if (l >= r)return;
	int i = l - 1, j = r + 1;
	while (i < j)
	{
		int mid = i + j / 2;
		do i++; while (i < j && strcmp(stu[mid].studentName ,stu[i].studentName)>0);
		do j--; while (i < j && strcmp(stu[mid].studentName ,stu[j].studentName)<=0);
		if (i < j)SwapStudentMessage(stu[i], stu[j]);
	}
	SortbyScoreUp(stu, l, j);
	SortbyScoreUp(stu, j + 1, r);
}
//�������ܣ�ͳ�Ƽ����ʡ�������
void  StaticScore(STU stu[])
{
	char CourseName[600][20];
	int idx = 0;
	printf("�γ̺�---�γ���---�γ�����---�ο���ʦ---�����ʣ�����80��-�����ʣ�����60��-�����ʣ�����60��\n");
	for (int i = 0; i < m; i++)
	{
		int good = 0, fine = 0, bad = 0;
		for (int j = 0; j < n; j++)
		{
			if (stu[j].course[i].total_score >= 80)good++;
			else if (stu[j].course[i].total_score >= 60)fine++;
			else bad++;
		}
		printf("|%s\t|%s\t|%s\t|%s\t|%.1f\t|%.1f\t|%.1f\n", stu[0].course[i].courseID, stu[0].course[i].courseName, Coursetype[stu[0].course[i].type], stu[0].course[i].teacher, 1.0 * good / m, 1.0 * fine / m, 1.0*bad / m);
	}
	printf("-----------------ͳ����ɣ�-------------\n");
}
//�������ܣ�ͳ�Ʋ�������
void  StaticMakeUpList(STU stu[])
{
	if (make_up_idx == 0)printf("  ---------------------�޲�����Ա-----------------\n");
		printf("רҵ-------�༶-------ѧ��-------����-----�Ա�---��ѧ��--ƽ��ѧ�ּ���---�γ���+�ɼ�...\n");
	for (int k = 0; k < make_up_idx; k++)
	{
		int i = findId(stu,make_up[k]);
		if (i == -1)continue;
		printf("|%s\t|%s\t|%s\t|%s\t|%s\t|%.1f\t|%.1f\t", stu[i].major, stu[i].className, stu[i].studentID, stu[i].studentName, stu[i].gender, stu[i].totalCredit, stu[i].avgOfCoreCredit);
		for (int j = 0; j < m; j++)
		{
			if(stu[i].course[j].total_score<60)
			printf("|%s+%.1f\t", stu[i].course[j].courseName, stu[i].course[j].total_score);
		}printf("|\n");
	}
}
//�������ܣ�¼�벹���ɼ�
void RecodeMake_Up_Score(STU stu[])
{
	if (make_up_idx == 0)printf("  ---------------------�޲�����Ա-----------------\n");
	for (int k = make_up_idx-1; k >= 0; k--,make_up_idx--)
	{
		int i = findId(stu,make_up[k]);
		if (i == -1)continue;
		for (int j = 0; j < m; j++)
		{
			if (stu[i].course[j].total_score < 60)
			{
				printf("����ѧ��%s�Ŀγ�%s�����ɼ���", stu[i].studentName,stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].make_up_score);
			}
		}
		CalculateScore(stu[i],i);
	}
}
//�������ܣ����༶ѧ��ƽ����������

/*�������ܺ���*/

//��������
int inputInt(int low, int high, const char description[30])
{
	int temp;
	char c;
	scanf_s("%d", &temp);
	while (temp<low || temp>high)
	{
		printf("����%s������ڵ���%d��С�ڵ���%d\n���������룺", description, low, high);
		while ((c = getchar()) != '\n');
		scanf_s("%d", &temp);
	}
	return temp;
}
//������˸��μ���
void  CalculateScore(STU &stui,int i)
{
	float t=0, t_1=0, t_2=0 ,t_c_s=0;			//�ܷ�	ѧλ-  ����-  ѧ�ּ���
	float c = 0, c_1 = 0, c_2 = 0;	//����
	float s = 0, s_1 = 0, s_2 = 0;	//ѧ��
	for (int j=0;j<m;j++)
	{
		//4 / 90 - 100  3.7 / 85 - 90  3.3 / 82 - 85  3.0 / 78 - 82  2.7 / 75 - 78  2.3 / 72 - 75  2.0 / 68 - 72  1.5 / 64 - 68  1.0 / 60 - 64  0 / 0 - 60
		//stui.course[j].total_score = stui.course[j].fina_score * 0.6 + stui.course[j].usual_score * 0.4;
		if (stui.course[j].total_score >= 90.0)stui.course[j].corecredit = 4;
		else if (stui.course[j].total_score >= 85.0)stui.course[j].corecredit = 3.7;
		else if (stui.course[j].total_score >= 82.0)stui.course[j].corecredit = 3.3;
		else if (stui.course[j].total_score >= 78.0)stui.course[j].corecredit = 3.0;
		else if (stui.course[j].total_score >= 75.0)stui.course[j].corecredit = 2.7;
		else if (stui.course[j].total_score >= 72.0)stui.course[j].corecredit = 2.3;
		else if (stui.course[j].total_score >= 68.0)stui.course[j].corecredit = 2.0;
		else if (stui.course[j].total_score >= 64.0)stui.course[j].corecredit = 1.5;
		else if (stui.course[j].total_score >= 60.0|| stui.course[j].make_up_score >= 60)stui.course[j].corecredit = 1.0;
		else if (stui.course[j].make_up_score==-1){
			stui.course[j].corecredit = 0;
			strcpy(make_up[make_up_idx], stui.studentID) ;
			make_up_idx++;
		}
		if (stui.course[j].type == 1)
		{
			t_1 += stui.course[j].total_score;
			c_1 += stui.course[j].corecredit;
			s_1 += stui.course[j].credit;
		}
		else if (stui.course[j].type == 2)
		{
			t_2 += stui.course[j].total_score;
			c_2 += stui.course[j].corecredit;
			s_2 += stui.course[j].credit;
		}
		t += stui.course[j].total_score;
		c += stui.course[j].corecredit;
		s += stui.course[j].credit;
		t_c_s += stui.course[j].corecredit * stui.course[j].credit;
	}
	stui.totalscore = t;
	stui.totalCoreCredit = c;	//����
	stui.totalCredit = s;		//ѧ��
	stui.avgscore = m > 0 ? t / m : -1;
	stui.avgCoreCredit = m > 0 ? c / m : -1;
	stui.avgCredit = m > 0 ? s / m : -1;
	stui.totalDegreeScore = t_1;  //ѧλ��
	stui.totalDegreeCoreCredit = c_1;
	stui.totalDegreeCredit = s_1;
	stui.avgDegreeScore = m > 0 ? t_1 / m : -1;
	stui.avgDegreeCoreCredit = m > 0 ? c_1 / m : -1;
	stui.avgDegreeCredit = m > 0 ? s_1 / m : -1;
	stui.totalRequiredScore = t_2;  //���޿�
	stui.totalRequiredCoreCredit = c_2;
	stui.totalRequiredCredit = s_2;
	stui.avgRequiredScore = m > 0 ? t_2 / m : -1;
	stui.avgRequiredCoreCredit = m > 0 ? c_2 / m : -1;
	stui.avgRequiredCredit = m > 0 ? s_2 / m : -1;
	//ƽ��ѧ�ּ���
	stui.avgOfCoreCredit = s>0?t_c_s / s:0;
	printf("---------%s�ļ��㣬ƽ�����㣬ƽ��ѧ�ּ���...�Ѹ��£�---------\n",stui.studentName);
}
//���һ��ѧ����Ϣ
void PrintStudentMessage(STU stui)
{
	printf("רҵ-------�༶-------ѧ��-------����-----�Ա�---��ѧ��--ѧ��ƽ������---�γ���...\n");
	printf("|%s\t|%s\t|%s\t|%s\t|%s\t|%.1f\t|%.1f\t", stui.major, stui.className, stui.studentID, stui.studentName, stui.gender,stui.totalCredit,stui.avgOfCoreCredit);
	for (int j = 0; j < m; j++)
	{
		printf("|%s\t", stui.course[j].courseName);
	}printf("|\n");
}
//���һ��ѧ��������Ϣ
void PrintStudentAllMessage(STU stui)
{
	printf("רҵ-------�༶-------ѧ��-------����-------�Ա�----����----����-----����-----�߿��ܷ�----���\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("|%s\t|%s\t|%s\t|%s\t|%s\t|%d\t|%s\t|%s\t|%1.f|%s\t|\n", stui.major, stui.className, stui.studentID, stui.studentName, stui.gender,stui.age,stui.nation,stui.native,stui.GaokaoScore,stui.brief_introduct);
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("�γ̺�----�γ���--------�ο���ʦ-----�γ�����------����ѧ��\n");
	printf("ƽʱ��---���гɼ�---��ĩ�ɼ�---ʵ��ɼ�---�����ɼ�---�γ������ɼ�----ѧ��----����\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < m; i++)
	{
		printf("|%s\t|%s\t|%s\t|%s\t|%d\t|\n", stui.course[i].courseID, stui.course[i].courseName, stui.course[i].teacher, Coursetype[stui.course[i].type], stui.course[i].term);
		printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.course[i].usual_score, stui.course[i].midterm_score, stui.course[i].fina_score, stui.course[i].exp_score, stui.course[i].make_up_score,stui.course[i].total_score, stui.course[i].credit, stui.course[i].corecredit);
		if(i<m-1)printf("-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  \n");
	}
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("�����ܷ�----��ѧ��----�ܼ���---ƽ����---ƽ��ѧ��---ƽ������---ѧ��ƽ������\n");
	printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.totalscore, stui.totalCredit, stui.totalCoreCredit,stui.avgscore,stui.avgCredit,stui.avgCoreCredit, stui.avgOfCoreCredit);
	printf("ѧλ���ܷ�--ѧλ��ѧ��--ѧλ�μ���--ѧλ��ƽ����--ѧλ��ƽ��ѧ��--ѧλ��ƽ������\n");
	printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.totalDegreeScore, stui.totalDegreeCredit, stui.totalDegreeCoreCredit, stui.avgDegreeScore, stui.avgDegreeCredit, stui.avgDegreeCoreCredit);
	printf("���޿��ܷ�--���޿�ѧ��--���޿μ���--���޿�ƽ����--���޿�ƽ��ѧ��--���޿�ƽ������\n");
	printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.totalRequiredScore, stui.totalRequiredCredit, stui.totalRequiredCoreCredit, stui.avgRequiredScore, stui.avgRequiredCredit, stui.avgRequiredCoreCredit);

}
//�������ѧ��������Ϣ
void PrintStudentbasicMessage(STU stu[])
{
	printf("רҵ------�༶-----ѧ��-----����----�Ա�---��ѧ��/ѧ��ƽ������---ѧλ���ܷ�/ƽ������---���޿��ܷ�/ƽ������---�γ���...\n");
	for (int i = 0; i < n; i++)
	{
		printf("|%s\t|%s\t|%s\t|%s\t|%s\t|%.1f//%.1f\t|%.1f//%.1f\t|%.1f//%.1f\t", stu[i].major, stu[i].className, stu[i].studentID, stu[i].studentName, stu[i].gender, stu[i].totalCredit, stu[i].avgOfCoreCredit,stu[i].totalDegreeScore,stu[i].avgDegreeCoreCredit, stu[i].totalRequiredScore,stu[i].avgRequiredCoreCredit);
		for (int j = 0; j < m; j++)
		{
			printf("|%s\t", stu[i].course[j].courseName);
		}printf("|\n");
	}
	
}
//�������ѧ�����Ƴɼ�
void PrintScore(STU stu[],char coursename[20])
{
	float t = 0, t_c = 0, t_s = 0,num=0;
	printf("רҵ-------�༶-------ѧ��-----����----�γ���---�ܷ�/ѧ��/����/ѧ��ƽ������--�ο���ʦ--�γ�����--����ѧ��\n");
	for (int i = 0; i < n; i++)
	{
		//printf("|%s\t|%s\t|%s\t|%s\t|%s\t", stu[i].major, stu[i].className,stu[i].studentID, stu[i].studentName);
		//printf("|%.1f//%.1f//%.1f//%.1f\t", stu[i].totalscore, stu[i].totalCredit, stu[i].totalCoreCredit, stu[i].avgOfCoreCredit);
		for (int j = 0; j < m; j++)
		{
			if (strcmp(coursename, stu[i].course[j].courseName) == 0)
			{
				num++;
				t += stu[i].course[j].total_score;
				t_c += stu[i].course[j].corecredit;
				t_s += stu[i].course[j].credit;
				printf("|%.1f\t|%.1f\t|%.1f\t|%s\t|%s\t|%d\t|\n", stu[i].course[j].total_score, stu[i].course[j].credit, stu[i].course[j].corecredit, stu[i].course[j].teacher,Coursetype[stu[i].course[j].type],  stu[i].course[j].term);
			}
		}
	}
	printf("--------------------------------------------------------------------------------------\n");
	printf("�ܷ֣�%1.f ��ѧ�֣�%1.f �ܼ��㣺%1.f ƽ���֣�%1.f ƽ��ѧ�֣�%1.f ƽ�����㣺%1.f \n",t,t_c,t_s,t/m,t_c/m,t_s/m );
}
//��������ѧ����Ϣ
void SwapStudentMessage(STU& stui, STU& stuj)
{
	STU temp=stui;
	stui = stuj;
	stuj = temp;
}
//�ҿγ̳ɼ�
float  findscore(STU stui, char n[20])
{
	int i;
	for ( i = 0; i < m; i++)
	{
		if (strcmp(stui.course[i].courseName, n) == 0)
			return stui.course[i].total_score;
	}
	if (i == m)return 999;
}
//��ѧ��
int   findId(STU stu[], char name[20])
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(stu[i].studentID, name) == 0)
			return i;
	}
	return -1;
}

void test(STU stu[])
{
	n = 2, m = 1;
	stu[0].studentID[0] = '1';			//ѧ��
	stu[0].studentName[0] = '1';		//����
	stu[0].major[0] = '1';				//רҵ
	stu[0].className[0] = '1';			//�༶��
	stu[0].gender[0] = '1';
	stu[0].course[0].term = 1;
	stu[0].course[0].courseID[0] = '1';
	stu[0].course[0].courseName[0] = '1';
	stu[0].course[0].teacher[0] = '1';
	stu[0].course[0].credit = 1;
	stu[0].course[0].usual_score = 59;
	stu[0].course[0].midterm_score = 1;
	stu[0].course[0].fina_score = 59;
	stu[0].course[0].exp_score = 1;
	stu[0].course[0].total_score = 59;
	stu[0].course[0].type = 1;

	stu[1].studentID[0] = '2';			//ѧ��
	stu[1].studentName[0] = '2';		//����
	stu[1].major[0] = '2';				//רҵ
	stu[1].className[0] = '2';			//�༶��
	stu[1].gender[0] = '2';
	stu[1].course[0].term = 2;
	stu[1].course[0].courseID[0] = '1';
	stu[1].course[0].courseName[0] = '2';
	stu[1].course[0].teacher[0] = '1';
	stu[1].course[0].credit = 2;
	stu[1].course[0].usual_score = 90;
	stu[1].course[0].midterm_score = 2;
	stu[1].course[0].fina_score = 90;
	stu[1].course[0].exp_score = 2;
	stu[1].course[0].total_score = 90;
	stu[1].course[0].type = 2;


	stu[0].studentID[1] = '\0';			//ѧ��
	stu[0].studentName[1] = '\0';		//����
	stu[0].major[1] = '\0';				//רҵ
	stu[0].className[1] = '\0';			//�༶��
	stu[0].gender[1] = '\0';
	stu[0].course[0].courseID[1] = '\0';
	stu[0].course[0].courseName[1] = '\0';
	stu[0].course[0].teacher[1] = '\0';

	stu[1].studentID[1] = '\0';			//ѧ��
	stu[1].studentName[1] = '\0';		//����
	stu[1].major[1] = '\0';				//רҵ
	stu[1].className[1] = '\0';			//�༶��
	stu[1].gender[1] = '\0';
	stu[1].course[0].courseID[1] = '\0';
	stu[1].course[0].courseName[1] = '\0';
	stu[1].course[0].teacher[1] = '\0';
	CalculateScore(stu[0], 0);
	CalculateScore(stu[1], 1);
}
