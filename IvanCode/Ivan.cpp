#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

// Prototype Procedure
void Login();
void Menu_Utama();
void Tampilkan_Catatan_Keuangan();
void Tambah_Catatan_Keuangan();
void Ubah_Catatan_Keuangan();
void Credits();

// Variabel Global
string Data[99999] = {};
int Data_Tanggal[99999] = {};
float Data_Nominal[99999] = {};
float Data_Modal[120] = {};
int Jumlah_Baris_Data = 1;

int Validasi_Angka(int Num)
{
    while (!(cin >> Num))
    {
        cout << "Hanya Menerima Angka" << endl;
        cin.clear();                                         // digunakan untuk menghapus Unlimited loop yang disebabkan input berupa huruf maupun simbol
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menentukan batas dari angka
    }
    return Num;
}

int String_ke_Integer(string Data_String)
{
    stringstream Ubah_Tipe;
    int Data_Interger;
    Ubah_Tipe << Data_String;
    Ubah_Tipe >> Data_Interger;
    return Data_Interger;
}

void Sortir_Riwayat(int Data_Tanggal[], int Ndata)
{
    string Temp_Kasar[7];
    int Temp[7], Idx_Min[7] = {}, Hit, Number;
    for (int i = 1; i <= Ndata + 1; i += 6)
    {
        Idx_Min[0] = Data_Tanggal[i];
        Idx_Min[1] = Data_Tanggal[i + 1];
        Idx_Min[2] = Data_Tanggal[i + 2];
        Idx_Min[3] = Data_Tanggal[i + 3];
        Idx_Min[4] = Data_Tanggal[i + 4];
        Idx_Min[5] = Data_Tanggal[i + 5];
        for (int j = i + 6; j <= Ndata + 1; j += 6)
        {
            if (Idx_Min[0] > Data_Tanggal[j] || (Idx_Min[1] == Data_Tanggal[j] && Idx_Min[2] > Data_Tanggal[j + 1]) || (Idx_Min[1] == Data_Tanggal[j] && Idx_Min[2] == Data_Tanggal[j + 1] && Idx_Min[3] > Data_Tanggal[j + 2]))
            {
                Idx_Min[0] = Data_Tanggal[j];
                Idx_Min[1] = Data_Tanggal[j + 1];
                Idx_Min[2] = Data_Tanggal[j + 2];
                Idx_Min[3] = Data_Tanggal[j + 3];
                Idx_Min[4] = Data_Tanggal[j + 4];
                Idx_Min[5] = Data_Tanggal[j + 5];
                Number = j;
                Hit++;
            } /*
             else if ()
             {
                 Idx_Min[1] = Data_Tanggal[j];
                 Idx_Min[2] = Data_Tanggal[j + 1];
                 Idx_Min[3] = Data_Tanggal[j + 2];
                 Idx_Min[4] = Data_Tanggal[j + 3];
                 Idx_Min[5] = Data_Tanggal[j + 4];
                 Idx_Min[6] = Data_Tanggal[j + 5];
                 Number = j;
                 Hit++;
             }
             else if ()
             {
                 Idx_Min[1] = Data_Tanggal[j];
                 Idx_Min[2] = Data_Tanggal[j + 1];
                 Idx_Min[3] = Data_Tanggal[j + 2];
                 Idx_Min[4] = Data_Tanggal[j + 3];
                 Idx_Min[5] = Data_Tanggal[j + 4];
                 Idx_Min[6] = Data_Tanggal[j + 5];
                 Number = j;
                 Hit++;
             }*/
        }
        if (Hit != 0)
        {
            Temp[0] = Data_Tanggal[i];
            Temp[1] = Data_Tanggal[i + 1];
            Temp[2] = Data_Tanggal[i + 2];
            Temp[3] = Data_Tanggal[i + 3];
            Temp[4] = Data_Tanggal[i + 4];
            Temp[5] = Data_Tanggal[i + 5];
            Data_Tanggal[i] = Idx_Min[0];
            Data_Tanggal[i + 1] = Idx_Min[1];
            Data_Tanggal[i + 2] = Idx_Min[2];
            Data_Tanggal[i + 3] = Idx_Min[3];
            Data_Tanggal[i + 4] = Idx_Min[4];
            Data_Tanggal[i + 5] = Idx_Min[5];
            Data_Tanggal[Number] = Temp[0];
            Data_Tanggal[Number + 1] = Temp[1];
            Data_Tanggal[Number + 2] = Temp[2];
            Data_Tanggal[Number + 3] = Temp[3];
            Data_Tanggal[Number + 4] = Temp[4];
            Data_Tanggal[Number + 5] = Temp[5];

            // Untuk Data Kasar berbentuk string
            Temp_Kasar[0] = Data[i];
            Temp_Kasar[1] = Data[i + 1];
            Temp_Kasar[2] = Data[i + 2];
            Temp_Kasar[3] = Data[i + 3];
            Temp_Kasar[4] = Data[i + 4];
            Temp_Kasar[5] = Data[i + 5];
            Data[i] = Data[Number];
            Data[i + 1] = Data[Number + 1];
            Data[i + 2] = Data[Number + 2];
            Data[i + 3] = Data[Number + 3];
            Data[i + 4] = Data[Number + 4];
            Data[i + 5] = Data[Number + 5];
            Data[Number] = Temp_Kasar[0];
            Data[Number + 1] = Temp_Kasar[1];
            Data[Number + 2] = Temp_Kasar[2];
            Data[Number + 3] = Temp_Kasar[3];
            Data[Number + 4] = Temp_Kasar[4];
            Data[Number + 5] = Temp_Kasar[5];
        }
        Hit = 0;
    }
}

