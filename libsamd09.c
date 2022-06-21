#include "libc.h"
#include "libsamd09.h"


/// INIT ///


extern int main(void);
extern char __data_start, __data_end, __data_load_start;
extern char __bss_start, __bss_end, __stack_top;

void
__reset_handler(void)
{
	volatile char *dst, *src = &__data_load_start;

	for (dst = &__data_start; dst < &__data_end; *dst++ = *src++);
	for (dst = &__bss_start; dst < &__bss_end; *dst++ = 0);
	main();
	for (int volatile i = 0 ;; i++);
}

static inline void
__isr_sercom(struct sercom *sercom)
{
	switch (sercom->CTRLA & SERCOM_CTRLA_MODE_Msk) {
	case SERCOM_CTRLA_MODE_USART_INT_CLK:
		usart_interrupt((struct usart *)sercom);
		break;
	case SERCOM_CTRLA_MODE_I2C_MASTER:
		i2c_master_interrupt((struct i2c_master *)sercom);
		break;
	case SERCOM_CTRLA_MODE_USART_EXT_CLK:
	case SERCOM_CTRLA_MODE_SPI_SLAVE:
	case SERCOM_CTRLA_MODE_SPI_MASTER:
	case SERCOM_CTRLA_MODE_I2C_SLAVE:
		break;
	}
}

static void
__isr_sercom0(void)
{
	__isr_sercom(SERCOM0);
}

static void
__isr_sercom1(void)
{
	__isr_sercom(SERCOM1);
}

static void
__isr_systick(void)
{
	systick_interrupt();
}

/* so that the debugger can immediately see which fault was triggered */
void __null_handler(void)		{ for (int volatile i = 0;; i++); }
void __isr_hard_fault(void)		{ for (int volatile i = 0;; i++); }
void __isr_memory_management(void)	{ for (int volatile i = 0;; i++); }
void __isr_non_maskable_interrupt(void)	{ for (int volatile i = 0;; i++); }
void __isr_bus_fault(void)		{ for (int volatile i = 0;; i++); }
void __isr_usage_fault(void)		{ for (int volatile i = 0;; i++); }
void __isr_secure_fault(void)		{ for (int volatile i = 0;; i++); }

void *__stack_pointer = &__stack_top;	/* 0x00 */

void (*__vectors[])(void) = {
	&__reset_handler,		/* 0x04 -15 ARM Reset */
	&__isr_non_maskable_interrupt,	/* 0x08 -14 ARM NonMaskableInt */
	&__isr_hard_fault,		/* 0x0C -13 ARM HardFault */
	&__isr_memory_management,	/* 0x10 -12 ARM MemoryManagement */
	&__isr_bus_fault,		/* 0x14 -11 ARM BusFault */
	&__isr_usage_fault,		/* 0x18 -10 ARM UsageFault */
	&__isr_secure_fault,		/* 0x1C -9 ARM SecureFault */
	&__null_handler,		/* 0x20 -8 Reserved */
	&__null_handler,		/* 0x24 -7 Reserved */
	&__null_handler,		/* 0x28 -6 Reserved */
	&__null_handler,		/* 0x2C -5 ARM SVCall */
	&__null_handler,		/* 0x30 -4 ARM DebugMonitor */
	&__null_handler,		/* 0x34 -3 Reserved */
	&__null_handler,		/* 0x38 -2 ARM PendSV */
	&__isr_systick,			/* 0x3C -1 ARM SysTick */
	&__null_handler,		/* 0x40 #0 PM */
	&__null_handler,		/* 0x44 #1 SYSCTRL */
	&__null_handler,		/* 0x48 #2 WDT */
	&__null_handler,		/* 0x4C #3 RTC */
	&__null_handler,		/* 0x50 #4 EIC */
	&__null_handler,		/* 0x54 #5 NVMCTRL */
	&__null_handler,		/* 0x58 #6 DMAC */
	&__null_handler,		/* 0x5C #7 Reserved */
	&__null_handler,		/* 0x60 #8 EVSYS */
	&__isr_sercom0,			/* 0x64 #9 SERCOM0 */
	&__isr_sercom1,			/* 0x68 #10 SERCOM1 */
	&__null_handler,		/* 0x6C #11 Reserved */
	&__null_handler,		/* 0x70 #12 Reserved */
	&__null_handler,		/* 0x74 #13 TC1 */
	&__null_handler,		/* 0x78 #14 TC2 */
	&__null_handler,		/* 0x7C #15 ADC */
	&__null_handler,		/* 0x80 #16 Reserved */
	&__null_handler,		/* 0x84 #17 Reserved */
	&__null_handler,		/* 0x88 #18 Reserved */
};


