#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdlib.h>

#include "backend.h"
#include "pieces.h"
#include "types.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif