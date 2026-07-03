#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

short int arr[SIZE];
char format[] = "%hd";
char format1[] = "%hd\t";

int main() {

    for (int i = 0; i < SIZE; i++) {
        short int* p = &arr[i];
        __asm {
            mov esi, p
            lea eax, format
            push esi
            push eax
            call scanf
            add esp, 8
        }
    }
    printf("\n");

    short int min_val = arr[0], max_val = arr[0];
    int min_idx = 0, max_idx = 0, min_idxtwo = 0;

    __asm {
        lea esi, arr
        mov ecx, SIZE
        xor edi, edi

        find_min_max :
        mov ax, word ptr[esi + edi * 2]

            cmp ax, min_val
            jge skip_min
            mov min_val, ax
            mov min_idx, edi
            skip_min :

        cmp ax, max_val
            jle skip_max
            mov max_val, ax
            mov max_idx, edi
            skip_max :

        inc edi
            loop find_min_max
    }

    if (min_idx > max_idx) {
        int temp = min_idx;
        min_idx = max_idx;
        max_idx = temp;
    }

    if (min_idx + 1 < max_idx) {
        min_idxtwo = min_idx * 2;
        __asm {
            lea edi, arr
            add edi, min_idxtwo
            mov ecx, max_idx
            sub ecx, min_idx
            dec ecx

            add edi, 2

            zero_loop:
            mov word ptr[edi], 0
                add edi, 2    
                loop zero_loop
        }
    }

    for (int i = 0; i < SIZE; i++) {
        __asm {
            mov ebx, i
            shl ebx, 1             
            mov ax, word ptr[arr + ebx]
            push eax
            lea eax, format1
            push eax
            call printf
            add esp, 8
        }
    }

    return 0;
}
