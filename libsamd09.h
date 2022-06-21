#ifndef LIBSAMD09_H
#define LIBSAMD09_H


#define RTC_BASE 0x40001400
#define TC1_BASE 0x42001800
#define TC2_BASE 0x42001C00
#define SERCOM0_BASE 0x42000800
#define SERCOM1_BASE 0x42000C00


#define SYSTICK ((struct systick *)0xE000E010)

struct systick {

	/* 0x00: SysTick Control and Status Register */
	uint32_t volatile CSR;
	/* Enable SysTick Timer */
#define SYSTICK_CSR_ENABLE                                      (1u << 0)
	/* Generate Tick Interrupt */
#define SYSTICK_CSR_TICKINT                                     (1u << 1)
	/* Source to count from */
#define SYSTICK_CSR_CLKSOURCE                                   (1u << 2)
	/* SysTick counted to zero */
#define SYSTICK_CSR_COUNTFLAG                                   (1u << 16)

	/* 0x04: SysTick Reload Value Register */
	uint32_t volatile RVR;

	/* 0x08: SysTick Current Value Register */
	uint32_t volatile CVR;

	/* 0x0C: SysTick Calibration Value Register */
	uint32_t volatile CALIB;
	/* Reload value to use for 10ms timing */
#define SYSTICK_CALIB_TENMS_Msk                                 (0xFFFFFFu << 0)
#define SYSTICK_CALIB_TENMS_Pos                                 0
	/* Clock Skew */
#define SYSTICK_CALIB_SKEW                                      (1u << 30)
	/* No Ref */
#define SYSTICK_CALIB_NOREF                                     (1u << 31)

};


#define NVIC ((struct nvic *)0xE000E100)

struct nvic {

	/* 0x00: Interrupt Set Enable Register */
	uint32_t volatile ISER;

	/* 0x04 */
	uint8_t RESERVED1[0x80-0x04];

	/* 0x80: Interrupt Clear Enable Register */
	uint32_t volatile ICER;

	/* 0x84 */
	uint8_t RESERVED2[0x100-0x84];

	/* 0x100: Interrupt Set-Pending Register */
	uint32_t volatile ISPR;

	/* 0x104 */
	uint8_t RESERVED3[0x180-0x104];

	/* 0x180: Interrupt Clear-Pending Register */
	uint32_t volatile ICPR;

	/* 0x184 */
	uint8_t RESERVED4[0x300-0x184];

	/* 0x300: Interrupt Priority Registers */
	uint32_t volatile IPR[8];

};


#define ADC ((struct adc *)0x42002000)

struct adc {

	/* 0x00: Control A */
	uint8_t volatile CTRLA;
	/* Software Reset */
#define ADC_CTRLA_SWRST						(1u << 0)
	/* Enable */
#define ADC_CTRLA_ENABLE					(1u << 1)
	/* Run in Standby */
#define ADC_CTRLA_RUNSTDBY					(1u << 2)

	/* 0x01: Reference Control */
	uint8_t volatile REFCTRL;
	/* Reference Selection */
#define ADC_REFCTRL_REFSEL_Msk					(0xFu << 0)
#define ADC_REFCTRL_REFSEL_Pos					0
#define ADC_REFCTRL_REFSEL_INT1V				(0x0u << 0)
#define ADC_REFCTRL_REFSEL_INTVCC0				(0x1u << 0)
#define ADC_REFCTRL_REFSEL_INTVCC1				(0x2u << 0)
#define ADC_REFCTRL_REFSEL_AREFA				(0x3u << 0)
#define ADC_REFCTRL_REFSEL_AREFB				(0x4u << 0)
	/* Reference Buffer Offset Compensation Enable */
#define ADC_REFCTRL_REFCOMP					(1u << 7)

	/* 0x02: Average Control */
	uint8_t volatile AVGCTRL;
	/* Number of Samples to be Collected */
#define ADC_AVGCTRL_SAMPLENUM_Msk				(0xFu << 0)
#define ADC_AVGCTRL_SAMPLENUM_Pos				0
#define ADC_AVGCTRL_SAMPLENUM_1					(0x0u << 0)
#define ADC_AVGCTRL_SAMPLENUM_2					(0x1u << 0)
#define ADC_AVGCTRL_SAMPLENUM_4					(0x2u << 0)
#define ADC_AVGCTRL_SAMPLENUM_8					(0x3u << 0)
#define ADC_AVGCTRL_SAMPLENUM_16				(0x4u << 0)
#define ADC_AVGCTRL_SAMPLENUM_32				(0x5u << 0)
#define ADC_AVGCTRL_SAMPLENUM_64				(0x6u << 0)
#define ADC_AVGCTRL_SAMPLENUM_128				(0x7u << 0)
#define ADC_AVGCTRL_SAMPLENUM_256				(0x8u << 0)
#define ADC_AVGCTRL_SAMPLENUM_512				(0x9u << 0)
#define ADC_AVGCTRL_SAMPLENUM_1024				(0xAu << 0)
	/* Adjusting Result / Division Coefficient */
#define ADC_AVGCTRL_ADJRES_Msk					(0x7u << 4)
#define ADC_AVGCTRL_ADJRES_Pos					4

	/* 0x03: Sampling Time Control */
	uint8_t volatile SAMPCTRL;
	/* Sampling Time Length */
#define ADC_SAMPCTRL_SAMPLEN_Msk				(0x3Fu << 0)
#define ADC_SAMPCTRL_SAMPLEN_Pos				0

	/* 0x04: Control B */
	uint16_t volatile CTRLB;
	/* Differential Mode */
#define ADC_CTRLB_DIFFMODE					(1u << 0)
	/* Left-Adjusted Result */
#define ADC_CTRLB_LEFTADJ					(1u << 1)
	/* Free Running Mode */
#define ADC_CTRLB_FREERUN					(1u << 2)
	/* Digital Correction Logic Enabled */
#define ADC_CTRLB_CORREN					(1u << 3)
	/* Conversion Result Resolution */
#define ADC_CTRLB_RESSEL_Msk					(0x3u << 4)
#define ADC_CTRLB_RESSEL_Pos					4
#define ADC_CTRLB_RESSEL_12BIT					(0x0u << 4)
#define ADC_CTRLB_RESSEL_16BIT					(0x1u << 4)
#define ADC_CTRLB_RESSEL_10BIT					(0x2u << 4)
#define ADC_CTRLB_RESSEL_8BIT					(0x3u << 4)
	/* Prescaler Configuration */
#define ADC_CTRLB_PRESCALER_Msk					(0x7u << 8)
#define ADC_CTRLB_PRESCALER_Pos					8
#define ADC_CTRLB_PRESCALER_DIV4				(0x0u << 8)
#define ADC_CTRLB_PRESCALER_DIV8				(0x1u << 8)
#define ADC_CTRLB_PRESCALER_DIV16				(0x2u << 8)
#define ADC_CTRLB_PRESCALER_DIV32				(0x3u << 8)
#define ADC_CTRLB_PRESCALER_DIV64				(0x4u << 8)
#define ADC_CTRLB_PRESCALER_DIV128				(0x5u << 8)
#define ADC_CTRLB_PRESCALER_DIV256				(0x6u << 8)
#define ADC_CTRLB_PRESCALER_DIV512				(0x7u << 8)

	/* 0x06 */
	uint8_t RESERVED0[0x08u-0x06u];

	/* 0x08: Window Monitor Control */
	uint8_t volatile WINCTRL;
	/* Window Monitor Mode */
#define ADC_WINCTRL_WINMODE_Msk					(0x7u << 0)
#define ADC_WINCTRL_WINMODE_Pos					0
#define ADC_WINCTRL_WINMODE_DISABLE				(0x0u << 0)
#define ADC_WINCTRL_WINMODE_MODE1				(0x1u << 0)
#define ADC_WINCTRL_WINMODE_MODE2				(0x2u << 0)
#define ADC_WINCTRL_WINMODE_MODE3				(0x3u << 0)
#define ADC_WINCTRL_WINMODE_MODE4				(0x4u << 0)

	/* 0x09 */
	uint8_t RESERVED1[0x0Cu-0x09u];

	/* 0x0C: Software Trigger */
	uint8_t volatile SWTRIG;
	/* ADC Conversion Flush */
#define ADC_SWTRIG_FLUSH					(1u << 0)
	/* ADC Start Conversion */
#define ADC_SWTRIG_START					(1u << 1)

	/* 0x0D */
	uint8_t RESERVED2[0x10u-0x0Du];

	/* 0x10: Input Control */
	uint32_t volatile INPUTCTRL;
	/* Positive Mux Input Selection */
#define ADC_INPUTCTRL_MUXPOS_Msk				(0x1Fu << 0)
#define ADC_INPUTCTRL_MUXPOS_Pos				0
#define ADC_INPUTCTRL_MUXPOS_PIN0				(0x0u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN1				(0x1u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN2				(0x2u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN3				(0x3u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN4				(0x4u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN5				(0x5u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN6				(0x6u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN7				(0x7u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN8				(0x8u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN9				(0x9u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN10				(0xAu << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN11				(0xBu << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN12				(0xCu << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN13				(0xDu << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN14				(0xEu << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN15				(0xFu << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN16				(0x10u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN17				(0x11u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN18				(0x12u << 0)
#define ADC_INPUTCTRL_MUXPOS_PIN19				(0x13u << 0)
#define ADC_INPUTCTRL_MUXPOS_TEMP				(0x18u << 0)
#define ADC_INPUTCTRL_MUXPOS_BANDGAP				(0x19u << 0)
#define ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC			(0x1Au << 0)
#define ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC			(0x1Bu << 0)
	/* Negative Mux Input Selection */
#define ADC_INPUTCTRL_MUXNEG_Msk				(0x1Fu << 8)
#define ADC_INPUTCTRL_MUXNEG_Pos				8
#define ADC_INPUTCTRL_MUXNEG_PIN0				(0x0u << 8)
#define ADC_INPUTCTRL_MUXNEG_PIN1				(0x1u << 8)
#define ADC_INPUTCTRL_MUXNEG_PIN2				(0x2u << 8)
#define ADC_INPUTCTRL_MUXNEG_PIN3				(0x3u << 8)
#define ADC_INPUTCTRL_MUXNEG_PIN4				(0x4u << 8)
#define ADC_INPUTCTRL_MUXNEG_PIN5				(0x5u << 8)
#define ADC_INPUTCTRL_MUXNEG_PIN6				(0x6u << 8)
#define ADC_INPUTCTRL_MUXNEG_PIN7				(0x7u << 8)
#define ADC_INPUTCTRL_MUXNEG_GND				(0x18u << 8)
#define ADC_INPUTCTRL_MUXNEG_IOGND				(0x19u << 8)
	/* Number of Input Channels Included in Scan */
#define ADC_INPUTCTRL_INPUTSCAN_Msk				(0xFu << 16)
#define ADC_INPUTCTRL_INPUTSCAN_Pos				16
	/* Positive Mux Setting Offset */
#define ADC_INPUTCTRL_INPUTOFFSET_Msk				(0xFu << 20)
#define ADC_INPUTCTRL_INPUTOFFSET_Pos				20
	/* Gain Factor Selection */
#define ADC_INPUTCTRL_GAIN_Msk					(0xFu << 24)
#define ADC_INPUTCTRL_GAIN_Pos					24
#define ADC_INPUTCTRL_GAIN_1X					(0x0u << 24)
#define ADC_INPUTCTRL_GAIN_2X					(0x1u << 24)
#define ADC_INPUTCTRL_GAIN_4X					(0x2u << 24)
#define ADC_INPUTCTRL_GAIN_8X					(0x3u << 24)
#define ADC_INPUTCTRL_GAIN_16X					(0x4u << 24)
#define ADC_INPUTCTRL_GAIN_DIV2					(0xFu << 24)

	/* 0x14: Event Control */
	uint8_t volatile EVCTRL;
	/* Start Conversion Event In */
#define ADC_EVCTRL_STARTEI					(1u << 0)
	/* Synchronization Event In */
#define ADC_EVCTRL_SYNCEI					(1u << 1)
	/* Result Ready Event Out */
#define ADC_EVCTRL_RESRDYEO					(1u << 4)
	/* Window Monitor Event Out */
#define ADC_EVCTRL_WINMONEO					(1u << 5)

	/* 0x15 */
	uint8_t RESERVED3[0x16u-0x15u];

	/* 0x16: Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Result Ready Interrupt Enable */
#define ADC_INTENCLR_RESRDY					(1u << 0)
	/* Overrun Interrupt Enable */
#define ADC_INTENCLR_OVERRUN					(1u << 1)
	/* Window Monitor Interrupt Enable */
#define ADC_INTENCLR_WINMON					(1u << 2)
	/* Synchronization Ready Interrupt Enable */
#define ADC_INTENCLR_SYNCRDY					(1u << 3)

	/* 0x17: Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Result Ready Interrupt Enable */
#define ADC_INTENSET_RESRDY					(1u << 0)
	/* Overrun Interrupt Enable */
#define ADC_INTENSET_OVERRUN					(1u << 1)
	/* Window Monitor Interrupt Enable */
#define ADC_INTENSET_WINMON					(1u << 2)
	/* Synchronization Ready Interrupt Enable */
#define ADC_INTENSET_SYNCRDY					(1u << 3)

	/* 0x18: Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Result Ready */
#define ADC_INTFLAG_RESRDY					(1u << 0)
	/* Overrun */
#define ADC_INTFLAG_OVERRUN					(1u << 1)
	/* Window Monitor */
#define ADC_INTFLAG_WINMON					(1u << 2)
	/* Synchronization Ready */
#define ADC_INTFLAG_SYNCRDY					(1u << 3)

	/* 0x19: Status */
	uint8_t volatile const STATUS;
	/* Synchronization Busy */
#define ADC_STATUS_SYNCBUSY					(1u << 7)

	/* 0x1A: Result */
	uint16_t volatile const RESULT;
	/* Result Conversion Value */
#define ADC_RESULT_RESULT_Msk					(0xFFFFu << 0)
#define ADC_RESULT_RESULT_Pos					0

	/* 0x1C: Window Monitor Lower Threshold */
	uint16_t volatile WINLT;
	/* Window Lower Threshold */
#define ADC_WINLT_WINLT_Msk					(0xFFFFu << 0)
#define ADC_WINLT_WINLT_Pos					0

	/* 0x1E */
	uint8_t RESERVED4[0x20u-0x1Eu];

	/* 0x20: Window Monitor Upper Threshold */
	uint16_t volatile WINUT;
	/* Window Upper Threshold */
#define ADC_WINUT_WINUT_Msk					(0xFFFFu << 0)
#define ADC_WINUT_WINUT_Pos					0

	/* 0x22 */
	uint8_t RESERVED5[0x24u-0x22u];

	/* 0x24: Gain Correction */
	uint16_t volatile GAINCORR;
	/* Gain Correction Value */
#define ADC_GAINCORR_GAINCORR_Msk				(0xFFFu << 0)
#define ADC_GAINCORR_GAINCORR_Pos				0

	/* 0x26: Offset Correction */
	uint16_t volatile OFFSETCORR;
	/* Offset Correction Value */
#define ADC_OFFSETCORR_OFFSETCORR_Msk				(0xFFFu << 0)
#define ADC_OFFSETCORR_OFFSETCORR_Pos				0

	/* 0x28: Calibration */
	uint16_t volatile CALIB;
	/* Linearity Calibration Value */
#define ADC_CALIB_LINEARITY_CAL_Msk				(0xFFu << 0)
#define ADC_CALIB_LINEARITY_CAL_Pos				0
	/* Bias Calibration Value */
#define ADC_CALIB_BIAS_CAL_Msk					(0x7u << 8)
#define ADC_CALIB_BIAS_CAL_Pos					8

	/* 0x2A: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Run */
#define ADC_DBGCTRL_DBGRUN					(1u << 0)

};


#define DMAC ((struct dmac *)0x41004800)

struct dmac {

	/* 0x00: Control */
	uint16_t volatile CTRL;
	/* Software Reset */
#define DMAC_CTRL_SWRST						(1u << 0)
	/* DMA Enable */
#define DMAC_CTRL_DMAENABLE					(1u << 1)
	/* CRC Enable */
#define DMAC_CTRL_CRCENABLE					(1u << 2)
	/* Priority Level 0 Enable */
#define DMAC_CTRL_LVLEN0					(1u << 8)
	/* Priority Level 1 Enable */
#define DMAC_CTRL_LVLEN1					(1u << 9)
	/* Priority Level 2 Enable */
#define DMAC_CTRL_LVLEN2					(1u << 10)
	/* Priority Level 3 Enable */
#define DMAC_CTRL_LVLEN3					(1u << 11)

	/* 0x02: CRC Control */
	uint16_t volatile CRCCTRL;
	/* CRC Beat Size */
#define DMAC_CRCCTRL_CRCBEATSIZE_Msk				(0x3u << 0)
#define DMAC_CRCCTRL_CRCBEATSIZE_Pos				0
#define DMAC_CRCCTRL_CRCBEATSIZE_BYTE				(0x0u << 0)
#define DMAC_CRCCTRL_CRCBEATSIZE_HWORD				(0x1u << 0)
#define DMAC_CRCCTRL_CRCBEATSIZE_WORD				(0x2u << 0)
	/* CRC Polynomial Type */
#define DMAC_CRCCTRL_CRCPOLY_Msk				(0x3u << 2)
#define DMAC_CRCCTRL_CRCPOLY_Pos				2
#define DMAC_CRCCTRL_CRCPOLY_CRC16				(0x0u << 2)
#define DMAC_CRCCTRL_CRCPOLY_CRC32				(0x1u << 2)
	/* CRC Input Source */
#define DMAC_CRCCTRL_CRCSRC_Msk					(0x3Fu << 8)
#define DMAC_CRCCTRL_CRCSRC_Pos					8
#define DMAC_CRCCTRL_CRCSRC_NOACT				(0x0u << 8)
#define DMAC_CRCCTRL_CRCSRC_IO					(0x1u << 8)

	/* 0x04: CRC Data Input */
	uint32_t volatile CRCDATAIN;
	/* CRC Data Input */
#define DMAC_CRCDATAIN_CRCDATAIN_Msk				(0xFFFFFFFFu << 0)
#define DMAC_CRCDATAIN_CRCDATAIN_Pos				0

	/* 0x08: CRC Checksum */
	uint32_t volatile CRCCHKSUM;
	/* CRC Checksum */
#define DMAC_CRCCHKSUM_CRCCHKSUM_Msk				(0xFFFFFFFFu << 0)
#define DMAC_CRCCHKSUM_CRCCHKSUM_Pos				0

	/* 0x0C: CRC Status */
	uint8_t volatile CRCSTATUS;
	/* CRC Module Busy */
#define DMAC_CRCSTATUS_CRCBUSY					(1u << 0)
	/* CRC Zero */
#define DMAC_CRCSTATUS_CRCZERO					(1u << 1)

	/* 0x0D: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Run */
#define DMAC_DBGCTRL_DBGRUN					(1u << 0)

	/* 0x0E: QOS Control */
	uint8_t volatile QOSCTRL;
	/* Write-Back Quality of Service */
#define DMAC_QOSCTRL_WRBQOS_Msk					(0x3u << 0)
#define DMAC_QOSCTRL_WRBQOS_Pos					0
#define DMAC_QOSCTRL_WRBQOS_DISABLE				(0x0u << 0)
#define DMAC_QOSCTRL_WRBQOS_LOW					(0x1u << 0)
#define DMAC_QOSCTRL_WRBQOS_MEDIUM				(0x2u << 0)
#define DMAC_QOSCTRL_WRBQOS_HIGH				(0x3u << 0)
	/* Fetch Quality of Service */
#define DMAC_QOSCTRL_FQOS_Msk					(0x3u << 2)
#define DMAC_QOSCTRL_FQOS_Pos					2
#define DMAC_QOSCTRL_FQOS_DISABLE				(0x0u << 2)
#define DMAC_QOSCTRL_FQOS_LOW					(0x1u << 2)
#define DMAC_QOSCTRL_FQOS_MEDIUM				(0x2u << 2)
#define DMAC_QOSCTRL_FQOS_HIGH					(0x3u << 2)
	/* Data Transfer Quality of Service */
#define DMAC_QOSCTRL_DQOS_Msk					(0x3u << 4)
#define DMAC_QOSCTRL_DQOS_Pos					4
#define DMAC_QOSCTRL_DQOS_DISABLE				(0x0u << 4)
#define DMAC_QOSCTRL_DQOS_LOW					(0x1u << 4)
#define DMAC_QOSCTRL_DQOS_MEDIUM				(0x2u << 4)
#define DMAC_QOSCTRL_DQOS_HIGH					(0x3u << 4)

	/* 0x0F */
	uint8_t RESERVED0[0x10u-0x0Fu];

	/* 0x10: Software Trigger Control */
	uint32_t volatile SWTRIGCTRL;
	/* Channel 0 Software Trigger */
#define DMAC_SWTRIGCTRL_SWTRIG0					(1u << 0)
	/* Channel 1 Software Trigger */
#define DMAC_SWTRIGCTRL_SWTRIG1					(1u << 1)
	/* Channel 2 Software Trigger */
#define DMAC_SWTRIGCTRL_SWTRIG2					(1u << 2)
	/* Channel 3 Software Trigger */
#define DMAC_SWTRIGCTRL_SWTRIG3					(1u << 3)
	/* Channel 4 Software Trigger */
#define DMAC_SWTRIGCTRL_SWTRIG4					(1u << 4)
	/* Channel 5 Software Trigger */
#define DMAC_SWTRIGCTRL_SWTRIG5					(1u << 5)

	/* 0x14: Priority Control 0 */
	uint32_t volatile PRICTRL0;
	/* Level 0 Channel Priority Number */
#define DMAC_PRICTRL0_LVLPRI0_Msk				(0x7u << 0)
#define DMAC_PRICTRL0_LVLPRI0_Pos				0
	/* Level 0 Round-Robin Scheduling Enable */
#define DMAC_PRICTRL0_RRLVLEN0					(1u << 7)
	/* Level 1 Channel Priority Number */
#define DMAC_PRICTRL0_LVLPRI1_Msk				(0x7u << 8)
#define DMAC_PRICTRL0_LVLPRI1_Pos				8
	/* Level 1 Round-Robin Scheduling Enable */
#define DMAC_PRICTRL0_RRLVLEN1					(1u << 15)
	/* Level 2 Channel Priority Number */
#define DMAC_PRICTRL0_LVLPRI2_Msk				(0x7u << 16)
#define DMAC_PRICTRL0_LVLPRI2_Pos				16
	/* Level 2 Round-Robin Scheduling Enable */
#define DMAC_PRICTRL0_RRLVLEN2					(1u << 23)
	/* Level 3 Channel Priority Number */
#define DMAC_PRICTRL0_LVLPRI3_Msk				(0x7u << 24)
#define DMAC_PRICTRL0_LVLPRI3_Pos				24
	/* Level 3 Round-Robin Scheduling Enable */
#define DMAC_PRICTRL0_RRLVLEN3					(1u << 31)

	/* 0x18 */
	uint8_t RESERVED1[0x20u-0x18u];

	/* 0x20: Interrupt Pending */
	uint16_t volatile INTPEND;
	/* Channel ID */
#define DMAC_INTPEND_ID_Msk					(0x7u << 0)
#define DMAC_INTPEND_ID_Pos					0
	/* Transfer Error */
#define DMAC_INTPEND_TERR					(1u << 8)
	/* Transfer Complete */
#define DMAC_INTPEND_TCMPL					(1u << 9)
	/* Channel Suspend */
#define DMAC_INTPEND_SUSP					(1u << 10)
	/* Fetch Error */
#define DMAC_INTPEND_FERR					(1u << 13)
	/* Busy */
#define DMAC_INTPEND_BUSY					(1u << 14)
	/* Pending */
#define DMAC_INTPEND_PEND					(1u << 15)

	/* 0x22 */
	uint8_t RESERVED2[0x24u-0x22u];

	/* 0x24: Interrupt Status */
	uint32_t volatile const INTSTATUS;
	/* Channel 0 Pending Interrupt */
#define DMAC_INTSTATUS_CHINT0					(1u << 0)
	/* Channel 1 Pending Interrupt */
#define DMAC_INTSTATUS_CHINT1					(1u << 1)
	/* Channel 2 Pending Interrupt */
#define DMAC_INTSTATUS_CHINT2					(1u << 2)
	/* Channel 3 Pending Interrupt */
#define DMAC_INTSTATUS_CHINT3					(1u << 3)
	/* Channel 4 Pending Interrupt */
#define DMAC_INTSTATUS_CHINT4					(1u << 4)
	/* Channel 5 Pending Interrupt */
#define DMAC_INTSTATUS_CHINT5					(1u << 5)

	/* 0x28: Busy Channels */
	uint32_t volatile const BUSYCH;
	/* Busy Channel 0 */
#define DMAC_BUSYCH_BUSYCH0					(1u << 0)
	/* Busy Channel 1 */
#define DMAC_BUSYCH_BUSYCH1					(1u << 1)
	/* Busy Channel 2 */
#define DMAC_BUSYCH_BUSYCH2					(1u << 2)
	/* Busy Channel 3 */
#define DMAC_BUSYCH_BUSYCH3					(1u << 3)
	/* Busy Channel 4 */
#define DMAC_BUSYCH_BUSYCH4					(1u << 4)
	/* Busy Channel 5 */
#define DMAC_BUSYCH_BUSYCH5					(1u << 5)

	/* 0x2C: Pending Channels */
	uint32_t volatile const PENDCH;
	/* Pending Channel 0 */
#define DMAC_PENDCH_PENDCH0					(1u << 0)
	/* Pending Channel 1 */
#define DMAC_PENDCH_PENDCH1					(1u << 1)
	/* Pending Channel 2 */
#define DMAC_PENDCH_PENDCH2					(1u << 2)
	/* Pending Channel 3 */
#define DMAC_PENDCH_PENDCH3					(1u << 3)
	/* Pending Channel 4 */
#define DMAC_PENDCH_PENDCH4					(1u << 4)
	/* Pending Channel 5 */
#define DMAC_PENDCH_PENDCH5					(1u << 5)

	/* 0x30: Active Channel and Levels */
	uint32_t volatile const ACTIVE;
	/* Level 0 Channel Trigger Request Executing */
#define DMAC_ACTIVE_LVLEX0					(1u << 0)
	/* Level 1 Channel Trigger Request Executing */
#define DMAC_ACTIVE_LVLEX1					(1u << 1)
	/* Level 2 Channel Trigger Request Executing */
#define DMAC_ACTIVE_LVLEX2					(1u << 2)
	/* Level 3 Channel Trigger Request Executing */
#define DMAC_ACTIVE_LVLEX3					(1u << 3)
	/* Active Channel ID */
#define DMAC_ACTIVE_ID_Msk					(0x1Fu << 8)
#define DMAC_ACTIVE_ID_Pos					8
	/* Active Channel Busy */
#define DMAC_ACTIVE_ABUSY					(1u << 15)
	/* Active Channel Block Transfer Count */
#define DMAC_ACTIVE_BTCNT_Msk					(0xFFFFu << 16)
#define DMAC_ACTIVE_BTCNT_Pos					16

