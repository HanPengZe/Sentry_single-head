#ifndef _ROBOT_CONFIG_H_
#define _ROBOT_CONFIG_H_

/* Macro Definitions ---------------------------------------------------------*/
/* �Դ˼�������������Ӵ�����RM���������� */

#define ROBOT_ID SRNTRY_2023_OMNI// - ��ǰ������ ID

#define INFANTRY_2019 1 // - 2019����
#define INFANTRY_2020 2 // - 2020����
#define INFANTRY_2021 3 // - 2021����
#define INFANTRY_2021_ZJ 4 // - 2021�̾�����
#define INFANTRY_2022_SWERVE_1 5 // - 2022���ֲ���
#define INFANTRY_2022_SWERVE_2 6 // - 2022��2̨�沽
#define INFANTRY_2022_SWERVE_3 7 // - 2022��3̨�沽

#define SRNTRY_2023_OMNI 8 // - 2023ȫ���ڱ�

#define Device_BoardType Device_BoardType_C

#define Device_BoardType_Wolf 0 // ����
#define Device_BoardType_old  1 // RM �ɰ�
#define Device_BoardType_A    2 // RM A��
#define Device_BoardType_C    3 // RM C��

//���º����ڲ���ʱʹ��
#define USE_DeviceMonitor 1 //�������ߡ����󱨾�
#define USE_Buzzer          //���÷�����

#define USE_GimbalCtrl      // ʹ����̨����
#define USE_ShootSystem     // �������ϵͳ
#define USE_GimbalIMU       // ������̨������
#define USE_RM_Referee    0 // ��������ϵͳ

#endif