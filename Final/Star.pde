class Star{
  
  private int x,y;
  private float s;
  private color clr = color(random(50,255));
  
  private int counterLimit = 100;
  private int counter = (int) random(0, counterLimit);
  
  public Star(int x ,int y ,float s){
    this.x = x;
    this.y = y;
    this.s = s;
  }
  
  
  public void display() {
  
    counter++;
    if(counter == counterLimit){
      counter = 0;
      clr = color(random(100,255));
    }
    
    pushMatrix();
    translate(x, y, 2);
    
    fill(clr);
    
    beginShape();
      vertex(0, -50, 0);
      vertex(14, -20, 0);
      vertex(47, -15, 0);
      vertex(23, 7, 0);
      vertex(29, 40, 0);
      vertex(0, 25, 0);
      vertex(-29, 40, 0);
      vertex(-23, 7, 0);
      vertex(-47, -15, 0);
      vertex(-14, -20, 0);
      scale(s);
    endShape(CLOSE);
    
    popMatrix();
  }
}
