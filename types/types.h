#ifndef SPECZANIE_TYPES_H
#define SPECZANIE_TYPES_H

#include <raylib.h>
#include <stdint.h>

#define MOVE_CHANGE_ZOOM 1
#define MOVE_CHANGE_PAN 2
#define MOVE_CHANGE_PLOT 4
#define MOVE_CHANGE_APPLY_OFFSET 8
#define MOVE_CHANGE_POLYNOMIAL 16
#define MOVE_CHANGE_BENCHMARK 32
typedef unsigned char move_change_t;

enum MovementLock {
    MOVEMENT_LOCK_NONE,
    MOVEMENT_LOCK_X,
    MOVEMENT_LOCK_Y,
};

typedef struct {
    Vector2 mouse_position;
    Vector2 pan;
    float zoom;
    float scale_x;

} ViewMove;

typedef struct {
    Vector2 plot_offset;
    enum MovementLock movement_lock;

} PlotMove;


enum PlotInputMode {
    PLOT_INPUT_IDLE,
    PLOT_INPUT_MOVE,
    PLOT_INPUT_SELECT,
    PLOT_INPUT_REGRESSION,
};

typedef struct {
    Vector2 end_point;
    int end_point_index;
    float a;
    float b;
} CurveLinear;

typedef struct {
    Vector2* point_buffer;
    float* coefficients;
    char* equation;
    float normal_offset_x;
    float start_x;
    float end_x;
    uint8_t order;
} CurvePolynomial;

typedef struct {
    float start_x;
    float end_x;
    float start_y;
    float end_y;
} Bounds;

typedef struct {
    int count;
    int start;
} VisibleWindow;

typedef struct {
    Vector2* buffer;
    VisibleWindow visible;
} PointCache;

#endif //SPECZANIE_TYPES_H