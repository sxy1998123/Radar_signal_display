from flask import Blueprint, request, jsonify
from datetime import datetime
from utils.func_SFCW_I_Q import generate_step_freq_signal
import logging

signal_bp = Blueprint('signal', __name__)


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

    responses:
      200:
        description: 信息成功添加
    """
    data = request.get_json()

    required_fields = ['fs', 'fc_start', 'fc_end', 'num_steps', 'use_iq', 'T']
    for field in required_fields:
        if field not in data:
            return jsonify({"error": f"Missing field: {field}"}), 400

    try:
        # todo: 生成信号并返回
        fs = data['fs']
        fc_start = data['fc_start']
        fc_end = data['fc_end']
        num_steps = data['num_steps']
        use_iq = data['use_iq']
        T = data['T']
        i_signal, q_signal = generate_step_freq_signal(fs=fs, fc_start=fc_start, fc_end=fc_end, num_steps=num_steps, use_iq=use_iq, T=T)
        
        # 返回成功响应
        response = {
            "message": "success",
            "data": {
                "i_signal": i_signal.tolist(),
                "q_signal": q_signal.tolist() if use_iq else None
            }
        }
        print(response)
        return jsonify(response), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500
