 .text
 .globl  __start
__start: 
    addiu $t0, $zero, 20	# load size = 20 to $t0 as an unsigned number;
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
    sw $s1, ($s6)         	# PassCnt = $s6 = $s1
    addi $t2, $zero, -1
    jal countArray      	# $ra = address of (countArray(testArray, size, -1))
    sw $s1, ($s7)         	# FailCnt = $s7 = $s1
    j exit
countArray: 
    addi $sp, $sp, -4
    sw $ra, ($sp)           # store instruction address
    add $t3, $zero, $t0     # $t3 = i = size
    addi $s1, $zero, 0      # $s1 = cnt = 0
loop: 
    addiu $s3, $zero, 1     # $s3 = 1
    sll $t4, $t3, 2         # $t4 = i * 4 - 4
    addi $t4, $t4, -4
    add $s2, $t4, $s0       # store address of testArray[i] in $s2(from size - 1 to 0)
    lw $s3, ($s2)           # $s3 = testArray[i]
    addi $sp, $sp, -4   
    sw $ra, ($sp)           # store instruction address
    beq $t2, $s3, Pass      # case (numElements == 1)
    sw $ra, ($sp)           # reload instruction address
    bne $t2, $s3, Fail      # default
    addi $t3, $t3, -1       # i--
    slt $s4, $zero, $t3     # i > 0
    beq $s4, $s3, loop
    lw $ra, 4($sp)
    jr $ra                  # back to main
Pass: 
    addiu $t5, $zero, 60
    slt, $s5, $s3, $t5      # if (testArray[i] >= 60) cnt++
    beq, $s5, $zero, add1
    lw $ra, ($sp)           # back to countArray
    jr $ra
Fail:   
    addiu $t5, $zero, 60
    slt $s5, $s3, $t5
    bne, $s5, $zero, add1   # if (testArray[i] < 60) cnt ++
    lw $ra, ($sp)
    jr $ra                  # back to countArray 
add1: 
    addiu $s3, $s3, 1
    lw $ra, ($sp)
    jr $ra                  # back to countArray
exit: 
    addiu $v0, $zero, 10
    syscall
