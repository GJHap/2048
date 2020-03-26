#ifndef _2048
#define _2048

#include <algorithm>
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>
#include <curses.h>
#include <string>

#define KEY_ESC 27

enum TextColor {RED = 1, BLUE, GREEN, YELLOW, MAGENTA, CYAN, WHITE};


class TwentyFortyEight {
	private:
		std::vector<std::vector<uint32_t>> matrix;
		std::vector<std::vector<bool>> combined;
		std::default_random_engine randomGenerator;
		uint32_t score;
		uint32_t height;
		uint32_t width;

		void generate();
		void print();
		void printColor(const TextColor&, const char*, const uint32_t&, const uint32_t&);
		void moveDown();
		void moveLeft();
		void moveRight();
		void moveUp();
		
		bool gameOver();
		bool isValidLeftMove();
		bool isValidRightMove();
		bool isValidUpMove();
		bool isValidDownMove();

	public:
		TwentyFortyEight();
		~TwentyFortyEight();
		void start();
		
};

#endif