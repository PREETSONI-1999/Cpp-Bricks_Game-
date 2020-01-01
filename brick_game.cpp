#include<iostream>
#include<graphics.h>
#include<stdlib.h>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<extlib.h>   //files with class declarations
using namespace std;


//public vars
int fb=0,brdstop=0,fc=0,ts=1,temp=0;
char* currentPower = "  ";
int t=0;
int nob=1;
int launchb=1;
unsigned int dx=6; //delay speed
char *levf;



Ball c[6];
Panel panel;
Brick b[10][5];


struct key
{
	int lef,righ,laun;
}play1,play2;

void keysDeclare()
{
play1.lef=52;
play1.righ=54;
play1.laun=113;
}


void Ball::move(int di,int sp)
{	
	m=xC;n=yC;
	
	if(launchb==0)
	{
		
	
		switch (di)
		{
		case 1:
			xC-=2*sp;yC-=sp;
			break;
		case 2:
			xC-=sp;yC-=sp;
			break;
		case 3:
			xC-=sp;yC-=2*sp;
			break;
		case 4:
			xC+=sp;yC-=2*sp;
			break;
		case 5:
			xC+=sp;yC-=sp;
			break;
		case 6:
			xC+=2*sp;yC-=sp;
			break;
		case 7:
			xC+=2*sp;yC+=sp;
			break;
		case 8:
			xC+=sp;yC+=sp;
			break;
		case 9:
			xC+=sp;yC+=2*sp;
			break;
		case 10:
			xC-=sp;yC+=2*sp;
			break;
		case 11:
			xC-=sp;yC+=sp;
			break;
		case 12:
			xC-=2*sp;yC+=sp;
			break;
		default:
			break;
		}
	}
}


void Board::clear()
{
	if(!brdstop&&(di==play1.lef||di==play1.righ))
	{
		setcolor(BLUE);
		setfillstyle(1,BLUE);
		bar(xC, yC,xC+len,yC+7);
		setcolor(15);
	}
}

int Brick::drawDead(void)
{
	if (!alive)
	{
		if (!f2)
		{
			setcolor(BLUE);
			setfillstyle(0,BLUE);
			bar(xC,yC,xC+width,yC+height);
			rectangle(xC, yC, xC+ width, yC + height);
			setcolor(15);
			f2=1;
		}
	}
	return 0;
}


int Brick::brickCheck(Ball& b)
{

	if (b.vC.di==2 || b.vC.di==3 || b.vC.di==1 || b.vC.di==5 || b.vC.di==6 || b.vC.di==4)
	{	
		if((b.yC >= yC) && (b.yC <= yC+height))
		{
			if(( (b.xC >= xC) && (b.xC < xC + width)) || ((b.xC+(2*b.radius)>= xC ) && ((b.xC+(2*b.radius))<= (xC+width))))
			{
				if(alive)
				{
					f2=0;
					if(b.type == 0 || b.type == 2)
					{
						if(b.vC.di == 5) b.vC.di = 8;
						if(b.vC.di == 6) b.vC.di = 7;
						if(b.vC.di == 4) b.vC.di = 9;
						if(b.vC.di == 2)b.vC.di = 11;
						if(b.vC.di == 1)b.vC.di = 12;
						if(b.vC.di == 3)b.vC.di = 10;
						return 1;
					}
				}
			}
		}
	}
	if (b.vC.di==11 || b.vC.di==10 || b.vC.di==12 || b.vC.di==8 || b.vC.di==7 || b.vC.di==9)
	{
		if((b.yC + 2*b.radius >= yC)&&(b.yC + 2*b.radius <= yC+height))
		{       
			if(( (b.xC >= xC) && (b.xC < xC + width)) || ((b.xC+(2*b.radius)>= xC ) && ((b.xC+(2*b.radius))<= (xC+width))))
			{
				if(alive)
				{       
					f2=0;
					if(b.type == 0 || b.type == 2 )
					{
						if (b.vC.di == 11) b.vC.di = 2;
						if(b.vC.di == 10) b.vC.di = 3;
						if(b.vC.di == 12) b.vC.di = 1;
						if(b.vC.di == 8) b.vC.di = 5;
						if(b.vC.di == 7) b.vC.di = 6;
						if(b.vC.di == 9) b.vC.di = 4;
					}
					return 1;
				}
			}
		}
	}
	if (b.vC.di==5 || b.vC.di==4 || b.vC.di==6 || b.vC.di==8 || b.vC.di==7 || b.vC.di==9)
	{
		if( (b.xC + 2*b.radius >= xC) && (b.xC + 2*b.radius <= xC+width))
		{
			if(((b.yC >= yC) && (b.yC <= (yC + height))) || (((b.yC + (2*b.radius))>=yC) && ((b.yC + (2*b.radius))<=(yC +height))))
			{
				if(alive)
				{       
					f2=0;
					if(b.type == 0 || b.type == 2)
					{
						if(b.vC.di == 8) b.vC.di = 11;
						if(b.vC.di == 7) b.vC.di = 6;
						if(b.vC.di == 9) b.vC.di = 4;
						if(b.vC.di == 5) b.vC.di = 2;
						if(b.vC.di == 6) b.vC.di = 1;
						if(b.vC.di == 4) b.vC.di = 3;
						f2=0;
					}
					return 1;
				}
			}
		}
	}
	if (b.vC.di==11 || b.vC.di==10 || b.vC.di==12 || b.vC.di==2 || b.vC.di==1 || b.vC.di==3)
	{	
		if( (b.xC <= xC+width) && (b.xC >= xC))
		{
			if(((b.yC >= yC) && (b.yC <= (yC + height))) || (((b.yC + (2*b.radius))>=yC) && ((b.yC + (2*b.radius))<=(yC +height))))
		    {
				if(alive)
				{       
					f2=0;
					if(b.type == 0 || b.type == 2)
					{
						if(b.vC.di == 11) b.vC.di = 8;
						if(b.vC.di == 12) b.vC.di = 7;
						if(b.vC.di == 10) b.vC.di = 9;
						if(b.vC.di == 2)b.vC.di = 5;
						if(b.vC.di == 1)b.vC.di = 6;
						if(b.vC.di == 3)b.vC.di = 4;
						f2=0;
					}
					return 1;
				}
			}
		}
	}
	return 0;
}


