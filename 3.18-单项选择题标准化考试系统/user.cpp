//user.cpp created time 2016-1-9 17:57:32

#include "all.h"

void user() {

	system("mode con cols=34 lines=22");
	system("color 3A");

	int i;
	struct user * head = NULL;
	head=read_user();
	struct user * temp = NULL;

	char get_1[10],get_2[10];
	for(i=0;i<3;i++) {
		system("cls");
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
		printf("           学生登录界面\n\n");
		printf("     -------------------------\n");
		printf("     | 学号: |               |\n");
		printf("     -------------------------\n");
		printf("\n");
		printf("     -------------------------\n");
		printf("     | 密码: |               |\n");
		printf("     -------------------------\n");
		printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fflush(stdin);
		goto_pos(16,7);
		scanf("%20s",get_1);
		fflush(stdin);
		goto_pos(16,11);
		scanf("%20s",get_2);

		temp=head;
		while(temp!=NULL){
			if(strcmp(temp->no,get_1)==0&&strcmp(temp->password,get_2)==0){
				goto_pos(11,17);
				printf("登录成功!");
				Sleep(800);
				user_login(head,temp);
				//->登录成功后进入user_login函数
				return ;
			}else
				temp=temp->next;
		}
		goto_pos(11,17);
		printf("密码错误\n    请重新输入 (剩余次数:%d)",2-i);
		Sleep(1300);
	}
	exit(-1);
}

void user_login(struct user * head,struct user * node) {
		
	int a;
	system("color 07");
	while (1) {

		system("mode con cols=70 lines=30");
		a = move_1(5,menuPrint_7);

		switch (a) {
			case 1:exam(node);continue;
			case 2:execrise(node);continue;
			case 3:
				system("cls");
				print_user_solo(node);
				system("pause");
				continue;
			case 4:
				system("cls");
				print_user_solo(node);
				change_user(node);
				system("pause");
				continue;
			case 0:
			default:break;
		}
		break;
	}
	write_user(head);
	free_user(head);  //save
}

/*

 *******************************************************

               单项选择题标准化考试系统      
 
       欢迎您,
                                             -------------------
             -------------------          | 1 开始考试  |
             | 2 开始练习  |          -------------------
             -------------------
                              --------------------
                              | 3  查看信息  |
                              --------------------
                --------------------
                | 4  修改密码  |
                --------------------          --------------------
                                                  | 0  退出登录  |
                                                  --------------------
  2016-1-9 coded by Reigning...
*/

void menuPrint_7(int a) {

	system("cls");
	
	char name[15]={"menu_7.txt"};

	
	char arr[1500];//这里1000最为合适~2333
	memset(arr,0,sizeof(char)*1500);
	FILE *fp;
	fp=fopen(name,"r");

	if(fp==NULL) {
		printf("cannot open %s\n",name);
		exit (0);
	}

	int h=0;
	while(!feof(fp)) {
		fread(arr+h,sizeof(char),1,fp);
		h++;
	}
	printf("%s",arr);

	fclose(fp);

	switch (a) {
		//显示光标
		case 1:printRectangle(42,6);break;
		case 2:printRectangle(13,7);break;
		case 3:printRectangle(30,10);break;
		case 4:printRectangle(16,13);break;
		case 0:printRectangle(50,15);break;
		default:break;
	}
	
}

void printRectangle(int x, int y) {

	color(14);
	goto_pos(x,y);
	printf("---------------");
	goto_pos(x,y+1);
	printf("|");
	goto_pos(x+14,y+1);
	printf("|");
	goto_pos(x,y+2);
	printf("---------------");
	goto_pos(x+2,y+1);
	color(7);

}

