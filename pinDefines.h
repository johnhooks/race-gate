#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H


#define SPI_CLK               PC1
#define SPI_CLK_PORT          PORTC
#define SPI_CLK_DDR           DDRC

#define SPI_DATA              PC2
#define SPI_DATA_PORT         PORTC
#define SPI_DATA_DDR          DDRC

#define SPI_SS                PC3
#define SPI_SS_PORT           PORTC
#define SPI_SS_DDR            DDRC

#define LED_PORT              PORTD
#define LED_DDR               DDRD
#define LED_R                 PD5
#define LED_G                 PD3
#define LED_B                 PD6
#define LED_PWM_R             OCR0B /* PD5 */
#define LED_PWM_G             OCR2B /* PD3 */
#define LED_PWM_B             OCR0A /* PD6 */


#endif
