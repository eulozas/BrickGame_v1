#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include "types.h"
#include "backend.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif 