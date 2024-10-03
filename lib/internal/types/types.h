/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main types of the game engine, like:
 *  - GAME_STATE
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/
#ifndef TYPES_H
#define TYPES_H

typedef enum {
    GAME_STATE_RUNNING,
    GAME_STATE_PAUSED,
    GAME_STATE_MENU,
    GAME_STATE_EXIT
} GAME_STATE;

#endif
