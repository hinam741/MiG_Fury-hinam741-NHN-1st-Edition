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
