#pragma once
#include <iostream>
#include <string> 
#include <thread>
#include <vector>
#include <shared_mutex>
#include <atomic>

#include "Console.h"

#define MAX_FIGURE 6
#define MIN_FIGURE 4
#define SIZE_CHES 8

static std::mutex cnt_mtx;
static std::atomic_int cnt(0);

static std::shared_mutex desk_mtx;
static std::vector<std::vector<bool> > ches_field(SIZE_CHES, std::vector<bool>(SIZE_CHES));

class RooksPlay
{
public:
	RooksPlay(int number_of_rooks = 5);
private:
	static void play(unsigned int x, unsigned int y);

private:
	std::vector<std::thread> rooks;
};