int Ball::checkCollision(int bX,int getmaxx,int getmaxy,int z)
{       if (alive)
		{
			if(xC <= 0 || yC <= 0 || xC >= getmaxx-(2*radius) || yC >= getmaxy-(2*radius) )
			{
				if (xC<=0)
				{
					if (vC.di==2) vC.di=5;
					if (vC.di==11) vC.di=8;
					if (vC.di==3) vC.di=4;
					if (vC.di==10) vC.di=9;
					if (vC.di==1) vC.di=6;
					if (vC.di==12) vC.di=7;
				}
				if (yC<=0)
				{
					if (vC.di==5) vC.di=8;
					if (vC.di==2) vC.di=11;
					if (vC.di==4) vC.di=9;
					if (vC.di==3) vC.di=10;
					if (vC.di==6) vC.di=7;
					if (vC.di==1) vC.di=12;
				}
				if (xC>=getmaxx-(2*radius))
				{
					if (vC.di==8) vC.di=11;
					if (vC.di==5) vC.di=2;
					if (vC.di==7) vC.di=12;
					if (vC.di==6) vC.di=1;
					if (vC.di==9) vC.di=10;
					if (vC.di==4) vC.di=3;
				}

				if ((yC + 2*radius)>= (getmaxy-7))
				{
					if(xC>=bX && xC<=bX+70 && type==2 && fb==1 )
					/*{	
						if(vC.di>6)
						vC.di=1;
						tcat=1;
						for(int k=0;k<6;k++)
						{
							if(k!=z)
							{	
								if(c[k].alive)
								{
									if((c[k].yC + 2*radius)>= (getmaxy-7))
									if(!c[k].vC.sp)
									{	c[k].tcat=0;
										c[k].vC.sp=1;
									}
								}
							}
						}
						vC.sp=0;
						brdstop=1;
					}*/
//					else
//					{
						if ((xC >= bX) && (xC <= (bX + 11)) )
						{
							if (vC.di == 10 || vC.di==12 || vC.di==11)
								vC.di=1;
							if (vC.di == 8 ||vC.di==9 ||vC.di==7)
								vC.di=1;
						}
						if((xC >= bX+12) && (xC <= (bX + 23)) )
						{
							if (vC.di == 10 || vC.di==12 || vC.di==11)
								vC.di=2;
							if (vC.di == 8 ||vC.di==9 ||vC.di==7)
								vC.di=4;
						}
						if ((xC >= bX+24) && (xC <= (bX + 35)) )
						{
							if (vC.di == 10 || vC.di==12 || vC.di==11)
								vC.di=3;
							if (vC.di == 8 ||vC.di==9 ||vC.di==7)
								vC.di=4;
						}
						if ((xC >= bX+36) && (xC <= (bX + 47)) )
						{
							if (vC.di == 10 || vC.di==12 || vC.di==11)
								vC.di=3;
							if (vC.di == 8 ||vC.di==9 ||vC.di==7)
								vC.di=4;
						}
						if ((xC >= bX+48) && (xC <= (bX +59 )) )
						{	
							if (vC.di == 10 || vC.di==12 || vC.di==11)
								vC.di=3;
							if (vC.di == 8 ||vC.di==9 ||vC.di==7)
								vC.di=5;
						}
						if ((xC >= bX+60) && (xC <= (bX + 70)) )
						{
							if (vC.di == 10 || vC.di==12 || vC.di==11)
								vC.di=6;
							if (vC.di == 8 ||vC.di==9 ||vC.di==7)
								vC.di=6;
						}
					//}
				}
				if (yC>=(getmaxy))
				{	
					clear();
					if (nob>0)
						nob--;
					alive=0;
					Ball bt;
//				    if (!c[0].alive && nob>0)
//					{
//						for(int i=0;i<6;i++)
//						{	
//							if (c[i].alive)
//							{	
//								bt=c[0];
//								c[0]=c[i];
//								c[i]=bt;
//								goto d;
//							}
//						}
//					}
d:					if(!nob)
					{
						outtextxy(getmaxx/2-(textwidth("Game Over!")/2),getmaxy/2-textheight("Game Over!"),"Game Over!");
						getch();
					//	go=1;
					}
				}
			}
		}
		return 0;
}







