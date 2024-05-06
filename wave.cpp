#include"wave.hpp"

namespace sha {
	Wave::Wave() : t(width, height), u(width, height), v(width, height) {
	}

	Wave::Wave(value_t _dx, value_t _dy, value_t _c, value_t _dt) : t(width, height), u(width, height), v(width, height) {
		dx = _dx;
		dy = _dy;
		c = _c;
		dt = _dt;
	}

	void Wave::update() {
		for(int y = 1; y < height - 1; y++) {
			for(int x = 1; x < width - 1; x++) {
				const value_t f = u[y+1][x] + u[y-1][x] + u[y][x+1] + u[y][x-1] - 4.0 * u[y][x];
				v[y][x] = 2.0 * u[y][x] - t[y][x] + std::pow(c * dt / dx, 2) * f;
			}
		}

		t = u;
		u = v;
	}

	void Wave::clear() {
		t.fill(0.0);
		u.fill(0.0);
		v.fill(0.0);
	}

	void Wave::load_by_dialog() {
		Image img = Dialog::OpenImage();
		img.grayscale();

		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				u[y][x] = img[y][x].r;
			}
		}

		t = v = u;
	}

	Image Wave::as_image() const {
		const auto a = min();
		const auto b = max();
		const auto l = b - a;
		Grid<Color> grid(width, height);

		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				const value_t c = (u[y][x] - a) / l;
				grid[y][x] = ColorF{c, c, c};
				//grid[y][x] = ColorF{(u[y][x] - a) / l};
			}
		}
		return Image(grid);
	}

	Wave::value_t Wave::max() const {
		value_t a = -100000;
		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				a = std::max(a, u[y][x]);
			}
		}
		return a;
	}

	Wave::value_t Wave::min() const {
		value_t a = 100000;
		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				a = std::min(a, u[y][x]);
			}
		}
		return a;
	}
}
