from flask import Flask, request

app = Flask(__name__)

@app.route('/Sensordatatoyou', methods=['POST'])
def receive_data():
    data = request.get_json()
    print("Data mottagen:", data)
    return '', 200

if __name__ == '__main__':
    app.run(port=8080)
