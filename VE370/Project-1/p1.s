 .text
 .globl  __start
__start: 
    addi $sp, $sp, -88
    addiu $t0, $zero, 20	# load size = 20 to $t0 as an unsigned number;
    addiu $s0, $sp, 8
    addi $t1, $zero, 55
    sw $t1, 0($s0)
    addi $t1, $zero, 83
    sw $t1, 4($s0)
    addi $t1, $zero, 18
    sw $t1, 8($s0)
    addi $t1, $zero, 69
    sw $t1, 12($s0)
    addi $t1, $zero, 96
    sw $t1, 16($s0)
    addi $t1, $zero, 80
    sw $t1, 20($s0)
    addi $t1, $zero, 59
    sw $t1, 24($s0)
    addi $t1, $zero, 72
    sw $t1, 28($s0)
    addi $t1, $zero, 50
    sw $t1, 32($s0)
    addi $t1, $zero, 61
    sw $t1, 36($s0)
    addi $t1, $zero, 54
    sw $t1, 40($s0)
    addi $t1, $zero, 94
    sw $t1, 44($s0)
    addi $t1, $zero, 32
    sw $t1, 48($s0)
    addi $t1, $zero, 21
    sw $t1, 52($s0)
    addi $t1, $zero, 29
    sw $t1, 56($s0)
    addi $t1, $zero, 73
    sw $t1, 60($s0)
    addi $t1, $zero, 100
    sw $t1, 64($s0)
    addi $t1, $zero, 86
    sw $t1, 68($s0)
    addi $t1, $zero, 62
    sw $t1, 72($s0)
    addi $t1, $zero, 42
    sw $t1, 76($s0)
    # testarray = [55, 83, 18, 69, 96, 80, 59, 72, 50, 61, 54, 94, 32, 21, 29, 73, 100, 86, 62, 42]
    # load testarray in $s0
    addi $t2, $zero, 1
    jal countArray       	# $ra = address of (countArray(testArray, size, 1))
    add $t1, $zero, $t1		
    add $t6, $zero, $s1     	# PassCnt = $t6 = $s1
    addi $t2, $zero, -1
    jal countArray      	# $ra = address of (countArray(testArray, size, -1))
    add $t1, $zero, $t1
    add $t7, $zero, $s1     	# FailCnt = $t7 = $s1
    j exit
countArray: 
    add $t1, $0, $t1
    add $t3, $zero, $t0     	# $t3 = i = size
    addi $s1, $zero, 0      	# $s1 = cnt = 0
    addi $s3, $zero, 1      	# $s3 = 1
    addi $t5, $zero, 60		# $t5 = 60
loop: 
    sll $t4, $t3, 2         	# $t4 = i * 4 - 4
    addi $t4, $t4, -4
    add $s2, $t4, $s0       	# store address of testArray[i] in $s2(from size - 1 to 0)
    lw $s5, ($s2)           	# $s5 = testArray[i]
    bne $t2, $s3, Fail      	# default, else into Pass
    slt $s4, $s5, $t5     
    beq $s4, $zero, add1	# if (testArray[i] >= 60)
    j judge_i               
Fail:
    slt $s4, $s5, $t5
    bne $s4, $zero, add1   	# if (testArray[i] < 60)
    j judge_i
    add $t1, $zero, $t1
add1:
    addiu $s1, $s1, 1		# cnt++
judge_i:
    addi $t3, $t3, -1       	# i--
    slt $s4, $zero, $t3     	# i > 0
    beq $s4, $s3, loop
    jr $ra  
exit: 
    addiu $v0, $zero, 10
    syscall
