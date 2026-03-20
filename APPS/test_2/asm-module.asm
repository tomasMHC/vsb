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
    ;rdi, rsi, rfdx, rcx, r8, r9

    global max_prvocislo
max_prvocislo:
    mov ecx, 0          ; index
    mov r11d, 0          ; max prvocislo

.dalsi:
    cmp ecx, esi        ; index ? N
    jge .hotovo          ; index >= N -> hotovo
    mov ebx, 2
    mov eax, dword [rdi + rcx*4]

.zpet:
    cmp ebx, eax        ; delitel ? num
    jge .je_prvocislo          ; delitel >= num -> hotovo

    mov edx, 0          ; rdx:rax / rbx -> zbytek
    mov eax, dword [rdi + rcx*4]
    cqo                 ; rax -> rax.rdx
    idiv ebx
    cmp edx, 0          ; zbytek ? 0
    je .neni_prvocislo   ; zbytek == 0 -> neni prvocislo
    inc ebx             ; delitel++
    jmp .zpet

.neni_prvocislo:
    inc ecx
    jmp .dalsi

.je_prvocislo:
    mov r11d, dword [rdi + rcx*4]
    cmp r11d, eax
    jle .dalsi
    mov eax, r11d
    inc ecx
    jmp .dalsi

.hotovo:
    ret

; 3. Urci poziciu najdlhsej sekvencie medzier v retazci, vrati index prveho znaku tej sekvencie.

; global longest_number
; longest_number:
;     xor eax, eax        ; max_len = 0
;     xor edx, edx        ; max_pos = 0
;     xor r8d, r8d        ; cur_len = 0
;     xor r9d, r9d        ; cur_pos = 0
;     xor ecx, ecx        ; index = 0

; .zpet:
;     mov bl, [rdi + rcx]
;     cmp bl, 0
;     je .end

;     cmp bl, '0'
;     jl .neni_cislo
;     cmp bl, '9'
;     jg .neni_cislo

;     cmp r8d, 0
;     jne .cislo
;     mov r9d, ecx

; .cislo:
;     inc r8d
;     inc ecx
;     jmp .zpet

; .neni_cislo:
;     cmp r8d, eax
;     jle .reset
;     mov eax, r8d
;     mov edx, r9d

; .reset:
;     xor r8d, r8d
;     inc ecx
;     jmp .zpet

; .end:
;     cmp r8d, eax
;     jle .hotovo
;     mov edx, r8d
;     mov eax, r9d

; .hotovo:
;     ret


global longest_number
longest_number:
    xor eax, eax        ; max_value = 0
    xor r8d, r8d        ; cur_len = 0
    xor r9d, r9d        ; cur_value = 0
    xor ecx, ecx        ; index = 0

.loop:
    mov bl, [rdi + rcx]
    cmp bl, 0
    je .end

    ; je číslice?
    cmp bl, '0'
    jl .not_digit
    cmp bl, '9'
    jg .not_digit

    ; přidat číslici do cur_value
    sub bl, '0'         ; bl = číslice 0–9
    imul r9d, 10    ; cur_value *= 10
    add r9d, ebx         ; cur_value += digit
    inc r8d             ; cur_len++
    inc ecx
    jmp .loop

.not_digit:
    ; porovnat hodnotu s max_value
    cmp r9d, eax
    jle .reset
    mov eax, r9d        ; max_value = cur_value

.reset:
    xor r8d, r8d        ; cur_len = 0
    xor r9d, r9d        ; cur_value = 0
    inc ecx
    jmp .loop

.end:
    ; konec řetězce – ještě jednou porovnat
    cmp r9d, eax
    jle .finish
    mov eax, r9d

.finish:
    ret