	/* 0x34: Descriptor Memory Section Base Address */
	uint32_t volatile BASEADDR;
	/* Descriptor Memory Base Address */
#define DMAC_BASEADDR_BASEADDR_Msk				(0xFFFFFFFFu << 0)
#define DMAC_BASEADDR_BASEADDR_Pos				0

	/* 0x38: Write-Back Memory Section Base Address */
	uint32_t volatile WRBADDR;
	/* Write-Back Memory Base Address */
#define DMAC_WRBADDR_WRBADDR_Msk				(0xFFFFFFFFu << 0)
#define DMAC_WRBADDR_WRBADDR_Pos				0

	/* 0x3C */
	uint8_t RESERVED3[0x3Fu-0x3Cu];

	/* 0x3F: Channel ID */
	uint8_t volatile CHID;
	/* Channel ID */
#define DMAC_CHID_ID_Msk					(0x7u << 0)
#define DMAC_CHID_ID_Pos					0

	/* 0x40: Channel Control A */
	uint8_t volatile CHCTRLA;
	/* Channel Software Reset */
#define DMAC_CHCTRLA_SWRST					(1u << 0)
	/* Channel Enable */
#define DMAC_CHCTRLA_ENABLE					(1u << 1)

	/* 0x41 */
	uint8_t RESERVED4[0x44u-0x41u];

	/* 0x44: Channel Control B */
	uint32_t volatile CHCTRLB;
	/* Event Input Action */
#define DMAC_CHCTRLB_EVACT_Msk					(0x7u << 0)
#define DMAC_CHCTRLB_EVACT_Pos					0
#define DMAC_CHCTRLB_EVACT_NOACT				(0x0u << 0)
#define DMAC_CHCTRLB_EVACT_TRIG					(0x1u << 0)
#define DMAC_CHCTRLB_EVACT_CTRIG				(0x2u << 0)
#define DMAC_CHCTRLB_EVACT_CBLOCK				(0x3u << 0)
#define DMAC_CHCTRLB_EVACT_SUSPEND				(0x4u << 0)
#define DMAC_CHCTRLB_EVACT_RESUME				(0x5u << 0)
#define DMAC_CHCTRLB_EVACT_SSKIP				(0x6u << 0)
	/* Channel Event Input Enable */
#define DMAC_CHCTRLB_EVIE					(1u << 3)
	/* Channel Event Output Enable */
#define DMAC_CHCTRLB_EVOE					(1u << 4)
	/* Channel Arbitration Level */
#define DMAC_CHCTRLB_LVL_Msk					(0x3u << 5)
#define DMAC_CHCTRLB_LVL_Pos					5
#define DMAC_CHCTRLB_LVL_LVL0					(0x0u << 5)
#define DMAC_CHCTRLB_LVL_LVL1					(0x1u << 5)
#define DMAC_CHCTRLB_LVL_LVL2					(0x2u << 5)
#define DMAC_CHCTRLB_LVL_LVL3					(0x3u << 5)
	/* Trigger Source */
#define DMAC_CHCTRLB_TRIGSRC_Msk				(0x1Fu << 8)
#define DMAC_CHCTRLB_TRIGSRC_Pos				8
#define DMAC_CHCTRLB_TRIGSRC_DISABLE				(0x0u << 8)
	/* Trigger Action */
#define DMAC_CHCTRLB_TRIGACT_Msk				(0x3u << 22)
#define DMAC_CHCTRLB_TRIGACT_Pos				22
#define DMAC_CHCTRLB_TRIGACT_BLOCK				(0x0u << 22)
#define DMAC_CHCTRLB_TRIGACT_BEAT				(0x2u << 22)
#define DMAC_CHCTRLB_TRIGACT_TRANSACTION			(0x3u << 22)
	/* Software Command */
#define DMAC_CHCTRLB_CMD_Msk					(0x3u << 24)
#define DMAC_CHCTRLB_CMD_Pos					24
#define DMAC_CHCTRLB_CMD_NOACT					(0x0u << 24)
#define DMAC_CHCTRLB_CMD_SUSPEND				(0x1u << 24)
#define DMAC_CHCTRLB_CMD_RESUME					(0x2u << 24)

	/* 0x48 */
	uint8_t RESERVED5[0x4Cu-0x48u];

	/* 0x4C: Channel Interrupt Enable Clear */
	uint8_t volatile CHINTENCLR;
	/* Channel Transfer Error Interrupt Enable */
#define DMAC_CHINTENCLR_TERR					(1u << 0)
	/* Channel Transfer Complete Interrupt Enable */
#define DMAC_CHINTENCLR_TCMPL					(1u << 1)
	/* Channel Suspend Interrupt Enable */
#define DMAC_CHINTENCLR_SUSP					(1u << 2)

	/* 0x4D: Channel Interrupt Enable Set */
	uint8_t volatile CHINTENSET;
	/* Channel Transfer Error Interrupt Enable */
#define DMAC_CHINTENSET_TERR					(1u << 0)
	/* Channel Transfer Complete Interrupt Enable */
#define DMAC_CHINTENSET_TCMPL					(1u << 1)
	/* Channel Suspend Interrupt Enable */
#define DMAC_CHINTENSET_SUSP					(1u << 2)

	/* 0x4E: Channel Interrupt Flag Status and Clear */
	uint8_t volatile CHINTFLAG;
	/* Channel Transfer Error */
#define DMAC_CHINTFLAG_TERR					(1u << 0)
	/* Channel Transfer Complete */
#define DMAC_CHINTFLAG_TCMPL					(1u << 1)
	/* Channel Suspend */
#define DMAC_CHINTFLAG_SUSP					(1u << 2)

	/* 0x4F: Channel Status */
	uint8_t volatile const CHSTATUS;
	/* Channel Pending */
#define DMAC_CHSTATUS_PEND					(1u << 0)
	/* Channel Busy */
#define DMAC_CHSTATUS_BUSY					(1u << 1)
	/* Channel Fetch Error */
#define DMAC_CHSTATUS_FERR					(1u << 2)

};


#define DSU ((struct dsu *)0x41002000)

struct dsu {

	/* 0x00: Control */
	uint8_t volatile CTRL;
	/* Software Reset */
#define DSU_CTRL_SWRST						(1u << 0)
	/* 32-bit Cyclic Redundancy Code */
#define DSU_CTRL_CRC						(1u << 2)
	/* Memory built-in self-test */
#define DSU_CTRL_MBIST						(1u << 3)
	/* Chip-Erase */
#define DSU_CTRL_CE						(1u << 4)
	/* Auxiliary Row Read */
#define DSU_CTRL_ARR						(1u << 6)
	/* Start Memory Stream Access */
#define DSU_CTRL_SMSA						(1u << 7)

	/* 0x01: Status A */
	uint8_t volatile STATUSA;
	/* Done */
#define DSU_STATUSA_DONE					(1u << 0)
	/* CPU Reset Phase Extension */
#define DSU_STATUSA_CRSTEXT					(1u << 1)
	/* Bus Error */
#define DSU_STATUSA_BERR					(1u << 2)
	/* Failure */
#define DSU_STATUSA_FAIL					(1u << 3)
	/* Protection Error */
#define DSU_STATUSA_PERR					(1u << 4)

	/* 0x02: Status B */
	uint8_t volatile const STATUSB;
	/* Protected */
#define DSU_STATUSB_PROT					(1u << 0)
	/* Debugger Present */
#define DSU_STATUSB_DBGPRES					(1u << 1)
	/* Debug Communication Channel 0 Dirty */
#define DSU_STATUSB_DCCD0					(1u << 2)
	/* Debug Communication Channel 1 Dirty */
#define DSU_STATUSB_DCCD1					(1u << 3)
	/* Hot-Plugging Enable */
#define DSU_STATUSB_HPE						(1u << 4)

	/* 0x03 */
	uint8_t RESERVED0[0x04u-0x03u];

	/* 0x04: Address */
	uint32_t volatile ADDR;
	/* Access Mode */
#define DSU_ADDR_AMOD_Msk					(0x3u << 0)
#define DSU_ADDR_AMOD_Pos					0
	/* Address */
#define DSU_ADDR_ADDR_Msk					(0x3FFFFFFFu << 2)
#define DSU_ADDR_ADDR_Pos					2

	/* 0x08: Length */
	uint32_t volatile LENGTH;
	/* Length */
#define DSU_LENGTH_LENGTH_Msk					(0x3FFFFFFFu << 2)
#define DSU_LENGTH_LENGTH_Pos					2

	/* 0x0C: Data */
	uint32_t volatile DATA;
	/* Data */
#define DSU_DATA_DATA_Msk					(0xFFFFFFFFu << 0)
#define DSU_DATA_DATA_Pos					0

	/* 0x10: Debug Communication Channel n */
	uint64_t volatile DCC[2];
	/* Data */
#define DSU_DCC_DATA_Msk					(0xFFFFFFFFu << 0)
#define DSU_DCC_DATA_Pos					0

	/* 0x18: Device Identification */
	uint32_t volatile const DID;
	/* Device Select */
#define DSU_DID_DEVSEL_Msk					(0xFFu << 0)
#define DSU_DID_DEVSEL_Pos					0
	/* Revision Number */
#define DSU_DID_REVISION_Msk					(0xFu << 8)
#define DSU_DID_REVISION_Pos					8
	/* Die Number */
#define DSU_DID_DIE_Msk						(0xFu << 12)
#define DSU_DID_DIE_Pos						12
	/* Series */
#define DSU_DID_SERIES_Msk					(0x3Fu << 16)
#define DSU_DID_SERIES_Pos					16
#define DSU_DID_SERIES_0					(0x0u << 16)
#define DSU_DID_SERIES_1					(0x1u << 16)
	/* Family */
#define DSU_DID_FAMILY_Msk					(0x1Fu << 23)
#define DSU_DID_FAMILY_Pos					23
#define DSU_DID_FAMILY_0					(0x0u << 23)
#define DSU_DID_FAMILY_1					(0x1u << 23)
	/* Processor */
#define DSU_DID_PROCESSOR_Msk					(0xFu << 28)
#define DSU_DID_PROCESSOR_Pos					28
#define DSU_DID_PROCESSOR_0					(0x0u << 28)
#define DSU_DID_PROCESSOR_1					(0x1u << 28)
#define DSU_DID_PROCESSOR_2					(0x2u << 28)
#define DSU_DID_PROCESSOR_3					(0x3u << 28)

	/* 0x1C */
	uint8_t RESERVED1[0xF0u-0x1Cu];

	/* 0xF0: Device Configuration */
	uint64_t volatile DCFG[2];
	/* Device Configuration */
#define DSU_DCFG_DCFG_Msk					(0xFFFFFFFFu << 0)
#define DSU_DCFG_DCFG_Pos					0

	/* 0xF8 */
	uint8_t RESERVED2[0x1000u-0xF8u];

	/* 0x1000: CoreSight ROM Table Entry 0 */
	uint32_t volatile const ENTRY0;
	/* Entry Present */
#define DSU_ENTRY0_EPRES					(1u << 0)
	/* Format */
#define DSU_ENTRY0_FMT						(1u << 1)
	/* Address Offset */
#define DSU_ENTRY0_ADDOFF_Msk					(0xFFFFFu << 12)
#define DSU_ENTRY0_ADDOFF_Pos					12

	/* 0x1004: CoreSight ROM Table Entry 1 */
	uint32_t volatile const ENTRY1;

	/* 0x1008: CoreSight ROM Table End */
	uint32_t volatile const END;
	/* End Marker */
#define DSU_END_END_Msk						(0xFFFFFFFFu << 0)
#define DSU_END_END_Pos						0

	/* 0x100C */
	uint8_t RESERVED3[0x1FCCu-0x100Cu];

	/* 0x1FCC: CoreSight ROM Table Memory Type */
	uint32_t volatile const MEMTYPE;
	/* System Memory Present */
#define DSU_MEMTYPE_SMEMP					(1u << 0)

	/* 0x1FD0: Peripheral Identification 4 */
	uint32_t volatile const PID4;
	/* JEP-106 Continuation Code */
#define DSU_PID4_JEPCC_Msk					(0xFu << 0)
#define DSU_PID4_JEPCC_Pos					0
	/* 4KB count */
#define DSU_PID4_FKBC_Msk					(0xFu << 4)
#define DSU_PID4_FKBC_Pos					4

	/* 0x1FD4: Peripheral Identification 5 */
	uint32_t volatile const PID5;

	/* 0x1FD8: Peripheral Identification 6 */
	uint32_t volatile const PID6;

	/* 0x1FDC: Peripheral Identification 7 */
	uint32_t volatile const PID7;

	/* 0x1FE0: Peripheral Identification 0 */
	uint32_t volatile const PID0;
	/* Part Number Low */
#define DSU_PID0_PARTNBL_Msk					(0xFFu << 0)
#define DSU_PID0_PARTNBL_Pos					0

	/* 0x1FE4: Peripheral Identification 1 */
	uint32_t volatile const PID1;
	/* Part Number High */
#define DSU_PID1_PARTNBH_Msk					(0xFu << 0)
#define DSU_PID1_PARTNBH_Pos					0
	/* Low part of the JEP-106 Identity Code */
#define DSU_PID1_JEPIDCL_Msk					(0xFu << 4)
#define DSU_PID1_JEPIDCL_Pos					4

	/* 0x1FE8: Peripheral Identification 2 */
	uint32_t volatile const PID2;
	/* JEP-106 Identity Code High */
#define DSU_PID2_JEPIDCH_Msk					(0x7u << 0)
#define DSU_PID2_JEPIDCH_Pos					0
	/* JEP-106 Identity Code is used */
#define DSU_PID2_JEPU						(1u << 3)
	/* Revision Number */
#define DSU_PID2_REVISION_Msk					(0xFu << 4)
#define DSU_PID2_REVISION_Pos					4

	/* 0x1FEC: Peripheral Identification 3 */
	uint32_t volatile const PID3;
	/* ARM CUSMOD */
#define DSU_PID3_CUSMOD_Msk					(0xFu << 0)
#define DSU_PID3_CUSMOD_Pos					0
	/* Revision Number */
#define DSU_PID3_REVAND_Msk					(0xFu << 4)
#define DSU_PID3_REVAND_Pos					4

	/* 0x1FF0: Component Identification 0 */
	uint32_t volatile const CID0;
	/* Preamble Byte 0 */
#define DSU_CID0_PREAMBLEB0_Msk					(0xFFu << 0)
#define DSU_CID0_PREAMBLEB0_Pos					0

	/* 0x1FF4: Component Identification 1 */
	uint32_t volatile const CID1;
	/* Preamble */
#define DSU_CID1_PREAMBLE_Msk					(0xFu << 0)
#define DSU_CID1_PREAMBLE_Pos					0
	/* Component Class */
#define DSU_CID1_CCLASS_Msk					(0xFu << 4)
#define DSU_CID1_CCLASS_Pos					4

	/* 0x1FF8: Component Identification 2 */
	uint32_t volatile const CID2;
	/* Preamble Byte 2 */
#define DSU_CID2_PREAMBLEB2_Msk					(0xFFu << 0)
#define DSU_CID2_PREAMBLEB2_Pos					0

	/* 0x1FFC: Component Identification 3 */
	uint32_t volatile const CID3;
	/* Preamble Byte 3 */
#define DSU_CID3_PREAMBLEB3_Msk					(0xFFu << 0)
#define DSU_CID3_PREAMBLEB3_Pos					0

};


#define EIC ((struct eic *)0x40001800)

struct eic {

	/* 0x00: Control */
	uint8_t volatile CTRL;
	/* Software Reset */
#define EIC_CTRL_SWRST						(1u << 0)
	/* Enable */
#define EIC_CTRL_ENABLE						(1u << 1)

	/* 0x01: Status */
	uint8_t volatile const STATUS;
	/* Synchronization Busy */
#define EIC_STATUS_SYNCBUSY					(1u << 7)

	/* 0x02: Non-Maskable Interrupt Control */
	uint8_t volatile NMICTRL;
	/* Non-Maskable Interrupt Sense */
#define EIC_NMICTRL_NMISENSE_Msk				(0x7u << 0)
#define EIC_NMICTRL_NMISENSE_Pos				0
#define EIC_NMICTRL_NMISENSE_NONE				(0x0u << 0)
#define EIC_NMICTRL_NMISENSE_RISE				(0x1u << 0)
#define EIC_NMICTRL_NMISENSE_FALL				(0x2u << 0)
#define EIC_NMICTRL_NMISENSE_BOTH				(0x3u << 0)
#define EIC_NMICTRL_NMISENSE_HIGH				(0x4u << 0)
#define EIC_NMICTRL_NMISENSE_LOW				(0x5u << 0)
	/* Non-Maskable Interrupt Filter Enable */
#define EIC_NMICTRL_NMIFILTEN					(1u << 3)

	/* 0x03: Non-Maskable Interrupt Flag Status and Clear */
	uint8_t volatile NMIFLAG;
	/* Non-Maskable Interrupt */
#define EIC_NMIFLAG_NMI						(1u << 0)

	/* 0x04: Event Control */
	uint32_t volatile EVCTRL;
	/* External Interrupt 0 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO0					(1u << 0)
	/* External Interrupt 1 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO1					(1u << 1)
	/* External Interrupt 2 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO2					(1u << 2)
	/* External Interrupt 3 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO3					(1u << 3)
	/* External Interrupt 4 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO4					(1u << 4)
	/* External Interrupt 5 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO5					(1u << 5)
	/* External Interrupt 6 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO6					(1u << 6)
	/* External Interrupt 7 Event Output Enable */
#define EIC_EVCTRL_EXTINTEO7					(1u << 7)

	/* 0x08: Interrupt Enable Clear */
	uint32_t volatile INTENCLR;
	/* External Interrupt 0 Enable */
#define EIC_INTENCLR_EXTINT0					(1u << 0)
	/* External Interrupt 1 Enable */
#define EIC_INTENCLR_EXTINT1					(1u << 1)
	/* External Interrupt 2 Enable */
#define EIC_INTENCLR_EXTINT2					(1u << 2)
	/* External Interrupt 3 Enable */
#define EIC_INTENCLR_EXTINT3					(1u << 3)
	/* External Interrupt 4 Enable */
#define EIC_INTENCLR_EXTINT4					(1u << 4)
	/* External Interrupt 5 Enable */
#define EIC_INTENCLR_EXTINT5					(1u << 5)
	/* External Interrupt 6 Enable */
#define EIC_INTENCLR_EXTINT6					(1u << 6)
	/* External Interrupt 7 Enable */
#define EIC_INTENCLR_EXTINT7					(1u << 7)

	/* 0x0C: Interrupt Enable Set */
	uint32_t volatile INTENSET;
	/* External Interrupt 0 Enable */
#define EIC_INTENSET_EXTINT0					(1u << 0)
	/* External Interrupt 1 Enable */
#define EIC_INTENSET_EXTINT1					(1u << 1)
	/* External Interrupt 2 Enable */
#define EIC_INTENSET_EXTINT2					(1u << 2)
	/* External Interrupt 3 Enable */
#define EIC_INTENSET_EXTINT3					(1u << 3)
	/* External Interrupt 4 Enable */
#define EIC_INTENSET_EXTINT4					(1u << 4)
	/* External Interrupt 5 Enable */
#define EIC_INTENSET_EXTINT5					(1u << 5)
	/* External Interrupt 6 Enable */
#define EIC_INTENSET_EXTINT6					(1u << 6)
	/* External Interrupt 7 Enable */
#define EIC_INTENSET_EXTINT7					(1u << 7)

	/* 0x10: Interrupt Flag Status and Clear */
	uint32_t volatile INTFLAG;
	/* External Interrupt 0 */
#define EIC_INTFLAG_EXTINT0					(1u << 0)
	/* External Interrupt 1 */
#define EIC_INTFLAG_EXTINT1					(1u << 1)
	/* External Interrupt 2 */
#define EIC_INTFLAG_EXTINT2					(1u << 2)
	/* External Interrupt 3 */
#define EIC_INTFLAG_EXTINT3					(1u << 3)
	/* External Interrupt 4 */
#define EIC_INTFLAG_EXTINT4					(1u << 4)
	/* External Interrupt 5 */
#define EIC_INTFLAG_EXTINT5					(1u << 5)
	/* External Interrupt 6 */
#define EIC_INTFLAG_EXTINT6					(1u << 6)
	/* External Interrupt 7 */
#define EIC_INTFLAG_EXTINT7					(1u << 7)

	/* 0x14: Wake-Up Enable */
	uint32_t volatile WAKEUP;
	/* External Interrupt 0 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN0					(1u << 0)
	/* External Interrupt 1 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN1					(1u << 1)
	/* External Interrupt 2 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN2					(1u << 2)
	/* External Interrupt 3 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN3					(1u << 3)
	/* External Interrupt 4 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN4					(1u << 4)
	/* External Interrupt 5 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN5					(1u << 5)
	/* External Interrupt 6 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN6					(1u << 6)
	/* External Interrupt 7 Wake-up Enable */
#define EIC_WAKEUP_WAKEUPEN7					(1u << 7)

	/* 0x18: Configuration n */
	uint32_t volatile CONFIG;
	/* Input Sense 0 Configuration */
#define EIC_CONFIG_SENSE0_Msk					(0x7u << 0)
#define EIC_CONFIG_SENSE0_Pos					0
#define EIC_CONFIG_SENSE0_NONE					(0x0u << 0)
#define EIC_CONFIG_SENSE0_RISE					(0x1u << 0)
#define EIC_CONFIG_SENSE0_FALL					(0x2u << 0)
#define EIC_CONFIG_SENSE0_BOTH					(0x3u << 0)
#define EIC_CONFIG_SENSE0_HIGH					(0x4u << 0)
#define EIC_CONFIG_SENSE0_LOW					(0x5u << 0)
	/* Filter 0 Enable */
#define EIC_CONFIG_FILTEN0					(1u << 3)
	/* Input Sense 1 Configuration */
#define EIC_CONFIG_SENSE1_Msk					(0x7u << 4)
#define EIC_CONFIG_SENSE1_Pos					4
#define EIC_CONFIG_SENSE1_NONE					(0x0u << 4)
#define EIC_CONFIG_SENSE1_RISE					(0x1u << 4)
#define EIC_CONFIG_SENSE1_FALL					(0x2u << 4)
#define EIC_CONFIG_SENSE1_BOTH					(0x3u << 4)
#define EIC_CONFIG_SENSE1_HIGH					(0x4u << 4)
#define EIC_CONFIG_SENSE1_LOW					(0x5u << 4)
	/* Filter 1 Enable */
#define EIC_CONFIG_FILTEN1					(1u << 7)
	/* Input Sense 2 Configuration */
#define EIC_CONFIG_SENSE2_Msk					(0x7u << 8)
#define EIC_CONFIG_SENSE2_Pos					8
#define EIC_CONFIG_SENSE2_NONE					(0x0u << 8)
#define EIC_CONFIG_SENSE2_RISE					(0x1u << 8)
#define EIC_CONFIG_SENSE2_FALL					(0x2u << 8)
#define EIC_CONFIG_SENSE2_BOTH					(0x3u << 8)
#define EIC_CONFIG_SENSE2_HIGH					(0x4u << 8)
#define EIC_CONFIG_SENSE2_LOW					(0x5u << 8)
	/* Filter 2 Enable */
#define EIC_CONFIG_FILTEN2					(1u << 11)
	/* Input Sense 3 Configuration */
#define EIC_CONFIG_SENSE3_Msk					(0x7u << 12)
#define EIC_CONFIG_SENSE3_Pos					12
#define EIC_CONFIG_SENSE3_NONE					(0x0u << 12)
#define EIC_CONFIG_SENSE3_RISE					(0x1u << 12)
#define EIC_CONFIG_SENSE3_FALL					(0x2u << 12)
#define EIC_CONFIG_SENSE3_BOTH					(0x3u << 12)
#define EIC_CONFIG_SENSE3_HIGH					(0x4u << 12)
#define EIC_CONFIG_SENSE3_LOW					(0x5u << 12)
	/* Filter 3 Enable */
#define EIC_CONFIG_FILTEN3					(1u << 15)
	/* Input Sense 4 Configuration */
#define EIC_CONFIG_SENSE4_Msk					(0x7u << 16)
#define EIC_CONFIG_SENSE4_Pos					16
#define EIC_CONFIG_SENSE4_NONE					(0x0u << 16)
#define EIC_CONFIG_SENSE4_RISE					(0x1u << 16)
#define EIC_CONFIG_SENSE4_FALL					(0x2u << 16)
#define EIC_CONFIG_SENSE4_BOTH					(0x3u << 16)
#define EIC_CONFIG_SENSE4_HIGH					(0x4u << 16)
#define EIC_CONFIG_SENSE4_LOW					(0x5u << 16)
	/* Filter 4 Enable */
#define EIC_CONFIG_FILTEN4					(1u << 19)
	/* Input Sense 5 Configuration */
#define EIC_CONFIG_SENSE5_Msk					(0x7u << 20)
#define EIC_CONFIG_SENSE5_Pos					20
#define EIC_CONFIG_SENSE5_NONE					(0x0u << 20)
#define EIC_CONFIG_SENSE5_RISE					(0x1u << 20)
#define EIC_CONFIG_SENSE5_FALL					(0x2u << 20)
#define EIC_CONFIG_SENSE5_BOTH					(0x3u << 20)
#define EIC_CONFIG_SENSE5_HIGH					(0x4u << 20)
#define EIC_CONFIG_SENSE5_LOW					(0x5u << 20)
	/* Filter 5 Enable */
#define EIC_CONFIG_FILTEN5					(1u << 23)
	/* Input Sense 6 Configuration */
#define EIC_CONFIG_SENSE6_Msk					(0x7u << 24)
#define EIC_CONFIG_SENSE6_Pos					24
#define EIC_CONFIG_SENSE6_NONE					(0x0u << 24)
#define EIC_CONFIG_SENSE6_RISE					(0x1u << 24)
#define EIC_CONFIG_SENSE6_FALL					(0x2u << 24)
#define EIC_CONFIG_SENSE6_BOTH					(0x3u << 24)
#define EIC_CONFIG_SENSE6_HIGH					(0x4u << 24)
#define EIC_CONFIG_SENSE6_LOW					(0x5u << 24)
	/* Filter 6 Enable */
#define EIC_CONFIG_FILTEN6					(1u << 27)
	/* Input Sense 7 Configuration */
#define EIC_CONFIG_SENSE7_Msk					(0x7u << 28)
#define EIC_CONFIG_SENSE7_Pos					28
#define EIC_CONFIG_SENSE7_NONE					(0x0u << 28)
#define EIC_CONFIG_SENSE7_RISE					(0x1u << 28)
#define EIC_CONFIG_SENSE7_FALL					(0x2u << 28)
#define EIC_CONFIG_SENSE7_BOTH					(0x3u << 28)
#define EIC_CONFIG_SENSE7_HIGH					(0x4u << 28)
#define EIC_CONFIG_SENSE7_LOW					(0x5u << 28)
	/* Filter 7 Enable */
#define EIC_CONFIG_FILTEN7					(1u << 31)

};


#define EVSYS ((struct evsys *)0x42000400)

struct evsys {

