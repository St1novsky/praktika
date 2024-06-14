 // G_zad1.cpp: главный файл проекта.

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
using namespace std;
using namespace System;
using namespace System::IO;
#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80


struct z {
	char name[30];
	char rarity[10];
	long summa;
	char type[11];
	int time;
};
struct sp {
	char pos[30];
	long summa;
	struct sp* sled;
	struct sp* pred;
} *spisok;
int menu(int);
void minim(struct z*, int);
void fast(struct z*, int);
void ovosch(struct z*, int);
void alfalist(struct z*, int);
void vstavka(struct z*, char*, int);
void diagram(struct z*, int);
void sravn(struct z*, int);


int main(array<System::String ^> ^args)
{
	char dan[7][55]={
		"Какая самая дешевая позиция в меню?                   ",
		"Какой сырник мне принесут быстрее?		         ",
		"Какие овощные сырники дешевле 300 рублей?             ",
		"Альфалист                                             ",
		"Диаграмма                                             ",
		"Первое совпадение                                     ",
		"Выход                                                 "
	};
	char BlankLine[ ]="                                                        ";
	int NC;
	int i,n;
	FILE *in;
	struct z *position;
	setlocale(LC_CTYPE,"Russian");
	Console::CursorVisible::set(false);
	Console::BufferHeight=Console::WindowHeight;
	Console::BufferWidth=Console::WindowWidth;
	if((in=fopen("Menu.dat","r"))==NULL)
	{
		printf("\nФайл Menu.dat не открыт !");
		getch(); exit(1);
	}
	fscanf(in,"%d",&NC);
	position=(struct z*)malloc(NC*sizeof(struct z));
	printf("\n|---------------------------|---------|-------|---------|----------|");
	printf("\n|     Позиция               | Частота | Цена  |   Тип   |  Время   |");
	printf("\n|---------------------------|---------|-------|---------|----------|");
	for(i=0;i<NC;i++)
		fscanf(in,"%s%s%d%s%d",position[i].name,
		position[i].rarity, &position[i].summa, position[i].type, &position[i].time);
	for(i=0;i<NC;i++)
		printf("\n| %-25s | %-7s |  %-4d | %-7s | %2d-Минут |",
		position[i].name, position[i].rarity, position[i].summa, position[i].type, position[i].time);
	printf("\n|---------------------------|---------|-------|---------|----------|");
		getch();
	while(1)
	{
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::DarkBlue;
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Blue;
		Console::CursorLeft=10;
		Console::CursorTop=4;
		printf(BlankLine);
		for(i=0;i<7;i++)
		{
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);
}
		Console::CursorLeft=10;
		Console::CursorTop=12;
		printf(BlankLine);
		n=menu(7);
		switch(n) 
		{
		case 1: minim(position, NC); break;
		case 2: fast(position, NC); break;
		case 3: ovosch(position, NC); break;
		case 4: alfalist(position, NC); break;
		case 5: diagram(position, NC); break;
		case 6: sravn(position, NC);break;
		case 7: exit(0);
		}
	} // конец while(1)...
