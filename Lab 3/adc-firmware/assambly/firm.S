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
.global converter
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

converter:
  LDI r24, 0x80            ; Armazena 0b10000000 
  LDI r26, 0x06             ; Armazena a posicao do bit de comparacao
  .equ POSITION, 6       ; ''  ''  ''  ''
  
forLoop:
  ;JMP writeValue            ; Escreve r24 na saida 


  OUT  PORTD, r24             ; Write value to port D


  

  IN r30, PINB
  ANDI r30,0x01             ; Isola apenas o bit 0 do registrador
  
  SBRC r30, 0               ; SE OC=1
  SBR r24, 1 << (POSITION)         ; Set o bit na posição POSITION  

  CPI r30, 0x00 
  BRNE 2                    ; ELSE
  CBR r24, 1 << (POSITION + 1)     ;  
  SBR r24, 1 << (POSITION)         ;

  .equ POSITION, (POSITION - 1)
  
  SUBI  r26, 0x01                 ; Decrementa o Bit Location
  BREQ 0            ; Sai d o looping
  JMP   forLoop

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
