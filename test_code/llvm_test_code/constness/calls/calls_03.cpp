/* mutable: i */
void addTen(int& a) {
	a += 10;
}

int main() {
	int i = 10;
	addTen(i);
	return 0;
}