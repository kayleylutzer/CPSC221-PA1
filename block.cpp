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
  //int w = width();
  for(int row = 0; row < height(); row++) {
    for(int column = x; column < width() + x; column++){
     *im.getPixel(row,column) = data[row][column-x];
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

  int h = im.height();
  cout << h << endl;
  data.resize(h);
  for (int j = 0; j < h ; j++){
    data[j].resize(width);
    //vector<HSLAPixel> column;
    for (int i = x; i < x + width ; i++){
      data[j][i-x] = *im.getPixel(j,i);
    }
  } 
}
