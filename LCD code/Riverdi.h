/*
 * Riverdi.h
 *
 * Created: 29/10/2018 07:00:51 م
 *  Author: Alaa
 * Edited : 24/11/2018 by Gamal
 */ 


#ifndef RIVERDI_H_
#define RIVERDI_H_
#include <ioport.h>
#include <spi.h>

volatile uint16_t cmdOffset = 0x0000;	/* used to navigate command ring buffer */


											/*Functions Declaration*/
void Riverdi_host_command(uint8_t command);
void Riverdi_write_8(uint32_t address,uint8_t data);
void Riverdi_write_16(uint32_t address,uint16_t data);
void Riverdi_write_32(uint32_t address,uint32_t data);
uint8_t Riverdi_read_8(uint32_t address);
uint16_t Riverdi_read_16(uint32_t address);
uint32_t Riverdi_read_32(uint32_t ftAddress);
void Riverdi_init(void);
void Riverdi_inc_cmdoffset(uint16_t increment);
void Riverdi_start_cmd(uint32_t command);


				-							/*Pin declarations*/


#define POWER_PIN PIO_PC2_IDX

											/* Host commands */
											
											
#define FT8_ACTIVE	0x00  /* place FT8xx in active state */
#define FT8_STANDBY	0x41  /* place FT8xx in Standby (clk running) */
#define FT8_SLEEP	0x42  /* place FT8xx in Sleep (clk off) */
#define FT8_PWRDOWN	0x50  /* place FT8xx in Power Down (core off) */
#define FT8_CLKEXT	0x44  /* select external clock source */
#define FT8_CLKINT	0x48  /* select internal clock source */
#define FT8_CORERST	0x68  /* reset core - all registers default and processors reset */
#define FT8_CLK48M	0x62  /* select 48MHz PLL output */
#define FT8_CLK36M	0x61  /* select 36MHz PLL output */

