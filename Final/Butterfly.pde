class Butterfly{
  private float x ,y0, y;
  private float dx = random(1, 2);
  
  private float freq = random(width/20, width/50);
  private float amp = random(10, 13); 
  
  private color col = color(random(256), random(256), random(256), 128);
  
  private float angle = PI/3;
  private float da = radians(20);
  
  public Butterfly(){
    x = -5;
    y0 = y = random(3*height/4, height - 40);
  }
  
  public void display(){
    
    update();
    
    pushMatrix();
    translate(x, y, 5);
    rotateZ(PI/4);
    rotateY(-PI/2);
    scale(2);
    
    stroke(255);
    strokeWeight(0.5);
    fill(col);
    
    // left part
    pushMatrix();
    rotateY(angle);
    
    rotateZ(radians(45));
    ellipse(0,2,3,5);
    
    rotateZ(radians(-90));
    ellipse(0,-2.5,4,6);
    
    popMatrix();
    
    // right part
    pushMatrix();
    rotateY(-angle);
    
    rotateZ(radians(45));
    ellipse(0,-2.5,4,6);
    
    rotateZ(radians(-90));
    ellipse(0,2,3,5);
    
    popMatrix();
    
    popMatrix();
  }
  
  private void update(){
    angle += da;
    if (angle > PI/3 || angle < PI/6) da *= -1;
    
    x += dx;
    y = this.y0 + amp * sin(2*PI*x/freq);
  }

}
