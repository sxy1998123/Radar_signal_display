#!/usr/bin/python
# -*- coding: utf8 -*-
from .myQTSetFunction import *

unCardIndex = 0
channelcount = 0
collecting = False


def start_collect(DA_delaytime=0, AD_delaytime=0, trigDelay=0, bin_file_path="", Frameswitch=False, save_path="", Segment=1024, Pretrigdots=0, RepetitionFrequency_input=60, save_file_size=1024*500):
    global unCardIndex, channelcount
    global collecting  # 全局变量，用于判断是否正在采集
    try:
        # 参数处理
        required_fields = ["DA_delaytime", "AD_delaytime", "trigDelay", "bin_file_path", "Frameswitch",
                           "save_path", "Segment", "Pretrigdots", "RepetitionFrequency_input", "save_file_size"]
        for field in required_fields:
            if locals()[field] == "":
                print(f"参数{field}不能为空")
                return -1
        workMode = 1  # 工作模式（0：DDS播放，1：bin文件播放）
        DA_delaytime = int(DA_delaytime)  # DA延迟时间（单位：us）
        AD_delaytime = int(AD_delaytime)  # AD延迟时间（单位：us）
        trigDelay = int(trigDelay)  # 触发延迟长度
        bin_file_path = os.path.normpath(bin_file_path)  # bin文件路径
        Frameswitch = int(Frameswitch)  # 设置帧头(0:禁用  1:使能)
        # bin_file_path = "D:\\Project2025\\Radar_signal_display_test\\I_signal.bin"
        save_path = os.path.normpath(save_path)  # 保存路径
        # save_path = "D:\\Project2025\\Radar_signal_display_test\\collect"
        Segment = int(Segment)  # 段长
        Pretrigdots = int(Pretrigdots)  # 预触发点数
        RepetitionFrequency_input = int(RepetitionFrequency_input)  # 重复频率
        save_file_size = int(save_file_size)  # 文件大小（单位：byte）

        # 打印参数
        print("\n**********调用参数start**********")
        print("工作模式:%d" % workMode)
        print("DA延迟时间:%d" % DA_delaytime)
        print("AD延迟时间:%d" % AD_delaytime)
        print("bin文件路径:%s" % bin_file_path)
        print("是否设置帧头:%s" % Frameswitch)
        print("保存路径:%s" % save_path)
        print("段长:%dB" % Segment)
        print("预触发点数:%d" % Pretrigdots)
        print("触发频率:%dHz" % RepetitionFrequency_input)
        print("文件大小:%dB" % save_file_size)
        print("**********调用参数end**********\n")
        # 打开板卡
        ret = QT_BoardOpenBoard(unCardIndex)
        if ret < 0:
            print("打开板卡失败!\n")

        # ADC软件复位
        QT_BoardSetSoftwareReset(unCardIndex, 0)
        # DAC软件复位
        QT_BoardSetSoftwareReset(unCardIndex, 1)
        # 停止采集
        QT_BoardSetupRecCollectData(unCardIndex, 0, 1)
        # 停止播放
        QT_BoardSetupRepPlayData(unCardIndex, 0)

        # 获取板卡信息
        QTSetFunction().QT_BoardGetBoardInfo()

        # 设置采集 / 播放模式 （0：DDS播放，1：bin文件播放）
        # workMode = 1

        # 回环模式1，标准模式0
        QT_BoardSetLoopbackOrStandardWorkMode(0, 1)

        # 时钟模式设置
        QTSetFunction.QT_BoardSetRepClockMode()
        QTSetFunction.QT_BoardSetRecClockMode()

        # 设置DA延迟时间（单位：us）
        # DA_delaytime = 0

        # 计算延迟值，并转换为 uint32 类型
        delay_value = DA_delaytime * 5000 // 2.667  # 使用 // 确保整除（结果为整数）
        delay_value = c_uint32(int(delay_value))  # 显式转换为整数，再封装为 uint32
        QT_BoardSetRepPlayDelay(0, delay_value)

        # DAC通道选择
        QT_BoardSetupRepChannelMode(0, 1)

        # 设置AD延迟时间（单位：us）
        # AD_delaytime = 0

        # 设置AD采集延迟间
        delay_value = AD_delaytime * 5000 // 2.667  # 使用 // 确保整除（结果为整数）
        delay_value = c_uint32(int(delay_value))  # 显式转换为整数，再封装为 uint32
        QT_BoardSetRepPlayDelay(0, delay_value)

        # 设置延迟触发长度:
        # trigDelay = 0
        QT_BoardSetupTrigRecExternal(unCardIndex, 2, trigDelay, 0)
        QT_BoardSetupTrigRepExternal(unCardIndex, 2)
        # 设置触发次数(0:无限次 1:有限次):
        trigcount = 0

        board_status = QT_BoardGetCardStatus(unCardIndex)
        if board_status != 15:
            print(f"板卡状态值不正确:{board_status}")
            return -1

        # 获取板卡DMA个数
        blockNumADC = QT_BoardObtainTheADCBlockNum(unCardIndex)
        print("blockNumADC is", blockNumADC)
        blockNumDAC = QT_BoardObtainTheDACBlockNum(unCardIndex)

        print("============开始无限点多次回环============")
        # 规范化路径
        bin_file_path = os.path.normpath(bin_file_path)
        try:
            # 打开文件
            with open(bin_file_path, "rb") as file:
                # 获取文件大小

                bin_file_size = os.stat(bin_file_path).st_size
                buffer = file.read()
                # 发送数据
                QT_BoardSetupRepSendData(unCardIndex, 0, buffer, bin_file_size)
                QT_BoardSetupRepFifoDMACtrlLoopPlay(unCardIndex, 0, bin_file_size)
        except FileNotFoundError:
            print("打开文件失败")
            return -1
        except Exception as e:
            print(f"发生错误: {e}")
            return -2
        # 规范化段长
        a = Segment % 64
        Segment = Segment - a
        print(f"下发的段长为: {Segment} 字节")
        RepetitionFrequency = c_double(float(RepetitionFrequency_input))
        QT_BoardSetupModeRecFIFOMulti(unCardIndex, 0, Segment, Frameswitch, Pretrigdots, RepetitionFrequency)

        # 设置文件保存路径
        QT_BoardSetInitializeOperation(unCardIndex)
        QT_BoardSetTheFilePathSizeName(unCardIndex, 0, ctypes.c_char_p(save_path.encode()), save_file_size, "0")

        # 开始播放
        QT_BoardSetupRepPlayData(unCardIndex, 1)

        # 上位机启动采集ADC数据
        QT_BoardSetupRecCollectData(unCardIndex, 1, 1)

        collecting = True

        import random

        while collecting:
            time.sleep(10)

        print("停止播放")
        # 上位机停止采集ADC数据
        QT_BoardSetupRecCollectData(unCardIndex, 0, 1)
        QT_BoardSetupRepPlayData(unCardIndex, 0)
        # 释放buffer
        QT_BoardSetFreeOperation(unCardIndex)
        # 关闭板卡
        QT_BoardCloseBoard(unCardIndex)
        return 0

    except KeyboardInterrupt:
        collecting = False
        print(" \n 接收到Ctrl+C，程序已停止执行")
    except Exception as e:
        print(f"发生错误: {e}")
        # 关闭板卡
        QT_BoardCloseBoard(unCardIndex)


def end_collect():
    global collecting
    collecting = False

if __name__ == '__main__':
    # test
    start_collect(
        DA_delaytime=0,
        AD_delaytime=0,
        trigDelay=0,
        bin_file_path="D:\\Project2025\\Radar_signal_display_test\\I_signal.bin",
        Frameswitch=False,
        save_path="D:\\Project2025\\Radar_signal_display_test\\collect",
        Segment=1024,
        Pretrigdots=0,
        RepetitionFrequency_input=60,
        save_file_size=1024*500
    )
