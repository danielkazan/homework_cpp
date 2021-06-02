template <class T>
class heap {
public:
	int size() {
		return n;
	}
	int top() {
		return h[0];
	}
	bool empty() {
		return n == 0;
	}
	void push(T a) {
		h.push_back(a);
		SiftUp(n);
		n++;
	}
	void pop() {
		n--;
		swap(h[n], h[0]);
		h.pop_back();
		SiftDown(0);
	}
	void clear() {
		h.clear();
		n = 0;
	}
	T operator [] (int a) {
		return h[a];
	}
private:
	vector<T> h;
	int n = 0;
	void SiftUp(int a) {
		while (a) {
			int p = (a - 1) / 2;
			if (h[p] > h[a]) swap(h[p], h[a]);
			else break;
			a--; a /= 2;
		}
	}
	void SiftDown(int a) {
		while (2 * a + 1 < n) {
			int l = 2 * a + 1, r = 2 * a + 2;
			if (r == n) {
				if (h[l] < h[a]) swap(h[l], h[a]);
				break;
			}
			else if (h[l] <= h[r]) {
				if (h[l] < h[a]) {
					swap(h[l], h[a]);
					a = l;
				}
				else break;
			}
			else if (h[r] < h[a]) {
				swap(h[r], h[a]);
				a = r;
			}
			else break;
		}
	}
};
void heapsort(int* l, int* r) {
	heap<int> h;
	for (int *i = l; i < r; i++) h.push(*i);
	for (int *i = l; i < r; i++) {
		*i = h.top();
		h.pop();
	}
}