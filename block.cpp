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
  //cout << width() << endl;
  //cout <<x << endl;
  //cout << height()<< endl;
  im.resize(width() + x, height() );
  unsigned int w = width();
  for(unsigned int row = 0; row < height(); row++) {
    for(unsigned int column = x; column < w + x; column++){
<<<<<<< HEAD
     *im.getPixel(column,row) = data[column - x][row];
=======
     *im.getPixel(row,column) = data[column - x][row];
>>>>>>> 99a9d7eda48aa6c461ab9ee5e37c06a95305000d
    }
  }
}

 /** 
   * Creates a block that is width X img.height pixels in size
   * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
   * in img. Assumes img is large enough to supply these pixels.
   */
void Block::build(PNG &im, int x, int width) {
  // int bound = width + x;
  // int h = im.height();

  // for(int j = 0; j < h; j++){
  //   data[h-j].resize(width);
  //   for(int i = x; i < bound; i++){
  //     data[h-j][i-x] = *im.getPixel(i,j);
  //   }
  // }
  
  //data.resize(im.height());

  vector<HSLAPixel> row;
  int h = im.height();
  for (int j = 0; j < h; j++){
    row.clear();
    for (int i = x; i < x + width ; i++){
      HSLAPixel *pixel = im.getPixel(i,j);
      row.push_back(*pixel);
    }
    data.push_back(row);
  } 
}
