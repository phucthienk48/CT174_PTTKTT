#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int w, v, qty;
    float ppu; // Giá tr? trên m?i don v? tr?ng lu?ng
    char name[25];    
} item;

void swap(item *a, item *b) {
    item temp = *a;
    *a = *b;
    *b = temp;
}

void sort(item *a, int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++)
            if(a[i].ppu < a[j].ppu)
                swap(&a[i], &a[j]);
}

void readFile(item **a, int *n, int *m) {
    FILE *f = fopen("CaiBalo1.txt", "r");
    if (f == NULL) {
        printf("Không th? m? t?p.\n");
        exit(1);
    }

    // C?p phát b? nh? cho m?ng a v?i kích thu?c ban d?u là 10
    *a = (item*)malloc(10 * sizeof(item));
    if (*a == NULL) {
        printf("L?i c?p phát b? nh?.\n");
        exit(1);
    }

    fscanf(f, "%d", m);
    int i = 0;
    while (fscanf(f, "%d %d %s", &(*a)[i].w, &(*a)[i].v, (*a)[i].name) == 3) {
        (*a)[i].ppu = (float)(*a)[i].v / (*a)[i].w;
        (*a)[i].qty = 0;
        i++;
        // Ki?m tra xem m?ng dã d?y chua, n?u d?y thì c?p phát thêm b? nh?
        if (i % 10 == 0) {
            *a = (item*)realloc(*a, (i + 10) * sizeof(item));
            if (*a == NULL) {
                printf("L?i c?p phát b? nh?.\n");
                exit(1);
            }
        }
    }

    *n = i;
    fclose(f);
}

void printChart(item *a, int n) {
    int total_val = 0, total_weight = 0;
    printf("|---|---------------------|-----------|-------|-------|---------|\n");
    printf("|%-3s|%-21s|%-11s|%-7s|%-7s|%-9s|\n", "STT", "     Tên d? v?t", "Tr?ng lu?ng", "Giá tr?", "Ðon giá", "Phuong án");
    printf("|---|---------------------|-----------|-------|-------|---------|\n");
    for(int i = 0, k = 1; i < n; i++) {        
        printf("| %-2d| %-20s|%11d|%7d|%7.2f|%9d|\n", k++, a[i].name, a[i].w, a[i].v, a[i].ppu, a[i].qty);
        total_val += a[i].v*a[i].qty;
        total_weight += a[i].w*a[i].qty;
    }	
    printf("|---|---------------------|-----------|-------|-------|---------|\n");	
    printf("Phuong án (theo th? t? ÐG gi?m d?n): X(");
    for(int i=0; i<n-1; i++){
        printf("%d,", a[i].qty);
    }	
    printf("%d)\n", a[n-1].qty);
    printf("T?ng tr?ng lu?ng = %5d\n", total_weight);
    printf("T?ng giá tr?     = %5d\n", total_val);
}

void greedy(item *a, int n, int m) {
    for(int i = 0; i < n; i++) {
        a[i].qty = m / a[i].w;
        m -= a[i].w*a[i].qty;
    }
}

int main() {
    int n = 0, m = 0;
    item *a;
    readFile(&a, &n, &m);
    sort(a, n);
    greedy(a, n, m);
    printChart(a, n);
    free(a);
    return 0;
}

