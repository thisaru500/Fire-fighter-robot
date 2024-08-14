#define enA 10 // Enable1 L298 Pin enA
#define in1 9 // Motor1 L298 Pin in1
#define in2 8 // Motor1 L298 Pin in2
#define in3 7 // Motor2 L298 Pin in3
#define in4 6 // Motor2 L298 Pin in4
#define enB 5 // Enable2 L298 Pin enB
#define ir_R A0 // Sensor for distance detection, A0 A1 A2
#define ir_F A1
#define ir_L A2
#define servo A4 // Servo motor control
#define pump A5 

int Speed = 160; // Duty Cycle 0 to 255 for Motor Speed
int s1, s2, s3;

void setup() { 
    Serial.begin(9600); // Start serial communication at 9600bps
    pinMode(ir_R, INPUT); // Declare fire sensor pin as input
    pinMode(ir_F, INPUT); // Declare fire sensor pin as input
    pinMode(ir_L, INPUT); // Declare fire sensor pin as input
    pinMode(enA, OUTPUT); // Declare as output for L298 Pin enA
    pinMode(in1, OUTPUT); // Declare as output for L298 Pin in1
    pinMode(in2, OUTPUT); // Declare as output for L298 Pin in2
    pinMode(in3, OUTPUT); // Declare as output for L298 Pin in3
    pinMode(in4, OUTPUT); // Declare as output for L298 Pin in4
    pinMode(enB, OUTPUT); // Declare as output for L298 Pin enB
    pinMode(servo, OUTPUT);
    pinMode(pump, OUTPUT);

    for (int angle = 90; angle <= 140; angle += 5) {
        servoPulse(servo, angle); 
    }

    for (int angle = 140; angle >= 40; angle -= 5) {
        servoPulse(servo, angle);
    }

    for (int angle = 40; angle <= 95; angle += 5) {
        servoPulse(servo, angle);
    }

    analogWrite(enA, Speed); // Set motor1 speed
    analogWrite(enB, Speed); // Set motor2 speed
    delay(500);
}

void loop() {
    s1 = analogRead(ir_R);
    s2 = analogRead(ir_F);
    s3 = analogRead(ir_L);

    //=============================================================
    // Auto Control
    //=============================================================
    Serial.print(s1);
    Serial.print("\t");
    Serial.print(s2);
    Serial.print("\t");
    Serial.println(s3);
    delay(50);

    if(s1 < 250) {
        Stop();
        digitalWrite(pump, 1);
        for(int angle = 90; angle >= 40; angle -= 3) {
            servoPulse(servo, angle);
        }
        for(int angle = 40; angle <= 90; angle += 3) {
            servoPulse(servo, angle);
        }
    } else if(s2 < 350) {
        Stop();
        digitalWrite(pump, 1);
        for(int angle = 90; angle <= 140; angle += 3) {
            servoPulse(servo, angle);
        }
        for(int angle = 140; angle >= 40; angle -= 3) {
            servoPulse(servo, angle);
        }
        for(int angle = 40; angle <= 90; angle += 3) {
            servoPulse(servo, angle);
        }
    } else if(s3 < 250) {
        Stop();
        digitalWrite(pump, 1);
        for(int angle = 90; angle <= 140; angle += 3) {
            servoPulse(servo, angle);
        }
        for(int angle = 140; angle >= 90; angle -= 3) {
            servoPulse(servo, angle);
        }
    } else if(s1 >= 251 && s1 <= 700) {
        digitalWrite(pump, 0);
        backword();
        delay(100);
        turnRight();
        delay(200);
    } else if(s2 >= 251 && s2 <= 800) {
        digitalWrite(pump, 0);
        forword();
    } else if(s3 >= 251 && s3 <= 700) {
        digitalWrite(pump, 0);
        backword();
        delay(100);
        turnRight();
        delay(200);
    } else if(s2 >= 251 && s2 <= 800) {
        digitalWrite(pump, 0);
        forword();
    } else if(s3 >= 251 && s3 <= 700) {
        digitalWrite(pump, 0);
        backword();
        delay(100);
        turnLeft();
        delay(200);
    } else {
        digitalWrite(pump, 0);
        Stop();
    }
    delay(10);
}

void servoPulse(int pin, int angle) {
    int pwm = (angle * 11) + 500; // Convert angle to microseconds
    digitalWrite(pin, HIGH);
    delayMicroseconds(pwm);
    digitalWrite(pin, LOW);
    delay(50);
}

// Movement functions of the robot

void forword() { // Move forward
    digitalWrite(in1, HIGH); // Right Motor forward
    digitalWrite(in2, LOW); // Right Motor backward
    digitalWrite(in3, LOW); // Left Motor backward
    digitalWrite(in4, HIGH); // Left Motor forward
}

void backword() { // Move backward
    digitalWrite(in1, LOW); // Right Motor forward
    digitalWrite(in2, HIGH); // Right Motor backward
    digitalWrite(in3, HIGH); // Left Motor backward
    digitalWrite(in4, LOW); // Left Motor forward
}

void turnRight() { // Turn right
    digitalWrite(in1, LOW); // Right Motor forward
    digitalWrite(in2, HIGH); // Right Motor backward
    digitalWrite(in3, LOW); // Left Motor backward
    digitalWrite(in4, HIGH); // Left Motor forward
}

void turnLeft() { // Turn left
    digitalWrite(in1, HIGH); // Right Motor forward
    digitalWrite(in2, LOW); // Right Motor backward
    digitalWrite(in3, HIGH); // Left Motor backward
    digitalWrite(in4, LOW); // Left Motor forward
}

void Stop() { // Stop
    digitalWrite(in1, LOW); // Right Motor forward
    digitalWrite(in2, LOW); // Right Motor backward
    digitalWrite(in3, LOW); // Left Motor backward
    digitalWrite(in4, LOW); // Left Motor forward
}
