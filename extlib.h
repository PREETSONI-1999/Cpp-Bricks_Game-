class Velocity;
class Brick;
class Ball;
class Board;
class Panel;
class TextBox;


class Velocity
{
	public:
	int sp, di;
};


class Brick
{
	public:
	int xC, yC;
	int alive, type;
	int height, width;
	int powerUp;
	 
	int f1,f2;

	int brickInit(void);
	void brickDesignInit(void);
	int aliveInit(void);
	Brick()
	{
		alive  =  1;
		height = 10;
		width  = 50;
		//powerUp=  0;
		f1=0;
		f2=0;
		xC =0;yC =0;
		powerUp= brickInit();
	    //	brickDesignInit();
	}

	int drawAlive(void);
	int drawDead(void);
	int brickCheck(Ball&);


};

class Ball
{
	public:
	int radius, xC, yC;
	int type,tcat;
	int alive;
	int m,n;
	int index;

	Velocity vC;
	void draw();
	void clear();
	void move(int,int);
	int  checkCollision(int,int,int,int);
	void collision();

	Ball()
	{

		vC.di = 2;
		vC.sp = 1;
		radius =2;
		type = 0;
		alive = 0;
		tcat=0;
	}
};

class Board
{
	public:
	int xC, yC, len, di,sp,height;
	void draw(void);
	void draw1(void);
	void brd(void);
	void clear();
  
	void launch(Ball& b,int tedi);
	//int change;
	Board()
	{	
		height = 7;
		xC=getmaxx()/2;
		sp = 15;
		yC = getmaxy()-height;
		//change = 1;
	}


};

class Panel
{
	public:
	int width,change;
	int points; char* pts;
	void score(int);
	void draw();

	Panel()
	{
		change = 1;
		width = 100;
		points = 0;
		pts = "";
	}
};
