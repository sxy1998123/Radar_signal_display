#ifndef _QT_BOARD_PROJECT_H
#define _QT_BOARD_PROJECT_H

#include <stdint.h>
#include <Windows.h>

#define QT_BOARD_PROJECT_API_EXPORTS
#ifdef QT_BOARD_PROJECT_API_EXPORTS
#define QT_BOARD_PROJECT_API __declspec(dllexport)
#else
#define QT_BOARD_PROJECT_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

	//L波段开始等待触发事件
	QT_BOARD_PROJECT_API int QT_BoardLStartWaittingForIntr(unsigned int unCardIndex);

	//L波段ADC采样率/带宽切换
	QT_BOARD_PROJECT_API int QT_BoardLRecSamplerateSwitching(unsigned int unCardIndex, int sampleRate);

	//L波段DAC采样率/带宽切换
	QT_BOARD_PROJECT_API int QT_BoardLRepSamplerateSwitching(unsigned int unCardIndex, int sampleRate);

	//L波段射频控制字计算
	QT_BOARD_PROJECT_API int QT_BoardLFreqNcoParamCalc(unsigned int unCardIndex, uint32_t rfFreqMhz, uint32_t *pFreqCtrlWord, uint32_t *pNcoFreqMHz);

	//L波段通道射频输入控制
	QT_BOARD_PROJECT_API int QT_BoardLChannelControl(unsigned int unCardIndex, int chID, uint32_t gain_mode, uint32_t rf_DampValue, uint32_t mid_DampValue, uint32_t freqControlWord);

	//L波段DMA参数设置
	QT_BOARD_PROJECT_API int QT_BoardLSetDMAParameters(unsigned int unCardIndex);

	//L波段通道中心频率计算NCO控制字
	QT_BOARD_PROJECT_API int QT_BoardLSetNCOControlWord(unsigned int unCardIndex, double dbCentFreqMHz);

	//L波段ADC DDS设置
	QT_BOARD_PROJECT_API int QT_BoardLSetRecDDSConfig(unsigned int unCardIndex, int chID, double freqControl);

	//流盘定时设置
	QT_BOARD_PROJECT_API int QT_BoardFlowMeterTimer(unsigned int unCardIndex, char hour_min_Start[256], char seconds_Start[256], char hour_min_Stop[256], char seconds_Stop[256]);

	//是否开启定时流盘
	QT_BOARD_PROJECT_API int QT_BoardTimedFlowEnable(unsigned int unCardIndex, int eEnable);

	//时间信息
	QT_BOARD_PROJECT_API int QT_BoardGetTimeInformation(unsigned int unCardIndex, char* ascii_array);

	//GPS是否有效
	QT_BOARD_PROJECT_API int QT_BoardGetIsGPSEffective(unsigned int unCardIndex);

	//DDC NCO使能
	QT_BOARD_PROJECT_API int QT_BoardTimedFlowDDCNCOEnable(unsigned int unCardIndex);

	//延时触发打开期间外部触发总数
	QT_BOARD_PROJECT_API int QT_BoardTotalExternalTriggers(unsigned int unCardIndex);

	//DDC抽取率2倍抽取
	QT_BOARD_PROJECT_API int QT_BoardSetDDC2xExtractionRate(unsigned int unCardIndex, int enable);

	//设置DDC抽取率
	QT_BOARD_PROJECT_API int QT_BoardSetDDCExtractionRate(unsigned int unCardIndex, uint32_t ddcSampleRateSel);

	//QT1426复位
	QT_BOARD_PROJECT_API int QT_BoardSetResetBeforeStart(unsigned int unCardIndex);

	//QT1426模式选择
	QT_BOARD_PROJECT_API int QT_BoardSetDataMode(unsigned int unCardIndex, uint32_t dataMode);

	//发送复位和接收复位
	QT_BOARD_PROJECT_API int QT_BoardFiberInterfaceReset(unsigned int unCardIndex, int direction);

	//QT1426光纤连接是否正常
	QT_BOARD_PROJECT_API int QT_BoardFiberConnections(unsigned int unCardIndex);

	//RFSOC获取板卡信息
	QT_BOARD_PROJECT_API int QT_BoardGetCardStatesRFSOC(unsigned int unCardIndex);

	//RFSOC执行光纤接口复位
	QT_BOARD_PROJECT_API int QT_BoardFiberInterfaceResetRFSOC(unsigned int unCardIndex);

	//RFSOC清除中断
	QT_BOARD_PROJECT_API int QT_BoardClearInterruptRFSOC(unsigned int unCardIndex);

	//RFSOC停止工作
	QT_BOARD_PROJECT_API int QT_BoardStopWorkRFSOC(unsigned int unCardIndex);

	//RFSOC设置板卡参考时钟模式(0:内参考 1:外参考)
	QT_BOARD_PROJECT_API int QT_BoardSetClockModeRFSOC(unsigned int unCardIndex, int clockMode);

	//RFSOC执行板卡初始化
	QT_BOARD_PROJECT_API int QT_BoardInitializeBoardRFSOC(unsigned int unCardIndex);

	//RFSOC设置数据流路径(默认写0即可)
	QT_BOARD_PROJECT_API int QT_BoardSetDataFlowPathRFSOC(unsigned int unCardIndex, int dataFlowPath);

	//RFSOC设置数据流速率(默认写0即可)
	QT_BOARD_PROJECT_API int QT_BoardSetDataFlowRateRFSOC(unsigned int unCardIndex, int dataFlowRate);

	//RFSOC采集数据模式选择(0:模拟数据 1:内回环 2:累加数  3:棋盘数据)
	QT_BOARD_PROJECT_API int QT_BoardSetDataCollectModeRFSOC(unsigned int unCardIndex, int dataCollectMode);

	//RFSOC播放数据模式选择(0:模拟数据 1:外回环 2:DDS数据 3:ROM数据)
	QT_BOARD_PROJECT_API int QT_BoardSetDataPlayModeRFSOC(unsigned int unCardIndex, int dataPlayMode);

	//RFSOCDDS频率控制字相位控制字
	QT_BOARD_PROJECT_API int QT_BoardSetDDSControlWordRFSOC(unsigned int unCardIndex, int freq);

	//RFSOC发射触发滑动延时
	QT_BOARD_PROJECT_API int QT_BoardSetRepSlideDelayTriggeredRFSOC(unsigned int unCardIndex, int delayTime);

	//RFSOC接收触发滑动延时
	QT_BOARD_PROJECT_API int QT_BoardSetReclideDelayTriggeredRFSOC(unsigned int unCardIndex, int delayTime);

	//RFSOC中断时间(单位毫秒)
	QT_BOARD_PROJECT_API int QT_BoardSetInterruptTimeRFSOC(unsigned int unCardIndex, int interruptTime);

	//RFSOC开始工作
	QT_BOARD_PROJECT_API int QT_BoardStartWorkRFSOC(unsigned int unCardIndex);

	//RFSOC采集模式设置
	QT_BOARD_PROJECT_API int QT_BoardSetAcquisitionMode(unsigned int unCardIndex, int mode, uint32_t segmentB);

	//LRU直通和变频模式切换 00代表直通模式  01代表变频模式
	QT_BOARD_PROJECT_API int QT_BoardCutthroughAndInverterModeSwitchingLRU(unsigned int unCardIndex, int mode);

	//LRU直通衰减控制
	QT_BOARD_PROJECT_API int QT_BoardCutthroughAttenuationControlLRU(unsigned int unCardIndex, int attenuation);

	//LRU频率控制
	QT_BOARD_PROJECT_API int QT_BoardFrequencyControlLRU(unsigned int unCardIndex, int frequency);

	//LRU校准衰减控制1
	QT_BOARD_PROJECT_API int QT_BoardCalibrationAttenuationControl1LRU(unsigned int unCardIndex, int attenuation);

	//LRU校准衰减控制2
	QT_BOARD_PROJECT_API int QT_BoardCalibrationAttenuationControl2LRU(unsigned int unCardIndex, double attenuation);

	//LRU常规和低噪声模式切换
	QT_BOARD_PROJECT_API int QT_BoardRegularAndLownoiseModeSwitchingLRU(unsigned int unCardIndex, int mode);

	//LRU配置使能
	QT_BOARD_PROJECT_API int QT_BoardEnableTheConfigurationLRU(unsigned int unCardIndex);

	//LRU唤醒使能
	QT_BOARD_PROJECT_API int QT_BoardWakeUpEnabledLRU(unsigned int unCardIndex, int chID);

	//LRU休眠状态获取
	QT_BOARD_PROJECT_API int QT_BoardHibernateReadsLRU(unsigned int unCardIndex, int chID);

	//LRUDAC输出幅度
	QT_BOARD_PROJECT_API int QT_BoardSetDACOutputAmplitudeLRU(unsigned int unCardIndex, int outputAmplitude);

	//LRU增益与偏置控制
	QT_BOARD_PROJECT_API int QT_BoardSetGainandBiasControlLRU(unsigned int unCardIndex, int order, uint32_t gain, uint32_t bias);

	//LRU抽取倍数控制
	QT_BOARD_PROJECT_API int QT_BoardSetExtractMultipleControlLRU(unsigned int unCardIndex, int order, int extractMultiple);

	//LRU包间隔
	QT_BOARD_PROJECT_API int QT_BoardPacketIntervalsLRU(unsigned int unCardIndex, int intervals);

	//LRUDNA功能
	QT_BOARD_PROJECT_API int QT_BoardObtainDNAInfoLRU(unsigned int unCardIndex, uint32_t * infoDNA);

	//LRU单次触发数据长度
	QT_BOARD_PROJECT_API int QT_BoardSetDataLengthLRU(unsigned int unCardIndex, int dataID, uint32_t dataLen);

	//LRU休眠使能
	QT_BOARD_PROJECT_API int QT_BoardDormancyEnabledLRU(unsigned int unCardIndex, int chID);

	//LRU射频频谱翻转使能
	QT_BOARD_PROJECT_API int QT_BoardSpectrumFlipEnableLRU(unsigned int unCardIndex, int order);

	//LRU射频下发DDS频率
	QT_BOARD_PROJECT_API int QT_BoardDistributeDDSFrequencyLRU(unsigned int unCardIndex, uint32_t phasefreq, uint32_t phaseoffse);

	//BRAM
	QT_BOARD_PROJECT_API int QT_BoardRepBRAMSendData(unsigned int unCardIndex, int fileCnt, int length, char *strFileName, int groupAddr);

	//BRAM
	QT_BOARD_PROJECT_API int QT_BoardRepBRAMSendDataLength(unsigned int unCardIndex, int length, char *strFileName);

	//BRAM或DDR
	QT_BOARD_PROJECT_API int QT_BoardRepBRAMEitherOrDDR(unsigned int unCardIndex, int param);

	//PWM
	QT_BOARD_PROJECT_API int QT_BoardPWMOutputSettings(unsigned int unCardIndex, int outFreq, int PulseWidth);

	//上传数据选择
	QT_BOARD_PROJECT_API int QT_BoardUploadDataSelection(unsigned int unCardIndex, int dataMode);
	
	//DDC控制字
	QT_BOARD_PROJECT_API int QT_BoardSetDDCControlWord(unsigned int unCardIndex, int chID, int freqMhz);

	//DAC电压调节功能
	QT_BOARD_PROJECT_API int QT_BoardVoltageControl(unsigned int unCardIndex, int voltageValuei1, int voltageValueq1, int voltageValuei2, int voltageValueq2);

	//万兆网12509累加数模式
	QT_BOARD_PROJECT_API int QT_BoardSetCumulativAdditionMode(unsigned int unCardIndex, int mode);

	//Aurora UFC功能 DDS(NCO)
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCNCODDS(unsigned int unCardIndex, int freqKHz);

	//Aurora UFC功能 DDC模式切换
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCDDCMode(unsigned int unCardIndex, int DDCMode);

	//Aurora UFC功能 数据模式切换
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCDataMode(unsigned int unCardIndex, int dataMode);

	//Aurora UFC功能 衰减器控制
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCAttenuatorControl(unsigned int unCardIndex, int attenuator, double attValuedB);

	//Aurora UFC功能 时钟锁定状态
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCClockStatus(unsigned int unCardIndex);

	//Aurora UFC功能 溢出状态计数器
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCOverflowCnt(unsigned int unCardIndex);

	//Aurora UFC功能 数据流量监测
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCDatatrafficMonitoring(unsigned int unCardIndex);

	//Aurora UFC功能 光纤顺序控制接口
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraOrder(unsigned int unCardIndex, int order);

	//Aurora UFC功能 时钟模式
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCClockMode(unsigned int unCardIndex, int clockMode);

	//Aurora UFC功能 用于文件名的频点卫星编号
	QT_BOARD_PROJECT_API int QT_BoardSetAuroraUFCFrequencypointSatellitenumber(unsigned int unCardIndex, char* pindian, char* weixingbianhao);

	//Aurora UFC功能 采集时长 单位:S
	QT_BOARD_PROJECT_API int QT_BoardSetCollectionDuration(unsigned int unCardIndex, uint64_t duration);

	//有限点单次采集模式JLDX
	QT_BOARD_PROJECT_API int QT_BoardSetupModeRecStdSingleJldx(unsigned int unCardIndex, int blockNum, uint32_t OnceBytes, uint32_t TotalBytes, uint32_t frameSwitch, uint32_t preTrigDots);

	//有限点多次采集模式JLDX
	QT_BOARD_PROJECT_API int QT_BoardSetupModeRecStdMultiJldx(unsigned int unCardIndex, int blockNum, uint32_t OnceBytes, uint32_t TotalBytes, uint32_t segCount, uint32_t frameSwitch, uint32_t preTrigDots);

	//无限点多次采集模式JLDX
	QT_BOARD_PROJECT_API int QT_BoardSetupModeRecFIFOMultiJldx(unsigned int unCardIndex, int blockNum, uint32_t OnceBytes, uint32_t TotalBytes, uint32_t frameSwitch, uint32_t preTrigDots, double repetitionFrequency);

	//数据源切换JLDX
	QT_BOARD_PROJECT_API int QT_BoardSetupDataSourceSwitchingJldx(unsigned int unCardIndex, int dataSource);

	//获取数据QQNY64
	QT_BOARD_PROJECT_API int QT_BoardSetupRecGetDataQqny(unsigned int unCardIndex, int blockNum, uint64_t offset, uint8_t *buffer, uint32_t bytes);

	//获取数据QQNY32
	QT_BOARD_PROJECT_API int QT_BoardSetupRecGetDataQqny32(unsigned int unCardIndex, int blockNum, uint32_t offset_low, uint32_t offset_high, uint8_t *buffer, uint32_t bytes);

	//SOA脉冲设置
	QT_BOARD_PROJECT_API int QT_BoardSetSOApulse(unsigned int unCardIndex, int pulsePeriod, int pulseWidth);

	//基于有限点多次采集时域累加模式
	QT_BOARD_PROJECT_API int QT_BoardSetTimeDomainAccumulationMode(unsigned int unCardIndex, int accEnable, int accNum, int accLen);

	//文件重命名 ZKY
	QT_BOARD_PROJECT_API int QT_BoardRenameFileOperation(char * srcFilPath);

	//累加平均FFT ZKY
	QT_BOARD_PROJECT_API int QT_BoardAccumulatedAverageFFT(unsigned int unCardIndex, char * srcFilPath, char * desFilePath, int point, int flag);

	//采集数据模式 ZSDX
	QT_BOARD_PROJECT_API int QT_BoardSetDataCollectionMode(unsigned int unCardIndex, int dataMode);

	//FFT寻峰起始点结束点 ZSDX
	QT_BOARD_PROJECT_API int QT_BoardSetFFTPeakFindingStartingandEndingPoints(unsigned int unCardIndex, uint32_t startingPoint, uint32_t endingPoint);

	//三角波周期和幅度 ZSDX
	QT_BOARD_PROJECT_API int QT_BoardSetPeriodandAmplitude(unsigned int unCardIndex, uint32_t period, uint32_t amplitude);

	//触发延时 ZSDX
	QT_BOARD_PROJECT_API int QT_BoardSetTriggerDelay(unsigned int unCardIndex, uint32_t delayTime);

	//光纤数据接口选择
	QT_BOARD_PROJECT_API int QT_BoardSetFiberOpticDataInterface(unsigned int unCardIndex, int interfaceMode);

	//采集板开始采集/停止采集
	QT_BOARD_PROJECT_API int QT_BoardSetAcquisitionBoardCollect(unsigned int unCardIndex, int recSwitch);

	//获取采集板板卡信息
	QT_BOARD_PROJECT_API int QT_BoardGetAcquisitionBoardType(unsigned int unCardIndex);

	//获取采集板软件版本
	QT_BOARD_PROJECT_API int QT_BoardGetAcquisitionBoardSoftVersion(unsigned int unCardIndex);

	//光开关脉冲
	QT_BOARD_PROJECT_API int QT_BoardSetLightPulsesSwitch(unsigned int unCardIndex, uint32_t param);

	//数据文件播放模式(可指定DDR地址)
	QT_BOARD_PROJECT_API int QT_BoardSpecifyDDRAddress(unsigned int unCardIndex, int blockNum, uint32_t DDRAddress_l, uint32_t DDRAddress_h);

	//采集模式DMA单次搬运数据量（可指定）
	QT_BOARD_PROJECT_API int QT_BoardSpecifyRecDMASingleSize(unsigned int unCardIndex, int blockNum, uint32_t singleVolume);

	//播放模式DMA单次搬运数据量（可指定）
	QT_BOARD_PROJECT_API int QT_BoardSpecifyRepDMASingleSize(unsigned int unCardIndex, int blockNum, uint32_t singleVolume);

	//超时跳出功能
	QT_BOARD_PROJECT_API int QT_BoardSetTimeoutBounceFunction(unsigned int unCardIndex, uint32_t timeOutns);

	//DDS数据幅值衰减
	QT_BOARD_PROJECT_API int QT_BoardSetDDSAmplitudeAttenuation(unsigned int unCardIndex, uint32_t attenuation);

	//设置数据类型
	QT_BOARD_PROJECT_API int QT_BoardSetTheDataType(unsigned int unCardIndex, int dataType);

	//下变频频率控制
	QT_BOARD_PROJECT_API int QT_BoardDownConversionFrequencyControl(unsigned int unCardIndex, uint16_t frequencyData, int delayTime0us, int delayTime1us);

	//下变频变频衰减控制
	QT_BOARD_PROJECT_API int QT_BoardDownConversionFrequencyAttenuationControl(unsigned int unCardIndex, uint8_t attenuationData, int delayTime0us, int delayTime1us);

	//下变频直通衰减控制
	QT_BOARD_PROJECT_API int QT_BoardDownConversionDirectAttenuationControl(unsigned int unCardIndex, uint8_t attenuationData, int delayTime0us, int delayTime1us);

	//上变频频率控制
	QT_BOARD_PROJECT_API int QT_BoardUpConversionFrequencyControl(unsigned int unCardIndex, uint16_t frequencyData, int delayTime0us, int delayTime1us);

	//上变频变频衰减控制
	QT_BOARD_PROJECT_API int QT_BoardUpConversionFrequencyAttenuationControl(unsigned int unCardIndex, uint8_t attenuationData, int delayTime0us, int delayTime1us);

	//上变频直通衰减控制
	QT_BOARD_PROJECT_API int QT_BoardUpConversionDirectAttenuationControl(unsigned int unCardIndex, uint8_t attenuationData, int delayTime0us, int delayTime1us);

	//抽取倍数控制
	QT_BOARD_PROJECT_API int QT_BoardSetTheExtractionMultiple(unsigned int unCardIndex, int extractMultiple);

	//高精度外触发软件旁路功能
	QT_BOARD_PROJECT_API int QT_BoardSetSoftwareBypassFunction(unsigned int unCardIndex, int order);

	//ADC通道状态监控
	QT_BOARD_PROJECT_API int QT_BoardADCChannelStatusMonitoring(unsigned int unCardIndex, int chID);

	//ADC通道状态清除
	QT_BOARD_PROJECT_API int QT_BoardClearADCChannelStatus(unsigned int unCardIndex);

	//ADC通道衰减控制
	QT_BOARD_PROJECT_API int QT_BoardADCChannelAttenuationControl(unsigned int unCardIndex, int chID, uint32_t DSACODE);

	//TTL测试
	QT_BOARD_PROJECT_API int QT_BoardSetTTLTest(unsigned int unCardIndex, int order);

	//TTL输出测试脉冲宽度和脉冲频率
	QT_BOARD_PROJECT_API int QT_BoardSetTTLPulseWidthAndFrequency(unsigned int unCardIndex, uint32_t width, uint32_t frequence);

	//TTL测试输入通道选择
	QT_BOARD_PROJECT_API int QT_BoardSetTTLInputChannelSelection(unsigned int unCardIndex, int chID);

	//TTL测试输入频率
	QT_BOARD_PROJECT_API int QT_BoardSetTTLInputFrequency(unsigned int unCardIndex, uint32_t * freqHz);

	//获取中断bit位
	QT_BOARD_PROJECT_API int QT_BoardGetInterruptBit(unsigned int unCardIndex);

	//光纤接口UFC控制
	QT_BOARD_PROJECT_API int QT_BoardSetFiberOpticUFCControl(unsigned int unCardIndex, int chID, int sendMode);

	//BRAM下发数据NBLHGZ
	QT_BOARD_PROJECT_API int QT_BoardDistributeDataThroughBRAM(unsigned int unCardIndex, int chID, const char * fileName);

	//频谱反折
	QT_BOARD_PROJECT_API int QT_BoardSetSpectrumInversion(unsigned int unCardIndex, int order);

	//直流滤波器
	QT_BOARD_PROJECT_API int QT_BoardSetDCFilter(unsigned int unCardIndex, int order);

#ifdef __cplusplus
}

#endif

#endif