void Board::launch(Ball& b,int tedi)
{	
	setcolor(BLUE);
	setfillstyle(1,BLUE);		
	bar(b.xC-16+b.radius,b.yC-16,b.xC+16+b.radius,b.yC+b.radius);
	b.draw();
	setcolor(2);
	switch(b.vC.di)
	{
		case 1:
			line(b.xC+b.radius,b.yC,b.xC-16+b.radius,b.yC-8);
			break;
		case 2:
			line(b.xC+b.radius,b.yC,b.xC-12+b.radius,b.yC-12);
			break;
		case 3:
			line(b.xC+b.radius,b.yC,b.xC-8+b.radius,b.yC-16);
			break;
		case 4:
			line(b.xC+b.radius,b.yC,b.xC+8+b.radius,b.yC-16);
			break;
		case 5:
			line(b.xC+b.radius,b.yC,b.xC+12+b.radius,b.yC-12);
			break;
		case 6:
			line(b.xC+b.radius,b.yC,b.xC+16+b.radius,b.yC-8);
			break;
			default : break;
	}
	setcolor(15);
}
void Ball::draw()
{	
	
	if (alive)
	{
		if (type == 0 || type==2)
		{
			setcolor(15);
			pieslice(xC+radius, yC+radius,0,360, radius);
			setfillstyle(9,5);
			floodfill(xC+radius,yC+radius,15);
			setcolor(15);
		}

	}
}
int Brick::drawAlive(void)
{
	if (alive)
	{   
		if (!f1)
		{
			setcolor(4);
			if(powerUp)
				setfillstyle(9,12);
			else
				setfillstyle(9,12);
			bar(xC,yC,xC+width,yC+height);
			setcolor(15);
			f1=1;
		}
		setcolor(4);
		
		rectangle(xC, yC, xC+ width, yC + height);
	
		
	}
	return 0;
}

void Panel::score(int amount)
{
	points += amount;
	change = 1;
}
void Board::brd(void)
{
	setcolor(6);
	setfillstyle(1,6);
	sector(xC+len/2, yC+7/2,0,360, len/2, 7/2 );
}

void Board::draw(void)
{	
	if(!brdstop || di==27 )
    {
		if(di==play1.lef)
		{
			if(xC<=4)
			{
				brd();
			}
			else
			{
				xC-=sp;
				
				brd();
			}
		}
		else if(di== play1.righ)
		{
			if (xC>=getmaxx()-panel.width-len-4)
			{
				brd();
			}
			else
			{	
	
				xC+=sp;
				brd();
			}
		}
		else
			if(di==27)
				exit(0);
		else
			brd();
	}
}

