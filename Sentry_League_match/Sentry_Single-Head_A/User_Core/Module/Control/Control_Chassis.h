#ifndef _CONTROL_CHASSIS_H_
#define _CONTROL_CHASSIS_H_

/* Includes ------------------------------------------------------------------*/
#include "GRWML.h"
#include "Control_DR16.h"
#include "Chassis_Power.h"

#ifdef __cplusplus

#pragma diag_suppress 550

/* Exported types ------------------------------------------------------------*/


#define RUD_OPSI       1
#define RUD_NOT_OPSI   0
#define RUD_RESET      1
#define RUD_NOT_RESET  0

typedef struct
{
	int32_t SumCurrent_IN;//����ĵ����ܺ�
	int32_t SumCurrent_Out;//����������ܺ�
	
	float powerBuffRatio;	//���������

	//����ϵͳ������
	uint16_t Chassis_Power_Limit;	//�����������
	uint16_t Chassis_Power_Buff_Limit;	//���幦������
	
}PowerLimit_t;


/* --- ����������� ID --------------------------------------------------------*/
enum CHAS_DrvMotorID_e
{
    RF_201 = 0,
    LF_202 = 1,
    LB_203 = 2,
    RB_204 = 3
};
/* --- ����ת���� ID --------------------------------------------------------*/
enum CHAS_RudMororID_e
{
    RF_205 = 0,
    LF_206 = 1,
    LB_207 = 2,
    RB_208 = 3
};

/* --- ���̿���ģʽ ------------------------------------------------------------*/
enum CHAS_CtrlMode_e
{
	CHAS_DisableMode,	    // ʧ��ģʽ
    CHAS_FollowMode ,	    // ����ģʽ
	CHAS_ReFollowMode,      // �������
	CHAS_SpinMode ,	        // С����ģʽ
    CHAS_sinSpinMode,       // ����С����
	CHAS_AutoTrackMode,     // �Զ�׷��ģʽ
	CHAS_LockMode,		    // ��ס����
	CHAS_NotFollowMode,	    // �޸���ģʽ

	CHAS_SupplyMode,	    // ����ģʽ
	CHAS_SwingMode,		    // Ť��ģʽ
	CHAS_InitMode,          // ��ʼ���׶�
};


/* --- ת���ֵ����ز��� -------------------------------------------------------*/
typedef struct 
{
    float Init_angle;   // ��ʼ��У׼�Ƕ�
    float Target_angle; // Ŀ��Ƕ�
    float PreTar_angle; // ǰһ��Ŀ��Ƕ�
    float Total_angle;  // ��ǰ�ܽǶ�
    int32_t Turns_cnt;
    int32_t TarTurns_cnt;
    int32_t Turns_flag;
}RUD_Param_t;

/* �˲����Ŀ��ֵ */
typedef struct 
{
    float Vx;
    float Vy;
    float Vw;
}FilterTarget_t;

/* ����������ز��� */
typedef struct
{
    uint8_t accelerating;
    uint8_t decelerating;
    float linnerSpeed;
    float linnerSpeedLast;
    float accCnt;
    float accK = 0.25;
    float accKp;
    float deceleRecodeSpeed[2];
}AccelerateParam_t;


class Chassis_classdef : public CTRL_DR16_classdef
{
private:
    // float Target_Vx, Target_Vy, Target_Vw;
    uint8_t Lspeed_Flag;  /*<! ���ٱ�־λ(�޲���ϵͳʹ��) */
    // float VxVy_Coe; //�޸�Ϊ public
    // float VxVy_Limit;
    float Vw_Limit;
    void Process(float Vx, float Vy, float Vw);             /*<! �������ݴ��� */
    void Set_MaxSpeed();                                    /*<! �ٶ����� */
    void Follow_Ctrl(float *Vx, float *Vy, float *Vw);      /*<! ����ģʽ */
    void ReFollow_Ctrl(float *Vx, float *Vy, float *Vw);    /*<! �������ģʽ */
    void Spin_Ctrl(float *Vx, float *Vy, float *Vw);        /*<! ����ģʽ */
    void Swing_Ctrl(float *Vx, float *Vy, float *Vw);       /*<! Ť��ģʽ */
    void AotuTrack_Ctrl(float *Vx, float *Vy, float *Vw);   /*<! ׷��װ�װ� */
    void NotFollwe_Ctrl(float *Vx, float *Vy, float *Vw);   /*<! �޸���ģʽ */
    void Speed_Decompose(const float angle, float *Vx, float *Vy);/*<! �ٶȷֽ� */

public:
	    int16_t Cal_Speed[4];