	/* 0x00: Control */
	uint8_t volatile CTRL;
	/* Software Reset */
#define EVSYS_CTRL_SWRST					(1u << 0)
	/* Generic Clock Requests */
#define EVSYS_CTRL_GCLKREQ					(1u << 4)

	/* 0x01 */
	uint8_t RESERVED0[0x04u-0x01u];

	/* 0x04: Channel */
	uint32_t volatile CHANNEL;
	/* Channel Selection */
#define EVSYS_CHANNEL_CHANNEL_Msk				(0x7u << 0)
#define EVSYS_CHANNEL_CHANNEL_Pos				0
	/* Software Event */
#define EVSYS_CHANNEL_SWEVT					(1u << 8)
	/* Event Generator Selection */
#define EVSYS_CHANNEL_EVGEN_Msk					(0x3Fu << 16)
#define EVSYS_CHANNEL_EVGEN_Pos					16
	/* Path Selection */
#define EVSYS_CHANNEL_PATH_Msk					(0x3u << 24)
#define EVSYS_CHANNEL_PATH_Pos					24
#define EVSYS_CHANNEL_PATH_SYNCHRONOUS				(0x0u << 24)
#define EVSYS_CHANNEL_PATH_RESYNCHRONIZED			(0x1u << 24)
#define EVSYS_CHANNEL_PATH_ASYNCHRONOUS				(0x2u << 24)
	/* Edge Detection Selection */
#define EVSYS_CHANNEL_EDGSEL_Msk				(0x3u << 26)
#define EVSYS_CHANNEL_EDGSEL_Pos				26
#define EVSYS_CHANNEL_EDGSEL_NO_EVT_OUTPUT			(0x0u << 26)
#define EVSYS_CHANNEL_EDGSEL_RISING_EDGE			(0x1u << 26)
#define EVSYS_CHANNEL_EDGSEL_FALLING_EDGE			(0x2u << 26)
#define EVSYS_CHANNEL_EDGSEL_BOTH_EDGES				(0x3u << 26)

	/* 0x08: User Multiplexer */
	uint16_t volatile USER;
	/* User Multiplexer Selection */
#define EVSYS_USER_USER_Msk					(0x1Fu << 0)
#define EVSYS_USER_USER_Pos					0
	/* Channel Event Selection */
#define EVSYS_USER_CHANNEL_Msk					(0xFu << 8)
#define EVSYS_USER_CHANNEL_Pos					8
#define EVSYS_USER_CHANNEL_0					(0x0u << 8)

	/* 0x0A */
	uint8_t RESERVED1[0x0Cu-0x0Au];

	/* 0x0C: Channel Status */
	uint32_t volatile const CHSTATUS;
	/* Channel 0 User Ready */
#define EVSYS_CHSTATUS_USRRDY0					(1u << 0)
	/* Channel 1 User Ready */
#define EVSYS_CHSTATUS_USRRDY1					(1u << 1)
	/* Channel 2 User Ready */
#define EVSYS_CHSTATUS_USRRDY2					(1u << 2)
	/* Channel 3 User Ready */
#define EVSYS_CHSTATUS_USRRDY3					(1u << 3)
	/* Channel 4 User Ready */
#define EVSYS_CHSTATUS_USRRDY4					(1u << 4)
	/* Channel 5 User Ready */
#define EVSYS_CHSTATUS_USRRDY5					(1u << 5)
	/* Channel 0 Busy */
#define EVSYS_CHSTATUS_CHBUSY0					(1u << 8)
	/* Channel 1 Busy */
#define EVSYS_CHSTATUS_CHBUSY1					(1u << 9)
	/* Channel 2 Busy */
#define EVSYS_CHSTATUS_CHBUSY2					(1u << 10)
	/* Channel 3 Busy */
#define EVSYS_CHSTATUS_CHBUSY3					(1u << 11)
	/* Channel 4 Busy */
#define EVSYS_CHSTATUS_CHBUSY4					(1u << 12)
	/* Channel 5 Busy */
#define EVSYS_CHSTATUS_CHBUSY5					(1u << 13)

	/* 0x10: Interrupt Enable Clear */
	uint32_t volatile INTENCLR;
	/* Channel 0 Overrun Interrupt Enable */
#define EVSYS_INTENCLR_OVR0					(1u << 0)
	/* Channel 1 Overrun Interrupt Enable */
#define EVSYS_INTENCLR_OVR1					(1u << 1)
	/* Channel 2 Overrun Interrupt Enable */
#define EVSYS_INTENCLR_OVR2					(1u << 2)
	/* Channel 3 Overrun Interrupt Enable */
#define EVSYS_INTENCLR_OVR3					(1u << 3)
	/* Channel 4 Overrun Interrupt Enable */
#define EVSYS_INTENCLR_OVR4					(1u << 4)
	/* Channel 5 Overrun Interrupt Enable */
#define EVSYS_INTENCLR_OVR5					(1u << 5)
	/* Channel 0 Event Detection Interrupt Enable */
#define EVSYS_INTENCLR_EVD0					(1u << 8)
	/* Channel 1 Event Detection Interrupt Enable */
#define EVSYS_INTENCLR_EVD1					(1u << 9)
	/* Channel 2 Event Detection Interrupt Enable */
#define EVSYS_INTENCLR_EVD2					(1u << 10)
	/* Channel 3 Event Detection Interrupt Enable */
#define EVSYS_INTENCLR_EVD3					(1u << 11)
	/* Channel 4 Event Detection Interrupt Enable */
#define EVSYS_INTENCLR_EVD4					(1u << 12)
	/* Channel 5 Event Detection Interrupt Enable */
#define EVSYS_INTENCLR_EVD5					(1u << 13)

	/* 0x14: Interrupt Enable Set */
	uint32_t volatile INTENSET;
	/* Channel 0 Overrun Interrupt Enable */
#define EVSYS_INTENSET_OVR0					(1u << 0)
	/* Channel 1 Overrun Interrupt Enable */
#define EVSYS_INTENSET_OVR1					(1u << 1)
	/* Channel 2 Overrun Interrupt Enable */
#define EVSYS_INTENSET_OVR2					(1u << 2)
	/* Channel 3 Overrun Interrupt Enable */
#define EVSYS_INTENSET_OVR3					(1u << 3)
	/* Channel 4 Overrun Interrupt Enable */
#define EVSYS_INTENSET_OVR4					(1u << 4)
	/* Channel 5 Overrun Interrupt Enable */
#define EVSYS_INTENSET_OVR5					(1u << 5)
	/* Channel 0 Event Detection Interrupt Enable */
#define EVSYS_INTENSET_EVD0					(1u << 8)
	/* Channel 1 Event Detection Interrupt Enable */
#define EVSYS_INTENSET_EVD1					(1u << 9)
	/* Channel 2 Event Detection Interrupt Enable */
#define EVSYS_INTENSET_EVD2					(1u << 10)
	/* Channel 3 Event Detection Interrupt Enable */
#define EVSYS_INTENSET_EVD3					(1u << 11)
	/* Channel 4 Event Detection Interrupt Enable */
#define EVSYS_INTENSET_EVD4					(1u << 12)
	/* Channel 5 Event Detection Interrupt Enable */
#define EVSYS_INTENSET_EVD5					(1u << 13)

	/* 0x18: Interrupt Flag Status and Clear */
	uint32_t volatile INTFLAG;
	/* Channel 0 Overrun */
#define EVSYS_INTFLAG_OVR0					(1u << 0)
	/* Channel 1 Overrun */
#define EVSYS_INTFLAG_OVR1					(1u << 1)
	/* Channel 2 Overrun */
#define EVSYS_INTFLAG_OVR2					(1u << 2)
	/* Channel 3 Overrun */
#define EVSYS_INTFLAG_OVR3					(1u << 3)
	/* Channel 4 Overrun */
#define EVSYS_INTFLAG_OVR4					(1u << 4)
	/* Channel 5 Overrun */
#define EVSYS_INTFLAG_OVR5					(1u << 5)
	/* Channel 0 Event Detection */
#define EVSYS_INTFLAG_EVD0					(1u << 8)
	/* Channel 1 Event Detection */
#define EVSYS_INTFLAG_EVD1					(1u << 9)
	/* Channel 2 Event Detection */
#define EVSYS_INTFLAG_EVD2					(1u << 10)
	/* Channel 3 Event Detection */
#define EVSYS_INTFLAG_EVD3					(1u << 11)
	/* Channel 4 Event Detection */
#define EVSYS_INTFLAG_EVD4					(1u << 12)
	/* Channel 5 Event Detection */
#define EVSYS_INTFLAG_EVD5					(1u << 13)

};


#define GCLK ((struct gclk *)0x40000C00)

struct gclk {

	/* 0x00: Control */
	uint8_t volatile CTRL;
	/* Software Reset */
#define GCLK_CTRL_SWRST						(1u << 0)

	/* 0x01: Status */
	uint8_t volatile const STATUS;
	/* Synchronization Busy Status */
#define GCLK_STATUS_SYNCBUSY					(1u << 7)

	/* 0x02: Generic Clock Control */
	uint16_t volatile CLKCTRL;
	/* Generic Clock Selection ID */
#define GCLK_CLKCTRL_ID_Msk					(0x3Fu << 0)
#define GCLK_CLKCTRL_ID_Pos					0
#define GCLK_CLKCTRL_ID_DFLL48					(0x0u << 0)
#define GCLK_CLKCTRL_ID_FDPLL					(0x1u << 0)
#define GCLK_CLKCTRL_ID_FDPLL32K				(0x2u << 0)
#define GCLK_CLKCTRL_ID_WDT					(0x3u << 0)
#define GCLK_CLKCTRL_ID_RTC					(0x4u << 0)
#define GCLK_CLKCTRL_ID_EIC					(0x5u << 0)
#define GCLK_CLKCTRL_ID_EVSYS_0					(0x7u << 0)
#define GCLK_CLKCTRL_ID_EVSYS_1					(0x8u << 0)
#define GCLK_CLKCTRL_ID_EVSYS_2					(0x9u << 0)
#define GCLK_CLKCTRL_ID_EVSYS_3					(0xAu << 0)
#define GCLK_CLKCTRL_ID_EVSYS_4					(0xBu << 0)
#define GCLK_CLKCTRL_ID_EVSYS_5					(0xCu << 0)
#define GCLK_CLKCTRL_ID_SERCOMX_SLOW				(0xDu << 0)
#define GCLK_CLKCTRL_ID_SERCOM0_CORE				(0xEu << 0)
#define GCLK_CLKCTRL_ID_SERCOM1_CORE				(0xFu << 0)
#define GCLK_CLKCTRL_ID_SERCOM2_CORE				(0x10u << 0)
#define GCLK_CLKCTRL_ID_TC1_TC2					(0x12u << 0)
#define GCLK_CLKCTRL_ID_ADC					(0x13u << 0)
#define GCLK_CLKCTRL_ID_AC_DIG					(0x14u << 0)
#define GCLK_CLKCTRL_ID_AC_ANA					(0x15u << 0)
	/* Generic Clock Generator */
#define GCLK_CLKCTRL_GEN_Msk					(0xFu << 8)
#define GCLK_CLKCTRL_GEN_Pos					8
#define GCLK_CLKCTRL_GEN_GCLK0					(0x0u << 8)
#define GCLK_CLKCTRL_GEN_GCLK1					(0x1u << 8)
#define GCLK_CLKCTRL_GEN_GCLK2					(0x2u << 8)
#define GCLK_CLKCTRL_GEN_GCLK3					(0x3u << 8)
#define GCLK_CLKCTRL_GEN_GCLK4					(0x4u << 8)
#define GCLK_CLKCTRL_GEN_GCLK5					(0x5u << 8)
	/* Clock Enable */
#define GCLK_CLKCTRL_CLKEN					(1u << 14)
	/* Write Lock */
#define GCLK_CLKCTRL_WRTLOCK					(1u << 15)

	/* 0x04: Generic Clock Generator Control */
	uint32_t volatile GENCTRL;
	/* Generic Clock Generator Selection */
#define GCLK_GENCTRL_ID_Msk					(0xFu << 0)
#define GCLK_GENCTRL_ID_Pos					0
#define GCLK_GENCTRL_ID_GCLKGEN0				(0x0u << 0)
#define GCLK_GENCTRL_ID_GCLKGEN1				(0x1u << 0)
#define GCLK_GENCTRL_ID_GCLKGEN2				(0x2u << 0)
#define GCLK_GENCTRL_ID_GCLKGEN3				(0x3u << 0)
#define GCLK_GENCTRL_ID_GCLKGEN4				(0x4u << 0)
#define GCLK_GENCTRL_ID_GCLKGEN5				(0x5u << 0)
	/* Source Select */
#define GCLK_GENCTRL_SRC_Msk					(0x1Fu << 8)
#define GCLK_GENCTRL_SRC_Pos					8
#define GCLK_GENCTRL_SRC_XOSC					(0x0u << 8)
#define GCLK_GENCTRL_SRC_GCLKIN					(0x1u << 8)
#define GCLK_GENCTRL_SRC_GCLKGEN1				(0x2u << 8)
#define GCLK_GENCTRL_SRC_OSCULP32K				(0x3u << 8)
#define GCLK_GENCTRL_SRC_OSC32K					(0x4u << 8)
#define GCLK_GENCTRL_SRC_XOSC32K				(0x5u << 8)
#define GCLK_GENCTRL_SRC_OSC8M					(0x6u << 8)
#define GCLK_GENCTRL_SRC_DFLL48M				(0x7u << 8)
#define GCLK_GENCTRL_SRC_DPLL96M				(0x8u << 8)
	/* Generic Clock Generator Enable */
#define GCLK_GENCTRL_GENEN					(1u << 16)
	/* Improve Duty Cycle */
#define GCLK_GENCTRL_IDC					(1u << 17)
	/* Output Off Value */
#define GCLK_GENCTRL_OOV					(1u << 18)
	/* Output Enable */
#define GCLK_GENCTRL_OE						(1u << 19)
	/* Divide Selection */
#define GCLK_GENCTRL_DIVSEL					(1u << 20)
	/* Run in Standby */
#define GCLK_GENCTRL_RUNSTDBY					(1u << 21)

	/* 0x08: Generic Clock Generator Division */
	uint32_t volatile GENDIV;
	/* Generic Clock Generator Selection */
#define GCLK_GENDIV_ID_Msk					(0xFu << 0)
#define GCLK_GENDIV_ID_Pos					0
	/* Division Factor */
#define GCLK_GENDIV_DIV_Msk					(0xFFFFu << 8)
#define GCLK_GENDIV_DIV_Pos					8

};


#define HMATRIX ((struct hmatrix *)0x41007000)

struct hmatrix {

	/* 0x0C */
	uint8_t RESERVED0[0x80u-0x0Cu];

	/* 0x80: Priority A for Slave */
	uint64_t volatile PRAS[16];
	/* Master 0 Priority */
#define HMATRIX_PRAS_M0PR_Msk					(0xFu << 0)
#define HMATRIX_PRAS_M0PR_Pos					0
	/* Master 1 Priority */
#define HMATRIX_PRAS_M1PR_Msk					(0xFu << 4)
#define HMATRIX_PRAS_M1PR_Pos					4
	/* Master 2 Priority */
#define HMATRIX_PRAS_M2PR_Msk					(0xFu << 8)
#define HMATRIX_PRAS_M2PR_Pos					8
	/* Master 3 Priority */
#define HMATRIX_PRAS_M3PR_Msk					(0xFu << 12)
#define HMATRIX_PRAS_M3PR_Pos					12
	/* Master 4 Priority */
#define HMATRIX_PRAS_M4PR_Msk					(0xFu << 16)
#define HMATRIX_PRAS_M4PR_Pos					16
	/* Master 5 Priority */
#define HMATRIX_PRAS_M5PR_Msk					(0xFu << 20)
#define HMATRIX_PRAS_M5PR_Pos					20
	/* Master 6 Priority */
#define HMATRIX_PRAS_M6PR_Msk					(0xFu << 24)
#define HMATRIX_PRAS_M6PR_Pos					24
	/* Master 7 Priority */
#define HMATRIX_PRAS_M7PR_Msk					(0xFu << 28)
#define HMATRIX_PRAS_M7PR_Pos					28
	/* Master 8 Priority */
#define HMATRIX_PRBS_M8PR_Msk					(0xFu << 32)
#define HMATRIX_PRBS_M8PR_Pos					0
	/* Master 9 Priority */
#define HMATRIX_PRBS_M9PR_Msk					(0xFu << 36)
#define HMATRIX_PRBS_M9PR_Pos					4
	/* Master 10 Priority */
#define HMATRIX_PRBS_M10PR_Msk					(0xFu << 40)
#define HMATRIX_PRBS_M10PR_Pos					8
	/* Master 11 Priority */
#define HMATRIX_PRBS_M11PR_Msk					(0xFu << 44)
#define HMATRIX_PRBS_M11PR_Pos					12
	/* Master 12 Priority */
#define HMATRIX_PRBS_M12PR_Msk					(0xFu << 48)
#define HMATRIX_PRBS_M12PR_Pos					16
	/* Master 13 Priority */
#define HMATRIX_PRBS_M13PR_Msk					(0xFu << 52)
#define HMATRIX_PRBS_M13PR_Pos					20
	/* Master 14 Priority */
#define HMATRIX_PRBS_M14PR_Msk					(0xFu << 56)
#define HMATRIX_PRBS_M14PR_Pos					24
	/* Master 15 Priority */
#define HMATRIX_PRBS_M15PR_Msk					(0xFu << 60)
#define HMATRIX_PRBS_M15PR_Pos					28

	/* 0x100 */
	uint8_t RESERVED1[0x110u-0x100];

	/* 0x110: Special Function */
	uint32_t volatile SFR[16];
	/* Special Function Register */
#define HMATRIX_SFR_SFR_Msk					(0xFFFFFFFFu << 0)
#define HMATRIX_SFR_SFR_Pos					0

};


#define MTB ((struct mtb *)0x41006000)

struct mtb {

	/* 0x00: MTB Position */
	uint32_t volatile POSITION;
	/* Pointer Value Wraps */
#define MTB_POSITION_WRAP					(1u << 2)
	/* Trace Packet Location Pointer */
#define MTB_POSITION_POINTER_Msk				(0x1FFFFFFFu << 3)
#define MTB_POSITION_POINTER_Pos				3

	/* 0x04: MTB Master */
	uint32_t volatile MASTER;
	/* Maximum Value of the Trace Buffer in SRAM */
#define MTB_MASTER_MASK_Msk					(0x1Fu << 0)
#define MTB_MASTER_MASK_Pos					0
	/* Trace Start Input Enable */
#define MTB_MASTER_TSTARTEN					(1u << 5)
	/* Trace Stop Input Enable */
#define MTB_MASTER_TSTOPEN					(1u << 6)
	/* Special Function Register Write Privilege */
#define MTB_MASTER_SFRWPRIV					(1u << 7)
	/* SRAM Privilege */
#define MTB_MASTER_RAMPRIV					(1u << 8)
	/* Halt Request */
#define MTB_MASTER_HALTREQ					(1u << 9)
	/* Main Trace Enable */
#define MTB_MASTER_EN						(1u << 31)

	/* 0x08: MTB Flow */
	uint32_t volatile FLOW;
	/* Auto Stop Tracing */
#define MTB_FLOW_AUTOSTOP					(1u << 0)
	/* Auto Halt Request */
#define MTB_FLOW_AUTOHALT					(1u << 1)
	/* Watermark value */
#define MTB_FLOW_WATERMARK_Msk					(0x1FFFFFFFu << 3)
#define MTB_FLOW_WATERMARK_Pos					3

	/* 0x0C: MTB Base */
	uint32_t volatile const BASE;

	/* 0x10 */
	uint8_t RESERVED0[0xF00u-0x10u];

	/* 0xF00: MTB Integration Mode Control */
	uint32_t volatile ITCTRL;

	/* 0xF04 */
	uint8_t RESERVED1[0xFA0u-0xF04u];

	/* 0xFA0: MTB Claim Set */
	uint32_t volatile CLAIMSET;

	/* 0xFA4: MTB Claim Clear */
	uint32_t volatile CLAIMCLR;

	/* 0xFA8 */
	uint8_t RESERVED2[0xFB0u-0xFA8u];

	/* 0xFB0: MTB Lock Access */
	uint32_t volatile LOCKACCESS;

	/* 0xFB4: MTB Lock Status */
	uint32_t volatile const LOCKSTATUS;

	/* 0xFB8: MTB Authentication Status */
	uint32_t volatile const AUTHSTATUS;

	/* 0xFBC: MTB Device Architecture */
	uint32_t volatile const DEVARCH;

	/* 0xFC0 */
	uint8_t RESERVED3[0xFC8u-0xFC0u];

	/* 0xFC8: MTB Device Configuration */
	uint32_t volatile const DEVID;

	/* 0xFCC: MTB Device Type */
	uint32_t volatile const DEVTYPE;

	/* 0xFD0: CoreSight */
	uint32_t volatile const PID4;

	/* 0xFD4: CoreSight */
	uint32_t volatile const PID5;

	/* 0xFD8: CoreSight */
	uint32_t volatile const PID6;

	/* 0xFDC: CoreSight */
	uint32_t volatile const PID7;

	/* 0xFE0: CoreSight */
	uint32_t volatile const PID0;

	/* 0xFE4: CoreSight */
	uint32_t volatile const PID1;

	/* 0xFE8: CoreSight */
	uint32_t volatile const PID2;

	/* 0xFEC: CoreSight */
	uint32_t volatile const PID3;

	/* 0xFF0: CoreSight */
	uint32_t volatile const CID0;

	/* 0xFF4: CoreSight */
	uint32_t volatile const CID1;

	/* 0xFF8: CoreSight */
	uint32_t volatile const CID2;

	/* 0xFFC: CoreSight */
	uint32_t volatile const CID3;

};


#define NVMCTRL ((struct nvmctrl *)0x41004000)

struct nvmctrl {

	/* 0x00: Control A */
	uint16_t volatile CTRLA;
	/* Command */
#define NVMCTRL_CTRLA_CMD_Msk					(0x7Fu << 0)
#define NVMCTRL_CTRLA_CMD_Pos					0
#define NVMCTRL_CTRLA_CMD_ER					(0x2u << 0)
#define NVMCTRL_CTRLA_CMD_WP					(0x4u << 0)
#define NVMCTRL_CTRLA_CMD_EAR					(0x5u << 0)
#define NVMCTRL_CTRLA_CMD_WAP					(0x6u << 0)
#define NVMCTRL_CTRLA_CMD_SF					(0xAu << 0)
#define NVMCTRL_CTRLA_CMD_WL					(0xFu << 0)
#define NVMCTRL_CTRLA_CMD_LR					(0x40u << 0)
#define NVMCTRL_CTRLA_CMD_UR					(0x41u << 0)
#define NVMCTRL_CTRLA_CMD_SPRM					(0x42u << 0)
#define NVMCTRL_CTRLA_CMD_CPRM					(0x43u << 0)
#define NVMCTRL_CTRLA_CMD_PBC					(0x44u << 0)
#define NVMCTRL_CTRLA_CMD_SSB					(0x45u << 0)
#define NVMCTRL_CTRLA_CMD_INVALL				(0x46u << 0)
	/* Command Execution */
#define NVMCTRL_CTRLA_CMDEX_Msk					(0xFFu << 8)
#define NVMCTRL_CTRLA_CMDEX_Pos					8
#define NVMCTRL_CTRLA_CMDEX_KEY					(0xA5u << 8)

	/* 0x02 */
	uint8_t RESERVED0[0x04u-0x02u];

	/* 0x04: Control B */
	uint32_t volatile CTRLB;
	/* NVM Read Wait States */
#define NVMCTRL_CTRLB_RWS_Msk					(0xFu << 1)
#define NVMCTRL_CTRLB_RWS_Pos					1
#define NVMCTRL_CTRLB_RWS_SINGLE				(0x0u << 1)
#define NVMCTRL_CTRLB_RWS_HALF					(0x1u << 1)
#define NVMCTRL_CTRLB_RWS_DUAL					(0x2u << 1)
	/* Manual Write */
#define NVMCTRL_CTRLB_MANW					(1u << 7)
	/* Power Reduction Mode during Sleep */
#define NVMCTRL_CTRLB_SLEEPPRM_Msk				(0x3u << 8)
#define NVMCTRL_CTRLB_SLEEPPRM_Pos				8
#define NVMCTRL_CTRLB_SLEEPPRM_WAKEONACCESS			(0x0u << 8)
#define NVMCTRL_CTRLB_SLEEPPRM_WAKEUPINSTANT			(0x1u << 8)
#define NVMCTRL_CTRLB_SLEEPPRM_DISABLED				(0x3u << 8)
	/* NVMCTRL Read Mode */
#define NVMCTRL_CTRLB_READMODE_Msk				(0x3u << 16)
#define NVMCTRL_CTRLB_READMODE_Pos				16
#define NVMCTRL_CTRLB_READMODE_NO_MISS_PENALTY			(0x0u << 16)
#define NVMCTRL_CTRLB_READMODE_LOW_POWER			(0x1u << 16)
#define NVMCTRL_CTRLB_READMODE_DETERMINISTIC			(0x2u << 16)
	/* Cache Disable */
#define NVMCTRL_CTRLB_CACHEDIS					(1u << 18)

	/* 0x08: NVM Parameter */
	uint32_t volatile PARAM;
	/* NVM Pages */
#define NVMCTRL_PARAM_NVMP_Msk					(0xFFFFu << 0)
#define NVMCTRL_PARAM_NVMP_Pos					0
	/* Page Size */
#define NVMCTRL_PARAM_PSZ_Msk					(0x7u << 16)
#define NVMCTRL_PARAM_PSZ_Pos					16
#define NVMCTRL_PARAM_PSZ_8					(0x0u << 16)
#define NVMCTRL_PARAM_PSZ_16					(0x1u << 16)
#define NVMCTRL_PARAM_PSZ_32					(0x2u << 16)
#define NVMCTRL_PARAM_PSZ_64					(0x3u << 16)
#define NVMCTRL_PARAM_PSZ_128					(0x4u << 16)
#define NVMCTRL_PARAM_PSZ_256					(0x5u << 16)
#define NVMCTRL_PARAM_PSZ_512					(0x6u << 16)
#define NVMCTRL_PARAM_PSZ_1024					(0x7u << 16)

	/* 0x0C: Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* NVM Ready Interrupt Enable */
#define NVMCTRL_INTENCLR_READY					(1u << 0)
	/* Error Interrupt Enable */
#define NVMCTRL_INTENCLR_ERROR					(1u << 1)

	/* 0x0D */
	uint8_t RESERVED1[0x10u-0x0Du];

	/* 0x10: Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* NVM Ready Interrupt Enable */
#define NVMCTRL_INTENSET_READY					(1u << 0)
	/* Error Interrupt Enable */
#define NVMCTRL_INTENSET_ERROR					(1u << 1)

	/* 0x11 */
	uint8_t RESERVED2[0x14u-0x11u];

	/* 0x14: Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* NVM Ready */
#define NVMCTRL_INTFLAG_READY					(1u << 0)
	/* Error */
#define NVMCTRL_INTFLAG_ERROR					(1u << 1)

