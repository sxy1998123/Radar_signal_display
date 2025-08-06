#!/usr/bin/python
# -*- coding: utf8 -*-
import time

from .pyQueentest import *
import os

unCardIndex = 0
temp = 0
channelcount = 1
uint8 = c_uint8
uint64 = c_uint64
uptr8 = POINTER(uint8)

collecting = False


class QTSetFunction:
    def QT_BoardGetBoardInfo(self):
        # 获取板卡信息
        print("板卡型号:%d" % (QT_BoardGetCardType(unCardIndex)))

        # 获取板卡固件版本号
        print("固件版本号:%d" % QT_BoardGetCardSoftVersion(unCardIndex))

        # 获取板卡ADC采样率信息
        print("ADC采样率:%d" % QT_BoardGetCardADCSamplerate(unCardIndex))

        # 获取板卡ADC通道数信息
        print("ADC通道数:%d" % QT_BoardGetCardADCChNumbers(unCardIndex))

        # 获取板卡ADC分辨率信息
        print("ADC分辨率:%d" % QT_BoardGetCardADCResolution(unCardIndex))

        # 获取板卡DAC采样率信息
        print("DAC采样率:%d" % QT_BoardGetCardDACSamplerate(unCardIndex))

        # 获取板卡DAC通道数信息
        print("DAC通道数:%d" % QT_BoardGetCardDACChNumbers(unCardIndex))

        # 获取板卡DAC分辨率信息
        print("DAC分辨率:%d" % QT_BoardGetCardDACResolution(unCardIndex))

        # 获取板卡状态值
        print("板卡状态值:%d" % QT_BoardGetCardStatus(unCardIndex))

        return 0
    # 有限点单次回环

    def QT_BoardSetRecStdSingleLoopback(workMode, file_path, save_path):

        if workMode == 0:
            dbFreq = int(input("设置DDS播放频率(单位:KHz):"))
            QT_BoardSetupRepSourceDDS(unCardIndex, dbFreq)
        elif workMode == 1:
            # 获取文件路径
            # file_path = input("播放文件(文件路径及文件名):")
            # 规范化路径
            file_path = os.path.normpath(file_path)
            c_file_path = file_path.encode('utf-8')
            try:
                # 打开文件
                with open(file_path, "rb") as file:

                    file_size = os.stat(file_path).st_size
                    buffer = file.read()
                    # 发送数据（假设这两个函数已正确实现）
                    QT_BoardSetupRepSourceFileDMALoopPlay(unCardIndex, 0, 0, 0, c_file_path, file_size)
                    print(file_path, file_size)
            except FileNotFoundError:
                print("打开文件失败")
                return -1
            except Exception as e:
                print(f"发生错误: {e}")
                return -2
            # hfilehandle = input("播放文件(文件路径及文件名):")
            # hfilehandle = os.path.normpath(hfilehandle).encode("utf-8")
            # hfilehandle = open(hfilehandle.decode('utf-8'), "rb")
            # if hfilehandle is None:
            # 	print("打开文件失败\n")
            # 	return -1
            # hfilehandle.seek(0, 2)
            # stats = os.stat(hfilehandle)
            # MBytes2 = stats.st_size
            # hfilehandle.seek(0)

    # 设置段长(单位:字节)
        Segment = 1024
        a = Segment % 64
        Segment = Segment-a
        print(f"下发的段长为: {Segment} 字节")
        # 设置帧头（0:禁用1:使能）
        Frameswitch = 0
        # 设置预触发(单位:点数)
        Pretrigdots = 0
        QT_BoardSetupModeRecStdSingle(unCardIndex, 0, Segment, Frameswitch, Pretrigdots)

        # 上位机启动采集ADC数据
        QT_BoardSetupRepPlayData(unCardIndex, 1)
        QT_BoardSetupRecCollectData(unCardIndex, 1, 1)

        # 获取数据
        Buffer = create_string_buffer(Segment)
        # file = open("./adc_std_single_0.bin", 'wb+')
        file = open(save_path, 'wb+')
        QT_BoardSetupRecGetData(0, 0, Buffer, Segment)
        file.write(Buffer)
        file.close()

        # 上位机停止采集ADC数据
        QT_BoardSetupRepPlayData(unCardIndex, 0)
        QT_BoardSetupRecCollectData(unCardIndex, 0, 1)

        return 0

    def QT_BoardSetRepClockMode():
        temp = QT_BoardIfSupportClockMode(unCardIndex)
        if temp == 0:
            # DAC时钟模式 (0:内参考时钟 1:外采样时钟 2:外参考时钟)
            clockMode = 0
            QT_BoardSetupRepClockMode(unCardIndex, clockMode)
        elif temp == -1:
            # DAC时钟模式 (0:内参考时钟 1:外采样时钟)
            clockMode = 0
            QT_BoardSetupRepClockMode(unCardIndex, clockMode)
        elif temp == -2:
            # DAC时钟模式 (0:内参考时钟 2:外参考时钟)
            clockMode = 0
            QT_BoardSetupRepClockMode(unCardIndex, clockMode)
        elif temp == -3:
            # DAC时钟模式 (0:内参考时钟)
            clockMode = 0
            QT_BoardSetupRepClockMode(unCardIndex, clockMode)

        return 0

    def QT_BoardSetRecClockMode():
        # ADC时钟模式
        temp = QT_BoardIfSupportClockMode(unCardIndex)
        if temp == 0:
            # ADC时钟模式(0:内参考时钟 1:外采样时钟 2:外参考时钟)
            clockMode = 0
            QT_BoardSetupRecClockMode(unCardIndex, clockMode)
            print("colck", clockMode)
        elif temp == -1:
            # ADC时钟模式(0:内参考时钟 1:外采样时钟)
            clockMode = 0
            QT_BoardSetupRecClockMode(unCardIndex, clockMode)
        elif temp == -2:
            # ADC时钟模式(0:内参考时钟 2:外参考时钟)
            clockMode = 0
            QT_BoardSetupRecClockMode(unCardIndex, clockMode)
        elif temp == -3:
            # ADC时钟模式(0:内参考时钟)
            clockMode = 0
            QT_BoardSetupRecClockMode(unCardIndex, clockMode)

        return 0
