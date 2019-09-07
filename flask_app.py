from flask import Flask, render_template, request, redirect, url_for
from pyduino import *
import time

app = Flask(__name__)

a = Arduino(serial_port='/dev/ttyS0') 
time.sleep(3)

LED_PIN = 13
ANALOG_PIN = 0

a.set_pin_mode(LED_PIN,'O')

print 'Arduino initialized'

@app.route('/', methods = ['POST','GET'])
def index():

    # LED On/Off/Blink Buttons
    if request.method == 'POST':

        # On Button
        if request.form['submit'] == 'Turn On':
            print 'TURN ON'

            a.digital_write(LED_PIN,1)

        # Off Button
        elif request.form['submit'] == 'Turn Off':
            print 'TURN OFF'

            a.digital_write(LED_PIN,0)

        # Blink Button
        elif request.form['submit'] == 'Blink':
            print 'BLINK'

            for i in range(0,20):
                a.digital_write(LED_PIN,1)

            a.digital_write(LED_PIN,0)

        else:
            pass

    # Reading the analog value from the Arduino's temperature sensor
    readval = a.analog_read(ANALOG_PIN)

    # Conversion from analog reading to Celsius
    temperature = ((5*(readval/1024.))-0.5)*100
    temperature = round(temperature,2)

    return render_template('index.html', value=temperature)

if __name__ == "__main__":

    app.run(host='0.0.0.0') # http://127.0.0.1:5000/
