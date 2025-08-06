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

	//ǧ��������IP
	QT_BOARD_PRODUCT_API int QT_BoardSetGbNetIP(unsigned int unCardIndex, void * IPAddress);

	//�򿪰忨
	QT_BOARD_PRODUCT_API int QT_BoardOpenBoard(unsigned int unCardIndex);

	//�رհ忨
	QT_BOARD_PRODUCT_API int QT_BoardCloseBoard(unsigned int unCardIndex);

	//��ȡSDK�汾��
	QT_BOARD_PRODUCT_API int QT_BoardGetSDKVersion(char * ver);

	//��ȡ�忨�ͺ�
	QT_BOARD_PRODUCT_API int QT_BoardGetCardType(unsigned int unCardIndex);

	//��ȡ�忨�̼��汾��
	QT_BOARD_PRODUCT_API int QT_BoardGetCardSoftVersion(unsigned int unCardIndex);

	//��ȡ�忨ADC��������Ϣ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardADCSamplerate(unsigned int unCardIndex);

	//��ȡ�忨ADCͨ������Ϣ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardADCChNumbers(unsigned int unCardIndex);

	//��ȡ�忨ADC�ֱ�����Ϣ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardADCResolution(unsigned int unCardIndex);

	//��ȡ�忨DAC��������Ϣ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDACSamplerate(unsigned int unCardIndex);

	//��ȡ�忨DACͨ������Ϣ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDACChNumbers(unsigned int unCardIndex);

	//��ȡ�忨DAC�ֱ�����Ϣ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDACResolution(unsigned int unCardIndex);

	//��ȡ�忨״ֵ̬
	QT_BOARD_PRODUCT_API int QT_BoardGetCardStatus(unsigned int unCardIndex);

	//��ȡ�忨��Ϸ�ʽ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardCouplingMode(unsigned int unCardIndex, char* str);

	//��ȡ�忨��ʽ
	QT_BOARD_PRODUCT_API int QT_BoardGetCardForm(unsigned int unCardIndex, char* str);

	//��ȡ�忨AD/DA
	QT_BOARD_PRODUCT_API int QT_BoardGetCardRecToRep(unsigned int unCardIndex, char* str);

	//��ȡ�忨DMA����
	QT_BOARD_PRODUCT_API int QT_BoardGetCardDMACounts(unsigned int unCardIndex);

	//��ȡ�忨��Ʒ�ͺ�
	QT_BOARD_PRODUCT_API int QT_BoardGetProductType(unsigned int unCardIndex, char* str);

	//��ȡ�豸����
	QT_BOARD_PRODUCT_API int QT_BoardGetDeviceCnt();

	//��ȡ�豸ID
	QT_BOARD_PRODUCT_API int QT_BoardGetDeviceID(int deviceCnt, char* deviceID);

	//дEEPROM 32bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM32Write(unsigned int unCardIndex, uint32_t offsetaddr, uint32_t value);

	//дEEPROM 8bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM8Write(unsigned int unCardIndex, uint32_t offsetaddr, uint8_t value);

	//дEEPROM 16bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM16Write(unsigned int unCardIndex, uint32_t offsetaddr, uint16_t value);

	//дEEPROM char
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM4Write(unsigned int unCardIndex, uint32_t offsetaddr, char* value);

	//��EEPROM 8bit
	QT_BOARD_PRODUCT_API int QT_BoardEEPROM8Read(unsigned int unCardIndex, uint32_t offsetaddr, uint8_t *value);

	//ǧ�������ݷ���
	QT_BOARD_PRODUCT_API int QT_BoardDataSendFlash(unsigned int unCardIndex, char *filename);

	//ǧ�������Ϳ�ʼ�̻�ָ��
	QT_BOARD_PRODUCT_API int QT_BoardStartProgramFlash(unsigned int unCardIndex);

	//ǧ����flash��Ϣ�·�//cancel
	QT_BOARD_PRODUCT_API int QT_BoardFlashCalculateInfo(unsigned int unCardIndex, char* buffer, long size, uint32_t cnt);

	//ǧ����flash��д����//cancel
	QT_BOARD_PRODUCT_API int QT_BoardFlashCalOperate(unsigned int unCardIndex, uint32_t cmdhead, uint32_t operate, uint32_t cnt, long size, char *recv);

	//ǧ����flash��д
	QT_BOARD_PRODUCT_API int QT_BoardFlashReadAndWriteOperations(unsigned int unCardIndex, const char* filename, uint32_t optCode);

	//ǧ����������λ����־�������
	QT_BOARD_PRODUCT_API int QT_BoardSetLogLevelOfLower(unsigned int unCardIndex, uint32_t logLevel);

	//��ȡ�忨���̷�Χ
	QT_BOARD_PRODUCT_API int QT_BoardObtainThechRange(unsigned int unCardIndex, int chRange);

	//��ȡ�忨���̷�Χ����
	QT_BOARD_PRODUCT_API int QT_BoardObtainThechRangeNum(unsigned int unCardIndex);

	//��ȡ�忨ADC DMA����
	QT_BOARD_PRODUCT_API int QT_BoardObtainTheADCBlockNum(unsigned int unCardIndex);

	//��ȡ�忨DAC DMA����
	QT_BOARD_PRODUCT_API int QT_BoardObtainTheDACBlockNum(unsigned int unCardIndex);

	//�Ƿ�֧��ʱ�ӣ���ο�ʱ�ӡ������ʱ��
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportClockMode(unsigned int unCardIndex);

	//�Ƿ�֧��ADCͨ��ѡ��
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportRecChannelSwitch(unsigned int unCardIndex);

	//�Ƿ�֧��DACͨ��ѡ��
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportRepChannelSwitch(unsigned int unCardIndex);

	//�Ƿ�֧�����޵㵥�βɼ�
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportInfiniteSingle(unsigned int unCardIndex);

	//�Ƿ�֧�����޵��βɼ�
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportInfiniteMulti(unsigned int unCardIndex);

	//�Ƿ�֧�����޵㵥�βɼ�
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFiniteSingle(unsigned int unCardIndex);

	//�Ƿ�֧�����޵��βɼ�
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFiniteMulti(unsigned int unCardIndex);

	//�Ƿ�֧��DDS����
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportDDSPlay(unsigned int unCardIndex);

	//�Ƿ�֧���ⲿ�����ļ�����
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFilePlay(unsigned int unCardIndex);

	//�ⲿ���ݲ�����DMA����DATAMOVE
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFilePlaySource(unsigned int unCardIndex);

	//�Ƿ�֧��ģ��ǰ������
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportOffsetAdjust(unsigned int unCardIndex);

	//�Ƿ�֧�ַ��ȿ���
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportFanControl(unsigned int unCardIndex);

	//�Ƿ���9009
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport9009Rf(unsigned int unCardIndex);

	//�Ƿ���QT1144VG
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport1144VG(unsigned int unCardIndex);

	//�Ƿ���QT1140
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport1140(unsigned int unCardIndex);

	//�Ƿ���QT1149���л���У׼��ֱ��У׼����
	QT_BOARD_PRODUCT_API int QT_BoardIfSupport1149NonStandard(unsigned int unCardIndex);

	//�Ƿ�ʹ��EEPROM
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportUseEEPROM(unsigned int unCardIndex);

	//�Ƿ�֧��DA��ģʽ����
	QT_BOARD_PRODUCT_API int QT_BoardIfSupportRepStreamPlay(unsigned int unCardIndex);

	//buffer 8bitת16bit
	QT_BOARD_PRODUCT_API int QT_Board_Buff_BIT8_TO_BIT16(uint8_t buffer_8bit, uint16_t buffer_16bit, bool isSignal);

	//buffer 10bitת16bit
	QT_BOARD_PRODUCT_API int QT_Board_Buff_BIT10_TO_BIT16(uint8_t buffer_10bit[5], uint16_t buffer_16bit[4], bool isSignal);

	//buffer 12bitת16bit
	QT_BOARD_PRODUCT_API int QT_Board_Buff_BIT12_TO_BIT16(uint8_t buffer_12bit[3], uint16_t buffer_16bit[2], bool isSignal);

	//�ļ� 8bitת16bit
	QT_BOARD_PRODUCT_API int QT_Board_File_BIT8_TO_BIT16(char *src8bitFilename, char *dst16bitFilename, bool isSignal);

	//�ļ� 10bitת16bit
	QT_BOARD_PRODUCT_API int QT_Board_File_BIT10_TO_BIT16(char *src10bitFilename, char *dst16bitFilename, bool isSignal);

	//�ļ� 12bitת16bit
	QT_BOARD_PRODUCT_API int QT_Board_File_BIT12_TO_BIT16(char *src12bitFilename, char *dst16bitFilename, bool isSignal);

	//����ADCʹ��
	QT_BOARD_PRODUCT_API int QT_BoardSetADCEnable(unsigned int unCardIndex);

	//����DACʹ��
	QT_BOARD_PRODUCT_API int QT_BoardSetDACEnable(unsigned int unCardIndex);

	//�����λ
	QT_BOARD_PRODUCT_API int QT_BoardSetSoftwareReset(unsigned int unCardIndex, int direction);

	//PCIe�ж�ʹ��
	QT_BOARD_PRODUCT_API int QT_BoardSetIntrControl(unsigned int unCardIndex, int intrCtrl);

	//���ȿ���
	QT_BOARD_PRODUCT_API int QT_BoardSetFanControl(unsigned int unCardIndex, int controlsource, int fangear);

	//ADCʱ��ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecClockMode(unsigned int unCardIndex, int clockMode);

	//ADC�������
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecSoftware(unsigned int unCardIndex);

	//ADC�������
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecSoftwareRe(unsigned int unCardIndex, int blockNum);

	//ADC�ⲿ���崥��
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecExternal(unsigned int unCardIndex, int extMode, uint32_t trigDelay, double biasvoltage);

	//ADC�ⲿ���崥��
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecExternalRe(unsigned int unCardIndex, int blockNum, int extMode, uint32_t trigDelay, double biasvoltage);

	//ADCͨ������
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecChannel(unsigned int unCardIndex, int trigMode, int channel, int hysteresis, int trigLevel);

	//ADCͨ������
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecChannelRe(unsigned int unCardIndex, int blockNum, int trigMode, int channel, int hysteresis, int trigLevel);

	//ADC�ڲ����崥��
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecInternalPulse(unsigned int unCardIndex, int pulsePeriod, int pulseWidth);

	//ADC�ڲ����崥��
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRecInternalPulseRe(unsigned int unCardIndex, int blockNum, int pulsePeriod, int pulseWidth);

	//ADC����������
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecSamplerate(unsigned int unCardIndex, uint32_t sampleRate);

	//ADC����ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecWorkingMode(unsigned int unCardIndex, int chMode);

	//ͨ��ѡ����ʱ  ȷ��֮��ɾ��
	QT_BOARD_PRODUCT_API int QT_BoardSetRecChannelModeDelayTime(unsigned int unCardIndex, int delayTime0us, int delayTime1us);

	//ADCͨ��ѡ��
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecChannelMode(unsigned int unCardIndex, int chParam);

	//AD�ɼ��ӳ�ʱ��
	QT_BOARD_PRODUCT_API int QT_BoardSetRecCollectDelay(unsigned int unCardIndex, uint32_t delayTime);

	//ģ��ǰ�˵��ڶ�ȡEEPROM
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEEEPROM(unsigned int unCardIndex, int chID, int chRange, uint32_t * offsetValue, double * calibrationValue);

	//ģ��ǰ�˵��ڶ�ȡJSON�����ļ�
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEJSON(unsigned int unCardIndex, int chID, int chRange);

	//ģ��ǰ��ƫ�õ���
	QT_BOARD_PRODUCT_API int QT_BoardSetBiasAdjustment(unsigned int unCardIndex, int chID, uint32_t bias);

	//ģ��ǰ���������
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEGain(unsigned int unCardIndex, int chID, int gainValue);

	//ģ��ǰ��˥������
	QT_BOARD_PRODUCT_API int QT_BoardSetAFEAttenuation(unsigned int unCardIndex, int chID, int attenuationValue);

	//QT1144VGģ��ǰ������
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEndVG(unsigned int unCardIndex, int chID, double biasVoltage, int iGainFalloff);

	//QT1144VGģ��ǰ������20250307
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEndVGRe(unsigned int unCardIndex, int chID, double biasVoltage, int range);

	//QT1140ģ��ǰ������
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEnd(unsigned int unCardIndex, int chID, int biasVoltage, int position);

	//QT1140ģ��ǰ������20250307
	QT_BOARD_PRODUCT_API int QT_BoardConfigureAnalogFrontEndRe(unsigned int unCardIndex, double biasVoltagech0, double biasVoltagech1, int rangech0, int rangech1);

	//���޵㵥�βɼ�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecStdSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//���޵��βɼ�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecStdMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t segCount, uint32_t frameSwitch, uint32_t preTrigDots);

	//���޵㵥�βɼ�ģʽMB
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecFIFOSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentMB, uint32_t frameSwitch, uint32_t pretrigdots);

	//���޵㵥�βɼ�ģʽB
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecFIFOSingleB(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t pretrigdots);

	//���޵��βɼ�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupModeRecFIFOMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots, double repetitionFrequency);

	//���޵�ģʽ�����ļ��ļ�·���ļ���С�ļ���
	QT_BOARD_PRODUCT_API int QT_BoardSetTheFilePathSizeName(unsigned int unCardIndex, int blockNum, char *filepath, uint64_t filesize, const char *filename);

	//���޵�ģʽ��ʼ��buffer
	QT_BOARD_PRODUCT_API int QT_BoardSetInitializeOperation(unsigned int unCardIndex);

	//���޵�ģʽ�ͷ�buffer
	QT_BOARD_PRODUCT_API int QT_BoardSetFreeOperation(unsigned int unCardIndex);

	//���޵�ģʽ��ȡ�ڴ��е�����
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBuffer(unsigned int unCardIndex, unsigned char * buffer, int bufferSize, int timeOutms);

	//���޵�ģʽ��ȡ�ڴ��е�����20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferExtend(unsigned int unCardIndex, int blockNum, unsigned char * buffer, int bufferSize, int timeOutms);

	//���޵�ģʽ��ȡ�ڴ��е�����ָ��
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferPointer(unsigned int unCardIndex, unsigned char ** buffer, int bufferSize, int timeOutms);

	//���޵�ģʽ��ȡ�ڴ��е�����ָ��20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferPointerExtend(unsigned int unCardIndex, int blockNum, unsigned char ** buffer, int bufferSize, int timeOutms);

	//���޵�ģʽ�ͷ��ڴ��е�����ָ��
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBufferPointer(unsigned int unCardIndex, unsigned char ** buffer, int bufferSize);

	//���޵�ģʽ�ͷ��ڴ��е�����ָ��20250411
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBufferPointerExtend(unsigned int unCardIndex, int blockNum, unsigned char ** buffer, int bufferSize);

	//�����ڴ�SPEC
	QT_BOARD_PRODUCT_API unsigned char * QT_BoardAllocBuffer(unsigned int unCardIndex, int bufferSize);

	//�����ڴ�SPEC20250411
	QT_BOARD_PRODUCT_API unsigned char * QT_BoardAllocBufferExtend(unsigned int unCardIndex, int blockNum, int bufferSize);

	//����֪ͨ��СSPEC
	QT_BOARD_PRODUCT_API int QT_BoardSetFIFONotifySizeB(unsigned int unCardIndex, int notifySizeB);

	//����֪ͨ��СSPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardSetFIFONotifySizeBExtend(unsigned int unCardIndex, int blockNum, int notifySizeB);

	//��ȡ����������SPEC
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataAvail(unsigned int unCardIndex);

	//��ȡ����������SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataAvailExtend(unsigned int unCardIndex, int blockNum);

	//��ȡ��ǰָ��λ��SPEC
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataPos(unsigned int unCardIndex);

	//��ȡ��ǰָ��λ��SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataPosExtend(unsigned int unCardIndex, int blockNum);

	//��ȡ����״̬SPEC
	QT_BOARD_PRODUCT_API int QT_BoardWaitFIFOData(unsigned int unCardIndex, int timeOutMS);

	//��ȡ����״̬SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardWaitFIFODataExtend(unsigned int unCardIndex, int blockNum, int timeOutMS);

	//���޵�ģʽ�ͷ��ڴ��е�����SPEC
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBuffer(unsigned int unCardIndex, int bufferSize);

	//���޵�ģʽ�ͷ��ڴ��е�����SPEC20250411
	QT_BOARD_PRODUCT_API int QT_BoardReturnFIFODataBufferExtend(unsigned int unCardIndex, int blockNum, int bufferSize);

	//�Ƿ�洢�ļ�
	QT_BOARD_PRODUCT_API int QT_BoardIfStoreFiles(unsigned int unCardIndex, int fileSave);

	//���޵�ģʽ��ȡ����������ʾDMA0
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferForShow0(unsigned int unCardIndex, unsigned char * buffer);

	//���޵�ģʽ��ȡ����������ʾDMA1
	QT_BOARD_PRODUCT_API int QT_BoardGetFIFODataBufferForShow1(unsigned int unCardIndex, unsigned char * buffer);

	//��ȡ����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecGetData(unsigned int unCardIndex, int blockNum, uint8_t *buffer, uint32_t bytes);

	//��λ������/ֹͣ�ɼ�ADC����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRecCollectData(unsigned int unCardIndex, int recSwitch, int iIfDisk);

	//DACʱ��ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepClockMode(unsigned int unCardIndex, int clockMode);

	//DAC�������
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRepSoftware(unsigned int unCardIndex);

	//DAC�ڲ����崥��
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRepInternalPulse(unsigned int unCardIndex, int pulsePeriod, int pulseWidth);

	//DAC�ⲿ���崥��
	QT_BOARD_PRODUCT_API int QT_BoardSetupTrigRepExternal(unsigned int unCardIndex, int extMode);

	//DAC����������
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSamplerate(unsigned int unCardIndex, uint32_t sampleRate);

	//DACͨ��ѡ��
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepChannelMode(unsigned int unCardIndex, int chParam);

	//DAC DMAѡ��
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepDMAMode(unsigned int unCardIndex, int dmaParam);

	//DA�����ӳ�ʱ��
	QT_BOARD_PRODUCT_API int QT_BoardSetRepPlayDelay(unsigned int unCardIndex, uint32_t delayTime);

	//DDS����ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceDDS(unsigned int unCardIndex, int outFreq);

	//�����ļ�����ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDMA(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, char *strFileName, uint32_t segmentB);

	//�ػ������ļ�����ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDMALoopPlay(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, char *strFileName, uint32_t segmentB);

	//���޵�DA����DMA����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepStdDMACtrl(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, uint32_t segmentB);

	//���޵�DA����DMA����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepFifoDMACtrl(unsigned int unCardIndex, int blockNum, uint32_t segmentB);

	//�ػ����޵�DA����DMA����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepStdDMACtrlLoopPlay(unsigned int unCardIndex, int blockNum, uint32_t loopFlag, uint32_t loopCount, uint32_t segmentB);

	//�ػ����޵�DA����DMA����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepFifoDMACtrlLoopPlay(unsigned int unCardIndex, int blockNum, uint32_t segmentB);

	//�����ļ�����ģʽDATAMOVE
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDatamove(unsigned int unCardIndex, char *strFileName, uint32_t segmentB);

	//�����ļ�����ģʽDATAMOVE20241225
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSourceFileDatamoveRe(unsigned int unCardIndex, char *strFileName, int loopFlag, uint64_t segmentB);

	//DA��ģʽ����
	QT_BOARD_PRODUCT_API int QT_BoardSetRepStreamPlay(unsigned int unCardIndex, char * playFile);

	//�·�����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepSendData(unsigned int unCardIndex, int blockNum, uint8_t *buffer, uint32_t bytes);

	//��λ������/ֹͣ����DAC����
	QT_BOARD_PRODUCT_API int QT_BoardSetupRepPlayData(unsigned int unCardIndex, int repSwitch);

	//�ػ���ʼ�ɼ��Ͳ���
	QT_BOARD_PRODUCT_API int QT_BoardSetLoopPlayStart(unsigned int unCardIndex);

	//�жϳ�ʼ��״̬9009
	QT_BOARD_PRODUCT_API int QT_BoardParseState(unsigned int unCardIndex);

	//�л��ο�Դ9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRefClockMode(unsigned int unCardIndex, uint32_t refMode);

	//���ñ���9009
	QT_BOARD_PRODUCT_API int QT_BoardSetUpdateFrequency(unsigned int unCardIndex, int freq);

	//�޸Ľ���˥��9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRecAttenuation(unsigned int unCardIndex, double attenuation);

	//���÷���˥��9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRepAttenuation(unsigned int unCardIndex, double attenuation);

	//���òɼ���������9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRecDataType(unsigned int unCardIndex, int datatype);

	//���ý������ݴ���9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRecBandwidth(unsigned int unCardIndex, uint32_t bandwidth);

	//���÷�����������9009
	QT_BOARD_PRODUCT_API int QT_BoardSetRepDataType(unsigned int unCardIndex, int datatype);

	//QT1149����ƽ��
	QT_BOARD_PRODUCT_API int QT_BoardSetMovingAverage(unsigned int unCardIndex, uint32_t length);

	//QT1149ֱ��У׼
	QT_BOARD_PRODUCT_API int QT_BoardSetDCCalibration(unsigned int unCardIndex, uint32_t calibrationValues);

	//QT1149����У׼����ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetBaselineCalibrationDataMode(unsigned int unCardIndex, uint32_t dataMode);

	//QT1144VG HMC853 д����
	QT_BOARD_PRODUCT_API int QT_BoardSetVGHMC853Wrt(unsigned int unCardIndex);

	//QT1144VG HMC853 ������
	QT_BOARD_PRODUCT_API int QT_BoardSetVGHMC853Rd(unsigned int unCardIndex, int *readValue);

	//QT1144VG ads42lb69 д���� ��һ�׶�
	QT_BOARD_PRODUCT_API int QT_BoardSetVGads42lb69Wrt1st(unsigned int unCardIndex);

	//QT1144VG �ض�LVDSѵ������ź�
	QT_BOARD_PRODUCT_API int QT_BoardSetReadVGLVDSSignal(unsigned int unCardIndex);

	//QT1144VG ads42lb69 �ڶ��׶�
	QT_BOARD_PRODUCT_API int QT_BoardSetVGads42lb69Wrt2nd(unsigned int unCardIndex);

	//QT1144VG ads42lb69 ������
	QT_BOARD_PRODUCT_API int QT_BoardSetVGads42lb6Rd(unsigned int unCardIndex, int *readValue);

	//FFT����
	QT_BOARD_PRODUCT_API int QT_BoardSetFFTPointCount(unsigned int unCardIndex, int point);

	//����������
	QT_BOARD_PRODUCT_API int QT_BoardSetWindowFunctionType(unsigned int unCardIndex, int windowFunction);

	//�ϴ�����ѡ��
	QT_BOARD_PRODUCT_API int QT_BoardUploadDataSelection(unsigned int unCardIndex, int dataMode);

	//�ػ�ģʽ1 ��׼ģʽ0
	QT_BOARD_PRODUCT_API int QT_BoardSetLoopbackOrStandardWorkMode(unsigned int unCardIndex, int workMode);

	//userLogic����0xA000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicAControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//userLogic����0xB000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicBControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//userLogic����0xC000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicCControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//userLogic����0xD000
	QT_BOARD_PRODUCT_API int64_t QT_BoardUserLogicDControl(unsigned int unCardIndex, uint32_t offset, uint32_t value, int direction);

	//7135DC�ⲿֱ��ƫ��У׼�Ĵ���
	QT_BOARD_PRODUCT_API int QT_BoardSetExternalDCBiasCalibration(unsigned int unCardIndex, int direction);

	//codeֵת��ѹ(У׼ϵ��)
	QT_BOARD_PRODUCT_API int QT_BoardConvertCodeValueToVoltageValue(unsigned int unCardIndex, int chID, int chRange, int chNum, void * inputBuffer, uint32_t size, void ** outputBuffer);

	//���ݷ�ת
	QT_BOARD_PRODUCT_API void QT_BoardFlipBufferMultiThreaded(void * buffer, size_t size, int32_t axis, int resolution, int32_t* flipped_data);

	//�����ۼӴ���
	QT_BOARD_PRODUCT_API int QT_BoardSetTheCumulativeTimes(unsigned int unCardIndex, uint32_t times);

	//��ģʽ�ж� 1:��ģʽ 0:�ж�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardCheckStreamMode(unsigned int unCardIndex);

	//��ģʽ��λ�������ɼ� DMA���俪ʼ
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStartCollectData(unsigned int unCardIndex);

	//��ģʽ��λ��ֹͣ�ɼ� DMA�������
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStopCollectData(unsigned int unCardIndex);

	//��ģʽ��ȡӳ��buffer
	QT_BOARD_PRODUCT_API int QT_BoardGetStreamModeMappingBuffer(unsigned int unCardIndex, int blockNum, PVOID * mappedBuffer);

	//��ģʽ���޵㵥�βɼ�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStdSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//��ģʽ���޵��βɼ�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecStdMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t segCount, uint32_t frameSwitch, uint32_t preTrigDots);

	//��ģʽ���޵㵥�βɼ�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecFIFOSingle(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//��ģʽ���޵��βɼ�ģʽ
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamModeRecFIFOMulti(unsigned int unCardIndex, int blockNum, uint32_t segmentB, uint32_t frameSwitch, uint32_t preTrigDots);

	//��ģʽ��ȡSTD����
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamRecGetSTDData(unsigned int unCardIndex, int blockNum, void *buffer, uint32_t bytes);

	//��ģʽ��ȡFIFO����
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamRecGetFIFOData(unsigned int unCardIndex, int blockNum, void **buffer, uint32_t* bytes, int* dataPos, uint32_t* remainBytes);

	//��ģʽ���ó�ʱ
	QT_BOARD_PRODUCT_API int QT_BoardSetStreamRecGetDataTimeout(unsigned int unCardIndex, int blockNum, int64_t timeoutMS);

	//FFT���㹦��
	QT_BOARD_PRODUCT_API int QT_BoardSetZeroFillingFunction(unsigned int unCardIndex, int enable);

	//FFT�����������������
	QT_BOARD_PRODUCT_API int QT_BoardSetSamplePoints(unsigned int unCardIndex, int samplePoints);

	//FFT���δ��������Ÿ���
	QT_BOARD_PRODUCT_API int QT_BoardSetDistanceDoorsNumbers(unsigned int unCardIndex, int numbers);

	//������RAM
	QT_BOARD_PRODUCT_API int QT_BoardSetWindowFunctionRAM(unsigned int unCardIndex, int32_t * data);

	//FFT��������������
	QT_BOARD_PRODUCT_API int QT_BoardSetScalingConfiguration(unsigned int unCardIndex, int scale);

#ifdef __cplusplus
}

#endif

#endif