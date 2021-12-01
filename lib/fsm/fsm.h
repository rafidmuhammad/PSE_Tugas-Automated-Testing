#include <define.h>
extern void edgedetector(int *state, int *input, int *output);
extern void debouncing(int *state, int *input, int *output);
extern void running(int *inputR, int *inputL, int *state, int *output);
extern void fsm_init(int *state_edge, int *state_debounce);