/*颜色对应值： 
　　0=黑色                8=灰色　　
  　 1=蓝色                9=淡蓝色                　　                        
　　2=绿色                10=淡绿色       0xa        　　
　　3=湖蓝色          11=淡浅绿色        0xb　
　　4=红色                12=淡红色        0xc　　
　　5=紫色                13=淡紫色        0xd        　　
　　6=黄色                14=淡黄色        0xe        　　
　　7=白色                15=亮白色        0xf 
　　也可以吧这些值设置成常量。
*/
void color(const unsigned short color1)
{        
	/*仅限改变0-15的颜色;如果在0-15那么实现他的颜色   因为如果超过15后面的改变的是文本背景色。*/
    if(color1>=0&&color1<=15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
    /*如果不在0-15的范围颜色，那么改为默认的颜色白色；*/
    else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void exam(struct user * node) {

	int i=0,lever=100;
	float num,right=0,score=0;
	time_t begin,temp,end;
	char ch[20];
	int key;
	system("mode con cols=80 lines=300");

	printf("---------考试---------\n");
	printf("请输入题目数量: ");
	fflush(stdin);
	scanf("%f",&num);
	printf("请输入考试内容(如基础,拔高,数组,指针.无要求请直接按@+回车): ");
	fflush(stdin);
	scanf("%20s",ch);

	struct info * head = read_info();
	struct info * p = head->next;

	printf("考生须知:在作答过程中,按 0 放弃作答当前题目,按Esc则放弃剩余所有题目并交卷!\n");
	printf("按任意键考试开始!\n");
	begin=time(NULL);
	key=getch();
	if(key==0||key==224||key==-32)
		key=getch();
	//开始
	while(i<num&&p!=NULL)
	{
		if(isQusetion(p,ch))
		{
			temp=time(NULL);
			printf("\n---------当前分数:%g 分---经过时间:%ld 秒------\n",score,temp-begin);
			printf("\n---第%d题:",i);
			printf("\n statement:\n\t%s\n\n",p->statement);
			printf(" A:%s\t",p->options[0]);
			printf(" B:%s\n",p->options[1]);
			printf(" C:%s\t",p->options[2]);
			printf(" D:%s\n",p->options[3]);
			printf("***请作答: ");
			fflush(stdin);
			key=getch();
			if(key==0||key==224||key==-32)
				key=getch();
			else if(key>=97&&key<=100)
				if((key-97)==p->rightAnswer){
					right++;
					printf("答案正确!\n");
				}else
					printf("答案错误!\n");
			else if(key==27)
				return ;//结算
			else
				printf("答案错误!\n");
			i++;
		}
		p=p->next;
	}//while
	if(i!=num)
		printf("当前题库数量有限,敬请谅解\n");
	else{
		end=time(NULL);
		printf("考试完成!\n");
		printf("你答对题目%g道,正确率为%g%%\n",right,right*100.0/num);
		printf("总计用时间 %ld minutes %ld seconds",(end-begin)/60,(end-begin)%60);
	}
	system("pause");
}

int isQusetion(struct info * node,char *p) {

	int i;
	if(strcmp(p,"基础")==0)
		if(node->lever>=5)
			return 0;
	else if(strcmp(p,"拔高")==0)
		if(node->lever<=5)
			return 0;
	else if(*p!='@')
	{
		for(i=0;i<4;i++)
			if(fuzzy_search(node->keyWords[i],p)==1)
				return 1;
		return 0;
	}
	else
		if(rand()%2==0)
			return 0;
	return 1;
}

void execrise(struct user * node) {

	int i=0,lever=100;
	float num,right=0,score=0;
	time_t begin,temp,end;
	char ch[20];
	int key;
	system("mode con cols=80 lines=300");

	printf("---------考试---------\n");
	printf("请输入题目数量: ");
	fflush(stdin);
	scanf("%f",&num);
	printf("请输入考试内容(如基础,拔高,数组,指针.无要求请直接按@+回车): ");
	fflush(stdin);
	scanf("%20s",ch);

	struct info * head = read_info();
	struct info * p = head->next;

	printf("考生须知:在作答过程中,按 0 放弃作答当前题目,按Esc则放弃剩余所有题目并交卷!\n");
	printf("按任意键考试开始!\n");
	begin=time(NULL);
	key=getch();
	if(key==0||key==224||key==-32)
		key=getch();
	//开始
	while(i<num&&p!=NULL)
	{
		if(isQusetion(p,ch))
		{
			temp=time(NULL);
			printf("\n---------当前分数:%g 分---经过时间:%ld 秒------\n",score,temp-begin);
			printf("\n---第%d题:",i);
			printf("\n statement:\n\t%s\n\n",p->statement);
			printf(" A:%s\t",p->options[0]);
			printf(" B:%s\n",p->options[1]);
			printf(" C:%s\t",p->options[2]);
			printf(" D:%s\n",p->options[3]);
			printf("***请作答: ");
			fflush(stdin);
			key=getch();
			if(key==0||key==224||key==-32)
				key=getch();
			else if(key>=97&&key<=100)
				if((key-97)==p->rightAnswer){
					right++;
					printf("答案正确!\n");
				}else
					printf("答案错误!\n");
			else if(key==27)
				return ;//结算
			else
				printf("答案错误!\n");
			i++;
		}
		p=p->next;
	}//while
	if(i!=num)
		printf("当前题库数量有限,敬请谅解\n");
	else{
		end=time(NULL);
		printf("考试完成!\n");
		printf("你答对题目%g道,正确率为%g%%\n",right,right*100.0/num);
		printf("总计用时间 %ld minutes %ld seconds",(end-begin)/60,(end-begin)%60);
	}
	system("pause");
}