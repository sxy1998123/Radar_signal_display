#!/usr/bin/python
# -*- coding: utf8 -*-
import time

from QTSetFunction import *

unCardIndex = 0
channelcount = 0


if __name__ == '__main__':
    try:
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

        # 设置采集 / 播放模式
        workMode =int(input("设置播放模式（0：DDS播放，1：bin文件播放）："))

        #回环模式1，标准模式0
        QT_BoardSetLoopbackOrStandardWorkMode(0, 1)

        #时钟模式设置
        QTSetFunction.QT_BoardSetRepClockMode()
        QTSetFunction.QT_BoardSetRecClockMode()

        # 获取用户输入,#设置DA延迟间
        DA_delaytime = int(input("设置DA延迟时间（单位：us）"))

        # 计算延迟值，并转换为 uint32 类型
        delay_value = DA_delaytime * 5000 // 2.667  # 使用 // 确保整除（结果为整数）
        delay_value = c_uint32(int(delay_value))  # 显式转换为整数，再封装为 uint32
        QT_BoardSetRepPlayDelay(0, delay_value)

        #DAC通道选择
        QT_BoardSetupRepChannelMode(0, 1);
        AD_delaytime = int(input("设置AD延迟时间（单位：us）"))

        # 设置AD采集延迟间
        delay_value = AD_delaytime * 5000 // 2.667  # 使用 // 确保整除（结果为整数）
        delay_value = c_uint32(int(delay_value))  # 显式转换为整数，再封装为 uint32
        QT_BoardSetRepPlayDelay(0, delay_value)

        #ADC触发方式
        trigMode = int(input("设置触发模式（0:软件触发 1:内部脉冲触发 2:外部脉冲触发）："))
        if trigMode != 0 and trigMode != 1 and trigMode != 2:
            print("触发模式设置错误")
        if trigMode == 0:
            print("触发次数为1！")
            trigcount = 1
            QT_BoardSetupTrigRecSoftware(unCardIndex)
            QT_BoardSetupTrigRepSoftware(unCardIndex)
        elif trigMode == 1:
            tgintperiod = int(input("设置脉冲周期(ns):"))
            QT_BoardSetupTrigRecInternalPulse(unCardIndex, tgintperiod, 10)
            QT_BoardSetupTrigRepInternalPulse(unCardIndex, tgintperiod, 10)
            trigcount = int(input("设置触发次数(0:无限次 1:有限次):"))
        elif trigMode == 2:
            trigDelay = int(input("设置延迟触发长度:"))
            QT_BoardSetupTrigRecExternal(unCardIndex, 2, trigDelay, 0)
            QT_BoardSetupTrigRepExternal(unCardIndex, 2)
            trigcount = int(input("设置触发次数(0:无限次 1:有限次):"))

        board_status = QT_BoardGetCardStatus(unCardIndex)
        if board_status != 15:
            print(f"板卡状态值不正确:{board_status}")
            exit(-1)

        #获取板卡DMA个数
        blockNumADC = QT_BoardObtainTheADCBlockNum(unCardIndex)
        print("blockNumADC is",blockNumADC)
        blockNumDAC = QT_BoardObtainTheDACBlockNum(unCardIndex)

        if trigcount == 1:
            print("============开始有限点单次回环============")
            QTSetFunction.QT_BoardSetRecStdSingleLoopback(workMode)
        elif trigcount == 0:
            print("============开始无限点多次回环============")
            QTSetFunction.QT_BoardSetRecFIFOMultiLoopback(workMode)

        # 关闭板卡
        QT_BoardCloseBoard(unCardIndex)

    except KeyboardInterrupt:
        print(" \n 程序已停止执行")