/// CLOCK ///


static inline uint32_t
clock_get_source_hz(uint32_t srcid)
{
	switch (srcid) {
	case GCLK_GENCTRL_SRC_XOSC:
		break; // TODO
	case GCLK_GENCTRL_SRC_GCLKIN:
		break; // TODO
	case GCLK_GENCTRL_SRC_GCLKGEN1:
		return clock_get_generator_hz(1);
	case GCLK_GENCTRL_SRC_OSCULP32K:
		return 32000;
	case GCLK_GENCTRL_SRC_OSC32K:
		return 32000;
	case GCLK_GENCTRL_SRC_XOSC32K:
		return 32000;
	case GCLK_GENCTRL_SRC_OSC8M:
		return 8000000;
	case GCLK_GENCTRL_SRC_DFLL48M:
		return 48000000;
	case GCLK_GENCTRL_SRC_DPLL96M:
		return 96000000;
	default:
		assert(!"unknown clock value");
	}
	assert(!"unknown clock source");
	return 0;
}

static inline uint32_t
clock_get_generator_source(uint8_t genid)
{
	*(uint8_t *)&GCLK->GENCTRL = genid;
	return GCLK->GENCTRL & GCLK_GENCTRL_SRC_Msk;
}

static inline uint8_t
clock_get_generator_div(uint8_t genid)
{
	uint8_t div;

	*(uint8_t *)&GCLK->GENDIV = genid;
	div = FIELD(GCLK->GENDIV, GCLK_GENDIV_DIV);
	return div ? div : 1;
}

static inline uint8_t
clock_get_generator(uint8_t clkid)
{
	*(uint8_t *)&GCLK->CLKCTRL = clkid;
	return FIELD(GCLK->CLKCTRL, GCLK_CLKCTRL_GEN);
}

uint32_t
clock_get_generator_hz(uint8_t genid)
{
	return clock_get_source_hz(clock_get_generator_source(genid))
	 / clock_get_generator_div(genid);
}

uint32_t
clock_get_channel_hz(uint8_t clkid)
{
	return clock_get_generator_hz(clock_get_generator(clkid));
}

void
clock_init_generator(uint8_t genid, uint32_t srcid, uint32_t div)
{
	GCLK->GENDIV = genid | div;
	GCLK->GENCTRL = genid | srcid | GCLK_GENCTRL_GENEN;
	while (GCLK->STATUS & GCLK_STATUS_SYNCBUSY);
}

void
clock_enable_generator_output(uint8_t genid)
{
	GCLK->GENCTRL = (GCLK->GENCTRL & ~GCLK_GENCTRL_ID_Msk)
	 | genid | GCLK_GENCTRL_OE;
	while (GCLK->STATUS & GCLK_STATUS_SYNCBUSY);
}

void
clock_init(uint8_t clkid, uint8_t genid)
{
	GCLK->CLKCTRL = clkid | genid | GCLK_CLKCTRL_CLKEN;
	while (GCLK->STATUS & GCLK_STATUS_SYNCBUSY);
}


/// PWM ///


void
pwm_init(struct tc_count8 *tc, uint32_t ctrla_prescaler)
{
	switch (tc_get_id(tc)) {
	case 1:
		PM->APBCMASK |= PM_APBCMASK_TC1;
		break;
	case 2:
		PM->APBCMASK |= PM_APBCMASK_TC2;
		break;
	default: assert(!"unknown timer/counter");
	}

	tc->CTRLA = 0
	/* switch timer/counter to 8-bit mode */
	 | TC_COUNT8_CTRLA_MODE_COUNT8
	/* normal PWM mode */
	 | TC_COUNT8_CTRLA_WAVEGEN_NPWM
	/* do not divide the input generic clock */
	 | ctrla_prescaler
	/* stick to the prescaler signal on wraparound */
	 | TC_COUNT8_CTRLA_PRESCSYNC_PRESC;

	/* enable the timer/counter */
	tc->CTRLA |= TC_COUNT8_CTRLA_ENABLE;

	/* wait that the register write to complete */
	while (tc->STATUS & TC_COUNT8_STATUS_SYNCBUSY);
}

