#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
}

int Block::width() const {
  /* your code here */
}

void Block::render(PNG &im, int x) const {
  /* your code here */
}

 /** 
   * Creates a block that is width X img.height pixels in size
   * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
   * in img. Assumes img is large enough to supply these pixels.
   */
void Block::build(PNG &im, int x, int width) {
  int height = im.height;
  
  /* your code here */
}
