class Logic{ 

private:
	static const int NONE = 0;
	static const int WHITE = 1;
	static const int BLACK = 2;  //����ڰ��Ӻ����ӵ�������ʾ

	

	static const int width = 10;
	int table[width][width];  //����

	bool Count(int x, int y, int sx, int sy);  //����IsWin()���ж��Ƿ���������
	
public:
	int total;  //��ǰ������
	void Init();  //��ʼ������
	bool Go(int x, int y);  //����
	bool IsDraw();  //�ж�ƽ��
	bool IsWin(int x, int y);  //�ж�ʤ��
	int GetStatus(int x, int y); //��ȡĳ���������ɫ

};	
