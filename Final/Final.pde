import java.util.ArrayList;

Star[] stars;
Grass[] grass; 
ArrayList<Butterfly> butterflies;
//Butterfly[] butterflies;

//PImage butterfly;

void setup(){
  //size(500, 500, P3D);
  fullScreen(P3D);
  frameRate(30);
  noCursor();
  ellipseMode(CENTER);
  
 // butterfly = loadImage("butterfly.png");
  
  stars = new Star[300];
  for (int i = 0 ; i < stars.length ; ++i){
   stars[i] = new Star((int) random(0,width), (int)random(0,7*height/8), random(0.01,0.05));
  }
  
  grass = new Grass[width];
  for (int i = 0 ; i < grass.length ; ++i) grass[i] = new Grass(40, i, height);
  
  butterflies = new ArrayList<Butterfly>();
  butterflies.add(new Butterfly());
  
  /*butterflies = new Butterfly[5]; 
  for(int i = 0 ; i < butterflies.length ; ++i){
    butterflies[i] = new Butterfly();//(int)random(width),(int)random(3 * height / 4, height - 40));
  }*/
  
}

void draw(){  
  
  setGradient();
  for (int i = 0 ; i < stars.length ; ++i) stars[i].display();
  for (int i = 0 ; i < grass.length ; ++i) grass[i].display();
  for (int i = 0 ; i < butterflies.size() ; ++i) butterflies.get(i).display();
  
  for (int i = 0 ; i < butterflies.size() ; ++i) {
    if (butterflies.get(i).x > width + 10) {
      butterflies.remove(i);
      break;
    }
  }
  
  if (random(1) < 0.005 && butterflies.size() < 10) {
    butterflies.add(new Butterfly());
  }
  
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
