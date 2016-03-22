#include "Logic.h"

void Logic::Init(){
	for (int i=0;i<10;i++)
		for (int j=0;j<10;j++)
			table[i][j]=0;
	total=0;
}

bool Logic::Go(int x, int y){
	if (x>9||x<0||y>9||y<0)
		return false;
	if (table[x][y]!=NONE)
		return false;
	if (total%2==0)
		table[x][y]=BLACK;
	else
		table[x][y]=WHITE;
	total++;
	return true;
}

bool Logic::IsDraw(){
	return total==100;
}

bool Logic::IsWin(int x, int y){
	bool hor = Count(x,y,1,0);
	bool ver = Count(x,y,0,1);
	bool l2r = Count(x,y,1,1);
	bool r2l = Count(x,y,1,-1);
	if (hor||ver||l2r||r2l)
		return true;
	else
		return false;
}

bool Logic::Count(int x, int y, int sx, int sy){
	int count = 1;
	int color = table[x][y];
	int x0 = x;
	int y0 = y;
	while (((sx<0 && x+sx>=0) || (sx>0 && x+sx<10) || sx==0) && ((sy<0 && y+sy>=0) || (sy>0 && y+sy<10) || sy==0)){
		x=x+sx;
		y=y+sy;
		if (table[x][y] == color)
			count++;
		else
			break;
	}
	x=x0;
	y=y0;
	while (((sx>0 && x+sx>=0) || (sx<0 && x+sx<10 || sx==0)) && ((sy>0 && y+sy>=0) || (sy<0 && y+sy<10) || sy==0)){
		x=x-sx;
		y=y-sy;
		if (table[x][y] == color)
			count++;
		else
			break;
	}
	return (count>=5);
}

int Logic::GetStatus(int x, int y){
	return table[x][y];
}