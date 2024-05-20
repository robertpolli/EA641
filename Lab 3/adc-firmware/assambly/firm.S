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
    CBI   DDRB, 0            ; Input - OC
    SBI   DDRB, 1            ; Output - SH
    SBI   DDRB, 2            ; Output - EOC
    SBI   DDRB, 3            ; Output - START
    
    RET                       ;return to setup() function
;---------------------------------------------------------------------------

writeValue:
  OUT  PORTD, r24             ; Write value to port D

  LDI   r30, 0xea             ;
  CLR   r31                   ;
                              ;
valWritten:                   ;
  DEC   r30                   ;
  CPSE  r30, r31              ;
  JMP   valWritten            ; Delay
    
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
  JMP   retSample           ; Delay
  
  CBI   PORTB, 1            ; Hold
  
  RET
;---------------------------------------------------------------------------

converter:

  LDI r24, 0x80             ; Armazena 0b10000000 
  LDI r26, 0x07             ; Armazena o numero de interacoes do looping
  LDI r20, 0x40             ; Armazena o bit de step

  CLR   r31
  
forLoop:

  CALL writeValue              ; Escreve r24 na saida 

  IN r28, PINB 
  ANDI r28, 0x01               ; Isola apenas o bit 0 do registrador
  
  ;; ---- IF ----
  SBRC r28, 0                  ; SE OC=1
  OR r24, r20                  ; Set o bit na posição apontada por r20  
  ;; ------------

  CPSE r28, r31 
  JMP retLoop
  ;; ---- ELSE ----
  LSL r20
  
  MOVW r22, r20
  NEG r22
  DEC r22 
  AND r24,r22
 
  LSR r20
  OR r24, r20
  ;; -------------- 
retLoop:
  LSR r20        
  
  DEC  r26                  ; Decrementa o Bit Location
  CPSE r26, r31             ; Sai d o looping
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
