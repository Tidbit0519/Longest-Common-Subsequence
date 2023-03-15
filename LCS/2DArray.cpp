class TwoDimIntArray {
private:
	int* data;
	int sizeX;

public:
	TwoDimIntArray(int width, int height) {
		sizeX = width;
		data = new int[width * height];
	}

	~TwoDimIntArray() {
		delete[] data;
	}

	int get(int x, int y) {
		return data[y * sizeX + x];
	}

	void set(int x, int y, int val) {
		data[y * sizeX + x] = val;
	}
};