#pragma once

#include "Board.h"

#ifdef BENCHMARK
const int MAX_DEPTH = 9;
#else
const int MAX_DEPTH = 7;
#endif

const Slot HUMAN_PLAYER = Slot::PLAYER_1;
const Slot AI_PLAYER = Slot::PLAYER_2;

const int SPLITTING_DEPTH = 2;

const int TASK_TAG = 1;
const int TERMINATE_TAG = 2;
const int MSG_SIZE_TAG = 3;