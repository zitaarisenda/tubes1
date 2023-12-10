#ifndef TUBES1_H_INCLUDED
#define TUBES1_H_INCLUDED
#include <iostream>
#define info(P) (P)->info
#define nextD(P) (P)->nextD
#define nextR(P) (P)->nextR
#define nextP(P) (P)->nextP
#define first(L) ((L).first)

using namespace std;

typedef struct elmDokter *adrD;
typedef struct elmRelasi *adrR;
typedef struct elmPasien *adrP;

struct infoDokter{
    int kodeDokter;
    string namaDokter, spesialis, jadwal;
};
struct elmDokter{
    infoDokter info;
    adrD nextD;
    adrR nextR;
};
struct listDokter{
    adrD first;
};
struct infoPasien{
    int idPasien, usia, jmlDok;
    string namaPasien;
};
struct elmPasien{
    infoPasien info;
    adrP nextP;
};
struct listPasien{
    adrP first;
};
struct elmRelasi{
    adrP nextP;
    adrR nextR;
};

void createListDokter(listDokter &LD);
adrD createElmDokter(infoDokter x);
void masukkanInputDokter(listDokter &LD);
void insertDokterTerurutKode(listDokter &LD, adrD D);
void deleteDokter(listDokter &LD, adrD &D, int kodeDokter, string namaDokter);
void createListPasien(listPasien &LP);
adrP createElmPasien(infoPasien y);
void insertLastPasien(listPasien &LP,listDokter &LD, adrP P);
void deletePasien(listPasien &LP, listDokter &LD, adrP &P, int idPasien, string namaPasien);
adrR createElmRelasi();
void daftarDokterSesuai(listDokter LD, string spesialis);
void pilihDokter(listDokter &LD, listPasien &LP, int idPasien, string namaPasien);
void hapusDokterTerpilih(listDokter &LD, listPasien &LP, int idPasien, string namaPasien);
adrD searchDokter(listDokter LD, int kodeDokter, string namaDokter);
adrP searchPasien(listPasien LP, int idPasien, string namaPasien);
void showAllPasienBesertaDokter(listPasien LP, listDokter LD);
void showAllDokterBesertaPasien(listDokter LD, listPasien LP);
void pasienDokterTertentu(listDokter LD, int kodeDokter, string namaDokter);
void dokterPasienTertentu(listPasien LP, listDokter LD, int idPasien, string namaPasien);
void tingkatKesibukanDokter(listDokter LD);
int selectMenu();

#endif // TUBES1_H_INCLUDED
