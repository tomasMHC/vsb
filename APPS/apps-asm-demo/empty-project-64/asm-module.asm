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

    ;global g_some_asm_var
    ;extern g_some_c_var
    extern g_int_a, g_int_b, g_int_max
    extern g_str, g_str_len
    extern g_long_pole, g_suma

;g_some_asm_var dd ?

;***************************************************************************

    section .text

    ; functions
    global my_strlen
my_strlen:
    ; while (str[len] != '\n' ) len++

    mov rcx, 0
.zpet
    cmp byte [g_str + rcx * 1], 0
    je .hotovo
    inc rcx
    jmp .zpet
.hotovo
    mov [g_str_len], ecx
    ret

    global my_max
my_max:
    mov eax, [g_int_a] 
    cmp eax, [g_int_b]
    jg .taknic
    mov eax, [g_int_b]
.taknic:
    mov [g_int_max], eax
    ret

    global my_suma
my_suma:
    mov rcx, 0
.zpet
    cmp rcx, 10
    jge .hotovo

    add rax, [ g_long_pole + rcx * 8]
    inc rcx             
    jmp .zpet
.hotovo
mov [g_suma] , rax
    ret

    global my_asm_function
my_asm_function:
    mov eax, [g_int_a]
    mov ecx, [g_int_b]
    mov [g_int_b], eax
    mov [g_int_a], ecx

    mov al, ','
    mov [g_str + 5 ], al
    mov byte [g_str + 11] , ' '

    ret

    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret


