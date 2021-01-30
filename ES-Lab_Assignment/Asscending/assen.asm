	AREA accend,CODE,READONLY
	ENTRY
MAIN
	LDR R0,=VALUE
	LDR R6,=VALUE
	MOV R1,#05
	MOV R7,R1
	LDR R2,[R6],#04
	ldr r4,value1
LOOP
	LDR R3,[R0]
	CMP R2,R3
	BHI OUTER
	SUB R1,R1,#01
	CMP R1,#00
	BNE LOOP
	SUB R7,R7,#01
	MOV R0,R6
	MOV R1,R7
	STR R2,[R4],#04
	LDR R2,[R6],#04
	CMP R7,#00
	BNE LOOP
OUTER
	MOV R2,R5
	MOV R3,R2
	MOV R5,R3
	CMP R1,#00
	BNE LOOP
STOP	B STOP
VALUE	DCD &40000000
value1	dcd &4000f000

	END

;pgm to find the asending oredr number
	
	
	
		