void Ball::clear()
{	
	if (alive)
	{
		if (type == 0 || type==2)
		{	
			setcolor(BLUE);
			setfillstyle(0,15);
			
			pieslice(m+radius, n+radius,0,360, radius);
			setcolor(15);
		}
		if (type == 1)
		{
			setcolor(RED);
			setfillstyle(0,0);
			bar(m,n,m+2*radius,n+2*radius);
			pieslice(m+radius, n+radius,0,360, radius);
			line(xC,yC,xC+5,yC+5);
			setcolor(15);
		}
	}
}
void Panel::draw()
{
	//Base
	setfillstyle(1, 7);
	//bar(getmaxx()-width, 0,getmaxx(),getmaxy());
	setfillstyle(0, 0);

	//Score
	
	char strScore[10];
	itoa(points,strScore,10);
	setfillstyle(0, 7);
	
	bar(getmaxx()-panel.width/2-textwidth(strScore)/2,0-textheight(strScore),getmaxx()/2+textwidth(strScore),textheight(strScore));
	setcolor(WHITE);
	settextstyle(4,0,2);
	outtextxy(getmaxx()-panel.width/2-(textwidth(strScore)/2),50-textheight(strScore),strScore);
	outtextxy(getmaxx()-panel.width,50-textheight(strScore)-textheight(strScore),"SCORE:");
//	outtextxy(getmaxx()-panel.width/2-(textwidth(currentPower)/2), 100-textheight(currentPower),currentPower);

	//Default Change
	change = 0;
}


int Brick::aliveInit(void)
{
	int r = rand()%3;
	if (r == 0)
		r++;
	return r;
}
void Brick::brickDesignInit(void)
{
	 int r = rand()%2;
	// if(r == 0)
		//alive = 0;
}
int Brick::brickInit(void)
{
     int r = rand()%2;
	 int a = rand()%2;

	 if(!r && !a)
		return (rand()%5)+1;
	 else
		return 0;
}
void split()
{
	//if (c[0].type==3)
	//{
	setcolor(RED);
	bar(c[0].xC-10,c[0].yC-10,c[0].xC+2*c[0].radius+10,c[0].yC+2*c[0].radius+10);
	for(int i = 0; i <6; i++)
	{	
		c[0].type=0;
		c[i]=c[0];
		c[i].vC.di=(i+1);
		c[i].alive = 1;
	}	
	cleardevice();
	panel.change = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			b[i][j].f1 = 0;
		}
	}
	nob=6;
}

void leveldesign()
{
	ifstream f;
	f.open(levf);
	for(int i=0;i<10;i++)
	{	
		for(int k=0;k<5;k++)
		{
			f.read((char*)&b[i][k],sizeof(b[i][k]));
		}
	}
	f.close();
	for( int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{	
			b[i][j].powerUp = b[i][j].brickInit();
			
			b[i][j].f1 = 0;
			b[i][j].f2 = 0;
		}
		
	}

}
void gameStart()
{
	setcolor(5);
	settextstyle(4,0,12);
	outtextxy(getmaxx()/2-(textwidth("BRICKZ")/2),getmaxy()/2-textheight("BRICKZ"),"BRICKZ");
	settextstyle(4,0,2);
	outtextxy(getmaxx()/2-(textwidth("Press any key to start...")/2),getmaxy()/2-textheight("Press any key to start...")+200,"Press any key to start...");
	getch();
	cleardevice();
	settextstyle(0,0,1);
	outtextxy(getmaxx()/2-(textwidth("Loading...")/2),getmaxy()/2-textheight("Loading..."),"Loading...");
	delay(1000);
	cleardevice();
}


void posinit(Board& b1)
{
	if(launchb==1)
	{	
		int a=0,temdir=0,flag1=0;
		c[0].xC=b1.xC + b1.len/2;
		c[0].yC=b1.yC-2*c[0].radius;
		
		b1.launch(c[0],temdir) ;
		temdir++;
//		for(int i=0;i<6;i++)
//		{
//			c[i].clear();
//			if(i!=0)
//			c[i].alive=0;
//		}
//		c[0].xC=b1.xC + b1.len/2;
//		c[0].yC=b1.yC-2*c[0].radius;
		c[0].draw();
		
		while(launchb==1)
		{
			temdir=c[0].vC.di;
			if(kbhit())
			{	
				a=getch();
				
				if(a==play1.lef&& temdir!=1)
				{
					c[0].vC.di--;
					b1.launch(c[0],temdir) ;
				}
				if(a==play1.righ&& temdir!=6)
				{
					c[0].vC.di++;
					b1.launch(c[0],temdir) ;	
				}
				if(a == play1.laun)
					launchb=0;
				if(a==27)
					exit(0);
			}
		}
	}
 }

