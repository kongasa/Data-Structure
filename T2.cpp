#include "Line_editing_system.h"

int main() {
	Line_editing_system system;
	system.open("file.txt");
	system.list(1, 4);
	cout << endl;
	system.del(1, 2, 16);
//	system.list(1, 3);
	return 0;
}