void
pwm_init_counter(uint8_t pin)
{
	PORT->PINCFG[pin] = 0
	/* enable peripheral multiplexing */
	 | PORT_PINCFG_PMUXEN
	/* internal pull-up resistor on SCL pin */
	 | PORT_PINCFG_PULLEN
	/* permit input to check for SCL pin stretching as common in I²C */
	 | PORT_PINCFG_INEN
	/* increase driver strength a bit */
	 | PORT_PINCFG_DRVSTR;
	/* apply the configuration to the pins */

	/* pin as output */
        PORT->DIRSET = (1u << pin);

	/* plug the pin to the timer/counter */
	port_set_pmux(pin, PORT_PMUX_TC);
}

void
pwm_set_duty_cycle(struct tc_count8 *tc, uint8_t counter_id, uint8_t duty_cycle)
{
	assert(counter_id < 4);
	tc->CC[counter_id] = duty_cycle;
}


/// USART ///


static struct usart_buffer {
	uint8_t *mem;
	size_t sz;
	int volatile done;
} usart_rx[2], usart_tx[2];

void
usart_init(struct usart *usart, uint32_t baud_hz, uint8_t txpo, uint8_t rxpo)
{
	uint32_t clock_hz = sercom_get_clock_hz(sercom_get_id(usart));

	usart->CTRLA = 0
	/* asynchronous usart with internal clock */
	 | USART_CTRLA_MODE_USART_INT_CLK
	/* most common way to use usart: least significant bit first */
	 | USART_CTRLA_DORD
	/* set to fractionnal baud rate for better accuracy */
	 | USART_CTRLA_SAMPR_16_FRACTIONAL
	/* pinout mapping for the `tx` and `tx` pins */
	 | txpo | rxpo;

	/* set the baud rate integer part (IP) and fractional part (FP) */
	usart->BAUD = 0
	 | (clock_hz / 16 / baud_hz / 8 << USART_BAUD_IP_Pos)
	 | (clock_hz / 16 / baud_hz % 8 << USART_BAUD_FP_Pos);

	/* enable the receiver and transmitter */
	usart->CTRLB |= USART_CTRLB_RXEN | USART_CTRLB_TXEN;
	while (usart->SYNCBUSY & USART_SYNCBUSY_CTRLB);

	/* enable the USART *after* it is configured (#25.6.2) */
	usart->CTRLA |= USART_CTRLA_ENABLE;
	while (usart->SYNCBUSY & USART_SYNCBUSY_ENABLE);
}

void
usart_queue_tx(struct usart *usart, uint8_t const *mem, size_t sz)
{
	struct usart_buffer *tx = &usart_tx[sercom_get_id(usart)];

	tx->done = 0;
	tx->mem = (uint8_t *)mem;
	tx->sz = sz;

	usart->INTENSET = USART_INTENSET_DRE;
	NVIC->ISER = (1u << (9 + sercom_get_id(usart)));
}

void
usart_wait_tx(struct usart *usart)
{
	struct usart_buffer *tx = &usart_tx[sercom_get_id(usart)];

	while (!tx->done);
}

void
usart_queue_rx(struct usart *usart, uint8_t *mem, size_t sz)
{
	struct usart_buffer *rx = &usart_rx[sercom_get_id(usart)];

	rx->done = 0;
	rx->mem = mem;
	rx->sz = sz;

	usart->INTENSET = USART_INTENSET_RXC;
}

void
usart_wait_rx(struct usart *usart)
{
	struct usart_buffer *rx = &usart_rx[sercom_get_id(usart)];

	while (!rx->done);
}

static inline void
usart_interrupt_tx_data_register_empty(struct usart *usart)
{
	struct usart_buffer *tx = &usart_tx[sercom_get_id(usart)];

	if (tx->sz == 0) {
		usart->INTENCLR = USART_INTENSET_DRE;
		usart->INTENSET = USART_INTENSET_TXC;
	} else {
		usart->DATA = *tx->mem++;
		tx->sz--;
	}
}

static inline void
usart_interrupt_tx_complete(struct usart *usart)
{
	struct usart_buffer *tx = &usart_tx[sercom_get_id(usart)];

	if (tx->sz == 0) {
		usart->INTENCLR = USART_INTENSET_TXC;
		tx->done = 1;
	}
}

