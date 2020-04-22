
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame



        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here
        ; TRUE FOR TESTS mov rax, 1

         mov rax,rdx
                mov rdx, 0
                imul rax,rsi
                add rax,rcx

                mov rsi, 8
                idiv rsi
                add rdi, rax

                mov rsi, 1
                mov rbx, 7
                sub rbx, rdx
                mov rcx, rbx
                sal rsi, cl
                mov rax, rdi
              ;  or [rax], rsi

                mov rsp, rbp
                pop rbp

                ret

                mov rax, 1


        mov rsp, rbp
        pop rbp
        ret




get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here - for now returning 0

        mov rax, rdx
                mov rdx, 0
                imul rax, rsi
                add rax, rcx

                mov rsi, 8
                idiv rsi
                add rdi, rax

                mov rsi, 1
                mov rbx, 7
                sub rbx, rdx
                mov rcx, rbx
                sal rsi, cl


                mov rax, rdi
                ;and [rax], rsi


                setg al
                movsx rax, al


                mov rax, 1


        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax

