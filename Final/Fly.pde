class Fly{
  private float x, y;
  private final float yMin, yMax = height - 25;
  
  private float dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
  private float dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
  private int direction = (int) random(dx.length);
  
  private final int counterLimit = 75;
  private int counter = (int) random(counterLimit);
  
  private float speed = random(0.5, 1);
  private float size = 2;
  
  public Fly(float _yMin){
    this.yMin = _yMin;
    this.x = random(width);
    this.y = random(yMin, yMax);
  }
  
  public void display(){
    pushMatrix();
    translate(x, y, 6);
    
    noStroke();
    fill(color(255, 215, 0));
    ellipse(0, 0, size, size);
    
    popMatrix();
    
    update();
  }
  
  private void update(){
    
    ++counter;
    if (counter == counterLimit || (x <= 0 || x >= width) || (y <= yMin || y >= yMax)) {
      counter = 0;
      direction = (int) random(dx.length);
    }
    
    this.x += dx[direction] * speed;
    this.y += dy[direction] * speed;
    
    x = constrain(x, 0, width);
    y = constrain(y, yMin, yMax);
  }
}
