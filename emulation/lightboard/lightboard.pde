/*
 Digial light board 
 Dynamic Light
 Matthew Loewen
 2/13/2019
 
 
 This code is for a single cell of lights for the Totem project
 
*/


final int COLAMT = 9;
final int ROWAMT = 36;
final int SIZE = 15;

//spaceing of lights
final int SPACEX = SIZE + 10;
final int SPACEY = SIZE + 12;

//loop counter
int k = 0;

Pixel[][] pixel = new Pixel[COLAMT][ROWAMT];

void setup() {

  size(216, 961); //DO NOT USE VARS OR ANY MATH EXPRESSIONS HERE


  background(40);
  stroke(20);

  //make new pixels
  for (int i = 0; i < COLAMT; i++) {
    for (int z = 0; z < ROWAMT; z++) {
      pixel[i][z] = new Pixel(SIZE, i * SPACEX, z * SPACEY );
    }
  }
}

void draw() {

  k++;
  if (k > 254) {
    k = 0;
  }

  //SIMPLE light pettern here
  for (int i = 0; i < COLAMT; i++) {
    for (int z = 0; z < ROWAMT; z++) {
      pixel[i][z].display(k + (i * 4));
    }
  }
  delay(20);
}
