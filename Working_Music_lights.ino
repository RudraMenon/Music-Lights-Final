 qint x = A5;
int sound;
int counter = 0;
int max = 0;
double MAX_MULTIPLIER = 0.6;
int prev = 0;
int RGB[] = {0,0,0};


void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
  float fC = fV * fS; // Chroma
  float fHPrime = fmod(fH / 60.0, 6);
  float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  float fM = fV - fC;
  
  if(0 <= fHPrime && fHPrime < 1) {
    fR = fC;
    fG = fX;
    fB = 0;
  } else if(1 <= fHPrime && fHPrime < 2) {
    fR = fX;
    fG = fC;
    fB = 0;
  } else if(2 <= fHPrime && fHPrime < 3) {
    fR = 0;
    fG = fC;
    fB = fX;
  } else if(3 <= fHPrime && fHPrime < 4) {
    fR = 0;
    fG = fX;
    fB = fC;
  } else if(4 <= fHPrime && fHPrime < 5) {
    fR = fX;
    fG = 0;
    fB = fC;
  } else if(5 <= fHPrime && fHPrime < 6) {
    fR = fC;
    fG = 0;
    fB = fX;
  } else {
    fR = 0;
    fG = 0;
    fB = 0;
  }
  
  fR += fM;
  fG += fM;
  fB += fM;
  int brightness = 70;
  fR *= brightness;
  fG *= brightness;
  fB *= brightness;
}
void setup() {
  Serial.begin(9600);
}
void update_sound(int s){
  int diff;
  Serial.print("heyo");
  for (int i= 0; i < 3; i++){
    diff = RGB[i] - s;
    Serial.println(diff);
    if (diff > 50){
      RGB[i] = RGB[i] - 25;
    }else if (diff < -50){
      RGB[i] = RGB[i] + 25;
    }else{
      RGB[i] = s;
    }
  }

 
  analogWrite(3, RGB[0]);
  analogWrite(5, RGB[1]);
  analogWrite(6, RGB[2]);
  return;
}

void pretty_colors(float h, float s, float v){
  float r = 0,g = 0, b = 0;
  HSVtoRGB(r,g,b,h,s,v);
  Serial.println(r);
  analogWrite(3,r);
  analogWrite(5,g);
  analogWrite(6,b);
  delay(60);
  if (analogRead(x) == 0){
    h  = h + 1;
    if (h>359){h = 0;}
    pretty_colors(h,s,v);    
  }
}
void loop() {
  sound = analogRead(x);
  Serial.print(counter);
  if (sound == 0){
    counter = counter + 1;
  }else{
    counter = 0;
  }
  if(counter > 10000){
    pretty_colors(0,1,1);
  }
  if (sound > max){
    max = sound;
  }else{
    max = max - 0.05;
  }
  if (counter > 3 || (sound != 0 && sound > (max*MAX_MULTIPLIER))){ 
    if (sound < prev || sound > (prev*1.5)){
      update_sound(sound);
    }else{
      update_sound(0);
    }
    prev = sound;
  }
  //analogWrite(3,x);
  delay(10);
}
