#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

///buat data layanan
struct dt_layanan{
	int id;
    string id_user;
	string layanan;
	string dokter;
	string waktu;
	int harga;
	struct dt_layanan* next;
    struct dt_layanan* prev;
};

//data antrian
struct antrian{
    string id_pesanan;
	string nama;
    string layanan;
	string dokter;
	string waktu;
	int harga;
    int jumlah;
    int total;
	struct antrian* next;
    struct antrian* prev;
};

struct akun {
    string username;
    string pass;
    string sebagai;
};

dt_layanan *head = NULL;
dt_layanan *tail = NULL;
antrian *FRONT = NULL;
antrian *REAR = NULL;
akun simpan[50] = {{"admin", "admin", "Admin"}, 
{"user", "123", "User"}};

akun *point = simpan;
int panjang;

void menu_admin(){
    system("color F4");
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=               MENU ADMIN                 =" <<endl;
	cout <<setw(100)<<"--------------------------------------------" <<endl;
	cout <<setw(100)<<"=           [1] TAMBAHKAN LAYANAN          =" <<endl;
	cout <<setw(100)<<"=           [2] TAMPILKAN LAYANAN          =" <<endl;
	cout <<setw(100)<<"=           [3] PANGGIL & LIHAT ANTRIAN    =" <<endl;
	cout <<setw(100)<<"=           [4] KELUARKAN ANTRIAN          =" <<endl;
	cout <<setw(100)<<"=           [5] UBAH LAYANAN               =" <<endl;
	cout <<setw(100)<<"=           [6] HAPUS LAYANAN              =" <<endl;
	cout <<setw(100)<<"=           [7] URUTKAN LAYANAN            =" <<endl;
	cout <<setw(100)<<"=           [8] CARI LAYANAN               =" <<endl;
	cout <<setw(100)<<"=           [9] LOGOUT ADMIN               =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(69)<<"PILIH [1-9]: "; 
}
void menu_user(){
    system("color F9");
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=               MENU PASIEN                =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=            [1] DAFTAR ANTRIAN            =" <<endl;
	cout <<setw(100)<<"=            [2] TAMPILKAN ANTRIAN         =" <<endl;
	cout <<setw(100)<<"=            [3] LOGOUT USER               =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(69)<<"PILIH [1-3]: ";
}
void read_menu(dt_layanan *head){
    if (head == NULL){
	    cout <<setw(100)<<"============================================" <<endl;
	    cout <<setw(100)<<"= DATA LAYANAN KOSONG SILAHKAN ISI DAHULU! =" <<endl;
	    cout <<setw(100)<<"============================================" <<endl;
        return;
    }
    
    cout << setw(4) << "ID";
    cout << setw(20) << "NAMA PELAYANAN" ;
    cout << setw(20) << "NAMA DOKTER" ;
    cout << setw(15) << "WAKTU LAYANAN" ;
    cout << setw(15) << "HARGA" << endl;
    while (head != NULL){
        cout << setw(4) << head->id;
        cout << setw(20) << head->layanan ;
        cout << setw(20) << head->dokter ;
        cout << setw(15) << head->waktu ;
        cout << setw(15) << head->harga;
        head = head->next;
        cout << endl;
    }
    cout<<endl;
}

void TXTtoLinklist(dt_layanan **head, dt_layanan **tail){
    panjang = 0;
    string baris, elemen;
	ifstream file;
	stringstream ss;
	file.open("data_layanan.txt");

	dt_layanan *terakhir;
	bool pertama = true;
	
	// Membaca per baris dari file
	while (getline(file, baris)) {
		// Baris dijadikan stringstream
		ss.str(baris);
		
		// Membaca per elemen dari baris
		// dan diubah menjadi linked list
		dt_layanan* nodeBaru = new dt_layanan();
		for (int i = 0; getline(ss, elemen, ','); i++) {
			if (i == 0) {
				nodeBaru->id = stoi(elemen);
			} else if (i == 1) {
				nodeBaru->layanan = elemen;
			} else if (i == 2) {
				nodeBaru->dokter = elemen;
			} else if (i == 3) {
				nodeBaru->waktu = elemen;
			} else if (i == 4) {
				nodeBaru->harga = stoi(elemen);
				nodeBaru->next = NULL;
				if (*head == NULL) {
					nodeBaru->prev = NULL;
					*head = nodeBaru;
					terakhir = nodeBaru;
                    panjang++;
				} else {
					nodeBaru->prev = terakhir;
					terakhir->next = nodeBaru;
                    panjang++;
				}
			}
		}
		*tail = nodeBaru;
		
		// Mencegah variabel terakhir bergerak
		// pada pembacaan baris pertama
		if (pertama) {
			pertama = false;
		} else {
			terakhir = terakhir->next;
		}
		
		// Membersihkan stringstream untuk baris berikutnya
		ss.clear();
	}

	// Menutup file
	file.close();
}

