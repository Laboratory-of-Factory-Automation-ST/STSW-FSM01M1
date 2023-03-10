/**
  ******************************************************************************
  * @file    fsm01m1_eval_driver.c
  * @author  ST Power Application Laboratory
  * @version V1.0.0
  * @brief   Provides functions for programmable board control and measurement
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fsm01m1_eval_driver.h"

/* Private variables ---------------------------------------------------------*/
extern SPI_HandleTypeDef hspi2;

float VCC_scan  = 0;
float VCC1_scan = 0;
float VCC2_scan = 0;

float OUT1_scan = 0;
float OUT2_scan = 0;

FSM_OperationMode_TypeDef fsm_operation_mode = FSM_MODE_DEFAULT;

/** @defgroup Private Variables
 * @{
 */


/**
 * @}
 */

/* Private functions ---------------------------------------------------------*/
void TimeLoop_test_pulse() {
	uint16_t i;

	for(i = 0; i<0x3FFF; i++);
}

/* Exported functions --------------------------------------------------------*/
void FSM01M1_TimeLoop_Default() {
	uint16_t i,j;

	for(i = 0; i<0xFFFF; i++) {
		for(j = 0; j<0xF; j++);
	}
}

/* 350ms */
void FSM01M1_TimeLoop_Short() {
	uint16_t i,j;

	for(i = 0; i<0x7FFF; i++) {
		for(j = 0; j<0xF; j++);
	}
}

void FSM01M1_TimeLoop_Short_div2() {
	uint16_t i,j;

	for(i = 0; i<0x3FFF; i++) {
		for(j = 0; j<0xF; j++);
	}
}

/**
 * @brief Initial setup testing procedure
 * @retval None
 */
void FSM01M1_initialization() {


	fsm_operation_mode = FSM_MODE_RESET;


	/* Initialization sequence starting - NUCLEO onboard LED LD2 ON */
	FSM01M1_LD2_USER_ON();

	/* USER_LED test */
	FSM01M1_user_LED_green_ON();
	FSM01M1_TimeLoop_Short();

	FSM01M1_user_LED_red_ON();
	FSM01M1_TimeLoop_Short();

	FSM01M1_user_LED_red_OFF();
	FSM01M1_TimeLoop_Short();

	FSM01M1_user_LED_green_OFF();
	FSM01M1_TimeLoop_Short();

	/* VCC1 control test */
	FSM01M1_VCC1_ON();
	FSM01M1_VCC1_DSC_ON();
	FSM01M1_TimeLoop_Short();
	FSM01M1_VCC1_DSC_OFF();

	/* OUT1 control test */
	FSM01M1_OUT1_CTRL_ON();
	FSM01M1_OUT1_DSC_ON();
	FSM01M1_TimeLoop_Short();
	FSM01M1_OUT1_DSC_OFF();

	/* VCC2 control test */
	FSM01M1_VCC2_ON();
	FSM01M1_VCC2_DSC_ON();
	FSM01M1_TimeLoop_Short();
	FSM01M1_VCC2_DSC_OFF();

	/* OUT2 control test */
	FSM01M1_OUT2_CTRL_ON();
	FSM01M1_OUT2_DSC_ON();
	FSM01M1_TimeLoop_Short();
	FSM01M1_OUT2_DSC_OFF();


	FSM01M1_OUT1_CTRL_OFF();
	FSM01M1_OUT2_CTRL_OFF();

	FSM01M1_VCC1_OFF();
	FSM01M1_VCC2_OFF();

	/* Test pulses static setup */
	FSM01M1_TP1_OFF();
	FSM01M1_TP2_OFF();

	FSM01M1_CUTOFF1_CTRL_OFF();
	FSM01M1_CUTOFF2_CTRL_OFF();

	/* Initialization sequence starting - NUCLEO onboard LED LD2 ON */
	FSM01M1_LD2_USER_OFF();
}

/**
 * @brief Turns on user LED
 * @retval None
 */
