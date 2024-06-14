from flask import Flask, request, jsonify
import time
import pandas as pd

# Initialize Flask app
app = Flask('Unique_Flask_App')

# Data storage lists
air_quality_data = []
temp_data = []
humidity_data = []
timestamps = []

@app.route('/', methods=['GET'])
def home():
    # Check if there is data available
    if temp_data:
        data = {
            'timestamp': timestamps,
            'Air Quality': air_quality_data,
            'temperature': temp_data,
            'humidity': humidity_data
        }
        dataframe = pd.DataFrame(data)
        return dataframe.to_html()
    else:
        return 'No Data Received'

@app.route('/data', methods=['POST'])
def receive_data():
    # Check if the request contains JSON data
    if request.is_json:
        received_data = request.json
        air_quality = received_data.get('Air Quality')
        temperature = received_data.get('temperature')
        humidity = received_data.get('humidity')
    else:
        air_quality = request.form.get('Air Quality')
        temperature = request.form.get('temperature')
        humidity = request.form.get('humidity')

    # Append received data to respective lists
    current_time = time.time()
    air_quality_data.append(air_quality)
    temp_data.append(temperature)
    humidity_data.append(humidity)
    timestamps.append(current_time)

    # Return JSON response with the received data
    return jsonify({
        'temperature': temperature,
        'Air Quality': air_quality,
        'humidity': humidity,
        'timestamp': current_time
    })

if __name__ == '__main__':
    # Run the Flask app
    app.run(host='0.0.0.0')
