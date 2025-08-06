#ifndef _QT_BOARD_PRODUCT_H
#ifndef _QT_BOARD_PRODUCT_H

#include <stdint.h>
#include <Windows.h>

#define QT_BOARD_PRODUCT_API_EXPORTS
#ifdef QT_BOARD_PRODUCT_API_EXPORTS
#define QT_BOARD_PRODUCT_API __declspec(dllexport)
#else
#define QT_BOARD_PRODUCT_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

	//千兆网设置IP
	QT_BOARD_PRODUCT_API int QT_BoardSetGbNetIP(unsigned int unCardIndex, void * IPAddress);

	//打开板卡
	QT_BOARD_PRODUCT_API int QT_BoardOpenBoard(unsigned int unCardIndex);

	//关闭板卡
	QT_BOARD_PRODUCT_API int QT_BoardCloseBoard(unsigned int unCardIndex);

	//获取SDK版本号
	QT_BOARD_PRODUCT_API int QT_BoardGetSDKVersion(char * ver);

	//获取板卡型号
	QT_BOARD_PRODUCT_API int QT_BoardGetCardType(unsigned int unCardIndex);

	//获取板卡固件版本号
	QT_BOARD_PRODUCT_API int QT_BoardGetCardSoftVersion(unsigned int unCardIndex);

	//获取板卡ADC采样率信息
	QT_BOARD_PRODUCT_API int QT_BoardGetCardADCSamplerate(unsigned int unCardIndex);

	//获取板卡ADC通道数信息
	QT_BOARD_PRODUCT_API int QT_BoardGetCardADCChNumbers(unsigned int unCardIndex);

	//获取板卡ADC分辨率信息
	QT_BOARD_PRODUCT_API int QT_BoardGetCardADCResolution(unsigned int unCardIndex);

	//获取板卡DAC采样率信息
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDACSamplerate(unsigned int unCardIndex);

	//获取板卡DAC通道数信息
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDACChNumbers(unsigned int unCardIndex);

	//获取板卡DAC分辨率信息
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDACResolution(unsigned int unCardIndex);

	//获取板卡状态值
	QT_BOARD_PRODUCT_API int QT_BoardGetCardStatus(unsigned int unCardIndex);

	//获取板卡耦合方式
	QT_BOARD_PRODUCT_API int QT_BoardGetCardCouplingMode(unsigned int unCardIndex, char* str);

	//获取板卡形式
	QT_BOARD_PRODUCT_API int QT_BoardGetCardForm(unsigned int unCardIndex, char* str);

	//获取板卡AD/DA
	QT_BOARD_PRODUCT_API int QT_BoardGetCardRecToRep(unsigned int unCardIndex, char* str);

	//获取板卡DMA数量
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDMACounts(unsigned int unCardIndex);

	//获取板卡产品型号
	QT_BOARD_PRODUCT_API int QT_BoardGetProductType(unsigned int unCardIndex, char* str);

	//获取设备个数
	QT_BOARD_PRODUCT_API int QT_BoardGetDeviceCnt();

	//获取设备ID
	QT_BOARD_PRODUCT_API int QT_BoardGetDeviceID(int deviceCnt, char* deviceID);

	//写EEPROM 32bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM32Write(unsigned int unCardIndex, uint32_t offsetaddr, uint32_t value);

	//写EEPROM 8bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM8Write(unsigned int unCardIndex, uint32_t offsetaddr, uint8_t value);

	//写EEPROM 16bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM16Write(unsigned int unCardIndex, uint32_t offsetaddr, uint16_t value);

	//写EEPROM char
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM4Write(unsigned int unCardIndex, uint32_t offsetaddr, char* value);

	//读EEPROM 8bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM8Read(unsigned int unCardIndex, uint32_t offsetaddr, uint8_t *value);

	//千兆网数据发送
	QT_BOARD_PRODUCT_API int QT_BoardDataSendFlash(unsigned int unCardIndex, char *filename);

	//千兆网发送开始固化指令
	QT_BOARD_PRODUCT_API int QT_BoardStartProgramFlash(unsigned int unCardIndex);

	//千兆网flash信息下发//cancel
	QT_BOARD_PRODUCT_API int QT_BoardFlashCalculateInfo(unsigned int unCardIndex, char* buffer, long size, uint32_t cnt);

	//千兆网flash读写操作//cancel
	QT_BOARD_PRODUCT_API int QT_BoardFlashCalOperate(unsigned int unCardIndex, uint32_t cmdhead, uint32_t operate, uint32_t cnt, long size, char *recv);

	//千兆网flash读写
	QT_BOARD_PRODUCT_API int QT_BoardFlashReadAndWriteOperations(unsigned int unCardIndex, const char* filename, uint32_t optCode);

	//千兆网设置下位机日志输出级别
	QT_BOARD_PRODUCT_API int QT_BoardSetLogLevelOfLower(unsigned int unCardIndex, uint32_t logLevel);

	//获取板卡量程范围
	QT_BOARD_PRODUCT_API int QT_BoardObtainThechRange(unsigned int unCardIndex, int chRange);

	//获取板卡量程范围个数
	QT_BOARD_PRODUCT_API int QT_BoardObtainThechRangeNum(unsigned int unCardIndex);

	//获取板卡ADC DMA个数
	QT_BOARD_PRODUCT_API int QT_BoardObtainTheADCBlockNum(unsigned int unCardIndex);

	//获取板卡DAC DMA个数
	QT_BOARD_PRODUCT_API int QT_BoardObtainTheDACBlockNum(unsigned int unCardIndex);

	//是否支持时钟：外参考时钟、外采样时钟
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportClockMode(unsigned int unCardIndex);

	//是否支持ADC通道选择
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportRecChannelSwitch(unsigned int unCardIndex);

	//是否支持DAC通道选择
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportRepChannelSwitch(unsigned int unCardIndex);

	//是否支持无限点单次采集
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportInfiniteSingle(unsigned int unCardIndex);

	//是否支持无限点多次采集
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportInfiniteMulti(unsigned int unCardIndex);

	//是否支持有限点单次采集
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFiniteSingle(unsigned int unCardIndex);

	//是否支持有限点多次采集
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFiniteMulti(unsigned int unCardIndex);

	//是否支持DDS播放
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportDDSPlay(unsigned int unCardIndex);

	//是否支持外部数据文件播放
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFilePlay(unsigned int unCardIndex);

	//外部数据播放是DMA还是DATAMOVE
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFilePlaySource(unsigned int unCardIndex);

	//是否支持模拟前端配置
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportOffsetAdjust(unsigned int unCardIndex);

	//是否支持风扇控制
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFanControl(unsigned int unCardIndex);

	//是否是9009
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport9009Rf(unsigned int unCardIndex);

	//是否是QT1144VG
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport1144VG(unsigned int unCardIndex);

	//是否是QT1140
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport1140(unsigned int unCardIndex);

	//是否是QT1149带有基线校准、直流校准功能
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport1149NonStandard(unsigned int unCardIndex);

	//是否使用EEPROM
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportUseEEPROM(unsigned int unCardIndex);

	//是否支持DA流模式播放
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportRepStreamPlay(unsigned int unCardIndex);

	//buffer 8bit转16bit
	QT_BOARD_PRODUCT_API int QT_Board_Buff_BIT8_TO_BIT16(uint8_t buffer_8bit, uint16_t buffer_16bit, bool isSignal);

	//buffer 10bit转16bit
	QT_BOARD_PRODUCT_API int QT_Board_Buff_BIT10_TO_BIT16(uint8_t buffer_10bit[5], uint16_t buffer_16bit[4], bool isSignal);

	//buffer 12bit转16bit
	QT_BOARD_PRODUCT_API int QT_Board_Buff_BIT12_TO_BIT16(uint8_t buffer_12bit[3], uint16_t buffer_16bit[2], bool isSignal);

	//文件 8bit转16bit
	QT_BOARD_PRODUCT_API int QT_Board_File_BIT8_TO_BIT16(char *src8bitFilename, char *dst16bitFilename, bool isSignal);

	//文件 10bit转16bit
	QT_BOARD_PRODUCT_API int QT_Board_File_BIT10_TO_BIT16(char *src10bitFilename, char *dst16bitFilename, bool isSignal);

	//文件 12bit转16bit
	QT_BOARD_PRODUCT_API int QT_Board_File_BIT12_TO_BIT16(char *src12bitFilename, char *dst16bitFilename, bool isSignal);

	//配置ADC使能
	QT_BOARD_PRODUCT_API int QT_BoardSetADCEnable(unsigned int unCardIndex);

	//配置DAC使能
	QT_BOARD_PRODUCT_API int QT_BoardSetDACEnable(unsigned int unCardIndex);

	//软件复位
	QT_BOARD_PRODUCT_API int QT_BoardSetSoftwareReset(unsigned int unCardIndex, int direction);

	//PCIe中断使能
	QT_BOARD_PRODUCT_API int QT_BoardSetIntrControl(unsigned int unCardIndex, int intrCtrl);

	//风扇控制
	QT_BOARD_PRODUCT_API int QT_BoardSetFanControl(unsigned int unCardIndex, int controlsource, int fangear);

	//ADC时钟模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecClockMode(unsigned int unCardIndex, int clockMode);

	//ADC软件触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecSoftware(unsigned int unCardIndex);

	//ADC软件触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecSoftwareRe(unsigned int unCardIndex, int blockNum);

	//ADC外部脉冲触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecExternal(unsigned int unCardIndex, int extMode, uint32_t trigDelay, double biasvoltage);

	//ADC外部脉冲触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecExternalRe(unsigned int unCardIndex, int blockNum, int extMode, uint32_t trigDelay, double biasvoltage);

	//ADC通道触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecChannel(unsigned int unCardIndex, int trigMode, int channel, int hysteresis, int trigLevel);

	//ADC通道触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecChannelRe(unsigned int unCardIndex, int blockNum, int trigMode, int channel, int hysteresis, int trigLevel);

	//ADC内部脉冲触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecInternalPulse(unsigned int unCardIndex, int pulsePeriod, int pulseWidth);

	//ADC内部脉冲触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecInternalPulseRe(unsigned int unCardIndex, int blockNum, int pulsePeriod, int pulseWidth);

	//ADC采样率设置
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecSamplerate(unsigned int unCardIndex, uint32_t sampleRate);

	//ADC工作模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecWorkingMode(unsigned int unCardIndex, int chMode);

	//通道选择延时  确认之后删除
	QT_BOARD_PRODUCT_API int QT_BoardSetRecChannelModeDelayTime(unsigned int unCardIndex, int delayTime0us, int delayTime1us);

	//ADC通道选择
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecChannelMode(unsigned int unCardIndex, int chParam);

	//AD采集延迟时间
	QT_BOARD_PRODUCT_API int QT_BoardSetRecCollectDelay(unsigned int unCardIndex, uint32_t delayTime);

	//模拟前端调节读取EEPROM
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEEEPROM(unsigned int unCardIndex, int chID, int chRange, uint32_t * offsetValue, double * calibrationValue);

	//模拟前端调节读取JSON配置文件
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEJSON(unsigned int unCardIndex, int chID, int chRange);

	//模拟前端偏置调节
	QT_BOARD_PRODUCT_API int QT_BoardSetBiasAdjustment(unsigned int unCardIndex, int chID, uint32_t bias);

	//模拟前端增益调节
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEGain(unsigned int unCardIndex, int chID, int gainValue);

	//模拟前端衰减调节
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEAttenuation(unsigned int unCardIndex, int chID, int attenuationValue);

	//QT1144VG模拟前端配置
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEndVG(unsigned int unCardIndex, int chID, double biasVoltage, int iGainFalloff);

	//QT1144VG模拟前端配置20250307
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEndVGRe(unsigned int unCardIndex, int chID, double biasVoltage, int range);

	//QT1140模拟前端配置
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEnd(unsigned int unCardIndex, int chID, int biasVoltage, int position);

	//QT1140模拟前端配置20250307
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEndRe(unsigned int unCardIndex, double biasVoltagech0, double biasVoltagech1, int rangech0, int rangech1);

	//有限点单次采集模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecStdSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//有限点多次采集模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecStdMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t segCount, uint32_t frameSwitch, uint32_t preTrigDots);

	//无限点单次采集模式MB
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecFIFOSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentMB, uint32_t frameSwitch, uint32_t pretrigdots);

	//无限点单次采集模式B
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecFIFOSingleB(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t pretrigdots);

	//无限点多次采集模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecFIFOMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots, double repetitionFrequency);

	//无限点模式设置文件文件路径文件大小文件名
	QT_BOARD_PRODUCT_API int QT_BoardSetTheFilePathSizeName(unsigned int unCardIndex, int blockNum, char *filepath, uint64_t filesize, const char *filename);

	//无限点模式初始化buffer
	QT_BOARD_PRODUCT_API int QT_BoardSetInitializeOperation(unsigned int unCardIndex);

	//无限点模式释放buffer
	QT_BOARD_PRODUCT_API int QT_BoardSetFreeOperation(unsigned int unCardIndex);

	//无限点模式获取内存中的数据
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBuffer(unsigned int unCardIndex, unsigned char * buffer, int bufferSize, int timeOutms);

	//无限点模式获取内存中的数据20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferExtend(unsigned int unCardIndex, int blockNum, unsigned char * buffer, int bufferSize, int timeOutms);

	//无限点模式获取内存中的数据指针
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferPointer(unsigned int unCardIndex, unsigned char ** buffer, int bufferSize, int timeOutms);

	//无限点模式获取内存中的数据指针20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferPointerExtend(unsigned int unCardIndex, int blockNum, unsigned char ** buffer, int bufferSize, int timeOutms);

	//无限点模式释放内存中的数据指针
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBufferPointer(unsigned int unCardIndex, unsigned char ** buffer, int bufferSize);

	//无限点模式释放内存中的数据指针20250411
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBufferPointerExtend(unsigned int unCardIndex, int blockNum, unsigned char ** buffer, int bufferSize);

	//开辟内存SPEC
	QT_BOARD_PRODUCT_API unsigned char * QT_BoardAllocBuffer(unsigned int unCardIndex, int bufferSize);

	//开辟内存SPEC20250411
	QT_BOARD_PRODUCT_API unsigned char * QT_BoardAllocBufferExtend(unsigned int unCardIndex, int blockNum, int bufferSize);

	//设置通知大小SPEC
	QT_BOARD_PRODUCT_API int QT_BoardSetFIFONotifySizeB(unsigned int unCardIndex, int notifySizeB);

	//设置通知大小SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardSetFIFONotifySizeBExtend(unsigned int unCardIndex, int blockNum, int notifySizeB);

	//获取可用数据量SPEC
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataAvail(unsigned int unCardIndex);

	//获取可用数据量SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataAvailExtend(unsigned int unCardIndex, int blockNum);

	//获取当前指针位置SPEC
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataPos(unsigned int unCardIndex);

	//获取当前指针位置SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataPosExtend(unsigned int unCardIndex, int blockNum);

	//获取数据状态SPEC
	QT_BOARD_PRODUCT_API int QT_BoardWaitFIFOData(unsigned int unCardIndex, int timeOutMS);

	//获取数据状态SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardWaitFIFODataExtend(unsigned int unCardIndex, int blockNum, int timeOutMS);

	//无限点模式释放内存中的数据SPEC
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBuffer(unsigned int unCardIndex, int bufferSize);

	//无限点模式释放内存中的数据SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBufferExtend(unsigned int unCardIndex, int blockNum, int bufferSize);

	//是否存储文件
	QT_BOARD_PRODUCT_API int QT_BoardIfStoreFiles(unsigned int unCardIndex, int fileSave);

	//无限点模式获取数据用做显示DMA0
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferForShow0(unsigned int unCardIndex, unsigned char * buffer);

	//无限点模式获取数据用做显示DMA1
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferForShow1(unsigned int unCardIndex, unsigned char * buffer);

	//获取数据
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecGetData(unsigned int unCardIndex, int blockNum, uint8_t *buffer, uint32_t bytes);

	//上位机启动/停止采集ADC数据
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecCollectData(unsigned int unCardIndex, int recSwitch, int iIfDisk);

	//DAC时钟模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepClockMode(unsigned int unCardIndex, int clockMode);

	//DAC软件触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRepSoftware(unsigned int unCardIndex);

	//DAC内部脉冲触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRepInternalPulse(unsigned int unCardIndex, int pulsePeriod, int pulseWidth);

	//DAC外部脉冲触发
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRepExternal(unsigned int unCardIndex, int extMode);

	//DAC采样率设置
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSamplerate(unsigned int unCardIndex, uint32_t sampleRate);

	//DAC通道选择
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepChannelMode(unsigned int unCardIndex, int chParam);

	//DAC DMA选择
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepDMAMode(unsigned int unCardIndex, int dmaParam);

	//DA播放延迟时间
	QT_BOARD_PRODUCT_API int QT_BoardSetRepPlayDelay(unsigned int unCardIndex, uint32_t delayTime);

	//DDS播放模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceDDS(unsigned int unCardIndex, int outFreq);

	//数据文件播放模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDMA(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, char *strFileName, uint32_t segmentB);

	//回环数据文件播放模式
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDMALoopPlay(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, char *strFileName, uint32_t segmentB);

	//有限点DA播放DMA控制
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepStdDMACtrl(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, uint32_t segmentB);

	//无限点DA播放DMA控制
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepFifoDMACtrl(unsigned int unCardIndex, int blockNum, uint32_t segmentB);

	//回环有限点DA播放DMA控制
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepStdDMACtrlLoopPlay(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, uint32_t segmentB);

	//回环无限点DA播放DMA控制
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepFifoDMACtrlLoopPlay(unsigned int unCardIndex, int blockNum, uint32_t segmentB);

	//数据文件播放模式DATAMOVE
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDatamove(unsigned int unCardIndex, char *strFileName, uint32_t segmentB);

	//数据文件播放模式DATAMOVE20241225
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDatamoveRe(unsigned int unCardIndex, char *strFileName, int loopFlag, uint64_t segmentB);

	//DA流模式播放
	QT_BOARD_PRODUCT_API int QT_BoardSetRepStreamPlay(unsigned int unCardIndex, char * playFile);

	//下发数据
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSendData(unsigned int unCardIndex, int blockNum, uint8_t *buffer, uint32_t bytes);

	//上位机启动/停止播放DAC数据
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepPlayData(unsigned int unCardIndex, int repSwitch);

	//回环开始采集和播放
	QT_BOARD_PRODUCT_API int QT_BoardSetLoopPlayStart(unsigned int unCardIndex);

	//判断初始化状态9009
	QT_BOARD_PRODUCT_API int QT_BoardParseState(unsigned int unCardIndex);

	//切换参考源9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRefClockMode(unsigned int unCardIndex, uint32_t refMode);

	//设置本振9009
	QT_BOARD_PRODUCT_API int QT_BoardSetUpdateFrequency(unsigned int unCardIndex, int freq);

	//修改接收衰减9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRecAttenuation(unsigned int unCardIndex, double attenuation);

	//设置发射衰减9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRepAttenuation(unsigned int unCardIndex, double attenuation);

	//设置采集数据类型9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRecDataType(unsigned int unCardIndex, int datatype);

	//设置接收数据带宽9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRecBandwidth(unsigned int unCardIndex, uint32_t bandwidth);

	//设置发射数据类型9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRepDataType(unsigned int unCardIndex, int datatype);

	//QT1149滑动平均
	QT_BOARD_PRODUCT_API int QT_BoardSetMovingAverage(unsigned int unCardIndex, uint32_t length);

	//QT1149直流校准
	QT_BOARD_PRODUCT_API int QT_BoardSetDCCalibration(unsigned int unCardIndex, uint32_t calibrationValues);

	//QT1149基线校准数据模式
	QT_BOARD_PRODUCT_API int QT_BoardSetBaselineCalibrationDataMode(unsigned int unCardIndex, uint32_t dataMode);

	//QT1144VG HMC853 写操作
	QT_BOARD_PRODUCT_API int QT_BoardSetVGHMC853Wrt(unsigned int unCardIndex);

	//QT1144VG HMC853 读操作
	QT_BOARD_PRODUCT_API int QT_BoardSetVGHMC853Rd(unsigned int unCardIndex, int *readValue);

	//QT1144VG ads42lb69 写操作 第一阶段
	QT_BOARD_PRODUCT_API int QT_BoardSetVGads42lb69Wrt1st(unsigned int unCardIndex);

	//QT1144VG 回读LVDS训练完成信号
	QT_BOARD_PRODUCT_API int QT_BoardSetReadVGLVDSSignal(unsigned int unCardIndex);

	//QT1144VG ads42lb69 第二阶段
	QT_BOARD_PRODUCT_API int QT_BoardSetVGads42lb69Wrt2nd(unsigned int unCardIndex);

	//QT1144VG ads42lb69 读操作
	QT_BOARD_PRODUCT_API int QT_BoardSetVGads42lb6Rd(unsigned int unCardIndex, int *readValue);

	//FFT点数
	QT_BOARD_PRODUCT_API int QT_BoardSetFFTPointCount(unsigned int unCardIndex, int point);

	//窗函数类型
	QT_BOARD_PRODUCT_API int QT_BoardSetWindowFunctionType(unsigned int unCardIndex, int windowFunction);

	//上传数据选择
	QT_BOARD_PRODUCT_API int QT_BoardUploadDataSelection(unsigned int unCardIndex, int dataMode);

	//回环模式1 标准模式0
	QT_BOARD_PRODUCT_API int QT_BoardSetLoopbackOrStandardWorkMode(unsigned int unCardIndex, int workMode);

	//userLogic控制0xA000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicAControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//userLogic控制0xB000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicBControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//userLogic控制0xC000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicCControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//userLogic控制0xD000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicDControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//7135DC外部直流偏置校准寄存器
	QT_BOARD_PRODUCT_API int QT_BoardSetExternalDCBiasCalibration(unsigned int unCardIndex, int direction);

	//code值转电压(校准系数)
	QT_BOARD_PRODUCT_API int QT_BoardConvertCodeValueToVoltageValue(unsigned int unCardIndex, int chID, int chRange, int chNum, void * inputBuffer, uint32_t size, void ** outputBuffer);

	//数据翻转
	QT_BOARD_PRODUCT_API void QT_BoardFlipBufferMultiThreaded(void * buffer, size_t size, int32_t axis, int resolution, int32_t* flipped_data);

	//设置累加次数
	QT_BOARD_PRODUCT_API int QT_BoardSetTheCumulativeTimes(unsigned int unCardIndex, uint32_t times);

	//流模式判断 1:流模式 0:中断模式
	QT_BOARD_PRODUCT_API int QT_BoardCheckStreamMode(unsigned int unCardIndex);

	//流模式上位机启动采集 DMA传输开始
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStartCollectData(unsigned int unCardIndex);

	//流模式上位机停止采集 DMA传输结束
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStopCollectData(unsigned int unCardIndex);

	//流模式获取映射buffer
	QT_BOARD_PRODUCT_API int QT_BoardGetStreamModeMappingBuffer(unsigned int unCardIndex, int blockNum, PVOID * mappedBuffer);

	//流模式有限点单次采集模式
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStdSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//流模式有限点多次采集模式
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStdMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t segCount, uint32_t frameSwitch, uint32_t preTrigDots);

	//流模式无限点单次采集模式
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecFIFOSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//流模式无限点多次采集模式
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecFIFOMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//流模式获取STD数据
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamRecGetSTDData(unsigned int unCardIndex, int blockNum, void *buffer, uint32_t bytes);

	//流模式获取FIFO数据
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamRecGetFIFOData(unsigned int unCardIndex, int blockNum, void **buffer, uint32_t* bytes, int* dataPos, uint32_t* remainBytes);

	//流模式设置超时
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamRecGetDataTimeout(unsigned int unCardIndex, int blockNum, int64_t timeoutMS);

	//FFT补零功能
	QT_BOARD_PRODUCT_API int QT_BoardSetZeroFillingFunction(unsigned int unCardIndex, int enable);

	//FFT单个距离门样点个数
	QT_BOARD_PRODUCT_API int QT_BoardSetSamplePoints(unsigned int unCardIndex, int samplePoints);

	//FFT单次触发距离门个数
	QT_BOARD_PRODUCT_API int QT_BoardSetDistanceDoorsNumbers(unsigned int unCardIndex, int numbers);

	//窗函数RAM
	QT_BOARD_PRODUCT_API int QT_BoardSetWindowFunctionRAM(unsigned int unCardIndex, int32_t * data);

	//FFT输出结果缩放配置
	QT_BOARD_PRODUCT_API int QT_BoardSetScalingConfiguration(unsigned int unCardIndex, int scale);

#ifdef __cplusplus
}

#endif

#endif