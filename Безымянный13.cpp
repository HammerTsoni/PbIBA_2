#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <time.h>
#include <graphics.h>
using namespace std;

class Predator {

public:
	int x, y, health, size, fieldOfView, movementSpeed, movementDirection;
	bool findFood = false;
	Predator();
	void Movement(int,int,int);
	void Hunt();
	void Out();
};

class Fish : public Predator {

public:
	Fish();
	void Death();
};

Predator::Predator() 
{
	x = 700 + rand()%400; y = 400 + rand()%200;
//	x = 430 - rand()%2; y = 330 - rand()%2;
//	x = 650; y = 325;
	size = 15;
	fieldOfView = 90;
	movementSpeed = 2;
	movementDirection = rand()%4;
	health = 10;
}

Fish::Fish()
{
	x = rand()%600 - 100; y = rand()%300 - 100;
	//x = 400 + rand()%3; y = 300 + rand()%3;
	size = 5 + rand()%2;
	fieldOfView = 15;
	movementSpeed = 2;
	movementDirection = rand()%4;
	health = 1;
}

void Predator::Movement(int Step, int Dir, int bColor) // Движение 
{	
	setcolor(bColor);
	setfillstyle(1, bColor);

	//случайная смена напр. движения
	if (health > 0 and Dir % rand()%40 == 0) 
	{
		if (bColor == 4 and findFood == false) movementDirection = rand()%4;
		
		if (bColor == 15) movementDirection = rand()%4;
	}
	
	/*//условие нестолкновнеия с другими // 				
	if (getpixel(x -= Step -= size, y) == 15 or getpixel(x -= Step, y) == 4) movementDirection = 3;
	if (getpixel(x, y += Step += size) == 15 or getpixel(x, y += Step) == 4) movementDirection = 2;
	if (getpixel(x, y -= Step -= size) == 15 or getpixel(x, y -= Step) == 4) movementDirection = 1;
	if (getpixel(x += Step += size, y) == 15 or getpixel(x += Step, y) == 4) movementDirection = 0;	
	*/	
	
	/*//уменьшение здоровья и гибель хищника без учета того, что он поел 
	if (bColor == 4) {
		if (Dir % 10 == 0) health -= 1;
		if (health < 1) movementDirection = 1;
	} //*/
	
	//сама анимация перемещения
	if (health > 0 or bColor == 4) {
		if (movementDirection == 0) {  
			x -= Step;  /*putpixel(x, y, bColor);*/  
			circle(x, y, size); floodfill(x, y, bColor);
			putpixel(x - size/2, y - size/4, 0);
			//setcolor(15); line(x, y, x - size, y); setcolor(bColor); 
			line(x, y, x + 1.5*size, y - 1.5*size); line(x, y, x + 1.5*size, y + 1.5*size); line(x + 1.5*size, y - 1.5*size, x + 1.5*size, y + 1.5*size); floodfill(x + size+2, y, bColor);
			/*cout<<"x = "<< x <<", y = "<< y <<"\n";*/ 
			}
		else if (movementDirection == 1) {  
				y += Step; /*putpixel(x, y, bColor);*/   
				circle(x, y, size); floodfill(x, y, bColor); 
				putpixel(x - size/2, y - size/4, 0);
				//setcolor(15); line(x, y, x - size, y); setcolor(bColor);  
				line(x, y, x+1.5*size, y-1.5*size); line(x, y, x+1.5*size, y+1.5*size); line(x+1.5*size, y-1.5*size, x+1.5*size, y+1.5*size); floodfill(x+size+2, y, bColor);
				/*cout<<"x = "<< x <<", y = "<< y <<"\n";*/  
				}
		else if (movementDirection == 2) {  
				y -= Step; /*putpixel(x, y, bColor);*/   
				circle(x, y, size); floodfill(x, y, bColor);
				putpixel(x + size/2, y - size/4, 0);
//				setcolor(15); line(x, y, x + size, y); setcolor(bColor);  
				line(x, y, x-1.5*size, y-1.5*size); line(x, y, x-1.5*size, y+1.5*size); line(x-1.5*size, y-1.5*size, x-1.5*size, y+1.5*size); floodfill(x-size-2, y, bColor);
				/*	cout<<"x = "<< x <<", y = "<< y <<"\n";*/ 
				}
		else {  
				x += Step;  /*putpixel(x, y, bColor);*/   
				circle(x, y, size); floodfill(x, y, bColor); 
				putpixel(x + size/2, y - size/4, 0);
//				setcolor(15); line(x, y, x + size, y); setcolor(bColor); 
				line(x, y, x-1.5*size, y-1.5*size); line(x, y, x-1.5*size, y+1.5*size); line(x-1.5*size, y-1.5*size, x-1.5*size, y+1.5*size); floodfill(x-size-2, y, bColor);	
				/*cout<<"x = "<< x <<", y = "<< y <<"\n";*/ 
				}
	}
	
	//условие непокидания территории
	if (x > 1100) movementDirection = 0; //влево
	if (x < 100) movementDirection = 3; //вправо
	if (y > 600) movementDirection = 2; //вверх
	if (y < 100) movementDirection = 1; //вниз

	// Неудачная попытка сделать трупы на дне(
	//if (y > 670) setfillstyle(1,0); circle(x, y, size); floodfill(x, y, 0); setfillstyle(1,4);
}