void LinklistToTXT(dt_layanan *front) {
	ofstream out("data_layanan.txt");
	while (front != NULL) {
		out << front->id << ",";
		out << front->layanan << ",";
        out << front->dokter << ",";
		out << front->waktu << ",";
		out << front->harga << endl;
		front = front->next;
	}
	out.close();
}

void LinklistToTxtAntrian(antrian *front) {
	ofstream out("antrian.txt");
	while (front != NULL) {
		out << front->id_pesanan << ",";
        out << front->nama << ",";
		out << front->layanan << ",";
        out << front->dokter << ",";
		out << front->waktu << ",";
		out << front->harga << ",";
        out << front->jumlah << ",";
        out << front->total << endl;
		front = front->next;
	}
	out.close();
}

void TxtToLinklistAntrian(antrian **head, antrian **tail){
    string baris, elemen;
	ifstream file;
	stringstream ss;
	file.open("antrian.txt");

	antrian *terakhir;
	bool pertama = true;
	
	// Membaca per baris dari file
	while (getline(file, baris)) {
		// Baris dijadikan stringstream
		ss.str(baris);
		
		// Membaca per elemen dari baris
		// dan diubah menjadi linked list
		antrian* nodeBaru = new antrian();
		for (int i = 0; getline(ss, elemen, ','); i++) {
			if (i == 0) {
				nodeBaru->id_pesanan = elemen;
			} else if (i == 1) {
                nodeBaru->nama = elemen;
			} else if(i == 2){
				nodeBaru->layanan = elemen;
			} else if (i == 3) {
				nodeBaru->dokter = elemen;
			} else if (i == 4) {
				nodeBaru->waktu = elemen;
            }else if(i == 5){
                nodeBaru->harga = stoi(elemen);
            }else if(i == 6){
                nodeBaru->jumlah = stoi(elemen);
            }else if(i == 7){
                nodeBaru->total = stoi(elemen);
                nodeBaru->next = NULL;
				if (*head == NULL) {
					nodeBaru->prev = NULL;
					*head = nodeBaru;
					terakhir = nodeBaru;
				} else {
					nodeBaru->prev = terakhir;
					terakhir->next = nodeBaru;
                }
            }
		}
		*tail = nodeBaru;
		
		// Mencegah variabel terakhir bergerak
		// pada pembacaan baris pertama
		if (pertama) {
			pertama = false;
		} else {
			terakhir = terakhir->next;
		}
		
		// Membersihkan stringstream untuk baris berikutnya
		ss.clear();
	}

	// Menutup file
	file.close();
}
void create_menu(dt_layanan **head, dt_layanan **tail){
    dt_layanan *baru1 = new dt_layanan();
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=              TAMBAH LAYANAN              =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(72)<<"ID LAYANAN    : ",cin >> baru1->id;
    cout <<setw(72)<<"NAMA LAYANAN  : ",getline(cin >> ws, baru1->layanan);
    cout <<setw(72)<<"NAMA DOKTER   : ",getline(cin >> ws, baru1->dokter);
    cout <<setw(72)<<"WAKTU LAYANAN : ",getline(cin,baru1->waktu);
    cout <<setw(72)<<"HARGA         : ",cin >> baru1 -> harga;
    system("CLS");
    dt_layanan *temp = *head;
    baru1->next = NULL;
    if (*head == NULL){
            baru1->prev = NULL;
            *head = baru1;
            panjang++;
            return;
        }
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = baru1;
    baru1->prev = temp;
    panjang++;
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=         LAYANAN BERHASIL DITAMBAH!       =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    system("pause");
    system("CLS");
}
void update_menu(dt_layanan *head){
    read_menu(head);
    dt_layanan *dataganti = new dt_layanan();
    dt_layanan *prev=NULL;
    dt_layanan *current=NULL;
    system("cls");
    int pilih;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=               UBAH LAYANAN               =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(69)<<"ID Layanan : ";
    cin>>pilih;
    prev=head;
    current=head;
    while(current->id !=pilih){
        current=current->next;
    }
    current->id = pilih;
    cout << setw(69)<<"NAMA LAYANAN  : ", getline(cin >> ws, current->layanan);
    cout << setw(69)<<"NAMA DOKTER   : ", getline(cin >> ws, current->dokter); 
    cout << setw(69)<<"WAKTU LAYANAN : ", getline(cin,current->waktu); 
    cout << setw(69)<<"Harga         : ", cin >> current -> harga;
    current = current->next;
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=         LAYANAN BERHASIL DIUBAH!         =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    system("pause");
    system("CLS");
    
}

void hapus(dt_layanan **head, dt_layanan *del){
    if (*head == NULL || del == NULL){
        return;
    }

    if (*head == del){
        *head = del->next;
    }
        

    if (del->next != NULL){
        del->next->prev = del->prev;
    }

    
    if (del->prev != NULL)
        del->prev->next = del->next;
    delete(del);
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=         LAYANAN BERHASIL DIHAPUS!        =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    panjang--;
}

void delete_menu(dt_layanan **head){
    read_menu(*head);
    int posisi;
    cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=               HAPUS LAYANAN              =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(69)<<"ID Layanan : ", cin >> posisi;
    if (*head == NULL || posisi <= 0){
        return;
    }

    struct dt_layanan* current = *head;
    int i;

    for (int i = 1; current != NULL && i < posisi; i++){
        current = current->next;
    }
        

    if (current == NULL){
        return;
    }
        
    hapus(head, current);
}

void lihat_antrian(antrian *front){
    if(front == NULL){
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=              ANTRIAN KOSONG!             =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
		return;
	}
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=                 ANTRIAN                  =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<""<<endl;
    cout <<setw(77)<<"PANGGIL PASIEN......."                        <<endl;
    cout <<setw(100)<<""<<endl;
    cout << setw(10) << "ID Pesanan" <<"\t";
    cout << setw(10) << "NAMA PASIEN" <<"\t";
    cout << setw(10) << "NAMA LAYANAN" <<"\t" ;
    cout << setw(10) << "DOKTER"  <<"\t";
    cout << setw(10) << "WAKTU LAYANAN" <<"\t" ;
    cout << setw(10) << "Harga (Rp)" <<"\t" ;
    cout << setw(10) << "Jumlah" <<"\t" ;
    cout << setw(10) << "Total Harga (Rp)"  <<"\n";
	while(front != NULL){
        cout << setw(10) << front->id_pesanan <<"\t";
		cout << setw(10) << front->nama <<"\t";
		cout << setw(10) << front -> layanan <<"\t";
		cout << setw(10) << front -> dokter <<"\t";
		cout << setw(10) << front -> waktu <<"\t";
		cout << setw(10) <<front -> harga <<"\t";
        cout << setw(10)  << front -> jumlah <<"\t";
        cout << setw(10) <<front -> total <<"\t";
        cout << endl;
		front= front->next;
	}
	cout << endl;
}
void buat_antrian(antrian **front, antrian **rear, dt_layanan *head, antrian *FRONT){
	antrian *nodeBaru = new antrian();
    int pilih;
    dt_layanan *current = head;
    string id_pesan;
    if (FRONT == NULL){
        id_pesan = "PSN-0001";
    }else{
        while (FRONT->next != NULL){
            FRONT=FRONT->next;
        }
        id_pesan = FRONT->id_pesanan;
        string huruf = id_pesan.substr(0,4);
        string angka = id_pesan.substr(4,4);
        int tambah = stoi(angka)+1;
        angka = "000"+to_string(tambah);
        id_pesan = huruf+angka;   
    }
    
    nodeBaru->id_pesanan = id_pesan;
    cout << setw(69)<<"Masukan nama : ", getline(cin >> ws, nodeBaru->nama); 
    cout << setw(69)<<"ID Layanan   : ", cin>>pilih;
    while(current->id !=pilih){
        head=head->next;
    }
    nodeBaru->layanan = head->layanan;
    nodeBaru->dokter = head->dokter;
    nodeBaru->waktu = head->waktu;
    nodeBaru->harga = head->harga;
    cout << setw(69)<<"Jumlah : ", cin >> nodeBaru->jumlah;
    nodeBaru->total = head->harga * nodeBaru->jumlah;
    cout << setw(69)<<"Total : ", cout << nodeBaru->total << endl;
    // cout << "" << endl;
    system("cls");
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=           ANDA BERHASIL DAFTAR!          =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    antrian *temp = *front;
	nodeBaru->next = NULL;
    if (*front == NULL){
            nodeBaru->prev = NULL;
            *front = nodeBaru;
            return;
        }
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = nodeBaru;
    nodeBaru->prev = temp;
    system("pause");
}