void Tambah_Riwayat(string Jenis_riwayat)
{
    ofstream Tambah_Data; // Tulis riwayat
    int Hari = 0, Bulan = 0, Tahun = 0, Maks_Hari = 31;
    float Isi_Nominal;
    string Keterangan;
    Tambah_Data.open("Database.txt", ios::app | ios::out | ios::in); // Buka file, menambah riwayat di baris baru dan mengecek apakah terdapat file Database.txt
    cout << "Contoh: [2021/12/31] Pemasukan Sebesar Rp.2000000 Untuk Membeli Mobil\n";
    cout << "Tahun: \n";
    do
    {
        Tahun = Validasi_Angka(Tahun);
        if (Tahun < 2021 || Tahun > 2030)
        {
            cout << "Tahun pada program ini memiliki batas dari 2021 sampai 2030" << endl;
        }
    } while (Tahun < 2021 || Tahun > 2030);
    Tambah_Data << Tahun << "\n";
    cout << "Bulan: \n";
    do
    {
        Bulan = Validasi_Angka(Bulan);
        if (Bulan < 1 || Bulan > 12)
        {
            cout << "Bulan memiliki batas dari 1 sampai 12" << endl;
        }
    } while (Bulan < 1 || Bulan > 12);
    Tambah_Data << Bulan << "\n";
    cout << "Hari: \n";
    do
    {
        Hari = Validasi_Angka(Hari);
        if (Bulan == 1 && (Hari < 1 || Hari > 31))
        {
            cout << "Bulan Januari memiliki 31 Hari\n";
            Maks_Hari = 31;
        }
        else if (Bulan == 2 && Tahun % 4 != 0 && (Hari < 1 || Hari > 28))
        {
            cout << "Bulan Februari Tahun " << Tahun << " memiliki 28 Hari dan tidak tergolong tahun kabisat\n";
            Maks_Hari = 28;
        }
        else if (Bulan == 2 && Tahun % 4 == 0 && (Hari < 1 || Hari > 29))
        {
            cout << "Bulan Februari Tahun " << Tahun << " memiliki 29 Hari dan tidak tergolong tahun kabisat\n";
            Maks_Hari = 29;
        }
        else if (Bulan == 3 && (Hari < 1 || Hari > 31))
        {
            cout << "Bulan Maret memiliki 31 Hari\n";
            Maks_Hari = 31;
        }
        else if (Bulan == 4 && (Hari < 1 || Hari > 30))
        {
            cout << "Bulan April memiliki 30 Hari\n"
                 << endl;
            Maks_Hari = 30;
        }
        else if (Bulan == 5 && (Hari < 1 || Hari > 31))
        {
            cout << "Bulan Mei memiliki 31 Hari\n"
                 << endl;
            Maks_Hari = 31;
        }
        else if (Bulan == 6 && (Hari < 1 || Hari > 30))
        {
            cout << "Bulan Juni memiliki 30 Hari\n"
                 << endl;
            Maks_Hari = 30;
        }
        else if (Bulan == 7 && (Hari < 1 || Hari > 31))
        {
            cout << "Bulan Juli memiliki 31 Hari\n"
                 << endl;
            Maks_Hari = 31;
        }
        else if (Bulan == 8 && (Hari < 1 || Hari > 31))
        {
            cout << "Bulan Agustus memiliki 31 Hari\n"
                 << endl;
            Maks_Hari = 31;
        }
        else if (Bulan == 9 && (Hari < 1 || Hari > 30))
        {
            cout << "Bulan September memiliki 30 Hari\n"
                 << endl;
            Maks_Hari = 30;
        }
        else if (Bulan == 10 && (Hari < 1 || Hari > 31))
        {
            cout << "Bulan Oktober memiliki 31 Hari\n"
                 << endl;
            Maks_Hari = 31;
        }
        else if (Bulan == 11 && (Hari < 1 || Hari > 30))
        {
            cout << "Bulan November memiliki 30 Hari\n"
                 << endl;
            Maks_Hari = 30;
        }
        else if (Bulan == 12 && (Hari < 1 || Hari > 31))
        {
            cout << "Bulan Desember memiliki 31 Hari\n"
                 << endl;
            Maks_Hari = 31;
        }
    } while (Hari < 1 || Hari > Maks_Hari);
    Tambah_Data << Hari << "\n";
    Tambah_Data << Jenis_riwayat << "\n";
    cout << "Nominal: \n";
    Isi_Nominal = Validasi_Angka(Isi_Nominal);
    Tambah_Data << Isi_Nominal << "\n";
    cout << "Keterangan: \n";
    cin >> Keterangan;
    Tambah_Data << Keterangan << "\n";
}

