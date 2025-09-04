#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include "types.h"
#include "backend.h"
#include <sys/time.h>
#include <stdlib.h>

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif 