
	AREA  RESET ,CODE ,READONLY
	ENTRY
MAIN
	    MOV R8,#9;
		LDR	R1,=Value1 ;
		MOV R5,#0x4000001C;
		LDR R2,[R1];
LOOP1	ADD R1,R1,#4;
 		LDR R3,[R1];
		ADD R2,R2,R3;
		SUBS R8,#1;
		CMP R8,#00;
		BNE LOOP1;
DONE 
	 	STR R2,[R5];
STOP    B STOP

Value1  DCD  &01,&02,&03,&04,&05,&06,&07,&08,&09,&10;


		END