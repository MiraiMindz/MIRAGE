/******************************************************************************
 * This is the start of the MIRAGE Game Engine, the idea is to create a RayCast
 * basic engine to make DOOM/Wolfeinstain3D like games.
******************************************************************************/

#include <GL/freeglut_std.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

// Macro Constants
#define PI                          3.14159265358979323846
#define MAX_UINT16                  65535
#define DEGREE_TO_RADIAN            0.0174533

// OpenGL Window Macros
#define WINDOW_TITLE    "MIRAGE_BLANK_BUFFER_0"
#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   512

// Colors
// Every color used through the project is defined as a macro, because I want to
// access them by name without having the overhead to allocate memory on the
// stack nor on the heap for them, so macros will serve really well for this.
//
// The colors are splitted between RGB, RGBA btw, so read the first word.
#define RGBA_COLOR_WHITE            1,      1,      1,      0
#define RGBA_COLOR_GRAY             0.3,    0.3,    0.3,    0
#define RGBA_COLOR_RED              1,      0,      0,      0
#define RGBA_COLOR_GREEN            0,      1,      0,      0
#define RGBA_COLOR_BLUE             0,      0,      1,      0
#define RGB_COLOR_RED               1,      0,      0
#define RGB_COLOR_GREEN             0,      1,      0
#define RGB_COLOR_GREEN_A80         0,      0.8,    0
#define RGB_COLOR_GREEN_A60         0,      0.6,    0
#define RGB_COLOR_WHITE             1,      1,      1
#define RGB_COLOR_BLACK             0,      0,      0
#define RGB_COLOR_GRAY              0.5,    0.5,    0.5
#define RGB_COLOR_YELLOW            1,      1,      0
#define RGB_COLOR_CYAN              0,      1,      1
#define RGB_COLOR_BLUE              0,      0,      1

// Player Macros
#define PLAYER_MOV_STEP             0.2
#define PLAYER_ROT_DEG              0.1
#define PLAYER_DELTA_AMP            16
#define FACE_NORTH                  90
#define FACE_EAST                   180
#define FACE_WEST                   0
#define FACE_SOUTH                  270
#define COLLISION_OFFSET            8
#define INTERACTION_OFFSET          12

// Map Macros
#define GRID_OUTLINE                1

// Ray Caster Macros
#define RAYS_COUNT                  64
#define RAYS_ACCURACY               0.0001

// 3D Macros
#define DRAW_LINE_WIDTH_3D          8
#define LINE_X_OFFSET               0
#define LINE_Y_OFFSET               0

// Types
typedef struct {
    int up, left, right, down;
} ButtonKeys;


// Globals
ButtonKeys keys;

// 32x32 Textures
int ALL_TEXTURES[] = {
    //Checkerboard
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    
    //Brick
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    
    //Window
    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,    
        
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,   
        
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
    
    //Door
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
    0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,     

    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
    0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  

    0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,   
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,     
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,   
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,  
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,         
};


// Utility Functions

// This function exists to convert between degrees to radians 
// without using any magical number for it. 
float degree_to_radian(int angle) {
    return angle * PI / 180.0;
}

// Fixes any odd/decimal angles, and cap them between a range.
float fix_angle(int angle) {
    if (angle > 359) {
        angle -= 360;
    } else if (angle < 0) {
        angle += 360;
    }

    return angle;
}