void hapus_antrian(antrian **front){
	if(*front == NULL){
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=              ANTRIAN KOSONG!             =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
		return;
	}

	antrian* temp;
    temp = (*front);
    (*front) = (*front)->next;
    (*front)->prev = NULL;
    delete temp;
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=            ANTRIAN DIKELUARKAN!          =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
//    system("cls");
}

int shellSortLayanan(dt_layanan *front, int n, bool asc) {
	for (int gap = n/2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i += 1) {
			dt_layanan temp = front[i];
			int j;
			if (asc) {
				for (j = i; j >= gap && front[j - gap].layanan > temp.layanan; j -= gap)
					front[j] = front[j - gap];
			} else {
				for (j = i; j >= gap && front[j - gap].layanan < temp.layanan; j -= gap)
					front[j] = front[j - gap];
			}
			front[j] = temp;
		}
	}
	return 0;
}

int shellSortDokter(dt_layanan *front, int n, bool asc) {
	for (int gap = n/2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i += 1) {
			dt_layanan temp = front[i];
			int j;
			if (asc) {
				for (j = i; j >= gap && front[j - gap].dokter > temp.dokter; j -= gap)
					front[j] = front[j - gap];
			} else {
				for (j = i; j >= gap && front[j - gap].dokter < temp.dokter; j -= gap)
					front[j] = front[j - gap];
			}
			front[j] = temp;
		}
	}
	return 0;
}

int shellSortHarga(dt_layanan *front, int n, bool asc) {
	for (int gap = n/2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i += 1) {
			dt_layanan temp = front[i];
			int j;
			if (asc) {
				for (j = i; j >= gap && front[j - gap].harga > temp.harga; j -= gap)
					front[j] = front[j - gap];
			} else {
				for (j = i; j >= gap && front[j - gap].harga < temp.harga; j -= gap)
					front[j] = front[j - gap];
			}
			front[j] = temp;
		}
	}
	return 0;
}

