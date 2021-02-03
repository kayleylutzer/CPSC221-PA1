#include "block.h"
#include <cmath>
#include <iostream>
#include <vector>

int Block::height() const {
  if (data.size()== NULL) return 0;
  return data.size();
  
}

int Block::width() const {
  if (data.size()== NULL) return 0;
  return data[0].size();
}

void Block::render(PNG &im, int x) const {
  unsigned int w = width();
  for(unsigned int row = 0; row < height();row++ ){
    for(unsigned int column = x; column < w; column++){
     *im.getPixel(row,column) = data[row][column - x];
    }
  }
}

 /** 
   * Creates a block that is width X img.height pixels in size
   * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
   * in img. Assumes img is large enough to supply these pixels.
   */
void Block::build(PNG &im, int x, int width) {
  int height = im.height();
  vector<HSLAPixel> row;
  for (int j = 0; j < height; j++){
    row.clear();
    for (int i = x; i < x + width ; i++){
      HSLAPixel *pixel = im.getPixel(i,j);
      row.push_back(*pixel);
    }
    data.push_back(row);
  } 
}
