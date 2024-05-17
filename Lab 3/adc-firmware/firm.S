;---------------
; Assembly Code
;---------------
#define __SFR_OFFSET 0x00
#include "avr/io.h"

;---------------------------------------------------------------------------
.global start
.global writeValue
.global readOC
.global sampleHold
.global startConv
.global endConv
;---------------------------------------------------------------------------

start:

    RET                       ;return to setup() function
;---------------------------------------------------------------------------

writeValue:
  OUT  PORTD, r24             ; Write value to port D

  LDI   r30, 0xe7
  CLR   r31
  
valWritten:
  DEC   r30
  CPSE  r30, r31
  JMP   valWritten
    
  RET

;---------------------------------------------------------------------------

readOC:
  IN r24, PINB
  RET

;---------------------------------------------------------------------------

sampleHold:
  SBI   PORTB, 1            ; sample
  LDI   r30, 0xe0
  CLR   r31
  
retSample:
  DEC   r30
  CPSE  r30, r31
  JMP   retSample
  
  CBI   PORTB, 1            ; Hold
  
  RET
;---------------------------------------------------------------------------

startConv:
  CBI   PORTB, 2            ; EOC = 0
  SBI   PORTB, 3            ; START = 1
  RET
;---------------------------------------------------------------------------

endConv:
  SBI   PORTB, 2            ; EOC = 1
  CBI   PORTB, 3            ; START = 0
  RET  
