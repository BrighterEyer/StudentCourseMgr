#define MAXSIZE 100
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>

#include "Course.h"
#include "CStack.h"

#include "mydefines.h"

CStack stack;//ջ�������ݽṹ
CStack tmpStack;
int num=0;//�γ���

//�γ�ָ������
void print_sheet_head();
void print_stack(CStack stack);

char ShowMenu();
void AddCourse(CStack &stack);
void LoadFromCmd();
void LoadFromFile(char loadfilepath[],char write2diskpath[]);
void QueryCourse();
//�����ӡ
void printByOrderDesc();

int main(int argc, char** argv) {
	//1��ϵͳ�Բ˵���ʽ����-����
	//2���γ���Ϣ¼�빦��-���
	//3���γ���Ϣ�������-���
	//4����Ϣ��ѯ����-�㷨
	//5��ѧ��ѡ�޿γ�(��ѡ��)
	stack.size=0;
	char opt;//stdio.h��ĺ���
	while((opt=ShowMenu())!='0') {
		switch(opt) {
			case '1'://¼��γ���Ϣ
				AddCourse(stack);
				continue;
			case '2'://����γ���Ϣ
				print_stack(stack);
				getchar();
				continue;
			case '3'://��ѯ�γ���Ϣ
				QueryCourse();
				continue;
			case '4':
				printf("ѧ��ѡ�޿γ�");
				continue;
		}
	}
	printf("�˳�");
	return 0;
}

char ShowMenu() {
	system("cls");
	printf("\t\t=======================================\n");
	printf("\t\t\t\t������ʽ\n");
	printf("\t\t\t\t(1)¼��γ���Ϣ\n");
	printf("\t\t\t\t(2)����γ���Ϣ\n");
	printf("\t\t\t\t(3)��ѯ�γ���Ϣ\n");
	printf("\t\t\t\t(0)�˳�\n");
	printf("\t\t=======================================\n");
	printf("\t\t������ѡ��:");
	char c=getchar();
	fflush(stdin);
	return c;
}

//��ӡ��ͷ
void print_sheet_head() {
//	printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��ѧʱ\t�ϻ�ѧʱ\tѧ��\t������Ϣ\n");
	printf("�γ̱��  �γ�����  �γ�����  ��ѧʱ  �ڿ�ѧʱ  ʵ��ѧʱ  �ϻ�ѧʱ  ѧ��  ������Ϣ\n");
}
//���һ���γ�
void AddCourse(CStack &stack) {
	char c;
	fflush(stdin);
	while(true) {
		system("cls");
		printf("\n\n\t\t=========  ����γ���Ϣ[��ѯ]  ==========\n");
		printf("\t\t(1)����̨¼��\n\t\t(2)�ļ�¼��\n\t\t(0)�������˵�\n\t\t(1/2/0):");
		if((c=getchar())=='0')
			break;
		switch(c) {
			case '1':
				LoadFromCmd();
				continue;
			case '2':
				LoadFromFile((char *)"input.txt",(char *)"output.txt");//������ǿ������ת���Ļ����ᱨ��
				break;
		}
	}
}
//�Կ���̨����ķ�ʽ��¼��γ���Ϣ
void LoadFromCmd() {
	printf("���ݱ�ͷ��������,��Ϊ�ո�ֿ�,����:\n");
	printf("002 ��ѧ ���޿� 120 60 30 30 6 ��ѧ���������\n");
	print_sheet_head() ;
	_DECLARE_COURSE_MEMERS_//�궨�壬��mydefines.h�ﶨ��,����course��Ա����
	scanf("%s %s %s %f %f %f %f %f %s",
	      &no,
	      &name,
	      &type,
	      &totalTime,
	      &givingCourseTime,
	      &practiceTime,
	      &operatingTime,
	      &score,
	      &info
	     );
	_PUSH_CSTACK_//�궨�壬��mydefines.h�ﶨ��,������ӵ�CStack����
	system("pause");
}

