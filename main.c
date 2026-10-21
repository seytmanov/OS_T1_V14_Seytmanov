#include <stdio.h>

#define MAX 100

// Massiv o'sish tartibida saralanganligini tekshirish funksiyasi
int saralanganmi(const int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            return 0; // Saralanmagan
        }
    }
    return 1; // Saralangan
}

// 1-masala: Oddiy ikkilik qidiruv va qadamlar sonini hisoblash
int ikkilik_qidiruv(const int a[], int n, int x, int *qadamlar) {
    int chap = 0, ong = n - 1;
    *qadamlar = 0;

    while (chap <= ong) {
        (*qadamlar)++;
        int orta = chap + (ong - chap) / 2;

        if (a[orta] == x) {
            return orta; // Topilgan indeks
        } else if (a[orta] < x) {
            chap = orta + 1;
        } else {
            ong = orta - 1;
        }
    }
    return -1; // Topilmadi
}

// 2-masala: Pointer qaytaruvchi ikkilik qidiruv funksiyasi
int *qidir(int *a, int n, int x) {
    int chap = 0, ong = n - 1;

    while (chap <= ong) {
        int orta = chap + (ong - chap) / 2;
        int *joriy = a + orta; // Pointer arifmetikasi

        if (*joriy == x) {
            return joriy; // Topilgan elementga pointer qaytariladi
        } else if (*joriy < x) {
            chap = orta + 1;
        } else {
            ong = orta - 1;
        }
    }
    return NULL; // Topilmasa NULL qaytariladi
}

int main(void) {
    int a[MAX];
    int n, x;

    printf("Massiv o'lchamini kiriting (1 dan %d gacha): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Xatolik: Massiv o'lchami noto'g'ri kiritildi!\n");
        return 1;
    }

    printf("%d ta butun sonni O'SISH tartibida kiriting:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("Xatolik: Butun son o'rniga noto'g'ri belgi kiritildi!\n");
            return 1;
        }
    }

    // Massiv saralanganligini tekshirish
    if (!saralanganmi(a, n)) {
        printf("Xatolik: Kiritilgan massiv saralanmagan! Ikkilik qidiruv uchun massiv saralangan bo'lishi shart.\n");
        return 1;
    }

    printf("Qidirilayotgan sonni kiriting (x): ");
    if (scanf("%d", &x) != 1) {
        printf("Xatolik: Qidirilayotgan qiymat butun son bo'lishi kerak!\n");
        return 1;
    }

    // --- 1-MASALA NATIJASI ---
    int qadamlar = 0;
    int indeks1 = ikkilik_qidiruv(a, n, x, &qadamlar);

    printf("\n--- 1-masala: C asoslari (Ikkilik qidiruv) ---\n");
    printf("Qidiruv qadamlari soni: %d\n", qadamlar);
    if (indeks1 != -1) {
        printf("Natija: %d soni %d-indeksda topildi.\n", x, indeks1);
    } else {
        printf("Natija: %d soni massivdan topilmadi.\n", x);
    }

    // --- 2-MASALA NATIJASI ---
    printf("\n--- 2-masala: Pointerlar yordamida qidiruv ---\n");
    printf("Massiv boshlang'ich manzili (a): %p\n", (void *)a);

    int *p = qidir(a, n, x);
    if (p != NULL) {
        long indeks2 = p - a; // Pointerlar ayirmasi orqali indeksni topish
        printf("Topilgan element manzili (p):   %p\n", (void *)p);
        printf("Pointer orqali qiymat (*p):     %d\n", *p);
        printf("Pointerlar ayirmasi (p - a):    %ld-indeks\n", indeks2);
    } else {
        printf("Funksiya NULL qaytardi (%p): %d soni massivda mavjud emas.\n", (void *)p, x);
    }

    return 0;
}