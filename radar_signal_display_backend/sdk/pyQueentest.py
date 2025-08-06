#!/usr/bin/env python
# encoding: utf-8

import ctypes
import os
import platform
import sys
# import path
from ctypes import *

# load registers for easier access
# determine bit width of os
oPlatform = platform.architecture()
if oPlatform[0] == '64bit':
    bIs64Bit = 1
else:
    bIs64Bit = 0

uint8  = c_uint8
uint64 = c_uint64
uptr8  = POINTER(uint8)

# Windows
if os.name == 'nt':
    sys.stdout.write("Windows found\n")

    # define card handle type
    if(bIs64Bit):
        # for unknown reasons c_void_p gets messed up on Win7/64bit,  but this works:
        drv_handle = POINTER(c_uint64)
    else:
        drv_handle = c_void_p

    # Load DLL into memory.
    # use windll because all driver access functions use _stdcall calling convention under windows
    if(bIs64Bit == 1):
        QueentestDll = windll.LoadLibrary(".\\sdk\\QT_Board.dll")
    else:
        QueentestDll = windll.LoadLibrary(".\\sdk\\QT_Board.dll")

    # 打开板卡
    QT_BoardOpenBoard = getattr(QueentestDll, "QT_BoardOpenBoard")
    QT_BoardOpenBoard.unCardIdx = int

    #软件复位
    QT_BoardSetSoftwareReset = getattr(QueentestDll, "QT_BoardSetSoftwareReset")
    QT_BoardSetSoftwareReset.unCardIdx = int
    QT_BoardSetSoftwareReset.direction = int

    # 关闭板卡
    QT_BoardCloseBoard = getattr(QueentestDll, "QT_BoardCloseBoard")
    QT_BoardCloseBoard.unCardIdx = int

    # 获取板卡型号
    QT_BoardGetCardType = getattr(QueentestDll, "QT_BoardGetCardType")
    QT_BoardGetCardType.unCardIdx = int

    # 获取板卡固件版本号
    QT_BoardGetCardSoftVersion = getattr(QueentestDll,  "QT_BoardGetCardSoftVersion")
    QT_BoardGetCardSoftVersion.unCardIdx = int

    # 获取板卡ADC采样率信息
    QT_BoardGetCardADCSamplerate = getattr(QueentestDll, "QT_BoardGetCardADCSamplerate")
    QT_BoardGetCardADCSamplerate.unCardIdx = int

    # 获取板卡ADC通道数信息
    QT_BoardGetCardADCChNumbers = getattr(QueentestDll,  "QT_BoardGetCardADCChNumbers")
    QT_BoardGetCardADCChNumbers.unCardIdx = int

    # 获取板卡ADC分辨率信息
    QT_BoardGetCardADCResolution = getattr(QueentestDll, "QT_BoardGetCardADCResolution")
    QT_BoardGetCardADCResolution.unCardIdx = int

    # 获取板卡DAC采样率信息
    QT_BoardGetCardDACSamplerate = getattr(QueentestDll, "QT_BoardGetCardDACSamplerate")
    QT_BoardGetCardDACSamplerate.unCardIdx = int

    # 获取板卡DAC通道数信息
    QT_BoardGetCardDACChNumbers = getattr(QueentestDll, "QT_BoardGetCardDACChNumbers")
    QT_BoardGetCardDACChNumbers.unCardIdx = int

    # 获取板卡DAC分辨率信息
    QT_BoardGetCardDACResolution = getattr(QueentestDll, "QT_BoardGetCardDACResolution")
    QT_BoardGetCardDACResolution.unCardIdx = int

    # 获取板卡状态值
    QT_BoardGetCardStatus = getattr(QueentestDll, "QT_BoardGetCardStatus")
    QT_BoardGetCardStatus.unCardIdx = int

    # ADC时钟模式
    QT_BoardSetupRecClockMode = getattr(QueentestDll, "QT_BoardSetupRecClockMode")
    QT_BoardSetupRecClockMode.unCardIdx = int
    QT_BoardSetupRecClockMode.ClockMode = int

    # ADC软件触发
    QT_BoardSetupTrigRecSoftware = getattr(QueentestDll, "QT_BoardSetupTrigRecSoftware")
    QT_BoardSetupTrigRecSoftware.unCardIdx = int

    # ADC外部脉冲触发
    QT_BoardSetupTrigRecExternal = getattr(QueentestDll, "QT_BoardSetupTrigRecExternal")
    QT_BoardSetupTrigRecExternal.unCardIdx = int
    QT_BoardSetupTrigRecExternal.ExtMode = int
    QT_BoardSetupTrigRecExternal.trigDelay = int
    QT_BoardSetupTrigRecExternal.biasvoltage = int

    # ADC通道触发
    QT_BoardSetupTrigRecChannel = getattr(QueentestDll, "QT_BoardSetupTrigRecChannel")
    QT_BoardSetupTrigRecChannel.unCardIdx = int
    QT_BoardSetupTrigRecChannel.TrigMode = int
    QT_BoardSetupTrigRecChannel.Channel = int
    QT_BoardSetupTrigRecChannel.hysteresis = int
    QT_BoardSetupTrigRecChannel.TrigLevel = int

    # 获取板卡ADC DMA个数
    QT_BoardObtainTheADCBlockNum = getattr(QueentestDll, "QT_BoardObtainTheADCBlockNum")
    QT_BoardObtainTheADCBlockNum.unCardIdx = int

    # 获取板卡DAC DMA个数
    QT_BoardObtainTheDACBlockNum = getattr(QueentestDll, "QT_BoardObtainTheDACBlockNum")
    QT_BoardObtainTheDACBlockNum.unCardIdx = int

    # ADC内部脉冲触发
    QT_BoardSetupTrigRecInternalPulse = getattr(QueentestDll, "QT_BoardSetupTrigRecInternalPulse")
    QT_BoardSetupTrigRecInternalPulse.unCardIdx = int
    QT_BoardSetupTrigRecInternalPulse.PulsePeriod = int
    QT_BoardSetupTrigRecInternalPulse.PulseWidth = int

    # 有限点单次触发采集模式
    QT_BoardSetupModeRecStdSingle = getattr(QueentestDll, "QT_BoardSetupModeRecStdSingle")
    QT_BoardSetupModeRecStdSingle.unCardIdx = int
    QT_BoardSetupModeRecStdSingle.blockNum = int
    QT_BoardSetupModeRecStdSingle.segment = int
    QT_BoardSetupModeRecStdSingle.Frameswitch = int
    QT_BoardSetupModeRecStdSingle.pretrigdots = int

    # 上位机启动 / 停止采集ADC数据
    QT_BoardSetupRecCollectData = getattr(QueentestDll, "QT_BoardSetupRecCollectData")
    QT_BoardSetupRecCollectData.unCardIdx = int
    QT_BoardSetupRecCollectData.RecSwitch = int

    # 获取数据
    QT_BoardSetupRecGetData = getattr(QueentestDll, "QT_BoardSetupRecGetData")
    QT_BoardSetupRecGetData.unCardIdx = int
    QT_BoardSetupRecGetData.blockNum = int
    QT_BoardSetupRecGetData.Buffer = uptr8
    QT_BoardSetupRecGetData.Bytes = int

    #ADC工作模式
    QT_BoardSetupRecWorkingMode = getattr(QueentestDll, "QT_BoardSetupRecWorkingMode")
    QT_BoardSetupRecWorkingMode.unCardIdx = int
    QT_BoardSetupRecWorkingMode.chMode = int

    #获取板卡量程范围个数
    QT_BoardObtainThechRangeNum = getattr(QueentestDll, "QT_BoardObtainThechRangeNum")

    #获取板卡量程范围
    QT_BoardObtainThechRange = getattr(QueentestDll, "QT_BoardObtainThechRange")

    #读取JSON配置文件
    QT_BoardSetAFEJSON = getattr(QueentestDll, "QT_BoardSetAFEJSON")

    #是否支持有限点单次采集
    QT_BoardIfSupportFiniteSingle = getattr(QueentestDll, "QT_BoardIfSupportFiniteSingle")

    #是否支持有限点多次采集
    QT_BoardIfSupportFiniteMulti = getattr(QueentestDll, "QT_BoardIfSupportFiniteMulti")

    #是否支持无限点单次采集
    QT_BoardIfSupportInfiniteSingle = getattr(QueentestDll, "QT_BoardIfSupportInfiniteSingle")

    #是否支持无限点多次采集
    QT_BoardIfSupportInfiniteMulti = getattr(QueentestDll, "QT_BoardIfSupportInfiniteMulti")

    #是否支持DDS播放
    QT_BoardIfSupportDDSPlay = getattr(QueentestDll, "QT_BoardIfSupportDDSPlay")

    #是否支持外部数据文件播放
    QT_BoardIfSupportFilePlay = getattr(QueentestDll, "QT_BoardIfSupportFilePlay")

    #是否支持ADC通道选择
    QT_BoardIfSupportRecChannelSwitch = getattr(QueentestDll, "QT_BoardIfSupportRecChannelSwitch")

    #是否支持DAC通道选择
    QT_BoardIfSupportRepChannelSwitch = getattr(QueentestDll, "QT_BoardIfSupportRepChannelSwitch")

    #ADC通道选择
    QT_BoardSetupRecChannelMode = getattr(QueentestDll, "QT_BoardSetupRecChannelMode")
    QT_BoardSetupRecChannelMode.unCardIndex = int
    QT_BoardSetupRecChannelMode.chParam = int

    #是否支持时钟：外参考时钟、外采样时钟
    QT_BoardIfSupportClockMode = getattr(QueentestDll, "QT_BoardIfSupportClockMode")

    #是否支持风扇控制
    QT_BoardIfSupportFanControl = getattr(QueentestDll, "QT_BoardIfSupportFanControl")

    #风扇控制
    QT_BoardSetFanControl = getattr(QueentestDll, "QT_BoardSetFanControl")
    QT_BoardSetFanControl.unCardIndex = int
    QT_BoardSetFanControl.controlsource = int
    QT_BoardSetFanControl.fangear = int

    #是否支持模拟前端配置
    QT_BoardIfSupportOffsetAdjust = getattr(QueentestDll, "QT_BoardIfSupportOffsetAdjust")

    #是否是1144VG
    QT_BoardIfSupport1144VG = getattr(QueentestDll, "QT_BoardIfSupport1144VG")

    #QT1144VG模拟前端配置
    QT_BoardConfigureAnalogFrontEndVG = getattr(QueentestDll, "QT_BoardConfigureAnalogFrontEndVG")
    QT_BoardConfigureAnalogFrontEndVG.unCardIndex = int
    QT_BoardConfigureAnalogFrontEndVG.chID = int
    QT_BoardConfigureAnalogFrontEndVG.biasVoltage = int
    QT_BoardConfigureAnalogFrontEndVG.iGainFalloff = int

    #是否使用EEPROM
    QT_BoardIfSupportUseEEPROM = getattr(QueentestDll, "QT_BoardIfSupportUseEEPROM")

    #读取EEPROM
    QT_BoardSetAFEEEPROM = getattr(QueentestDll, "QT_BoardSetAFEEEPROM")
    QT_BoardSetAFEEEPROM.unCardIndex = int
    QT_BoardSetAFEEEPROM.chID = int
    QT_BoardSetAFEEEPROM.chRange = int
    QT_BoardSetAFEEEPROM.offsetValue = object
    QT_BoardSetAFEEEPROM.calibrationValue = object

    #DAC通道选择
    QT_BoardSetupRepChannelMode = getattr(QueentestDll, "QT_BoardSetupRepChannelMode")
    QT_BoardSetupRepChannelMode.unCardIndex = int
    QT_BoardSetupRepChannelMode.chParam = int

    #DAC时钟模式
    QT_BoardSetupRepClockMode = getattr(QueentestDll, "QT_BoardSetupRepClockMode")
    QT_BoardSetupRepClockMode.unCardIndex = int
    QT_BoardSetupRepClockMode.clockMode = int

    #DAC软件触发
    QT_BoardSetupTrigRepSoftware = getattr(QueentestDll, "QT_BoardSetupTrigRepSoftware")
    QT_BoardSetupTrigRepSoftware.unCardIndex = int

    #DAC内部脉冲触发
    QT_BoardSetupTrigRepInternalPulse = getattr(QueentestDll, "QT_BoardSetupTrigRepInternalPulse")
    QT_BoardSetupTrigRepInternalPulse.unCardIndex = int
    QT_BoardSetupTrigRepInternalPulse.pulsePeriod = int
    QT_BoardSetupTrigRepInternalPulse.pulseWidth = int

    #DAC外部脉冲触发
    QT_BoardSetupTrigRepExternal = getattr(QueentestDll, "QT_BoardSetupTrigRepExternal")
    QT_BoardSetupTrigRepExternal.unCardIndex = int
    QT_BoardSetupTrigRepExternal.extMode = int

    #有限点多次触发采集模式
    QT_BoardSetupModeRecStdMulti = getattr(QueentestDll, "QT_BoardSetupModeRecStdMulti")
    QT_BoardSetupModeRecStdMulti.unCardIndex = int
    QT_BoardSetupModeRecStdMulti.blockNum = int
    QT_BoardSetupModeRecStdMulti.segmentB = int
    QT_BoardSetupModeRecStdMulti.segCount = int
    QT_BoardSetupModeRecStdMulti.frameSwitch = int
    QT_BoardSetupModeRecStdMulti.preTrigDots = int

    #无限点单次触发采集模式
    QT_BoardSetupModeRecFIFOSingle = getattr(QueentestDll, "QT_BoardSetupModeRecFIFOSingle")
    QT_BoardSetupModeRecFIFOSingle.unCardIndex = int
    QT_BoardSetupModeRecFIFOSingle.blockNum = int
    QT_BoardSetupModeRecFIFOSingle.segmentMB = int
    QT_BoardSetupModeRecFIFOSingle.frameSwitch = int
    QT_BoardSetupModeRecFIFOSingle.pretrigdots = int

    #无限点模式初始化buffer
    QT_BoardSetInitializeOperation = getattr(QueentestDll, "QT_BoardSetInitializeOperation")
    QT_BoardSetInitializeOperation.unCardIndex = int
    # QT_BoardSetInitializeOperation.filepath = c_char_p
    # QT_BoardSetInitializeOperation.filesize = int

    # 无限点设置文件路径文件大小和文件名
    QT_BoardSetTheFilePathSizeName = getattr(QueentestDll, "QT_BoardSetTheFilePathSizeName")
    QT_BoardSetTheFilePathSizeName.unCardIndex = int
    QT_BoardSetTheFilePathSizeName.blockNum = int
    QT_BoardSetTheFilePathSizeName.filepath = c_char_p
    QT_BoardSetTheFilePathSizeName.filesize = int
    QT_BoardSetTheFilePathSizeName.filename = c_char_p

    #无限点模式释放buffer
    QT_BoardSetFreeOperation = getattr(QueentestDll, "QT_BoardSetInitializeOperation")
    QT_BoardSetFreeOperation.unCardIndex = int

    # 无限点多次触发采集模式
    QT_BoardSetupModeRecFIFOMulti = getattr(QueentestDll, "QT_BoardSetupModeRecFIFOMulti")
    QT_BoardSetupModeRecFIFOMulti.unCardIndex = int
    QT_BoardSetupModeRecFIFOMulti.blockNum = int
    QT_BoardSetupModeRecFIFOMulti.segmentB = int
    QT_BoardSetupModeRecFIFOMulti.frameSwitch = int
    QT_BoardSetupModeRecFIFOMulti.preTrigDots = int
    QT_BoardSetupModeRecFIFOMulti.repetitionFrequency = c_double

    #DDS播放模式
    QT_BoardSetupRepSourceDDS = getattr(QueentestDll, "QT_BoardSetupRepSourceDDS")
    QT_BoardSetupRepSourceDDS.unCardIndex = int
    QT_BoardSetupRepSourceDDS.outFreq = int

    #上位机启动/停止播放DAC数据
    QT_BoardSetupRepPlayData = getattr(QueentestDll, "QT_BoardSetupRepPlayData")
    QT_BoardSetupRepPlayData.unCardIndex = int
    QT_BoardSetupRepPlayData.repSwitch = int

    #外部数据播放是DMA还是DATAMOVE
    QT_BoardIfSupportFilePlaySource = getattr(QueentestDll, "QT_BoardIfSupportFilePlaySource")

    #数据文件播放模式
    QT_BoardSetupRepSourceFileDMA = getattr(QueentestDll, "QT_BoardSetupRepSourceFileDMA")
    QT_BoardSetupRepSourceFileDMA.unCardIndex = int
    QT_BoardSetupRepSourceFileDMA.blockNum = int
    QT_BoardSetupRepSourceFileDMA.loopFlag = int
    QT_BoardSetupRepSourceFileDMA.loopCount = int
    QT_BoardSetupRepSourceFileDMA.strFileName = c_char_p
    QT_BoardSetupRepSourceFileDMA.segmentB = int

    #数据文件播放模式DATAMOVE
    QT_BoardSetupRepSourceFileDatamove = getattr(QueentestDll, "QT_BoardSetupRepSourceFileDatamove")
    QT_BoardSetupRepSourceFileDatamove.unCardIndex = int
    QT_BoardSetupRepSourceFileDatamove.strFileName = c_char_p
    QT_BoardSetupRepSourceFileDatamove.segmentB = int

    #是否是9009
    QT_BoardIfSupport9009Rf = getattr(QueentestDll, "QT_BoardIfSupport9009Rf")

    #切换9009参考源
    QT_BoardSetRefClockMode = getattr(QueentestDll, "QT_BoardSetRefClockMode")
    QT_BoardSetRefClockMode.unCardIndex = int
    QT_BoardSetRefClockMode.refMode = int

    #设置本振9009
    QT_BoardSetUpdateFrequency = getattr(QueentestDll, "QT_BoardSetUpdateFrequency")
    QT_BoardSetUpdateFrequency.unCardIndex = int
    QT_BoardSetUpdateFrequency.freq = int

    #设置采集数据类型9009
    QT_BoardSetRecDataType = getattr(QueentestDll, "QT_BoardSetRecDataType")
    QT_BoardSetRecDataType.unCardIndex = int
    QT_BoardSetRecDataType.datatype = int

    #设置接收数据带宽
    QT_BoardSetRecBandwidth = getattr(QueentestDll, "QT_BoardSetRecBandwidth")
    QT_BoardSetRecBandwidth.unCardIndex = int
    QT_BoardSetRecBandwidth.bandwidth = int

    #修改接收衰减9009
    QT_BoardSetRecAttenuation = getattr(QueentestDll, "QT_BoardSetRecAttenuation")
    QT_BoardSetRecAttenuation.unCardIndex = int
    QT_BoardSetRecAttenuation.attenuation = int

    #设置发射衰减9009
    QT_BoardSetRepAttenuation = getattr(QueentestDll, "QT_BoardSetRepAttenuation")
    QT_BoardSetRepAttenuation.unCardIndex = int
    QT_BoardSetRepAttenuation.attenuation = int

    # 回环模式1 标准模式0 HW
    QT_BoardSetLoopbackOrStandardWorkMode = getattr(QueentestDll, "QT_BoardSetLoopbackOrStandardWorkMode")
    QT_BoardSetLoopbackOrStandardWorkMode.unCardIndex = int
    QT_BoardSetLoopbackOrStandardWorkMode.LoopbackOrStandardWorkMode = int

    # DAC电压调节功能
    QT_BoardVoltageControl = getattr(QueentestDll, "QT_BoardVoltageControl")
    QT_BoardVoltageControl.unCardIndex = int
    QT_BoardVoltageControl.voltageValuei1 = int
    QT_BoardVoltageControl.voltageValueq1 = int
    QT_BoardVoltageControl.voltageValuei2 = int
    QT_BoardVoltageControl.voltageValueq2 = int

    # 配置ADC使能
    QT_BoardSetADCEnable = getattr(QueentestDll, "QT_BoardSetADCEnable")
    QT_BoardSetADCEnable.unCardIndex = int

    # DAC延迟时间
    QT_BoardSetRepPlayDelay = getattr(QueentestDll, "QT_BoardSetRepPlayDelay")
    QT_BoardSetRepPlayDelay.unCardIndex = int
    QT_BoardSetRepPlayDelay.delayTime = c_uint32

    # 光脉冲开关
    QT_BoardSetLightPulsesSwitch = getattr(QueentestDll, "QT_BoardSetLightPulsesSwitch")
    QT_BoardSetLightPulsesSwitch.unCardIndex = int
    QT_BoardSetLightPulsesSwitch.delayTimeDAC = int
    # ADC延迟时间
    QT_BoardSetRecCollectDelay = getattr(QueentestDll, "QT_BoardSetRecCollectDelay")
    QT_BoardSetRecCollectDelay.unCardIndex = int
    QT_BoardSetRecCollectDelay.delayTime = int

    # SOA脉冲设置 HW
    QT_BoardSetSOApulse = getattr(QueentestDll, "QT_BoardSetSOApulse")
    QT_BoardSetSOApulse.unCardIndex = int
    QT_BoardSetSOApulse.pulsePeriod = int
    QT_BoardSetSOApulse.pulseWidth = int

    # 数据文件播放模式(可指定DDR地址)
    QT_BoardSpecifyDDRAddress = getattr(QueentestDll, "QT_BoardSpecifyDDRAddress")
    QT_BoardSpecifyDDRAddress.unCardIndex = int
    QT_BoardSpecifyDDRAddress.blockNum = int
    QT_BoardSpecifyDDRAddress.DDRAddress_l = int
    QT_BoardSpecifyDDRAddress.DDRAddress_h = int

    # 回环模式1，标准模式0
    QT_BoardSetLoopbackOrStandardWorkMode = getattr(QueentestDll, "QT_BoardSetLoopbackOrStandardWorkMode")
    QT_BoardSetLoopbackOrStandardWorkMode.unCardIndex = int
    QT_BoardSetLoopbackOrStandardWorkMode.workMode = int

    # 下发数据
    QT_BoardSetupRepSendData = getattr(QueentestDll, "QT_BoardSetupRepSendData")
    QT_BoardSetupRepSendData.unCardIndex = int
    QT_BoardSetupRepSendData.blockNum = int
    QT_BoardSetupRepSendData.buffer = uptr8
    QT_BoardSetupRepSendData.bytes = int

    # 回环无限点DA播放DMA控制
    QT_BoardSetupRepFifoDMACtrlLoopPlay = getattr(QueentestDll, "QT_BoardSetupRepFifoDMACtrlLoopPlay")
    QT_BoardSetupRepFifoDMACtrlLoopPlay.unCardIndex = int
    QT_BoardSetupRepFifoDMACtrlLoopPlay.blockNum = int
    QT_BoardSetupRepFifoDMACtrlLoopPlay.segmentB = int

    #回环数据文件播放模式
    QT_BoardSetupRepSourceFileDMALoopPlay = getattr(QueentestDll, "QT_BoardSetupRepSourceFileDMALoopPlay")
    QT_BoardSetupRepSourceFileDMALoopPlay.unCardIndex = int
    QT_BoardSetupRepSourceFileDMALoopPlay.blockNum = int
    QT_BoardSetupRepSourceFileDMALoopPlay.loopFlag = int
    QT_BoardSetupRepSourceFileDMALoopPlay.loopCount = int
    QT_BoardSetupRepSourceFileDMALoopPlay.strFileName = c_char_p
    QT_BoardSetupRepSourceFileDMALoopPlay.segmentB = int



elif os.name == 'posix':
    sys.stdout.write("Linux found which is currently not supported by pyQueentest")

else:
    raise Exception('Operating system not supported by pyQueentest')

#
# **************************************************************************
# ChkRT: check return value. Print error in stdout then exit
# **************************************************************************
#


def QTChkRT(RTVal):
    if RTVal != 0:
        sys.stdout.write("Return with ERROR...\n")
        exit()
    else:
        return