//���ļ���ȡ��ʽ��¼��γ���Ϣ
void LoadFromFile(char loadfilepath[],char write2diskpath[]) {
	FILE *fp;
	FILE *fout;
	fp = fopen(loadfilepath,"r");                  //���ļ�
	fout=fopen(write2diskpath,"a");
	if(fp == NULL) {
		printf("�򿪲���¼���ļ�!\n ");
		system("pause");
		exit(0);                                 //ͷ�ļ���Ҫ�� stdlib.h
	} else {
		while(!feof(fp)) {//fscanf()��ʽ���ַ�����β��û��\n,����ֶ��һ�����һ�е����
			_DECLARE_COURSE_MEMERS_//�궨��,��mydefines.h�ﶨ��,����course��Ա����
			fscanf(fp,"%s %s %s %f %f %f %f %f %s\n",&no,&name,&type,&totalTime,&givingCourseTime,&practiceTime,&operatingTime,&score,&info);
			fflush(stdin);
//			printf("%s %s %s %0.1f %0.1f %0.1f %0.1f %0.1f %s\n",no,name,type,totalTime,givingCourseTime,practiceTime,operatingTime,score,info);
//			printf(" %s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",no,name,type,totalTime,givingCourseTime,practiceTime,operatingTime,score,info);
			_PUSH_CSTACK_//�궨�壬��mydefines.h�ﶨ��,������ӵ�CStack����
			if(NULL==fout) {
				printf("ע���޷�д�뱾���ļ�������·��!\n");
				system("pause");
			} else {
				fprintf(fout,"%s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",
				        no,
				        name,
				        type,
				        totalTime,
				        givingCourseTime,
				        practiceTime,
				        operatingTime,
				        score,
				        info
				       );
			}
		}
	}
	print_stack(stack);
	system("pause");
	fclose(fp);
	fclose(fout);
	system("cls");
}
//��ѯ�γ�
void QueryCourse() {
	fflush(stdin);
	printf("\n\n\t\t=========  ����γ���Ϣ[��ѯ]  ==========\n");
	if(stack.size==0) {
		printf("\t\t\t���޿γ���Ϣ\n");
		system("pause");
		return;
	}
	char c;
	while(true) {
		system("cls");
		printf("\n\n\t\t=========  ����γ���Ϣ[��ѯ]  ==========\n");
		printf("\t\t(1)����ѧ�ֲ�ѯ[�����ӡ]\n\t\t(2)���տγ����ʲ�ѯ\n\t\t(0)�������˵�\n\t\t(1/2/0):");
		if((c=getchar())=='0')
			break;
		switch(c) {
			case '1':
				printByOrderDesc();
				system("pause");
				continue;
			case '2':
				printf("\t\tA/a.������ B/b.���޿� C/c.ѡ�޿�:\n\t\t");
				fflush(stdin);//��ˢ�»���Ļ��ᱻ�����getchar()�ջ� 
				char abc=getchar();
				if(abc=='A'||abc=='a') {
					QUERY_BY_TYPE("������");
				} else if(abc=='B'||abc=='b') {
					QUERY_BY_TYPE("���޿�");
				} else if(abc=='C'||abc=='c') {
					QUERY_BY_TYPE("ѡ�޿�");
				}
				system("pause");
				continue;
		}
	}
}

/**
*����ѧ�ֽ������кʹ�ӡ
**/
void printByOrderDesc() {
	tmpStack=stack;//����
	for(int i=0; i<num-1; i++) {//ð������
		for(int j=0; j<num-i-1; j++) {
			if(tmpStack.courses[j].score<tmpStack.courses[j+1].score) {//�Ƚϸ��γ̷�����С��ǰ��һ���һ��Сʱ���滻˳��Ҳ���ǣ������ǰ��С���ں� �����մ�ӡ���Ϊ����
				Course c=tmpStack.courses[j];
				tmpStack.courses[j]=tmpStack.courses[j+1];
				tmpStack.courses[j+1]=c;
			}
		}
	}
	print_stack(tmpStack);
}

//�����ʹ�ӡջ
void print_stack(CStack stack) {
	print_sheet_head();
	for(int i=0; i<stack.size; i++) {
//		printf("\%4s\t%4s\t%4s\t%0.1f\t%0.1f\t%0.1f\t%0.1f\t%0.1f\t%8s\n",
		printf("%s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",
		       stack.courses[i].no,
		       stack.courses[i].name,
		       stack.courses[i].type,
		       stack.courses[i].totalTime,
		       stack.courses[i].givingCourseTime,
		       stack.courses[i].practiceTime,
		       stack.courses[i].operatingTime,
		       stack.courses[i].score,
		       stack.courses[i].info
		      );
	}
}

