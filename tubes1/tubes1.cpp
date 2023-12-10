#include <iostream>
#include "tubes1.h"

using namespace std;

void createListDokter(listDokter &LD){
    first(LD) = NULL;
}

adrD createElmDokter(infoDokter x){
    int kodeDokter;
    string namaDokter, spesialis, jadwal;

    cin >> kodeDokter;
    cin >> namaDokter;
    cin >> spesialis;
    cin >> jadwal;

    x.kodeDokter = kodeDokter;
    x.namaDokter = namaDokter;
    x.spesialis = spesialis;
    x.jadwal = jadwal;

    adrD D = new elmDokter;
    info(D) = x;
    nextR(D) = NULL;
    nextD(D) = NULL;

    return D;
}

void masukkanInputDokter(listDokter &LD){
    int i;
    infoDokter x;
    adrD D;
    cout << "Jumlah data dokter yang akan diinput : "; cin >> i; cout << endl;
    cout << "Bila dokter lebih dari 1, silahkan masukkan secara berulang." << endl;
    cout << "Masukkan data dokter (kode, nama, spesialis (THT, bedah, mata, atau umum),dan jadwal) :" << endl;
    while (i > 0){
        D = createElmDokter(x);
        insertDokterTerurutKode(LD, D);
        i--;
    }
}

void insertDokterTerurutKode(listDokter &LD, adrD D){
    if (first(LD) == NULL){
        first(LD) = D;
    } else {
        adrD E = first(LD);
        while (nextD(E) != NULL){
            E = nextD(E);
        }
        adrD C = first(LD);

        if (info(D).kodeDokter < info(C).kodeDokter){
            nextD(D) = first(LD);
            first(LD) = D;
        } else if (info(D).kodeDokter > info(E).kodeDokter){
            nextD(E) = D;
        } else {
            while (nextD(C) != NULL){
                if (info(D).kodeDokter < info(nextD(C)).kodeDokter){
                    nextD(D) = nextD(C);
                    nextD(C) = D;
                    break;
                }
                C = nextD(C);
            }
        }
    }
}

void deleteDokter(listDokter &LD, adrD &D, int kodeDokter, string namaDokter){
    if (first(LD) == NULL){
        cout << "List dokter kosong" << endl;
    } else {
        D = searchDokter(LD, kodeDokter, namaDokter);
        if (D != NULL){
            while (nextR(D) != NULL){
                adrR R = nextR(D);
                info(nextP(R)).jmlDok--;
                nextP(R) = NULL;
                nextR(D) = nextR(R);
                nextR(R) = NULL;
            }

            if (D == first(LD)){
                first(LD) = nextD(D);
                nextD(D) = NULL;
            } else {
                adrD C = first(LD);
                while (nextD(C) != D){
                    C = nextD(C);
                }
                nextD(C) = nextD(D);
                nextD(D) = NULL;
            }
        }
    }
}

void createListPasien(listPasien &LP){
    first(LP) = NULL;
}

adrP createElmPasien(infoPasien y){
    int idPasien, usia;
    string namaPasien;

    cout << "Masukkan data pasien (id, nama, dan usia) :" << endl;
    cin >> idPasien;
    cin >> namaPasien;
    cin >> usia;

    y.idPasien = idPasien;
    y.namaPasien = namaPasien;
    y.usia = usia;
    y.jmlDok = 0;

    adrP P = new elmPasien;
    info(P) = y;
    nextP(P) = NULL;

    return P;
}

void insertLastPasien(listPasien &LP, listDokter &LD, adrP P){
    if (first(LP) == NULL){
        first(LP) = P;
    } else {
        adrP T = first(LP);
        while (nextP(T) != NULL){
            T = nextP(T);
        }
        nextP(T) = P;
    }
}