int shellSortReset(dt_layanan *front, int n) {
	for (int gap = n/2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i += 1) {
			dt_layanan temp = front[i];
			int j;
            for (j = i; j >= gap && front[j - gap].id > temp.id; j -= gap)
                front[j] = front[j - gap];

			front[j] = temp;
		}
	}
	return 0;
}
void menu_sort(dt_layanan *head){
    dt_layanan array[panjang];
    dt_layanan *data = head;
    dt_layanan *temp = head;
    dt_layanan *store = head;
    for (int i = 0; i < panjang; i++){
        array[i].id = head->id;
        array[i].layanan = head->layanan;
        array[i].dokter = head->dokter;
        array[i].waktu = head->waktu;
        array[i].harga = head->harga;
        head = head->next;  
    }
	int pli;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=             URUTKAN LAYANAN              =" <<endl;
	cout <<setw(100)<<"--------------------------------------------" <<endl;
    cout <<setw(100)<<"=            URUTKAN BERDASARKAN:          =" <<endl;
    cout <<setw(100)<<"--------------------------------------------" <<endl;
	cout <<setw(100)<<"=           [1] NAMA LAYANAN ASC           =" <<endl;
	cout <<setw(100)<<"=           [2] NAMA LAYANAN DESC          =" <<endl;
	cout <<setw(100)<<"=           [3] NAMA DOKTER ASC            =" <<endl;
	cout <<setw(100)<<"=           [4] NAMA DOKTER DESC           =" <<endl;
	cout <<setw(100)<<"=           [5] HARGA ASC                  =" <<endl;
	cout <<setw(100)<<"=           [6] HARGA DESC                 =" <<endl;
	cout <<setw(100)<<"=           [7] RESET                      =" <<endl;
    cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(69)<<"PILIH [1-7]: "; 
	cin >> pli; cout << endl;
	if (pli == 1) {
		shellSortLayanan(array, panjang, true);
	} else if (pli == 2) {
		shellSortLayanan(array, panjang, false);
	}else if (pli == 3) {
		shellSortDokter(array, panjang, true);
	}else if (pli == 4) {
		shellSortDokter(array, panjang, false);
	}else if (pli == 5) {
		shellSortHarga(array, panjang, true);
	}else if (pli == 6) {
		shellSortHarga(array, panjang, false);
	}else if(pli == 7){
        shellSortReset(array, panjang);
	}else{
    cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(100)<<"=            PILIHAN TIDAK ADA!            =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    }

    for (int i = 0; i < panjang; i++) {
        data->id = array[i].id;
        data->layanan = array[i].layanan;
        data->dokter = array[i].dokter;
        data->waktu = array[i].waktu;
        data->harga = array[i].harga;
        if (i == 0) {
            temp = data;
        } else {
            temp->next = data;
            temp = temp->next;
        }
        data = data->next; 
    }
    read_menu(store);
    shellSortReset(array, panjang);
    return;
}

int JumpSearch(dt_layanan *front, string x, int n) {
	int step = sqrt(n);
	int prev = 0;
	while (front[min(step, n)-1].layanan < x) {
		prev = step;
		step += sqrt(n);
		if (prev >= n)
		return -1;
	}
	while (front[prev].layanan < x) {
		prev++;
		if (prev == min(step, n))
		return -1;
	}
	if (front[prev].layanan == x) {
		return prev;
	}
	return -1;
}
void menu_cari(dt_layanan *front) {
    dt_layanan array[panjang];
	dt_layanan *data = front;
    dt_layanan *temp = front;
    dt_layanan *store = front;
    for (int i = 0; i < panjang; i++){
        array[i].id = head->id;
        array[i].layanan = head->layanan;
        array[i].dokter = head->dokter;
        array[i].waktu = head->waktu;
        array[i].harga = head->harga;
        head = head->next;  
    }
    int i;
	string cari;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=              CARI LAYANAN                =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(71)<<"Nama Layanan : ";
	cin.ignore();
    getline(cin >> ws, cari);
    shellSortLayanan(array, panjang, true);
	i = JumpSearch(array, cari, panjang);
	if (i >= 0) {
        data->id = array[i].id;
        data->layanan = array[i].layanan;
        data->dokter = array[i].dokter;
        data->waktu = array[i].waktu;
        data->harga = array[i].harga;

        system("CLS");
        cout <<setw(100)<<"============================================" <<endl;
        cout <<setw(100)<<"=             LAYANAN DITEMUKAN!           =" <<endl;
	    cout <<setw(100)<<"============================================" <<endl;
        cout << setw(61)<<"ID : " << data->id << endl;
        cout << setw(71)<<"NAMA LAYANAN : " << data->layanan<< endl;
        cout << setw(70)<<"NAMA DOKTER : " << data->dokter << endl;
        cout << setw(72)<<"WAKTU LAYANAN : " << data->waktu << endl;
        cout << setw(68)<<"Harga : Rp. " << data->harga << endl;
        data = data->next;
	} else {
		cout <<setw(100)<<"============================================" <<endl;
        cout <<setw(100)<<"=          LAYANAN TIDAK DITEMUKAN!        =" <<endl;
	    cout <<setw(100)<<"============================================" <<endl;
	}
	shellSortReset(array, panjang);
	
}

void admin(){
	int pilihan;
	while(true){
		menu_admin();
		cin >> pilihan ;
		if(pilihan == 1){
			system("cls");
            create_menu(&head, &tail);
            LinklistToTXT(head);
		}
		else if(pilihan == 2){
			system("cls");
            read_menu(head);
            system("pause");
            system("cls");
		}
        else if(pilihan == 3){
			system("cls");
            lihat_antrian(FRONT);
            system("pause");
            system("cls");
		}
        else if(pilihan == 4){
			system("cls");
            hapus_antrian(&FRONT);
//            LinklistToTxtAntrian(FRONT);
            system("pause");
//            system("cls");
		}
		else if (pilihan == 5){
			system("cls");
            update_menu(head);
            LinklistToTXT(head);
            system("pause");
            system("cls");
		}
		else if(pilihan == 6){
			system("cls");
            delete_menu(&head);
            LinklistToTXT(head);
            system("pause");
            system("cls");
		}
		else if(pilihan == 7){
			system("cls");
            menu_sort(head);
            LinklistToTXT(head);
            system("pause");
            system("cls");
		}
		else if(pilihan == 8){
			system("cls");
            menu_cari(head);
            system("pause");
            system("cls");
		}
		else if(pilihan == 9){
            system("CLS");
			cout <<setw(100)<<"============================================" <<endl;
	        cout <<setw(100)<<"=            KELUAR DARI ADMIN...          =" <<endl;
	        cout <<setw(100)<<"============================================" <<endl;
            system("pause");
			break;
		}else{
            system("CLS");
            cout <<setw(100)<<"============================================" <<endl;
	        cout <<setw(100)<<"=         INPUT SALAH, COBA LAGI...        =" <<endl;
	        cout <<setw(100)<<"============================================" <<endl;
            system("pause");
            system("CLS");
        }
	}
}
void user(){
	int pilihan;
    system("color F9");
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=         HALO PASIEN KLINIK GIGI :)       =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
        system("pause");
        system("cls");
	while(true){
        system("cls");
		menu_user();
		cin >> pilihan ;
		if(pilihan == 1){
            read_menu(head);
            buat_antrian(&FRONT, &REAR, head, FRONT);
            LinklistToTxtAntrian(FRONT);
		}
		else if(pilihan == 2){
            system("cls");
            lihat_antrian(FRONT);
			system("pause");
		}else if(pilihan == 3){
            system("cls");
			cout <<setw(100)<<"============================================" <<endl;
	        cout <<setw(100)<<"=          KELUAR DARI MENU USER...        =" <<endl;
	        cout <<setw(100)<<"============================================" <<endl;
            system("pause");
			break;
		}else{
            system("cls");
            cout <<setw(100)<<"============================================" <<endl;
	        cout <<setw(100)<<"=         INPUT SALAH, COBA LAGI...        =" <<endl;
	        cout <<setw(100)<<"============================================" <<endl;
            system("pause");
            system("CLS");
        }
	}
}

