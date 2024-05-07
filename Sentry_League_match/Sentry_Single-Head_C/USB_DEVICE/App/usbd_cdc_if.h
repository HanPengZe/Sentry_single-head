/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.h
  * @version        : v1.0_Cube
  * @brief          : Header for usbd_cdc_if.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc.h"

/* USER CODE BEGIN INCLUDE */
//#include "Control_Vision.h"
	 

/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief For Usb device.
  * @{
  */

/** @defgroup USBD_CDC_IF USBD_CDC_IF
  * @brief Usb VCP device module
  * @{
  */

/** @defgroup USBD_CDC_IF_Exported_Defines USBD_CDC_IF_Exported_Defines
  * @brief Defines.
  * @{
  */
/* USER CODE BEGIN EXPORTED_DEFINES */
/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */
#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048

/* USER CODE END EXPORTED_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Types USBD_CDC_IF_Exported_Types
  * @brief Types.
  * @{
  */

/* USER CODE BEGIN EXPORTED_TYPES */

/* USER CODE END EXPORTED_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Macros USBD_CDC_IF_Exported_Macros
  * @brief Aliases.
  * @{
  */

/* USER CODE BEGIN EXPORTED_MACRO */

/* USER CODE END EXPORTED_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

/** CDC Interface callback. */
extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_FunctionsPrototype USBD_CDC_IF_Exported_FunctionsPrototype
  * @brief Public functions declaration.
  * @{
  */

uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

/* USER CODE BEGIN EXPORTED_FUNCTIONS */
#pragma pack(1)
typedef struct
{
	uint8_t header;		/*<! ֡ͷ */
	uint8_t detect_color;		/*<! �Է���������ɫ */
//	uint8_t reset_tracker;			/*<! ����׷�� */
//	uint8_t reserved;
	float roll;
	float pit;		/*<! IMU Yaw */
	float yaw;		/*<! IMU Pit */
//	float x;
//	float y;		/*<! IMU Yaw */
//	float z;		/*<! IMU Pit */
	uint16_t  checksum;       /*<! CRCУ���� */
}Sentry_VisionSend_Pack_Usb;
#pragma pack()

typedef union 
{
	uint8_t data[16];
	Sentry_VisionSend_Pack_Usb Pack;
}Sentry_VisionSendMsg_Usb;

#pragma pack(1)
typedef struct  // �Ӿ���Э�� ����һ֡�����ݽṹ��
{
    uint8_t  header; /*<! ��ʼλ */ //0X A5
    uint8_t  enemy;      /*<! �Ƿ���Ŀ�� */
    uint8_t  auto_aim;/*<! �Զ���� */
    float 	 pit;	    /*<! Pit ƫ��Ƕ� */
    float 	 yaw;	    /*<! Yaw ƫ��Ƕ� */
		uint8_t enemy_id; /*<! ����ID */ //0ǰ��վ 1-5���� 6�ڱ� 7����
//		uint8_t detect_id;
//		float    depth;
    uint16_t  checksum;       /*<! CRCУ���� */
//	uint8_t hit;		
} Sentry_VisionRecv_Pack_Usb;
#pragma pack()
typedef union
{
	uint8_t data[14];
	Sentry_VisionRecv_Pack_Usb Pack;
}Sentry_VisionRecvMsg_Usb;


typedef struct 
{
float	Tar_Yaw_Vision;
float	Tar_Pit_Vision;
	
}Vision_Usb;




extern Sentry_VisionRecvMsg_Usb Sentry_Recv_Msg_usb;
extern Sentry_VisionSendMsg_Usb Sentry_Send_Msg_usb;

/* USER CODE END EXPORTED_FUNCTIONS */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CDC_IF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
