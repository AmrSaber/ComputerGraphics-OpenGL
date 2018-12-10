//import processing.sound.*;

Star[] stars;
Grass[] grass; 
Fly[] flies;
ArrayList<Butterfly> butterflies;
ArrayList<Meteor> meteors;

boolean isLooping = true;
//SoundFile soundFile;

void setup(){
  fullScreen(P3D);
  frameRate(30);
  noCursor();
  
  //soundFile = new SoundFile(this, "night_sound.mp3");
  //soundFile.loop();
    
  stars = new Star[300];
  for (int i = 0 ; i < stars.length ; ++i){
   stars[i] = new Star((int) random(0,width), (int)random(0,7*height/8), random(0.01,0.05));
  }
  
  grass = new Grass[width];
  for (int i = 0 ; i < grass.length ; ++i) grass[i] = new Grass(random(35, 45), i, height);
  
  flies = new Fly[20];
  for (int i = 0 ; i < flies.length ; ++i) flies[i] = new Fly(7 * height / 8);
  
  butterflies = new ArrayList<Butterfly>();
  
  meteors = new ArrayList<Meteor>();
}

void draw(){
   
  setGradient();
  for (int i = 0 ; i < stars.length ; ++i) stars[i].display();
  for (int i = 0 ; i < grass.length ; ++i) grass[i].display();  
  for (int i = 0 ; i < flies.length ; ++i) flies[i].display();
  for (int i = 0 ; i < butterflies.size() ; ++i) butterflies.get(i).display();
  for (int i = 0 ; i < meteors.size() ; ++i) meteors.get(i).display();
  
  handleButterflies();
  handleMeteors();
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
    strokeWeight(1);
    line(0, i, width, i);
  }
}

void handleButterflies(){
  for (int i = 0 ; i < butterflies.size() ; ++i) {
    if (butterflies.get(i).x > width + 10) {
      butterflies.remove(i);
      --i;
    }
  }
  
  if (butterflies.size() < 1 || (random(1) < 0.005 && butterflies.size() < 10)) {
    butterflies.add(new Butterfly());
  }
}

void handleMeteors(){
  for (int i = 0 ; i < meteors.size() ; ++i) {
    if (meteors.get(i).isGone) {
      meteors.remove(i);
      --i;
    }
  }
  
  if (random(1) < 0.0025 && meteors.size() < 5) {
    meteors.add(new Meteor());
  }
}

void keyPressed(){
  if (key != ' ') return;
  if (isLooping) noLoop();
  else loop();
  isLooping = !isLooping;
}