void FSM01M1_LD2_USER_ON() {
	HAL_GPIO_WritePin(LD2_USER_GPIO_Port, LD2_USER_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off user LED
 * @retval None
 */
void FSM01M1_LD2_USER_OFF() {
	HAL_GPIO_WritePin(LD2_USER_GPIO_Port, LD2_USER_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on green user LED on expansion board
 * @retval None
 */
void FSM01M1_user_LED_green_ON() {
	HAL_GPIO_WritePin(D12_USER_LED_GREEN_GPIO_Port, D12_USER_LED_GREEN_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off green user LED on expansion board
 * @retval None
 */
void FSM01M1_user_LED_green_OFF() {
	HAL_GPIO_WritePin(D12_USER_LED_GREEN_GPIO_Port, D12_USER_LED_GREEN_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on red user LED on expansion board
 * @retval None
 */
void FSM01M1_user_LED_red_ON() {
	HAL_GPIO_WritePin(D13_USER_LED_RED_GPIO_Port, D13_USER_LED_RED_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off red user LED on expansion board
 * @retval None
 */
void FSM01M1_user_LED_red_OFF() {
	HAL_GPIO_WritePin(D13_USER_LED_RED_GPIO_Port, D13_USER_LED_RED_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on VCC1 on expansion board
 * @retval None
 */
void FSM01M1_VCC1_ON() {
	HAL_GPIO_WritePin(VCC1_CTRL_GPIO_Port, VCC1_CTRL_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off VCC1 on expansion board
 * @retval None
 */
void FSM01M1_VCC1_OFF() {
	HAL_GPIO_WritePin(VCC1_CTRL_GPIO_Port, VCC1_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on VCC1_DSC on expansion board
 * @retval None
 */
void FSM01M1_VCC1_DSC_ON() {
	HAL_GPIO_WritePin(VCC1_DSC_GPIO_Port, VCC1_DSC_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off VCC1_DSC on expansion board
 * @retval None
 */
void FSM01M1_VCC1_DSC_OFF() {
	HAL_GPIO_WritePin(VCC1_DSC_GPIO_Port, VCC1_DSC_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on OUT1 on expansion board
 * @retval None
 */
void FSM01M1_OUT1_CTRL_ON() {
	HAL_GPIO_WritePin(OUT1_CTRL_GPIO_Port, OUT1_CTRL_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off OUT1 on expansion board
 * @retval None
 */
void FSM01M1_OUT1_CTRL_OFF() {
	HAL_GPIO_WritePin(OUT1_CTRL_GPIO_Port, OUT1_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on OUT1_DSC on expansion board
 * @retval None
 */
void FSM01M1_OUT1_DSC_ON() {
	HAL_GPIO_WritePin(OUT1_DSC_GPIO_Port, OUT1_DSC_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off OUT1_DSC on expansion board
 * @retval None
 */
void FSM01M1_OUT1_DSC_OFF() {
	HAL_GPIO_WritePin(OUT1_DSC_GPIO_Port, OUT1_DSC_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on COFF1 on expansion board
 * @retval None
 */
void FSM01M1_CUTOFF1_CTRL_ON() {
	HAL_GPIO_WritePin(COFF1_CTRL_GPIO_Port, COFF1_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns off COFF1 on expansion board
 * @retval None
 */
void FSM01M1_CUTOFF1_CTRL_OFF() {
	HAL_GPIO_WritePin(COFF1_CTRL_GPIO_Port, COFF1_CTRL_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns on VCC2 on expansion board
 * @retval None
 */
void FSM01M1_VCC2_ON() {
	HAL_GPIO_WritePin(VCC2_CTRL_GPIO_Port, VCC2_CTRL_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off VCC2 on expansion board
 * @retval None
 */
void FSM01M1_VCC2_OFF() {
	HAL_GPIO_WritePin(VCC2_CTRL_GPIO_Port, VCC2_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on VCC2_DSC on expansion board
 * @retval None
 */
void FSM01M1_VCC2_DSC_ON() {
	HAL_GPIO_WritePin(VCC2_DSC_GPIO_Port, VCC2_DSC_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off VCC2_DSC on expansion board
 * @retval None
 */
void FSM01M1_VCC2_DSC_OFF() {
	HAL_GPIO_WritePin(VCC2_DSC_GPIO_Port, VCC2_DSC_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on OUT2 on expansion board
 * @retval None
 */
void FSM01M1_OUT2_CTRL_ON() {
	HAL_GPIO_WritePin(OUT2_CTRL_GPIO_Port, OUT2_CTRL_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off OUT2 on expansion board
 * @retval None
 */
void FSM01M1_OUT2_CTRL_OFF() {
	HAL_GPIO_WritePin(OUT2_CTRL_GPIO_Port, OUT2_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on OUT2_DSC on expansion board
 * @retval None
 */
void FSM01M1_OUT2_DSC_ON() {
	HAL_GPIO_WritePin(OUT2_DSC_GPIO_Port, OUT2_DSC_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns off OUT2_DSC on expansion board
 * @retval None
 */
void FSM01M1_OUT2_DSC_OFF() {
	HAL_GPIO_WritePin(OUT2_DSC_GPIO_Port, OUT2_DSC_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns on COFF2 on expansion board
 * @retval None
 */
void FSM01M1_CUTOFF2_CTRL_ON() {
	HAL_GPIO_WritePin(COFF2_CTRL_GPIO_Port, COFF2_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns off COFF2 on expansion board
 * @retval None
 */
void FSM01M1_CUTOFF2_CTRL_OFF() {
	HAL_GPIO_WritePin(COFF2_CTRL_GPIO_Port, COFF2_CTRL_Pin, GPIO_PIN_SET);
}

/* DIGITAL INPUT - test pulse control */

/**
 * @brief Turns on TP1 on expansion board
 * @retval None
 */
void FSM01M1_TP1_ON() {
	HAL_GPIO_WritePin(TP1_CTRL_GPIO_Port, TP1_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns off TP1 on expansion board
 * @retval None
 */
void FSM01M1_TP1_OFF() {
	HAL_GPIO_WritePin(TP1_CTRL_GPIO_Port, TP1_CTRL_Pin, GPIO_PIN_SET);
}

/**
 * @brief Turns on TP2 on expansion board
 * @retval None
 */
void FSM01M1_TP2_ON() {
	HAL_GPIO_WritePin(TP2_CTRL_GPIO_Port, TP2_CTRL_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Turns off TP2 on expansion board
 * @retval None
 */
void FSM01M1_TP2_OFF() {
	HAL_GPIO_WritePin(TP2_CTRL_GPIO_Port, TP2_CTRL_Pin, GPIO_PIN_SET);
}

/* SPI communication control */

uint8_t FSM01M1_ADC120_control_register_assembler(uint8_t adc_channel_id) {

	/* address validation */
	if(adc_channel_id >= ADC120_CHANNELS_COUNT) {
		/* invalid address -> select default channel */
		adc_channel_id = ADC120_DEFAULT_CHANNEL_ID;
	}

	adc_channel_id <<= 3;

	return adc_channel_id;
}

uint16_t FSM01M1_SPI_frame_assembler(uint8_t adc_control_register) {

	uint16_t adc_spi_tx_frame = 0;

	adc_spi_tx_frame = adc_control_register;
	adc_spi_tx_frame <<= 8;

	return adc_spi_tx_frame;
}

uint16_t FSM01M1_SPI_ADC120_channel_read(SPI_HandleTypeDef *SpiHandle,
		uint8_t adc_channel_id) {

	uint16_t adc_readout = 0;

	adc_readout = ADC120_channel_read(SpiHandle, adc_channel_id);

	return adc_readout;
}

float FSM01M1_ADC120_translate_to_analog(uint16_t adc_value) {

	float analog_val = 0;

	analog_val = adc_value * FSM01M1_NOMINAL_VDD / ADC120_MAX_VALUE;

	return analog_val;
}

float FSM01M1_ADC120_rescale_analog(float analog_val) {

	analog_val = analog_val * FSM01M1_VSENSE_RESCALE_FACTOR;
	analog_val += FSM01M1_STPS_FORWARD_VOLTAGE;

	return analog_val;
}

float FSM01M1_ADC120_read_blind(SPI_HandleTypeDef *SpiHandle) {
	uint16_t adc_readout = 0;
	float voltage_scan = 0.0;

	/* Turn-ON ADC */
	HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_RESET);

	/* Scan requested channel, define next */
	adc_readout = ADC120_channel_read(SpiHandle, VCC1_ADC_CHANNEL_ID);
	voltage_scan = FSM01M1_ADC120_translate_to_analog(adc_readout);
	voltage_scan = FSM01M1_ADC120_rescale_analog(voltage_scan);

	/* Shut-down ADC */
	HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_SET);

	return voltage_scan;
}

float FSM01M1_ADC120_read_single_node(SPI_HandleTypeDef *SpiHandle, uint8_t voltage_channel_id) {

	uint16_t adc_readout = 0;
	float voltage_scan = 0.0;

	/* Turn-ON ADC */
	HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_RESET);

	/* First dummy scan */
	adc_readout = ADC120_channel_read(SpiHandle, voltage_channel_id);

	/* Scan requested channel, VCC1 next */
	adc_readout = ADC120_channel_read(SpiHandle, VCC1_ADC_CHANNEL_ID);
	voltage_scan = FSM01M1_ADC120_translate_to_analog(adc_readout);
	voltage_scan = FSM01M1_ADC120_rescale_analog(voltage_scan);

	/* Shut-down ADC */
	HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_SET);

	return voltage_scan;
}

uint8_t FSM01M1_scan_voltage_vector(SPI_HandleTypeDef *SpiHandle) {
	uint16_t adc_readout = 0;
	float voltage_scan = 0.0;

	/* Turn-ON ADC */
	HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_RESET);

	/* VCC1 scan */
	/* First read returns DEFAULT value (ADC IN0 = VCC1) */
	adc_readout = ADC120_channel_read(SpiHandle, OUT1_ADC_CHANNEL_ID);
	voltage_scan = FSM01M1_ADC120_translate_to_analog(adc_readout);
	VCC1_scan = FSM01M1_ADC120_rescale_analog(voltage_scan);

	/* OUT1 scan, VCC2 next */
	adc_readout = ADC120_channel_read(SpiHandle, VCC2_ADC_CHANNEL_ID);
	voltage_scan = FSM01M1_ADC120_translate_to_analog(adc_readout);
	OUT1_scan = FSM01M1_ADC120_rescale_analog(voltage_scan);

	/* VCC2 scan, OUT2 next */
	adc_readout = ADC120_channel_read(SpiHandle, OUT2_ADC_CHANNEL_ID);
	voltage_scan = FSM01M1_ADC120_translate_to_analog(adc_readout);
	VCC2_scan = FSM01M1_ADC120_rescale_analog(voltage_scan);

	/* OUT2 scan, VCC next */
	adc_readout = ADC120_channel_read(SpiHandle, VCC_ADC_CHANNEL_ID);
	voltage_scan = FSM01M1_ADC120_translate_to_analog(adc_readout);
	OUT2_scan = FSM01M1_ADC120_rescale_analog(voltage_scan);

	/* VCC scan, VCC1 next */
	adc_readout = ADC120_channel_read(SpiHandle, VCC1_ADC_CHANNEL_ID);
	voltage_scan = FSM01M1_ADC120_translate_to_analog(adc_readout);
	VCC_scan = FSM01M1_ADC120_rescale_analog(voltage_scan);

	/* Shut-down ADC */
	HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_SET);

	return 0;
}

void FSM01M1_B1_USER_activation_callback() {

	/* Acknowledge eventual dignostic events */
	FSM01M1_user_LED_red_OFF();
	FSM01M1_LD2_USER_ON();

	switch(fsm_operation_mode) {

		case (FSM_MODE_OUT1_OUT2_ON): {
			/* Output passivation */
			FSM01M1_OUT1_CTRL_OFF();
			FSM01M1_OUT2_CTRL_OFF();
			fsm_operation_mode = FSM_MODE_OUT1_OUT2_OFF;
			break;
		}
		case (FSM_MODE_DEFAULT):
		case (FSM_MODE_RESET):
		case (FSM_MODE_OUT1_OUT2_OFF): {
			/* Output activation */
			FSM01M1_OUT1_CTRL_ON();
			FSM01M1_OUT2_CTRL_ON();
			fsm_operation_mode = FSM_MODE_OUT1_OUT2_ON;
		}
		default: break;
	}
	FSM01M1_LD2_USER_OFF();
	return;
}

void FSM01M1_IN1_activation_callback() {
	  FSM01M1_LD2_USER_ON();
	  FSM01M1_TimeLoop_Default();

	  FSM01M1_LD2_USER_OFF();
	  FSM01M1_TimeLoop_Default();
}

void FSM01M1_IN2_activation_callback() {
	FSM01M1_LD2_USER_ON();
	  FSM01M1_TimeLoop_Default();

	  FSM01M1_LD2_USER_OFF();
	  FSM01M1_TimeLoop_Default();
}

void FSM01M1_OUT1_DIAG_alert_callback() {

	/* Detect edge direction (rising/falling) */
	if(HAL_GPIO_ReadPin(OUT1_DIAG_GPIO_Port, OUT1_DIAG_Pin) == GPIO_PIN_SET) {
		/* Rising edge detected */
//		STEVAL_FSM01M1_user_LED_red_OFF();
	} else {
		/* Falling edge detected */
		FSM01M1_user_LED_red_ON();
	}
}

void FSM01M1_OUT2_DIAG_alert_callback() {

	/* Detect edge direction (rising/falling) */
	if(HAL_GPIO_ReadPin(OUT2_DIAG_GPIO_Port, OUT2_DIAG_Pin) == GPIO_PIN_SET) {
		/* Rising edge detected */
//		STEVAL_FSM01M1_user_LED_red_OFF();
	} else {
		/* Falling edge detected */
		FSM01M1_user_LED_red_ON();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin) {
		case (B1_USER_Pin): {
			FSM01M1_B1_USER_activation_callback();
			break;
		}
		case (OUTP1_Pin): {
			FSM01M1_IN1_activation_callback();
			break;
		}
		case (OUTP2_Pin): {
			FSM01M1_IN2_activation_callback();
			break;
		}
		case (OUT1_DIAG_Pin): {
			FSM01M1_OUT1_DIAG_alert_callback();
			break;
		}
		case (OUT2_DIAG_Pin): {
			FSM01M1_OUT2_DIAG_alert_callback();
			break;
		}
		/* Other interupt callbacks to be added */
		default: break;
	}
}
