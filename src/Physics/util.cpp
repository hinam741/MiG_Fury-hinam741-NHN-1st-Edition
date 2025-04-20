//tiện ích
#include "common.h"

#include "util.h"

//hàm kiểm tra va chạm lấy 8 đối số để thử trên 2 hình chữ nhật
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	//trả về MAX(x1,x2): điểm bắt đầu của vùng giao nhau (bên trái nhất)
	//trả về MIN(x1 + w1, x2 + w2) điểm kết thúc của vùng giao nhau (bên phải nhất)
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

//hàm tính toán bước chuẩn hóa giữa 2 điểm
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)//con trỏ dx dy tính độ dốc
{
	//tính số bước cần thiết để đi từ a -> b
	int steps = MAX(abs(x1 - x2), abs(y1 - y2));

	//trường hợp nếu 2 điểm trùng nhau
	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}