static inline void
usart_interrupt_rx_complete(struct usart *usart)
{
	struct usart_buffer *rx = &usart_rx[sercom_get_id(usart)];

	(void)rx;
}

static inline void
usart_interrupt_rx_start(struct usart *usart)
{
	struct usart_buffer *rx = &usart_rx[sercom_get_id(usart)];

	(void)rx;
}

static inline void
usart_interrupt_rx_clear_to_send(struct usart *usart)
{
	struct usart_buffer *rx = &usart_rx[sercom_get_id(usart)];

	(void)rx;
}

static inline void
usart_interrupt_rx_break(struct usart *usart)
{
	struct usart_buffer *rx = &usart_rx[sercom_get_id(usart)];

	(void)rx;
}

static inline void
usart_interrupt_error(struct usart *usart)
{
	(void)usart;
}

void
usart_interrupt(struct usart *usart)
{
	uint32_t reg = usart->INTFLAG;

	if (reg & USART_INTFLAG_DRE)
		usart_interrupt_tx_data_register_empty(usart);
	if (reg & USART_INTFLAG_TXC)
		usart_interrupt_tx_complete(usart);
	if (reg & USART_INTFLAG_RXC)
		usart_interrupt_rx_complete(usart);
	if (reg & USART_INTFLAG_RXS)
		usart_interrupt_rx_start(usart);
	if (reg & USART_INTFLAG_CTSIC)
		usart_interrupt_rx_clear_to_send(usart);
	if (reg & USART_INTFLAG_RXBRK)
		usart_interrupt_rx_break(usart);
	if (reg & USART_INTFLAG_ERROR)
		usart_interrupt_error(usart);
}


/// I2C_MASTER ///


static struct i2c_master_ctx {
	uint8_t *buf;
	size_t sz;
	uint8_t volatile status;
} i2c_master_ctx[2];

void
i2c_master_init(struct i2c_master *i2c_master, uint32_t baud_hz, uint8_t pin_scl, uint8_t pin_sda)
{
	uint8_t pincfg;
	uint32_t baud;

	pincfg = 0
	/* enable peripheral multiplexing */
	 | PORT_PINCFG_PMUXEN
	/* internal pull-up resistor on SCL pin */
	 | PORT_PINCFG_PULLEN
	/* permit input to check for SCL pin stretching as common in I²C */
	 | PORT_PINCFG_INEN
	/* increase driver strength a bit */
	 | PORT_PINCFG_DRVSTR;
	PORT->PINCFG[pin_scl] = pincfg;
	PORT->PINCFG[pin_sda] = pincfg;

	/* plug SCL and SDA pins to SERCOM */
	port_set_pmux(pin_scl, PORT_PMUX_SERCOM);
	port_set_pmux(pin_sda, PORT_PMUX_SERCOM);

	i2c_master->CTRLA = 0
	/* time-out when SCL held low for too long */
	 | I2C_MASTER_CTRLA_LOWTOUTEN
	/* default for inactivity time-out */
	 | I2C_MASTER_CTRLA_INACTOUT_205_US
	/* allow SCL pin to be stretched by the slave */
	 | I2C_MASTER_CTRLA_SCLSM
	/* time-out and reset ourself when a slave stretches SCL for 25ms */
	 | I2C_MASTER_CTRLA_SEXTTOEN
	/* time-out and reset ourself when a slave stretches SCL for 10ms */
	 | I2C_MASTER_CTRLA_MEXTTOEN
	/* set SERCOM generic serial to I²C Master mode */
	 | I2C_MASTER_CTRLA_MODE_I2C_MASTER
	/* default speed mode to standard speed */
	 | I2C_MASTER_CTRLA_SPEED_400_KHZ_MAX
	/* default for SDA pin hold time */
	 | I2C_MASTER_CTRLA_SDAHOLD_450_NS;

	i2c_master->CTRLB = 0
	/* this code only supports "smart mode" where hardware does more */
	 | I2C_MASTER_CTRLB_SMEN;

	/* the rising time of the clock has been ignored below, it varies
	 * depending on the capacitance of the bus */
	baud = sercom_get_clock_hz(sercom_get_id(i2c_master)) / (baud_hz * 2) - 1;

	/* set the baud rate for normal mode */
	i2c_master->BAUD = baud << I2C_MASTER_BAUD_BAUD_Pos;

	i2c_master->INTENSET = 0
	/* master-on-bus interrupt: when writing */
	 | I2C_MASTER_INTENSET_MB 
	/* slave-on-bus interrupt: when reading */
	 | I2C_MASTER_INTENSET_SB
	/* interrupts for transaction errors */
	 | I2C_MASTER_INTENSET_ERROR;

	/* enable I²C *after* it is configured (#27.6.2.1) */
	i2c_master->CTRLA |= I2C_MASTER_CTRLA_ENABLE;
	while (i2c_master->SYNCBUSY & I2C_MASTER_SYNCBUSY_ENABLE);

	/* we just started, we do not know in which state are the
	 * slave, but we guess and move from UNKNOWN to IDLE */
	i2c_master->STATUS = (i2c_master->STATUS  & ~I2C_MASTER_STATUS_BUSSTATE_Msk)
	 | I2C_MASTER_STATUS_BUSSTATE_IDLE;
	while (i2c_master->SYNCBUSY & I2C_MASTER_SYNCBUSY_SYSOP);

	/* interrupt will be triggered as soon as I2C_MASTER->ADDR is written */
	NVIC->ISER = 1u << (9 + sercom_get_id(i2c_master));
}