    Chassis_classdef();
    CHAS_CtrlMode_e Mode;
    IncrementPID DRV_PID[4];     /*<! ������ ����ʽPID */
    PositionPID RUD_PID[4][2];   /*<! ת���� λ��ʽPID */
    PositionPID Follow_PID[2];   /*<! ����ģʽ PID */
    PositionPID Swing_PID[2];    /*<! Ť��ģʽ PID */
    Motor_M3508 DRV_Motor[4] = {Motor_M3508(1), Motor_M3508(2), Motor_M3508(3), Motor_M3508(4)};      /*<! ������ */
    Motor_GM6020 RUD_Motor[4] = {Motor_GM6020(1), Motor_GM6020(2), Motor_GM6020(3), Motor_GM6020(4)}; /*<! ת���� */

    RUD_Param_t RUD_Param[4]; /*<! ת������ز��� */

    LowPassFilter Vx_LPF = LowPassFilter(0.9f); /*<! ��ͨ�˲� */
    LowPassFilter Vy_LPF = LowPassFilter(0.9f); /*<! ��ͨ�˲� */
    LowPassFilter Vw_LPF = LowPassFilter(0.01f); /*<! ��ͨ�˲� */

    FilterTarget_t F_target;                  /*<! �˲�������� */

    AccelerateParam_t Acc_Param;    /*<! �������߲��� */

    float VxVy_Coe;
    float VxVy_Limit;
    float overHeat_Coe[4];  /*<! ���ȱ������ϵ�� */

    uint8_t ReF_Flag;     /*<! �������ת����־λ */
    int16_t ReF_Cnt;      /*<! ��������ۼ�ʱ�� */

    int16_t Target_Vx, Target_Vy, Target_Vw;

    uint8_t DRV_Motors_Update(CAN_RxHeaderTypeDef *header, uint8_t can_rx_data[]);


    void Control();

    void Mecanum_Solve(int16_t Vx, int16_t Vy, int16_t Vz, int16_t *cal_speed);  /*<! ���ֽ��� */
		void Omni_Solve(int16_t Vx, int16_t Vy, int16_t Vz, int16_t *cal_speed);  /*<! ȫ���ֽ��� */
    void Rudder_Solve(int16_t Vx, int16_t Vy, int16_t Vz, int16_t *cal_speed);   /*<�����ֽ��� */
    void RudAngle_Calc(int16_t Vx, int16_t Vy, int16_t Vz);   /*<! �����ٶȽ����Ƕ� */
    void RUDTotalAngle_Calc(Motor_GM6020* rudder_motor , int8_t motor_num , int8_t reset , uint8_t opposite);  /*<! ת�����ܽǶȼ��� */
    void RUDTargetAngle_Calc(int8_t motor_num , int8_t reset , uint8_t opposite);                             /*<! ת����Ŀ��Ƕȼ��� */
    void DRV_PIDCalc(uint8_t motor, float target, float current);
    void RUD_PIDCalc(uint8_t motor, float target, float current);
    void Judge_DRV_Dir(uint8_t motor, float target, float current);   /*<! �ж��������Ƿ���Ҫ���� */

    void Angle_Cnt();

    void Set_RudMaxOut(uint16_t maxout); /*<! ���� ת���������� */
    void Drv_Slow(float *rec , float target , float slow_Inc, float Accval, float DecVal);

    void OverHeat_Protect(uint8_t motor);  /*<! �������������� */
    void AcclerateCurve(float *Vx, float *Vy);  /*<! �������� */
    void Uphill_Process(int16_t *DRV_Current, uint8_t amount);     /*<! ����ģʽ���� */

    float Get_MinDeviation(int32_t target, int32_t current);
    float Turn_InferiorArc(uint8_t motor, float target, float current);  /*<! �ӻ���ת */

    float Get_Power();
    uint8_t IsMove();   /*<! �����Ƿ����ƶ�Ŀ���ٶ� */
    uint16_t Get_PowerLimit();
    uint16_t Get_PowerBuffer();
		PowerLimit_t PowerLimit={0,0,0,150,60};

};

extern float test_Vz;
extern int16_t ssssspeed[3];

extern float Ramp_Vy, Ramp_Vx;
extern CHAS_Power_classdef CHAS_Power;

#endif

#endif