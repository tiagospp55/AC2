     .equ STR_MAX_SIZE, 20
        .equ printStr, 8
        .equ readStr, 9
        .equ printInt, 6
        .equ printInt10, 7
        .data
s1:     .asciiz "Introduza 2 strings: "
s2:     .asciiz "Resultados: "
s3:		.asciiz "\n"
s4:		.asciiz " "
str1:   .space 21                       # char str1[STR_MAX_SIZE + 1]
str2:   .space 21                       # char str2[STR_MAX_SIZE + 1]
str3:   .space 41                       # char str3[2 * STR_MAX_SIZE + 1]
        .text
        .globl main
main: 

    addiu $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)

    li $v0, PrintStr
    la $a0, s1
    syscall

    la $a0, str1
    li $a1, STR_MAX_SIZE
    li $v0, readStr
    syscall

    la $a0, str2
    li $a1, STR_MAX_SIZE
    li $v0, readStr
    syscall

    jr $ra

strlen:
endstrlen:
    jr $ra