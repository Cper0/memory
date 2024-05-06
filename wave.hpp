#pragma once

#include<Siv3D.hpp>

using namespace std;

namespace sha {
	class Wave {
	public:
		using value_t = double;

		static constexpr int width = 128;
		static constexpr int height = 128;

		Wave();
		Wave(value_t dx, value_t dy, value_t c, value_t dt);

		void update();

		void clear();
		void load_by_dialog();

		Image as_image() const;

	private:
		value_t min() const;
		value_t max() const;

		Grid<value_t> t;
		Grid<value_t> u;
		Grid<value_t> v;

		value_t dx;
		value_t dy;
		value_t c;
		value_t dt;
	};
}
