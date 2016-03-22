class Logic{ 

public:
	enum {NONE=0,SNACK=1,FOOD=2,  //定义无东西、有蛇、有食物的整数表示
		UP=1,DOWN=2,LEFT=3,RIGHT=4, //定义上下左右
		SCALE = 20,  //棋盘大小
		MAX_LENGTH = 100  //蛇的最大长度
	};
	Logic();  //构造函数
	void Init();  //初始化
	int GetStatus(int x, int y); //棋盘状态接口
	void ChangeDirection(int direction);  //改变蛇移动方向
	bool Move();  //移动蛇
	bool IsDie();  //判断蛇是否死亡
	bool AddFood();  //添加食物

private:
	int table[SCALE][SCALE];  //棋盘
	int snack[MAX_LENGTH][2];  //蛇
	void ToTable();  //将蛇显示在棋盘上
	int direction;  //蛇移动方向
	bool hasFood;  //判断现在是否有食物
	int food[2];  //保存食物位置
	int length;  //蛇长度
};	
