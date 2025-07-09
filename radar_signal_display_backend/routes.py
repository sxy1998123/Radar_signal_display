from flask import Blueprint, request, jsonify, send_file, current_app
from datetime import datetime
from utils.func_SFCW_I_Q import generate_step_freq_signal, save_signal_with_dir
from utils.func_Handle import read_process_and_output
import logging
import os
signal_bp = Blueprint('signal', __name__)

# logging.basicConfig(
#     level=logging.INFO,  # 修改日志级别输出所有日志
#     format='%(asctime)s %(name)s [%(pathname)s:%(lineno)d] %(levelname)s %(message)s',
#     datefmt='%Y-%m-%d %H:%M:%S',  # 日期时间格式
# )

# 信号处理结果
base_dir = os.path.dirname(os.path.abspath(__file__))
img_save_path = os.path.join(base_dir, "plt_img")
num_units = None
logging.info(f"img_save_path: {img_save_path}")


@signal_bp.route('/index')
def index():
    logging.info("Hello")
    return "Hello, World!"

# 显式处理相同URL的其他方法


@signal_bp.route('/generate', methods=['GET', 'PUT', 'DELETE'])
def handle_invalid_methods():
    return jsonify({"error": "Method not allowed"}), 405


@signal_bp.route('/generate', methods=['POST'])
def generate_signal():
    """生成信号
    接收前端传来的信号参数，生成信号并返回
    ---
    parameters:
      - name: signal_type
        in: body
        type: string
        required: false
        description: 信号类型

      - name: fs
        in: body
        type: number
        required: true
        description: 采样率(Hz)

      - name: fc_start
        in: body
        type: number
        required: true
        description: 起始频率(Hz)

      - name: fc_end
        in: body
        type: number
        required: true
        description: 终止频率(Hz)

      - name: num_steps
        in: body
        type: number
        required: true
        description: 步进频率点数

      - name: use_iq
        in: body
        type: boolean
        required: true
        description: 同时生成I/Q信号

      - name: T
        in: body
        type: number
        required: true
        description: 单个频点持续时间(s)

      - name: save_dir
        in: body
        type: number
        required: true
        description: 保存路径
    responses:
      200:
        description: 信息成功添加
    """
    data = request.get_json()

    required_fields = ['fs', 'fc_start', 'fc_end', 'num_steps', 'use_iq', 'T', 'save_dir']
    for field in required_fields:
        if field not in data:
            return jsonify({"error": f"Missing field: {field}"}), 400

    try:
        # 生成信号
        fs = data['fs']
        fc_start = data['fc_start']
        fc_end = data['fc_end']
        num_steps = data['num_steps']
        use_iq = data['use_iq']
        T = data['T']
        i_signal, q_signal = generate_step_freq_signal(fs=fs, fc_start=fc_start, fc_end=fc_end, num_steps=num_steps, use_iq=use_iq, T=T)
        save_dir = data['save_dir']
        # 保存信号
        if use_iq:
            save_signal_with_dir(i_signal, "I", save_dir)
            save_signal_with_dir(q_signal, "Q", save_dir)
        else:
            save_signal_with_dir(i_signal, "I", save_dir)
        # 返回成功响应
        response = {
            "message": "success",
            "data": {
                "save_dir": save_dir
            }
        }
        print(response)
        return jsonify(response), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@signal_bp.route('/handle', methods=['GET', 'PUT', 'DELETE'])
def handle_invalid_methods_2():
    return jsonify({"error": "Method not allowed"}), 405