	/* 0x15 */
	uint8_t RESERVED3[0x18u-0x15u];

	/* 0x18: Status */
	uint16_t volatile STATUS;
	/* Power Reduction Mode */
#define NVMCTRL_STATUS_PRM					(1u << 0)
	/* NVM Page Buffer Active Loading */
#define NVMCTRL_STATUS_LOAD					(1u << 1)
	/* Programming Error Status */
#define NVMCTRL_STATUS_PROGE					(1u << 2)
	/* Lock Error Status */
#define NVMCTRL_STATUS_LOCKE					(1u << 3)
	/* NVM Error */
#define NVMCTRL_STATUS_NVME					(1u << 4)
	/* Security Bit Status */
#define NVMCTRL_STATUS_SB					(1u << 8)

	/* 0x1A */
	uint8_t RESERVED4[0x1Cu-0x1Au];

	/* 0x1C: Address */
	uint32_t volatile ADDR;
	/* NVM Address */
#define NVMCTRL_ADDR_ADDR_Msk					(0x3FFFFFu << 0)
#define NVMCTRL_ADDR_ADDR_Pos					0

	/* 0x20: Lock Section */
	uint16_t volatile LOCK;
	/* Region Lock Bits */
#define NVMCTRL_LOCK_LOCK_Msk					(0xFFFFu << 0)
#define NVMCTRL_LOCK_LOCK_Pos					0

};


#define PAC0 ((struct pac0 *)0x40000000)
#define PAC1 ((struct pac1 *)0x41000000)
#define PAC2 ((struct pac2 *)0x42000000)

struct pac0 {

	/* 0x00: Write Protection Clear */
	uint32_t volatile WPCLR;
	/* Write Protection Clear */
#define PAC0_WPCLR_WP_Msk					(0x7FFFFFFFu << 1)
#define PAC0_WPCLR_WP_Pos					1

	/* 0x04: Write Protection Set */
	uint32_t volatile WPSET;
	/* Write Protection Set */
#define PAC0_WPSET_WP_Msk					(0x7FFFFFFFu << 1)
#define PAC0_WPSET_WP_Pos					1

};


#define PM ((struct pm *)0x40000400)

struct pm {

	/* 0x00: Control */
	uint8_t volatile CTRL;
	/* Clock Failure Detector Enable */
#define PM_CTRL_CFDEN						(1u << 2)
	/* Backup Clock Select */
#define PM_CTRL_BKUPCLK						(1u << 4)

	/* 0x01: Sleep Mode */
	uint8_t volatile SLEEP;
	/* Idle Mode Configuration */
#define PM_SLEEP_IDLE_Msk					(0x3u << 0)
#define PM_SLEEP_IDLE_Pos					0
#define PM_SLEEP_IDLE_CPU					(0x0u << 0)
#define PM_SLEEP_IDLE_AHB					(0x1u << 0)
#define PM_SLEEP_IDLE_APB					(0x2u << 0)

	/* 0x02: External Reset Controller */
	uint8_t volatile EXTCTRL;
	/* External Reset Disable */
#define PM_EXTCTRL_SETDIS					(1u << 0)

	/* 0x03 */
	uint8_t RESERVED0[0x08u-0x03u];

	/* 0x08: CPU Clock Select */
	uint8_t volatile CPUSEL;
	/* CPU Prescaler Selection */
#define PM_CPUSEL_CPUDIV_Msk					(0x7u << 0)
#define PM_CPUSEL_CPUDIV_Pos					0
#define PM_CPUSEL_CPUDIV_DIV1					(0x0u << 0)
#define PM_CPUSEL_CPUDIV_DIV2					(0x1u << 0)
#define PM_CPUSEL_CPUDIV_DIV4					(0x2u << 0)
#define PM_CPUSEL_CPUDIV_DIV8					(0x3u << 0)
#define PM_CPUSEL_CPUDIV_DIV16					(0x4u << 0)
#define PM_CPUSEL_CPUDIV_DIV32					(0x5u << 0)
#define PM_CPUSEL_CPUDIV_DIV64					(0x6u << 0)
#define PM_CPUSEL_CPUDIV_DIV128					(0x7u << 0)

	/* 0x09: APBA Clock Select */
	uint8_t volatile APBASEL;
	/* APBA Prescaler Selection */
#define PM_APBASEL_APBADIV_Msk					(0x7u << 0)
#define PM_APBASEL_APBADIV_Pos					0
#define PM_APBASEL_APBADIV_DIV1					(0x0u << 0)
#define PM_APBASEL_APBADIV_DIV2					(0x1u << 0)
#define PM_APBASEL_APBADIV_DIV4					(0x2u << 0)
#define PM_APBASEL_APBADIV_DIV8					(0x3u << 0)
#define PM_APBASEL_APBADIV_DIV16				(0x4u << 0)
#define PM_APBASEL_APBADIV_DIV32				(0x5u << 0)
#define PM_APBASEL_APBADIV_DIV64				(0x6u << 0)
#define PM_APBASEL_APBADIV_DIV128				(0x7u << 0)

	/* 0x0A: APBB Clock Select */
	uint8_t volatile APBBSEL;
	/* APBB Prescaler Selection */
#define PM_APBBSEL_APBBDIV_Msk					(0x7u << 0)
#define PM_APBBSEL_APBBDIV_Pos					0
#define PM_APBBSEL_APBBDIV_DIV1					(0x0u << 0)
#define PM_APBBSEL_APBBDIV_DIV2					(0x1u << 0)
#define PM_APBBSEL_APBBDIV_DIV4					(0x2u << 0)
#define PM_APBBSEL_APBBDIV_DIV8					(0x3u << 0)
#define PM_APBBSEL_APBBDIV_DIV16				(0x4u << 0)
#define PM_APBBSEL_APBBDIV_DIV32				(0x5u << 0)
#define PM_APBBSEL_APBBDIV_DIV64				(0x6u << 0)
#define PM_APBBSEL_APBBDIV_DIV128				(0x7u << 0)

	/* 0x0B: APBC Clock Select */
	uint8_t volatile APBCSEL;
	/* APBC Prescaler Selection */
#define PM_APBCSEL_APBCDIV_Msk					(0x7u << 0)
#define PM_APBCSEL_APBCDIV_Pos					0
#define PM_APBCSEL_APBCDIV_DIV1					(0x0u << 0)
#define PM_APBCSEL_APBCDIV_DIV2					(0x1u << 0)
#define PM_APBCSEL_APBCDIV_DIV4					(0x2u << 0)
#define PM_APBCSEL_APBCDIV_DIV8					(0x3u << 0)
#define PM_APBCSEL_APBCDIV_DIV16				(0x4u << 0)
#define PM_APBCSEL_APBCDIV_DIV32				(0x5u << 0)
#define PM_APBCSEL_APBCDIV_DIV64				(0x6u << 0)
#define PM_APBCSEL_APBCDIV_DIV128				(0x7u << 0)

	/* 0x0C */
	uint8_t RESERVED1[0x14u-0x0Cu];

	/* 0x14: AHB Mask */
	uint32_t volatile AHBMASK;
	/* HPB0 AHB Clock Mask */
#define PM_AHBMASK_HPB0_					(1u << 0)
	/* HPB1 AHB Clock Mask */
#define PM_AHBMASK_HPB1_					(1u << 1)
	/* HPB2 AHB Clock Mask */
#define PM_AHBMASK_HPB2_					(1u << 2)
	/* DSU AHB Clock Mask */
#define PM_AHBMASK_DSU_						(1u << 3)
	/* NVMCTRL AHB Clock Mask */
#define PM_AHBMASK_NVMCTRL_					(1u << 4)
	/* DMAC AHB Clock Mask */
#define PM_AHBMASK_DMAC_					(1u << 5)

	/* 0x18: APBA Mask */
	uint32_t volatile APBAMASK;
	/* PAC0 APB Clock Enable */
#define PM_APBAMASK_PAC0_					(1u << 0)
	/* PM APB Clock Enable */
#define PM_APBAMASK_PM_						(1u << 1)
	/* SYSCTRL APB Clock Enable */
#define PM_APBAMASK_SYSCTRL_					(1u << 2)
	/* GCLK APB Clock Enable */
#define PM_APBAMASK_GCLK_					(1u << 3)
	/* WDT APB Clock Enable */
#define PM_APBAMASK_WDT_					(1u << 4)
	/* RTC APB Clock Enable */
#define PM_APBAMASK_RTC_					(1u << 5)
	/* EIC APB Clock Enable */
#define PM_APBAMASK_EIC_					(1u << 6)

	/* 0x1C: APBB Mask */
	uint32_t volatile APBBMASK;
	/* PAC1 APB Clock Enable */
#define PM_APBBMASK_PAC1_					(1u << 0)
	/* DSU APB Clock Enable */
#define PM_APBBMASK_DSU_					(1u << 1)
	/* NVMCTRL APB Clock Enable */
#define PM_APBBMASK_NVMCTRL_					(1u << 2)
	/* PORT APB Clock Enable */
#define PM_APBBMASK_PORT_					(1u << 3)
	/* DMAC APB Clock Enable */
#define PM_APBBMASK_DMAC_					(1u << 4)
	/* HMATRIX APB Clock Enable */
#define PM_APBBMASK_HMATRIX_					(1u << 6)

	/* 0x20: APBC Mask */
	uint32_t volatile APBCMASK;
	/* PAC2 APB Clock Enable */
#define PM_APBCMASK_PAC2_					(1u << 0)
	/* EVSYS APB Clock Enable */
#define PM_APBCMASK_EVSYS_					(1u << 1)
	/* SERCOM0 APB Clock Enable */
#define PM_APBCMASK_SERCOM0					(1u << 2)
	/* SERCOM1 APB Clock Enable */
#define PM_APBCMASK_SERCOM1					(1u << 3)
	/* TC1 APB Clock Enable */
#define PM_APBCMASK_TC1						(1u << 6)
	/* TC2 APB Clock Enable */
#define PM_APBCMASK_TC2						(1u << 7)
	/* ADC APB Clock Enable */
#define PM_APBCMASK_ADC						(1u << 8)
	/* PTC APB Clock Enable */
#define PM_APBCMASK_PTC						(1u << 11)

	/* 0x24 */
	uint8_t RESERVED2[0x34u-0x24u];

	/* 0x34: Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Clock Ready Interrupt Enable */
#define PM_INTENCLR_CKRDY					(1u << 0)
	/* Clock Failure Detector Interrupt Enable */
#define PM_INTENCLR_CFD						(1u << 1)

	/* 0x35: Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Clock Ready Interrupt Enable */
#define PM_INTENSET_CKRDY					(1u << 0)
	/* Clock Failure Detector Interrupt Enable */
#define PM_INTENSET_CFD						(1u << 1)

	/* 0x36: Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Clock Ready */
#define PM_INTFLAG_CKRDY					(1u << 0)
	/* Clock Failure Detector */
#define PM_INTFLAG_CFD						(1u << 1)

	/* 0x37 */
	uint8_t RESERVED3[0x38u-0x37u];

	/* 0x38: Reset Cause */
	uint8_t volatile const RCAUSE;
	/* Power On Reset */
#define PM_RCAUSE_POR						(1u << 0)
	/* Brown Out 12 Detector Reset */
#define PM_RCAUSE_BOD12						(1u << 1)
	/* Brown Out 33 Detector Reset */
#define PM_RCAUSE_BOD33						(1u << 2)
	/* External Reset */
#define PM_RCAUSE_EXT						(1u << 4)
	/* Watchdog Reset */
#define PM_RCAUSE_WDT						(1u << 5)
	/* System Reset Request */
#define PM_RCAUSE_SYST						(1u << 6)

};


#define PORT ((struct port *)0x41004400)

struct port {

	/* 0x00: Data Direction */
	uint32_t volatile DIR;
	/* Port Data Direction */
#define PORT_DIR_DIR_Msk					(0xFFFFFFFFu << 0)
#define PORT_DIR_DIR_Pos					0

	/* 0x04: Data Direction Clear */
	uint32_t volatile DIRCLR;
	/* Port Data Direction Clear */
#define PORT_DIRCLR_DIRCLR_Msk					(0xFFFFFFFFu << 0)
#define PORT_DIRCLR_DIRCLR_Pos					0

	/* 0x08: Data Direction Set */
	uint32_t volatile DIRSET;
	/* Port Data Direction Set */
#define PORT_DIRSET_DIRSET_Msk					(0xFFFFFFFFu << 0)
#define PORT_DIRSET_DIRSET_Pos					0

	/* 0x0C: Data Direction Toggle */
	uint32_t volatile DIRTGL;
	/* Port Data Direction Toggle */
#define PORT_DIRTGL_DIRTGL_Msk					(0xFFFFFFFFu << 0)
#define PORT_DIRTGL_DIRTGL_Pos					0

	/* 0x10: Data Output Value */
	uint32_t volatile OUT;
	/* Port Data Output Value */
#define PORT_OUT_OUT_Msk					(0xFFFFFFFFu << 0)
#define PORT_OUT_OUT_Pos					0

	/* 0x14: Data Output Value Clear */
	uint32_t volatile OUTCLR;
	/* Port Data Output Value Clear */
#define PORT_OUTCLR_OUTCLR_Msk					(0xFFFFFFFFu << 0)
#define PORT_OUTCLR_OUTCLR_Pos					0

	/* 0x18: Data Output Value Set */
	uint32_t volatile OUTSET;
	/* Port Data Output Value Set */
#define PORT_OUTSET_OUTSET_Msk					(0xFFFFFFFFu << 0)
#define PORT_OUTSET_OUTSET_Pos					0

	/* 0x1C: Data Output Value Toggle */
	uint32_t volatile OUTTGL;
	/* Port Data Output Value Toggle */
#define PORT_OUTTGL_OUTTGL_Msk					(0xFFFFFFFFu << 0)
#define PORT_OUTTGL_OUTTGL_Pos					0

	/* 0x20: Data Input Value */
	uint32_t volatile const IN;
	/* Port Data Input Value */
#define PORT_IN_IN_Msk						(0xFFFFFFFFu << 0)
#define PORT_IN_IN_Pos						0

	/* 0x24: Control */
	uint32_t volatile CTRL;
	/* Input Sampling Mode */
#define PORT_CTRL_SAMPLING_Msk					(0xFFFFFFFFu << 0)
#define PORT_CTRL_SAMPLING_Pos					0

	/* 0x28: Write Configuration */
	uint32_t volatile WRCONFIG;
	/* Pin Mask for Multiple Pin Configuration */
#define PORT_WRCONFIG_PINMASK_Msk				(0xFFFFu << 0)
#define PORT_WRCONFIG_PINMASK_Pos				0
	/* Peripheral Multiplexer Enable */
#define PORT_WRCONFIG_PMUXEN					(1u << 16)
	/* Input Enable */
#define PORT_WRCONFIG_INEN					(1u << 17)
	/* Pull Enable */
#define PORT_WRCONFIG_PULLEN					(1u << 18)
	/* Output Driver Strength Selection */
#define PORT_WRCONFIG_DRVSTR					(1u << 22)
	/* Peripheral Multiplexing */
#define PORT_WRCONFIG_PMUX_Msk					(0xFu << 24)
#define PORT_WRCONFIG_PMUX_Pos					24
	/* Write PMUX */
#define PORT_WRCONFIG_WRPMUX					(1u << 28)
	/* Write PINCFG */
#define PORT_WRCONFIG_WRPINCFG					(1u << 30)
	/* Half-Word Select */
#define PORT_WRCONFIG_HWSEL					(1u << 31)

	/* 0x2C */
	uint8_t RESERVED0[0x30u-0x2Cu];

	/* 0x30: Peripheral Multiplexing n - Group 0 */
	uint8_t volatile PMUX[16];
	/* Peripheral Multiplexing */
#define PORT_PMUX_A						0x0u
#define PORT_PMUX_EIC						0x0u
#define PORT_PMUX_B						0x1u
#define PORT_PMUX_REF						0x1u
#define PORT_PMUX_ADC						0x2u
#define PORT_PMUX_C						0x2u
#define PORT_PMUX_SERCOM					0x2u
#define PORT_PMUX_D						0x3u
#define PORT_PMUX_SERCOM_ALT					0x3u
#define PORT_PMUX_E						0x4u
#define PORT_PMUX_TC						0x4u
#define PORT_PMUX_F						0x5u
#define PORT_PMUX_G						0x6u
#define PORT_PMUX_COM						0x6u
#define PORT_PMUX_H						0x7u
#define PORT_PMUX_GCLK						0x7u

	/* 0x40: Pin Configuration n - Group 0 */
	uint8_t volatile PINCFG[32];
	/* Peripheral Multiplexer Enable */
#define PORT_PINCFG_PMUXEN					(1u << 0)
	/* Input Enable */
#define PORT_PINCFG_INEN					(1u << 1)
	/* Pull Enable */
#define PORT_PINCFG_PULLEN					(1u << 2)
	/* Output Driver Strength Selection */
#define PORT_PINCFG_DRVSTR					(1u << 6)

};


#define RTC_COUNT32 ((struct rtc_count32 *)RTC_BASE)

struct rtc_count32 {

	/* 0x00: MODE0 Control */
	uint16_t volatile CTRL;
	/* Software Reset */
#define RTC_COUNT32_CTRL_SWRST					(1u << 0)
	/* Enable */
#define RTC_COUNT32_CTRL_ENABLE					(1u << 1)
	/* Operating Mode */
#define RTC_COUNT32_CTRL_MODE_Msk				(0x3u << 2)
#define RTC_COUNT32_CTRL_MODE_Pos				2
#define RTC_COUNT32_CTRL_MODE_COUNT32				(0x0u << 2)
#define RTC_COUNT32_CTRL_MODE_COUNT16				(0x1u << 2)
#define RTC_COUNT32_CTRL_MODE_CLOCK				(0x2u << 2)
	/* Clear on Match */
#define RTC_COUNT32_CTRL_MATCHCLR				(1u << 7)
	/* Prescaler */
#define RTC_COUNT32_CTRL_PRESCALER_Msk				(0xFu << 8)
#define RTC_COUNT32_CTRL_PRESCALER_Pos				8
#define RTC_COUNT32_CTRL_PRESCALER_DIV1				(0x0u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV2				(0x1u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV4				(0x2u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV8				(0x3u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV16			(0x4u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV32			(0x5u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV64			(0x6u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV128			(0x7u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV256			(0x8u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV512			(0x9u << 8)
#define RTC_COUNT32_CTRL_PRESCALER_DIV1024			(0xAu << 8)

	/* 0x02: Read Request */
	uint16_t volatile READREQ;
	/* Address */
#define RTC_COUNT32_READREQ_ADDR_Msk				(0x3Fu << 0)
#define RTC_COUNT32_READREQ_ADDR_Pos				0
	/* Read Continuously */
#define RTC_COUNT32_READREQ_RCONT				(1u << 14)
	/* Read Request */
#define RTC_COUNT32_READREQ_RREQ				(1u << 15)

	/* 0x04: MODE0 Event Control */
	uint16_t volatile EVCTRL;
	/* Periodic Interval 0 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO0				(1u << 0)
	/* Periodic Interval 1 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO1				(1u << 1)
	/* Periodic Interval 2 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO2				(1u << 2)
	/* Periodic Interval 3 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO3				(1u << 3)
	/* Periodic Interval 4 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO4				(1u << 4)
	/* Periodic Interval 5 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO5				(1u << 5)
	/* Periodic Interval 6 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO6				(1u << 6)
	/* Periodic Interval 7 Event Output Enable */
#define RTC_COUNT32_EVCTRL_PEREO7				(1u << 7)
	/* Compare 0 Event Output Enable */
#define RTC_COUNT32_EVCTRL_CMPEO0				(1u << 8)
	/* Overflow Event Output Enable */
#define RTC_COUNT32_EVCTRL_OVFEO				(1u << 15)

	/* 0x06: MODE0 Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Compare 0 Interrupt Enable */
#define RTC_COUNT32_INTENCLR_CMP0				(1u << 0)
	/* Synchronization Ready Interrupt Enable */
#define RTC_COUNT32_INTENCLR_SYNCRDY				(1u << 6)
	/* Overflow Interrupt Enable */
#define RTC_COUNT32_INTENCLR_OVF				(1u << 7)

	/* 0x07: MODE0 Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Compare 0 Interrupt Enable */
#define RTC_COUNT32_INTENSET_CMP0				(1u << 0)
	/* Synchronization Ready Interrupt Enable */
#define RTC_COUNT32_INTENSET_SYNCRDY				(1u << 6)
	/* Overflow Interrupt Enable */
#define RTC_COUNT32_INTENSET_OVF				(1u << 7)

	/* 0x08: MODE0 Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Compare 0 */
#define RTC_COUNT32_INTFLAG_CMP0				(1u << 0)
	/* Synchronization Ready */
#define RTC_COUNT32_INTFLAG_SYNCRDY				(1u << 6)
	/* Overflow */
#define RTC_COUNT32_INTFLAG_OVF					(1u << 7)

	/* 0x09 */
	uint8_t RESERVED0[0x0Au-0x09u];

	/* 0x0A: Status */
	uint8_t volatile STATUS;
	/* Synchronization Busy */
#define RTC_COUNT32_STATUS_SYNCBUSY				(1u << 7)

	/* 0x0B: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Run During Debug */
#define RTC_COUNT32_DBGCTRL_DBGRUN				(1u << 0)

	/* 0x0C: Frequency Correction */
	uint8_t volatile FREQCORR;
	/* Correction Value */
#define RTC_COUNT32_FREQCORR_VALUE_Msk				(0x7Fu << 0)
#define RTC_COUNT32_FREQCORR_VALUE_Pos				0
	/* Correction Sign */
#define RTC_COUNT32_FREQCORR_SIGN				(1u << 7)

	/* 0x0D */
	uint8_t RESERVED1[0x10u-0x0Du];

	/* 0x10: MODE0 Counter Value */
	uint32_t volatile COUNT;
	/* Counter Value */
#define RTC_COUNT32_COUNT_COUNT_Msk				(0xFFFFFFFFu << 0)
#define RTC_COUNT32_COUNT_COUNT_Pos				0

	/* 0x14 */
	uint8_t RESERVED2[0x18u-0x14u];

	/* 0x18: MODE0 Compare n Value */
	uint32_t volatile COMP;
	/* Compare Value */
#define RTC_COUNT32_COMP_COMP_Msk				(0xFFFFFFFFu << 0)
#define RTC_COUNT32_COMP_COMP_Pos				0

};


#define RTC_COUNT16 ((struct rtc_count16 *)RTC_BASE)

struct rtc_count16 {

	/* 0x00: MODE1 Control */
	uint16_t volatile CTRL;
	/* Software Reset */
#define RTC_COUNT16_CTRL_SWRST					(1u << 0)
	/* Enable */
#define RTC_COUNT16_CTRL_ENABLE					(1u << 1)
	/* Operating Mode */
#define RTC_COUNT16_CTRL_MODE_Msk				(0x3u << 2)
#define RTC_COUNT16_CTRL_MODE_Pos				2
#define RTC_COUNT16_CTRL_MODE_COUNT32				(0x0u << 2)
#define RTC_COUNT16_CTRL_MODE_COUNT16				(0x1u << 2)
#define RTC_COUNT16_CTRL_MODE_CLOCK				(0x2u << 2)
	/* Prescaler */
#define RTC_COUNT16_CTRL_PRESCALER_Msk				(0xFu << 8)
#define RTC_COUNT16_CTRL_PRESCALER_Pos				8
#define RTC_COUNT16_CTRL_PRESCALER_DIV1				(0x0u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV2				(0x1u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV4				(0x2u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV8				(0x3u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV16			(0x4u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV32			(0x5u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV64			(0x6u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV128			(0x7u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV256			(0x8u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV512			(0x9u << 8)
#define RTC_COUNT16_CTRL_PRESCALER_DIV1024			(0xAu << 8)

	/* 0x02: Read Request */
	uint16_t volatile READREQ;
	/* Address */
#define RTC_COUNT16_READREQ_ADDR_Msk				(0x3Fu << 0)
#define RTC_COUNT16_READREQ_ADDR_Pos				0
	/* Read Continuously */
#define RTC_COUNT16_READREQ_RCONT				(1u << 14)
	/* Read Request */
#define RTC_COUNT16_READREQ_RREQ				(1u << 15)

	/* 0x04: MODE1 Event Control */
	uint16_t volatile EVCTRL;
	/* Periodic Interval 0 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO0				(1u << 0)
	/* Periodic Interval 1 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO1				(1u << 1)
	/* Periodic Interval 2 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO2				(1u << 2)
	/* Periodic Interval 3 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO3				(1u << 3)
	/* Periodic Interval 4 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO4				(1u << 4)
	/* Periodic Interval 5 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO5				(1u << 5)
	/* Periodic Interval 6 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO6				(1u << 6)
	/* Periodic Interval 7 Event Output Enable */
#define RTC_COUNT16_EVCTRL_PEREO7				(1u << 7)
	/* Compare 0 Event Output Enable */
#define RTC_COUNT16_EVCTRL_CMPEO0				(1u << 8)
	/* Compare 1 Event Output Enable */
#define RTC_COUNT16_EVCTRL_CMPEO1				(1u << 9)
	/* Overflow Event Output Enable */
#define RTC_COUNT16_EVCTRL_OVFEO				(1u << 15)

	/* 0x06: MODE1 Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Compare 0 Interrupt Enable */
#define RTC_COUNT16_INTENCLR_CMP0				(1u << 0)
	/* Compare 1 Interrupt Enable */
#define RTC_COUNT16_INTENCLR_CMP1				(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define RTC_COUNT16_INTENCLR_SYNCRDY				(1u << 6)
	/* Overflow Interrupt Enable */
#define RTC_COUNT16_INTENCLR_OVF				(1u << 7)

	/* 0x07: MODE1 Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Compare 0 Interrupt Enable */
#define RTC_COUNT16_INTENSET_CMP0				(1u << 0)
	/* Compare 1 Interrupt Enable */
#define RTC_COUNT16_INTENSET_CMP1				(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define RTC_COUNT16_INTENSET_SYNCRDY				(1u << 6)
	/* Overflow Interrupt Enable */
#define RTC_COUNT16_INTENSET_OVF				(1u << 7)

	/* 0x08: MODE1 Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Compare 0 */
#define RTC_COUNT16_INTFLAG_CMP0				(1u << 0)
	/* Compare 1 */
#define RTC_COUNT16_INTFLAG_CMP1				(1u << 1)
	/* Synchronization Ready */
#define RTC_COUNT16_INTFLAG_SYNCRDY				(1u << 6)
	/* Overflow */
#define RTC_COUNT16_INTFLAG_OVF					(1u << 7)

	/* 0x09 */
	uint8_t RESERVED3[0x0Au-0x09u];

	/* 0x0A: Status */
	uint8_t volatile STATUS;
	/* Synchronization Busy */
#define RTC_COUNT16_STATUS_SYNCBUSY				(1u << 7)

	/* 0x0B: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Run During Debug */
#define RTC_COUNT16_DBGCTRL_DBGRUN				(1u << 0)

	/* 0x0C: Frequency Correction */
	uint8_t volatile FREQCORR;
	/* Correction Value */
#define RTC_COUNT16_FREQCORR_VALUE_Msk				(0x7Fu << 0)
#define RTC_COUNT16_FREQCORR_VALUE_Pos				0
	/* Correction Sign */
#define RTC_COUNT16_FREQCORR_SIGN				(1u << 7)