static inline void
i2c_master_interrupt_error(struct i2c_master *i2c_master, struct i2c_master_ctx *ctx)
{
	if (FIELD(i2c_master->STATUS, I2C_MASTER_STATUS_BUSSTATE)
	 == I2C_MASTER_STATUS_BUSSTATE_BUSY) {
		i2c_master->CTRLB &= ~I2C_MASTER_CTRLB_ACKACT;
		i2c_master->CTRLB = (i2c_master->CTRLB & ~I2C_MASTER_CTRLB_CMD_Msk)
		 | I2C_MASTER_CTRLB_CMD_ACK_STOP;
	}
	ctx->status = -1;
}

static inline void
i2c_master_interrupt_master_on_bus(struct i2c_master *i2c_master, struct i2c_master_ctx *ctx)
{
	if (ctx->sz == 0) {
		i2c_master->CTRLB = (i2c_master->CTRLB & ~I2C_MASTER_CTRLB_CMD_Msk)
		 | I2C_MASTER_CTRLB_CMD_ACK_STOP;
		ctx->status = 0;
	} else {
		i2c_master->DATA = *ctx->buf++;
		ctx->sz--;
	}
}

static inline void
i2c_master_interrupt_slave_on_bus(struct i2c_master *i2c_master, struct i2c_master_ctx *ctx)
{
	if (ctx->sz == 0) {
		i2c_master->CTRLB &= ~I2C_MASTER_CTRLB_ACKACT;
		i2c_master->CTRLB = (i2c_master->CTRLB & ~I2C_MASTER_CTRLB_CMD_Msk)
		 | I2C_MASTER_CTRLB_CMD_ACK_STOP;
		ctx->status = 0;
	} else {
		*ctx->buf++ = i2c_master->DATA;
		ctx->sz--;
	}
}

void
i2c_master_interrupt(struct i2c_master *i2c_master)
{
	struct i2c_master_ctx *ctx = &i2c_master_ctx[sercom_get_id(i2c_master)];
	uint8_t reg = i2c_master->INTFLAG;

	if (reg & I2C_MASTER_INTFLAG_ERROR)
		i2c_master_interrupt_error(i2c_master, ctx);
	else if (reg & I2C_MASTER_INTFLAG_MB)
		i2c_master_interrupt_master_on_bus(i2c_master, ctx);
	else if (reg & I2C_MASTER_INTFLAG_SB)
		i2c_master_interrupt_slave_on_bus(i2c_master, ctx);
}

static inline void
i2c_master_queue(struct i2c_master *i2c_master, uint8_t addr, uint8_t *buf, size_t sz, uint8_t rw)
{
	struct i2c_master_ctx *ctx = &i2c_master_ctx[sercom_get_id(i2c_master)];

	ctx->status = 1;
	ctx->buf = buf;
	ctx->sz = sz;

        /* this starts to send the address immediately */
	i2c_master->ADDR = ((addr << 1) | rw) << I2C_MASTER_ADDR_ADDR_Pos;

	/* that's it, the rest happens in interrupts */
}

void
i2c_master_queue_tx(struct i2c_master *i2c_master, uint8_t addr, uint8_t const *buf, size_t sz)
{
	i2c_master_queue(i2c_master, addr, (uint8_t *)buf, sz, 0);
}