void Riwayat() // Tampilkan riwayat
{
    ifstream Baca_Data; // Baca riwayat0
    string Ubah;
    Baca_Data.open("Database.txt");
    while (!Baca_Data.eof())
    {
        getline(Baca_Data, Data[Jumlah_Baris_Data]);
        Jumlah_Baris_Data++;
    }
    Baca_Data.close();
    for (int n = 1; n <= Jumlah_Baris_Data + 6; n += 6)
    {
        Ubah = Data[n];
        Data_Tanggal[n] = String_ke_Integer(Ubah);
        Ubah = Data[n + 1];
        Data_Tanggal[n + 1] = String_ke_Integer(Ubah);
        Ubah = Data[n + 2];
        Data_Tanggal[n + 2] = String_ke_Integer(Ubah);
        Ubah = Data[n + 4];
        Data_Nominal[n + 4] = (float)String_ke_Integer(Ubah);
    }
    Sortir_Riwayat(Data_Tanggal, Jumlah_Baris_Data + 6);
}

void Hitung_Modal()
{
    int m = 1;
    int Jumlah_Hari_Modal;
    for (int Tahun_Modal = 2021; Tahun_Modal <= 2030; Tahun_Modal++)
    {
        for (int Bulan_Modal = 1; Bulan_Modal <= 12; Bulan_Modal++)
        {
            for (int l = 1; l <= Jumlah_Baris_Data + 6; l += 6)
            {
                if (Data[l + 3] == "Pemasukan" && Data_Tanggal[l] == Tahun_Modal && Data_Tanggal[l + 1] == Bulan_Modal)
                {
                    Data_Modal[Bulan_Modal] += Data_Nominal[l + 4];
                }
            }
        }
    }
}

void Rata_rata_Harian() // Tampilkan rata-rata pengeluaran harian
{
    system("cls");
    string Pilih_1_1;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Rata-rata per Hari\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << endl;
    cout << "Kembali ke Home                                           (0)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_1_1;
    if (Pilih_1_1 == "0")
    {
        Menu_Utama();
    }
    else
    {
        Rata_rata_Harian();
    }
}

void Rata_rata_Minggu() // Tampilkan rata-rata pengeluaran mingguan
{
    system("cls");
    string Pilih_1_2;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Rata-rata per Minggu\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << endl;
    cout << "Kembali ke Home                                           (0)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_1_2;
    if (Pilih_1_2 == "0")
    {
        Menu_Utama();
    }
    else
    {
        Rata_rata_Minggu();
    }
}

void Rata_rata_Bulan() // // Tampilkan rata-rata pengeluaran bulanan
{
    system("cls");
    string Pilih_1_3;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Rata-rata per Bulan\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << endl;
    cout << "Kembali ke Home                                           (0)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_1_3;
    if (Pilih_1_3 == "0")
    {
        Menu_Utama();
    }
    else
    {
        Rata_rata_Bulan();
    }
}

