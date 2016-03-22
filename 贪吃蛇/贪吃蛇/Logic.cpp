#include "Logic.h"
#include <cstdlib>

Logic::Logic(){
	Init();
}

void Logic::Init(){
	for (int i=0;i<SCALE;i++)  //初始化棋盘
		for (int j=0;j<SCALE;j++)
			table[i][j]=0;
	snack[0][0]=3; snack[0][1]=SCALE/2;
	snack[1][0]=2; snack[1][1]=SCALE/2;
	snack[2][0]=1; snack[2][1]=SCALE/2;
	snack[3][0]=0; snack[3][1]=SCALE/2;
	length = 4;
	direction=RIGHT;
	AddFood();
	ToTable();
}

int Logic::GetStatus(int x, int y){
	return table[x][y];
}

void Logic::ChangeDirection(int direction){
	switch(direction){
	case UP:
		if (snack[0][1]-1 != snack[1][1])
			this->direction=direction;
		break;
	case DOWN:
		if (snack[0][1]+1 != snack[1][1])
			this->direction=direction;
		break;
	case LEFT:
		if (snack[0][0]-1 != snack[1][0])
			this->direction=direction;
		break;
	case RIGHT:
		if (snack[0][0]+1 != snack[1][0])
			this->direction=direction;
		break;
	}
}

void Logic::ToTable(){
	for (int i=0;i<SCALE;i++)  //初始化棋盘
		for (int j=0;j<SCALE;j++)
			table[i][j]=NONE;
	for (int i=0;i<length;i++)  //将蛇放到棋盘上
			table [snack[i][0]][snack[i][1]] = SNACK;
	if (hasFood==true)
		table[food[0]][food[1]] = FOOD;  //将食物放到棋盘上
}

bool Logic::IsDie(){
	return ((direction==UP&&snack[0][1]==0) || (direction==DOWN&&snack[0][1]==SCALE-1) 
		|| (direction==LEFT&&snack[0][0]==0) || (direction==RIGHT&&snack[0][0]==SCALE-1));
}

bool Logic::Move(){
	if (IsDie())
		return false;
	for (int i=length-1;i>0;i--)
		for (int j=0;j<2;j++)
			snack[i][j]=snack[i-1][j];
	switch (direction){
	case UP:
		snack[0][1]--;
		break;
	case DOWN:
		snack[0][1]++;
		break;
	case LEFT:
		snack[0][0]--;
		break;
	case RIGHT:
		snack[0][0]++;
		break;
	}
	if (table[snack[0][0]][snack[0][1]]==SNACK)
		return false;
	if (table[snack[0][0]][snack[0][1]]==FOOD){
		ToTable();
		hasFood = false;
		length++;
		AddFood();
		return true;
	}
	ToTable();
	return true;
}

bool Logic::AddFood(){
	if (hasFood!=true){
		int x = -1;
		int y = -1;
		for (x = rand()%SCALE,y = rand()%SCALE;table[x][y]!=NULL;x = rand()%SCALE,y = rand()%SCALE){}
		food[0]=x;
		food[1]=y;
		table[x][y]=FOOD;
		hasFood = true;
		return true;
	}
	return false;
}