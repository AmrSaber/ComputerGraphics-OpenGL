class Meteor{

  private float s = 0.25 ; 
  private int counter= 1;
  private int counterLimit = (int) random(200, 400);
  
  private int len = (int) random(50,100);
  private float [] x = new float [len];
  private float [] y = new float [len];
  
  public boolean isGone = false;
  private boolean fading = false;
  private float ratio = 1;
  
  private PVector position, velocity;
  
   Meteor(){
     
     position = new PVector();
     velocity = new PVector(3, 3);
     counterLimit = (int) (random(200, 400) / velocity.mag());
     
     x[0] = (int) random(-20 / s, width / s);
     y[0] = (int) random(-30 / s, 0);
     for(int i = 1 ; i < x.length ; ++i) {
       x[i] = x[i-1] - 2;
       y[i] = y[i-1] - 2;
     }
   }

  public void display(){
    if (isGone) return;
    
    pushMatrix();
    
    translate(position.x, position.y, 2);
    scale(s);
    stroke(255);
    fill(255);
    
    //ellipse(x[0], y[0], 7, 7);
    for(int i = 0 ; i < x.length ; ++i){
      float size = x.length - i;
      size /= 8 * ratio;
      ellipse(x[i] , y[i] , size , size);
    }

    popMatrix();
    
    update();
  }
  
  private void update(){
    if(counter == counterLimit) fading = true;
    else counter++;
    
    if (fading) ratio += 0.1 * velocity.mag();
    if (ratio >= 10) isGone = true;
    
    position.add(velocity);
    
  }
}