	/* 0x0D */
	uint8_t RESERVED4[0x10u-0x0Du];

	/* 0x10: MODE1 Counter Value */
	uint16_t volatile COUNT;
	/* Counter Value */
#define RTC_COUNT16_COUNT_COUNT_Msk				(0xFFFFu << 0)
#define RTC_COUNT16_COUNT_COUNT_Pos				0

	/* 0x12 */
	uint8_t RESERVED5[0x14u-0x12u];

	/* 0x14: MODE1 Counter Period */
	uint16_t volatile PER;
	/* Counter Period */
#define RTC_COUNT16_PER_PER_Msk					(0xFFFFu << 0)
#define RTC_COUNT16_PER_PER_Pos					0

	/* 0x16 */
	uint8_t RESERVED6[0x18u-0x16u];

	/* 0x18: MODE1 Compare n Value */
	uint32_t volatile COMP[2];
	/* Compare Value */
#define RTC_COUNT16_COMP_COMP_Msk				(0xFFFFu << 0)
#define RTC_COUNT16_COMP_COMP_Pos				0

};


#define RTC_COUNT16 ((struct rtc_count16 *)RTC_BASE)

struct rtc_clock {

	/* 0x00: MODE2 Control */
	uint16_t volatile CTRL;
	/* Software Reset */
#define RTC_CLOCK_CTRL_SWRST					(1u << 0)
	/* Enable */
#define RTC_CLOCK_CTRL_ENABLE					(1u << 1)
	/* Operating Mode */
#define RTC_CLOCK_CTRL_MODE_Msk					(0x3u << 2)
#define RTC_CLOCK_CTRL_MODE_Pos					2
#define RTC_CLOCK_CTRL_MODE_COUNT32				(0x0u << 2)
#define RTC_CLOCK_CTRL_MODE_COUNT16				(0x1u << 2)
#define RTC_CLOCK_CTRL_MODE_CLOCK				(0x2u << 2)
	/* Clock Representation */
#define RTC_CLOCK_CTRL_CLKREP					(1u << 6)
	/* Clear on Match */
#define RTC_CLOCK_CTRL_MATCHCLR					(1u << 7)
	/* Prescaler */
#define RTC_CLOCK_CTRL_PRESCALER_Msk				(0xFu << 8)
#define RTC_CLOCK_CTRL_PRESCALER_Pos				8
#define RTC_CLOCK_CTRL_PRESCALER_DIV1				(0x0u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV2				(0x1u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV4				(0x2u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV8				(0x3u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV16				(0x4u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV32				(0x5u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV64				(0x6u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV128				(0x7u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV256				(0x8u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV512				(0x9u << 8)
#define RTC_CLOCK_CTRL_PRESCALER_DIV1024			(0xAu << 8)

	/* 0x02: Read Request */
	uint16_t volatile READREQ;
	/* Address */
#define RTC_CLOCK_READREQ_ADDR_Msk				(0x3Fu << 0)
#define RTC_CLOCK_READREQ_ADDR_Pos				0
	/* Read Continuously */
#define RTC_CLOCK_READREQ_RCONT					(1u << 14)
	/* Read Request */
#define RTC_CLOCK_READREQ_RREQ					(1u << 15)

	/* 0x04: MODE2 Event Control */
	uint16_t volatile EVCTRL;
	/* Periodic Interval 0 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO0					(1u << 0)
	/* Periodic Interval 1 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO1					(1u << 1)
	/* Periodic Interval 2 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO2					(1u << 2)
	/* Periodic Interval 3 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO3					(1u << 3)
	/* Periodic Interval 4 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO4					(1u << 4)
	/* Periodic Interval 5 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO5					(1u << 5)
	/* Periodic Interval 6 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO6					(1u << 6)
	/* Periodic Interval 7 Event Output Enable */
#define RTC_CLOCK_EVCTRL_PEREO7					(1u << 7)
	/* Alarm 0 Event Output Enable */
#define RTC_CLOCK_EVCTRL_ALARMEO0				(1u << 8)
	/* Overflow Event Output Enable */
#define RTC_CLOCK_EVCTRL_OVFEO					(1u << 15)

	/* 0x06: MODE2 Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Alarm 0 Interrupt Enable */
#define RTC_CLOCK_INTENCLR_ALARM0				(1u << 0)
	/* Synchronization Ready Interrupt Enable */
#define RTC_CLOCK_INTENCLR_SYNCRDY				(1u << 6)
	/* Overflow Interrupt Enable */
#define RTC_CLOCK_INTENCLR_OVF					(1u << 7)

	/* 0x07: MODE2 Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Alarm 0 Interrupt Enable */
#define RTC_CLOCK_INTENSET_ALARM0				(1u << 0)
	/* Synchronization Ready Interrupt Enable */
#define RTC_CLOCK_INTENSET_SYNCRDY				(1u << 6)
	/* Overflow Interrupt Enable */
#define RTC_CLOCK_INTENSET_OVF					(1u << 7)

	/* 0x08: MODE2 Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Alarm 0 */
#define RTC_CLOCK_INTFLAG_ALARM0				(1u << 0)
	/* Synchronization Ready */
#define RTC_CLOCK_INTFLAG_SYNCRDY				(1u << 6)
	/* Overflow */
#define RTC_CLOCK_INTFLAG_OVF					(1u << 7)

	/* 0x09 */
	uint8_t RESERVED7[0x0Au-0x09u];

	/* 0x0A: Status */
	uint8_t volatile STATUS;
	/* Synchronization Busy */
#define RTC_CLOCK_STATUS_SYNCBUSY				(1u << 7)

	/* 0x0B: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Run During Debug */
#define RTC_CLOCK_DBGCTRL_DBGRUN				(1u << 0)

	/* 0x0C: Frequency Correction */
	uint8_t volatile FREQCORR;
	/* Correction Value */
#define RTC_CLOCK_FREQCORR_VALUE_Msk				(0x7Fu << 0)
#define RTC_CLOCK_FREQCORR_VALUE_Pos				0
	/* Correction Sign */
#define RTC_CLOCK_FREQCORR_SIGN					(1u << 7)

	/* 0x0D */
	uint8_t RESERVED8[0x10u-0x0Du];

	/* 0x10: MODE2 Clock Value */
	uint32_t volatile CLOCK;
	/* Second */
#define RTC_CLOCK_CLOCK_SECOND_Msk				(0x3Fu << 0)
#define RTC_CLOCK_CLOCK_SECOND_Pos				0
	/* Minute */
#define RTC_CLOCK_CLOCK_MINUTE_Msk				(0x3Fu << 6)
#define RTC_CLOCK_CLOCK_MINUTE_Pos				6
	/* Hour */
#define RTC_CLOCK_CLOCK_HOUR_Msk				(0x1Fu << 12)
#define RTC_CLOCK_CLOCK_HOUR_Pos				12
#define RTC_CLOCK_CLOCK_HOUR_AM					(0x0u << 12)
#define RTC_CLOCK_CLOCK_HOUR_PM					(0x10u << 12)
	/* Day */
#define RTC_CLOCK_CLOCK_DAY_Msk					(0x1Fu << 17)
#define RTC_CLOCK_CLOCK_DAY_Pos					17
	/* Month */
#define RTC_CLOCK_CLOCK_MONTH_Msk				(0xFu << 22)
#define RTC_CLOCK_CLOCK_MONTH_Pos				22
	/* Year */
#define RTC_CLOCK_CLOCK_YEAR_Msk				(0x3Fu << 26)
#define RTC_CLOCK_CLOCK_YEAR_Pos				26

	/* 0x14 */
	uint8_t RESERVED9[0x18u-0x14u];

	/* 0x18: MODE2 Alarm n Value */
	uint32_t volatile ALARM;
	/* Second */
#define RTC_CLOCK_ALARM_SECOND_Msk				(0x3Fu << 0)
#define RTC_CLOCK_ALARM_SECOND_Pos				0
	/* Minute */
#define RTC_CLOCK_ALARM_MINUTE_Msk				(0x3Fu << 6)
#define RTC_CLOCK_ALARM_MINUTE_Pos				6
	/* Hour */
#define RTC_CLOCK_ALARM_HOUR_Msk				(0x1Fu << 12)
#define RTC_CLOCK_ALARM_HOUR_Pos				12
#define RTC_CLOCK_ALARM_HOUR_AM					(0x0u << 12)
#define RTC_CLOCK_ALARM_HOUR_PM					(0x10u << 12)
	/* Day */
#define RTC_CLOCK_ALARM_DAY_Msk					(0x1Fu << 17)
#define RTC_CLOCK_ALARM_DAY_Pos					17
	/* Month */
#define RTC_CLOCK_ALARM_MONTH_Msk				(0xFu << 22)
#define RTC_CLOCK_ALARM_MONTH_Pos				22
	/* Year */
#define RTC_CLOCK_ALARM_YEAR_Msk				(0x3Fu << 26)
#define RTC_CLOCK_ALARM_YEAR_Pos				26

	/* 0x1C: MODE2 Alarm n Mask */
	uint8_t volatile MASK;
	/* Alarm Mask Selection */
#define RTC_CLOCK_MASK_SEL_Msk					(0x7u << 0)
#define RTC_CLOCK_MASK_SEL_Pos					0
#define RTC_CLOCK_MASK_SEL_OFF					(0x0u << 0)
#define RTC_CLOCK_MASK_SEL_SS					(0x1u << 0)
#define RTC_CLOCK_MASK_SEL_MMSS					(0x2u << 0)
#define RTC_CLOCK_MASK_SEL_HHMMSS				(0x3u << 0)
#define RTC_CLOCK_MASK_SEL_DDHHMMSS				(0x4u << 0)
#define RTC_CLOCK_MASK_SEL_MMDDHHMMSS				(0x5u << 0)
#define RTC_CLOCK_MASK_SEL_YYMMDDHHMMSS				(0x6u << 0)

};


#define SERCOM0 ((struct sercom *)SERCOM0_BASE)
#define SERCOM1 ((struct sercom *)SERCOM1_BASE)

struct sercom {

	/* 0x00: I2C Master Control A */
	uint32_t volatile CTRLA;
	/* Software Reset */
#define SERCOM_CTRLA_SWRST					(1u << 0)
	/* Enable */
#define SERCOM_CTRLA_ENABLE					(1u << 1)
	/* Operating Mode */
#define SERCOM_CTRLA_MODE_Msk					(0x7u << 2)
#define SERCOM_CTRLA_MODE_Pos					2
#define SERCOM_CTRLA_MODE_USART_EXT_CLK				(0x0u << 2)
#define SERCOM_CTRLA_MODE_USART_INT_CLK				(0x1u << 2)
#define SERCOM_CTRLA_MODE_SPI_SLAVE				(0x2u << 2)
#define SERCOM_CTRLA_MODE_SPI_MASTER				(0x3u << 2)
#define SERCOM_CTRLA_MODE_I2C_SLAVE				(0x4u << 2)
#define SERCOM_CTRLA_MODE_I2C_MASTER				(0x5u << 2)

};


#define I2C0_MASTER ((struct i2c_master *)SERCOM0_BASE)
#define I2C1_MASTER ((struct i2c_master *)SERCOM1_BASE)

struct i2c_master {

	/* 0x00: I2C Master Control A */
	uint32_t volatile CTRLA;
	/* Software Reset */
#define I2C_MASTER_CTRLA_SWRST					(1u << 0)
	/* Enable */
#define I2C_MASTER_CTRLA_ENABLE					(1u << 1)
	/* Operating Mode */
#define I2C_MASTER_CTRLA_MODE_Msk				(0x7u << 2)
#define I2C_MASTER_CTRLA_MODE_Pos				2
#define I2C_MASTER_CTRLA_MODE_USART_EXT_CLK			(0x0u << 2)
#define I2C_MASTER_CTRLA_MODE_USART_INT_CLK			(0x1u << 2)
#define I2C_MASTER_CTRLA_MODE_SPI_SLAVE				(0x2u << 2)
#define I2C_MASTER_CTRLA_MODE_SPI_MASTER			(0x3u << 2)
#define I2C_MASTER_CTRLA_MODE_I2C_SLAVE				(0x4u << 2)
#define I2C_MASTER_CTRLA_MODE_I2C_MASTER			(0x5u << 2)
	/* Run in Standby */
#define I2C_MASTER_CTRLA_RUNSTDBY				(1u << 7)
	/* Pin Usage */
#define I2C_MASTER_CTRLA_PINOUT					(1u << 16)
	/* SDA Hold Time */
#define I2C_MASTER_CTRLA_SDAHOLD_Msk				(0x3u << 20)
#define I2C_MASTER_CTRLA_SDAHOLD_Pos				20
#define I2C_MASTER_CTRLA_SDAHOLD_75_NS				(0x1u << 20)
#define I2C_MASTER_CTRLA_SDAHOLD_450_NS				(0x2u << 20)
#define I2C_MASTER_CTRLA_SDAHOLD_600_NS				(0x3u << 20)
	/* Master SCL Low Extend Timeout */
#define I2C_MASTER_CTRLA_MEXTTOEN				(1u << 22)
	/* Slave SCL Low Extend Timeout */
#define I2C_MASTER_CTRLA_SEXTTOEN				(1u << 23)
	/* Transfer Speed */
#define I2C_MASTER_CTRLA_SPEED_Msk				(0x3u << 24)
#define I2C_MASTER_CTRLA_SPEED_Pos				24
#define I2C_MASTER_CTRLA_SPEED_400_KHZ_MAX			(0x0u << 24)
#define I2C_MASTER_CTRLA_SPEED_1000_KHZ_MAX			(0x1u << 24)
#define I2C_MASTER_CTRLA_SPEED_3400_KHZ_MAX			(0x2u << 24)
	/* SCL Clock Stretch Mode */
#define I2C_MASTER_CTRLA_SCLSM					(1u << 27)
	/* Inactive Time-Out */
#define I2C_MASTER_CTRLA_INACTOUT_Msk				(0x3u << 28)
#define I2C_MASTER_CTRLA_INACTOUT_Pos				28
#define I2C_MASTER_CTRLA_INACTOUT_DIS				(0x0u << 28)
#define I2C_MASTER_CTRLA_INACTOUT_55_US				(0x1u << 28)
#define I2C_MASTER_CTRLA_INACTOUT_105_US			(0x2u << 28)
#define I2C_MASTER_CTRLA_INACTOUT_205_US			(0x3u << 28)

	/* SCL Low Timeout Enable */
#define I2C_MASTER_CTRLA_LOWTOUTEN				(1u << 30)

	/* 0x04: I2C_MASTER Control B */
	uint32_t volatile CTRLB;
	/* Smart Mode Enable */
#define I2C_MASTER_CTRLB_SMEN					(1u << 8)
	/* Quick Command Enable */
#define I2C_MASTER_CTRLB_QCEN					(1u << 9)
	/* Command */
#define I2C_MASTER_CTRLB_CMD_Msk				(0x3u << 16)
#define I2C_MASTER_CTRLB_CMD_Pos				16
#define I2C_MASTER_CTRLB_CMD_ACK_START				(0x1u << 16)
#define I2C_MASTER_CTRLB_CMD_ACK_READ				(0x2u << 16)
#define I2C_MASTER_CTRLB_CMD_ACK_STOP				(0x3u << 16)

	/* Acknowledge Action */
#define I2C_MASTER_CTRLB_ACKACT					(1u << 18)

	/* 0x08 */
	uint8_t RESERVED0[0x0Cu-0x08u];

	/* 0x0C: I2C_MASTER Baud Rate */
	uint32_t volatile BAUD;
	/* Baud Rate Value */
#define I2C_MASTER_BAUD_BAUD_Msk				(0xFFu << 0)
#define I2C_MASTER_BAUD_BAUD_Pos				0
	/* Baud Rate Value Low */
#define I2C_MASTER_BAUD_BAUDLOW_Msk				(0xFFu << 8)
#define I2C_MASTER_BAUD_BAUDLOW_Pos				8
	/* High Speed Baud Rate Value */
#define I2C_MASTER_BAUD_HSBAUD_Msk				(0xFFu << 16)
#define I2C_MASTER_BAUD_HSBAUD_Pos				16
	/* High Speed Baud Rate Value Low */
#define I2C_MASTER_BAUD_HSBAUDLOW_Msk				(0xFFu << 24)
#define I2C_MASTER_BAUD_HSBAUDLOW_Pos				24

	/* 0x10 */
	uint8_t RESERVED1[0x14u-0x10u];

	/* 0x14: I2C_MASTER Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Master On Bus Interrupt Disable */
#define I2C_MASTER_INTENCLR_MB					(1u << 0)
	/* Slave On Bus Interrupt Disable */
#define I2C_MASTER_INTENCLR_SB					(1u << 1)
	/* Combined Error Interrupt Disable */
#define I2C_MASTER_INTENCLR_ERROR				(1u << 7)

	/* 0x15 */
	uint8_t RESERVED2[0x16u-0x15u];

	/* 0x16: I2C_MASTER Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Master On Bus Interrupt Enable */
#define I2C_MASTER_INTENSET_MB					(1u << 0)
	/* Slave On Bus Interrupt Enable */
#define I2C_MASTER_INTENSET_SB					(1u << 1)
	/* Combined Error Interrupt Enable */
#define I2C_MASTER_INTENSET_ERROR				(1u << 7)

	/* 0x17 */
	uint8_t RESERVED3[0x18u-0x17u];

	/* 0x18: I2C_MASTER Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Master On Bus Interrupt */
#define I2C_MASTER_INTFLAG_MB					(1u << 0)
	/* Slave On Bus Interrupt */
#define I2C_MASTER_INTFLAG_SB					(1u << 1)
	/* Combined Error Interrupt */
#define I2C_MASTER_INTFLAG_ERROR				(1u << 7)

	/* 0x19 */
	uint8_t RESERVED4[0x1Au-0x19u];

	/* 0x1A: I2C_MASTER Status */
	uint16_t volatile STATUS;
	/* Bus Error */
#define I2C_MASTER_STATUS_BUSERR				(1u << 0)
	/* Arbitration Lost */
#define I2C_MASTER_STATUS_ARBLOST				(1u << 1)
	/* Received Not Acknowledge */
#define I2C_MASTER_STATUS_RXNACK				(1u << 2)
	/* Bus State */
#define I2C_MASTER_STATUS_BUSSTATE_Msk				(0x3u << 4)
#define I2C_MASTER_STATUS_BUSSTATE_Pos				4
#define I2C_MASTER_STATUS_BUSSTATE_IDLE				(0x1u << 4)
#define I2C_MASTER_STATUS_BUSSTATE_OWNER			(0x2u << 4)
#define I2C_MASTER_STATUS_BUSSTATE_BUSY				(0x3u << 4)
	/* SCL Low Timeout */
#define I2C_MASTER_STATUS_LOWTOUT				(1u << 6)
	/* Clock Hold */
#define I2C_MASTER_STATUS_CLKHOLD				(1u << 7)
	/* Master SCL Low Extend Timeout */
#define I2C_MASTER_STATUS_MEXTTOUT				(1u << 8)
	/* Slave SCL Low Extend Timeout */
#define I2C_MASTER_STATUS_SEXTTOUT				(1u << 9)
	/* Length Error */
#define I2C_MASTER_STATUS_LENERR				(1u << 10)

	/* 0x1C: I2C_MASTER Syncbusy */
	uint32_t volatile const SYNCBUSY;
	/* Software Reset Synchronization Busy */
#define I2C_MASTER_SYNCBUSY_SWRST				(1u << 0)
	/* SERCOM Enable Synchronization Busy */
#define I2C_MASTER_SYNCBUSY_ENABLE				(1u << 1)
	/* System Operation Synchronization Busy */
#define I2C_MASTER_SYNCBUSY_SYSOP				(1u << 2)

	/* 0x20 */
	uint8_t RESERVED5[0x24u-0x20u];

	/* 0x24: I2C_MASTER Address */
	uint32_t volatile ADDR;
	/* Address Value */
#define I2C_MASTER_ADDR_ADDR_Msk				(0x7FFu << 0)
#define I2C_MASTER_ADDR_ADDR_Pos				0
	/* Length Enable */
#define I2C_MASTER_ADDR_LENEN					(1u << 13)
	/* High Speed Mode */
#define I2C_MASTER_ADDR_HS					(1u << 14)
	/* Ten Bit Addressing Enable */
#define I2C_MASTER_ADDR_TENBITEN				(1u << 15)
	/* Length */
#define I2C_MASTER_ADDR_LEN_Msk					(0xFFu << 16)
#define I2C_MASTER_ADDR_LEN_Pos					16

	/* 0x28: I2C_MASTER Data */
	uint8_t volatile DATA;
	/* Data Value */
#define I2C_MASTER_DATA_DATA_Msk				(0xFFu << 0)
#define I2C_MASTER_DATA_DATA_Pos				0

	/* 0x29 */
	uint8_t RESERVED6[0x30u-0x29u];

	/* 0x30: I2C_MASTER Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Mode */
#define I2C_MASTER_DBGCTRL_DBGSTOP				(1u << 0)

};


#define I2C0_SLAVE ((struct i2c_slave *)SERCOM0_BASE)
#define I2C1_SLAVE ((struct i2c_slave *)SERCOM1_BASE)

struct i2c_slave {

	/* 0x00: I2C Slave Control A */
	uint32_t volatile CTRLA;
	/* Software Reset */
#define I2C_SLAVE_CTRLA_SWRST					(1u << 0)
	/* Enable */
#define I2C_SLAVE_CTRLA_ENABLE					(1u << 1)
	/* Operating Mode */
#define I2C_SLAVE_CTRLA_MODE_Msk				(0x7u << 2)
#define I2C_SLAVE_CTRLA_MODE_Pos				2
#define I2C_SLAVE_CTRLA_MODE_USART_EXT_CLK			(0x0u << 2)
#define I2C_SLAVE_CTRLA_MODE_USART_INT_CLK			(0x1u << 2)
#define I2C_SLAVE_CTRLA_MODE_SPI_SLAVE				(0x2u << 2)
#define I2C_SLAVE_CTRLA_MODE_SPI_MASTER				(0x3u << 2)
#define I2C_SLAVE_CTRLA_MODE_I2C_SLAVE				(0x4u << 2)
#define I2C_SLAVE_CTRLA_MODE_I2C_MASTER				(0x5u << 2)
	/* Run during Standby */
#define I2C_SLAVE_CTRLA_RUNSTDBY				(1u << 7)
	/* Pin Usage */
#define I2C_SLAVE_CTRLA_PINOUT					(1u << 16)
	/* SDA Hold Time */
#define I2C_SLAVE_CTRLA_SDAHOLD_Msk				(0x3u << 20)
#define I2C_SLAVE_CTRLA_SDAHOLD_Pos				20
	/* Slave SCL Low Extend Timeout */
#define I2C_SLAVE_CTRLA_SEXTTOEN				(1u << 23)
	/* Transfer Speed */
#define I2C_SLAVE_CTRLA_SPEED_Msk				(0x3u << 24)
#define I2C_SLAVE_CTRLA_SPEED_Pos				24
	/* SCL Clock Stretch Mode */
#define I2C_SLAVE_CTRLA_SCLSM					(1u << 27)
	/* SCL Low Timeout Enable */
#define I2C_SLAVE_CTRLA_LOWTOUTEN				(1u << 30)

	/* 0x04: I2CS Control B */
	uint32_t volatile CTRLB;
	/* Smart Mode Enable */
#define I2C_SLAVE_CTRLB_SMEN					(1u << 8)
	/* PMBus Group Command */
#define I2C_SLAVE_CTRLB_GCMD					(1u << 9)
	/* Automatic Address Acknowledge */
#define I2C_SLAVE_CTRLB_AACKEN					(1u << 10)
	/* Address Mode */
#define I2C_SLAVE_CTRLB_AMODE_Msk				(0x3u << 14)
#define I2C_SLAVE_CTRLB_AMODE_Pos				14
	/* Command */
#define I2C_SLAVE_CTRLB_CMD_Msk					(0x3u << 16)
#define I2C_SLAVE_CTRLB_CMD_Pos					16
	/* Acknowledge Action */
#define I2C_SLAVE_CTRLB_ACKACT					(1u << 18)

	/* 0x08 */
	uint8_t RESERVED7[0x14u-0x08u];

	/* 0x14: I2CS Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Stop Received Interrupt Disable */
#define I2C_SLAVE_INTENCLR_PREC					(1u << 0)
	/* Address Match Interrupt Disable */
#define I2C_SLAVE_INTENCLR_AMATCH				(1u << 1)
	/* Data Interrupt Disable */
#define I2C_SLAVE_INTENCLR_DRDY					(1u << 2)
	/* Combined Error Interrupt Disable */
#define I2C_SLAVE_INTENCLR_ERROR				(1u << 7)

	/* 0x15 */
	uint8_t RESERVED8[0x16u-0x15u];

	/* 0x16: I2CS Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Stop Received Interrupt Enable */
#define I2C_SLAVE_INTENSET_PREC					(1u << 0)
	/* Address Match Interrupt Enable */
#define I2C_SLAVE_INTENSET_AMATCH				(1u << 1)
	/* Data Interrupt Enable */
#define I2C_SLAVE_INTENSET_DRDY					(1u << 2)
	/* Combined Error Interrupt Enable */
#define I2C_SLAVE_INTENSET_ERROR				(1u << 7)

	/* 0x17 */
	uint8_t RESERVED9[0x18u-0x17u];

	/* 0x18: I2CS Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Stop Received Interrupt */
#define I2C_SLAVE_INTFLAG_PREC					(1u << 0)
	/* Address Match Interrupt */
#define I2C_SLAVE_INTFLAG_AMATCH				(1u << 1)
	/* Data Interrupt */
#define I2C_SLAVE_INTFLAG_DRDY					(1u << 2)
	/* Combined Error Interrupt */
#define I2C_SLAVE_INTFLAG_ERROR					(1u << 7)

	/* 0x19 */
	uint8_t RESERVED10[0x1Au-0x19u];

	/* 0x1A: I2CS Status */
	uint16_t volatile STATUS;
	/* Bus Error */
#define I2C_SLAVE_STATUS_BUSERR					(1u << 0)
	/* Transmit Collision */
#define I2C_SLAVE_STATUS_COLL					(1u << 1)
	/* Received Not Acknowledge */
#define I2C_SLAVE_STATUS_RXNACK					(1u << 2)
	/* Read/Write Direction */
#define I2C_SLAVE_STATUS_DIR					(1u << 3)
	/* Repeated Start */
#define I2C_SLAVE_STATUS_SR					(1u << 4)
	/* SCL Low Timeout */
#define I2C_SLAVE_STATUS_LOWTOUT				(1u << 6)
	/* Clock Hold */
#define I2C_SLAVE_STATUS_CLKHOLD				(1u << 7)
	/* Slave SCL Low Extend Timeout */
#define I2C_SLAVE_STATUS_SEXTTOUT				(1u << 9)
	/* High Speed */
#define I2C_SLAVE_STATUS_HS					(1u << 10)

