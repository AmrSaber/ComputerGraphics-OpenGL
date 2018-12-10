class Grass{
  
  private int xTrans, yTrans;
  private float  gHeight;
  private final int segments = 8;
  
  private float angle = 0;
  private float t = random(10);
  
  private color grassColor;
  
  public Grass(float height_, int xTrans_, int yTrans_){
    this.gHeight = height_;
    this.xTrans = xTrans_;
    this.yTrans = yTrans_;
    
    //this.grassColor = color(0, random(16), random(64, 192));
    this.grassColor = color(0, random(16, 40), random(32));
  }
  
  public void display() {
    
    pushMatrix();
    translate(xTrans, yTrans, 5);
    
    stroke(grassColor);
    strokeWeight(1);
    
    angle = radians(map(noise(t), 0, 1, -6, 6)); 
    t += 0.01;
    
    float segLength = gHeight / segments;
    for (int i = 0 ; i < segments ; ++i){
      line(0, 0, 0, 0, -segLength, 0);
      translate(0, -segLength, 0);
      rotateZ(angle);
    }
    
    popMatrix();
  }
}