/* Register definitions */
#define REG_ANA_COMP         0x302184UL /* only listed in datasheet */
#define REG_BIST_EN          0x302174UL /* only listed in datasheet */
#define REG_CLOCK            0x302008UL
#define REG_CMDB_SPACE       0x302574UL
#define REG_CMDB_WRITE       0x302578UL
#define REG_CMD_DL           0x302100UL
#define REG_CMD_READ         0x3020f8UL
#define REG_CMD_WRITE        0x3020fcUL
#define REG_CPURESET         0x302020UL
#define REG_CSPREAD          0x302068UL
#define REG_CTOUCH_EXTENDED  0x302108UL
#define REG_CTOUCH_TOUCH0_XY 0x302124UL /* only listed in datasheet */
#define REG_CTOUCH_TOUCH4_X  0x30216cUL
#define REG_CTOUCH_TOUCH4_Y  0x302120UL
#define REG_CTOUCH_TOUCH1_XY 0x30211cUL
#define REG_CTOUCH_TOUCH2_XY 0x30218cUL
#define REG_CTOUCH_TOUCH3_XY 0x302190UL
#define REG_TOUCH_CONFIG     0x302168UL
#define REG_DATESTAMP        0x302564UL /* only listed in datasheet */
#define REG_DITHER           0x302060UL
#define REG_DLSWAP           0x302054UL
#define REG_FRAMES           0x302004UL
#define REG_FREQUENCY        0x30200cUL
#define REG_GPIO             0x302094UL
#define REG_GPIOX            0x30209cUL
#define REG_GPIOX_DIR        0x302098UL
#define REG_GPIO_DIR         0x302090UL
#define REG_HCYCLE           0x30202cUL
#define REG_HOFFSET          0x302030UL
#define REG_HSIZE            0x302034UL
#define REG_HSYNC0           0x302038UL
#define REG_HSYNC1           0x30203cUL
#define REG_ID               0x302000UL
#define REG_INT_EN           0x3020acUL
#define REG_INT_FLAGS        0x3020a8UL
#define REG_INT_MASK         0x3020b0UL
#define REG_MACRO_0          0x3020d8UL
#define REG_MACRO_1          0x3020dcUL
#define REG_MEDIAFIFO_READ   0x309014UL /* only listed in programmers guide */
#define REG_MEDIAFIFO_WRITE  0x309018UL /* only listed in programmers guide */
#define REG_OUTBITS          0x30205cUL
#define REG_PCLK             0x302070UL
#define REG_PCLK_POL         0x30206cUL
#define REG_PLAY             0x30208cUL
#define REG_PLAYBACK_FORMAT  0x3020c4UL
#define REG_PLAYBACK_FREQ    0x3020c0UL
#define REG_PLAYBACK_LENGTH  0x3020b8UL
#define REG_PLAYBACK_LOOP    0x3020c8UL
#define REG_PLAYBACK_PLAY    0x3020ccUL
#define REG_PLAYBACK_READPTR 0x3020bcUL
#define REG_PLAYBACK_START   0x3020b4UL
#define REG_PWM_DUTY         0x3020d4UL
#define REG_PWM_HZ           0x3020d0UL
#define REG_RENDERMODE       0x302010UL /* only listed in datasheet */
#define REG_ROTATE           0x302058UL
#define REG_SNAPFORMAT       0x30201cUL /* only listed in datasheet */
#define REG_SNAPSHOT         0x302018UL /* only listed in datasheet */
#define REG_SNAPY            0x302014UL /* only listed in datasheet */
#define REG_SOUND            0x302088UL
#define REG_SPI_WIDTH        0x302188UL /* listed with false offset in programmers guide V1.1 */
#define REG_SWIZZLE          0x302064UL
#define REG_TAG              0x30207cUL
#define REG_TAG_X            0x302074UL
#define REG_TAG_Y            0x302078UL
#define REG_TAP_CRC          0x302024UL /* only listed in datasheet */
#define REG_TAP_MASK         0x302028UL /* only listed in datasheet */
#define REG_TOUCH_ADC_MODE   0x302108UL
#define REG_TOUCH_CHARGE     0x30210cUL
#define REG_TOUCH_DIRECT_XY  0x30218cUL
#define REG_TOUCH_DIRECT_Z1Z2 0x302190UL
#define REG_TOUCH_MODE       0x302104UL
#define REG_TOUCH_OVERSAMPLE 0x302114UL
#define REG_TOUCH_RAW_XY     0x30211cUL
#define REG_TOUCH_RZ         0x302120UL
#define REG_TOUCH_RZTHRESH   0x302118UL
#define REG_TOUCH_SCREEN_XY  0x302124UL
#define REG_TOUCH_SETTLE     0x302110UL
#define REG_TOUCH_TAG        0x30212cUL
#define REG_TOUCH_TAG1       0x302134UL /* only listed in datasheet */
#define REG_TOUCH_TAG1_XY    0x302130UL /* only listed in datasheet */
#define REG_TOUCH_TAG2       0x30213cUL /* only listed in datasheet */
#define REG_TOUCH_TAG2_XY    0x302138UL /* only listed in datasheet */
#define REG_TOUCH_TAG3       0x302144UL /* only listed in datasheet */
#define REG_TOUCH_TAG3_XY    0x302140UL /* only listed in datasheet */
#define REG_TOUCH_TAG4       0x30214cUL /* only listed in datasheet */
#define REG_TOUCH_TAG4_XY    0x302148UL /* only listed in datasheet */
#define REG_TOUCH_TAG_XY     0x302128UL
#define REG_TOUCH_TRANSFORM_A 0x302150UL
#define REG_TOUCH_TRANSFORM_B 0x302154UL
#define REG_TOUCH_TRANSFORM_C 0x302158UL
#define REG_TOUCH_TRANSFORM_D 0x30215cUL
#define REG_TOUCH_TRANSFORM_E 0x302160UL
#define REG_TOUCH_TRANSFORM_F 0x302164UL
#define REG_TRACKER          0x309000UL /* only listed in programmers guide */
#define REG_TRACKER_1        0x309004UL /* only listed in programmers guide */
#define REG_TRACKER_2        0x309008UL /* only listed in programmers guide */
#define REG_TRACKER_3        0x30900cUL /* only listed in programmers guide */
#define REG_TRACKER_4        0x309010UL /* only listed in programmers guide */
#define REG_TRIM             0x302180UL
#define REG_VCYCLE           0x302040UL
#define REG_VOFFSET          0x302044UL
#define REG_VOL_PB           0x302080UL
#define REG_VOL_SOUND        0x302084UL
#define REG_VSIZE            0x302048UL
#define REG_VSYNC0           0x30204cUL
#define REG_VSYNC1           0x302050UL

									/*Initialization parameters for FT812*/

