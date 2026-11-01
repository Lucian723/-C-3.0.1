#include "Motor_VESC.h"
/**
 ******************************************************************************
 * @file	motor_VESC.c
 * @author  Dong Yangxing
 * @version V1.1.0
 * @date    2026/5/10
 * @brief
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
//VESC上位机设置每个电调的VESC_ID，如需反馈数据，需要在在上位机打开CAN回传
//摩擦轮推荐只打开status1反馈(ERPM，Current，Duty)，反馈ID为(0x900|VESC_ID)
//VESC通信协议资料：https://github.com/vedderb/bldc/blob/master/documentation/comm_can.md

void buffer_append_int16(uint8_t* buffer, int16_t number, int32_t *index) 
{
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) 
{
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_float16(uint8_t* buffer, float number, float scale, int32_t *index) 
{
    buffer_append_int16(buffer, (int16_t)(number * scale), index);
}

void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index) 
{
    buffer_append_int32(buffer, (int32_t)(number * scale), index);
}

void Motor_VESC_Set_Duty(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float duty) 
{
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
	CAN_cmd_shoot1(hcan, VESC_ID | ((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}

void Motor_VESC_Set_Current(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float Current) 
{
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(Current * 1000.0), &send_index);
	CAN_cmd_shoot1(hcan, VESC_ID | ((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

void Motor_VESC_Set_ERPM(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float ERPM) 
{
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)ERPM, &send_index);
	CAN_cmd_shoot1(hcan, VESC_ID | ((uint32_t)CAN_PACKET_SET_RPM << 8), buffer, send_index);
}

void Motor_VESC_Set_Position(CAN_HandleTypeDef *hcan, uint8_t VESC_ID, float Position) 
{
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(Position * 1000000.0), &send_index);
	CAN_cmd_shoot1(hcan, VESC_ID | ((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}

void Motor_VESC_Storage_Status_1(uint8_t *Data, Motor_Data_StructTypeDef *Motor_Data_Struct, uint8_t Pole_Pair)
{
    /*===| 协议解包 |===*/
    Motor_Data_Struct->Speed_RPM = ((int32_t)Data[0]<<24 | (int32_t)Data[1]<<16 | (int32_t)Data[2]<<8 | (int32_t)Data[3]<<0) / Pole_Pair;
    Motor_Data_Struct->Torque = (int16_t)Data[4]<<8 | (int16_t)Data[5]<<0;

    Motor_Data_Struct->Ticker = 0;
    Motor_Data_Struct->If_Online = 1; 
}



