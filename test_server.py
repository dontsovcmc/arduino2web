__author__ = 'dontsov'

from flask import Flask
from flask import request
from flask import jsonify
from logger import log
import argparse

app = Flask(__name__)

@app.route('/data', methods=['GET'])
def data():
    if 'data' in request.args:
        log.info('SERVER: data=%s' % request.args['data'])
        return 'data received'
    else:
        log.info('SERVER: no data in request')
        response = jsonify({'message': 'no data field in request GET'})
        response.status_code = 400
        return response


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Arduino to web test server. Waits data in GET request.')
    parser.add_argument('-o', '--host', default='127.0.0.1', help='server host')
    parser.add_argument('-p', '--port', type=int, default=45000, help='port of the server')
    args = parser.parse_args()
    app.run(host=args.host, port=args.port)