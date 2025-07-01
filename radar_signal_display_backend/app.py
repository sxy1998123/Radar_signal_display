from flask import Flask, jsonify
from flask_cors import CORS
import logging


logging.basicConfig(
    level=logging.INFO,  # 修改日志级别输出所有日志
    format='%(asctime)s %(name)s [%(pathname)s:%(lineno)d] %(levelname)s %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',  # 日期时间格式
)

app = Flask(__name__)
CORS(app) # 开发环境下允许跨域请求

@app.route('/')
def index():
    logging.info('index accessed')
    return jsonify({"message": "Hello World!"})

@app.route('/api/test')
def test():
    logging.info('/api/test accessed')
    return jsonify({"message": "Flask启动成功!"})

if __name__ == '__main__':
    app.run(debug=True)