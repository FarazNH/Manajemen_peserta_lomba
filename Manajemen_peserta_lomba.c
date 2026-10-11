#include <stdio.h>
#include <string.h>


typedef struct {
    int id;
    char nama[50];
    char kategori[30];
    float kreativitas;
    float teknis;
    float penampilan;
    float nilaiAkhir;
} Peserta;


float wKreativitas = 0;
float wTeknis      = 0;
float wPenampilan  = 0;


int  inputPeserta(Peserta p[], int *n);
int  tampilPeserta(Peserta p[], int n);
int  cariPesertaIndex(Peserta p[], int n, int idCari);
int  updatePeserta(Peserta p[], int n);
int  hapusPeserta(Peserta p[], int *n);

int  aturBobotPenilaian();
float hitungNilaiAkhir(float k, float t, float p);
int  hitungSemuaNilai(Peserta arr[], int n);
int  urutkanPeserta(Peserta arr[], int n);
int  statistikNilai(Peserta arr[], int n, float *min, float *max, float *rata);

int  inputKategoriValid(char kategori[], int maxLen);


int main() {
    Peserta data[100];
    int n = 0;
    int pilih, idCari;

    do {
        printf("\n==============================================\n");
        printf("      PROGRAM MANAJEMEN DATA PESERTA LOMBA\n");
        printf("==============================================\n");
        printf("1. Input Data Peserta\n");
        printf("2. Tampilkan Data Peserta\n");
        printf("3. Update Data Peserta\n");
        printf("4. Hapus Data Peserta\n");
        printf("5. Hitung Nilai Akhir Peserta\n");
        printf("6. Urutkan Peserta & Tampilkan Juara\n");
        printf("7. Statistik Nilai Peserta\n");
        printf("8. Cari Peserta (berdasarkan ID)\n");
        printf("9. Atur Bobot Penilaian\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                inputPeserta(data, &n);
                break;

            case 2:
                tampilPeserta(data, n);
                break;

            case 3:
                updatePeserta(data, n);
                break;

            case 4:
                hapusPeserta(data, &n);
                break;

            case 5:
                if (hitungSemuaNilai(data, n)) {
                    printf("\nHASIL PERHITUNGAN NILAI AKHIR:\n");
                    tampilPeserta(data, n);
                }
                break;

            case 6:
                if (urutkanPeserta(data, n)) {
                    printf("\nDATA SETELAH DIURUTKAN BERDASARKAN NILAI AKHIR:\n");
                    tampilPeserta(data, n);

                    printf("\n=== JUARA LOMBA ===\n");
                    if (n >= 1) printf("Juara 1 : %s (%.2f)\n", data[0].nama, data[0].nilaiAkhir);
                    if (n >= 2) printf("Juara 2 : %s (%.2f)\n", data[1].nama, data[1].nilaiAkhir);
                    if (n >= 3) printf("Juara 3 : %s (%.2f)\n", data[2].nama, data[2].nilaiAkhir);
                }
                break;

            case 7: {
                float min, max, rata;
                if (statistikNilai(data, n, &min, &max, &rata)) {
                    printf("\nSTATISTIK NILAI PESERTA:\n");
                    printf("Nilai Tertinggi : %.2f\n", max);
                    printf("Nilai Terendah  : %.2f\n", min);
                    printf("Rata-rata       : %.2f\n", rata);
                }
                break;
            }

            case 8:
                if (n == 0) {
                    printf("Belum ada data peserta.\n");
                } else {
                    printf("Masukkan ID peserta yang dicari: ");
                    scanf("%d", &idCari);

                    int pos = cariPesertaIndex(data, n, idCari);
                    if (pos == -1) {
                        printf("Peserta dengan ID %d tidak ditemukan.\n", idCari);
                    } else {
                        printf("\nDATA PESERTA DITEMUKAN:\n");
                        printf("ID          : %d\n", data[pos].id);
                        printf("Nama        : %s\n", data[pos].nama);
                        printf("Kategori    : %s\n", data[pos].kategori);
                        printf("Kreativitas : %.2f\n", data[pos].kreativitas);
                        printf("Teknis      : %.2f\n", data[pos].teknis);
                        printf("Penampilan  : %.2f\n", data[pos].penampilan);
                        printf("Nilai Akhir : %.2f\n", data[pos].nilaiAkhir);
                    }
                }
                break;

            case 9:
                aturBobotPenilaian();
                break;

            case 0:
                printf("Keluar program...\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilih != 0);

    return 0;
}


int inputKategoriValid(char kategori[], int maxLen) {
    int valid;
    do {
        valid = 1;

        printf("Kategori (Lagu / Puisi / Tari Tradisional / Pidato): ");
        scanf(" %29[^\n]", kategori);

        if (strcmp(kategori, "Lagu") != 0 &&
            strcmp(kategori, "Puisi") != 0 &&
            strcmp(kategori, "Tari Tradisional") != 0 &&
            strcmp(kategori, "Pidato") != 0) {

            printf("Kategori tidak terdaftar. Silakan masukkan ulang.\n");
            valid = 0;
        }

    } while (!valid);

    return 1;
}


int inputPeserta(Peserta p[], int *n) {
    int tambah;

    printf("Jumlah peserta yang ingin ditambah: ");
    scanf("%d", &tambah);

    if (*n + tambah > 100) {
        printf("Data melebihi kapasitas maksimum (100 peserta).\n");
        return 0;
    }

    for (int i = *n; i < *n + tambah; i++) {
        printf("\nPeserta ke-%d\n", i + 1);

        printf("ID Peserta        : ");
        scanf("%d", &p[i].id);

        printf("Nama Peserta      : ");
        scanf(" %49[^\n]", p[i].nama);

        inputKategoriValid(p[i].kategori, 30);

        printf("Nilai Kreativitas (0-100): ");
        scanf("%f", &p[i].kreativitas);

        printf("Nilai Teknis (0-100): ");
        scanf("%f", &p[i].teknis);

        printf("Nilai Penampilan (0-100): ");
        scanf("%f", &p[i].penampilan);

        p[i].nilaiAkhir = 0;
    }

    *n += tambah;
    printf("%d data peserta berhasil ditambahkan.\n", tambah);
    return 1;
}


int tampilPeserta(Peserta p[], int n) {
    if (n == 0) {
        printf("Belum ada data peserta.\n");
        return 0;
    }

    printf("\n====================================================================================\n");
    printf("No  ID    Nama                 Kategori               Kr    Tk    Pn   NilaiAkhir\n");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-3d %-5d %-20s %-20s %-5.2f %-5.2f %-5.2f %-10.2f\n",
               i + 1,
               p[i].id,
               p[i].nama,
               p[i].kategori,
               p[i].kreativitas,
               p[i].teknis,
               p[i].penampilan,
               p[i].nilaiAkhir);
    }

    printf("====================================================================================\n");
    return 1;
}



int cariPesertaIndex(Peserta p[], int n, int idCari) {
    for (int i = 0; i < n; i++) {
        if (p[i].id == idCari) return i;
    }
    return -1;
}


int updatePeserta(Peserta p[], int n) {
    if (n == 0) {
        printf("Belum ada data peserta.\n");
        return 0;
    }

    int idUbah;
    printf("Masukkan ID peserta yang akan diubah: ");
    scanf("%d", &idUbah);

    int pos = cariPesertaIndex(p, n, idUbah);
    if (pos == -1) {
        printf("Peserta dengan ID %d tidak ditemukan.\n", idUbah);
        return 0;
    }

    printf("\nMASUKKAN DATA BARU:\n");

    printf("ID Peserta baru        : ");
    scanf("%d", &p[pos].id);

    printf("Nama Peserta baru      : ");
    scanf(" %49[^\n]", p[pos].nama);

    inputKategoriValid(p[pos].kategori, 30);

    printf("Nilai Kreativitas (0-100): ");
    scanf("%f", &p[pos].kreativitas);

    printf("Nilai Teknis (0-100): ");
    scanf("%f", &p[pos].teknis);

    printf("Nilai Penampilan (0-100): ");
    scanf("%f", &p[pos].penampilan);

    p[pos].nilaiAkhir = 0;
    printf("Data peserta berhasil diupdate.\n");
    return 1;
}


int hapusPeserta(Peserta p[], int *n) {
    if (*n == 0) {
        printf("Belum ada data peserta.\n");
        return 0;
    }

    int idHapus;
    printf("Masukkan ID peserta yang akan dihapus: ");
    scanf("%d", &idHapus);

    int pos = cariPesertaIndex(p, *n, idHapus);
    if (pos == -1) {
        printf("Peserta dengan ID %d tidak ditemukan.\n", idHapus);
        return 0;
    }

    for (int i = pos; i < *n - 1; i++) {
        p[i] = p[i + 1];
    }

    (*n)--;
    printf("Data peserta berhasil dihapus.\n");
    return 1;
}


int aturBobotPenilaian() {
    int bK, bT, bP;

    printf("\n=== ATUR BOBOT PENILAIAN ===\n");
    printf("Bobot Kreativitas (%%): ");
    scanf("%d", &bK);
    printf("Bobot Teknis (%%): ");
    scanf("%d", &bT);
    printf("Bobot Penampilan (%%): ");
    scanf("%d", &bP);

    if (bK + bT + bP != 100) {
        printf("TOTAL BOBOT HARUS 100%% (sekarang %d%%).\n", bK + bT + bP);
        return 0;
    }

    wKreativitas = bK / 100.0f;
    wTeknis      = bT / 100.0f;
    wPenampilan  = bP / 100.0f;

    printf("Bobot berhasil disimpan.\n");
    return 1;
}


float hitungNilaiAkhir(float k, float t, float p) {
    return (k * wKreativitas) + (t * wTeknis) + (p * wPenampilan);
}

int hitungSemuaNilai(Peserta arr[], int n) {
    if (n == 0) {
        printf("Belum ada data peserta.\n");
        return 0;
    }

    if (wKreativitas == 0 && wTeknis == 0 && wPenampilan == 0) {
        printf("Bobot belum diatur! Silakan atur bobot dulu (menu 9).\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        arr[i].nilaiAkhir = hitungNilaiAkhir(arr[i].kreativitas, arr[i].teknis, arr[i].penampilan);
    }

    printf("Nilai akhir semua peserta berhasil dihitung.\n");
    return 1;
}


int urutkanPeserta(Peserta arr[], int n) {
    if (n == 0) {
        printf("Belum ada data peserta.\n");
        return 0;
    }

    if (!hitungSemuaNilai(arr, n)) return 0;

    Peserta temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j].nilaiAkhir < arr[j + 1].nilaiAkhir) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return 1;
}


int statistikNilai(Peserta arr[], int n, float *min, float *max, float *rata) {
    if (n == 0) {
        printf("Belum ada data peserta.\n");
        return 0;
    }

    if (!hitungSemuaNilai(arr, n)) return 0;

    *min = arr[0].nilaiAkhir;
    *max = arr[0].nilaiAkhir;
    float total = arr[0].nilaiAkhir;

    for (int i = 1; i < n; i++) {
        float nilai = arr[i].nilaiAkhir;
        if (nilai < *min) *min = nilai;
        if (nilai > *max) *max = nilai;
        total += nilai;
    }

    *rata = total / n;
    return 1;
}

