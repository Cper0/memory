#include<Siv3D/Siv3D.hpp>
#include<vector>
#include<limits>
#include"wave.hpp"

using namespace std;

int w = 128;
int h = 128;

double dx = 0.1;
double dy = 0.1;

double c = 1;
double dt = 0.01;

vector<vector<double>> u(h, vector<double>(w));
vector<vector<double>> v(h, vector<double>(w));
vector<vector<double>> u_new(h, vector<double>(w));

long long n = 0;

double sigmoid(double x) {
	return 1.f / (1.f + std::exp(-x));
}

double min() {
	double v = 100000;
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			v = std::min(u[y][x], v);
		}
	}
	return v;
}

double max() {
	double v = -100000;
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			v = std::max(u[y][x], v);
		}
	}
	return v;
}

void write_image(Image& img) {
	const double a = min();
	const double b = max();
	const double l = b - a;
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			const double c = (u[y][x] - a) / l;
			img[y][x] = ColorF{c, c, c};
		}
	}
}

void load_image() {
	Image img = Dialog::OpenImage();
	if(img.width() == w && img.height() == h) {
		img.grayscale();
		
		for(int y = 0; y < h; y++) {
			for(int x = 0; x < w; x++) {
				const double c = 1.0 * img[y][x].r / 255.0;
				u[y][x] = c;
			}
		}
	}
}

void update() {
	for(int y = 1; y < h - 1; y++) {
		for(int x = 1; x < w - 1; x++) {
			const double fil = u[y+1][x] + u[y-1][x] + u[y][x+1] + u[y][x-1] - 4 * u[y][x];
			u_new[y][x] = 2 * u[y][x] - v[y][x] + std::pow(c * dt / dx, 2) * fil;
		}
	}

	v = u;
	u = u_new;
}

void Main() {
	DynamicTexture tex(Image(sha::Wave::width, sha::Wave::height));

	sha::Wave wave(dx, dy, c, dt);

	while(System::Update()) {
		if(SimpleGUI::Button(U"Clear", Vec2{0, 100}, 100)) {
			wave.clear();
		}
		if(SimpleGUI::Button(U"Load file", Vec2{0, 0}, 100)) {
			wave.load_by_dialog();
		}

		wave.update();
		tex.fill(wave.as_image());
		
		tex.scaled(5.f).draw(100, 0);
			
		n++;
	}	
}

