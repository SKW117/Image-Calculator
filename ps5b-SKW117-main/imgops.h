#include "common.h"
#include <stdlib.h>
#include <math.h>

void reflect(struct image* image);
void grayscale(struct image* image);
void greenscreen(struct image* image, struct image* background);
struct image* make_blue_gradient(int width, int height);