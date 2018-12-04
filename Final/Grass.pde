class Grass{
  
  private int gHeight, xTrans, yTrans;
  private final int segments = 8;
  
  private final int counterMax = 60;
  private int counter = (int)random(0, counterMax);
  
  private float angle = 0, da = radians(random(-0.05, 0.05));
  
  private color grassColor;
  
  public Grass(int height_, int xTrans_, int yTrans_){
    this.gHeight = height_;
    this.xTrans = xTrans_;
    this.yTrans = yTrans_;
    
    //this.grassColor = color(0, random(16), random(64, 192));
    this.grassColor = color(0, random(16, 40), random(32));
  }
  
  private void randomizeChange() {
    float newDa = radians(random(0.01, 0.05));
    if (da < 0) da = newDa;
    else da = -newDa;
  }
  
  public void display() {
    
    counter = (counter + 1) % counterMax;
    if(counter == 0) randomizeChange();
    
    pushMatrix();
    translate(xTrans, yTrans, 5);
    
    stroke(grassColor);
    strokeWeight(1);
    
    angle += da;
    
    int segLength = gHeight / segments;
    for (int i = 0 ; i < segments ; ++i){
      line(0, 0, 0, 0, -segLength, 0);
      translate(0, -segLength, 0);
      rotateZ(angle);
    }
    
    popMatrix();
  }
}
