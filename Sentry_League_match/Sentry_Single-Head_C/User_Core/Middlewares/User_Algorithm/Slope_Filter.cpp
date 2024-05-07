/**
 ------------------------------------------------------------------------------
 * @file    Slope_Filter.cpp
 * @author  Shake
 * @brief   �����˲��㷨
 * @version V1.0
 * @date    2022-04
 * @copyright Copyright (c) 2021
 ------------------------------------------------------------------------------
 * @note
   ����ƽ���˲��㷨ֻ����һ�Σ���һ�β���ֵ�͹�ȥ�����ɴβ���ֵһ����ƽ�����õ�����Ч����ֵ����Ͷ��ʹ��
   ���ȡN������ֵ��ƽ�����洢���б��뿪��N�����ݵ��ݴ���
   ÿ�²ɼ�һ�����ݱ�����ݴ����У�ͬʱȥ��һ���������ݣ�������N������ʼ�������¸��µ�����
   ���û��Ͷ��нṹ���Է����ʵ���������ݴ�ŷ�ʽ
   �ŵ㣺
        �������Ը��������õ��������ã�ƽ���ȸ�
        �����ڸ�Ƶ�񵴵�ϵͳ 

   ȱ�㣺
        �����ȵ�
        ��żȻ���ֵ������Ը��ŵ��������ýϲ�
        �������������������������Ĳ���ֵƫ��
        ��������������űȽ����صĳ���
        �Ƚ��˷�RAM
 */

/* Includes ------------------------------------------------------------------*/
#include "Slope_Filter.h"
/* Private macros ------------------------------------------------------------*/
/* function prototypes -------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/

/**
 * @brief   �����˲�����
 * @note    ����������һ�����       
 * @note    len�����൱��һ�����ڵĴ�С �Դ���������ƽ��  
 * @note    �˲����Ȳ�Ҫ����100
 * @note    �����ݴ������鳤�ȣ��滻�������һ�����ݣ��൱�ڻ��ζ��и��£��Ƚ��ȳ�
 * @retval  filter out
 */
float SlopeFilter_Calc(float data ,float *queue ,uint16_t len)
{
	float sum = 0;
	float res = 0;
  
    //�������� FIFO
    for(uint16_t i = 0 ; i < len-1 ; i++)
    {
        //���¶���
        queue[i] = queue[i+1];
    }
    queue[len-1] = data;
    
	//���¶������
	for(uint16_t j = 0 ; j < len ; j++)
	{
		sum += queue[j];
	}
	res = sum/(len);
	
	return res;
}
