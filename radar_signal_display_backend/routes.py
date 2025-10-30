from flask import Blueprint, request, jsonify, send_file, current_app
from datetime import datetime
# 信号生成及处理
from utils.func_SFCW_I_Q import generate_step_freq_signal, save_signal_with_dir
from utils.func_Handle import read_process_and_output
# 信号采集sdk
from sdk.myMain import start_collect, end_collect
import logging
import os
import threading
signal_bp = Blueprint('signal', __name__)

logger = logging.getLogger()

# 信号处理结果
base_dir = os.path.dirname(os.path.abspath(__file__))
img_save_path = os.path.join(base_dir, "plt_img")
num_units = None
logger.info(f"img_save_path: {img_save_path}")


@signal_bp.route('/index')
def index():
    logger.info("Hello")
    return "Hello, World!"

# 显式处理相同URL的其他方法

# 信号生成接口 start
@signal_bp.route('/generate', methods=['GET', 'PUT', 'DELETE'])
def handle_invalid_generate():
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
# 信号生成接口 end
# 信号处理接口 start


@signal_bp.route('/handle', methods=['GET', 'PUT', 'DELETE'])
def handle_invalid_handle():
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
        description: 参考Q相信号文件夹地址

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
# 信号处理接口 end
# 图片接口 start


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
    logger.info(f"img_path: {img_path}")
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
    logger.info(f"img_path: {img_path}")
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
# 图片接口 end


@signal_bp.route('/collect_start', methods=['GET', 'PUT', 'DELETE'])
def handle_invalid_collect_start():
    return jsonify({"error": "Method not allowed"}), 405


@signal_bp.route('/collect_start', methods=['POST'])
def handle_collect_start():
    """采集信号
    接收前端传来的信号参数，采集信号并返回
    ---
    parameters:
      - name:  DA_delaytime
        in: body
        type: string
        required: true
        description: DA延迟时间（us）

      - name: AD_delaytime
        in: body
        type: string
        required: true
        description: AD延迟时间（us）

      - name: trigDelay
        in: body
        type: string
        required: true
        description: 触发延迟长度

      - name: bin_file_path
        in: body
        type: string
        required: true
        description: 播放文件地址

      - name: Frameswitch
        in: body
        type: string
        required: true
        description: 是否使用帧头

      - name: collectionSaveFolder
        in: body
        type: string
        required: true
        description: 信号保存地址        

      - name: Segment
        in: body
        type: string
        required: true
        description: 段长(字节)

      - name: Pretrigdots
        in: body
        type: string
        required: true
        description: 预触发点数

      - name: RepetitionFrequency_input
        in: body
        type: string
        required: true
        description: 触发频率（Hz）

      - name: save_file_size
        in: body
        type: string
        required: true
        description: 文件大小(B)
    """
    data = request.get_json()

    required_fields = ['DA_delaytime', 'AD_delaytime', 'trigDelay', 'bin_file_path', 'Frameswitch',
                       'collectionSaveFolder', 'Segment', 'Pretrigdots', 'RepetitionFrequency_input', 'save_file_size']
    for field in required_fields:
        if field not in data:
            return jsonify({"error": f"Missing field: {field}"}), 400
    try:
        # todo: 参数检查及处理
        DA_delaytime = int(data['DA_delaytime'])
        AD_delaytime = int(data['AD_delaytime'])
        trigDelay = int(data['trigDelay'])
        bin_file_path = data['bin_file_path']
        Frameswitch = data['Frameswitch']
        collectionSaveFolder = data['collectionSaveFolder']
        Segment = data['Segment']
        Pretrigdots = data['Pretrigdots']
        RepetitionFrequency_input = data['RepetitionFrequency_input']
        save_file_size = data['save_file_size']
        logger.info(data)
        logger.info(f"DA_delaytime: {DA_delaytime}, AD_delaytime: {AD_delaytime}, trigDelay: {trigDelay}, bin_file_path: {bin_file_path}, Frameswitch: {Frameswitch}, collectionSaveFolder: {collectionSaveFolder}, Segment: {Segment}, Pretrigdots: {Pretrigdots}, RepetitionFrequency_input: {RepetitionFrequency_input}, save_file_size: {save_file_size}")
        # todo: 采集信号并保存
        # collect_thread = threading.Thread(
        #     target=start_collect,
        #     name="collect_thread",
        #     args=(DA_delaytime, AD_delaytime, trigDelay, bin_file_path, Frameswitch, collectionSaveFolder, Segment, Pretrigdots, RepetitionFrequency_input, save_file_size)
        # )
        # collect_thread.start()
        collect_thread = threading.Thread(
            target=start_collect,
            name="collect_thread",
            kwargs={
                "DA_delaytime": DA_delaytime,
                "AD_delaytime": AD_delaytime,
                "trigDelay": trigDelay,
                "bin_file_path": bin_file_path,
                "Frameswitch": Frameswitch,
                "collectionSaveFolder": collectionSaveFolder,
                "Segment": Segment,
                "Pretrigdots": Pretrigdots,
                "RepetitionFrequency_input": RepetitionFrequency_input,
                "save_file_size": save_file_size
            }
        )
        collect_thread.start()
    except Exception as e:
        return jsonify({"error": str(e)}), 500
    # 返回成功响应
    response = {
        "message": "success",
        "status": "collecting"
    }
    return jsonify(response), 200


@signal_bp.route('/collect_end', methods=['GET'])
def handle_collect_end():
    try:
        end_collect()
    except Exception as e:
        return jsonify({"error": str(e)}), 500
    response = {
        "message": "success",
        "status": "collectend"
    }
    return jsonify(response), 200
