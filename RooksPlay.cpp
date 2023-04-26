#include "RooksPlay.h"

void RooksPlay::play(unsigned int x, unsigned int y)
{
	std::vector<std::string> dir{ "up", "down", "right", "left" };

	while (true) {

		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100 + 200));
		unsigned int new_x = 0, new_y = 0;

		std::string log = "old coordinates - " + std::to_string(y) + " " + std::to_string(x) + " ";

		/*choose one of 4 directions and, accordingly, 
		the coordinates of the new field - within the chess field and the position of the rook*/
		int direction = rand() % 4;
		log += "dirrection is " + dir[direction];

		switch (direction) {
			case 0:
				new_x = x;
				new_y = y == 0 ? y : rand() % y;
				break;
			case 1:
				new_x = x;
				new_y = rand() % (SIZE_CHES - y) + y;
				break;
			case 2:
				new_x = rand() % (SIZE_CHES - x) + x;
				new_y = y;
				break;
			case 3:
				new_x = x == 0 ? x : rand() % x;
				new_y = y;
				break;
		}

		log += " new coordinates - " + std::to_string(new_y) + " " + std::to_string(new_x) + "\n";

		bool change_field = false;

		std::shared_lock<std::shared_mutex> sl_desk(desk_mtx);

		/*check all the squares in the direction of the rook movement*/
		/*UP TO FIX: combine the loop to view all directions into one*/
		switch (direction) {
		case 0:
			for (size_t id = new_y; id < y; id++) {
				if (ches_field[id][x]) {
					log += "\trook on the way, waiting...\n";
					sl_desk.unlock();
					std::this_thread::sleep_for(std::chrono::seconds(5));
					sl_desk.lock();

					if (!ches_field[id][x]) {
						log += "\t\tthe path is clear\n";
						continue;
					}
					else {
						change_field = true;
						log += "\t\tnot wait\n";
						break;
					}
				}
			}
			break;
		case 1:
			for (size_t id = y + 1; id <= new_y; id++) {
				if (ches_field[id][x]) {
					log += "\trook on the way, waiting...\n";
					sl_desk.unlock();
					std::this_thread::sleep_for(std::chrono::seconds(5));
					sl_desk.lock();

					if (!ches_field[id][x]) {
						log += "\t\tthe path is clear\n";
						continue;
					}
					else {
						change_field = true;
						log += "\t\tnot wait\n";
						break;
					}
				}
			}
			break;
		case 2:
			for (size_t id = x + 1; id <= new_x; id++) {
				if (ches_field[y][id]) {
					log += "\trook on the way, waiting...\n";
					sl_desk.unlock();
					std::this_thread::sleep_for(std::chrono::seconds(5));
					sl_desk.lock();

					if (!ches_field[y][id]) {
						log += "\t\tthe path is clear\n";
						continue;
					}
					else {
						change_field = true;
						log += "\t\tnot wait\n";
						break;
					}
				}
			}
			break;
		case 3:
			for (size_t id = new_x; id < x; id++) {
				if (ches_field[y][id]) {
					log += "\trook on the way, waiting...\n";
					sl_desk.unlock();
					std::this_thread::sleep_for(std::chrono::seconds(5));
					sl_desk.lock();

					if (!ches_field[y][id]) {
						log += "\t\tthe path is clear\n";
						continue;
					}
					else {
						change_field = true;
						log += "\t\tnot wait\n";
						break;
					}
				}
			}
			break;
		}

		sl_desk.unlock();

		if (cnt >= 50) break;
		cnt++;

		if (change_field) continue;

		std::unique_lock<std::shared_mutex> ul_desk(desk_mtx);
		{
			ches_field[y][x] = false;
			ches_field[new_y][new_x] = true;
			ul_desk.unlock();
		}

		x = new_x;
		y = new_y;

		Console::instance().putString(log);
	}
}

RooksPlay::RooksPlay(int number_of_rooks) {

	rooks.reserve(number_of_rooks);

	std::vector < std::pair<int, int>> rnd;

	srand(time(NULL));

	/*initial filling*/
	for (int i = 0; i < number_of_rooks; ++i)
	{
		int x = rand() % 8;
		int y = rand() % 8;
		rnd.push_back({ x, y });
		ches_field[y][x] = true;
	}

	/*create thread*/
	for (int i = 0; i < number_of_rooks; ++i)
	{
		rooks.push_back(std::thread(&RooksPlay::play, rnd[i].first, rnd[i].second));
	}

	for (int i = 0; i < number_of_rooks; ++i)
	{
		rooks[i].join();
	}
}
