/*
 * Sketch to control the pins of Arduino via serial interface
 *
 * Commands implemented with examples:
 *
 * - RD13 -> Reads the Digital input at pin 13
 * - RA4 - > Reads the Analog input at pin 4
 * - WD13:1 -> Writes 1 (HIGH) to digital output pin 13
 * - WA6:125 -> Writes 125 to analog output pin 6 (PWM)
 */

char operation; // Holds operation (R, W, ...)
char mode; // Holds the mode (D, A)
int pin_number; // Holds the pin number
int digital_value; // Holds the digital value
int analog_value; // Holds the analog value
int value_to_write; // Holds the value that we want to write
int wait_for_transmission = 5; // Delay in ms in order to receive the serial data

void set_pin_mode(int pin_number, char mode){

    switch (mode){
        case 'I':
            pinMode(pin_number, INPUT);
            break;
        case 'O':
            pinMode(pin_number, OUTPUT);
            break;
        case 'P':
            pinMode(pin_number, INPUT_PULLUP);
            break;
    }
}

void digital_read(int pin_number){

    digital_value = digitalRead(pin_number);
    Serial.print('D');
    Serial.print(pin_number);
    Serial.print(':');
    Serial.println(digital_value);
}

void analog_read(int pin_number){

    analog_value = analogRead(pin_number);
    Serial.print('A');
    Serial.print(pin_number);
    Serial.print(':');
    Serial.println(analog_value);
}

void digital_write(int pin_number, int digital_value){
  
  digitalWrite(pin_number, digital_value);
}

void analog_write(int pin_number, int analog_value){

  analogWrite(pin_number, analog_value);
}

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(100); 
}

void loop() {
    if (Serial.available() > 0) {
        operation = Serial.read();
        delay(wait_for_transmission);
        mode = Serial.read();
        pin_number = Serial.parseInt();
        if (Serial.read()==':'){
            value_to_write = Serial.parseInt();
        }
        switch (operation){
            case 'R': // Read operation
                if (mode == 'D'){ // Digital write
                    digital_read(pin_number);
                } else if (mode == 'A'){ // Analog write
                    analog_read(pin_number);
        } else {
          break; // Unexpected mode
        }
                break;

            case 'W': // Write operation
                if (mode == 'D'){ // Digital write
                    digital_write(pin_number, value_to_write);
                } else if (mode == 'A'){ // Analog write
                    analog_write(pin_number, value_to_write);
                } else {
                    break; // Unexpected mode
                }
                break;

            case 'M': // Pin mode
                set_pin_mode(pin_number, mode); // Mode contains I, O or P (INPUT, OUTPUT or PULLUP_INPUT)
                break;

            default: // Unexpected char
                break;
        }
    }
}