#define FT8_VSYNC0	(0L)	/* Tvf Vertical Front Porch */
#define FT8_VSYNC1	(10L)	/* Tvf + Tvp Vertical Front Porch plus Vsync Pulse width */
#define FT8_VOFFSET	(23L)	/* Tvf + Tvp + Tvb Number of non-visible lines (in lines) */
#define FT8_VCYCLE	(525L)	/* Tv Total number of lines (visible and non-visible) (in lines) */
#define FT8_VSIZE	(480L)	/* Tvd Number of visible lines (in lines) - display height */
#define FT8_HSYNC0	(0L)	/* Thf Horizontal Front Porch */
#define FT8_HSYNC1	(10L)	/* Thf + Thp Horizontal Front Porch plus Hsync Pulse width */
#define FT8_HOFFSET (46L)	/* Thf + Thp + Thb Length of non-visible part of line (in PCLK cycles) */
#define FT8_HCYCLE 	(1056L)	/* Th Total length of line (visible and non-visible) (in PCLKs) */
#define FT8_HSIZE	(800L)	/* Thd Length of visible part of line (in PCLKs) - display width */
#define FT8_PCLKPOL (1L)	/* PCLK polarity (0 = rising edge, 1 = falling edge) */
#define FT8_SWIZZLE (0L)	/* Defines the arrangement of the RGB pins of the FT800 */
#define FT8_PCLK	(2L)	/* 60MHz / REG_PCLK = PCLK frequency 30 MHz */
#define FT8_CSPREAD	(1L)	/* helps with noise, when set to 1 fewer signals are changed simultaneously, reset-default: 1 */
#define FT8_TOUCH_RZTHRESH (1800L)	/* touch-sensitivity */
#define FT8_HAS_CRYSTAL 0

								/* Memory definitions */

#define FT8_RAM_G			0x000000UL
#define FT8_ROM_CHIPID		0x0C0000UL
#define FT8_ROM_FONT		0x1E0000UL
#define FT8_ROM_FONT_ADDR	0x2FFFFCUL
#define FT8_RAM_DL			0x300000UL
#define FT8_RAM_REG			0x302000UL
#define FT8_RAM_CMD			0x308000UL

/* FT8xx Memory Commands - use with FT8_memWritexx and FT8_memReadxx */
#define MEM_WRITE	0x80	/* FT8xx Host Memory Write */
#define MEM_READ	0x00	/* FT8xx Host Memory Read */