void login(){
		string log_use;
		string log_pass;
		string who;
        ifstream data("pengguna.txt");
        if(data.is_open())
        {
            data >> log_use;
            data >> log_pass;
            data >> who;
        }
        data.close();
        system("CLS");
        cout <<setw(100)<<"============================================" <<endl;
	    cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	    cout <<setw(100)<<"============================================" <<endl;
	    cout <<setw(100)<<"=                   LOGIN                  =" <<endl;
	    cout <<setw(100)<<"============================================" <<endl;
        cout <<setw(69)<<"= Username : "; cin>>log_use;
        cout <<setw(69)<<"= Password : "; cin>>log_pass;
        cout <<"============================================" <<endl;
        cin.clear();
        for(int i =0; i< sizeof(simpan)/sizeof(*point); i++){
            if(point[i].username==log_use && point[i].pass==log_pass){
                who=point[i].sebagai;
                break;
            }
        }
        cout<<"\n\n";
        if(who=="Admin"){
            system("CLS");
            system("color F4");
            cout <<setw(100)<<"============================================" <<endl;
            cout <<setw(100)<<"==            LOGIN BERHASIL!!!           =="<<endl;
            cout <<setw(100)<<"==               HAI ADMIN !!!            =="<<endl;
            cout <<setw(100)<<"============================================" <<endl;
            system("pause");
			system("CLS");
            admin();
        }
        else if(who=="User"){
            system("CLS");
            system("color F9");
            cout <<setw(100)<<"============================================="<<endl;
            cout <<setw(100)<<"==             LOGIN BERHASIL!!!           =="<<endl;
            cout <<setw(100)<<"=   SELAMAT DATANG DI PROGRAM KLINIK GIGI   ="<<endl;
            cout <<setw(100)<<"============================================="<<endl;
            system("pause");
			system("CLS");
            user();
        }
        else {
            system("CLS");
            cout <<setw(100)<<"============================================="<<endl;
            cout <<setw(100)<<"==             LOGIN GAGAL!!!              =="<<endl;
            cout <<setw(100)<<"=     USERNAME / PASSWORD ANDA SALAH!!!     ="<<endl;
            cout <<setw(100)<<"============================================="<<endl;
            system("pause");
        }
}

