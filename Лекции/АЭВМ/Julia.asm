﻿dseg segment
	s	db	'swap first and second word*$'	;изначальная строка
	lf	db	13,10,'$'
	len_1 dw 0
	len_2 dw 0
	s1 db '         '						;используем две строки
	s2 db '         '						;для хранения первого и второго слова
dseg ends

cseg segment
	assume cs:cseg, ds:dseg
start:	mov ax,dseg
		mov ds,ax
		
		mov ah, 9		;выведем изначальную строку
		lea dx, s
		int 21h
		lea dx, lf
		int 21h


	;составляем первую строку-----------------------------------------
		mov si, 0
	count_1:
		mov dl, s[si]	;положим очередной символ в dl
		mov s1[si], dl	;и переложим его в s1
		inc si			;увеличим si
		cmp s[si], ' '	;если слово ещё не закончилось,
		jne count_1		;продолжаем

		mov len_1, si	;дошли до пробела, запомним длину первого слова
	;------------------------------------------------------------------

		inc si			;перешагнём пробел
	
	;составляем вторую строку------------------------------------------
	count_2:
		mov dl, s[si]	;положим очередной символ в dl
		sub si, len_1	;переведём si из индекса s в индекс s2
		sub si, 1
		mov s2[si], dl	;переложим очередной символ в s2
		add si, 1		;вернём si обратно
		add si, len_1

		inc len_2			;увеличим счётчик длины второго слова
		inc si				;увеличим si
		cmp s[si], ' '		;если текущий символ не пробел
		je start_swapping
		cmp s[si], '*'		;и не '*',
		je start_swapping	;то завершаем итерации
		jmp count_2			;иначе продолжаем составлять второе слово
	;------------------------------------------------------------------

	start_swapping:
		mov si, 0				;обнулим si

	;выставляем второе слово на первую позицию----------------------------
	put_second_to_first:
		mov dl, s2[si]			;положим очередной символ в dl
		mov s[si], dl			;и переложим его в s
		inc si					;увеличим si
		cmp si, len_2			;если слово ещё не закончилось,
		jne put_second_to_first	;продолжаем
    
		mov s[si], ' '			;слово закончилось, выставляем пробел
		inc si					;и перешагиваем через него
	;------------------------------------------------------------------
    
	
	;выставляем первое слово на вторую позицию-------------------------
		mov bx, 0				;будем хранить в bx индекс символа в s1
	put_first_to_second:
		mov dl, s1[bx]			;положим очередной символ в dl
		mov s[si], dl			;и переложим его в s
		inc si					;увеличим si
		inc bx					;увеличим bi
		cmp bx, len_1			;если слово ещё не закончилось,
		jne put_first_to_second	;продолжаем
	;------------------------------------------------------------------

		mov ah, 9				;выводим изменённую строку s
		lea dx, s
		int 21h
	
		mov ax, 4C00h			;завершаем программу
		int 21h
	cseg ends
end start