void deletePasien(listPasien &LP, listDokter &LD, adrP &P, int idPasien, string namaPasien){
    if (first(LP) == NULL){
        cout << "List pasien kosong" << endl;
    } else {
        P = searchPasien(LP, idPasien, namaPasien);
        if (P != NULL){
            adrD D = first(LD);
            while (D != NULL){
                adrR R = nextR(D);
                while (R != NULL){
                    if (nextP(R) == P){
                        nextP(R) == NULL;
                        if (R == nextR(D)){
                            nextR(D) = nextR(R);
                            nextR(R) = NULL;
                        } else {
                            adrR Q = nextR(D);
                            while (nextR(Q) != R){
                                Q = nextR(Q);
                            }
                            nextR(Q) = nextR(R);
                            nextR(R) = NULL;
                        }
                        break;
                    }
                    R = nextR(R);
                }
                D = nextD(D);
            }

            if (P == first(LP)){
                first(LP) = nextP(P);
                nextP(P) = NULL;
            } else {
                adrP T = first(LP);
                while (nextP(T) != P){
                    T = nextP(T);
                }
                nextP(T) = nextP(P);
                nextP(P) = NULL;
            }
        }
    }
}

adrR createElmRelasi(){
    adrR R = new elmRelasi;
    nextR(R) = NULL;
    nextP(R) = NULL;
    return R;
}

void daftarDokterSesuai(listDokter LD, string spesialis){
    if (first(LD) == NULL){
        cout << "List dokter kosong" << endl;
    } else {
        cout << "========== Pilihan Dokter ==========" << endl;
        adrD D = first(LD);
        while (D != NULL){
            if (info(D).spesialis == spesialis){
                cout << "Kode dokter : " << info(D).kodeDokter << endl;
                cout << "Nama dokter : " << info(D).namaDokter << endl;
                cout << "Spesialis : " << info(D).spesialis << endl;
                cout << "Jadwal praktik: " << info(D).jadwal << endl << endl;
            }
            D = nextD(D);
        }
        cout << "====================================" << endl << endl;
    }
}

void pilihDokter(listDokter &LD, listPasien &LP, int idPasien, string namaPasien){
    string namaDokter, keluhan;
    int n, kodeDokter;
    adrD D;
    adrR R;
    adrP P = searchPasien(LP, idPasien, namaPasien);
    if (P != NULL) {
        cout << "Satu pasien maksimal ditangani oleh 5 dokter." << endl;
        cout << "Jumlah dokter yang dibutuhkan : "; cin >> n; cout << endl;
        while (n > 0){
            if (info(P).jmlDok < 5) {
                cout << "Pilihan keluhan : batuk, pilek, TBC, jantung, saraf, plus/minus(rabun), katarak, glaukoma." << endl;
                cout << "Atau bila tidak ada, ketik : lainnya" << endl;
                cout << "Masukkan keluhan : "; cin >> keluhan; cout << endl;
                if (keluhan == "batuk" || keluhan == "pilek" || keluhan  == "TBC"){
                    daftarDokterSesuai(LD, "THT");
                } else if (keluhan == "jantung" || keluhan == "saraf"){
                    daftarDokterSesuai(LD, "bedah");
                } else if (keluhan == "plus/minus(rabun)" || keluhan == "katarak" || keluhan == "glaukoma"){
                    daftarDokterSesuai(LD, "mata");
                } else {
                    daftarDokterSesuai(LD, "umum");
                }
                cout << "Masukkan kode dokter yang dipilih : "; cin >> kodeDokter;
                cout << "Masukkan nama dokter yang dipilih : "; cin >> namaDokter; cout << endl;
                D = searchDokter(LD, kodeDokter, namaDokter);

                R = createElmRelasi();
                if (nextR(D) != NULL){
                    adrR Q = nextR(D);
                    while (nextR(Q) != NULL){
                        Q = nextR(Q);
                    }
                    nextR(Q) = R;
                } else {
                    nextR(D) = R;
                }
                nextP(R) = P;
                info(P).jmlDok++;
            } else {
                cout << "Maaf, jumlah dokter yang menangani pasien sudah mencapai batas maksimum (5)." << endl;
                break;
            }
            n--;
        }
    }
}

