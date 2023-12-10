#include <iostream>
#include "tubes1.h"

using namespace std;

int main()
{
    listDokter LD;
    listPasien LP;
    infoPasien y;
    adrP P;
    adrD D;
    int pilihan, jawab, kodeDokter, idPasien;
    string namaDokter, namaPasien;

    createListDokter(LD);
    createListPasien(LP);

    pilihan = -1;
    while (pilihan != 0){
        pilihan = selectMenu();
        switch(pilihan){
        case 1 :
            masukkanInputDokter(LD);
            cout << endl;
            break;

        case 2 :
            cout << "Masukkan kode dokter : "; cin >> kodeDokter;
            cout << "Masukkan nama dokter : "; cin >> namaDokter;
            deleteDokter(LD, D, kodeDokter, namaDokter);
            cout << endl;
            break;

        case 3 :
            showAllDokterBesertaPasien(LD, LP);
            cout << endl;
            break;

        case 4 :
            P = createElmPasien(y);
            insertLastPasien(LP, LD, P);

            cout << endl << "Ingin memilih dokter? ketik 1 jika ya, 0 jika tidak" << endl;
            cout << "Jawab : "; cin >> jawab;
            if (jawab == 1){
                pilihDokter(LD, LP, info(P).idPasien, info(P).namaPasien);
            }
            cout << endl;
            break;

        case 5 :
            cout << "Masukkan id pasien : "; cin >> idPasien;
            cout << "Masukkan nama pasien : "; cin >> namaPasien;
            deletePasien(LP, LD, P, idPasien, namaPasien);
            cout << endl;
            break;

        case 6 :
            cout << "Masukkan id pasien : "; cin >> idPasien;
            cout << "Masukkan nama pasien : "; cin >> namaPasien;
            pilihDokter(LD, LP, idPasien, namaPasien);
            cout << endl;
            break;

        case 7 :
            cout << "Masukkan id pasien : "; cin >> idPasien;
            cout << "Masukkan nama pasien : "; cin >> namaPasien;
            hapusDokterTerpilih(LD, LP, idPasien, namaPasien);
            cout << endl;
            break;

        case 8 :
            showAllPasienBesertaDokter(LP, LD);
            cout << endl;
            break;

        case 9 :
            cout << "Masukkan kode dokter : "; cin >> kodeDokter;
            cout << "Masukkan nama dokter : "; cin >> namaDokter;
            pasienDokterTertentu(LD, kodeDokter, namaDokter);
            cout << endl;
            break;

        case 10 :
            cout << "Masukkan id pasien : "; cin >> idPasien;
            cout << "Masukkan nama pasien : "; cin >> namaPasien;
            dokterPasienTertentu(LP, LD, idPasien, namaPasien);
            cout << endl;
            break;

        case 11 :
            tingkatKesibukanDokter(LD);
            cout << endl;
            break;
        }
    }
    cout << "Terima kasih" << endl;
    return 0;
}