@signal_bp.route('/handle', methods=['POST'])
def handle_signal():
    """处理信号
    接收前端传来的信号参数，处理信号并返回
    ---
    parameters:
      - name:  collectionSigFolder
        in: body
        type: string
        required: true
        description: 采集信号文件夹地址

      - name: referenceSig_I
        in: body
        type: string
        required: true
        description: 参考I相信号文件夹地址

      - name: referenceSig_Q
        in: body
        type: string
        required: true
        description: 参考I相信号文件夹地址

      - name: window_type
        in: body
        type: string
        required: true
        description: 加窗处理类型

      - name: other_process
        in: body
        type: string
        required: true
        description: 其他处理
    """
    data = request.get_json()

    required_fields = ['collectionSigFolder', 'referenceSig_I', 'referenceSig_Q', 'window_type', 'other_process']
    for field in required_fields:
        if field not in data:
            return jsonify({"error": f"Missing field: {field}"}), 400

    try:
        # todo: 处理信号并返回
        collectionSigFolder = data['collectionSigFolder']
        referenceSig_I = data['referenceSig_I']
        referenceSig_Q = data['referenceSig_Q']
        window_type = data['window_type']
        other_process = data['other_process']
        # todo: 处理信号并生成4种生成图表文件
        if not os.path.exists(img_save_path):
            os.makedirs(img_save_path)
        else:
            # 清空文件夹
            for file in os.listdir(img_save_path):
                os.remove(os.path.join(img_save_path, file))
        sig_handle_result = read_process_and_output(collectionSigFolder, referenceSig_I, referenceSig_Q, img_save_path)
        global num_units
        num_units = sig_handle_result["num_units"]
        response = {
            "message": "success",
            "data": {
                "num_units": sig_handle_result["num_units"],
                "time_domain_img": "/api/signal/time_domain_img",
                "freq_domain_img":  "/api/signal/freq_domain_img",
                "ascan_img": "/api/signal/ascan_img",
                "bscan_img": "/api/signal/bscan_img"
            }
        }
        return jsonify(response), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@signal_bp.route('/time_domain_img', methods=['GET'])
def get_time_domain_data():
    num_unit = request.args.get("num_unit")
    num_unit_int = int(num_unit)
    # 未处理信号时
    if num_units is None:
        return jsonify({"error": "No signal processed"}), 400
    # 参数检查
    if num_unit_int is None:
        return jsonify({"error": "Missing num_unit"}), 400
    if num_unit_int < 0 or num_unit_int >= num_units:
        return jsonify({"error": f"num_unit out of range, should be in [0, {num_units})"}), 400
    # 准备返回图片
    img_path = os.path.join(img_save_path, f"Unit_{num_unit}_Time_Domain.png")
    logging.info(f"img_path: {img_path}")
    if not os.path.exists(img_path):
        return jsonify({"error": "Image not found"}), 404
    return send_file(img_path, mimetype='image/png'), 200


@signal_bp.route('/freq_domain_img', methods=['GET'])
def get_freq_domain_data():
    num_unit = request.args.get("num_unit")
    num_unit_int = int(num_unit)
    # 未处理信号时
    if num_units is None:
        return jsonify({"error": "No signal processed"}), 400
    # 参数检查
    if num_unit_int is None:
        return jsonify({"error": "Missing num_unit"}), 400
    if num_unit_int < 0 or num_unit_int >= num_units:
        return jsonify({"error": f"num_unit out of range, should be in [0, {num_units})"}), 400
    # 准备返回图片
    img_path = os.path.join(img_save_path, f"Unit_{num_unit}_Frequency_Domain.png")
    logging.info(f"img_path: {img_path}")
    if not os.path.exists(img_path) or num_units is None:
        return jsonify({"error": "Image not found"}), 404
    return send_file(img_path, mimetype='image/png'), 200


@signal_bp.route('/ascan_img', methods=['GET'])
def get_ascan():
    img_path = os.path.join(img_save_path, "A-Scan.png")
    if not os.path.exists(img_path):
        return jsonify({"error": "Image not found"}), 404
    return send_file(img_path, mimetype='image/png'), 200


@signal_bp.route('/bscan_img', methods=['GET'])
def get_bscan():
    img_path = os.path.join(img_save_path, "B-Scan.png")
    if not os.path.exists(img_path):
        return jsonify({"error": "Image not found"}), 404
    return send_file(img_path, mimetype='image/png'), 200