	/* 0x1C: I2CS Syncbusy */
	uint32_t volatile const SYNCBUSY;
	/* Software Reset Synchronization Busy */
#define I2C_SLAVE_SYNCBUSY_SWRST				(1u << 0)
	/* SERCOM Enable Synchronization Busy */
#define I2C_SLAVE_SYNCBUSY_ENABLE				(1u << 1)

	/* 0x20 */
	uint8_t RESERVED11[0x24u-0x20u];

	/* 0x24: I2CS Address */
	uint32_t volatile ADDR;
	/* General Call Address Enable */
#define I2C_SLAVE_ADDR_GENCEN					(1u << 0)
	/* Address Value */
#define I2C_SLAVE_ADDR_ADDR_Msk					(0x3FFu << 1)
#define I2C_SLAVE_ADDR_ADDR_Pos					1
	/* Ten Bit Addressing Enable */
#define I2C_SLAVE_ADDR_TENBITEN					(1u << 15)
	/* Address Mask */
#define I2C_SLAVE_ADDR_ADDRMASK_Msk				(0x3FFu << 17)
#define I2C_SLAVE_ADDR_ADDRMASK_Pos				17

	/* 0x28: I2CS Data */
	uint8_t volatile DATA;
	/* Data Value */
#define I2C_SLAVE_DATA_DATA_Msk					(0xFFu << 0)
#define I2C_SLAVE_DATA_DATA_Pos					0

};


#define SPI0 ((struct spi *)SERCOM0_BASE)
#define SPI1 ((struct spi *)SERCOM1_BASE)

struct spi {

	/* 0x00: SPI Control A */
	uint32_t volatile CTRLA;
	/* Software Reset */
#define SPI_CTRLA_SWRST						(1u << 0)
	/* Enable */
#define SPI_CTRLA_ENABLE					(1u << 1)
	/* Operating Mode */
#define SPI_CTRLA_MODE_Msk					(0x7u << 2)
#define SPI_CTRLA_MODE_Pos					2
#define SPI_CTRLA_MODE_USART_EXT_CLK				(0x0u << 2)
#define SPI_CTRLA_MODE_USART_INT_CLK				(0x1u << 2)
#define SPI_CTRLA_MODE_SPI_SLAVE				(0x2u << 2)
#define SPI_CTRLA_MODE_SPI_MASTER				(0x3u << 2)
#define SPI_CTRLA_MODE_I2C_SLAVE				(0x4u << 2)
#define SPI_CTRLA_MODE_I2C_MASTER				(0x5u << 2)
	/* Run during Standby */
#define SPI_CTRLA_RUNSTDBY					(1u << 7)
	/* Immediate Buffer Overflow Notification */
#define SPI_CTRLA_IBON						(1u << 8)
	/* Data Out Pinout */
#define SPI_CTRLA_DOPO_Msk					(0x3u << 16)
#define SPI_CTRLA_DOPO_Pos					16
#define SPI_CTRLA_DOPO_MOSI0_SCK1_SS2				(0x0u << 16)
#define SPI_CTRLA_DOPO_MOSI2_SCK3_SS1				(0x1u << 16)
#define SPI_CTRLA_DOPO_MOSI3_SCK1_SS2				(0x2u << 16)
#define SPI_CTRLA_DOPO_MOSI0_SCK3_SS1				(0x3u << 16)
	/* Data In Pinout */
#define SPI_CTRLA_DIPO_Msk					(0x3u << 20)
#define SPI_CTRLA_DIPO_Pos					20
#define SPI_CTRLA_DIPO_MISO0					(0x0u << 20)
#define SPI_CTRLA_DIPO_MISO1					(0x1u << 20)
#define SPI_CTRLA_DIPO_MISO2					(0x2u << 20)
#define SPI_CTRLA_DIPO_MISO3					(0x3u << 20)
	/* Frame Format */
#define SPI_CTRLA_FORM_Msk					(0xFu << 24)
#define SPI_CTRLA_FORM_Pos					24
#define SPI_CTRLA_FORM_SPI					(0x0u << 24)
#define SPI_CTRLA_FORM_SPI_ADDR					(0x1u << 24)
	/* Clock Phase */
#define SPI_CTRLA_CPHA						(1u << 28)
	/* Clock Polarity */
#define SPI_CTRLA_CPOL						(1u << 29)
	/* Data Order */
#define SPI_CTRLA_DORD						(1u << 30)

	/* 0x04: SPI Control B */
	uint32_t volatile CTRLB;
	/* Character Size */
#define SPI_CTRLB_CHSIZE_Msk					(0x7u << 0)
#define SPI_CTRLB_CHSIZE_Pos					0
#define SPI_CTRLB_CHSIZE_8BIT					(0x0u << 0)
#define SPI_CTRLB_CHSIZE_9BIT					(0x1u << 0)

	/* Data Preload Enable */
#define SPI_CTRLB_PLOADEN					(1u << 6)
	/* Slave Select Low Detect Enable */
#define SPI_CTRLB_SSDE						(1u << 9)
	/* Master Slave Select Enable */
#define SPI_CTRLB_MSSEN						(1u << 13)
	/* Address Mode */
#define SPI_CTRLB_AMODE_Msk					(0x3u << 14)
#define SPI_CTRLB_AMODE_Pos					14
	/* Receiver Enable */
#define SPI_CTRLB_RXEN						(1u << 17)

	/* 0x08 */
	uint8_t RESERVED12[0x0Cu-0x08u];

	/* 0x0C: SPI Baud Rate */
	uint8_t volatile BAUD;
	/* Baud Rate Value */
#define SPI_BAUD_BAUD_Msk					(0xFFu << 0)
#define SPI_BAUD_BAUD_Pos					0

	/* 0x0D */
	uint8_t RESERVED13[0x14u-0x0Du];

	/* 0x14: SPI Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Data Register Empty Interrupt Disable */
#define SPI_INTENCLR_DRE					(1u << 0)
	/* Transmit Complete Interrupt Disable */
#define SPI_INTENCLR_TXC					(1u << 1)
	/* Receive Complete Interrupt Disable */
#define SPI_INTENCLR_RXC					(1u << 2)
	/* Slave Select Low Interrupt Disable */
#define SPI_INTENCLR_SSL					(1u << 3)
	/* Combined Error Interrupt Disable */
#define SPI_INTENCLR_ERROR					(1u << 7)

	/* 0x15 */
	uint8_t RESERVED14[0x16u-0x15u];

	/* 0x16: SPI Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Data Register Empty Interrupt Enable */
#define SPI_INTENSET_DRE					(1u << 0)
	/* Transmit Complete Interrupt Enable */
#define SPI_INTENSET_TXC					(1u << 1)
	/* Receive Complete Interrupt Enable */
#define SPI_INTENSET_RXC					(1u << 2)
	/* Slave Select Low Interrupt Enable */
#define SPI_INTENSET_SSL					(1u << 3)
	/* Combined Error Interrupt Enable */
#define SPI_INTENSET_ERROR					(1u << 7)

	/* 0x17 */
	uint8_t RESERVED15[0x18u-0x17u];

	/* 0x18: SPI Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Data Register Empty Interrupt */
#define SPI_INTFLAG_DRE						(1u << 0)
	/* Transmit Complete Interrupt */
#define SPI_INTFLAG_TXC						(1u << 1)
	/* Receive Complete Interrupt */
#define SPI_INTFLAG_RXC						(1u << 2)
	/* Slave Select Low Interrupt Flag */
#define SPI_INTFLAG_SSL						(1u << 3)
	/* Combined Error Interrupt */
#define SPI_INTFLAG_ERROR					(1u << 7)

	/* 0x19 */
	uint8_t RESERVED16[0x1Au-0x19u];

	/* 0x1A: SPI Status */
	uint16_t volatile STATUS;
	/* Buffer Overflow */
#define SPI_STATUS_BUFOVF					(1u << 2)

	/* 0x1C: SPI Syncbusy */
	uint32_t volatile const SYNCBUSY;
	/* Software Reset Synchronization Busy */
#define SPI_SYNCBUSY_SWRST					(1u << 0)
	/* SERCOM Enable Synchronization Busy */
#define SPI_SYNCBUSY_ENABLE					(1u << 1)
	/* CTRLB Synchronization Busy */
#define SPI_SYNCBUSY_CTRLB					(1u << 2)

	/* 0x20 */
	uint8_t RESERVED17[0x24u-0x20u];

	/* 0x24: SPI Address */
	uint32_t volatile ADDR;
	/* Address Value */
#define SPI_ADDR_ADDR_Msk					(0xFFu << 0)
#define SPI_ADDR_ADDR_Pos					0
	/* Address Mask */
#define SPI_ADDR_ADDRMASK_Msk					(0xFFu << 16)
#define SPI_ADDR_ADDRMASK_Pos					16

	/* 0x28: SPI Data */
	uint32_t volatile DATA;
	/* Data Value */
#define SPI_DATA_DATA_Msk					(0x1FFu << 0)
#define SPI_DATA_DATA_Pos					0

	/* 0x2C */
	uint8_t RESERVED18[0x30u-0x2Cu];

	/* 0x30: SPI Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Mode */
#define SPI_DBGCTRL_DBGSTOP					(1u << 0)

};


#define USART0 ((struct usart *)SERCOM0_BASE)
#define USART1 ((struct usart *)SERCOM1_BASE)

struct usart {

	/* 0x00: USART Control A */
	uint32_t volatile CTRLA;
	/* Software Reset */
#define USART_CTRLA_SWRST					(1u << 0)
	/* Enable */
#define USART_CTRLA_ENABLE					(1u << 1)
	/* Operating Mode */
#define USART_CTRLA_MODE_Msk					(0x7u << 2)
#define USART_CTRLA_MODE_Pos					2
#define USART_CTRLA_MODE_USART_EXT_CLK				(0x0u << 2)
#define USART_CTRLA_MODE_USART_INT_CLK				(0x1u << 2)
#define USART_CTRLA_MODE_SPI_SLAVE				(0x2u << 2)
#define USART_CTRLA_MODE_SPI_MASTER				(0x3u << 2)
#define USART_CTRLA_MODE_I2C_SLAVE				(0x4u << 2)
#define USART_CTRLA_MODE_I2C_MASTER				(0x5u << 2)
	/* Run during Standby */
#define USART_CTRLA_RUNSTDBY					(1u << 7)
	/* Immediate Buffer Overflow Notification */
#define USART_CTRLA_IBON					(1u << 8)
	/* Sample */
#define USART_CTRLA_SAMPR_Msk					(0x7u << 13)
#define USART_CTRLA_SAMPR_Pos					13
#define USART_CTRLA_SAMPR_16_ARITHMETIC				(0x0u << 13)
#define USART_CTRLA_SAMPR_16_FRACTIONAL				(0x1u << 13)
#define USART_CTRLA_SAMPR_8_ARITHMETIC				(0x2u << 13)
#define USART_CTRLA_SAMPR_8_FRACTIONAL				(0x3u << 13)
#define USART_CTRLA_SAMPR_3_ARITHMETIC				(0x4u << 13)

	/* Transmit Data Pinout */
#define USART_CTRLA_TXPO_Msk					(0x3u << 16)
#define USART_CTRLA_TXPO_Pos					16
	/* Receive Data Pinout */
#define USART_CTRLA_RXPO_Msk					(0x3u << 20)
#define USART_CTRLA_RXPO_Pos					20
	/* Sample Adjustment */
#define USART_CTRLA_SAMPA_Msk					(0x3u << 22)
#define USART_CTRLA_SAMPA_Pos					22
	/* Frame Format */
#define USART_CTRLA_FORM_Msk					(0xFu << 24)
#define USART_CTRLA_FORM_Pos					24
	/* Communication Mode */
#define USART_CTRLA_CMODE					(1u << 28)
	/* Clock Polarity */
#define USART_CTRLA_CPOL					(1u << 29)
	/* Data Order */
#define USART_CTRLA_DORD					(1u << 30)

	/* 0x04: USART Control B */
	uint32_t volatile CTRLB;
	/* Character Size */
#define USART_CTRLB_CHSIZE_Msk					(0x7u << 0)
#define USART_CTRLB_CHSIZE_Pos					0
	/* Stop Bit Mode */
#define USART_CTRLB_SBMODE					(1u << 6)
	/* Collision Detection Enable */
#define USART_CTRLB_COLDEN					(1u << 8)
	/* Start of Frame Detection Enable */
#define USART_CTRLB_SFDE					(1u << 9)
	/* Encoding Format */
#define USART_CTRLB_ENC						(1u << 10)
	/* Parity Mode */
#define USART_CTRLB_PMODE					(1u << 13)
	/* Transmitter Enable */
#define USART_CTRLB_TXEN					(1u << 16)
	/* Receiver Enable */
#define USART_CTRLB_RXEN					(1u << 17)

	/* 0x08 */
	uint8_t RESERVED19[0x0Cu-0x08u];

	/* 0x0C: USART Baud Rate */
	uint16_t volatile BAUD;
	/* Baud Rate Value */
#define USART_BAUD_BAUD_Msk					(0xFFFFu << 0)
#define USART_BAUD_BAUD_Pos					0
	/* Baud Rate Value, Integer Part */
#define USART_BAUD_IP_Msk					(0x1FFFu << 0)
#define USART_BAUD_IP_Pos					0
	/* Baud Rate Value, Fractionnal Part */
#define USART_BAUD_FP_Msk					(0x7u << 13)
#define USART_BAUD_FP_Pos					8

	/* 0x0C: USART Baud Rate */
	uint16_t volatile BAUD_FRAC_MODE;
	/* Baud Rate Value */
#define USART_BAUD_FRAC_MODE_BAUD_Msk				(0x1FFFu << 0)
#define USART_BAUD_FRAC_MODE_BAUD_Pos				0
	/* Fractional Part */
#define USART_BAUD_FRAC_MODE_FP_Msk				(0x7u << 13)
#define USART_BAUD_FRAC_MODE_FP_Pos				13

	/* 0x0C: USART Baud Rate */
	uint16_t volatile BAUD_FRACFP_MODE;
	/* Baud Rate Value */
#define USART_BAUD_FRACFP_MODE_BAUD_Msk				(0x1FFFu << 0)
#define USART_BAUD_FRACFP_MODE_BAUD_Pos				0
	/* Fractional Part */
#define USART_BAUD_FRACFP_MODE_FP_Msk				(0x7u << 13)
#define USART_BAUD_FRACFP_MODE_FP_Pos				13

	/* 0x0C: USART Baud Rate */
	uint16_t volatile BAUD_USARTFP_MODE;
	/* Baud Rate Value */
#define USART_BAUD_USARTFP_MODE_BAUD_Msk			(0xFFFFu << 0)
#define USART_BAUD_USARTFP_MODE_BAUD_Pos			0

	/* 0x0E: USART Receive Pulse Length */
	uint8_t volatile RXPL;
	/* Receive Pulse Length */
#define USART_RXPL_RXPL_Msk					(0xFFu << 0)
#define USART_RXPL_RXPL_Pos					0

	/* 0x0F */
	uint8_t RESERVED20[0x14u-0x0Fu];

	/* 0x14: USART Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Data Register Empty Interrupt Disable */
#define USART_INTENCLR_DRE					(1u << 0)
	/* Transmit Complete Interrupt Disable */
#define USART_INTENCLR_TXC					(1u << 1)
	/* Receive Complete Interrupt Disable */
#define USART_INTENCLR_RXC					(1u << 2)
	/* Receive Start Interrupt Disable */
#define USART_INTENCLR_RXS					(1u << 3)
	/* Clear To Send Input Change Interrupt Disable */
#define USART_INTENCLR_CTSIC					(1u << 4)
	/* Break Received Interrupt Disable */
#define USART_INTENCLR_RXBRK					(1u << 5)
	/* Combined Error Interrupt Disable */
#define USART_INTENCLR_ERROR					(1u << 7)

	/* 0x15 */
	uint8_t RESERVED21[0x16u-0x15u];

	/* 0x16: USART Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Data Register Empty Interrupt Enable */
#define USART_INTENSET_DRE					(1u << 0)
	/* Transmit Complete Interrupt Enable */
#define USART_INTENSET_TXC					(1u << 1)
	/* Receive Complete Interrupt Enable */
#define USART_INTENSET_RXC					(1u << 2)
	/* Receive Start Interrupt Enable */
#define USART_INTENSET_RXS					(1u << 3)
	/* Clear To Send Input Change Interrupt Enable */
#define USART_INTENSET_CTSIC					(1u << 4)
	/* Break Received Interrupt Enable */
#define USART_INTENSET_RXBRK					(1u << 5)
	/* Combined Error Interrupt Enable */
#define USART_INTENSET_ERROR					(1u << 7)

	/* 0x17 */
	uint8_t RESERVED22[0x18u-0x17u];

	/* 0x18: USART Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Data Register Empty Interrupt */
#define USART_INTFLAG_DRE					(1u << 0)
	/* Transmit Complete Interrupt */
#define USART_INTFLAG_TXC					(1u << 1)
	/* Receive Complete Interrupt */
#define USART_INTFLAG_RXC					(1u << 2)
	/* Receive Start Interrupt */
#define USART_INTFLAG_RXS					(1u << 3)
	/* Clear To Send Input Change Interrupt */
#define USART_INTFLAG_CTSIC					(1u << 4)
	/* Break Received Interrupt */
#define USART_INTFLAG_RXBRK					(1u << 5)
	/* Combined Error Interrupt */
#define USART_INTFLAG_ERROR					(1u << 7)

	/* 0x19 */
	uint8_t RESERVED23[0x1Au-0x19u];

	/* 0x1A: USART Status */
	uint16_t volatile STATUS;
	/* Parity Error */
#define USART_STATUS_PERR					(1u << 0)
	/* Frame Error */
#define USART_STATUS_FERR					(1u << 1)
	/* Buffer Overflow */
#define USART_STATUS_BUFOVF					(1u << 2)
	/* Clear To Send */
#define USART_STATUS_CTS					(1u << 3)
	/* Inconsistent Sync Field */
#define USART_STATUS_ISF					(1u << 4)
	/* Collision Detected */
#define USART_STATUS_COLL					(1u << 5)

	/* 0x1C: USART Syncbusy */
	uint32_t volatile const SYNCBUSY;
	/* Software Reset Synchronization Busy */
#define USART_SYNCBUSY_SWRST					(1u << 0)
	/* SERCOM Enable Synchronization Busy */
#define USART_SYNCBUSY_ENABLE					(1u << 1)
	/* CTRLB Synchronization Busy */
#define USART_SYNCBUSY_CTRLB					(1u << 2)

	/* 0x20 */
	uint8_t RESERVED24[0x28u-0x20u];

	/* 0x28: USART Data */
	uint16_t volatile DATA;
	/* Data Value */
#define USART_DATA_DATA_Msk					(0x1FFu << 0)
#define USART_DATA_DATA_Pos					0

	/* 0x2A */
	uint8_t RESERVED25[0x30u-0x2Au];

	/* 0x30: USART Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Mode */
#define USART_DBGCTRL_DBGSTOP					(1u << 0)

};


#define SYSCTRL ((struct sysctrl *)0x40000800)

struct sysctrl {

	/* 0x00: Interrupt Enable Clear */
	uint32_t volatile INTENCLR;
	/* XOSC Ready Interrupt Enable */
#define SYSCTRL_INTENCLR_XOSCRDY				(1u << 0)
	/* XOSC32K Ready Interrupt Enable */
#define SYSCTRL_INTENCLR_XOSC32KRDY				(1u << 1)
	/* OSC32K Ready Interrupt Enable */
#define SYSCTRL_INTENCLR_OSC32KRDY				(1u << 2)
	/* OSC8M Ready Interrupt Enable */
#define SYSCTRL_INTENCLR_OSC8MRDY				(1u << 3)
	/* DFLL Ready Interrupt Enable */
#define SYSCTRL_INTENCLR_DFLLRDY				(1u << 4)
	/* DFLL Out Of Bounds Interrupt Enable */
#define SYSCTRL_INTENCLR_DFLLOOB				(1u << 5)
	/* DFLL Lock Fine Interrupt Enable */
#define SYSCTRL_INTENCLR_DFLLLCKF				(1u << 6)
	/* DFLL Lock Coarse Interrupt Enable */
#define SYSCTRL_INTENCLR_DFLLLCKC				(1u << 7)
	/* DFLL Reference Clock Stopped Interrupt Enable */
#define SYSCTRL_INTENCLR_DFLLRCS				(1u << 8)
	/* BOD33 Ready Interrupt Enable */
#define SYSCTRL_INTENCLR_BOD33RDY				(1u << 9)
	/* BOD33 Detection Interrupt Enable */
#define SYSCTRL_INTENCLR_BOD33DET				(1u << 10)
	/* BOD33 Synchronization Ready Interrupt Enable */
#define SYSCTRL_INTENCLR_B33SRDY				(1u << 11)
	/* DPLL Lock Rise Interrupt Enable */
#define SYSCTRL_INTENCLR_DPLLLCKR				(1u << 15)
	/* DPLL Lock Fall Interrupt Enable */
#define SYSCTRL_INTENCLR_DPLLLCKF				(1u << 16)
	/* DPLL Lock Timeout Interrupt Enable */
#define SYSCTRL_INTENCLR_DPLLLTO				(1u << 17)

	/* 0x04: Interrupt Enable Set */
	uint32_t volatile INTENSET;
	/* XOSC Ready Interrupt Enable */
#define SYSCTRL_INTENSET_XOSCRDY				(1u << 0)
	/* XOSC32K Ready Interrupt Enable */
#define SYSCTRL_INTENSET_XOSC32KRDY				(1u << 1)
	/* OSC32K Ready Interrupt Enable */
#define SYSCTRL_INTENSET_OSC32KRDY				(1u << 2)
	/* OSC8M Ready Interrupt Enable */
#define SYSCTRL_INTENSET_OSC8MRDY				(1u << 3)
	/* DFLL Ready Interrupt Enable */
#define SYSCTRL_INTENSET_DFLLRDY				(1u << 4)
	/* DFLL Out Of Bounds Interrupt Enable */
#define SYSCTRL_INTENSET_DFLLOOB				(1u << 5)
	/* DFLL Lock Fine Interrupt Enable */
#define SYSCTRL_INTENSET_DFLLLCKF				(1u << 6)
	/* DFLL Lock Coarse Interrupt Enable */
#define SYSCTRL_INTENSET_DFLLLCKC				(1u << 7)
	/* DFLL Reference Clock Stopped Interrupt Enable */
#define SYSCTRL_INTENSET_DFLLRCS				(1u << 8)
	/* BOD33 Ready Interrupt Enable */
#define SYSCTRL_INTENSET_BOD33RDY				(1u << 9)
	/* BOD33 Detection Interrupt Enable */
#define SYSCTRL_INTENSET_BOD33DET				(1u << 10)
	/* BOD33 Synchronization Ready Interrupt Enable */
#define SYSCTRL_INTENSET_B33SRDY				(1u << 11)
	/* DPLL Lock Rise Interrupt Enable */
#define SYSCTRL_INTENSET_DPLLLCKR				(1u << 15)
	/* DPLL Lock Fall Interrupt Enable */
#define SYSCTRL_INTENSET_DPLLLCKF				(1u << 16)
	/* DPLL Lock Timeout Interrupt Enable */
#define SYSCTRL_INTENSET_DPLLLTO				(1u << 17)

	/* 0x08: Interrupt Flag Status and Clear */
	uint32_t volatile INTFLAG;
	/* XOSC Ready */
#define SYSCTRL_INTFLAG_XOSCRDY					(1u << 0)
	/* XOSC32K Ready */
#define SYSCTRL_INTFLAG_XOSC32KRDY				(1u << 1)
	/* OSC32K Ready */
#define SYSCTRL_INTFLAG_OSC32KRDY				(1u << 2)
	/* OSC8M Ready */
#define SYSCTRL_INTFLAG_OSC8MRDY				(1u << 3)
	/* DFLL Ready */
#define SYSCTRL_INTFLAG_DFLLRDY					(1u << 4)
	/* DFLL Out Of Bounds */
#define SYSCTRL_INTFLAG_DFLLOOB					(1u << 5)
	/* DFLL Lock Fine */
#define SYSCTRL_INTFLAG_DFLLLCKF				(1u << 6)
	/* DFLL Lock Coarse */
#define SYSCTRL_INTFLAG_DFLLLCKC				(1u << 7)
	/* DFLL Reference Clock Stopped */
#define SYSCTRL_INTFLAG_DFLLRCS					(1u << 8)
	/* BOD33 Ready */
#define SYSCTRL_INTFLAG_BOD33RDY				(1u << 9)
	/* BOD33 Detection */
#define SYSCTRL_INTFLAG_BOD33DET				(1u << 10)
	/* BOD33 Synchronization Ready */
#define SYSCTRL_INTFLAG_B33SRDY					(1u << 11)
	/* DPLL Lock Rise */
#define SYSCTRL_INTFLAG_DPLLLCKR				(1u << 15)
	/* DPLL Lock Fall */
#define SYSCTRL_INTFLAG_DPLLLCKF				(1u << 16)
	/* DPLL Lock Timeout */
#define SYSCTRL_INTFLAG_DPLLLTO					(1u << 17)

	/* 0x0C: Power and Clocks Status */
	uint32_t volatile const PCLKSR;
	/* XOSC Ready */
#define SYSCTRL_PCLKSR_XOSCRDY					(1u << 0)
	/* XOSC32K Ready */
#define SYSCTRL_PCLKSR_XOSC32KRDY				(1u << 1)
	/* OSC32K Ready */
#define SYSCTRL_PCLKSR_OSC32KRDY				(1u << 2)
	/* OSC8M Ready */
#define SYSCTRL_PCLKSR_OSC8MRDY					(1u << 3)
	/* DFLL Ready */
#define SYSCTRL_PCLKSR_DFLLRDY					(1u << 4)
	/* DFLL Out Of Bounds */
#define SYSCTRL_PCLKSR_DFLLOOB					(1u << 5)
	/* DFLL Lock Fine */
#define SYSCTRL_PCLKSR_DFLLLCKF					(1u << 6)
	/* DFLL Lock Coarse */
#define SYSCTRL_PCLKSR_DFLLLCKC					(1u << 7)
	/* DFLL Reference Clock Stopped */
#define SYSCTRL_PCLKSR_DFLLRCS					(1u << 8)
	/* BOD33 Ready */
#define SYSCTRL_PCLKSR_BOD33RDY					(1u << 9)
	/* BOD33 Detection */
#define SYSCTRL_PCLKSR_BOD33DET					(1u << 10)
	/* BOD33 Synchronization Ready */
#define SYSCTRL_PCLKSR_B33SRDY					(1u << 11)
	/* DPLL Lock Rise */
#define SYSCTRL_PCLKSR_DPLLLCKR					(1u << 15)
	/* DPLL Lock Fall */
#define SYSCTRL_PCLKSR_DPLLLCKF					(1u << 16)
	/* DPLL Lock Timeout */
#define SYSCTRL_PCLKSR_DPLLLTO					(1u << 17)

