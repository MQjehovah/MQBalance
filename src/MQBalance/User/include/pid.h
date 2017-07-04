/*******************************************************************************
  * @file                   pid.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.3
  * @date                   2017.5.24
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef  _PID_H
#define  _PID_H

/* Includes ------------------------------------------------------------------*/

/* Definition ----------------------------------------------------------------*/
typedef struct
{
	double eP;
	double eI;
	double eD;
	double kP;
	double kI;
	double kD;
	double lastErr;
	double preErr;
	double OUT;
}PID_Type;
/* Exported Functions --------------------------------------------------------*/
int LocPIDCalc(PID_Type *PID,int cur_err);
int IncPIDCalc(PID_Type *PID,int cur_err);

#endif
/*********************************END OF FILE**********************************/