void Tampilkan_Riwayat() // Tampilkan riwayat transaksi
{
    string Kembali_1, Jenis_Riwayat, Keterangan, Isi_Nominal, Hari, Bulan, Tahun;
    system("cls");
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t\t       Riwayat Transaksi   \n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << endl;
    Riwayat();
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "No ︱ Tanggal ︱  Jenis Riwayat ︱  Nominal  ︱   Keterangan\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    for (int k = 1; k <= Jumlah_Baris_Data + 6; k += 6)
    {
        Hari = Data[k];
        Bulan = Data[k + 1];
        Tahun = Data[k + 2];
        Jenis_Riwayat = Data[k + 3];
        Isi_Nominal = Data[k + 4];
        Keterangan = Data[k + 5];

        if (Jenis_Riwayat == "Pemasukan")
        {
            cout << ((k + 5) / 6) << "   [" << Hari << "/" << Bulan << "/" << Tahun << "]     " << Jenis_Riwayat << "      Rp " << Isi_Nominal << "       dari " << Keterangan << endl;
        }
        else if (Jenis_Riwayat == "Pengeluaran")
        {
            cout << ((k + 5) / 6) << "   [" << Hari << "/" << Bulan << "/" << Tahun << "]     " << Jenis_Riwayat << "      Rp " << Isi_Nominal << "       untuk " << Keterangan << endl;
        }
    }
    cout << "\n"
         << endl;
    cout << "Kembali ke Home                                           (0)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Kembali_1;
    if (Kembali_1 == "0")
    {
        Menu_Utama();
    }
    else
    {
        Tampilkan_Riwayat();
    }
}

void Ubah_Pemasukan() // Mengubah pemasukan
{
    system("cls");
    string Pilih_3_1_1;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Ubah Riwayat Pemasukan\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    Tampilkan_Riwayat();
    cout << endl;
    cout << "Kembali ke Home                                           (1)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: ";
    cin >> Pilih_3_1_1;
    if (Pilih_3_1_1 == "1")
    {
        Menu_Utama();
    }
    else
    {
        Ubah_Pemasukan();
    }
}
void Hapus_Pemasukan() // Hapus pemasukan
{
    system("cls");
    string Pilih_3_1_2;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Hapus Riwayat Pemasukan\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    Tampilkan_Riwayat();
    cout << endl;
    cout << "Kembali ke Home                                           (1)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi : ";
    cin >> Pilih_3_1_2;
    if (Pilih_3_1_2 == "1")
    {
        Menu_Utama();
    }
    else
    {
        Hapus_Pemasukan();
    }
}

void Ubah_Pengeluaran() // Mengubah pengeluaran
{
    system("cls");
    string Pilih_3_2_1;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Ubah Riwayat Pengeluaran\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    Tampilkan_Riwayat();
    cout << endl;
    cout << "Kembali ke Home                                           (1)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: ";
    cin >> Pilih_3_2_1;
    if (Pilih_3_2_1 == "1")
    {
        Menu_Utama();
    }
    else
    {
        Ubah_Pengeluaran();
    }
}

void Hapus_Pengeluaran() // Hapus pengeluaran
{
    system("cls");
    string Pilih_3_2_2;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Hapus Riwayat Pengeluaran\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    Tampilkan_Riwayat();
    cout << endl;
    cout << "Kembali ke Home                                           (1)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi : ";
    cin >> Pilih_3_2_2;
    if (Pilih_3_2_2 == "1")
    {
        Menu_Utama();
    }
    else
    {
        Hapus_Pengeluaran();
    }
}

