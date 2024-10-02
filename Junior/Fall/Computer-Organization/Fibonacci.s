        .data
n:      .word 10                  # Number of Fibonacci terms
fib0:   .word 0                   # First Fibonacci term (0)
fib1:   .word 1                   # Second Fibonacci term (1)

        .text
        .globl main
main:
        # Load number of terms from memory
        lw $t0, n                 # $t0 = n
        lw $t1, fib0              # $t1 = fib0 (0)
        lw $t2, fib1              # $t2 = fib1 (1)

        # Print the first two terms
        li $v0, 1                 # Syscall to print integer
        move $a0, $t1             # Print fib0
        syscall

        li $v0, 4                 # Syscall to print string (space between numbers)
        la $a0, space
        syscall

        li $v0, 1                 # Syscall to print integer
        move $a0, $t2             # Print fib1
        syscall

        li $v0, 4                 # Syscall to print string (space between numbers)
        la $a0, space
        syscall

        # Loop to print the rest of the series
        addi $t0, $t0, -2         # n = n - 2 (we already printed two terms)
fib_loop:
        beq $t0, $zero, end       # If n == 0, end the loop

        add $t3, $t1, $t2         # t3 = t1 + t2 (next Fibonacci number)
        move $t1, $t2             # t1 = t2 (shift terms)
        move $t2, $t3             # t2 = t3

        # Print the next Fibonacci number
        li $v0, 1                 # Syscall to print integer
        move $a0, $t3             # Print the next term
        syscall

        li $v0, 4                 # Syscall to print string (space between numbers)
        la $a0, space
        syscall

        addi $t0, $t0, -1         # n = n - 1
        j fib_loop                # Repeat loop

end:
        li $v0, 10                # Syscall to exit
        syscall

        .data
space:  .asciiz " "
