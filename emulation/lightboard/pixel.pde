class Pixel {
  int size; 
  int xPos, yPos;
  
  Pixel(int size, int xPos, int yPos){
    this.size = size;
    this.xPos = xPos;
    this.yPos = yPos;
  }
  
   void display(float brightNess){
    fill((int)brightNess);
    rect(xPos, yPos, size, size); 
   }
}
