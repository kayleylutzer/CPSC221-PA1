/**
 * @file main.cpp
 * Split an image into k vertical strips (blocks), 
 * rearrange the blocks into a random order,
 * write the concatenation of the blocks into a new image,
 * unscramble the new image back into the original.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include <iostream>
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;

int main() {
  /**
   * Use your own images and other tests to test your code!
   * Some tests you should write:
   * 1) building and rendering blocks
   * 2) copying a chain
   * 3) assigning one chain to another
   * 4) swapping Nodes in a chain
   * 5) unscrambling an image
   * NOTE: Your code should not be able to correctly unscramble
   * kh.png.  Why not?
   */
  PNG im;
  PNG im2;
  PNG im3;
  PNG im4;
  im4.readFromFile("images/kh.png");
  im3.readFromFile("images/terrain.png");
  im2.readFromFile("images/ronMueck.png");
  im.readFromFile("images/sun.png");

<<<<<<< HEAD
  cout << "pre width: " << im4.width() << endl;
  cout << "pre height: " << im4.height() << endl;

  //testing building and rendering images
  Block a;
  a.build(im4, 100, 300);
  cout << "post width: " << a.width() << endl;
  cout << "post block height: " << a.height() << endl;
  a.render(im2, 0);
  im2.writeToFile("images/test.png");
  cout << "post width: " << a.width() << endl;
  cout << "post block height: " << a.height() << endl;
 
  Chain c(im, 5);
  // randomly scramble the blocks.
  c.scramble();
  // or test swapping a few blocks
  // c.testSwap(3,4); // swap the 3rd and 4th blocks.
  // c.testSwap(0,1);
  // c.testSwap(1,0);
  // c.testSwap(0,4);

  c.render().writeToFile("images/scram.png");  // look at scram.png to debug

  // test unscramble()
  c.unscramble();
  c.render().writeToFile("images/unscram.png");// look at unscram.png also

  /* Check that unscramble works to unscramble a *saved* image too.
  PNG om;
  om.readFromFile("images/scram.png");
  Chain d(om, 5);
  d.unscramble();
  d.render().writeToFile("images/unscram.png");
  */
  return 0;
}