return 0;
} // конец main()
int menu(int n)
{
	char dan[7][55]={
		"Какая самая дешевая позиция в меню?                   ",
		"Какой сырник мне принесут быстрее?		         ",
		"Какие овощные сырники дешевле 300 рублей?             ",
		"Альфалист                                             ",
		"Диаграмма                                             ",
		"Первое совпадение                                     ",
		"Выход                                                 "
	};
	char BlankLine[ ]="                                                        ";
	int NC;
	int y1=0,y2=n-1;
	char c=1;
	while (c!=ESC)
	{
		switch(c) {
		case DOWN: y2=y1; y1++; break;
		case UP: y2=y1; y1--; break;
		case ENTER: return y1+1;
	}
	if(y1>n-1){y2=n-1;y1=0;}
	if(y1<0) {y2=0;y1=n-1;}
	Console::ForegroundColor=ConsoleColor::Cyan;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Blue;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	} // конец while(c!=ESC)...
exit(0);
}
void minim(struct z* position, int NC)
{
	int i;
	struct z worse;
	strcpy(worse.name,position[0].name);
	worse.summa=position[0].summa;
	for(i=1;i<NC;i++)
		if (position[i].summa<worse.summa)
		{
			strcpy(worse.name,position[i].name);
			worse.summa=position[i].summa;
		}
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Самый дешевый сырник: %s",worse.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Стоит: %i рублей",worse.summa);
	getch();
}
void fast(struct z* position, int NC)
{
	int i;
	struct z best;
	strcpy(best.name, position[0].name);
	best.time=position[0].time;
	for(i=1;i<NC;i++)
		if(position[i].time<best.time)
		{
			strcpy(best.name,position[i].name);
			best.time=position[i].time;
		}
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Быстрее всего принесут сырник %s",best.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("За %i Минут ",best.time);
	getch();
}
void ovosch(struct z* position, int NC)
{
	int i;
	struct z* nt;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::Clear();
	printf("\n\r                Список овощных позиций дешевле 300 рублей");
	printf("\n\r================================================================================\n\r");
	for(i=0,nt=position;i<NC;nt++,i++)
		if(nt->summa<300 && strcmp(nt->type,"Овощной")==0)
			printf("\n\r                   %-23s %ld Рублей",nt->name,nt->summa);
	getch();
}
void vstavka(struct z* position, char* pos, int NC)
{
	int i;
	struct sp *nov, *nt, *z=0;
	for(nt=spisok; nt!=0 && strcmp(nt->pos,pos)<0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->pos,pos)==0) return;
	nov =(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->pos,pos);
	nov->sled=nt;
	nov->summa=0;
	nov->pred=z;
	for(i=0;i<NC;i++)
		if(strcmp(position[i].name,pos)==0)
			nov->summa+=position[i].summa;
	if(!z) spisok=nov;
	else z->sled=nov;
	if(nt) nt->pred=nov;
	return;
}
void alfalist(struct z* position, int NC)
{
	int i;
	struct sp *nt, *z;
	printf("\n  Алфавитный список позиций");
	printf("\n=================================================");
	if(!spisok)
		for(i=0;i<NC;i++)
			vstavka(position,position[i].name, NC);
	Console::Clear();
	for(nt=spisok;nt!=0;nt=nt->sled)
		printf("\n %-30s %d", nt->pos,nt->summa);
	for(nt=spisok, z=0; nt!=0; z=nt, nt=nt->sled)
		Console::CursorTop=1;
	for(nt=z, i=0; nt!=0; i++, nt=nt->pred)
	{
		Console::CursorLeft=40;
		printf("%-30s %d", nt->pos, nt->summa);
		Console::CursorTop+=1;
	}
	getch();
}
void diagram(struct z* position, int NC) 
{ 
struct sp *nt; 
int len, i, NColor; 
long sum = 0; 
char str1[35]; 
char str2[35]; 
System::ConsoleColor Color; 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::DarkBlue; 
Console::Clear(); 
for (i=0; i<NC; i++) 
 sum = sum+position[i].summa; 
if(!spisok) 
 for(i=0; i<NC; i++) 
  vstavka(position,position[i].name, NC); 
Color=ConsoleColor::DarkRed; 
NColor=0; 
for(nt=spisok, i=0; nt!=0; nt = nt->sled, i++) 
{ 
 sprintf(str1, "%-35s", nt->pos); 
 sprintf(str2, "%3.lf%%", (nt->summa*100./sum)); 
 Console::ForegroundColor=ConsoleColor::White; 
 Console::BackgroundColor=ConsoleColor::DarkBlue; 
 Console::CursorLeft=5; 
 Console::CursorTop=i+1; 
 printf(str1); 
 Console::CursorLeft=35; 
 printf("%s", str2); 
 Console::BackgroundColor=++Color; 
 NColor++; 
 Console::CursorLeft=40; 
 for(len=0; len<nt->summa*100./sum; len++) printf(" "); 
 if (NColor==6){ 
  Color=ConsoleColor::DarkRed; 
  NColor=0; 
 } 
} 
_getch(); 
return; 
}
void sravn(struct z* postion, int NC) 
{ 
int i, j; 
int srvn=0; 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::DarkBlue;
Console::Clear(); 
for (i=0; i<NC; i++)
{ 
 for (j=i+1; j<NC; j++)
 { 
  if ((postion[i].summa == postion[j].summa) && (strcmp(postion[i].type, postion[j].type)==0))
  { 
  printf("\n %-30s Тип: %10s Цена: %3ld \n %-30s Тип: %10s Цена: %3ld", postion[i].name, postion[i].type, postion[i].summa, postion[j].name, postion[j].type, postion[j].summa); 
  srvn++;
   break; 
  } 
 } 
 if (srvn == 1) break;
} 
_getch(); 
}