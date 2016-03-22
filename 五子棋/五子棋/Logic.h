class Logic{ 

private:
	static const int NONE = 0;
	static const int WHITE = 1;
	static const int BLACK = 2;  //定义黑白子和无子的整数表示

	

	static const int width = 10;
	int table[width][width];  //棋盘

	bool Count(int x, int y, int sx, int sy);  //辅助IsWin()，判断是否连成五子
	
public:
	int total;  //当前棋子数
	void Init();  //初始化棋盘
	bool Go(int x, int y);  //下棋
	bool IsDraw();  //判断平局
	bool IsWin(int x, int y);  //判断胜利
	int GetStatus(int x, int y); //读取某点的棋子颜色

};	
