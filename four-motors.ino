// Button Pins
const int button_right = 2;
const int button_up = 3;
const int button_left = 4;
const int button_down = 5;

// Motor Driver Pins
const int IN1 = 11;
const int IN2 = 10;
const int IN3 = 9;
const int IN4 = 8;

// Sensor Pins
const int sonic = A2;
const int temp_pin = A1;

// Temperature and Distance Variables
long baselineTemp = 0;
long celsius = 0;
long fahrenheit = 0;
long distance_cm = 0;
long distance_in = 0;

void setup()
{
    Serial.begin(9600);

    // Initialize button pins as inputs
    pinMode(button_right, INPUT);
    pinMode(button_up, INPUT);
    pinMode(button_left, INPUT);
    pinMode(button_down, INPUT);

    // Initialize motor control pins as outputs
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Initialize sensor pins
    pinMode(sonic, INPUT);
    pinMode(temp_pin, INPUT);
}

void loop()
{
    // Read sensor data
    readTemperature();
    readUltrasonic();

    // Read button states
    int go_forward = digitalRead(button_up);
    int go_backward = digitalRead(button_down);
    int go_left = digitalRead(button_left);
    int go_right = digitalRead(button_right);

    // Control motors based on button inputs
    controlMotors(go_forward, go_backward, go_left, go_right);

    delay(25); // Small delay for stability
}

// Function to read and display temperature from TMP36 sensor
void readTemperature()
{
    celsius = map(((analogRead(temp_pin) - 20) * 3.04), 0, 1023, -40, 125);
    fahrenheit = ((celsius * 9) / 5 + 32);
    Serial.print(celsius);
    Serial.print(" C, ");
    Serial.print(fahrenheit);
    Serial.println(" F");
}

// Function to read and display distance from Ultrasonic sensor
void readUltrasonic()
{
    pinMode(sonic, OUTPUT);
    digitalWrite(sonic, LOW);
    delayMicroseconds(2);
    digitalWrite(sonic, HIGH);
    delayMicroseconds(5);
    digitalWrite(sonic, LOW);
    pinMode(sonic, INPUT);
    long duration = pulseIn(sonic, HIGH);
    distance_cm = (duration / 29.0) / 2.0;
    distance_in = distance_cm * 0.393701;
    Serial.print(distance_cm);
    Serial.println(" cm");
}

// Function to control motors based on button inputs
void controlMotors(int forward, int backward, int left, int right)
{
    if (forward == HIGH)
    {
        // Move forward
        digitalWrite(IN2, HIGH);
        digitalWrite(IN1, LOW);
    }
    else if (backward == HIGH)
    {
        // Move backward
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, HIGH);
    }
    else
    {
        // Stop forward/backward movement
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, LOW);
    }

    if (left == HIGH)
    {
        // Move left
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }
    else if (right == HIGH)
    {
        // Move right
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    else
    {
        // Stop left/right movement
        digitalWrite(IN4, LOW);
        digitalWrite(IN3, LOW);
    }
}
