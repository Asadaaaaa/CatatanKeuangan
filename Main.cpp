#include <iostream>
#include <fstream>

using namespace std;

/************ Prototype Function ************/

// Prototype Function
void loader();
void notificator(string text, int borderLen, int parentLen);
void Main_Page();

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

// Struct for data financial
struct Data {
  string type[99999] = {};
  int year[99999] = {};
  int month[99999] = {};
  int day[99999] = {};
  int amount[99999] = {};
  string desc[99999] = {};
  int counter = 0;
};

// Declare a Structs
UI ui;
Data data;

//////////////////////////////////////////////



/**************** SMARPL Page ****************/

void History_Transaction() {
  // Variables
  string input;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "             Riwayat Transaksi" << endl;
  cout << ui.border << endl;
  
}

void Financial_Notes_Page() {
  // Variables
  string input;

  // Layouts
  system("cls");
  cout << ui.border << endl;
  cout << "             Menu Catatan Keuangan" << endl;
  cout << ui.border << endl;
  cout << " [1] Rata-rata pengeluaran per hari" << endl;
  cout << " [2] Rata-rata pengeluaran per minggu" << endl;
  cout << " [3] Rata-rata pengeluaran per bulan" << endl;
  cout << " [4] Riwayat transaksi" << endl;
  cout << " [5] Modal awal" << endl;
  cout << " [6] Sisal uang" << endl;
  cout << " [0] Kembali" << endl;
  cout << ui.border << endl;
  
  // Inputs
  cout << "> Pilih menu: " << endl;
  getline(cin, input);

  if(input == "1") {

    return;
  } else if(input == "2") {

    return;
  } else if(input == "3") {

    return;
  } else if(input == "4") {

    return;
  } else if(input == "5") {

    return;
  } else if(input == "6") {

    return;
  } else if(input == "0") {

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
  cout << "            Tambah Riwayat " << jenis_riwayat << endl;
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

    if(intInput <= 7) {
      if(intInput % 2 == 0) {
        if(intInput < 1 || intInput > 30) {
          notificator("Bulan " + bulan + " Memiliki 30 Hari", 38, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      } else {
        if(intInput < 1 || intInput > 31) {
          notificator("Bulan " + bulan + " Memiliki 31 Hari", 38, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      }
    } else {
      if(intInput % 2 == 0) {
        if(intInput < 1 || intInput > 31) {
          notificator("Bulan " + bulan + " Memiliki 31 Hari", 38, 50);

          Add_History_Transaction_Page(jenis_riwayat, tahun, bulan, hari, nominal, keterangan);

          return;
        }
      } else {
        if(intInput < 1 || intInput > 30) {
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
  cout << "             Tambah Catatan Keuangan" << endl;
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
  cout << "            (SISTEM MONETER ANAK RPL)" << endl;
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

    return;
  } else if(input == "2") {

    Choose_History_Transaction_Type_Page();

    return;
  }  else if(input == "3") {

    return;
  }  else if(input == "4") {

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
      data.type[data.counter] = tempData;
      
      getline(dataBase, tempData);
      tempData.erase(0, 8);
      data.year[data.counter] =stoi(tempData);
      
      getline(dataBase, tempData);
      tempData.erase(0, 8);
      data.month[data.counter] = stoi(tempData);

      getline(dataBase, tempData);
      tempData.erase(0, 9);
      data.day[data.counter] = stoi(tempData);

      getline(dataBase, tempData);
      tempData.erase(0, 10);
      data.amount[data.counter] = stoi(tempData);

      getline(dataBase, tempData);
      tempData.erase(0, 8);
      data.desc[data.counter] = stoi(tempData);

      data.counter++;
    }
  }

  dataBase.close();
  return;
}

void Save_DB() {
  // Variables
  ofstream dataBase;

  // Algo
  dataBase.open("db.txt", ios::trunc);
  for(int i = 0; i < data.counter; i++) {
    dataBase << "{" << endl;
    dataBase << "  Type: " << data.type[i] << endl;
    dataBase << "  Year: " << data.year[i] << endl;
    dataBase << "  Month: " << data.year[i] << endl;
    dataBase << "  Day: " << data.year[i] << endl;
    dataBase << "  Amount: " << data.year[i] << endl;
    dataBase << "  Desc: " << data.year[i] << endl;
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
  data.type[data.counter] = jenis_riwayat;
  data.year[data.counter] = stoi(tahun);
  data.month[data.counter] = stoi(bulan);
  data.day[data.counter] = stoi(hari);
  data.amount[data.counter] = stoi(nominal);
  data.desc[data.counter] = keterangan;
  data.counter++;

  Save_DB();
  /* for(int i = 0; i <= 99999; i++) {
    if(data.type[i] == "") {
      data.type[i] = jenis_riwayat;
      data.year[i] = stoi(tahun);
      data.month[i] = stoi(bulan);
      data.day[i] = stoi(hari);
      data.amount[i] = stoi(nominal);
      data.desc[i] = keterangan;

      break;
    }
  } */

  return;
}

//////////////////////////////////////////////