// This function calculates the distance between two points in a plane.
float distance(int ax, int ay, int bx, int by, int angle) {
    return cos(degree_to_radian(angle)) * (bx - ax) - sin(degree_to_radian(angle)) * (by - ay);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
void resize(int width, int height) {
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}
#pragma GCC diagnostic pop

// Map Section

// MAP_WIDTH represents how many CELLS the map will have in the X axis.
// MAP_HEIGHT represents how many CELLS the map will have in the Y axis.
// MAP_CELL_SIZE represents the size in pixels of each cell.
// so this map will have 4096 pixels in size.
const int MAP_CELL_SIZE = 64;
const int MAP_WIDTH     = 8;
const int MAP_HEIGHT    = 8;

// The map is a simple binary array, were 1 represents a wall and 0 not.
// becase the map is a 8x8 grid, this array needs to have 64 values to fully
// represent the map.
int MAP_WALLS[] = {
    1, 1, 1, 3, 1, 3, 3, 1,
    1, 0, 1, 0, 2, 0, 0, 1,
    1, 0, 1, 0, 2, 4, 2, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 4, 1, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 3,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 3, 1, 3, 3, 1, 1, 1,
};

int MAP_FLOOR[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 0, 3, 0,
    0, 2, 2, 2, 2, 0, 3, 0,
    0, 2, 2, 2, 2, 2, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

int MAP_CEILING[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 0, 3, 0,
    0, 2, 2, 2, 2, 0, 3, 0,
    0, 2, 2, 2, 2, 2, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};


// Iterates through the map and draws the quadrants of it.
void draw_map_2d() {
    int x, y, xOffset, yOffset;
    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            if (MAP_WALLS[y * MAP_WIDTH + x] > 0) {
                glColor3f(RGB_COLOR_WHITE);
            } else {
                glColor3f(RGB_COLOR_BLACK);
            }

            xOffset = x * MAP_CELL_SIZE;
            yOffset = y * MAP_CELL_SIZE;

            glBegin(GL_QUADS);
            glVertex2i(0 + xOffset + 1,             0 + yOffset + 1);
            glVertex2i(0 + xOffset + 1,             MAP_CELL_SIZE + yOffset - 1);
            glVertex2i(MAP_CELL_SIZE + xOffset - 1, MAP_CELL_SIZE + yOffset - 1);
            glVertex2i(MAP_CELL_SIZE + xOffset - 1, 0 + yOffset + 1);
            glEnd();
        }
    }
}

// Player Section
float player_pos_x, player_pos_y, player_delta_x, player_delta_y, player_angle;

// This function draws the player camera into the 2D space.
void draw_player_2d() {
    glColor3f(RGB_COLOR_YELLOW);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player_pos_x, player_pos_y);
    glEnd();


    // Debug line
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(player_pos_x, player_pos_y);
    glVertex2i( player_pos_x + player_delta_x * PLAYER_DELTA_AMP, 
                player_pos_y + player_delta_y * PLAYER_DELTA_AMP);
    glEnd();
}

void open_door() {
    int x_offset = 0;
    int y_offset = 0;

    if (player_delta_x < 0) {
        x_offset = -INTERACTION_OFFSET;
    } else {
        x_offset = INTERACTION_OFFSET;
    }

    if (player_delta_y < 0) {
        y_offset = -INTERACTION_OFFSET;
    } else {
        y_offset = INTERACTION_OFFSET;
    }
    int player_x_grid_position_add_offset = (player_pos_x + x_offset) / 64.0;

    int player_y_grid_position_add_offset = (player_pos_y + y_offset) / 64.0;

    if (MAP_WALLS[player_y_grid_position_add_offset * MAP_WIDTH + player_x_grid_position_add_offset] == 4) {
        MAP_WALLS[player_y_grid_position_add_offset * MAP_WIDTH + player_x_grid_position_add_offset] = 0;
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
void key_down(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            keys.up = 1;
            break;
        case 'a':
            keys.left = 1;
            break;
        case 's':
            keys.down = 1;
            break;
        case 'd':
            keys.right = 1;
            break;
        case 'e':
                open_door();
            break;
    }

    glutPostRedisplay();
}

void key_up(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            keys.up = 0;
            break;
        case 'a':
            keys.left = 0;
            break;
        case 's':
            keys.down = 0;
            break;
        case 'd':
            keys.right = 0;
            break;
    }

    glutPostRedisplay();
}

#pragma GCC diagnostic pop