void regis(){
	string reg_use;
	string reg_pass;
    ofstream myfile("pengguna.txt");
    cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=               REGISTRASI                 =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
    cout <<setw(69)<<"= Username : "; cin>>reg_use; 
    cout <<setw(69)<<"= Password : "; cin>>reg_pass;
    cout <<setw(100)<<"============================================" <<endl;
    myfile << reg_use << endl;
    myfile << reg_pass << endl;   
    myfile.close();
    cin.clear();
    for (int i = 0; i< sizeof(simpan)/sizeof(*point); i++){
        if (point[i].username==""){
            point[i].username = reg_use;
            point[i].pass = reg_pass;
            point[i].sebagai = "User";
            system("CLS");
            cout <<setw(100)<<"============================================="<<endl;
            cout <<setw(100)<<"==           REGISTRASI BERHASIL!!!        =="<<endl;
            cout <<setw(100)<<"============================================="<<endl;
            system("pause");
			system("CLS");
            break;
        }
    }
    panjang++;
}

void menu_login(){
    system("color 07");
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=    PROGRAM ANTRIAN PASIEN KLINIK GIGI    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=                  MENU                    =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(100)<<"=               [1] LOGIN                  =" <<endl;
	cout <<setw(100)<<"=               [2] REGISTRASI             =" <<endl;
	cout <<setw(100)<<"=               [3] EXIT                   =" <<endl;
	cout <<setw(100)<<"============================================" <<endl;
	cout <<setw(69)<<"PILIH [1-3]: ";
}


int main(){
    TXTtoLinklist(&head, &tail);
    TxtToLinklistAntrian(&FRONT, &REAR);
    cout<<panjang;
	string pilih;
	for (int i = 0; i < 100; i++) {
        if (point[i].username == "") {
                break;
        }
    }
    while(true){
        system("CLS");
        menu_login();
        cin >>pilih;
        if (pilih == "1" || pilih =="LOGIN" || pilih == "login"){
            login();
        } else if (pilih == "2" || pilih =="REGISTRASI" || pilih == "registrasi"){
            system("CLS");
            regis();
        } else if (pilih == "3" || pilih =="KELUAR" || pilih =="keluar"){
            system("CLS");
            cout <<setw(100)<<"============================================" <<endl;
	        cout <<setw(100)<<"=                TERIMAKASIH               =" <<endl;
	        cout <<setw(100)<<"============================================" <<endl;
            break;
        }else{
            cout <<setw(100)<<"============================================" <<endl;
	        cout <<setw(100)<<"=               INPUT SALAH !              =" <<endl;
	        cout <<setw(100)<<"============================================" <<endl;
            system("pause");
            system("CLS");
        }
    }
    return 0;
}
