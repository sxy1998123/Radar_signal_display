from flask import Flask, jsonify, send_from_directory,Blueprint
from flask_cors import CORS
import logging
from routes import signal_bp
from flasgger import Swagger 

logging.basicConfig(
    level=logging.INFO,  # 修改日志级别输出所有日志
    format='%(asctime)s %(name)s [%(pathname)s:%(lineno)d] %(levelname)s %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',  # 日期时间格式
)

app = Flask(__name__, static_folder='frontend_dist', static_url_path='')
CORS(app) # 开发环境下允许跨域请求

@app.route('/')
def index():
    return "Hello World!"

app.register_blueprint(signal_bp, url_prefix="/api/signal")
Swagger(app)

if __name__ == '__main__':
    app.run(debug=True)