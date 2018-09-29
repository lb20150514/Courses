# VE370_Project_1.s
# Count specific elements in the integer array A[] whose 
#   size is numElements and return the following: 

#   1. When cntType = 1, count the elements greater than 
#       or equal to 60.
#   2. When cntType = -1, count the elements less than 60.
#---------------------------------------------------------
.data
size:       .word   20
testarray:  .word   55, 83, 18, 69, 96
            .word   80, 69, 72, 50, 61
            .word   54, 94, 32, 21, 29
            .word   73, 100, 86, 62, 42

#---------------------------------------------------------
.text
.globl  main
.ent    main
main:
    la $t0, testarray   # load address of testArray[20] to $t0;
    lw $t1, size        # load value of size to $t1;
    li $s1, 1
    addi $sp, $sp, -4   # adjust stack for 1 items
    sw $ra, ($sp)       #   store instruction address to ($sp)
    j countArray        # $ra = countArray(testArray, size, 1)
    sw $v0, $s2         # PassCnt = $v0 = $s2
    li $s1, -1
    sw $ra, ($sp)
    j countArray        # $ra = countArray(testArray, size, -1)
    sw $v1, $s2         # FailCnt = $v1 = $s2
    j exit
countArray: 
    addi $t2, $t1, -1   # $t2 = i = size - 1
    lw $s2, $zero       # $s2 = cnt = 0
loop: 
    li $t3, 1
    add $s3, $t2, $t0   # address of testArray[i] in $s3
    lbu $s4, 0($s3)     # $s4 = testArray[i]
    addi $sp, $sp, -4   #   store instruction address to -4($sp)
    sw $ra, ($sp)
    beq $s1, $t3, Pass  # case (numElements == 1)
    sw $ra, ($sp)       #   reload instruction address to -4($sp)
    bne $s1, $t3, Fail  # default
    addi $t2, $t2, -1   # i--
    bgt $t2, $zero, loop# i > 0
    lw $ra 4($sp)
    jr $ra              # back to main
Pass: 
    li $t4, 60
    sw $ra, -4($sp)     #   store instruction address to -8($sp)
    bge $s4, $t4, add1
    lw $ra, ($sp)       # back to loop
    jr $ra
Fail:   
    li $t4, 60
    sw $ra, -4($sp)
    blt $s4, $t4, add1
    lw $ra, ($sp)
    jr $ra
add1: 
    addi $s2, $s2, 1
    lw $ra, -4($sp)
    jr $ra              # back to Pass/Fail
exit: 
    li $v0, 10
    syscall
.end main