void hapusDokterTerpilih(listDokter &LD, listPasien &LP, int idPasien, string namaPasien){
    int kodeDokter;
    string namaDokter;
    adrP P = searchPasien(LP, idPasien, namaPasien);
    if (P != NULL){
        dokterPasienTertentu(LP, LD, idPasien, namaPasien);
        cout << "Masukkan kode dokter : "; cin >> kodeDokter;
        cout << "Masukkan nama dokter : "; cin >> namaDokter;
        adrD D = searchDokter(LD, kodeDokter, namaDokter);
        adrR R = nextR(D);
        while (R != NULL){
            if (nextP(R) == P){
                nextP(R) == NULL;
                if (R == nextR(D)){
                    nextR(D) = nextR(R);
                    nextR(R) = NULL;
                } else {
                    adrR Q = nextR(D);
                    while (nextR(Q) != R){
                        Q = nextR(Q);
                    }
                    nextR(Q) = nextR(R);
                    nextR(R) = NULL;
                }
                break;
            }
            R = nextR(R);
        }
        info(P).jmlDok--;
    }
}

adrD searchDokter(listDokter LD, int kodeDokter, string namaDokter){
    adrD D;
    if (first(LD) == NULL){
        cout << "List dokter kosong" << endl;
        D = NULL;
    } else {
        D = first(LD);
        while (D != NULL && info(D).kodeDokter != kodeDokter && info(D).namaDokter != namaDokter){
            D = nextD(D);
        }
        if (D == NULL){
            cout << "Data dokter tidak ditemukan. Harap pastikan input sudah benar." << endl;
        }
    }
    return D;
}
adrP searchPasien(listPasien LP, int idPasien, string namaPasien){
    adrP P;
    if (first(LP) == NULL){
        cout << "List pasien kosong" << endl;
        P = NULL;
    } else {
        P = first(LP);
        while (P != NULL && info(P).idPasien != idPasien && info(P).namaPasien != namaPasien){
            P = nextP(P);
        }
        if (P == NULL){
            cout << "Data pasien tidak ditemukan.  Harap pastikan input sudah benar." << endl;
        }
    }
    return P;
}

void showAllPasienBesertaDokter(listPasien LP, listDokter LD){
    if (first(LP) == NULL){
        cout << "List pasien kosong." << endl;
    } else {
        cout << "======== DAFTAR PASIEN BESERTA DOKTER ========" << endl;
        adrP P = first(LP);
        while (P != NULL){
            cout << "ID pasien : " << info(P).idPasien << endl;
            cout << "Nama pasien : " << info(P).namaPasien << endl;
            cout << "Usia : " << info(P).usia << endl;
            cout << "Jumlah dokter yang menangani : " << info(P).jmlDok << endl;
            dokterPasienTertentu(LP, LD, info(P).idPasien, info(P).namaPasien);
            cout << endl;
            P = nextP(P);
        }
    }
}

void showAllDokterBesertaPasien(listDokter LD, listPasien LP){
    if (first(LD) == NULL){
        cout << "List dokter kosong." << endl;
    } else {
        cout << "======== DAFTAR DOKTER BESERTA PASIEN ========" << endl;
        adrD D = first(LD);
        while (D != NULL){
            cout << "Kode dokter : " << info(D).kodeDokter << endl;
            cout << "Nama dokter : " << info(D).namaDokter << endl;
            cout << "Spesialis : " << info(D).spesialis << endl;
            cout << "Jadwal praktik: " << info(D).jadwal << endl;
            pasienDokterTertentu(LD, info(D).kodeDokter, info(D).namaDokter);
            cout << endl;
            D = nextD(D);
        }
    }
}

void pasienDokterTertentu(listDokter LD, int kodeDokter, string namaDokter){
    adrD D = searchDokter(LD, kodeDokter, namaDokter);
    if (D != NULL){
        if (nextR(D) == NULL){
            cout << "Dokter " << namaDokter << " tidak memiliki pasien." << endl;
        } else {
            cout << "========== Daftar Pasien Dokter " << namaDokter << " ==========" << endl;
            adrR R = nextR(D);
            while (R != NULL){
                cout << "ID pasien : " << info(nextP(R)).idPasien << endl;
                cout << "Nama pasien : " << info(nextP(R)).namaPasien << endl;
                cout << "Usia : " << info(nextP(R)).usia << endl;
                cout << "Jumlah dokter yang menangani : " << info(nextP(R)).jmlDok << endl << endl;

                R = nextR(R);
            }
            cout << "===============================================" << endl;
        }
    }
}

