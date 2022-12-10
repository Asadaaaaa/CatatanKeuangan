#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/************ Prototype Function ************/

// Prototype Function
void Financial_Notes_Page();
void Main_Page();
void loader();
void notificator(string text, int borderLen, int parentLen);
void Add_Notes(string jenis_riwayat, string tahun, string bulan, string hari, string nominal, string keterangan);

//////////////////////////////////////////////



/************ Object & Global Variables ************/

// Struct for UI
struct UI {
  string border;
};

// Struct for Account
struct Account {
  string username = "SMARPL", password = "1234";
};

// Struct for name of month
struct Month {
  string name[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
};

// Struct for financialData financial
struct FinancialData {
  string type[99999] = {};
  int year[99999] = {};
  int month[99999] = {};
  int day[99999] = {};
  int amount[99999] = {};
  string desc[99999] = {};
  int balance = 0;
  int counter = 0;
};

// Declare a Structs
UI ui;
Month month;
FinancialData financialData;

//////////////////////////////////////////////



/**************** SMARPL Page ****************/

void Initial_Income_Page() {
  // Variables
  string input;
  int counter = 0;
  int year[99999] = {};

  // Algo
  for(int i = 0; i < financialData.counter; i++) {
    if(counter == 0) {
      year[counter] = financialData.year[i];
      counter++;
    } else {
      bool isExist = false;
      for(int j = 0; j < counter; j++) {
        if(financialData.year[i] == year[j]) {
          isExist = true;
          break;
        }
      }
      if(isExist == false) {
        year[counter] = financialData.year[i];
        counter++;
      }
    }
  }
  sort(year, year + (sizeof(year) / sizeof(year)));

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "               Modal Awal" << endl;
  cout << ui.border << endl << endl;
  if(financialData.counter == 0) {
    cout << " Data transaksi tidak ada!" << endl;
  }
  for(int i = 0; i < counter; i++) {
    for(int j = 1; j <= 12; j++) {
      int total = 0;
      for(int k = 0; k < financialData.counter; k++) {
        if(financialData.year[k] == year[i] && financialData.month[k] == j) {
          total += financialData.amount[k];
        }
      }
      if(total != 0) {
        cout << " -> Modal pada bulan ke-" << j << " Tahun " << year[i] << ": " << total << endl;
      }
    }
  }
  cout << endl << " [0] Kembali" << endl;
  cout << ui.border << endl;
  cout << "> Pilih Menu: ";

  // Input
  getline(cin, input);
  if(input ==  "0") {
    Financial_Notes_Page();

    return;
  } else {
    notificator("Menu tidak ditemukan", 38, 50);

    Initial_Income_Page();

    return;
  }
}

void History_Transaction_Page() {
  // Variables
  string input;
  int counter = 0;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "             Riwayat Transaksi" << endl;
  cout << ui.border << endl;
  if(financialData.counter == 0) {
    cout << endl << " Data transaksi tidak ada!" << endl << endl;
  }
  for(int i = (financialData.counter - 1); i >= 0; i--) {
    counter++;
    cout << " [" << (i + 1) << "] " << financialData.type[i] << endl;
    cout << "     Tanggal:  " << financialData.year[i] << "/" << financialData.month[i] << "/" << financialData.day[i] << endl;
    cout << "     Jumlah: " << financialData.amount[i] << endl;
    cout << "     Keterangan: " << financialData.desc[i] << endl << endl;

    if(counter == 10) break;
  }
  cout << " [0] Kembali" << endl;
  cout << ui.border << endl;
  cout << "> Pilih Menu: ";

  // Input
  getline(cin, input);
  if(input == "0") {
    Financial_Notes_Page();

    return;
  } else {
    notificator("Menu tidak ditemukan", 38, 50);
    History_Transaction_Page();

    return;
  }
  
  
}

void Financial_Notes_Page() {
  // Variables
  string input;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "             Menu Catatan Keuangan" << endl << endl;
  cout << " Uang kamu: " << financialData.balance << endl;
  cout << ui.border << endl;
  cout << " [1] Rata-rata pengeluaran per hari" << endl;
  cout << " [2] Rata-rata pengeluaran per bulan" << endl;
  cout << " [3] Riwayat transaksi" << endl;
  cout << " [4] Modal awal" << endl;
  cout << " [0] Kembali" << endl;
  cout << ui.border << endl;
  
  // Inputs
  cout << "> Pilih menu: ";
  getline(cin, input);

  if(input == "1") {

    return;
  } else if(input == "2") {

    return;
  } else if(input == "3") {
    History_Transaction_Page();
    
    return;
  } else if(input == "4") {
    Initial_Income_Page();

    return;
  } else if(input == "0") {
    Main_Page();

    return;
  }
  return;
}

void Add_History_Transaction_Page(string jenis_riwayat, string tahun, string bulan, string hari, string nominal, string keterangan) {
  // Variables
  string input;
  int intInput;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "            Tambah Riwayat " << jenis_riwayat << endl << endl;
  cout << " Uang kamu: " << financialData.balance << endl;
  cout << ui.border << endl;
  cout << " Tahun      : " << tahun << endl; 
  cout << " Bulan      : " << bulan << endl; 
  cout << " Hari       : " << hari << endl; 
  cout << " Nominal    : " << nominal << endl; 
  cout << " Keterangan : " << keterangan << endl;
  cout << ui.border << endl;

  // Input
  if(tahun == "") {
    cout << "> Input Tahun: ";
    getline(cin, input);

    try {
      intInput = stoi(input);
    } catch(exception &err) {
      notificator("Input harus berupa angka", 38, 50);
      Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

      return;
    }

    if(intInput < 2021 || intInput > 2030) {
      notificator("Tahun harus diantara 2021-2030", 38, 50);
      Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

      return;
    }

    Add_History_Transaction_Page(jenis_riwayat, input, bulan, hari, nominal, keterangan);

    return;
  } else if(bulan == "") {
    cout << "> Input Bulan: ";
    getline(cin, input);

    try {
      intInput = stoi(input);
    } catch(exception &err) {
      notificator("Input harus berupa angka", 38, 50);
      Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

      return;
    }

    if(intInput < 1 || intInput > 12) {
      notificator("Tahun harus diantara 1-12", 38, 50);
      Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

      return;
    }

    Add_History_Transaction_Page(jenis_riwayat, tahun, input, hari, nominal, keterangan);

    return;
  } else if(hari == "") {
    cout << "> Input Hari: ";
    getline(cin, input);

    try {
      intInput = stoi(input);
    } catch(exception &err) {
      notificator("Input harus berupa angka", 38, 50);
      Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

      return;
    }

    if(intInput < 1) {
      notificator("Hari harus lebih besar dari 0", 38, 50);

      Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

      return;
    }

    if(stoi(bulan) == 2) {
      if(stoi(tahun) % 4 == 0) {
        if(intInput > 29) {
          notificator("Bulan " + month.name[stoi(bulan)-1] + " Memiliki 29 Hari (Kabisat)", 48, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      } else {
        if(intInput > 28) {
          notificator("Bulan " + month.name[stoi(bulan)-1] + " Memiliki 28 Hari (Bukan Kabisat)", 48, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      }
    } else if(stoi(bulan) <= 7) {
      if(stoi(bulan) % 2 == 0) {
        if(intInput > 30) {
          notificator("Bulan " + month.name[stoi(bulan)-1] + " Memiliki 30 Hari", 38, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      } else {
        if(intInput > 31) {
          notificator("Bulan " + month.name[stoi(bulan)-1] + " Memiliki 31 Hari", 38, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      }
    } else {
      if(stoi(bulan) % 2 == 0) {
        if(intInput > 31) {
          notificator("Bulan " + bulan + " Memiliki 31 Hari", 38, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      } else {
        if(intInput > 30) {
          notificator("Bulan " + bulan + " Memiliki 30 Hari", 38, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      }
    }

    Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, input, nominal, keterangan);

    return;
  } else if(nominal == "") {
    cout << "> Input Nominal: ";
    getline(cin, input);

    try {
      intInput = stoi(input);
    } catch(exception &err) {
      notificator("Input harus berupa angka", 38, 50);
      Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

      return;
    }

    Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, input, keterangan);

    return;
  } else if(keterangan == "") {
    cout << "> Input Keterangan: ";
    getline(cin, keterangan);

    Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

    return;
  } else {
    if(jenis_riwayat == "Pemasukan") {
      financialData.balance += stoi(nominal);
    } else if(jenis_riwayat == "Pengeluaran") {
      financialData.balance -= stoi(nominal);
    }
    Add_Notes(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);
    notificator("Riwayat Berhasil Ditambahkan", 38, 50);

    Main_Page();

    return;
  }
}

void Choose_History_Transaction_Type_Page() {
  // Variables
  string input;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "             Tambah Catatan Keuangan" << endl << endl;
  cout << " Uang kamu: " << financialData.balance << endl;
  cout << ui.border << endl;
  cout << " [1] Tambah Riwayat Pemasukan" << endl;
  cout << " [2] Tambah Riwayat Pengeluaran" << endl;
  cout << " [0] Kembali ke Home" << endl;
  cout << ui.border << endl;

  // Inputs
  cout << "> Pilih menu: ";
  getline(cin, input);

  if(input == "1") {
    Add_History_Transaction_Page("Pemasukan", "", "", "", "", "");

    return;
  } else if(input == "2") {
    Add_History_Transaction_Page("Pengeluaran", "", "", "", "", "");

    return;
  } else if(input == "0") {
    Main_Page();

    return;
  }
  return;
}

void Main_Page() {
  // Variables
  string input;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "             SELAMAT DATANG DI SMARPL" << endl;
  cout << "            (SISTEM MONETER ANAK RPL)" << endl << endl;
  cout << " Uang kamu: " << financialData.balance << endl;
  cout << ui.border << endl;
  cout << " [1] Tampilkan catatan keuangan" << endl;
  cout << " [2] Tambah catatan keuangan" << endl;
  cout << " [3] Ubah catatan keuangan" << endl;
  cout << " [4] Credits" << endl;
  cout << " [5] Exit" << endl;
  cout << ui.border << endl;

  // Input
  cout << "> Pilih menu: ";
  getline(cin, input);

  if(input == "1") {
    Financial_Notes_Page();

    return;
  } else if(input == "2") {

    Choose_History_Transaction_Type_Page();

    return;
  } else if(input == "3") {

    return;
  } else if(input == "4") {

    return;
  } else if(input == "5") {

    return;
  } else {
    notificator("Menu tidak ditemukan", 38, 50);

    Main_Page();

    return;
  }
}

void Login_Page(string username, string password) {
  // Variables
  Account account;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "                 SMARPL LOGIN" << endl;
  cout << ui.border << endl;
  cout << " Username: " << username << endl;
  cout << " Password: " << password << endl;
  cout << ui.border << endl;

  // Input
  if(username == "") {
    cout << "> Input Username: ";
    getline(cin, username);
    
    Login_Page(username, password);

    return;
  } else if(password == "") {
    cout << "> Input Password: ";
    getline(cin, password);
    
    Login_Page(username, password);

    return;
  } else {
    if(username != account.username || password != account.password) {
      notificator("Username atau Password salah", 38, 50);
      Login_Page("", "");

      return;
    } else {
      Main_Page();

      return;
    }
  }
}

//////////////////////////////////////////////



/************** Main Function **************/

int main() {
  loader();
  Login_Page("", "");

  return 0;
}

//////////////////////////////////////////////



/*************** Algorithms ***************/

// Loaders function when first run
void loader() {
  // UI
  for(int i = 1; i <= 50; i++) {
		ui.border += 205;
	}

  // Databse Loader
  ifstream dataBase;
  string tempData;
  
  dataBase.open("db.txt");
  if(dataBase.fail()) return;
  while(!dataBase.eof()) {
    getline(dataBase, tempData);
    if(tempData == "{") {
      getline(dataBase, tempData);
      tempData.erase(0, 8);
      financialData.type[financialData.counter] = tempData;
      
      getline(dataBase, tempData);
      tempData.erase(0, 8);
      financialData.year[financialData.counter] = stoi(tempData);
      
      getline(dataBase, tempData);
      tempData.erase(0, 8);
      financialData.month[financialData.counter] = stoi(tempData);

      getline(dataBase, tempData);
      tempData.erase(0, 7);
      financialData.day[financialData.counter] = stoi(tempData);

      getline(dataBase, tempData);
      tempData.erase(0, 10);
      financialData.amount[financialData.counter] = stoi(tempData);

      getline(dataBase, tempData);
      tempData.erase(0, 8);
      financialData.desc[financialData.counter] = tempData;

      if(financialData.type[financialData.counter] == "Pemasukan") {
        financialData.balance += financialData.amount[financialData.counter];
      } else if(financialData.type[financialData.counter] == "Pengeluaran") {
        financialData.balance -= financialData.amount[financialData.counter];
      }

      financialData.counter++;
    }
  }

  dataBase.close();
  return;
}

// Save to DB
void Save_DB() {
  // Variables
  ofstream dataBase;

  // Algo
  dataBase.open("db.txt", ios::trunc);
  for(int i = 0; i < financialData.counter; i++) {
    dataBase << "{" << endl;
    dataBase << "  Type: " << financialData.type[i] << endl;
    dataBase << "  Year: " << financialData.year[i] << endl;
    dataBase << "  Month: " << financialData.month[i] << endl;
    dataBase << "  Day: " << financialData.day[i] << endl;
    dataBase << "  Amount: " << financialData.amount[i] << endl;
    dataBase << "  Desc: " << financialData.desc[i] << endl;
    dataBase << "}" << endl;
  }
  dataBase.close();
  return;
}

// Notification algorithms
void notificator(string text, int borderLen, int parentLen) {
	/* Colors:
		(1) = Green
		(2) = Red
	*/
	
	// variables
  string input;
	char sym1 = 218; // ┌
	char sym2 = 196; // ─
	char sym3 = 191; // ┐
	char sym4 = 179; // │
	char sym5 = 192; // └
	char sym6 = 217; // ┘
	int textLen = text.length();
	int splitTextLen = textLen / 2;
	int splitBorderLen = borderLen / 2;
	string confirm = "Press any key to continue...";
	int confirmLen = confirm.length();
	int splitConfirmLen = confirmLen / 2;
	int intPosition = (parentLen - (borderLen + 2)) / 2;
	string strPosition;


	// Check Param
	if(textLen <= 0) { 
		cout << "Error 1";
		return;
	} else if(borderLen <= 0) {
		cout << "Error 3";
		return;
	}
	
	if(textLen > borderLen) {
		cout << "Error 3";
		return;
	} else if(borderLen > parentLen) {
		cout << "Error 4";
		return;
	}

	// Algo
	for(int i = 1; i <= intPosition; i++) {
    strPosition += " ";
  }
  cout << strPosition << sym1;
  for(int i = 1; i <= borderLen; i++) {
    cout << sym2;
  }
  cout << sym3 << endl;
  cout << strPosition << sym4;
  for(int i = 1; i <= (splitBorderLen - splitTextLen); i++) {
    cout << " ";
  }
  cout << text;
  for(int i = 1; i <= (borderLen - ((splitBorderLen - splitTextLen) + textLen)); i++) {
    cout << " ";
  }
  cout << sym4 << endl;
  cout << strPosition << sym4;
  for(int i = 1; i <= (splitBorderLen - splitConfirmLen); i++) {
    cout << " ";
  }
  cout << confirm;
  for(int i = 1; i <= (borderLen - ((splitBorderLen - splitConfirmLen) + confirmLen)); i++) {
    cout << " ";
  }
  cout << sym4 << endl;
  cout << strPosition << sym5;
  for(int i = 1; i <= borderLen; i++) {
    cout << sym2;
  }
  cout << sym6 << endl;
  getline(cin, input);
	return;
}

void Add_Notes(string jenis_riwayat, string tahun, string bulan, string hari, string nominal, string keterangan) {
  financialData.type[financialData.counter] = jenis_riwayat;
  financialData.year[financialData.counter] = stoi(tahun);
  financialData.month[financialData.counter] = stoi(bulan);
  financialData.day[financialData.counter] = stoi(hari);
  financialData.amount[financialData.counter] = stoi(nominal);
  financialData.desc[financialData.counter] = keterangan;
  financialData.counter++;

  Save_DB();
  /* for(int i = 0; i <= 99999; i++) {
    if(financialData.type[i] == "") {
      financialData.type[i] = jenis_riwayat;
      financialData.year[i] = stoi(tahun);
      financialData.month[i] = stoi(bulan);
      financialData.day[i] = stoi(hari);
      financialData.amount[i] = stoi(nominal);
      financialData.desc[i] = keterangan;

      break;
    }
  } */

  return;
}

//////////////////////////////////////////////