void Predator::Hunt() // Пока что определение цвета вокруг
{
	for (int i = 0; i < fieldOfView; i++) {
//				findFood = true; cout<<"Нашел \n findFood = "<< findFood <<"\n";
				if ( getpixel(x, y - i) == 15 ) {
					movementDirection = 2; break;
				}
					else if ( getpixel(x - i, y) == 15 ) {
						movementDirection = 0; break;
					}
						else if ( getpixel(x, y + i) == 15 ) {
							movementDirection = 1; break;
						}
							else if ( getpixel(x + i, y) == 15 ) {
								movementDirection = 3; break;
							}
			if (i % 10 == 0) findFood = false;
			//cout<<" , x - fieldOfView/2 + i = "<< x - fieldOfView/2 + i <<", y - fieldOfView/2 + j = "<< y - fieldOfView/2 + j <<"\n";
			//cout<<" , x - fieldOfView/2 + i = "<< x - fieldOfView/2 + i <<"\n";
//			cout<<getpixel(x - fieldOfView/2 + i, y - fieldOfView/2 + j)<<"\n";
	}
}

void Fish::Death()
{
	for (int i = 0; i < fieldOfView; i++) {
		for (int j = 0; j < fieldOfView; j++) {
			if ( getpixel(x - fieldOfView/2 + i, y - fieldOfView/2 + j) == 4 ) health = 0;
			//cout<<" x - fieldOfView/2 + i = "<< x - fieldOfView/2 + i <<", y - fieldOfView/2 + j = "<< y - fieldOfView/2 + j <<"\n";
			//cout<<" getpixel(x - fieldOfView/2 + i, y - fieldOfView/2 + j) = "<< getpixel(x - fieldOfView/2 + i, y - fieldOfView/2 + j) <<"\n";
		}
	}
}

void Predator::Out() 
{
//	cout<<"Size = "<<size<<", FOV = "<<fieldOfView<<", speed = "<<movementSpeed<<", Direction = "<<movementDirection<<"\n\n";
//	cout<<"\n health = "<< health <<"\n";
//	cout<<"\n findFood = "<< findFood <<"\n";
}

int main () {
	setlocale (0,"Rus");

	srand(time(NULL));

	initwindow(1200,700);
	//setfillstyle(1,5);
	setbkcolor(0);

	Predator A [1];
	//Predator A;
	
	Fish a [20];
	//Fish a;

	int maxX = getmaxx();
	int maxY = getmaxy();

	for (int j = 0; ; j++) {
///*
		for (int i = 0; i < 20; i++) {
			a [i].Movement(2, j, 15);
			//a [i].Out();
		}//*/
		//a.Movement(5,j,15);
		//cout<<" j = "<< j <<"\n"; 

		///*
		for (int i = 0; i < 1; i++) {
			A [i].Movement(2, j, 4);
//			A [i].Out();
			A [i].Hunt();
//			A [i].Out();
		}//*/
		//A.Movement(10,j,4);
		
		for (int i = 0; i < 20; i++) {
			a [i].Death();
		}
		
		delay(100);
		cleardevice();
	}

	getch();
	closegraph();
	return 0; 
}