void Modal_Awal() // Menampilkan Modal awal
{
    string pilih_1_5;
    system("cls");
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t               Modal Awal\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    Riwayat();
    Hitung_Modal();
    for (int i = 0; i <= 120; i++)
    {
        if (i >= 1 && i <= 12)
        {
            cout << "Modal pada bulan ke-" << i << " Tahun 2021: " << Data_Modal[i] << endl;
        }
        else if (i >= 13 && i <= 24)
        {
            cout << "Modal pada bulan ke-" << i - 12 << " Tahun 2022: " << Data_Modal[i] << endl;
        }
        else if (i >= 25 && i <= 36)
        {
            cout << "Modal pada bulan ke-" << i - 24 << " Tahun 2023: " << Data_Modal[i] << endl;
        }
        else if (i >= 37 && i <= 48)
        {
            cout << "Modal pada bulan ke-" << i - 36 << " Tahun 2024: " << Data_Modal[i] << endl;
        }
        else if (i >= 49 && i <= 60)
        {
            cout << "Modal pada bulan ke-" << i - 48 << " Tahun 2025: " << Data_Modal[i] << endl;
        }
        else if (i >= 60 && i <= 72)
        {
            cout << "Modal pada bulan ke-" << i - 60 << " Tahun 2026: " << Data_Modal[i] << endl;
        }
        else if (i >= 73 && i <= 84)
        {
            cout << "Modal pada bulan ke-" << i - 72 << " Tahun 2027: " << Data_Modal[i] << endl;
        }
        else if (i >= 85 && i <= 96)
        {
            cout << "Modal pada bulan ke-" << i - 84 << " Tahun 2028: " << Data_Modal[i] << endl;
        }
        else if (i >= 97 && i <= 108)
        {
            cout << "Modal pada bulan ke-" << i - 96 << " Tahun 2029: " << Data_Modal[i] << endl;
        }
        else if (i >= 109 && i <= 120)
        {
            cout << "Modal pada bulan ke-" << i - 108 << " Tahun 2030: " << Data_Modal[i] << endl;
        }
    }

    cout << "Kembali ke Home                                           (0)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> pilih_1_5;
    if (pilih_1_5 == "0")
    {
        Menu_Utama();
    }
    else
    {
        Modal_Awal();
    }
}

void Sisa_Uang() // Menampilkan Sisa uang
{
    string pilih_1_6;
    system("cls");
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t                     Sisa uang\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Kembali ke Home                                           (0)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> pilih_1_6;
    if (pilih_1_6 == "0")
    {
        Menu_Utama();
    }
    else
    {
        Sisa_Uang();
    }
}

void Tampilkan_Catatan_Keuangan() // Tampilkan catatan keuangan
{
    system("cls");
    string Pilih_1;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Catatan Keuangan Anda\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Rata-rata Pengeluaran per Hari                             (1)\n";
    cout << "Rata-rata Pengeluaran per Minggu                           (2)\n";
    cout << "Rata-rata Pengeluaran per Bulan                            (3)\n";
    cout << "Riwayat Transaksi                                          (4)\n";
    cout << "Modal Awal                                                 (5)\n";
    cout << "Sisa Uang                                                  (6)\n";
    cout << "Kembali                                                    (7)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_1;
    if (Pilih_1 == "1")
    {
        Rata_rata_Harian();
    }
    else if (Pilih_1 == "2")
    {
        Rata_rata_Minggu();
    }
    else if (Pilih_1 == "3")
    {
        Rata_rata_Bulan();
    }
    else if (Pilih_1 == "4")
    {
        Tampilkan_Riwayat();
    }
    else if (Pilih_1 == "5")
    {
        Modal_Awal();
    }
    else if (Pilih_1 == "6")
    {
        Sisa_Uang();
    }
    else if (Pilih_1 == "7")
    {
        Menu_Utama();
    }
    else
    {
        Tampilkan_Catatan_Keuangan();
    }
}

void Tambah_Catatan_Keuangan() // Tampilkan menu catatan keuangan
{
    string Pilih_2, Jenis_Riwayat;
    system("cls");
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Tambah Catatan Keuangan\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << endl;
    cout << "Tambah Riwayat Pemasukan                                  (1)\n";
    cout << "Tambah Riwayat Pengeluaran                                (2)\n";
    cout << "Kembali ke Home                                           (3)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_2;
    if (Pilih_2 == "1")
    {
        system("cls");
        Jenis_Riwayat = "Pemasukan";
        Tambah_Riwayat(Jenis_Riwayat);
        Tambah_Catatan_Keuangan();
    }
    else if (Pilih_2 == "2")
    {
        system("cls");
        Jenis_Riwayat = "Pengeluaran";
        Tambah_Riwayat(Jenis_Riwayat);
        Tambah_Catatan_Keuangan();
    }
    else if (Pilih_2 == "3")
    {
        Menu_Utama();
    }
    else
    {
        Tambah_Catatan_Keuangan();
    }
}

void Riwayat_Pemasukan()
{
    system("cls");
    string Pilih_3_1;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Riwayat Pemasukan\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << endl;
    cout << "Ubah Riwayat Pemasukan                                    (1)\n";
    cout << "Hapus Riwayat Pemasukan                                   (2)\n";
    cout << "Kembali ke Home                                           (3)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_3_1;
    if (Pilih_3_1 == "1")
    {
        Ubah_Pemasukan();
    }
    else if (Pilih_3_1 == "2")
    {
        Hapus_Pemasukan();
    }
    else if (Pilih_3_1 == "3")
    {
        Menu_Utama();
    }
    else
    {
        Riwayat_Pemasukan();
    }
}