// Update the keys.
void update_keys(float frames_per_second) {
    int x_offset = 0;
    int y_offset = 0;

    if (player_delta_x < 0) {
        x_offset = -COLLISION_OFFSET;
    } else {
        x_offset = COLLISION_OFFSET;
    }

    if (player_delta_y < 0) {
        y_offset = -COLLISION_OFFSET;
    } else {
        y_offset = COLLISION_OFFSET;
    }

    // Collision Variables
    int player_x_grid_position = player_pos_x / 64.0;
    int player_x_grid_position_add_offset = (player_pos_x + x_offset) / 64.0;
    int player_x_grid_position_sub_offset = (player_pos_x - x_offset) / 64.0;

    int player_y_grid_position = player_pos_y / 64.0;
    int player_y_grid_position_add_offset = (player_pos_y + y_offset) / 64.0;
    int player_y_grid_position_sub_offset = (player_pos_y - y_offset) / 64.0;

    if (keys.left == 1) {
        player_angle = fix_angle(player_angle + (PLAYER_MOV_STEP * frames_per_second));
        player_delta_x = cos(degree_to_radian(player_angle));
        player_delta_y = -sin(degree_to_radian(player_angle));
    }

    if (keys.right == 1) {
        player_angle = fix_angle(player_angle - (PLAYER_MOV_STEP * frames_per_second));
        player_delta_x = cos(degree_to_radian(player_angle));
        player_delta_y = -sin(degree_to_radian(player_angle));
    }

    // Collision Logic
    if (keys.up == 1) {
        if (MAP_WALLS[player_y_grid_position * MAP_WIDTH + player_x_grid_position_add_offset] == 0) {
            player_pos_x += player_delta_x * (PLAYER_MOV_STEP * frames_per_second);
        }
        
        if (MAP_WALLS[player_y_grid_position_add_offset * MAP_WIDTH + player_x_grid_position] == 0) {
            player_pos_y += player_delta_y * (PLAYER_MOV_STEP * frames_per_second);
        }
    }
    
    if (keys.down == 1) {
        if(MAP_WALLS[player_y_grid_position * MAP_WIDTH + player_x_grid_position_sub_offset] == 0){ 
            player_pos_x -= player_delta_x * (PLAYER_MOV_STEP * frames_per_second);
        }
        
        if(MAP_WALLS[player_y_grid_position_sub_offset* MAP_WIDTH + player_x_grid_position] == 0) {
            player_pos_y -= player_delta_y * (PLAYER_MOV_STEP * frames_per_second);
        }
    }
    

    glutPostRedisplay();
}

// Ray cast and Walls Section

