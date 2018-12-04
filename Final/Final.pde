Star[] stars;
Grass[] grass; 

PImage butterfly;

void setup(){
  //size(500, 500, P3D);
  fullScreen(P3D);
  frameRate(30);
  noCursor();
  
  butterfly = loadImage("butterfly.png");
  
  stars = new Star[300];
  for (int i = 0 ; i < stars.length ; ++i){
   stars[i] = new Star((int) random(0,width), (int)random(0,7*height/8), random(0.01,0.05));
  }
  
  grass = new Grass[width];
  for (int i = 0 ; i < grass.length ; ++i) grass[i] = new Grass(40, i, height);
}

void draw(){/*
  pushMatrix();
  scale(0.5);
  image(butterfly, width/2, height/2);
  popMatrix();
  if(true) return;
  */
  
  setGradient();
  for (int i = 0 ; i < stars.length ; ++i) stars[i].display();
  for (int i = 0 ; i < grass.length ; ++i) grass[i].display();
}

void setGradient() {
  noFill();
  background(0);
 
  color c1 = color(0, 32, 90);
  color c2 = color(0);
  
  for (int i = 0 ; i <= height ; ++i) {
    float inter = map(i, 0, height, 0, 1);
    color c = lerpColor(c1, c2, inter);
    stroke(c);
    line(0, i, width, i);
  }
}
