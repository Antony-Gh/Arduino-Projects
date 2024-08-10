int bulb = 13; // Define the pin connected to the bulb

// Function to turn the bulb on or off
void turn(bool state)
{
    digitalWrite(bulb, state ? HIGH : LOW); // Use HIGH/LOW instead of 1/0 for clarity
}

void setup()
{
    Serial.begin(9600);    // Start serial communication at 9600 baud rate
    pinMode(bulb, OUTPUT); // Set the bulb pin as an output
}

void loop()
{
    Serial.println("Type 'on' or 'off' to control the relay:");

    // Wait for user input
    while (Serial.available() == 0)
    {
    }

    String value = Serial.readString(); // Read the input string
    value.trim();                       // Remove any leading or trailing whitespace

    if (value.equalsIgnoreCase("on"))
    {
        turn(true); // Turn the bulb on
        Serial.println("Relay turned ON");
    }
    else if (value.equalsIgnoreCase("off"))
    {
        turn(false); // Turn the bulb off
        Serial.println("Relay turned OFF");
    }
    else
    {
        Serial.println("Invalid input. Please type 'on' or 'off'."); // Error message for wrong input
    }

    delay(50); // Short delay to improve performance
}