	/* 0x10: External Multipurpose Crystal Oscillator (XOSC) Control */
	uint16_t volatile XOSC;
	/* Oscillator Enable */
#define SYSCTRL_XOSC_ENABLE					(1u << 1)
	/* Crystal Oscillator Enable */
#define SYSCTRL_XOSC_XTALEN					(1u << 2)
	/* Run in Standby */
#define SYSCTRL_XOSC_RUNSTDBY					(1u << 6)
	/* On Demand Control */
#define SYSCTRL_XOSC_ONDEMAND					(1u << 7)
	/* Oscillator Gain */
#define SYSCTRL_XOSC_GAIN_Msk					(0x7u << 8)
#define SYSCTRL_XOSC_GAIN_Pos					8
#define SYSCTRL_XOSC_GAIN_0					(0x0u << 8)
#define SYSCTRL_XOSC_GAIN_1					(0x1u << 8)
#define SYSCTRL_XOSC_GAIN_2					(0x2u << 8)
#define SYSCTRL_XOSC_GAIN_3					(0x3u << 8)
#define SYSCTRL_XOSC_GAIN_4					(0x4u << 8)
	/* Automatic Amplitude Gain Control */
#define SYSCTRL_XOSC_AMPGC					(1u << 11)
	/* Start-Up Time */
#define SYSCTRL_XOSC_STARTUP_Msk				(0xFu << 12)
#define SYSCTRL_XOSC_STARTUP_Pos				12

	/* 0x12 */
	uint8_t RESERVED0[0x14u-0x12u];

	/* 0x14: 32kHz External Crystal Oscillator (XOSC32K) Control */
	uint16_t volatile XOSC32K;
	/* Oscillator Enable */
#define SYSCTRL_XOSC32K_ENABLE					(1u << 1)
	/* Crystal Oscillator Enable */
#define SYSCTRL_XOSC32K_XTALEN					(1u << 2)
	/* 32kHz Output Enable */
#define SYSCTRL_XOSC32K_EN32K					(1u << 3)
	/* 1kHz Output Enable */
#define SYSCTRL_XOSC32K_EN1K					(1u << 4)
	/* Automatic Amplitude Control Enable */
#define SYSCTRL_XOSC32K_AAMPEN					(1u << 5)
	/* Run in Standby */
#define SYSCTRL_XOSC32K_RUNSTDBY				(1u << 6)
	/* On Demand Control */
#define SYSCTRL_XOSC32K_ONDEMAND				(1u << 7)
	/* Oscillator Start-Up Time */
#define SYSCTRL_XOSC32K_STARTUP_Msk				(0x7u << 8)
#define SYSCTRL_XOSC32K_STARTUP_Pos				8
	/* Write Lock */
#define SYSCTRL_XOSC32K_WRTLOCK					(1u << 12)

	/* 0x16 */
	uint8_t RESERVED1[0x18u-0x16u];

	/* 0x18: 32kHz Internal Oscillator (OSC32K) Control */
	uint32_t volatile OSC32K;
	/* Oscillator Enable */
#define SYSCTRL_OSC32K_ENABLE					(1u << 1)
	/* 32kHz Output Enable */
#define SYSCTRL_OSC32K_EN32K					(1u << 2)
	/* 1kHz Output Enable */
#define SYSCTRL_OSC32K_EN1K					(1u << 3)
	/* Run in Standby */
#define SYSCTRL_OSC32K_RUNSTDBY					(1u << 6)
	/* On Demand Control */
#define SYSCTRL_OSC32K_ONDEMAND					(1u << 7)
	/* Oscillator Start-Up Time */
#define SYSCTRL_OSC32K_STARTUP_Msk				(0x7u << 8)
#define SYSCTRL_OSC32K_STARTUP_Pos				8
	/* Write Lock */
#define SYSCTRL_OSC32K_WRTLOCK					(1u << 12)
	/* Oscillator Calibration */
#define SYSCTRL_OSC32K_CALIB_Msk				(0x7Fu << 16)
#define SYSCTRL_OSC32K_CALIB_Pos				16

	/* 0x1C: 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */
	uint8_t volatile OSCULP32K;
	/* Oscillator Calibration */
#define SYSCTRL_OSCULP32K_CALIB_Msk				(0x1Fu << 0)
#define SYSCTRL_OSCULP32K_CALIB_Pos				0
	/* Write Lock */
#define SYSCTRL_OSCULP32K_WRTLOCK				(1u << 7)

	/* 0x1D */
	uint8_t RESERVED2[0x20u-0x1Du];

	/* 0x20: 8MHz Internal Oscillator (OSC8M) Control */
	uint32_t volatile OSC8M;
	/* Oscillator Enable */
#define SYSCTRL_OSC8M_ENABLE					(1u << 1)
	/* Run in Standby */
#define SYSCTRL_OSC8M_RUNSTDBY					(1u << 6)
	/* On Demand Control */
#define SYSCTRL_OSC8M_ONDEMAND					(1u << 7)
	/* Oscillator Prescaler */
#define SYSCTRL_OSC8M_PRESC_Msk					(0x3u << 8)
#define SYSCTRL_OSC8M_PRESC_Pos					8
#define SYSCTRL_OSC8M_PRESC_0					(0x0u << 8)
#define SYSCTRL_OSC8M_PRESC_1					(0x1u << 8)
#define SYSCTRL_OSC8M_PRESC_2					(0x2u << 8)
#define SYSCTRL_OSC8M_PRESC_3					(0x3u << 8)
	/* Oscillator Calibration */
#define SYSCTRL_OSC8M_CALIB_Msk					(0xFFFu << 16)
#define SYSCTRL_OSC8M_CALIB_Pos					16
	/* Oscillator Frequency Range */
#define SYSCTRL_OSC8M_FRANGE_Msk				(0x3u << 30)
#define SYSCTRL_OSC8M_FRANGE_Pos				30
#define SYSCTRL_OSC8M_FRANGE_0					(0x0u << 30)
#define SYSCTRL_OSC8M_FRANGE_1					(0x1u << 30)
#define SYSCTRL_OSC8M_FRANGE_2					(0x2u << 30)
#define SYSCTRL_OSC8M_FRANGE_3					(0x3u << 30)

	/* 0x24: DFLL48M Control */
	uint16_t volatile DFLLCTRL;
	/* DFLL Enable */
#define SYSCTRL_DFLLCTRL_ENABLE					(1u << 1)
	/* Operating Mode Selection */
#define SYSCTRL_DFLLCTRL_MODE					(1u << 2)
	/* Stable DFLL Frequency */
#define SYSCTRL_DFLLCTRL_STABLE					(1u << 3)
	/* Lose Lock After Wake */
#define SYSCTRL_DFLLCTRL_LLAW					(1u << 4)
	/* USB Clock Recovery Mode */
#define SYSCTRL_DFLLCTRL_USBCRM					(1u << 5)
	/* Run in Standby */
#define SYSCTRL_DFLLCTRL_RUNSTDBY				(1u << 6)
	/* On Demand Control */
#define SYSCTRL_DFLLCTRL_ONDEMAND				(1u << 7)
	/* Chill Cycle Disable */
#define SYSCTRL_DFLLCTRL_CCDIS					(1u << 8)
	/* Quick Lock Disable */
#define SYSCTRL_DFLLCTRL_QLDIS					(1u << 9)
	/* Bypass Coarse Lock */
#define SYSCTRL_DFLLCTRL_BPLCKC					(1u << 10)
	/* Wait Lock */
#define SYSCTRL_DFLLCTRL_WAITLOCK				(1u << 11)

	/* 0x26 */
	uint8_t RESERVED3[0x28u-0x26u];

	/* 0x28: DFLL48M Value */
	uint32_t volatile DFLLVAL;
	/* Fine Value */
#define SYSCTRL_DFLLVAL_FINE_Msk				(0x3FFu << 0)
#define SYSCTRL_DFLLVAL_FINE_Pos				0
	/* Coarse Value */
#define SYSCTRL_DFLLVAL_COARSE_Msk				(0x3Fu << 10)
#define SYSCTRL_DFLLVAL_COARSE_Pos				10
	/* Multiplication Ratio Difference */
#define SYSCTRL_DFLLVAL_DIFF_Msk				(0xFFFFu << 16)
#define SYSCTRL_DFLLVAL_DIFF_Pos				16

	/* 0x2C: DFLL48M Multiplier */
	uint32_t volatile DFLLMUL;
	/* DFLL Multiply Factor */
#define SYSCTRL_DFLLMUL_MUL_Msk					(0xFFFFu << 0)
#define SYSCTRL_DFLLMUL_MUL_Pos					0
	/* Fine Maximum Step */
#define SYSCTRL_DFLLMUL_FSTEP_Msk				(0x3FFu << 16)
#define SYSCTRL_DFLLMUL_FSTEP_Pos				16
	/* Coarse Maximum Step */
#define SYSCTRL_DFLLMUL_CSTEP_Msk				(0x3Fu << 26)
#define SYSCTRL_DFLLMUL_CSTEP_Pos				26

	/* 0x30: DFLL48M Synchronization */
	uint8_t volatile DFLLSYNC;
	/* Read Request */
#define SYSCTRL_DFLLSYNC_READREQ				(1u << 7)

	/* 0x31 */
	uint8_t RESERVED4[0x34u-0x31u];

	/* 0x34: 3.3V Brown-Out Detector (BOD33) Control */
	uint32_t volatile BOD33;
	/* Enable */
#define SYSCTRL_BOD33_ENABLE					(1u << 1)
	/* Hysteresis */
#define SYSCTRL_BOD33_HYST					(1u << 2)
	/* BOD33 Action */
#define SYSCTRL_BOD33_ACTION_Msk				(0x3u << 3)
#define SYSCTRL_BOD33_ACTION_Pos				3
#define SYSCTRL_BOD33_ACTION_NONE				(0x0u << 3)
#define SYSCTRL_BOD33_ACTION_RESET				(0x1u << 3)
#define SYSCTRL_BOD33_ACTION_INTERRUPT				(0x2u << 3)
	/* Run in Standby */
#define SYSCTRL_BOD33_RUNSTDBY					(1u << 6)
	/* Operation Mode */
#define SYSCTRL_BOD33_MODE					(1u << 8)
	/* Clock Enable */
#define SYSCTRL_BOD33_CEN					(1u << 9)
	/* Prescaler Select */
#define SYSCTRL_BOD33_PSEL_Msk					(0xFu << 12)
#define SYSCTRL_BOD33_PSEL_Pos					12
#define SYSCTRL_BOD33_PSEL_DIV2					(0x0u << 12)
#define SYSCTRL_BOD33_PSEL_DIV4					(0x1u << 12)
#define SYSCTRL_BOD33_PSEL_DIV8					(0x2u << 12)
#define SYSCTRL_BOD33_PSEL_DIV16				(0x3u << 12)
#define SYSCTRL_BOD33_PSEL_DIV32				(0x4u << 12)
#define SYSCTRL_BOD33_PSEL_DIV64				(0x5u << 12)
#define SYSCTRL_BOD33_PSEL_DIV128				(0x6u << 12)
#define SYSCTRL_BOD33_PSEL_DIV256				(0x7u << 12)
#define SYSCTRL_BOD33_PSEL_DIV512				(0x8u << 12)
#define SYSCTRL_BOD33_PSEL_DIV1K				(0x9u << 12)
#define SYSCTRL_BOD33_PSEL_DIV2K				(0xAu << 12)
#define SYSCTRL_BOD33_PSEL_DIV4K				(0xBu << 12)
#define SYSCTRL_BOD33_PSEL_DIV8K				(0xCu << 12)
#define SYSCTRL_BOD33_PSEL_DIV16K				(0xDu << 12)
#define SYSCTRL_BOD33_PSEL_DIV32K				(0xEu << 12)
#define SYSCTRL_BOD33_PSEL_DIV64K				(0xFu << 12)
	/* BOD33 Threshold Level */
#define SYSCTRL_BOD33_LEVEL_Msk					(0x3Fu << 16)
#define SYSCTRL_BOD33_LEVEL_Pos					16

	/* 0x38 */
	uint8_t RESERVED5[0x40u-0x38u];

	/* 0x40: Voltage References System (VREF) Control */
	uint32_t volatile VREF;
	/* Temperature Sensor Enable */
#define SYSCTRL_VREF_TSEN					(1u << 1)
	/* Bandgap Output Enable */
#define SYSCTRL_VREF_BGOUTEN					(1u << 2)
	/* Bandgap Voltage Generator Calibration */
#define SYSCTRL_VREF_CALIB_Msk					(0x7FFu << 16)
#define SYSCTRL_VREF_CALIB_Pos					16

	/* 0x44: DPLL Control A */
	uint8_t volatile DPLLCTRLA;
	/* DPLL Enable */
#define SYSCTRL_DPLLCTRLA_ENABLE				(1u << 1)
	/* Run in Standby */
#define SYSCTRL_DPLLCTRLA_RUNSTDBY				(1u << 6)
	/* On Demand Clock Activation */
#define SYSCTRL_DPLLCTRLA_ONDEMAND				(1u << 7)

	/* 0x45 */
	uint8_t RESERVED6[0x48u-0x45u];

	/* 0x48: DPLL Ratio Control */
	uint32_t volatile DPLLRATIO;
	/* Loop Divider Ratio */
#define SYSCTRL_DPLLRATIO_LDR_Msk				(0xFFFu << 0)
#define SYSCTRL_DPLLRATIO_LDR_Pos				0
	/* Loop Divider Ratio Fractional Part */
#define SYSCTRL_DPLLRATIO_LDRFRAC_Msk				(0xFu << 16)
#define SYSCTRL_DPLLRATIO_LDRFRAC_Pos				16

	/* 0x4C: DPLL Control B */
	uint32_t volatile DPLLCTRLB;
	/* Proportional Integral Filter Selection */
#define SYSCTRL_DPLLCTRLB_FILTER_Msk				(0x3u << 0)
#define SYSCTRL_DPLLCTRLB_FILTER_Pos				0
#define SYSCTRL_DPLLCTRLB_FILTER_DEFAULT			(0x0u << 0)
#define SYSCTRL_DPLLCTRLB_FILTER_LBFILT				(0x1u << 0)
#define SYSCTRL_DPLLCTRLB_FILTER_HBFILT				(0x2u << 0)
#define SYSCTRL_DPLLCTRLB_FILTER_HDFILT				(0x3u << 0)
	/* Low-Power Enable */
#define SYSCTRL_DPLLCTRLB_LPEN					(1u << 2)
	/* Wake Up Fast */
#define SYSCTRL_DPLLCTRLB_WUF					(1u << 3)
	/* Reference Clock Selection */
#define SYSCTRL_DPLLCTRLB_REFCLK_Msk				(0x3u << 4)
#define SYSCTRL_DPLLCTRLB_REFCLK_Pos				4
#define SYSCTRL_DPLLCTRLB_REFCLK_REF0				(0x0u << 4)
#define SYSCTRL_DPLLCTRLB_REFCLK_REF1				(0x1u << 4)
#define SYSCTRL_DPLLCTRLB_REFCLK_GCLK				(0x2u << 4)
	/* Lock Time */
#define SYSCTRL_DPLLCTRLB_LTIME_Msk				(0x7u << 8)
#define SYSCTRL_DPLLCTRLB_LTIME_Pos				8
#define SYSCTRL_DPLLCTRLB_LTIME_NONE				(0x0u << 8)
#define SYSCTRL_DPLLCTRLB_LTIME_8MS				(0x4u << 8)
#define SYSCTRL_DPLLCTRLB_LTIME_9MS				(0x5u << 8)
#define SYSCTRL_DPLLCTRLB_LTIME_10MS				(0x6u << 8)
#define SYSCTRL_DPLLCTRLB_LTIME_11MS				(0x7u << 8)
	/* Lock Bypass */
#define SYSCTRL_DPLLCTRLB_LBYPASS				(1u << 12)
	/* Clock Divider */
#define SYSCTRL_DPLLCTRLB_DIV_Msk				(0x7FFu << 16)
#define SYSCTRL_DPLLCTRLB_DIV_Pos				16

	/* 0x50: DPLL Status */
	uint8_t volatile const DPLLSTATUS;
	/* DPLL Lock Status */
#define SYSCTRL_DPLLSTATUS_LOCK					(1u << 0)
	/* Output Clock Ready */
#define SYSCTRL_DPLLSTATUS_CLKRDY				(1u << 1)
	/* DPLL Enable */
#define SYSCTRL_DPLLSTATUS_ENABLE				(1u << 2)
	/* Divider Enable */
#define SYSCTRL_DPLLSTATUS_DIV					(1u << 3)

};


#define TC1_COUNT8 ((struct tc_count8 *)TC1_BASE)
#define TC2_COUNT8 ((struct tc_count8 *)TC1_BASE)

struct tc_count8 {

	/* 0x00: Control A */
	uint16_t volatile CTRLA;
	/* Software Reset */
#define TC_COUNT8_CTRLA_SWRST					(1u << 0)
	/* Enable */
#define TC_COUNT8_CTRLA_ENABLE					(1u << 1)
	/* TC Mode */
#define TC_COUNT8_CTRLA_MODE_Msk				(0x3u << 2)
#define TC_COUNT8_CTRLA_MODE_Pos				2
#define TC_COUNT8_CTRLA_MODE_COUNT8				(0x1u << 2)
	/* Waveform Generation Operation */
#define TC_COUNT8_CTRLA_WAVEGEN_Msk				(0x3u << 5)
#define TC_COUNT8_CTRLA_WAVEGEN_Pos				5
#define TC_COUNT8_CTRLA_WAVEGEN_NFRQ				(0x0u << 5)
#define TC_COUNT8_CTRLA_WAVEGEN_MFRQ				(0x1u << 5)
#define TC_COUNT8_CTRLA_WAVEGEN_NPWM				(0x2u << 5)
#define TC_COUNT8_CTRLA_WAVEGEN_MPWM				(0x3u << 5)
	/* Prescaler */
#define TC_COUNT8_CTRLA_PRESCALER_Msk				(0x7u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_Pos				8
#define TC_COUNT8_CTRLA_PRESCALER_DIV1				(0x0u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_DIV2				(0x1u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_DIV4				(0x2u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_DIV8				(0x3u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_DIV16				(0x4u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_DIV64				(0x5u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_DIV256			(0x6u << 8)
#define TC_COUNT8_CTRLA_PRESCALER_DIV1024			(0x7u << 8)
	/* Run in Standby */
#define TC_COUNT8_CTRLA_RUNSTDBY				(1u << 11)
	/* Prescaler and Counter Synchronization */
#define TC_COUNT8_CTRLA_PRESCSYNC_Msk				(0x3u << 12)
#define TC_COUNT8_CTRLA_PRESCSYNC_Pos				12
#define TC_COUNT8_CTRLA_PRESCSYNC_GCLK				(0x0u << 12)
#define TC_COUNT8_CTRLA_PRESCSYNC_PRESC				(0x1u << 12)
#define TC_COUNT8_CTRLA_PRESCSYNC_RESYNC			(0x2u << 12)

	/* 0x02: Read Request */
	uint16_t volatile READREQ;
	/* Address */
#define TC_COUNT8_READREQ_ADDR_Msk				(0x1Fu << 0)
#define TC_COUNT8_READREQ_ADDR_Pos				0
	/* Read Continuously */
#define TC_COUNT8_READREQ_RCONT					(1u << 14)
	/* Read Request */
#define TC_COUNT8_READREQ_RREQ					(1u << 15)

	/* 0x04: Control B Clear */
	uint8_t volatile CTRLBCLR;
	/* Counter Direction */
#define TC_COUNT8_CTRLBCLR_DIR					(1u << 0)
	/* One-Shot */
#define TC_COUNT8_CTRLBCLR_ONESHOT				(1u << 2)
	/* Command */
#define TC_COUNT8_CTRLBCLR_CMD_Msk				(0x3u << 6)
#define TC_COUNT8_CTRLBCLR_CMD_Pos				6
#define TC_COUNT8_CTRLBCLR_CMD_NONE				(0x0u << 6)
#define TC_COUNT8_CTRLBCLR_CMD_RETRIGGER			(0x1u << 6)
#define TC_COUNT8_CTRLBCLR_CMD_STOP				(0x2u << 6)

	/* 0x05: Control B Set */
	uint8_t volatile CTRLBSET;
	/* Counter Direction */
#define TC_COUNT8_CTRLBSET_DIR					(1u << 0)
	/* One-Shot */
#define TC_COUNT8_CTRLBSET_ONESHOT				(1u << 2)
	/* Command */
#define TC_COUNT8_CTRLBSET_CMD_Msk				(0x3u << 6)
#define TC_COUNT8_CTRLBSET_CMD_Pos				6
#define TC_COUNT8_CTRLBSET_CMD_NONE				(0x0u << 6)
#define TC_COUNT8_CTRLBSET_CMD_RETRIGGER			(0x1u << 6)
#define TC_COUNT8_CTRLBSET_CMD_STOP				(0x2u << 6)

	/* 0x06: Control C */
	uint8_t volatile CTRLC;
	/* Output Waveform 0 Invert Enable */
#define TC_COUNT8_CTRLC_INVEN0					(1u << 0)
	/* Output Waveform 1 Invert Enable */
#define TC_COUNT8_CTRLC_INVEN1					(1u << 1)
	/* Capture Channel 0 Enable */
#define TC_COUNT8_CTRLC_CPTEN0					(1u << 4)
	/* Capture Channel 1 Enable */
#define TC_COUNT8_CTRLC_CPTEN1					(1u << 5)

	/* 0x07 */
	uint8_t RESERVED0[0x08u-0x07u];

	/* 0x08: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Run Mode */
#define TC_COUNT8_DBGCTRL_DBGRUN				(1u << 0)

	/* 0x09 */
	uint8_t RESERVED1[0x0Au-0x09u];

	/* 0x0A: Event Control */
	uint16_t volatile EVCTRL;
	/* Event Action */
#define TC_COUNT8_EVCTRL_EVACT_Msk				(0x7u << 0)
#define TC_COUNT8_EVCTRL_EVACT_Pos				0
#define TC_COUNT8_EVCTRL_EVACT_OFF				(0x0u << 0)
#define TC_COUNT8_EVCTRL_EVACT_RETRIGGER			(0x1u << 0)
#define TC_COUNT8_EVCTRL_EVACT_COUNT				(0x2u << 0)
#define TC_COUNT8_EVCTRL_EVACT_START				(0x3u << 0)
#define TC_COUNT8_EVCTRL_EVACT_PPW				(0x5u << 0)
#define TC_COUNT8_EVCTRL_EVACT_PWP				(0x6u << 0)
	/* TC Inverted Event Input */
#define TC_COUNT8_EVCTRL_TCINV					(1u << 4)
	/* TC Event Input */
#define TC_COUNT8_EVCTRL_TCEI					(1u << 5)
	/* Overflow/Underflow Event Output Enable */
#define TC_COUNT8_EVCTRL_OVFEO					(1u << 8)
	/* Match or Capture Channel 0 Event Output Enable */
#define TC_COUNT8_EVCTRL_MCEO0					(1u << 12)
	/* Match or Capture Channel 1 Event Output Enable */
#define TC_COUNT8_EVCTRL_MCEO1					(1u << 13)

	/* 0x0C: Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Overflow Interrupt Enable */
#define TC_COUNT8_INTENCLR_OVF					(1u << 0)
	/* Error Interrupt Enable */
#define TC_COUNT8_INTENCLR_ERR					(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define TC_COUNT8_INTENCLR_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 Interrupt Enable */
#define TC_COUNT8_INTENCLR_MC0					(1u << 4)
	/* Match or Capture Channel 1 Interrupt Enable */
#define TC_COUNT8_INTENCLR_MC1					(1u << 5)

	/* 0x0D: Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Overflow Interrupt Enable */
#define TC_COUNT8_INTENSET_OVF					(1u << 0)
	/* Error Interrupt Enable */
#define TC_COUNT8_INTENSET_ERR					(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define TC_COUNT8_INTENSET_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 Interrupt Enable */
#define TC_COUNT8_INTENSET_MC0					(1u << 4)
	/* Match or Capture Channel 1 Interrupt Enable */
#define TC_COUNT8_INTENSET_MC1					(1u << 5)

	/* 0x0E: Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Overflow */
#define TC_COUNT8_INTFLAG_OVF					(1u << 0)
	/* Error */
#define TC_COUNT8_INTFLAG_ERR					(1u << 1)
	/* Synchronization Ready */
#define TC_COUNT8_INTFLAG_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 */
#define TC_COUNT8_INTFLAG_MC0					(1u << 4)
	/* Match or Capture Channel 1 */
#define TC_COUNT8_INTFLAG_MC1					(1u << 5)

	/* 0x0F: Status */
	uint8_t volatile const STATUS;
	/* Stop */
#define TC_COUNT8_STATUS_STOP					(1u << 3)
	/* Slave */
#define TC_COUNT8_STATUS_SLAVE					(1u << 4)
	/* Synchronization Busy */
#define TC_COUNT8_STATUS_SYNCBUSY				(1u << 7)

	/* 0x10: COUNT8 Counter Value */
	uint8_t volatile COUNT;
	/* Counter Value */
#define TC_COUNT8_COUNT_COUNT_Msk				(0xFFu << 0)
#define TC_COUNT8_COUNT_COUNT_Pos				0

	/* 0x11 */
	uint8_t RESERVED2[0x14u-0x11u];

	/* 0x14: COUNT8 Period Value */
	uint8_t volatile PER;
	/* Period Value */
#define TC_COUNT8_PER_PER_Msk					(0xFFu << 0)
#define TC_COUNT8_PER_PER_Pos					0

	/* 0x15 */
	uint8_t RESERVED3[0x18u-0x15u];

	/* 0x18: COUNT8 Compare/Capture */
	uint8_t volatile CC[4];
	/* Compare/Capture Value */
#define TC_COUNT8_CC_CC_Msk					(0xFFu << 0)
#define TC_COUNT8_CC_CC_Pos					0

};


#define TC1_COUNT16 ((struct tc_count16 *)TC1_BASE)
#define TC2_COUNT16 ((struct tc_count16 *)TC2_BASE)

struct tc_count16 {

	/* 0x00: Control A */
	uint16_t volatile CTRLA;
	/* Software Reset */
#define TC_COUNT16_CTRLA_SWRST					(1u << 0)
	/* Enable */
#define TC_COUNT16_CTRLA_ENABLE					(1u << 1)
	/* TC Mode */
#define TC_COUNT16_CTRLA_MODE_Msk				(0x3u << 2)
#define TC_COUNT16_CTRLA_MODE_Pos				2
#define TC_COUNT16_CTRLA_MODE_COUNT16				(0x0u << 2)
	/* Waveform Generation Operation */
#define TC_COUNT16_CTRLA_WAVEGEN_Msk				(0x3u << 5)
#define TC_COUNT16_CTRLA_WAVEGEN_Pos				5
#define TC_COUNT16_CTRLA_WAVEGEN_NFRQ				(0x0u << 5)
#define TC_COUNT16_CTRLA_WAVEGEN_MFRQ				(0x1u << 5)
#define TC_COUNT16_CTRLA_WAVEGEN_NPWM				(0x2u << 5)
#define TC_COUNT16_CTRLA_WAVEGEN_MPWM				(0x3u << 5)
	/* Prescaler */
#define TC_COUNT16_CTRLA_PRESCALER_Msk				(0x7u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_Pos				8
#define TC_COUNT16_CTRLA_PRESCALER_DIV1				(0x0u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_DIV2				(0x1u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_DIV4				(0x2u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_DIV8				(0x3u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_DIV16			(0x4u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_DIV64			(0x5u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_DIV256			(0x6u << 8)
#define TC_COUNT16_CTRLA_PRESCALER_DIV1024			(0x7u << 8)
	/* Run in Standby */
#define TC_COUNT16_CTRLA_RUNSTDBY				(1u << 11)
	/* Prescaler and Counter Synchronization */
#define TC_COUNT16_CTRLA_PRESCSYNC_Msk				(0x3u << 12)
#define TC_COUNT16_CTRLA_PRESCSYNC_Pos				12
#define TC_COUNT16_CTRLA_PRESCSYNC_GCLK				(0x0u << 12)
#define TC_COUNT16_CTRLA_PRESCSYNC_PRESC			(0x1u << 12)
#define TC_COUNT16_CTRLA_PRESCSYNC_RESYNC			(0x2u << 12)

