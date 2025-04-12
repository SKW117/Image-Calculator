#include "imgops.h"

_Bool close_to_green(struct pixel* p) {
    if( sqrt(pow(p->g - 255.0,2) + pow((double) p->r,2) + pow((double) p->b,2)) < 100) {
        return 1;
    }
    return 0;
}





void grayscale(struct image* image){
  int width = image-> width;
  int height = image-> height;
  for (int i = 0; i < width * height; i++){
    int sum = (image-> pixels[i].r + image-> pixels[i].g + image-> pixels[i].b);
    int avg = sum / 3;                                                            // calculates the average of the three values.
    image-> pixels[i].r = avg;                                                    // makes red equal to the average.
    image-> pixels[i].g = avg;                                                    // makes green equal to the average.
    image-> pixels[i].b = avg;                                                    // makes blue equal to the average.
  }

}

void reflect (struct image* image){
  int width = image-> width;
  int height = image-> height;
  
  for(int i = 0; i < height/2; i++){                                              // loops till half the page and flips all rows across the middle
    for( int j = 0; j < width; j++){
      struct pixel temp = image-> pixels[i * width + j];
      image-> pixels[i * width + j] = image-> pixels[(height - i - 1) * width + j];
      image-> pixels [(height - i - 1) * width + j] = temp;                       // reassigns to the value of temp.
    }
  }
}

struct image* make_blue_gradient(int width, int height){
  struct image* image = malloc(sizeof(struct image));                             // designates memory to store the data in the stack.

  image-> width = width;
  image-> height = height;

  image-> pixels = malloc(width * height * 12);                                   // designates memory to store data about every pixel.

  int count = 0;
  for(int i = 0; i < width * height; i++){
    if(count == 256){                                                             // in case the gradient reaches its max of 256.
      count = 0;
    }
    image-> pixels[i].r = 255;
    image-> pixels[i].g = 255;
    image-> pixels[i].b = count;
    count++;
  }
  return image;
}


void greenscreen(struct image* image, struct image* background){
  int width = image-> width;
  int height = image-> height;

  for(int i = 0; i < width * height; i++){
    if(close_to_green(&image-> pixels[i])){
      image-> pixels[i].r = background-> pixels[i].r;
      image-> pixels[i].g = background-> pixels[i].g;
      image-> pixels[i].b = background-> pixels[i].b;
    }
  }
}
