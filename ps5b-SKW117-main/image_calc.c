#include "imgops.h"
#include "loader.h"
#include <stdlib.h>
#include <string.h>


int main(int argv, char** argc){

    // TODO: assign the below variables correctly.
    char* input_filepath = argc[1];
    char* output_filepath = argc[5];

    // TODO: parse the arguments in argc. 
    // You can expect argc[1] to be the input filepath
    // You can expect argc[2] to be the integer width
    // You can expect argc[3] to be the integer height
    // You can expect argc[4] to be the operation, either "reflect", "grayscale", or "greenscreen"
    // You can expect argc[5] to be the output filepath.
    

    if(argv != 6) {
        printf("Incorrect number of arguments. Expected: ./build/image_calc <input_image> <width> <height> <img operation=reflect,grayscale,greenscreen> <output_image_path>\n");
        return -1;
    }

    // TODO: allocate the space needed for one image.
    int width = atoi(argc[2]);
    int height = atoi(argc[3]);

    struct image* image = malloc(sizeof(struct image));                        // designates memory the size of image struct in the stack.
    if (!image){
      printf("Memory allocation failed\n");
      return -1;
    }

    image-> width = width;
    image-> height = height;
    image-> pixels = malloc(width * height * 12);                             // designates memory for width, and height in the stack.
    if(!image-> pixels){
      printf("Memory allocation failed\n");                                   // to know if there was a problem in desegnating the memory for pixels.
      return -1;
    }

    // call load image
    int err = loadimage(input_filepath, image);

    if(err == -1) {
        printf("ERROR loading image. Is your filepath correct?\n");
        return -1;
    }


    // TODO: check operation based on input string
    if(strcmp(argc[4], "grayscale") == 0){
      grayscale(image);
    } else if(strcmp(argc[4], "reflect") == 0){
      reflect(image);
    } else if(strcmp(argc[4], "greenscreen") == 0){
      struct image* background = make_blue_gradient(width, height);
      greenscreen(image, background);
    } else {
      printf("Error: operation not found\n");
      return -1;
    }
      
    
    // save result to file
    saveimage(output_filepath, image);

    // TODO: add any clean-up nessecary.
    free(image-> pixels);                                                     // cleans memory designated for pixels area.
    free(image);                                                              // cleans memory designated for image struct.
    return 0;
}