void
i2c_master_queue_rx(struct i2c_master *i2c_master, uint8_t addr, uint8_t *buf, size_t sz)
{
	i2c_master_queue(i2c_master, addr, buf, sz, 1);
}

int
i2c_master_wait(struct i2c_master *i2c_master)
{
	struct i2c_master_ctx *ctx = &i2c_master_ctx[sercom_get_id(i2c_master)];

	while (ctx->status > 0);
	return ctx->status;
}


/// SPI_MASTER ///


void
spi_master_init(struct spi *spi_master, uint32_t baud_hz, uint8_t pin_sck,
	uint8_t pin_miso, uint8_t pin_mosi, uint8_t pin_ss,
	uint32_t dipo, uint32_t dopo)
{
	uint32_t clock_hz;
	uint8_t pincfg;

	pincfg = 0
	/* enable peripheral multiplexing */
	 | PORT_PINCFG_PMUXEN
	/* internal pull-up resistor on SCL pin */
	 | PORT_PINCFG_PULLEN
	/* permit input to check for SCL pin stretching as common in I²C */
	 | PORT_PINCFG_INEN
	/* increase driver strength a bit */
	 | PORT_PINCFG_DRVSTR;
	/* apply the configuration to the pins */
	PORT->PINCFG[pin_sck] = pincfg;
	PORT->PINCFG[pin_miso] = pincfg;
	PORT->PINCFG[pin_mosi] = pincfg;
	PORT->PINCFG[pin_ss] = pincfg;

	/* pins MOSI, SCK, SS as output */
	PORT->DIRSET = (1u << pin_mosi) | (1u << pin_sck) | (1u << pin_ss);
	/* pins MISO as input */
	PORT->DIRCLR = (1u << pin_miso);

	/* plug the SCK, MISO, MOSI and SS pins to the SERCOM */
	port_set_pmux(pin_sck, PORT_PMUX_SERCOM);
	port_set_pmux(pin_miso, PORT_PMUX_SERCOM);
	port_set_pmux(pin_mosi, PORT_PMUX_SERCOM);
	port_set_pmux(pin_ss, PORT_PMUX_SERCOM);

	spi_master->CTRLA = 0
	/* select SPI Master mode for the SERCOM peripheral */
	 | SPI_CTRLA_MODE_SPI_MASTER
	/* not using SPI addresses, just regular frames */
	 | SPI_CTRLA_FORM_SPI
	/* pinout for input and output */
	 | (dipo << SPI_CTRLA_DIPO_Pos)
	 | (dopo << SPI_CTRLA_DOPO_Pos)
	/* least-significant bit first */
	 | SPI_CTRLA_DORD;

	spi_master->CTRLB = 0
	/* the hardware toggles the SS pin */
	 | SPI_CTRLB_MSSEN
	/* character size to 8-bit */
	 | SPI_CTRLB_CHSIZE_8BIT
	/* enable the receiver */
	 | SPI_CTRLB_RXEN;

	/* set the baud rate (Asynchronous Arithmetic mode) */
	clock_hz = sercom_get_clock_hz(sercom_get_id(spi_master));
	spi_master->BAUD = clock_hz / (2 * baud_hz) - 1;

	/* enable SPI *after* it is configured (#26.6.2.1 ) */
	spi_master->CTRLA |= SPI_CTRLA_ENABLE;
	while (spi_master->SYNCBUSY & SPI_SYNCBUSY_ENABLE);
}


/// SYSTICK ///


static volatile uint64_t systick_runtime_ms;

void
systick_init(void)
{
	/* set the number of ticks per milliseconds */
	SYSTICK->RVR = clock_get_generator_hz(0) / 1000;

	SYSTICK->CSR = 0
	/* enable the peripheral */
	 | SYSTICK_CSR_ENABLE
	/* use system clock as source for systick */
	 | SYSTICK_CSR_CLKSOURCE
	/* generate an interrupts on every tick */
	 | SYSTICK_CSR_TICKINT;
}

void
systick_interrupt(void)
{
	systick_runtime_ms++;
}

uint64_t
systick_get_runtime_ms(void)
{
	// TODO: make it callable from higher priority interrupt
	return systick_runtime_ms;
}

void
systick_sleep_ms(uint64_t duration_ms)
{
	uint64_t deadline_ms;

	deadline_ms = systick_get_runtime_ms() + duration_ms;
	while (systick_get_runtime_ms() < deadline_ms);
}