// This function casts all the rays from the player and draws the corresponding
// walls into the 3D space.
void cast_scene() {
    int     rays, max_x, max_y, main_position, depth_of_field;
    float   vertical_x, vertical_y, 
            rays_x, rays_y, rays_angle, 
            x_offset, y_offset, distance_v, distance_h;

    // Draws the SKY (Roof) Color
    glColor3f(RGB_COLOR_CYAN);
    glBegin(GL_QUADS);
    glVertex2i(WINDOW_WIDTH / 2, 0);
    glVertex2i(WINDOW_WIDTH, 0);
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    glVertex2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    glEnd();

    // Draws the Ground Color
    glColor3f(RGB_COLOR_GRAY);
    glBegin(GL_QUADS);
    glVertex2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    glEnd();

    // offset half of the rays to the side to make the player be in the middle.
    rays_angle = fix_angle(player_angle + (int)(RAYS_COUNT / 2));

    // the cast loop, it shoots the rays.
    for (rays = 0; rays < RAYS_COUNT; rays++) {
        int vertical_map_texture = 0;
        int horizontal_map_texture = 0;


        // Cast/Check the Vertical Rays/Lines
        depth_of_field = 0;
        distance_v = MAX_UINT16;
        float tangent = tan(degree_to_radian(rays_angle));
        if (cos(degree_to_radian(rays_angle)) > 0.001) {
            rays_x = (((int)player_pos_x >> 6) << 6) + MAP_CELL_SIZE;
            rays_y = (player_pos_x - rays_x) * tangent + player_pos_y;
            x_offset = MAP_CELL_SIZE;
            y_offset = -x_offset * tangent;
        } else if (cos(degree_to_radian(rays_angle)) < -0.001) {
            rays_x = (((int)player_pos_x >> 6) << 6) - RAYS_ACCURACY;
            rays_y = (player_pos_x - rays_x) * tangent + player_pos_y;
            x_offset = -MAP_CELL_SIZE;
            y_offset = -x_offset * tangent;
        } else {
            rays_x = player_pos_x;
            rays_y = player_pos_y;
            depth_of_field = 8;
        }

        while (depth_of_field < 8) {
            max_x = (int)(rays_x) >> 6;
            max_y = (int)(rays_y) >> 6;
            main_position = max_y * MAP_WIDTH + max_x;
            if (main_position > 0 && main_position < MAP_WIDTH * MAP_HEIGHT && MAP_WALLS[main_position] > 0) {
                vertical_map_texture = MAP_WALLS[main_position] - 1;
                depth_of_field = 8;
                distance_v = cos(degree_to_radian(rays_angle)) * (rays_x - player_pos_x) - sin(degree_to_radian(rays_angle)) * (rays_y - player_pos_y);
            } else {
                rays_x += x_offset;
                rays_y += y_offset;
                depth_of_field += 1;
            }
        }

        vertical_x = rays_x;
        vertical_y = rays_y;
    
        // Cast/Check the Horizontal Rays/Lines
        depth_of_field = 0;
        distance_h = MAX_UINT16;
        tangent = 1.0 / tangent;
        if (sin(degree_to_radian(rays_angle)) > 0.001) {
            rays_y = (((int)player_pos_y >> 6) << 6) - RAYS_ACCURACY;
            rays_x = (player_pos_y - rays_y) * tangent + player_pos_x;
            y_offset = -MAP_CELL_SIZE;
            x_offset = -y_offset * tangent;
        } else if (sin(degree_to_radian(rays_angle)) < -0.001) {
            rays_y = (((int)player_pos_y >> 6) << 6) + 64;
            rays_x = (player_pos_y - rays_y) * tangent + player_pos_x;
            y_offset = MAP_CELL_SIZE;
            x_offset = -y_offset * tangent;
        } else {
            rays_x = player_pos_x;
            rays_y = player_pos_y;
            depth_of_field = 8;
        }

        while (depth_of_field < 8) {
            max_x = (int)(rays_x) >> 6;
            max_y = (int)(rays_y) >> 6;
            main_position = max_y * MAP_WIDTH + max_x;
            if (main_position > 0 && main_position < MAP_WIDTH * MAP_HEIGHT && MAP_WALLS[main_position] > 0) {
                horizontal_map_texture = MAP_WALLS[main_position] - 1;
                depth_of_field = 8;
                distance_h = cos(degree_to_radian(rays_angle)) * (rays_x - player_pos_x) - sin(degree_to_radian(rays_angle)) * (rays_y - player_pos_y);
            } else {
                rays_x += x_offset;
                rays_y += y_offset;
                depth_of_field += 1;
            }
        }

        float shading = 1.0;
        glColor3f(RGB_COLOR_GREEN_A80);
        if (distance_v < distance_h) {
            horizontal_map_texture = vertical_map_texture;
            shading = 0.5;
            rays_x = vertical_x;
            rays_y = vertical_y;
            distance_h = distance_v;
            glColor3f(RGB_COLOR_GREEN_A60);
        }

        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(player_pos_x, player_pos_y);
        glVertex2i(rays_x, rays_y);
        glEnd();

        int cast_angle = fix_angle(player_angle - rays_angle);
        distance_h = distance_h * cos(degree_to_radian(cast_angle));
        int line_height = (MAP_CELL_SIZE * 540) / distance_h;
        
        float texture_y_offset = 0.0;
        float texture_y_step = 32.0/(float)line_height;

        if (line_height > 540) {
            texture_y_offset = (line_height - 540) / 2.0;
            line_height = 540;
        }
        float texture_y = texture_y_offset * texture_y_step + horizontal_map_texture * 32;
        float texture_x;
        //if (rays_angle > 180) {
        //    texture_x = 31 - texture_x;
        //}

        if (shading == 1) {
            texture_x = (int)(rays_x / 2.0) % 32;
            if (rays_angle > 180) {
                texture_x = 31 - texture_x;
            }
        } else {
            texture_x = (int)(rays_y / 2.0) % 32;
            if (rays_angle > 90 && rays_angle < 270) {
                texture_x = 31 - texture_x;
            }
        }

        // Draws the Walls
        int line_offset = (WINDOW_HEIGHT / 2) - (line_height >> 1) + LINE_Y_OFFSET;
        for (int _y = 0; _y < line_height; _y++) {
            float color = ALL_TEXTURES[(int)(texture_y) * 32 + (int)(texture_x)] * shading;
            switch (horizontal_map_texture) {
                case 0:
                    glColor3f(color, color / 2.0, color / 2.0);
                    break;
                case 1:
                    glColor3f(color, color, color / 2.0);
                    break;
                case 2:
                    glColor3f(color / 2.0, color, color / 2.0);
                    break;
                case 3:
                    glColor3f(color / 2.0, color / 2.0, color);
                    break;
                default:
                    glColor3f(color, color, color);
                    break;
            }
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i(rays * DRAW_LINE_WIDTH_3D + (WINDOW_WIDTH / 2) + LINE_X_OFFSET, _y + line_offset + LINE_X_OFFSET);
            glEnd();
            texture_y += texture_y_step;
        }

        // Draws the Floor & Ceiling
        for (int _y = line_offset + line_height; _y < (WINDOW_WIDTH / 2); _y++) {
            // Calculates the projections
            float delta_y = _y - ((float)WINDOW_WIDTH / 4);
            float degrees = degree_to_radian(rays_angle);
            float rays_angle_fix = cos(degree_to_radian(fix_angle(player_angle - rays_angle)));
            // int projection_angle = (int)((0.5 * MAP_WIDTH * MAP_CELL_SIZE) / ((0.5 * WINDOW_WIDTH) / (5.0 / MAP_HEIGHT * WINDOW_HEIGHT)));
            int projection_angle = ((float)DRAW_LINE_WIDTH_3D / 2) / tan((float)RAYS_COUNT / 2);
            texture_x = player_pos_x / 2 + cos(degrees) * projection_angle * 32 / delta_y / rays_angle_fix;
            texture_y = player_pos_y / 2 - sin(degrees) * projection_angle * 32 / delta_y / rays_angle_fix;
            
            // Draws the Floor
            int texture = MAP_FLOOR[(int)(texture_y / 32.0) * MAP_WIDTH + (int)(texture_x / 32.0)] * 32 * 32; // 1024 = 32 * 32
            float color = ALL_TEXTURES[((int)(texture_y) & 31) * 32 + ((int)(texture_y) & 31) + texture] * 0.75;
            glColor3f(color, color, color);
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i(rays * DRAW_LINE_WIDTH_3D + (WINDOW_WIDTH / 2) + LINE_X_OFFSET, _y + LINE_X_OFFSET);
            glEnd();

            // Draws the Ceiling
            texture = MAP_CEILING[(int)(texture_y / 32.0) * MAP_WIDTH + (int)(texture_x / 32.0)] * 32 * 32; // 1024 = 32 * 32
            color = ALL_TEXTURES[((int)(texture_y) & 31) * 32 + ((int)(texture_y) & 31) + texture] * 0.75;
            glColor3f(color, color, color);
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i(rays * DRAW_LINE_WIDTH_3D + (WINDOW_WIDTH / 2) + LINE_X_OFFSET, WINDOW_HEIGHT - _y + LINE_X_OFFSET);
            glEnd();
        }















        rays_angle = fix_angle(rays_angle - 1);
    }
}

// Main Section

void init() {
    glClearColor(RGBA_COLOR_GRAY);
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    player_pos_x = (2 * MAP_CELL_SIZE) - (int)(MAP_CELL_SIZE / 2);
    player_pos_y = (2 * MAP_CELL_SIZE) - (int)(MAP_CELL_SIZE / 2);
    player_angle = FACE_SOUTH;

    player_delta_x = cos(degree_to_radian(player_angle));
    player_delta_y = -sin(degree_to_radian(player_angle));
}

float frame_1, frame_2, frames_per_second;
void display() {
    frame_2 = glutGet(GLUT_ELAPSED_TIME);
    frames_per_second = (frame_2 - frame_1);
    frame_1 = glutGet(GLUT_ELAPSED_TIME);
    update_keys(frames_per_second);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    draw_map_2d();
    draw_player_2d();
    cast_scene();
    glutSwapBuffers();  
}

int main(int argc, char* argv[]) { 
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);
    glutMainLoop();

    return 0;
}
