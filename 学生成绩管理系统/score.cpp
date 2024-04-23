#define  _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <windows.h>
#define   MAX_LEN 40                        //最长字符
#define   STU_NUM 300                       // 最多的学生人数
#define   COURSE_NUM 12                     // 最多的考试科目数
#define   STU_MES	"a"
#define   COU_MES   "专业-------班级名-------学号-------姓名-------课程号-------课程名-------总分-----学分----绩点----任课老师-------课程性质"
int   n = 0, m = 0;					//学生人数\课程数

struct courseInf {
	char courseID[10];		//课程号
	char courseName[20];	//课程名
	float  credit;			//学分			
	float corecredit;		//绩点			4/90-100  3.7/85-90  3.3/82-85  3.0/78-82  2.7/75-78  2.3/72-75  2.0/68-72  1.5/64-68  1.0/60-64  0/0-60
	float usual_score;		//平时成绩
	float midterm_score;	//期中成绩
	float fina_score;		//期末成绩
	float make_up_score=-1;	//补考成绩
	float exp_score;		//实验成绩
	float total_score;		//课程总评成绩		//期末成绩*0.6+平时成绩*0.4  补考为1.0
	int term;				//开课学期
	char teacher[20]="空";	//任课老师
	int type;				//课程性质
};

//学生信息设计 N门课程

typedef struct student {
	char studentID[20];				//学号
	char studentName[20];			//姓名
	char major[12];					//专业
	char className[12];				//班级名
	char gender[10];				//性别
	char nation[20] = "空";			//民族
	char native[20] = "空";			//籍贯
	struct courseInf course[COURSE_NUM];	//结构体数组存放若干课程详细信息
	float totalscore=0;				//总成绩
	float totalCredit = 0;			//总学分
	float totalCoreCredit = 0;		//总绩点
	float totalDegreeScore = 0;		//学位课总分
	float totalRequiredScore = 0;	//必修课总分
	float totalDegreeCredit = 0;	//学位课学分
	float totalRequiredCredit = 0;	//必修课学分
	float totalDegreeCoreCredit = 0;//学位课绩点
	float totalRequiredCoreCredit = 0;//必修课绩点
	float avgscore = 0;				//平均成绩
	float avgCredit = 0;			//平均学分
	float avgCoreCredit = 0;		//平均绩点
	float avgDegreeScore = 0;		//学位课平均分
	float avgRequiredScore = 0;		//必修课平均分
	float avgDegreeCredit = 0;		//学位课平均学分
	float avgRequiredCredit = 0;	//必修课平均学分
	float avgDegreeCoreCredit = 0;	//学位课平均绩点
	float avgRequiredCoreCredit = 0;//必修课平均绩点
	float avgOfCoreCredit = 0;		//学分平均绩点   (绩点*学分)总和/学分总和
	float GaokaoScore=-1;			//高考成绩
	char  brief_introduct[1000] = "空";//简介
	int age=-1;						//年龄
}STU;

char make_up[STU_NUM][20];			//补考名单
int make_up_idx=0;					

char Coursetype[6][30] = {" ", "学位课","专业必修课","专业选修课","公共必修课","公共选修课" };

//主功能函数
int   Menu(void);												//菜单
void  ReadScore(STU stu[]);										//录入成绩
void  DeleteStudent(STU stu[]);									//删除学生信息
void  FixedStudentMessage(STU stu[]);							//修改学生信息
void  FixedStudentCourse(STU stu[]);							//修改学生成绩
void  SearchbyNum(STU stu[]);									//学号查找
void  SearchbyName(STU stu[]);									//姓名查找
void  SearchbyClass(STU stu[]);									//班级查找
void  SortbyID(STU stu[], int l, int r);						//学号排序
void  SortbyScoreUp(STU stu[], int l, int r);					//总分升序排序
void  SortbyScoreDown(STU stu[], int l, int r);					//总分降序排序
void  SortbyCourseScore(STU stu[], int l, int r,char couse[20]);//按课程排序
void  SortbyavgCoreCredit(STU stu[], int l, int r);				//按学分平均绩点排序
void  SortbyDegreeScore(STU stu[], int l, int r);				//按学位课总分排列
void  SortbyRequiredScore(STU stu[], int l, int r);				//按必修课总分排列
void  SortbyDegreeCoreCredit(STU stu[], int l, int r);			//按学位课平均绩点排列
void  SortbyRequiredCoreCredit(STU stu[], int l, int r);		//按必修课平均绩点排列
void  SortbyClassAvgCoreCredit(STU stu[], int l, int r);		//按班级学分平均绩点排列
void  SortbyName(STU stu[], int l, int r);						//按姓名字典序列排序
void  StaticScore(STU stu[]);									//统计及格率、优秀率
void  StaticMakeUpList(STU stu[]);								//统计补考名单
void  RecodeMake_Up_Score(STU stu[]);							//录入补考成绩