/* FT8xx graphics engine specific macros useful for static display list generation */
#define ALPHA_FUNC(func,ref) ((9UL<<24)|(((func)&7UL)<<8)|(((ref)&255UL)<<0))
#define BEGIN(prim) ((31UL<<24)|(((prim)&15UL)<<0))
#define BITMAP_HANDLE(handle) ((5UL<<24)|(((handle)&31UL)<<0))
#define BITMAP_LAYOUT(format,linestride,height) ((7UL<<24)|(((format)&31UL)<<19)|(((linestride)&1023UL)<<9)|(((height)&511UL)<<0))
#define BITMAP_SIZE(filter,wrapx,wrapy,width,height) ((8UL<<24)|(((filter)&1UL)<<20)|(((wrapx)&1UL)<<19)|(((wrapy)&1UL)<<18)|(((width)&511UL)<<9)|(((height)&511UL)<<0))
#define BITMAP_TRANSFORM_A(a) ((21UL<<24)|(((a)&131071UL)<<0))
#define BITMAP_TRANSFORM_B(b) ((22UL<<24)|(((b)&131071UL)<<0))
#define BITMAP_TRANSFORM_C(c) ((23UL<<24)|(((c)&16777215UL)<<0))
#define BITMAP_TRANSFORM_D(d) ((24UL<<24)|(((d)&131071UL)<<0))
#define BITMAP_TRANSFORM_E(e) ((25UL<<24)|(((e)&131071UL)<<0))
#define BITMAP_TRANSFORM_F(f) ((26UL<<24)|(((f)&16777215UL)<<0))
#define BLEND_FUNC(src,dst) ((11UL<<24)|(((src)&7UL)<<3)|(((dst)&7UL)<<0))
#define CALL(dest) ((29UL<<24)|(((dest)&65535UL)<<0))
#define CELL(cell) ((6UL<<24)|(((cell)&127UL)<<0))
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))
#define CLEAR_COLOR_A(alpha) ((15UL<<24)|(((alpha)&255UL)<<0))
#define CLEAR_COLOR_RGB(red,green,blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define CLEAR_STENCIL(s) ((17UL<<24)|(((s)&255UL)<<0))
#define CLEAR_TAG(s) ((18UL<<24)|(((s)&255UL)<<0))
#define COLOR_A(alpha) ((16UL<<24)|(((alpha)&255UL)<<0))
#define COLOR_MASK(r,g,b,a) ((32UL<<24)|(((r)&1UL)<<3)|(((g)&1UL)<<2)|(((b)&1UL)<<1)|(((a)&1UL)<<0))
#define COLOR_RGB(red,green,blue) ((4UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define DISPLAY() ((0UL<<24))
#define END() ((33UL<<24))
#define JUMP(dest) ((30UL<<24)|(((dest)&65535UL)<<0))
#define LINE_WIDTH(width) ((14UL<<24)|(((width)&4095UL)<<0))
#define MACRO(m) ((37UL<<24)|(((m)&1UL)<<0))
#define POINT_SIZE(size) ((13UL<<24)|(((size)&8191UL)<<0))
#define RESTORE_CONTEXT() ((35UL<<24))
#define RETURN() ((36UL<<24))
#define SAVE_CONTEXT() ((34UL<<24))
#define STENCIL_FUNC(func,ref,mask) ((10UL<<24)|(((func)&7UL)<<16)|(((ref)&255UL)<<8)|(((mask)&255UL)<<0))
#define STENCIL_MASK(mask) ((19UL<<24)|(((mask)&255UL)<<0))
#define STENCIL_OP(sfail,spass) ((12UL<<24)|(((sfail)&7UL)<<3)|(((spass)&7UL)<<0))
#define TAG(s) ((3UL<<24)|(((s)&255UL)<<0))
#define TAG_MASK(mask) ((20UL<<24)|(((mask)&1UL)<<0))
#define VERTEX2F(x,y) ((1UL<<30)|(((x)&32767UL)<<15)|(((y)&32767UL)<<0))
#define VERTEX2II(x,y,handle,cell) ((2UL<<30)|(((x)&511UL)<<21)|(((y)&511UL)<<12)|(((handle)&31UL)<<7)|(((cell)&127UL)<<0))
///////////////////////
/* commands to draw graphics objects: */
void Riverdi_cmd_text(int16_t x0, int16_t y0, int16_t font, uint16_t options, const char* text);
void Riverdi_cmd_button(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t font, uint16_t options, const char* text);
void Riverdi_cmd_clock(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t hours, uint16_t minutes, uint16_t seconds, uint16_t millisecs);
void Riverdi_cmd_bgcolor(uint32_t color);
void Riverdi_cmd_fgcolor(uint32_t color);
void Riverdi_cmd_gradcolor(uint32_t color);
void Riverdi_cmd_gauge(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range);
void Riverdi_cmd_gradient(int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1);
void Riverdi_cmd_keys(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t font, uint16_t options, const char* text);
void Riverdi_cmd_progress(int16_t x0, int16_t y0, int16_t w0, int16_t h0, uint16_t options, uint16_t val, uint16_t range);
void Riverdi_cmd_scrollbar(int16_t x0, int16_t y0, int16_t w0, int16_t h0, uint16_t options, uint16_t val, uint16_t size, uint16_t range);
void Riverdi_cmd_slider(int16_t x1, int16_t y1, int16_t w1, int16_t h1, uint16_t options, uint16_t val, uint16_t range);
void Riverdi_cmd_dial(int16_t x0, int16_t y0, int16_t r0, uint16_t options, uint16_t val);
void Riverdi_cmd_toggle(int16_t x0, int16_t y0, int16_t w0, int16_t font, uint16_t options, uint16_t state, const char* text);
void Riverdi_cmd_number(int16_t x0, int16_t y0, int16_t font, uint16_t options, int32_t number);
// command execution // 
void Riverdi_cmd_start(void);
void Riverdi_cmd_execute(void);
uint8_t Riverdi_busy(void);
void Riverdi_write_string(const char *text);
/* commands addresses in ram*/
#define CMD_APPEND				0xFFFFFF1EUL
#define CMD_BGCOLOR				0xFFFFFF09UL
#define CMD_BUTTON				0xFFFFFF0DUL
#define CMD_CALIBRATE			0xFFFFFF15UL
#define CMD_CLOCK				0xFFFFFF14UL
#define CMD_COLDSTART			0xFFFFFF32UL
#define CMD_DIAL				0xFFFFFF2DUL
#define CMD_DLSTART				0xFFFFFF00UL
#define CMD_FGCOLOR				0xFFFFFF0AUL
#define CMD_GAUGE				0xFFFFFF13UL
#define CMD_GETMATRIX			0xFFFFFF33UL
#define CMD_GETPROPS			0xFFFFFF25UL
#define CMD_GETPTR				0xFFFFFF23UL
#define CMD_GRADCOLOR			0xFFFFFF34UL
#define CMD_GRADIENT			0xFFFFFF0BUL
#define CMD_INFLATE				0xFFFFFF22UL
#define CMD_INTERRUPT			0xFFFFFF02UL
#define CMD_KEYS				0xFFFFFF0EUL
#define CMD_LOADIDENTITY		0xFFFFFF26UL
#define CMD_LOADIMAGE			0xFFFFFF24UL
#define CMD_LOGO				0xFFFFFF31UL
#define CMD_MEMCPY				0xFFFFFF1DUL
#define CMD_MEMCRC				0xFFFFFF18UL
#define CMD_MEMSET				0xFFFFFF1BUL
#define CMD_MEMWRITE			0xFFFFFF1AUL
#define CMD_MEMZERO				0xFFFFFF1CUL
#define CMD_NUMBER				0xFFFFFF2EUL
#define CMD_PROGRESS			0xFFFFFF0FUL
#define CMD_REGREAD				0xFFFFFF19UL
#define CMD_ROTATE				0xFFFFFF29UL
#define CMD_SCALE				0xFFFFFF28UL
#define CMD_SCREENSAVER			0xFFFFFF2FUL
#define CMD_SCROLLBAR			0xFFFFFF11UL
#define CMD_SETFONT				0xFFFFFF2BUL
#define CMD_SETMATRIX			0xFFFFFF2AUL
#define CMD_SKETCH				0xFFFFFF30UL
#define CMD_SLIDER				0xFFFFFF10UL
#define CMD_SNAPSHOT			0xFFFFFF1FUL
#define CMD_SPINNER				0xFFFFFF16UL
#define CMD_STOP				0xFFFFFF17UL
#define CMD_SWAP				0xFFFFFF01UL
#define CMD_TEXT				0xFFFFFF0CUL
#define CMD_TOGGLE				0xFFFFFF12UL
#define CMD_TRACK				0xFFFFFF2CUL
#define CMD_TRANSLATE			0xFFFFFF27UL

/* Graphics display list swap defines */
#define FT8_DLSWAP_DONE          0UL
#define FT8_DLSWAP_LINE          1UL
#define FT8_DLSWAP_FRAME         2UL //Recommended by datasheet page 35
/* display list commands function */
