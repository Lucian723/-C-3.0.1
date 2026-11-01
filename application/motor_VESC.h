#ifndef __Motor_VESC__
#define __Motor_VESC__

#include "main.h"

typedef enum 
{
	CAN_PACKET_SET_DUTY = 0,
	CAN_PACKET_SET_CURRENT,
	CAN_PACKET_SET_CURRENT_BRAKE,
	CAN_PACKET_SET_RPM,
	CAN_PACKET_SET_POS,
	CAN_PACKET_SET_CURRENT_REL = 10,
	CAN_PACKET_SET_CURRENT_BRAKE_REL,
	CAN_PACKET_SET_CURRENT_HANDBRAKE,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
	CAN_PACKET_MAKE_ENUM_32_BITS = 0xFFFFFFFF,
} CAN_PACKET_ID;

typedef struct
{
    int16_t Encoder;        //编码器值
    int16_t Encoder_Last;   //上一个编码器值
    int32_t Round;          //圈数
    float Angle;            //绝对角度   
    float Angle_Last;       //上一个绝对角度     
    float Total_Angle;      //总角度值
    float Total_Angle_Last; //总角度值
    float Total_Angle_Speed_RPM; //总角度值速度
    float Total_Angle_Speed_RPM_Last; //总角度值速度
    float Total_Angle_Offset;      //总角度值零点
    uint32_t Total_Angle_DWT_Count;
    float Speed_RPM;        //转速[RPM]
    float Torque;           //力矩[电流]
    int8_t Temperature;     //电机温度
    uint16_t Ticker;        //收到数据计时
    uint8_t If_Online;      //是否在线     
} Motor_Data_StructTypeDef;


void Motor_VESC_Set_Duty(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float duty);
void Motor_VESC_Set_Current(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float Current); 
void Motor_VESC_Set_ERPM(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float ERPM); 
void Motor_VESC_Set_Position(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float Position); 
void Motor_VESC_Storage_Status_1(uint8_t *Data, Motor_Data_StructTypeDef *Motor_Data_Struct, uint8_t Pole_Pair);

#endif