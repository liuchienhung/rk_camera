#ifndef _CAM_IA10_ENGINE_H_
#define _CAM_IA10_ENGINE_H_

#include <calib_xml/calibdb.h>
#include <cam_calibdb/cam_calibdb_api.h>

#include "include/cam_ia10_engine_api.h"
#include "include/cameric.h"
#include <awb/awb.h>
#include <awb/awbConvert.h>

class CamIA10Engine:public CamIA10EngineItf 
{
public:
	CamIA10Engine();
	virtual ~CamIA10Engine();

	virtual RESULT initStatic(char* aiqb_data_file);
	virtual RESULT initDynamic(struct CamIA10_DyCfg *cfg);
	virtual RESULT setStatistics(struct CamIA10_Stats *stats);
	
	virtual RESULT runAEC();
	virtual RESULT getAECResults(AecResult_t *result);

	virtual RESULT runAWB();
	virtual RESULT getAWBResults(CamIA10_AWB_Result_t *result);

	virtual RESULT runADPF();
	virtual RESULT getADPFResults(AdpfResult_t *result);

	virtual RESULT runAF();
	virtual RESULT getAFResults();

	/* manual ISP configs*/
	virtual RESULT runManISP(struct HAL_ISP_cfg_s *manCfg ,struct CamIA10_Results *result);
	virtual void mapSensorExpToHal(
				int sensorGain,
				int sensorInttime,
				float& halGain,
				float& halInttime);

private:
	void convertAwbResult2Cameric
	(
	AwbRunningOutputResult_t *awbResult,
	CamIA10_AWB_Result_t *awbCamicResult
	);
	
	void updateAwbConfigs
	(
	CamIA10_AWB_Result_t *old,
	CamIA10_AWB_Result_t *newcfg,
	CamIA10_AWB_Result_t *update
	);

	void mapHalExpToSensor
	(
		float hal_gain,
		float hal_time,
		int& sensor_gain,
		int& sensor_time
	);
	
	CalibDb calidb;
	CamCalibDbHandle_t	hCamCalibDb;

	struct CamIA10_DyCfg	dCfg;
	struct CamIA10_DyCfg	dCfgShd;

	AfHandle_t	hAf;
	AdpfHandle_t	hAdpf;
	AwbHandle_t	hAwb;
	AwbConfig_t awbcfg;
	AecConfig_t aecCfg;
	AdpfConfig_t adpfCfg;
	CamIA10_AWB_Result_t lastAwbResult;
	CamIA10_AWB_Result_t curAwbResult;
	AecResult_t	     lastAecResult;
	AecResult_t	     curAecResult;
	struct CamIA10_Stats mStats;

private:
	RESULT initAEC();
	RESULT initAWB();
	RESULT initADPF();
	RESULT initAF();
};

#endif