int main()
{	
	
	keysDeclare();
	int gdriver = DETECT, gmode, errorcode;/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "C://turboc3//bgi");
	
	
	setbkcolor(BLUE);
	
	int radius =30;
	//bar(10,10,10+2*radius,10+2*radius);
			//pieslice(0+radius, 0+radius,0,360, radius);
	
			
			
	gameStart();
	int n=1;
	//index balls
	for (int inc = 0; inc < 6; inc++)
	{
		c[inc].index = inc; //Ball c[6];
	}
	int l=0,gamest=0;
	while(!gamest)
	{
		if(kbhit())
		{
			l=getch();
			
		}
		//Check l
		if (l==13)
		{	
			if (n==1||n==2||n==3||n==5||n==4)
			gamest=1;
			//if(n==3)
		}
	
	}
	cleardevice();
	setbkcolor(1);
	levf="level1.lvl\0";
	
	//void levelini()
//{
	int ixC = 200, iyC = 100;
	for (int i = 0; i < 10; i++)
	{
		ixC=200;
		for (int j = 0; j < 5; j++)
		{
			b[i][j].xC=ixC;
			ixC+=50;
			b[i][j].yC =iyC;
		}
		iyC+=10;
	}
	ofstream fi;
	fi.open(levf);
	fi.write((char*)&b,sizeof(Brick)*50);
	fi.close();

	for(int i=0;i<10;i++)
	{
		for(int j=0;j<5;j++)
		{
			b[i][j].f1=0;
		}
	}
//}
	//Declare Maximums of the Screen
	const int mX=getmaxx()-panel.width,mY=getmaxy(); int a=0; 
	//DECLARING OBJECTS:-
	// declaring board
	Board b1,b2;
	b1.di = 53; b1.len = 70;
	b1.xC = ((mX/2)-((b1.len)/2));
	 
	// declaring ball
	c[0].alive =1;
	c[0].xC=b1.xC + b1.len/2;
	c[0].yC=b1.yC-2*c[0].radius;
	int z = 5;
	//init Variables
	int tedi=0; //Temporary Direction
	
	
	int bricksAlive = 10 * 5;
	
	leveldesign();
		launchb=1;
		int fn=0,tick=10;
	do
	{
			setcolor(0);
			line(getmaxx()-panel.width,0,getmaxx()-panel.width,getmaxy());
			line(getmaxx()-panel.width+1,0,getmaxx()-panel.width+1,getmaxy());
			
			if (panel.change)
			{
				panel.draw();
			}	
			if (n==1)
			{
				b1.di = 1;
				b2.di=1;
			}
			
			if (t)
			{	
				for(int x=0;x<6;x++)
				{
					if(c[x].alive)
					{	
						
						c[x].clear();
					}
						
				}
				split();
				t = 0;
			}
			
			for(int k=0;k<6;k++)
			{
				if(c[k].alive)
				//Check the keyboard buffer:-
				{
					if(kbhit() )
					{
						a = getch();
			
						b1.di=a;
				

					}
				}
			}
			
			
			
			
			
			for (int z=0; z < 6; z++)
			{
				if(c[z].alive)
				{
					c[z].move(c[z].vC.di,c[z].vC.sp);
					c[z].checkCollision(b1.xC,mX,mY-7,z);
					
				}
			}
			bricksAlive = 10 * 5;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					for (z=0; z < 6; z++)
					{
						if(c[z].alive)
						{
							if(b[i][j].brickCheck(c[z]))
							{
								if (b[i][j].alive)
								{
									panel.score(5);
									
								}						
								b[i][j].alive = 0;
							}
						}
					}
					
					if (b[i][j].alive == 0)
					{	
						cout<<"[" <<i <<"]["<<j <<"] gaya\n";
						bricksAlive--;
					}
						
					
				}
			}
			
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					b[i][j].drawDead();
				}
			}
			
			
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					b[i][j].drawAlive();
				}
			}
			for (int z=0; z < 6; z++)
			{
				if(c[z].alive)
				{
					c[z].clear();
					
					c[z].draw();
				}
			}
			b1.clear();
			b1.draw();
			posinit(b1);
	}while(bricksAlive!=0);
	
	getch();
}
