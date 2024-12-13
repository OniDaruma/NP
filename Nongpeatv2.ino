#define trigPin D0  //initialize pin9 for HC-SR04 trigger pin
#define echoPin D1 //initialize pin9 for HC-SR04 Echo pin
int speak = D4; // เสียบขาที่ 7
int sensor = D2; //ประกาศขาใช้อ่านค่า sensor
int led1 = D5 ; //ขาที่เชื่อมต่อกับ led
int led2 = D6 ; //ขาที่เชื่อมต่อกับ led
#include <Servo.h>
Servo myservo;
long duration;
int distance;


void setup () 
{  
  Serial.begin(115200); //ประกาศใช้งาน serial monitor
  pinMode(sensor,INPUT); //ให้ sensor เป็น input
  pinMode(led1,OUTPUT); //ให้ led เป็น output
  pinMode(led2,OUTPUT); //ให้ led เป็น output
 
  myservo.attach (D3);
  pinMode (speak, OUTPUT);
  pinMode (trigPin, OUTPUT);// Define trigger pin as output
  pinMode (echoPin, INPUT);// Define echo pin as input  
}

void loop () 
{  
  int val = digitalRead(sensor); //ประกาศตัวแปร val เพื่อเก็บค่าที่อ่านได้จาก sensor
  Serial.println(val); //serial monitor แสดงค่า val
  Serial.print(distance);
  Serial.println(" cm ");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Calculate distance in CM   
  
  if (val == 0)
    { 
      digitalWrite(led1, LOW); 
      digitalWrite(led2, HIGH);
      Serial.println("ขยะเต็มแล้ว");  
    }
  if (val == 1)  
    {      
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      Serial.println("ขยะยังไม่เต็ม");       
    }   
  if (distance <= 20)
    {
      delay(100);
      myservo.write(0);
      Serial.println("Open");
      digitalWrite (speak, HIGH);
      delay(10000);
      digitalWrite (speak, LOW);   
    }
  if (distance >= 20)
    {               
      delay(100);
      Serial.println("Close");        
      myservo.write(180);  
    }
}