void dokterPasienTertentu(listPasien LP, listDokter LD, int idPasien, string namaPasien){
    adrP P = searchPasien(LP, idPasien, namaPasien);
    if (P != NULL){
        cout << "========== Daftar Dokter Pasien " << namaPasien << " ==========" << endl;
        adrD D = first(LD);
        while (D != NULL){
            adrR R = nextR(D);
            while (R != NULL){
                if (nextP(R) == P){
                    cout << "Kode dokter : " << info(D).kodeDokter << endl;
                    cout << "Nama dokter : " << info(D).namaDokter << endl;
                    cout << "Spesialis : " << info(D).spesialis << endl;
                    cout << "Jadwal praktik: " << info(D).jadwal << endl << endl;
                }
                R = nextR(R);
            }
            D = nextD(D);
        }
        cout << "===============================================" << endl;
    }
}

void tingkatKesibukanDokter(listDokter LD){
    adrD Sibuk, TdkSibuk;
    int jmlPasTerbanyak = 0;
    int jmlPasTersedikit = 0;
    int jmlPas = 0;
    adrD D = first(LD);
    adrR R = nextR(D);
    while (R != NULL){
        jmlPas++;
        R = nextR(R);
    }
    jmlPasTerbanyak = jmlPas;
    jmlPasTersedikit = jmlPas;
    Sibuk = D;
    TdkSibuk = D;

    while (D != NULL){
        jmlPas = 0;
        adrR R = nextR(D);
        while (R != NULL){
            jmlPas++;
            R = nextR(R);
        }
        if (jmlPasTerbanyak < jmlPas){
            jmlPasTerbanyak = jmlPas;
            Sibuk = D;
        }
        if (jmlPasTersedikit > jmlPas){
            jmlPasTersedikit = jmlPas;
            TdkSibuk = D;
        }

        D = nextD(D);
    }

    cout << "Dokter yang paling sibuk :" << endl;
    cout << "Kode dokter : " << info(Sibuk).kodeDokter << endl;
    cout << "Nama dokter : " << info(Sibuk).namaDokter << endl;
    cout << "Spesialis : " << info(Sibuk).spesialis << endl;
    cout << "Jadwal praktik: " << info(Sibuk).jadwal << endl;
    cout << "Jumlah pasien : " << jmlPasTerbanyak << endl << endl;

    cout << "Dokter yang paling tidak sibuk :" << endl;
    cout << "Kode dokter : " << info(TdkSibuk).kodeDokter << endl;
    cout << "Nama dokter : " << info(TdkSibuk).namaDokter << endl;
    cout << "Spesialis : " << info(TdkSibuk).spesialis << endl;
    cout << "Jadwal praktik : " << info(TdkSibuk).jadwal << endl;
    cout << "Jumlah pasien : " << jmlPasTersedikit << endl << endl;
}

int selectMenu()
{
    cout << "============================ MENU ============================" << endl;
    cout << "1. Insert data dokter" << endl;
    cout << "2. Delete data dokter" << endl;
    cout << "3. Menampilkan seluruh data dokter beserta pasien" << endl;
    cout << "4. Insert data pasien" << endl;
    cout << "5. Delete data pasien" << endl;
    cout << "6. Pilih dokter" << endl;
    cout << "7. Hapus dokter terpilih" << endl;
    cout << "8. Menampilkan seluruh data pasien beserta dokter" << endl;
    cout << "9. Menampilkan data pasien dari dokter tertentu" << endl;
    cout << "10. Menampilkan data dokter dari pasien tertentu" << endl;
    cout << "11. Menampilkan data dokter yang paling sibuk dan tidak sibuk"  << endl;
    cout << "0. Exit" << endl;
    cout << "Pilihan menu : ";

    int input = 0;
    cin >> input;
    cout << endl;

    return input;
}
