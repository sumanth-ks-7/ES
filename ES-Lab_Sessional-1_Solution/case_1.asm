;
	AREA RESET, CODE, READONLY
	ENTRY
START
	mov r0, #0x40000000		;Array counter
	mov r5, #0x40000004		;Starting of array
	mov r4, #0x40000030		;Final answer
	mov r11, #0x40000034	;Max num of array
	mov r12, #0x40000038	;Min num of array

	mov r1, #00				;Init counter to zero
	mov r6, #00				;Init Accumulator to zero
	mov r7, #00				;min
	mov r8, #00				;max

	;Addition of array elements
loop
	ldr r2, [r5]			;Loading the array elements to reg R2
	adc r6, r6, r2			;Accumulating the array elements in reg R6
	cmp r2, #00				;Exit the loop if reg R2 is equal to zero
	beq exit				;Comparing ZERO with array elements 								   
	addne r5, r5, #04		;If cmp is not equal to zero than increament mem address
	addne r1, r1, #01		;If cmp is not equal to zero than increament counter
	bne loop

exit	
	str r1, [r0]		   	;Store the counter value to 0x40000000
	str r6, [r4]			;Store the final answer to 0x40000030

here	
	bal here

	END