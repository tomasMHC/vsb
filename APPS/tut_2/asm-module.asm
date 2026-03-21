;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************

    bits 64

    section .data

    ; variables

    

;***************************************************************************

    section .text

    ; functions
    ;rdi, rsi, rdx, rcx, r8, r9

    global sude_max
sude_max:
    movsx rsi, esi                      ; N int -> long
    mov eax, 0x00000000                 ;min int
    mov rcx,0
.zpet:
    cmp rcx, rsi
    jge .hotovo
    
    test dword [ rdi + rcx *4], 1       ; sude ?
    jnz .skip
    cmp dword [rdi + rcx *4], eax  ;max?
    jle .skip
    mov eax, [rdi +rcx*4]

.skip:
    inc rcx
    jmp .zpet
.hotovo:
    ret

    global pocet_cislic
pocet_cislic:
    mov eax, 0
    mov rcx, 0
.zpet:
    cmp [rdi +rcx], byte 0
    je .hotovo
    cmp [rdi +rcx], byte '0'
    jl .skip
    cmp [rdi +rcx], byte '9'
    jg .skip
    inc eax
.skip:
    inc rcx
    jmp .zpet
.hotovo:
    ret

    global faktorial
faktorial:
    mov rax, 1
.zpet:
    cmp rdi, 1
    jle .hotovo

    imul rdi            ; rax *= rdi

    dec rdi
    jmp .zpet
.hotovo:
    ret

    global deleni_pole
deleni_pole:
    mov rcx, 0
    movsx r11, edx           ; delitel
    movsx rsi, esi          ; int -> long
.zpet:
    cmp rcx, rsi            ; i ? N
    jge .hotovo
    
    mov rax, [rdi + rcx  *8]    ; a = pole[i]
    cqo                         ; rax -> rax.rdx
    idiv r11 
    mov  [rdi +rcx * 8], rax    ; pole[i] = rax
    
    inc rcx
    jmp .zpet
.hotovo:
    ret
;rdi, rsi, rdx, rcx, r8, r9


    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret


