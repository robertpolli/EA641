;---------------
; Assembly Code
;---------------
#define __SFR_OFFSET 0x00
#include "avr/io.h"

;---------------------------------------------------------------------------
.global start
.global writeValue
.global sampleHold
.global startConv
.global endConv
;---------------------------------------------------------------------------

start:

    RET                       ;return to setup() function
;---------------------------------------------------------------------------

writeValue:
  OUT  PORTD, r24             ; Write value to port D
  RET

;---------------------------------------------------------------------------

sampleHold:
  SBI   PORTB, 1            ; sample
  CBI   PORTB, 1            ; Hold
  RET
;---------------------------------------------------------------------------

startConv:
  SBI   PORTB, 2            ; EOC = 1
  SBI   PORTB, 3            ; START = 1
  RET
;---------------------------------------------------------------------------

endConv:
  CBI   PORTB, 2            ; EOC = 0
  CBI   PORTB, 3            ; START = 0
  RET  