	/* 0x02: Read Request */
	uint16_t volatile READREQ;
	/* Address */
#define TC_COUNT16_READREQ_ADDR_Msk				(0x1Fu << 0)
#define TC_COUNT16_READREQ_ADDR_Pos				0
	/* Read Continuously */
#define TC_COUNT16_READREQ_RCONT				(1u << 14)
	/* Read Request */
#define TC_COUNT16_READREQ_RREQ					(1u << 15)

	/* 0x04: Control B Clear */
	uint8_t volatile CTRLBCLR;
	/* Counter Direction */
#define TC_COUNT16_CTRLBCLR_DIR					(1u << 0)
	/* One-Shot */
#define TC_COUNT16_CTRLBCLR_ONESHOT				(1u << 2)
	/* Command */
#define TC_COUNT16_CTRLBCLR_CMD_Msk				(0x3u << 6)
#define TC_COUNT16_CTRLBCLR_CMD_Pos				6
#define TC_COUNT16_CTRLBCLR_CMD_NONE				(0x0u << 6)
#define TC_COUNT16_CTRLBCLR_CMD_RETRIGGER			(0x1u << 6)
#define TC_COUNT16_CTRLBCLR_CMD_STOP				(0x2u << 6)

	/* 0x05: Control B Set */
	uint8_t volatile CTRLBSET;
	/* Counter Direction */
#define TC_COUNT16_CTRLBSET_DIR					(1u << 0)
	/* One-Shot */
#define TC_COUNT16_CTRLBSET_ONESHOT				(1u << 2)
	/* Command */
#define TC_COUNT16_CTRLBSET_CMD_Msk				(0x3u << 6)
#define TC_COUNT16_CTRLBSET_CMD_Pos				6
#define TC_COUNT16_CTRLBSET_CMD_NONE				(0x0u << 6)
#define TC_COUNT16_CTRLBSET_CMD_RETRIGGER			(0x1u << 6)
#define TC_COUNT16_CTRLBSET_CMD_STOP				(0x2u << 6)

	/* 0x06: Control C */
	uint8_t volatile CTRLC;
	/* Output Waveform 0 Invert Enable */
#define TC_COUNT16_CTRLC_INVEN0					(1u << 0)
	/* Output Waveform 1 Invert Enable */
#define TC_COUNT16_CTRLC_INVEN1					(1u << 1)
	/* Capture Channel 0 Enable */
#define TC_COUNT16_CTRLC_CPTEN0					(1u << 4)
	/* Capture Channel 1 Enable */
#define TC_COUNT16_CTRLC_CPTEN1					(1u << 5)

	/* 0x07 */
	uint8_t RESERVED4[0x08u-0x07u];

	/* 0x08: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Run Mode */
#define TC_COUNT16_DBGCTRL_DBGRUN				(1u << 0)

	/* 0x09 */
	uint8_t RESERVED5[0x0Au-0x09u];

	/* 0x0A: Event Control */
	uint16_t volatile EVCTRL;
	/* Event Action */
#define TC_COUNT16_EVCTRL_EVACT_Msk				(0x7u << 0)
#define TC_COUNT16_EVCTRL_EVACT_Pos				0
#define TC_COUNT16_EVCTRL_EVACT_OFF				(0x0u << 0)
#define TC_COUNT16_EVCTRL_EVACT_RETRIGGER			(0x1u << 0)
#define TC_COUNT16_EVCTRL_EVACT_COUNT				(0x2u << 0)
#define TC_COUNT16_EVCTRL_EVACT_START				(0x3u << 0)
#define TC_COUNT16_EVCTRL_EVACT_PPW				(0x5u << 0)
#define TC_COUNT16_EVCTRL_EVACT_PWP				(0x6u << 0)
	/* TC Inverted Event Input */
#define TC_COUNT16_EVCTRL_TCINV					(1u << 4)
	/* TC Event Input */
#define TC_COUNT16_EVCTRL_TCEI					(1u << 5)
	/* Overflow/Underflow Event Output Enable */
#define TC_COUNT16_EVCTRL_OVFEO					(1u << 8)
	/* Match or Capture Channel 0 Event Output Enable */
#define TC_COUNT16_EVCTRL_MCEO0					(1u << 12)
	/* Match or Capture Channel 1 Event Output Enable */
#define TC_COUNT16_EVCTRL_MCEO1					(1u << 13)

	/* 0x0C: Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Overflow Interrupt Enable */
#define TC_COUNT16_INTENCLR_OVF					(1u << 0)
	/* Error Interrupt Enable */
#define TC_COUNT16_INTENCLR_ERR					(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define TC_COUNT16_INTENCLR_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 Interrupt Enable */
#define TC_COUNT16_INTENCLR_MC0					(1u << 4)
	/* Match or Capture Channel 1 Interrupt Enable */
#define TC_COUNT16_INTENCLR_MC1					(1u << 5)

	/* 0x0D: Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Overflow Interrupt Enable */
#define TC_COUNT16_INTENSET_OVF					(1u << 0)
	/* Error Interrupt Enable */
#define TC_COUNT16_INTENSET_ERR					(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define TC_COUNT16_INTENSET_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 Interrupt Enable */
#define TC_COUNT16_INTENSET_MC0					(1u << 4)
	/* Match or Capture Channel 1 Interrupt Enable */
#define TC_COUNT16_INTENSET_MC1					(1u << 5)

	/* 0x0E: Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Overflow */
#define TC_COUNT16_INTFLAG_OVF					(1u << 0)
	/* Error */
#define TC_COUNT16_INTFLAG_ERR					(1u << 1)
	/* Synchronization Ready */
#define TC_COUNT16_INTFLAG_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 */
#define TC_COUNT16_INTFLAG_MC0					(1u << 4)
	/* Match or Capture Channel 1 */
#define TC_COUNT16_INTFLAG_MC1					(1u << 5)

	/* 0x0F: Status */
	uint8_t volatile const STATUS;
	/* Stop */
#define TC_COUNT16_STATUS_STOP					(1u << 3)
	/* Slave */
#define TC_COUNT16_STATUS_SLAVE					(1u << 4)
	/* Synchronization Busy */
#define TC_COUNT16_STATUS_SYNCBUSY				(1u << 7)

	/* 0x10: COUNT16 Counter Value */
	uint16_t volatile COUNT;
	/* Count Value */
#define TC_COUNT16_COUNT_COUNT_Msk				(0xFFFFu << 0)
#define TC_COUNT16_COUNT_COUNT_Pos				0

	/* 0x12 */
	uint8_t RESERVED6[0x18u-0x12u];

	/* 0x18: COUNT16 Compare/Capture */
	uint16_t volatile CC[4];
	/* Compare/Capture Value */
#define TC_COUNT16_CC_CC_Msk					(0xFFFFu << 0)
#define TC_COUNT16_CC_CC_Pos					0

};


#define TC1_COUNT32 ((struct tc_count32 *)TC1_BASE)
#define TC2_COUNT32 ((struct tc_count32 *)TC2_BASE)

struct tc_count32 {

	/* 0x00: Control A */
	uint16_t volatile CTRLA;
	/* Software Reset */
#define TC_COUNT32_CTRLA_SWRST					(1u << 0)
	/* Enable */
#define TC_COUNT32_CTRLA_ENABLE					(1u << 1)
	/* TC Mode */
#define TC_COUNT32_CTRLA_MODE_Msk				(0x3u << 2)
#define TC_COUNT32_CTRLA_MODE_Pos				2
#define TC_COUNT32_CTRLA_MODE_COUNT32				(0x2u << 2)
	/* Waveform Generation Operation */
#define TC_COUNT32_CTRLA_WAVEGEN_Msk				(0x3u << 5)
#define TC_COUNT32_CTRLA_WAVEGEN_Pos				5
#define TC_COUNT32_CTRLA_WAVEGEN_NFRQ				(0x0u << 5)
#define TC_COUNT32_CTRLA_WAVEGEN_MFRQ				(0x1u << 5)
#define TC_COUNT32_CTRLA_WAVEGEN_NPWM				(0x2u << 5)
#define TC_COUNT32_CTRLA_WAVEGEN_MPWM				(0x3u << 5)
	/* Prescaler */
#define TC_COUNT32_CTRLA_PRESCALER_Msk				(0x7u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_Pos				8
#define TC_COUNT32_CTRLA_PRESCALER_DIV1				(0x0u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_DIV2				(0x1u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_DIV4				(0x2u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_DIV8				(0x3u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_DIV16			(0x4u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_DIV64			(0x5u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_DIV256			(0x6u << 8)
#define TC_COUNT32_CTRLA_PRESCALER_DIV1024			(0x7u << 8)
	/* Run in Standby */
#define TC_COUNT32_CTRLA_RUNSTDBY				(1u << 11)
	/* Prescaler and Counter Synchronization */
#define TC_COUNT32_CTRLA_PRESCSYNC_Msk				(0x3u << 12)
#define TC_COUNT32_CTRLA_PRESCSYNC_Pos				12
#define TC_COUNT32_CTRLA_PRESCSYNC_GCLK				(0x0u << 12)
#define TC_COUNT32_CTRLA_PRESCSYNC_PRESC			(0x1u << 12)
#define TC_COUNT32_CTRLA_PRESCSYNC_RESYNC			(0x2u << 12)

	/* 0x02: Read Request */
	uint16_t volatile READREQ;
	/* Address */
#define TC_COUNT32_READREQ_ADDR_Msk				(0x1Fu << 0)
#define TC_COUNT32_READREQ_ADDR_Pos				0
	/* Read Continuously */
#define TC_COUNT32_READREQ_RCONT				(1u << 14)
	/* Read Request */
#define TC_COUNT32_READREQ_RREQ					(1u << 15)

	/* 0x04: Control B Clear */
	uint8_t volatile CTRLBCLR;
	/* Counter Direction */
#define TC_COUNT32_CTRLBCLR_DIR					(1u << 0)
	/* One-Shot */
#define TC_COUNT32_CTRLBCLR_ONESHOT				(1u << 2)
	/* Command */
#define TC_COUNT32_CTRLBCLR_CMD_Msk				(0x3u << 6)
#define TC_COUNT32_CTRLBCLR_CMD_Pos				6
#define TC_COUNT32_CTRLBCLR_CMD_NONE				(0x0u << 6)
#define TC_COUNT32_CTRLBCLR_CMD_RETRIGGER			(0x1u << 6)
#define TC_COUNT32_CTRLBCLR_CMD_STOP				(0x2u << 6)

	/* 0x05: Control B Set */
	uint8_t volatile CTRLBSET;
	/* Counter Direction */
#define TC_COUNT32_CTRLBSET_DIR					(1u << 0)
	/* One-Shot */
#define TC_COUNT32_CTRLBSET_ONESHOT				(1u << 2)
	/* Command */
#define TC_COUNT32_CTRLBSET_CMD_Msk				(0x3u << 6)
#define TC_COUNT32_CTRLBSET_CMD_Pos				6
#define TC_COUNT32_CTRLBSET_CMD_NONE				(0x0u << 6)
#define TC_COUNT32_CTRLBSET_CMD_RETRIGGER			(0x1u << 6)
#define TC_COUNT32_CTRLBSET_CMD_STOP				(0x2u << 6)

	/* 0x06: Control C */
	uint8_t volatile CTRLC;
	/* Output Waveform 0 Invert Enable */
#define TC_COUNT32_CTRLC_INVEN0					(1u << 0)
	/* Output Waveform 1 Invert Enable */
#define TC_COUNT32_CTRLC_INVEN1					(1u << 1)
	/* Capture Channel 0 Enable */
#define TC_COUNT32_CTRLC_CPTEN0					(1u << 4)
	/* Capture Channel 1 Enable */
#define TC_COUNT32_CTRLC_CPTEN1					(1u << 5)

	/* 0x07 */
	uint8_t RESERVED7[0x08u-0x07u];

	/* 0x08: Debug Control */
	uint8_t volatile DBGCTRL;
	/* Debug Run Mode */
#define TC_COUNT32_DBGCTRL_DBGRUN				(1u << 0)

	/* 0x09 */
	uint8_t RESERVED8[0x0Au-0x09u];

	/* 0x0A: Event Control */
	uint16_t volatile EVCTRL;
	/* Event Action */
#define TC_COUNT32_EVCTRL_EVACT_Msk				(0x7u << 0)
#define TC_COUNT32_EVCTRL_EVACT_Pos				0
#define TC_COUNT32_EVCTRL_EVACT_OFF				(0x0u << 0)
#define TC_COUNT32_EVCTRL_EVACT_RETRIGGER			(0x1u << 0)
#define TC_COUNT32_EVCTRL_EVACT_COUNT				(0x2u << 0)
#define TC_COUNT32_EVCTRL_EVACT_START				(0x3u << 0)
#define TC_COUNT32_EVCTRL_EVACT_PPW				(0x5u << 0)
#define TC_COUNT32_EVCTRL_EVACT_PWP				(0x6u << 0)
	/* TC Inverted Event Input */
#define TC_COUNT32_EVCTRL_TCINV					(1u << 4)
	/* TC Event Input */
#define TC_COUNT32_EVCTRL_TCEI					(1u << 5)
	/* Overflow/Underflow Event Output Enable */
#define TC_COUNT32_EVCTRL_OVFEO					(1u << 8)
	/* Match or Capture Channel 0 Event Output Enable */
#define TC_COUNT32_EVCTRL_MCEO0					(1u << 12)
	/* Match or Capture Channel 1 Event Output Enable */
#define TC_COUNT32_EVCTRL_MCEO1					(1u << 13)

	/* 0x0C: Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Overflow Interrupt Enable */
#define TC_COUNT32_INTENCLR_OVF					(1u << 0)
	/* Error Interrupt Enable */
#define TC_COUNT32_INTENCLR_ERR					(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define TC_COUNT32_INTENCLR_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 Interrupt Enable */
#define TC_COUNT32_INTENCLR_MC0					(1u << 4)
	/* Match or Capture Channel 1 Interrupt Enable */
#define TC_COUNT32_INTENCLR_MC1					(1u << 5)

	/* 0x0D: Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Overflow Interrupt Enable */
#define TC_COUNT32_INTENSET_OVF					(1u << 0)
	/* Error Interrupt Enable */
#define TC_COUNT32_INTENSET_ERR					(1u << 1)
	/* Synchronization Ready Interrupt Enable */
#define TC_COUNT32_INTENSET_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 Interrupt Enable */
#define TC_COUNT32_INTENSET_MC0					(1u << 4)
	/* Match or Capture Channel 1 Interrupt Enable */
#define TC_COUNT32_INTENSET_MC1					(1u << 5)

	/* 0x0E: Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Overflow */
#define TC_COUNT32_INTFLAG_OVF					(1u << 0)
	/* Error */
#define TC_COUNT32_INTFLAG_ERR					(1u << 1)
	/* Synchronization Ready */
#define TC_COUNT32_INTFLAG_SYNCRDY				(1u << 3)
	/* Match or Capture Channel 0 */
#define TC_COUNT32_INTFLAG_MC0					(1u << 4)
	/* Match or Capture Channel 1 */
#define TC_COUNT32_INTFLAG_MC1					(1u << 5)

	/* 0x0F: Status */
	uint8_t volatile const STATUS;
	/* Stop */
#define TC_COUNT32_STATUS_STOP					(1u << 3)
	/* Slave */
#define TC_COUNT32_STATUS_SLAVE					(1u << 4)
	/* Synchronization Busy */
#define TC_COUNT32_STATUS_SYNCBUSY				(1u << 7)

	/* 0x10: COUNT32 Counter Value */
	uint32_t volatile COUNT;
	/* Count Value */
#define TC_COUNT32_COUNT_COUNT_Msk				(0xFFFFFFFFu << 0)
#define TC_COUNT32_COUNT_COUNT_Pos				0

	/* 0x14 */
	uint8_t RESERVED9[0x18u-0x14u];

	/* 0x18: COUNT32 Compare/Capture */
	uint32_t volatile CC[4];
	/* Compare/Capture Value */
#define TC_COUNT32_CC_CC_Msk					(0xFFFFFFFFu << 0)
#define TC_COUNT32_CC_CC_Pos					0

};


#define WDT ((struct wdt *)0x40001000)

struct wdt {

	/* 0x00: Control */
	uint8_t volatile CTRL;
	/* Enable */
#define WDT_CTRL_ENABLE						(1u << 1)
	/* Watchdog Timer Window Mode Enable */
#define WDT_CTRL_WEN						(1u << 2)
	/* Always-On */
#define WDT_CTRL_ALWAYSON					(1u << 7)

	/* 0x01: Configuration */
	uint8_t volatile CONFIG;
	/* Time-Out Period */
#define WDT_CONFIG_PER_Msk					(0xFu << 0)
#define WDT_CONFIG_PER_Pos					0
#define WDT_CONFIG_PER_8					(0x0u << 0)
#define WDT_CONFIG_PER_16					(0x1u << 0)
#define WDT_CONFIG_PER_32					(0x2u << 0)
#define WDT_CONFIG_PER_64					(0x3u << 0)
#define WDT_CONFIG_PER_128					(0x4u << 0)
#define WDT_CONFIG_PER_256					(0x5u << 0)
#define WDT_CONFIG_PER_512					(0x6u << 0)
#define WDT_CONFIG_PER_1K					(0x7u << 0)
#define WDT_CONFIG_PER_2K					(0x8u << 0)
#define WDT_CONFIG_PER_4K					(0x9u << 0)
#define WDT_CONFIG_PER_8K					(0xAu << 0)
#define WDT_CONFIG_PER_16K					(0xBu << 0)
	/* Window Mode Time-Out Period */
#define WDT_CONFIG_WINDOW_Msk					(0xFu << 4)
#define WDT_CONFIG_WINDOW_Pos					4
#define WDT_CONFIG_WINDOW_8					(0x0u << 4)
#define WDT_CONFIG_WINDOW_16					(0x1u << 4)
#define WDT_CONFIG_WINDOW_32					(0x2u << 4)
#define WDT_CONFIG_WINDOW_64					(0x3u << 4)
#define WDT_CONFIG_WINDOW_128					(0x4u << 4)
#define WDT_CONFIG_WINDOW_256					(0x5u << 4)
#define WDT_CONFIG_WINDOW_512					(0x6u << 4)
#define WDT_CONFIG_WINDOW_1K					(0x7u << 4)
#define WDT_CONFIG_WINDOW_2K					(0x8u << 4)
#define WDT_CONFIG_WINDOW_4K					(0x9u << 4)
#define WDT_CONFIG_WINDOW_8K					(0xAu << 4)
#define WDT_CONFIG_WINDOW_16K					(0xBu << 4)

	/* 0x02: Early Warning Interrupt Control */
	uint8_t volatile EWCTRL;
	/* Early Warning Interrupt Time Offset */
#define WDT_EWCTRL_EWOFFSET_Msk					(0xFu << 0)
#define WDT_EWCTRL_EWOFFSET_Pos					0
#define WDT_EWCTRL_EWOFFSET_8					(0x0u << 0)
#define WDT_EWCTRL_EWOFFSET_16					(0x1u << 0)
#define WDT_EWCTRL_EWOFFSET_32					(0x2u << 0)
#define WDT_EWCTRL_EWOFFSET_64					(0x3u << 0)
#define WDT_EWCTRL_EWOFFSET_128					(0x4u << 0)
#define WDT_EWCTRL_EWOFFSET_256					(0x5u << 0)
#define WDT_EWCTRL_EWOFFSET_512					(0x6u << 0)
#define WDT_EWCTRL_EWOFFSET_1K					(0x7u << 0)
#define WDT_EWCTRL_EWOFFSET_2K					(0x8u << 0)
#define WDT_EWCTRL_EWOFFSET_4K					(0x9u << 0)
#define WDT_EWCTRL_EWOFFSET_8K					(0xAu << 0)
#define WDT_EWCTRL_EWOFFSET_16K					(0xBu << 0)

	/* 0x03 */
	uint8_t RESERVED0[0x04u-0x03u];

	/* 0x04: Interrupt Enable Clear */
	uint8_t volatile INTENCLR;
	/* Early Warning Interrupt Enable */
#define WDT_INTENCLR_EW						(1u << 0)

	/* 0x05: Interrupt Enable Set */
	uint8_t volatile INTENSET;
	/* Early Warning Interrupt Enable */
#define WDT_INTENSET_EW						(1u << 0)

	/* 0x06: Interrupt Flag Status and Clear */
	uint8_t volatile INTFLAG;
	/* Early Warning */
#define WDT_INTFLAG_EW						(1u << 0)

	/* 0x07: Status */
	uint8_t volatile const STATUS;
	/* Synchronization Busy */
#define WDT_STATUS_SYNCBUSY					(1u << 7)

	/* 0x08: Clear */
	uint8_t volatile CLEAR;
	/* Watchdog Clear */
#define WDT_CLEAR_CLEAR_Msk					(0xFFu << 0)
#define WDT_CLEAR_CLEAR_Pos					0
#define WDT_CLEAR_CLEAR_KEY					(0xA5u << 0)

};


/*** LIBSAMD09 ***/


#define FIELD(reg, fld)		(((reg) & fld##_Msk) >> fld##_Pos)


/*** USART ***/

/* init the usart, to call last before sending data */
void usart_init(struct usart *usart, uint32_t baud_hz, uint8_t txpo, uint8_t rxpo);

/* queue a transmission of `buf` of size `sz` over `usart` TX pin */
void usart_queue_tx(struct usart *usart, uint8_t const *buf, size_t sz);

/* queue a reception to `buf` of size `sz` over `usart` RX pin */
void usart_queue_rx(struct usart *usart, uint8_t *buf, size_t sz);

/* wait for `usart` transmission to complete */
void usart_wait_tx(struct usart *usart);

/* wait for `usart` reception to complete */
void usart_wait_rx(struct usart *usart);

/* interrupt coming from a generic SERCOM interface */
void usart_interrupt(struct usart *usart);


/*** I²C MASTER ***/

/* set `i2c_master` to I²C master mode */
void i2c_master_set_master(struct i2c_master *i2c_master);

/* configure and init `i2c_master` */
void i2c_master_init(struct i2c_master *i2c_master, uint32_t baud_hz, uint8_t pin_clk, uint8_t pin_sda);

/* receive `i2c_master` interrupt from SERCOM0 or SERCOM1 */
void i2c_master_interrupt(struct i2c_master *i2c_master);

/* queue a transmission of `buf` of size `sz` to `addr` over `i2c_master` */
void i2c_master_queue_tx(struct i2c_master *i2c_master, uint8_t addr, uint8_t const *mem, size_t sz);

/* queue a transmission of `buf` of size `sz` to `addr` over `i2c_master` */
void i2c_master_queue_rx(struct i2c_master *i2c_master, uint8_t addr, uint8_t *mem, size_t sz);

/* wait for `i2c_master` to complete transmission or reception */
int i2c_master_wait(struct i2c_master *i2c_master);


/*** SPI MASTER ***/

/* configure and init `i2c_master` */
void spi_master_init(struct spi *spi_master, uint32_t baud_hz, uint8_t pin_sck,
	uint8_t pin_miso, uint8_t pin_mosi, uint8_t pin_ss,
	uint32_t dipo, uint32_t dopo);


/*** CLOCK ***/

/* give the clock-rate for selected clock channel `clkid` */ 
uint32_t clock_get_channel_hz(uint8_t clkid);

/* give the clock-rate for selected clock generator `genid` */ 
uint32_t clock_get_generator_hz(uint8_t genid);

/* init a clock generator `genid`, plugging it a source `srcid` divided by `div` */
void clock_init_generator(uint8_t genid, uint32_t srcid, uint32_t div);

/* output the signal of clock `genid` to an external pin directly */
void clock_enable_generator_output(uint8_t genid);

/* init a clock channel `clkid`, plugging it a clock generator `genid` */
void clock_init(uint8_t clkid, uint8_t genid);


/*** PWM ***/

/* setup a timer/counter of resolution 8 `tc` for use with PWM on `pin` */
void pwm_init(struct tc_count8 *tc, uint32_t ctrla_prescaler);

/* setup `pin` for use as a counter output */
void pwm_init_counter(uint8_t pin);

/* set `tc` duration of time with pin "up" out of UINT8_MAX to `duty_cycle` */
void pwm_set_duty_cycle(struct tc_count8 *tc, uint8_t counter_id, uint8_t duty_cycle);


/*** SYSTICK ***/

/* start a timer counting milliseconds, to be setup after system clock */
void systick_init(void);

/* receive interrupt to update the systick timer */
void systick_interrupt(void);

/* return the runtime in milliseconds */
uint64_t systick_get_runtime_ms(void);

/* busy wait `duration_ms` milliseconds */
void systick_sleep_ms(uint64_t duration_ms);


/*** POWER ***/

static inline void
power_on_sercom(uint8_t id)
{
	PM->APBCMASK |= PM_APBCMASK_SERCOM0 << id;
}

static inline void
power_on_osc8m(void)
{
	SYSCTRL->OSC8M |= SYSCTRL_OSC8M_ENABLE;
}

static inline void
power_on_dfll48m(void)
{
	SYSCTRL->OSC8M |= SYSCTRL_DFLLCTRL_ENABLE;
}


/*** PORT ***/

static inline void
port_set_pmux(uint8_t pin, uint8_t pmux)
{
	if (pin % 2 == 0) {
		/* even */
		PORT->PMUX[pin/2] = (PORT->PMUX[pin/2] & ~0x0F) | (pmux << 0);
	} else {
		/* odd */
		PORT->PMUX[pin/2] = (PORT->PMUX[pin/2] & ~0xF0) | (pmux << 4);
	}
}


/*** SERCOM ***/

static inline uint8_t
sercom_get_id(void *ptr)
{
	if (ptr == SERCOM0) return 0;
	if (ptr == SERCOM1) return 1;
	assert(!"unknown sercom");
	return 0xFF;
}

static inline uint32_t
sercom_get_clock_hz(uint8_t id)
{
	return clock_get_channel_hz(GCLK_CLKCTRL_ID_SERCOM0_CORE + id);
}


/*** TIMER/COUNTER ***/

static inline uint8_t
tc_get_id(void *ptr)
{
	if (ptr == (void *)TC1_BASE) return 1;
	if (ptr == (void *)TC2_BASE) return 2;
	assert(!"unknown timer/counter");
	return 0xFF;
}

#endif