//辅助功能函数
int   inputInt(int low, int high, const char description[30]);   //限制整数非法输入
void  PrintStudentMessage(STU stui);							//简单输出一个学生信息
void  PrintStudentAllMessage(STU stui);							//输出一个人所有信息
void  PrintScore(STU stu[], char coursename[20]);				//输出所有人单科成绩
void  PrintStudentbasicMessage(STU stu[]);						//输出所有人的基本信息
void  CalculateScore(STU &stui,int i);							//计算成绩、学分、绩点、平均学分绩点
void  SwapStudentMessage(STU &stui, STU &stuj);					//交换两个学生信息
float findscore(STU stui, char n[20]);						//找课程成绩
int   findId(STU stu[], char name[20]);							//找学号
void  test(STU stu[]);

int   main(void)
{
	STU stu[STU_NUM];
	int choice;
	test(stu);
	while (1)
	{
		choice = Menu();						// 显示菜单，并读取用户输入 
		switch (choice)	
		{
		case 1:
			ReadScore(stu);						//录入学生基本信息和成绩
			break;
		case 2:
			DeleteStudent(stu);					//删除学生基本信息
			break;
		case 3:
			FixedStudentMessage(stu);			//修改学生信息
			break;
		case 4:
			FixedStudentCourse(stu);			//修改学生课程
			break;
		case 5:
			SearchbyNum(stu);					//按学号查找学生
			break;
		case 6:
			SearchbyName(stu);					//按姓名查找学生
			break;
		case 7:
			SearchbyClass(stu);					//按班级查找学生
			break;
		case 8:
			SortbyID(stu, 0, n-1);				//按学号排序
			PrintStudentbasicMessage(stu);
			break;
		case 9:
			SortbyScoreUp(stu, 0, n - 1);			//按总分升序排序
			PrintStudentbasicMessage(stu);
			break;
		case 10:
			SortbyScoreDown(stu, 0, n - 1);			//按总分降序排序
			PrintStudentbasicMessage(stu);
			break;
		case 11:
			char mes[20];
			strcpy(Coursetype[0], mes);
			SortbyCourseScore(stu, 0, n - 1 ,mes);	//按课程排序
			PrintStudentbasicMessage(stu);
			break;
		case 12:
			SortbyavgCoreCredit(stu, 0, n - 1);		//按平均学分绩点排序
			PrintStudentbasicMessage(stu);
			break;
		case 13:
			SortbyDegreeScore(stu, 0, n - 1);		//按学位课总分排列
			PrintStudentbasicMessage(stu);
			break;
		case 14:
			SortbyRequiredScore(stu, 0, n - 1);		//按必修课总分排列
			PrintStudentbasicMessage(stu);
			break;
		case 15:
			SortbyDegreeCoreCredit(stu, 0, n - 1);	//按学位课平均绩点排列
			PrintStudentbasicMessage(stu);
			break;
		case 16:
			SortbyRequiredCoreCredit(stu, 0, n - 1);//按必修课平均绩点排列
			PrintStudentbasicMessage(stu);
			break;
		case 17:
			SortbyClassAvgCoreCredit(stu, 0, n - 1);//按班级平均学分绩点排列
			break;
		case 18:
			SortbyName(stu, 0, n - 1);				//按姓名字典序列排序
			PrintStudentbasicMessage(stu);
			break;
		case 19:
			StaticScore(stu);						//统计及格率，优秀率
			break;
		case 20:
			StaticMakeUpList(stu);					//统计补考名单
			break;
		case 21:
			RecodeMake_Up_Score(stu);				//录入补考成绩
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			break;
		case 0:
			printf("程序结束!");
			exit(0);
		default:
			printf("错误输入!");
		}
		system("pause");
		system("cls");
	}
	return 0;
}
//  函数功能：显示菜单并获得用户键盘输入的选项
int   Menu(void)
{
	int itemSelected;
	printf("  ----------------------------------------------------------------------------------------------------------------------\n");
	printf("  |						学生成绩管理系统（%3d/%3d）																			|\n", n, STU_NUM);
	printf("  |--------------------------------------------------------------------------------------------------------------------|\n");
	printf("  |																												|\n");
	printf("  |		1.录入学生基本信息和成绩					15.按学位课平均绩点排列									|\n");
	printf("  |		2.删除学生基本信息						16.按必修课平均绩点排列				|\n");
	printf("  |		3.修改学生基本信息						17.按班级平均学分绩点排列				|\n");
	printf("  |		4.修改学生课程信息						18.按姓名字典序列排序				|\n");
	printf("  |		5.查找学生--姓名						19.统计及格率、优秀率				|\n");
	printf("  |		6.查找学生--学号						20.统计补考名单				|\n");
	printf("  |		7.查找学生--班级						21.录入补考成绩				|\n");
	printf("  |		8.按学号排列							22.计算每门课程的平均分、最高分和最低分					|\n");
	printf("  |		9.按总分升序排列						23.录入学生其他个人信息				|\n");
	printf("  |		10.按总分降序排列						24.输出学生完整个人信息				|\n");
	printf("  |		11.按每门课程成绩排列						25.取本地文件						|\n");
	printf("  |		12.按学分平均绩点排列						26.写入本地文件									|\n");
	printf("  |		13.按学位课总分排列 																|\n");
	printf("  |		14.按必修课总分排列 																|\n");
	printf("  |										0.退出													|\n");
	printf("  |																														|\n");
	printf("  ----------------------------------------------------------------------------------------------------------------------\n");
	printf("请输入你的选择:");
	itemSelected = inputInt(0, 25, "选择序号"); 	// 读入用户输入，合法输入
	if ((m == 0 || n==0)&& itemSelected!=24)
	{
		printf("--除当列表为空或读入本地文件外，输入后不可修改!--\n");
		printf("输入学生课程数(课程数<=%d):", COURSE_NUM);
		m = inputInt(1, COURSE_NUM, "课程数");
	}
	if (n == 0&& itemSelected!=1 && itemSelected != 25 && itemSelected != 24 && itemSelected != 0)
	{
		printf("----------成绩表为空，先录入学生-------\n");
		return -1;
	}
	return itemSelected;
}
// 函数功能：输入n个学生的m门课成绩
void  ReadScore(STU stu[])
{
	int i, j,num ;
	printf("录入人数(0<人数<%d)：",STU_NUM);
	num = inputInt(0, STU_NUM-n, "人数");
	for (int i = 0; i < num; n++,i++)
	{
		printf("输入第%d个学生的学号：",i+1);
		scanf("%s",stu[i].studentID);
		printf("输入第%d个学生的姓名：", i + 1);
		scanf("%s", stu[i].studentName);
		printf("输入学生'%s'的专业：", stu[i].studentName);
		scanf("%s", stu[i].major);
		printf("输入学生'%s'的班级：", stu[i].studentName);
		scanf("%s", stu[i].className);
		printf("输入学生'%s'的性别：", stu[i].studentName);
		scanf("%s", stu[i].gender);
		for (int j = 0; j < m; j++)
		{
			printf("输入第%d门课程的开课学期：", j + 1);
			scanf("%d", &stu[i].course[j].term);
			printf("输入第%d门课程的课程号:",j+1);
			scanf("%s", stu[i].course[j].courseID);
			printf("输入第%d门课程的课程名：", j + 1);
			scanf("%s",stu[i].course[j].courseName);
			printf("输入课程%s的任课老师：", stu[i].course[j].courseName);
			scanf("%s", stu[i].course[j].teacher);
			printf("输入课程%s的学分：", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].credit);
			printf("输入课程%s的平时分：", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].usual_score);
			printf("输入课程%s的期中成绩：", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].midterm_score);
			printf("输入课程%s的期末成绩：", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].fina_score);
			printf("输入课程%s的实验成绩：", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].exp_score);
			printf("输入课程%s的课程总评成绩：", stu[i].course[j].courseName);
			scanf("%f", &stu[i].course[j].total_score);
			printf("课程性质--（1学位课，2专业必修课，3专业选修课，4公共必修课，5公共选修课)\n");
			printf("输入课程%s的课程性质 0<num<6:", stu[i].course[j].courseName);
			stu[i].course[j].type = inputInt(1, 5, "课程性质");
		}
		CalculateScore(stu[i],i);
		printf("-------------录入成功（%3d/%3d）--------\n", n+1, STU_NUM);
		if (n + 1 >= STU_NUM) { 
		printf("-------------人数已满-------------------\n"); break; }
	}
	
}
//函数功能：删除学生信息
void  DeleteStudent(STU stu[])
{
	int num;
	char ch;
	printf("输入删除学生的人数：");
	num = inputInt(0, n, "删除人数");
	while (num--)
	{
		int same[STU_NUM], idx = 0;
		char mes[20];
		printf("输入学生的学号或姓名删除学生");
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
			printf("查询到%d个相同'%s'信息学生，选择上面排列第（？）个学生：", idx, mes);
			choice = same[inputInt(1, idx, "序号")-1];
		}
		else if (idx == 0)
		{
			printf("-------查找失败，请输入正确信息!--------\n");
			continue;
		}
		printf("输入Y确认删除（任意键取消）：");
		ch = getchar();
		if (ch == 'Y' || ch == 'y')
		{
			for (int j = choice; j < n - 1; j++) {
				stu[j] = stu[j + 1];
			}
			n--;
		}
			printf("----------------删除成功!--------------\n");

	}
}
//函数功能：修改学生信息
void  FixedStudentMessage(STU stu[])
{
	int num;
	printf("输入修改学生的人数：");
	num = inputInt(0, n, "修改人数");
	while (num--)
	{
		int same[STU_NUM], idx = 0;
		char mes[20];
		printf("输入学生的学号或姓名：");
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
			printf("查询到%d个相同'%s'信息学生，选择上面排列第（？）个学生：", idx, mes);
			choice = same[inputInt(1, idx, "序号")-1];
		}
		else if (idx == 0)
		{
			printf("-------查找失败，请输入正确信息!--------\n");
			continue;
		}
		printf("原信息：\n");
		int i = choice;
		printf("学号：%s 姓名：%s 专业：%s 班级：%s 性别：%s\n",stu[i].studentID , stu[i].studentName, stu[i].major, stu[i].className, stu[i].gender);
		printf("修改学生的学号：");
		scanf("%s", stu[i].studentID);
		printf("修改学生的姓名：");
		scanf("%s", stu[i].studentName);
		printf("修改学生%s的专业：", stu[i].studentName);
		scanf("%s", stu[i].major);
		printf("修改学生%s的班级：", stu[i].studentName);
		scanf("%s", stu[i].className);
		printf("修改学生%s的性别：", stu[i].studentName);
		scanf("%s", stu[i].gender);
		printf("修改后信息：\n");
		printf("学号：%s 姓名：%s 专业：%s 班级：%s 性别：%s\n", stu[i].studentID, stu[i].studentName, stu[i].major, stu[i].className,stu[i].gender);
			printf("--------------------修改成功!-------------\n");
	}
}
//函数功能，修改学生课程信息
void  FixedStudentCourse(STU stu[])
{

	int num;
	printf("输入修改学生的人数：");
	num = inputInt(0, n, "修改人数");
	while (num--)
	{
		int same[STU_NUM], idx = 0;
		char mes[20];
		printf("输入学生的学号或姓名：");
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
			printf("查询到%d个相同'%s'信息学生，选择上面排列第（？）个学生：", idx, mes);
			choice = same[inputInt(1, idx, "序号") - 1];
		}
		else if (idx == 0)
		{
			printf("----------查找失败，请输入正确信息!----------\n");
			continue;
		}
		printf("输入修改的课程号或课程名：");
		scanf("%s", mes);
		for (int j = 0,i=choice; j < m; j++)
		{
			if (strcmp(mes, stu[i].course[j].courseID) == 0 || strcmp(mes, stu[i].course[j].courseName) == 0)
			{
				printf("修改课程的开课学期：");
				scanf("%d", &stu[i].course[j].term);
				printf("修改课程的课程号:");
				scanf("%s", stu[i].course[j].courseID);
				printf("修改课程的课程名：");
				scanf("%s", stu[i].course[j].courseName);
				printf("修改课程%s的任课老师：", stu[i].course[j].courseName);
				scanf("%s", stu[i].course[j].teacher);
				printf("修改课程%s的学分：", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].credit);
				printf("修改课程%s的平时分：", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].usual_score);
				printf("修改课程%s的期中成绩：", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].midterm_score);
				printf("修改课程%s的期末成绩：", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].fina_score);
				printf("修改课程%s的实验成绩：", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].exp_score);
				printf("修改课程%s的课程总评成绩：", stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].total_score);
				printf("课程性质--（1学位课，2专业必修课，3专业选修课，4公共必修课，5公共选修课)\n");
				printf("修改课程%s的课程性质 0<num<6:", stu[i].course[j].courseName);
				stu[i].course[j].type = inputInt(1, 5, "课程性质");
				printf("----------------修改成功！-------------------\n");
				break;
			}
		}
	}
}
//函数功能：按学号查找学生信息
void  SearchbyNum(STU stu[])
{
	int num,i;
	printf("输入查找学生的次数：");
	num = inputInt(0, n, "修改人数");
	while (num--)
	{
		char mes[20];
		printf("输入学生的学号：");
		scanf("%s", mes);
		for (i = 0; i < n; i++)
		{
			if (strcmp(mes, stu[i].studentID) == 0 )
			{
				PrintStudentAllMessage(stu[i]);
				break;
			}
		}
		if (i == n)printf("-------------查找失败，请输入正确信息!--------\n");
	}
}
//函数功能：按姓名查找学生信息
void  SearchbyName(STU stu[])
{
	int num,i;
	printf("输入查找学生的次数：");
	num = inputInt(0, n, "修改人数");
	while (num--)
	{
		char mes[20];
		printf("输入学生的学号：");
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
		if (i == n)printf("--------查找失败，请输入正确信息!------\n");
	}
}
//函数功能：按班级查找学生信息
void  SearchbyClass(STU stu[])
{
	char mes[20];
	int clas[STU_NUM],idx=0;
	printf("输入班级名：");
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
	if(idx==0)printf("----------查找失败，请输入正确信息------\n");
}
//函数功能：按学号排序
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
//函数功能：按总分升序排序
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
//函数功能：按总分降序排序
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
//函数功能：按每门课程成绩排列
void  SortbyCourseScore(STU stu[],int l,int r,char coursename[20])
{
	while (l == 0 &&r==n-1&& strcmp(coursename, Coursetype[0]) == 0)
	{
		printf("输入课程号进行排序：");
		scanf("%s", coursename);
		if (strcmp(coursename, Coursetype[0]) == 0)printf("不能输入空白课程号!\n");
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
//函数功能：按平均学分绩点排列
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
//函数功能：按学位课总分排列
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
//函数功能：按必修课总分排列
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
//函数功能：按学位课平均绩点排列
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
//函数功能：按必修课平均绩点排列
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
//函数功能：按姓名字典序列排序
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
//函数功能：统计及格率、优秀率
void  StaticScore(STU stu[])
{
	char CourseName[600][20];
	int idx = 0;
	printf("课程号---课程名---课程性质---任课老师---优秀率（大于80）-良好率（大于60）-及格率（大于60）\n");
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
	printf("-----------------统计完成！-------------\n");
}
//函数功能：统计补考名单
void  StaticMakeUpList(STU stu[])
{
	if (make_up_idx == 0)printf("  ---------------------无补考人员-----------------\n");
		printf("专业-------班级-------学号-------姓名-----性别---总学分--平均学分绩点---课程名+成绩...\n");
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
//函数功能：录入补考成绩
void RecodeMake_Up_Score(STU stu[])
{
	if (make_up_idx == 0)printf("  ---------------------无补考人员-----------------\n");
	for (int k = make_up_idx-1; k >= 0; k--,make_up_idx--)
	{
		int i = findId(stu,make_up[k]);
		if (i == -1)continue;
		for (int j = 0; j < m; j++)
		{
			if (stu[i].course[j].total_score < 60)
			{
				printf("输入学生%s的课程%s补考成绩：", stu[i].studentName,stu[i].course[j].courseName);
				scanf("%f", &stu[i].course[j].make_up_score);
			}
		}
		CalculateScore(stu[i],i);
	}
}
//函数功能：按班级学分平均绩点排列

/*辅助功能函数*/

//限制输入
int inputInt(int low, int high, const char description[30])
{
	int temp;
	char c;
	scanf_s("%d", &temp);
	while (temp<low || temp>high)
	{
		printf("输入%s必须大于等于%d且小于等于%d\n请重新输入：", description, low, high);
		while ((c = getchar()) != '\n');
		scanf_s("%d", &temp);
	}
	return temp;
}
//计算个人各课绩点
void  CalculateScore(STU &stui,int i)
{
	float t=0, t_1=0, t_2=0 ,t_c_s=0;			//总分	学位-  必修-  学分绩点
	float c = 0, c_1 = 0, c_2 = 0;	//绩点
	float s = 0, s_1 = 0, s_2 = 0;	//学分
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
	stui.totalCoreCredit = c;	//绩点
	stui.totalCredit = s;		//学分
	stui.avgscore = m > 0 ? t / m : -1;
	stui.avgCoreCredit = m > 0 ? c / m : -1;
	stui.avgCredit = m > 0 ? s / m : -1;
	stui.totalDegreeScore = t_1;  //学位课
	stui.totalDegreeCoreCredit = c_1;
	stui.totalDegreeCredit = s_1;
	stui.avgDegreeScore = m > 0 ? t_1 / m : -1;
	stui.avgDegreeCoreCredit = m > 0 ? c_1 / m : -1;
	stui.avgDegreeCredit = m > 0 ? s_1 / m : -1;
	stui.totalRequiredScore = t_2;  //必修课
	stui.totalRequiredCoreCredit = c_2;
	stui.totalRequiredCredit = s_2;
	stui.avgRequiredScore = m > 0 ? t_2 / m : -1;
	stui.avgRequiredCoreCredit = m > 0 ? c_2 / m : -1;
	stui.avgRequiredCredit = m > 0 ? s_2 / m : -1;
	//平均学分绩点
	stui.avgOfCoreCredit = s>0?t_c_s / s:0;
	printf("---------%s的绩点，平均绩点，平均学分绩点...已更新！---------\n",stui.studentName);
}
//输出一个学生信息
void PrintStudentMessage(STU stui)
{
	printf("专业-------班级-------学号-------姓名-----性别---总学分--学分平均绩点---课程名...\n");
	printf("|%s\t|%s\t|%s\t|%s\t|%s\t|%.1f\t|%.1f\t", stui.major, stui.className, stui.studentID, stui.studentName, stui.gender,stui.totalCredit,stui.avgOfCoreCredit);
	for (int j = 0; j < m; j++)
	{
		printf("|%s\t", stui.course[j].courseName);
	}printf("|\n");
}
//输出一个学生完整信息
void PrintStudentAllMessage(STU stui)
{
	printf("专业-------班级-------学号-------姓名-------性别----年龄----民族-----籍贯-----高考总分----简介\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("|%s\t|%s\t|%s\t|%s\t|%s\t|%d\t|%s\t|%s\t|%1.f|%s\t|\n", stui.major, stui.className, stui.studentID, stui.studentName, stui.gender,stui.age,stui.nation,stui.native,stui.GaokaoScore,stui.brief_introduct);
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("课程号----课程名--------任课老师-----课程性质------开课学期\n");
	printf("平时分---期中成绩---期末成绩---实验成绩---补考成绩---课程总评成绩----学分----绩点\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < m; i++)
	{
		printf("|%s\t|%s\t|%s\t|%s\t|%d\t|\n", stui.course[i].courseID, stui.course[i].courseName, stui.course[i].teacher, Coursetype[stui.course[i].type], stui.course[i].term);
		printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.course[i].usual_score, stui.course[i].midterm_score, stui.course[i].fina_score, stui.course[i].exp_score, stui.course[i].make_up_score,stui.course[i].total_score, stui.course[i].credit, stui.course[i].corecredit);
		if(i<m-1)printf("-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  \n");
	}
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("各科总分----总学分----总绩点---平均分---平均学分---平均绩点---学分平均绩点\n");
	printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.totalscore, stui.totalCredit, stui.totalCoreCredit,stui.avgscore,stui.avgCredit,stui.avgCoreCredit, stui.avgOfCoreCredit);
	printf("学位课总分--学位课学分--学位课绩点--学位课平均分--学位课平均学分--学位课平均绩点\n");
	printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.totalDegreeScore, stui.totalDegreeCredit, stui.totalDegreeCoreCredit, stui.avgDegreeScore, stui.avgDegreeCredit, stui.avgDegreeCoreCredit);
	printf("必修课总分--必修课学分--必修课绩点--必修课平均分--必修课平均学分--必修课平均绩点\n");
	printf("|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|%.1f\t|\n", stui.totalRequiredScore, stui.totalRequiredCredit, stui.totalRequiredCoreCredit, stui.avgRequiredScore, stui.avgRequiredCredit, stui.avgRequiredCoreCredit);

}
//输出所有学生基本信息
void PrintStudentbasicMessage(STU stu[])
{
	printf("专业------班级-----学号-----姓名----性别---总学分/学分平均绩点---学位课总分/平均绩点---必修课总分/平均绩点---课程名...\n");
	for (int i = 0; i < n; i++)
	{
		printf("|%s\t|%s\t|%s\t|%s\t|%s\t|%.1f//%.1f\t|%.1f//%.1f\t|%.1f//%.1f\t", stu[i].major, stu[i].className, stu[i].studentID, stu[i].studentName, stu[i].gender, stu[i].totalCredit, stu[i].avgOfCoreCredit,stu[i].totalDegreeScore,stu[i].avgDegreeCoreCredit, stu[i].totalRequiredScore,stu[i].avgRequiredCoreCredit);
		for (int j = 0; j < m; j++)
		{
			printf("|%s\t", stu[i].course[j].courseName);
		}printf("|\n");
	}
	
}
//输出所有学生单科成绩
void PrintScore(STU stu[],char coursename[20])
{
	float t = 0, t_c = 0, t_s = 0,num=0;
	printf("专业-------班级-------学号-----姓名----课程名---总分/学分/绩点/学分平均绩点--任课老师--课程性质--开课学期\n");
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
	printf("总分：%1.f 总学分：%1.f 总绩点：%1.f 平均分：%1.f 平均学分：%1.f 平均绩点：%1.f \n",t,t_c,t_s,t/m,t_c/m,t_s/m );
}
//交换两个学生信息
void SwapStudentMessage(STU& stui, STU& stuj)
{
	STU temp=stui;
	stui = stuj;
	stuj = temp;
}
//找课程成绩
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
//找学号
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
	stu[0].studentID[0] = '1';			//学号
	stu[0].studentName[0] = '1';		//姓名
	stu[0].major[0] = '1';				//专业
	stu[0].className[0] = '1';			//班级名
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

	stu[1].studentID[0] = '2';			//学号
	stu[1].studentName[0] = '2';		//姓名
	stu[1].major[0] = '2';				//专业
	stu[1].className[0] = '2';			//班级名
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


	stu[0].studentID[1] = '\0';			//学号
	stu[0].studentName[1] = '\0';		//姓名
	stu[0].major[1] = '\0';				//专业
	stu[0].className[1] = '\0';			//班级名
	stu[0].gender[1] = '\0';
	stu[0].course[0].courseID[1] = '\0';
	stu[0].course[0].courseName[1] = '\0';
	stu[0].course[0].teacher[1] = '\0';

	stu[1].studentID[1] = '\0';			//学号
	stu[1].studentName[1] = '\0';		//姓名
	stu[1].major[1] = '\0';				//专业
	stu[1].className[1] = '\0';			//班级名
	stu[1].gender[1] = '\0';
	stu[1].course[0].courseID[1] = '\0';
	stu[1].course[0].courseName[1] = '\0';
	stu[1].course[0].teacher[1] = '\0';
	CalculateScore(stu[0], 0);
	CalculateScore(stu[1], 1);
}
