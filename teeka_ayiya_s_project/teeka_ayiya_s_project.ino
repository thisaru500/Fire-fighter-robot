#define enA 10//Enable1 L298 Pin enA

#define in1 9 //Motor1 L298 Pin in1

#define in2 8 //Motor1 L298 Pin in2

#define in3 7 //Motor2 L298 Pin in3

#define in4 6 //Motor2 L298 Pin in4

#define enB 5 //Enable2 L298 Pin enB

#define ir_R A0 //this sensor for getting distance for fire A0 A1 A2

#define ir_F A1

#define ir_L A2

#define servo A4 //TO getting servo motor values

#define pump A5 

int Speed = 160; // Write The Duty Cycle 0 to 255 Enable for Motor Speed
int s1, s2, s3;
void setup(){ // put your setup code here, to run once
Serial.begin(9600); // start serial communication at 9600bps
pinMode(ir_R, INPUT);// declare fire sensor pin as input
pinMode(ir_F, INPUT);// declare fire sensor pin as input
pinMode(ir_L, INPUT);// declare fire sensor pin as input
pinMode(enA, OUTPUT); // declare as output for L298 Pin enA
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB
pinMode(servo, OUTPUT);
pinMode(pump, OUTPUT);
for (int angle = 90; angle <= 140; angle += 5) {
servoPulse(servo, angle); }
