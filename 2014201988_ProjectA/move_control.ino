int left = 0;
int Left_motor_backwards=9;     //左电机后退(IN1)
int Left_motor_forwards=5;     //左电机前进(IN2)

int right = 1;
int Right_motor_forwards=6;    // 右电机前进(IN3)
int Right_motor_backwards=10;    // 右电机后退(IN4)

void setup() {
  pinMode(Left_motor_forwards,OUTPUT); 
  pinMode(Left_motor_backwards,OUTPUT); 
  pinMode(Right_motor_forwards,OUTPUT);
  pinMode(Right_motor_backwards,OUTPUT);
}

void unilateralControl(int side, int back, int go, int velocity, int time) { //单边电机控制：前进/后退/停转
  if (back && go) return;
  
  int backwards, forwards;
  //assert：side输入无误
  side == left ? ( backwards = Left_motor_backwards, forwards = Left_motor_forwards ) :
  ( backwards = Right_motor_backwards, forwards = Right_motor_forwards );
  
  digitalWrite(backwards, back ? HIGH : LOW);    
  digitalWrite(forwards, go ? HIGH : LOW);  
  
  //PWM比例0~255可调速
  analogWrite(backwards, back ? velocity : 0);
  analogWrite(forwards, go ? velocity : 0);
  delay(time);
}

void run(int time) { //小车前进
  // 右电机前进
  unilateralControl(right, 0, 1, 200, 0);
  
  // 左电机前进
  unilateralControl(left, 0, 1, 200, 0);
  delay(time);
}

void brake(int time) { //小车制动
  //右电机停转
  unilateralControl(right, 0, 0, 0, 0);
  
  //左电机停转
  unilateralControl(left, 0, 0, 0, 0);
  delay(time);
}

void turn_left(int time) { //小车左转向
   //右电机前进
  unilateralControl(right, 0, 1, 200, 0);

  //左电机停转
  unilateralControl(left, 0, 0, 0, 0);
  delay(time);
}

void spin_left(int time) { //小车逆时针旋转
  //右电机前进
  unilateralControl(right, 0, 1, 200, 0);

  //左轮后退
  unilateralControl(left, 1, 0, 200, 0);
  delay(time);
}

void turn_right(int time) { //小车右转向
   //右电机停转
  unilateralControl(right, 0, 0, 0, 0);

  //左电机前进
  unilateralControl(left, 0, 1, 200, 0);
  delay(time);
}

void spin_right(int time) { //小车顺时针旋转
  //右电机后退
  unilateralControl(right, 1, 0, 200, 0);

  //左电机前进
  unilateralControl(left, 0, 1, 200, 0);
  delay(time);	//执行时间，可以调整  
}

void go_back(int time) { //小车后退
  //右电机后退
  unilateralControl(right, 1, 0, 150, 0);

  //左电机后退
  unilateralControl(left, 1, 0, 150, 0);
  delay(time);  //执行时间，可以调整  
}

void loop()
{    
  int i;
  delay(1000);
  // 设计动作：
  // 1. 前进一秒
  // 2. 刹车0.5秒
  // 3. 后退一秒
  run(1000);
  brake(500);
  go_back(1000);

  // 4. 原地逆时针转0.5s两次
  for(i=0;i<2;i++) spin_left(500);

  // 5. 原地顺时针转0.5s两次
  for(i=0;i<2;i++) spin_right(500);

  // 6. 左转1s刹车1s两次
  for(i=0;i<2;i++) { turn_left(1000); brake(1000); }
  
  // 6. 右转1s刹车1s两次
  for(i=0;i<2;i++) { turn_right(1000); brake(1000); }
}
