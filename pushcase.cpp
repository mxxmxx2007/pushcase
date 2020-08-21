#include <graphics.h>
#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;
void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height){
	PIMAGE temp = newimage();
	getimage(temp, fileName);
	
	if (getwidth(pimg) != width || getheight(pimg) != height)
		resize(pimg, width, height);
		
	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));

	delimage(temp);
}
struct c{
	int x,y;
};
int a[10][60][60]={
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,9,9,9,0,2,0,1},
	{1,0,2,2,2,3,3,3,0,2,5,1},
	{1,0,0,0,0,9,9,9,0,2,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
}
,
{
	{0,0,0,1,1,1,1,1,1,0},
	{0,1,1,1,0,0,0,0,1,0},
	{1,1,9,0,2,1,1,0,1,1},
	{1,9,9,2,0,2,0,0,5,1},
	{1,9,9,0,2,0,2,0,1,1},
	{1,1,1,1,1,1,0,0,1,0},
	{0,0,0,0,0,0,1,1,0,0}
}
,
{
	{0,1,1,1,1,1,1,1,0,0},
	{0,1,0,0,0,0,0,1,1,1},
	{1,1,2,1,1,1,0,0,0,1},
	{1,0,5,0,2,0,0,2,0,1},
	{1,0,9,9,1,0,2,0,1,1},
	{1,1,9,9,1,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,0}
}
};
int b[10][60][60] = {
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,9,9,9,0,0,0,1},
	{1,0,0,0,0,9,9,9,0,0,0,1},
	{1,0,0,0,0,9,9,9,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
},
{
	{0,0,0,1,1,1,1,1,1,0},
	{0,1,1,1,0,0,0,0,1,0},
	{1,1,9,0,0,1,1,0,1,1},
	{1,9,9,0,0,0,0,0,0,1},
	{1,9,9,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,0,0,1,0},
	{0,0,0,0,0,0,1,1,0,0}
}
,
{
	{0,1,1,1,1,1,1,1,0,0},
	{0,1,0,0,0,0,0,1,1,1},
	{1,1,0,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,9,9,1,0,0,0,1,1},
	{1,1,9,9,1,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,0}
}
};
c casep[101];
int casen = 0;
int dx[5] = { 0, -1, 0, 1 };
int dy[5] = { -1, 0, 1, 0 };
int x = 2,y = 10;
int fx,fy;
int k,flag = 0;
int level = 0;
/*1= 墙
  2 = 未完成的箱子
  3 = 已经完成的箱子
  5 = 玩家
  9 = 地标
*/
PIMAGE Case = newimage();	
PIMAGE Wall = newimage();
PIMAGE Player = newimage();
PIMAGE Player2 = newimage();
PIMAGE Target = newimage();
PIMAGE Finish = newimage();	
PIMAGE Floor2 = newimage();
int n,m,l;
void print(){
	for(int i = 0;i<n;i++){
		for(int j = 0;j<m;j++){
			if(a[level][i][j]==1){
				putimage(l*j,l*i,Wall);
			}else if(a[level][i][j]==2){
				putimage(l*j,l*i,Case);
			}else if(a[level][i][j]==3){
				putimage(l*j,l*i,Finish);
			}else if(a[level][i][j]==5){
				fx = i;
				fy = j;
				putimage(l*j,l*i,Player);
			}else if(a[level][i][j]==9){
				putimage(l*j,l*i,Target);
//			}else if(a[level][i][j]==0){
//				putimage(l*j,l*i,Floor);
			}			
		}
	}
}
int main(){
	//n 宽,m 长,l图像大小 
	n = 5,m = 12,l = 60;
//	cin>>n>>m;
//	for(int i = 0;i<n;i++){
//		for(int j = 0;j<m;j++){
//			cin>>a[i][j];
//		}
//	}
	initgraph(m*l,n*l, 0);
	//initgraph(1000,600, 0);
	setcaption("Push_Case Beta 1.0.5");
			
	//getimage(pimg, "case.png");
	getZoomImage(Case,"case.png",l,l);
	getZoomImage(Wall,"wall.png",l,l);
	getZoomImage(Player,"player.png",l,l);
	getZoomImage(Player2,"player2.png",l,l);
	getZoomImage(Target,"target.png",l,l);
	getZoomImage(Finish,"finish.png",l,l);
	getZoomImage(Floor2,"floor2.png",l,l);
	//putimage(0, 0, pimg);
	//绘制
	setcolor(RED);		
	setfontbkcolor(WHITE);		//字体颜色 
	setbkmode(TRANSPARENT);
	setfont(l, 0, "楷体");			//设置字体 
		
	for(int i = 0;i<n;i++){
		for(int j = 0;j<m;j++){
			//b[i][j] = a[i][j];
			if(a[0][i][j]==1){
				putimage(l*j,l*i,Wall);
			}else if(a[0][i][j]==2){
				putimage(l*j,l*i,Case);
				//casep[casen].x = i;
			}else if(a[0][i][j]==3){
				putimage(l*j,l*i,Finish);
			}else if(a[0][i][j]==5){
				putimage(l*j,l*i,Player);
			}else if(a[0][i][j]==9){
				putimage(l*j,l*i,Target);
//			}else if(a[0][i][j]==0){
//				putimage(l*j,l*i,Floor);
			}			
		}
	}
	ege_enable_aa(true);
	for (; is_run(); delay_fps(60)) {
		int direction = -1;
		//按键消息处理
		while (kbmsg()) {
			key_msg keyMsg = getkey();
			if (keyMsg.msg == key_msg_down) {
				switch (keyMsg.key) {
				case 'A': case key_left:	direction = 0;	break;
				case 'W': case key_up:		direction = 1;	break;
				case 'D': case key_right:	direction = 2;	break;
				case 'S': case key_down:	direction = 3;	break;
				}
			}
		}
		
		if (direction != -1) {
			flag = 1;
			//可以计算出下一个位置坐标
			int xGridNext = x + dx[direction], yGridNext = y + dy[direction];
			//判断移动是否会出边界，没出边界则移动
			if (a[level][xGridNext][yGridNext]!=1){
				if(a[level][xGridNext][yGridNext]!=2&&a[level][xGridNext][yGridNext]!=3){
					a[level][x][y] =b[level][x][y];
					x = xGridNext;
					y = yGridNext;
					a[level][x][y] = 5;
				}
				//移动
				if((a[level][xGridNext][yGridNext]==2||a[level][xGridNext][yGridNext]==3)&&(a[level][xGridNext+dx[direction]][yGridNext+dy[direction]]==0||a[level][xGridNext+dx[direction]][yGridNext+dy[direction]]==9)){
					a[level][xGridNext][yGridNext] =b[level][xGridNext][yGridNext];
					if(b[level][xGridNext+dx[direction]][yGridNext+dy[direction]]==9){
						a[level][xGridNext+dx[direction]][yGridNext+dy[direction]]=3;
					}else{
						a[level][xGridNext+dx[direction]][yGridNext+dy[direction]] = 2;
					}
					a[level][x][y] =b[level][x][y];
					x = xGridNext;
					y = yGridNext;
					a[level][x][y] = 5;
				}
				//计算绘制位置，绘制
				for(int i = 0;i<n;i++){
					for(int j = 0;j<m;j++){
						if(a[level][i][j]==1){
							putimage(l*j,l*i,Wall);
						}else if(a[level][i][j]==2){
							if((a[level][i-1][j]==1&&a[level][i][j-1]==1)||(a[level][i-1][j]==1&&a[level][i][j+1]==1)||(a[level][i][j+1]==1&&a[level][i+1][j]==1)||(a[level][i][j-1]==1&&a[level][i+1][j]==1)){
								xyprintf(0,0, "你输了");
								//MessageBox(NULL,"你输了","提示",MB_OK);
							}
							putimage(l*j,l*i,Case);
						}else if(a[level][i][j]==3){
							putimage(l*j,l*i,Finish);
						}else if(a[level][i][j]==5){
							if(b[level][i][j]==9){
								flag = 0;
							}
							if(direction == 0){
								putimage(l*j,l*i,Player2);
								k = 0;
							}else if(direction == 2){
								putimage(l*j,l*i,Player);
								k = 2;
							}else if(direction == 1||direction == 3){
								if(k == 0){
									putimage(l*j,l*i,Player2);
								}else if(k == 2){
									putimage(l*j,l*i,Player);
								}	
							}	
							//putimage_withalpha(l*j,l*i,Player);
						}else if(a[level][i][j]==9){
							putimage(l*j,l*i,Target);
							flag = 0;
						}else if(a[level][i][j]==0){
							putimage(l*j,l*i,Floor2);
						}			
					}
				}
				if(flag == 1){
					xyprintf(0,0, "你赢了");
					if(level != 2){
						level++;
						n = 7;
						m = 10;
						initgraph(m*l,n*l, 0);
						print();
						x = fx;
						y = fy;
						
					}
					//MessageBox(NULL,"你赢了","提示",MB_OK);
				}	
			}
		}
	}
	delimage(Wall);
	delimage(Case);
	delimage(Finish);
	delimage(Player);
	delimage(Target);
	getch();
	closegraph();
	return 0;
}
