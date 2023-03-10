/**
  ******************************************************************************
  * @file    adc120.c
  * @author  ST Power Application Laboratory
  * @version V1.0.0
  * @brief   Provides functions for control of ADC120 component
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
#include "adc120.h"

/* Private function prototypes -----------------------------------------------*/
void ADC120_ErrorHandler(uint16_t error);

/* Private variables ---------------------------------------------------------*/
static uint8_t adc_spi_tx_buffer[2] = {0,0};
static uint8_t adc_spi_rx_buffer[2] = {0,0};

/** Function pointer to error handler call back */
static void (*pErrorHandlerCallback)(uint16_t);

static adc120Drv_t adc120Drv = {
	ADC120_Init,                         /* void (*Init)(void*); */
	ADC120_AttachErrorHandler,           /* void (*AttachErrorHandler)(void (*callback)(uint16_t)); */
	ADC120_ErrorHandler,	             /* void (*ErrorHandler)(uint16_t); */
	Adc120_ReadAdcChannel				 /* uint8_t (*ReadAdcChannel)(uint8_t) */
};


/******************************************************//**
 * @brief Starts a new ADC120 instance
 * @param[in] pInit pointer to the initialization data
 * @retval None
 **********************************************************/
void ADC120_Init(void* pInit)
{
}

/******************************************************//**
 * @brief  Attaches a user callback to the error Handler.
 * The call back will be then called each time the library
 * detects an error
 * @param[in] callback Name of the callback to attach
 * to the error Hanlder
 * @retval None
 **********************************************************/
void ADC120_AttachErrorHandler(void (*callback)(uint16_t))
{
  pErrorHandlerCallback = (void (*)(uint16_t))callback;
}

/******************************************************//**
 * @brief Error handler which calls the user callback (if defined)
 * @param[in] error Number of the error
 * @retval None
 **********************************************************/
void ADC120_ErrorHandler(uint16_t error)
{
  if (pErrorHandlerCallback != (void *)0)
  {
    (void) pErrorHandlerCallback(error);
  }
  else
  {
    while(1)
    {
      /* Infinite loop */
    }
  }
}

/* SPI communication control */

uint8_t ADC120_control_register_assembler(uint8_t adc_channel_id) {

	/* address validation */
	if(adc_channel_id >= ADC120_CHANNELS_COUNT) {
		/* invalid address -> select default channel */
		adc_channel_id = ADC120_DEFAULT_CHANNEL_ID;
	}

	adc_channel_id <<= 3;

	return adc_channel_id;
}

uint16_t ADC120_SPI_frame_assembler(uint8_t adc_control_register) {

	uint16_t adc_spi_tx_frame = 0;

	adc_spi_tx_frame = adc_control_register;
	adc_spi_tx_frame <<= 8;

	return adc_spi_tx_frame;
}

uint16_t ADC120_channel_read(SPI_HandleTypeDef *SpiHandle, uint8_t adc_channel_id) {

	HAL_StatusTypeDef status = HAL_OK;

	uint16_t adc_readout = 0;

	/* assemble TX frame */
	adc_spi_tx_buffer[0] = 0;
	adc_spi_tx_buffer[1] = ADC120_control_register_assembler(adc_channel_id);

	//HAL_GPIO_WritePin(SPI_NSS_PORT, SPI_NSS_PIN, GPIO_PIN_RESET);

	/* read ADC */
	status = HAL_SPI_TransmitReceive(SpiHandle, adc_spi_tx_buffer, adc_spi_rx_buffer, 1, SPIx_TIMEOUT_MAX);

	//HAL_GPIO_WritePin(SPI_NSS_PORT, SPI_NSS_PIN, GPIO_PIN_SET);

	if (status != HAL_OK) {
		while(1);
	}

	/* disassemble RX frame */
	adc_readout = adc_spi_rx_buffer[1];
	adc_readout <<= 8;
	adc_readout |= (uint16_t) adc_spi_rx_buffer[0];

	/* secure 12b data extraction */
	adc_readout &= ADC120_DATA_MASK;

	return adc_readout;
}

/******************************************************//**
 * @brief Read defined ADC120 channel via SPI
 * @param ADC120 channel to read
 * @retval specific ADC120 channel value
 **********************************************************/
uint8_t Adc120_ReadAdcChannel(uint8_t channel_id)
{
	return 0;
}

/******************************************************//**
 * @brief Return ADC120 handle (pointer to the ADC120 driver structure)
 * @retval Pointer to the adc120Drv_t structure
 **********************************************************/
adc120Drv_t* ADC120_GetAdc120Handle(void)
{
  return (&adc120Drv);
}





