class Logic{ 

public:
	enum {NONE=0,SNACK=1,FOOD=2,  //�����޶��������ߡ���ʳ���������ʾ
		UP=1,DOWN=2,LEFT=3,RIGHT=4, //������������
		SCALE = 20,  //���̴�С
		MAX_LENGTH = 100  //�ߵ���󳤶�
	};
	Logic();  //���캯��
	void Init();  //��ʼ��
	int GetStatus(int x, int y); //����״̬�ӿ�
	void ChangeDirection(int direction);  //�ı����ƶ�����
	bool Move();  //�ƶ���
	bool IsDie();  //�ж����Ƿ�����
	bool AddFood();  //���ʳ��

private:
	int table[SCALE][SCALE];  //����
	int snack[MAX_LENGTH][2];  //��
	void ToTable();  //������ʾ��������
	int direction;  //���ƶ�����
	bool hasFood;  //�ж������Ƿ���ʳ��
	int food[2];  //����ʳ��λ��
	int length;  //�߳���
};	
