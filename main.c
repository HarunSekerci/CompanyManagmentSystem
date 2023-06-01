#include <stdio.h>
#include <stdlib.h>

typedef struct Company {
    int vergiNo;
    char firmaAdi[20];
    char faaliyet[20];
    struct Company *sonraki;
} Com;

Com *kok = NULL, *ptr = NULL, *gecici = NULL, *son;

Com *ekleme(Com *buffer, int number) {
    if (kok == NULL) {
        kok = (Com*) malloc(sizeof (Com));
        kok->vergiNo = number;
        printf("Firma ismini giriniz:");
        scanf("%s", kok->firmaAdi);
        printf("Firma Faaliyet Alanini Giriniz:");
        scanf("%s", kok->faaliyet);
        kok->sonraki = NULL;
        ptr = kok;
        son = kok;
        printf("\n");
    } else {
        ptr->sonraki = (Com*) malloc(sizeof (Com));
        ptr = ptr->sonraki;
        ptr->vergiNo = number;
        printf("Firma ismini giriniz:");
        scanf("%s", &ptr->firmaAdi);
        printf("Firma Faaliyet Alanini Giriniz:");
        scanf("%s", &ptr->faaliyet);
        ptr->sonraki = NULL;
        son = ptr;
        printf("\n");
    }
}

int verginoKontrol(Com *y, int num) {
    while (y != NULL) {
        if (y->vergiNo == num) {
            return 1;
        }
        y = y->sonraki;
    }
    return 0;
}

void firmaListele() {
    int kontrol = 0;
    Com *y = kok;
    while (y != NULL) {
        kontrol = 1;
        printf("Firma ismi:%s\nVergi Numarasi:%d\nFaaliyet Alani:%s\n", y->firmaAdi, y->vergiNo, y->faaliyet);
        y = y->sonraki;
    }
    if (kontrol == 0) {
        printf("Listeleme yapmak icin en az bir tane firma eklemeniz gerekir.\n");
    }
}

void firmaSilme() {
    int kontrol = 0;
    Com *gecici = kok, *silGecici;
    int sil;
    printf("Silmek istediginiz firmanin vergi numarasini giriniz:");
    scanf("%d", &sil);
    if (kok->vergiNo == sil) {
        silGecici = kok;
        kok = kok->sonraki;
        free(silGecici);
        kontrol = 1;
    } else {
        while (gecici->sonraki != NULL) {
            if (gecici->sonraki->vergiNo == sil) {
                kontrol = 1;
                silGecici = gecici->sonraki;
                if (silGecici == son)
                    son = gecici;
                gecici->sonraki = silGecici->sonraki;
                free(silGecici);
                break;
            }
            gecici = gecici->sonraki;
        }
    }
    if (kontrol == 0) printf("Silmek istenilen vergi numarasina ait bir firma yoktur.\n");
    else printf("%d vergi numarali firma silinmistir.\n", sil);
}

void firmaDuzenleme() {
    Com *gecici = kok;
    int duzenle, kontrol = 0, secim;
    printf("Duzenlemek istediginiz firmanin vergi numarasini giriniz:");
    scanf("%d", &duzenle);
    while (gecici != NULL) {
        if (gecici->vergiNo == duzenle) {
            printf("Duzenlemek istediginiz firma ozelligini belirtiniz.\n");
            printf("Firma adi --> 1\nVergi Numarasi -->2\nFaaliyet Alani -->3\n");
            scanf("%d", &secim);
            switch (secim) {
                case 1:
                    printf("Yeni Firma adini giriniz:");
                    scanf("%s", gecici->firmaAdi);
                    kontrol = 1;
                    break;
                case 2:
                    printf("Yeni firma faaliyet alanini giriniz:");
                    scanf("%s", gecici->faaliyet);
                    kontrol = 1;
                    break;
                case 3:
                    printf("Firma vergi numarasi:");
                    scanf("%d", &gecici->vergiNo);
                    kontrol = 1;
                    break;
            }
        }
        gecici = gecici->sonraki;
    }
    if (kontrol == 0) printf("Firma sistemde kayitli degildir.");
    else printf("Duzenleme islemi basarili\n");
}

int main(int argc, char** argv) {
    int sayi, secim;
    while (1) {
        printf("Firma Ekleme---> 1\nFirma Duzenleme ---> 2\nFirma Silme --> 3\nFirma Listeleme --> 4\nCikis --> 5\n");
        scanf("%d", &secim);
        system("CLS");
        switch (secim) {
            case 1:
                printf("Firma Vergi Numarasini Giriniz:");
                scanf("%d", &sayi);
                if (verginoKontrol(kok, sayi) == 0) {
                    ekleme(gecici, sayi);
                } else {
                    printf("\nAyni vergi numarali bir firma bulunmaktadir.\n\n");
                }
                break;
            case 5:
                exit(0);
                break;
            case 4:
                firmaListele();
                break;
            case 3:
                firmaSilme();
                break;
            case 2:
                firmaDuzenleme();
        }
    }
    return (EXIT_SUCCESS);
}