void Riwayat_Pengeluaran()
{
    Jumlah_Baris_Data = 1;
    system("cls");
    string Pilih_3_2;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t             Riwayat Pengeluaran\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Ubah Riwayat Pengeluaran                                  (1)\n";
    cout << "Hapus Riwayat Pengeluaran                                 (2)\n";
    cout << "Kembali ke Home                                           (3)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_3_2;
    if (Pilih_3_2 == "1")
    {
        Ubah_Pengeluaran();
    }
    else if (Pilih_3_2 == "2")
    {
        Hapus_Pengeluaran();
    }
    else if (Pilih_3_2 == "3")
    {
        Menu_Utama();
    }
    else
    {
        Riwayat_Pengeluaran();
    }
}

void Ubah_Catatan_Keuangan()
{
    system("cls");
    string Pilih_3;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t         Ubah Catatan Keuangan Anda\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << endl;
    cout << "Ubah Riwayat Pemasukan                                    (1)\n";
    cout << "Ubah Riwayat Pengeluaran                                  (2)\n";
    cout << "Kembali ke Home                                           (3)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_3;
    if (Pilih_3 == "1")
    {
        Riwayat_Pemasukan();
    }
    else if (Pilih_3 == "2")
    {
        Riwayat_Pengeluaran();
    }
    else if (Pilih_3 == "3")
    {
        Menu_Utama();
    }
    else
    {
        Ubah_Catatan_Keuangan();
    }
}

void Credits()
{
    system("cls");
    string Pilih_3;
    system("cls");
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t                    Credits\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;

    cout << endl;
    cout << "Kembali ke Home                                           (1)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_3;
    if (Pilih_3 == "1")
    {
        Menu_Utama();
    }
    else
    {
        Credits();
    }
}

void Keluar()
{
    system("cls");
    cout << "Sampai jumpa! \n";
    cout << endl;
}

void Menu_Utama() // Tampilkan pilihan menu
{
    system("cls");
    string Pilih_Menu;
    cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
    cout << "\t          SELAMAT DATANG DI SMARPL\n";
    cout << "\t         (SISTEM MONETER ANAK RPL)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Tampilkan catatan keuangan                                (1)\n";
    cout << "Tambah catatan keuangan                                   (2)\n";
    cout << "Ubah catatan keuangan                                     (3)\n";
    cout << "Credits                                                   (4)\n";
    cout << "Exit                                                      (5)\n";
    cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
         << endl;
    cout << "Pilih opsi: \n";
    cin >> Pilih_Menu;     // Pengguna memasukkan pilihan menu
    if (Pilih_Menu == "1") // Tampilkan pilihan Catatan keuangan
    {
        Tampilkan_Catatan_Keuangan();
    }
    else if (Pilih_Menu == "2") // Tampilkan Menu Tambah Catatan Keuangan
    {
        Tambah_Catatan_Keuangan();
    }
    else if (Pilih_Menu == "3") // Tampilkan Menu Ubah Catatan Keuangan
    {
        Ubah_Catatan_Keuangan();
    }
    else if (Pilih_Menu == "4") // Tampilkan Credits
    {
        Credits();
    }
    else if (Pilih_Menu == "5") // Keluar dari Program SMARPL
    {
        Keluar();
    }
    else
    {
        Menu_Utama();
    }
}

void Login()
{
    string uname, pw;
    for (int i = 4; i > 0; i--)
    {
        cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
        cout << "\t                SMARPL LOGIN\n";
        cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
        cout << "Username: ";
        cin >> uname;
        cout << "Password: ";
        cin >> pw;
        cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
        if (uname == "SMARPL" || pw == "1234")
        {
            system("clear");
            cout << "Login Berhasil! \n";
            cout << "Tekan tombol apapun untuk melanjutkan \n";
            system("read");
            Menu_Utama();
            break;
        }
        else if (i == 1)
        {
            system("clear");
            cout << "Akses login ditolak \nSilakan hubungi admin terkait";
        }
        else
        {
            cout << "Username atau Password Anda salah! \n";
            cout << "Kesempatan login Anda " << i - 1 << " kali lagi\n";
        }
    }
}

int main()
{
    Login(); // Tampilkan menu utama
    return 0;
}