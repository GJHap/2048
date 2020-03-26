#include "2048.hpp"

TwentyFortyEight :: TwentyFortyEight() {
	matrix = 
	{{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}};

	combined = 
	{{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0 , 0}};

	score = 0;

	randomGenerator.seed(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));

	
	initscr();
	getmaxyx(stdscr, height, width);
	noecho();
	keypad(stdscr, true);
	start_color();
	init_pair(TextColor::RED, COLOR_RED, COLOR_BLACK);
	init_pair(TextColor::BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(TextColor::GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(TextColor::YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(TextColor::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(TextColor::CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(TextColor::WHITE, COLOR_WHITE, COLOR_BLACK);

}

TwentyFortyEight :: ~TwentyFortyEight() {
	endwin();
}

void TwentyFortyEight :: start() {
	uint32_t input;

	generate();
	print();
	while((input = getch()) != KEY_ESC &&  !gameOver()){
		bool isValidMove = false;
		switch(input) {
			case KEY_LEFT:
				if(isValidLeftMove()) {
					moveLeft();
					isValidMove = true;
				}
				break;
			case KEY_RIGHT:
				if(isValidRightMove()) {
					moveRight();
					isValidMove = true;
				}
				break;
			case KEY_UP:
				if(isValidUpMove()) {
					moveUp();
					isValidMove = true;
				}
				break;
			case KEY_DOWN:
				if(isValidDownMove()) {
					moveDown();
					isValidMove = true;
				}
				break;
			default:
				break;
				
		}

		if(isValidMove) {
			clear();
			generate();
			print();
			for(uint32_t i = 0; i < 4; ++i) 
				std::fill(combined[i].begin(), combined[i].end(), false);
		}
	
	}
	

}

void TwentyFortyEight :: print() {
	printColor(TextColor::YELLOW, "+-----------------------+\n", (height - 6) / 2, (width - 29) / 2);
	for(uint32_t i = 0; i < 4; ++i) {
			printColor(TextColor::YELLOW, "|", ((height - 6) / 2) + i + 1, ((width - 29) / 2));
		for(uint32_t j = 0; j < 4; ++j) {
			switch(matrix[i][j]) {
				case 2:
					printColor(TextColor::RED, "2", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 4:
					printColor(TextColor::CYAN, "4", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 8:
					printColor(TextColor::MAGENTA, "8", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 16:
					printColor(TextColor::BLUE, "16", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 32:
					printColor(TextColor::WHITE, "32", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 64:
					printColor(TextColor::GREEN, "64", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 128:
					printColor(TextColor::RED, "128", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 256:
					printColor(TextColor::CYAN, "256", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 512:
					printColor(TextColor::MAGENTA, "512", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 1024:
					printColor(TextColor::BLUE, "1024", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 2048:
					printColor(TextColor::WHITE, "2048", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
				case 4096:
					printColor(TextColor::GREEN, "4096", ((height-6) / 2) + i + 1, ((width - 29) / 2) + 1 + 6*j);
					break;
			}
			printColor(TextColor::YELLOW, "|", ((height - 6) / 2) + i + 1, ((width - 29) / 2) +  6*(j+1));
		}
	}
	printColor(TextColor::YELLOW, "+-----------------------+\n", ((height - 6) / 2) + 5, (width - 29) / 2);
	mvprintw(0,0, "Score: %d", score);
}

void TwentyFortyEight :: printColor(const TextColor& color, const char* value, const uint32_t& y, const uint32_t& x) {
	attron(COLOR_PAIR(color));
	mvaddstr(y, x, value);
	attroff(COLOR_PAIR(color));
}

void TwentyFortyEight :: moveDown() {
	for(uint32_t i = 0; i < 3; ++i) {
		for(uint32_t row = 3; row > 0; --row) {
			for(uint32_t col = 0; col < 4; ++col) {
				if(matrix[row][col] == matrix[row-1][col] && !combined[row][col] && !combined[row-1][col]) {
					matrix[row][col] += matrix[row-1][col];
					score += matrix[row][col];
					matrix[row-1][col] = 0;
					combined[row][col] = true;
				} else if(matrix[row][col] == 0) {
					matrix[row][col] += matrix[row-1][col];
					matrix[row-1][col] = 0;
					combined[row][col] = combined[row-1][col];
					combined[row-1][col] = false;
				}
			}
		}
	}
}

void TwentyFortyEight :: moveLeft() {
	for(uint32_t i = 0; i < 3; ++i) {
		for(uint32_t col = 0; col < 3; ++col) {
			for(uint32_t row = 0; row < 4; ++row) {
				if(matrix[row][col] == matrix[row][col+1] && !combined[row][col] && !combined[row][col+1]) {
					matrix[row][col] += matrix[row][col+1];
					score += matrix[row][col];
					matrix[row][col+1] = 0;
					combined[row][col] = true;
				} else if(matrix[row][col] == 0) {
					matrix[row][col] += matrix[row][col+1];
					matrix[row][col+1] = 0;
					combined[row][col] = matrix[row][col+1];
					combined[row][col+1] = false;
				}
			}
		}
	}
}

void TwentyFortyEight :: moveRight() {
	for(uint32_t i = 0; i < 3; ++i) {
		for(uint32_t col = 3; col > 0; --col) {
			for(uint32_t row = 0; row < 4; ++row) {
				if(matrix[row][col] == matrix[row][col-1] && !combined[row][col] && !combined[row][col-1]) {
					matrix[row][col] += matrix[row][col-1];
					score += matrix[row][col];
					matrix[row][col-1] = 0;
					combined[row][col] = true;
				} else if(matrix[row][col] == 0) {
					matrix[row][col] += matrix[row][col-1];
					matrix[row][col-1] = 0;
					combined[row][col] = combined[row][col-1];
					combined[row][col-1] = false;
				}
			}
		}
	}
}

void TwentyFortyEight :: moveUp() {
	for(uint32_t i = 0; i < 3; ++i) {
		for(uint32_t row = 0; row < 3; ++row) {
			for(uint32_t col = 0; col < 4; ++col) {
				if(matrix[row][col] == matrix[row+1][col] && !combined[row][col] && !combined[row+1][col]) {
					matrix[row][col] += matrix[row+1][col];
					score += matrix[row][col];
					matrix[row+1][col] = 0;
					combined[row][col] = true;
				} else if(matrix[row][col] == 0) {
					matrix[row][col] += matrix[row+1][col];
					matrix[row+1][col] = 0;
					combined[row][col] = combined[row+1][col];
					combined[row+1][col] = false;
				}
			}
		}
	}
}

void TwentyFortyEight :: generate() {
	uint32_t number = (randomGenerator() % 2) == 0 ? 2 : 4;
	uint32_t row;
	uint32_t col;

	bool isValid = false;
	while(!isValid) {
		row = randomGenerator() % 4;
		col = randomGenerator() % 4;

		isValid = (matrix[row][col] == 0) ? true : false;
	}
	matrix[row][col] = number;
}

bool TwentyFortyEight :: gameOver() {
	return !(isValidUpMove() || isValidDownMove() || isValidLeftMove() || isValidRightMove());
}

bool TwentyFortyEight :: isValidLeftMove() {
	for(int col = 0; col < 3; ++col)
		for(int row = 0; row < 4; ++row)
			if((matrix[row][col] > 0 && matrix[row][col] == matrix[row][col+1]) || (matrix[row][col] == 0 && matrix[row][col+1] > 0))
				return true;
	return false;
}

bool TwentyFortyEight :: isValidRightMove() {
	for(int col = 3; col > 0; --col)
		for(int row = 0; row < 4; ++row)
			if((matrix[row][col] > 0 && matrix[row][col] == matrix[row][col-1]) || (matrix[row][col] == 0 && matrix[row][col-1] > 0))
				return true;
	return false;
}

bool TwentyFortyEight :: isValidUpMove() {
	for(int row = 0; row < 3; ++row)
		for(int col = 0; col < 4; ++col)
			if((matrix[row][col] > 0 && matrix[row][col] == matrix[row+1][col]) || (matrix[row][col] == 0 && matrix[row+1][col] > 0))
				return true;
	return false;
}

bool TwentyFortyEight :: isValidDownMove() {
	for(int row = 3; row > 0; --row)
		for(int col = 0; col < 4; ++col)
			if((matrix[row][col] > 0 && matrix[row][col] == matrix[row-1][col]) || (matrix[row][col] == 0 && matrix[row-1][col] > 0))
				return true;
	return false;
}