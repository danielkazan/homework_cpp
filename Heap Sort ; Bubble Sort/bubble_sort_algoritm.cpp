void bubblesort(int* l, int* r) {
	int sz = r - l;
	if (sz <= 1) return;
	bool b = true;
	while (b) {
		b = false;
		for (int* i = l; i + 1 < r; i++) {
			if (*i > *(i + 1)) {
				swap(*i, *(i + 1));
				b = true;
			}
		}
		r--;
	}
}