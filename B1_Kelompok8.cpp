#include <iostream> // digunakan untuk masukan dan keluaran pada program C++
#include <string.h> // digunakan untuk berbagai operasi terkait string seperti penggabungan string, perbandingan string dan pencarian
#include <sstream> // digunakan untuk mengkonversi antara tipe data dan string
#include <fstream> // digunakan untuk operasi file
#include <conio.h> // digunakan untuk operasi masukan/keluaran karakter dan mengatur tampilan layar
#include <stdio.h> // digunakan sebagai standar input output operasi
#include <windows.h> // digunakan dalam lingkungan Windows untuk mengakses fungsi sistem, seperti operasi berkas, GUI, jendela, dll
using namespace std;

// Struct untuk data size dan stok pada parfume
struct Size
{
    string size;
    int stok;
};

// Struct untuk data parfume
struct parfum
{
    string nama;
    int harga;
    Size size_stok[3];
};

// Struct untuk data akun (login dan register)
struct data_akun
{
    string username;
    string password;
    string Nama;
};

// Struct untuk data orderan
struct order
{
    string nama_akun;
    string nama_parfum;
    string size;
};

// 
struct Node
{
    order ord;
    Node *next;
};

// Struct untuk data riwayat pembelian
struct data_riwayat
{
    string nama_akun;
    string nama_parfum;
    string size;
};

// Untuk membuat objek 'file' dari kelas 'fstream'
fstream file;

parfum parfume[100]; // deklarasi array 'parfume' yang dapat menyimpan data parfum hingga 100 elemen
data_akun akun[100]; // deklarasi array 'akun' yang dapat menyimpan data akun hingga 100 elemen
data_riwayat riwayat[100]; // deklarasi array 'riwayat' yang dapat menyimpan data riwayat hingga 100 elemen

void read_file_parfum();
void save_file_parfum();

void save_file_akun();
void read_file_akun();

void save_file_order(Node *head);
void read_file_order(Node **head, Node **tail);

void tambah_data();
void lihat_data_parfum(int update);
void lihat_detail(int see);

void lihat_data_user();
void ubah_data(int ubah);
void hapus_data(int hapus);
int cari_data(string dicari, int urutan);

int shellSort();

int searching_data(string cari);

void menu_parfum();
void menu_utama();
void menu_cari();

void bersih();
void enter();
void keluar();

// Fungsi 'banyak_parfum' digunakan untuk menghitung berapa banyak parfum yang ada dalam array 'parfume'.
int banyak_parfum()
{
    int i = 0;

    // Loop while digunakan untuk mengiterasi melalui elemen-elemen array 'parfume' 
    // dan berhenti ketika ditemukan elemen dengan nama parfum yang kosong ("").
    while (parfume[i].nama != "")
    {
        i++;
    }

    // Fungsi ini mengembalikan nilai 'i', yang merupakan jumlah parfum yang ditemukan dalam array 'parfume'.
    return i;
}


// Fungsi 'banyak_akun' digunakan untuk menghitung berapa banyak akun yang ada dalam array 'akun'.
int banyak_akun()
{
    int i = 0;

    // Loop while digunakan untuk mengiterasi melalui elemen-elemen array 'akun' 
    // dan berhenti ketika ditemukan elemen dengan username akun yang kosong ("").
    while (akun[i].username != "")
    {
        i++;
    }

    // Fungsi ini mengembalikan nilai 'i', yang merupakan jumlah akun yang ditemukan dalam array 'akun'.
    return i;
}

// Fungsi 'banyak_riwayat' digunakan untuk menghitung berapa banyak riwayat yang ada dalam array 'riwayat'.
int banyak_riwayat()
{
    int i = 0;

    // Loop while digunakan untuk mengiterasi melalui elemen-elemen array 'riwayat' 
    // dan berhenti ketika ditemukan elemen dengan nama akun yang kosong ("").
    while (riwayat[i].nama_akun != "")
    {
        i++;
    }
    // Fungsi ini mengembalikan nilai 'i', yang merupakan jumlah riwayat yang ditemukan dalam array 'riwayat'.
    return i;
}

// Fungsi 'color' digunakan untuk mengubah warna teks konsol.
void color(int color)
{
    // Menggunakan fungsi Windows 'SetConsoleTextAttribute' untuk mengubah atribut teks konsol, seperti warna teks dan latar belakang.
    // Fungsi ini memerlukan handle ke output konsol (STDOUT_HANDLE) dan warna yang diinginkan sebagai argumen
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Fungsi 'menu' digunakan untuk menampilkan menu dengan pilihan yang dapat dipilih menggunakan panah atas/bawah dan Enter.
int menu(string jenis[], int banyak, string judul)
{
    // Inisialisasi variable
    bool menu_end = false; // Variable digunakan untuk mengontrol perulangan dalam program.
    int counter = 1; // Digunakan untuk melacak elemen menu yang sedang dipilih oleh pengguna dalam program. 
    // dengan mengatur nilai awalnya sebagai 1, berarti dimulai dari elemen menu pertama.
    
    // Set array 'Set' dengan nilai awal 175.
    int Set[banyak] = {175}; 


    for (int i = 1; i < banyak; i++)
    {
        // Mengatur nilai elemen ke-i dalam array Set menjadi 7, 
        // sehingga angka 7 digunakan untuk mewakili warna atau penanda tertentu dalam tampilan menu
        Set[i] = 7; 
    }

    while (!menu_end)
    {
        bersih();
        cout << "==================================" << endl;
        cout << judul << endl;
        cout << "==================================" << endl;

        // Menampilkan daftar opsi menu dengan nomor dan judul.
        for (int i = 0; i < banyak; i++)
        {
            string awu = jenis[i];
            color(7);
            cout << "|";
            color(Set[i]);
            cout << "  " << i + 1 << "  ";
            color(7);
            cout << "| ";
            cout << jenis[i] << endl;
            color(7);
        }

        cout << "==================================" << endl;
        cout << "   Pilih dengan panah (up/down)   " << endl;
        cout << "        Enter untuk masuk         " << endl;

        char key = _getch();

        if (key == 72 && (counter > 1))
        {
            counter--;
        }

        if (key == 80 && (counter < banyak))
        {
            counter++;
        }

        if (key == '\r')
        {
            color(7);
            return counter; // Mengembalikan nomor pilihan yang dipilih.
        }

        for (int i = 0; i < banyak; i++)
        {
            Set[i] = 7;
            if (i == counter - 1)
            {
                Set[i] = 175; // Mengganti tampilan pilihan yang aktif dengan warna yang berbeda (175).
            }
        }
    }
}

// Fungsi 'read_file_akun' digunakan untuk membaca data akun dari file "akun.txt" dan memasukkannya ke dalam array 'akun'.
void read_file_akun()
{
    int i = 0;

    // Membuka file "akun.txt" untuk membaca (ios::in)
    file.open("akun.txt", ios::in);

    // Memeriksa apakah file berhasil dibuka.
    if (!file.is_open())
    {
        // Jika file tidak terbuka, maka coba membukanya dalam mode tulis ('ios::out').
        file.open("akun.txt", ios::out);
        
        // Kemudian, tutup file.
        file.close();
    }
    else
    {
        // Jika file berhasil dibuka, baca data akun dari file.
        while (!file.eof())
        {
            // Gunakan getline untuk membaca username, Nama, dan password dari file dengan pemisah koma (',') dan newline ('\n').
            getline(file, akun[i].username, ',');
            getline(file, akun[i].Nama, ',');
            getline(file, akun[i].password, '\n');
            
            // Tambahkan indeks untuk menggerakkan ke elemen akun berikutnya
            i++;
        }
    }

    // Menutup file
    file.close();
}

// Fungsi 'save_file_akun' digunakan untuk menyimpan data akun ke dalam file 'akun.txt'.
void save_file_akun()
{
    // Membuka file 'akun.txt' untuk penulisan (ios::out)
    file.open("akun.txt", ios::out);

    int i = 0;

    // Loop while digunakan untuk mengiterasi melalui elemen-elemen array 'akun'
    // dan berhenti ketika ditemukan elemen dengan username kosong ("").
    while (akun[i].username != "")
    {
        // Menyimpan data dari array 'akun' ke variabel lokal
        string username = akun[i].username;
        string Nama = akun[i].Nama;
        string password = akun[i].password;

        // Menulis data akun ke dalam file 'akun.txt' dengan format yang sesuai
        file << username << "," << Nama << "," << password << "\n";

        i++;
    }

    // Menutup file setelah selesai penulisan
    file.close();
}

// Fungsi 'read_file_parfum' digunakan untuk membaca data parfum dari file 'parfum.txt'.
void read_file_parfum()
{
    int i = 0;

    // Membuka file 'parfum.txt' untuk membaca data.
    file.open("parfum.txt", ios::in);

    // Memeriksa apakah file berhasil dibuka.
    if (!file.is_open())
    {
        // Jika file tidak dapat dibuka, maka buat file baru.
        file.open("parfum.txt", ios::out);
        file.close();
    }
    else
    {
        // Jika file berhasil dibuka, baca data parfum dari file.
        while (!file.eof())
        {
            string stk1, stk2, stk3;

            // Membaca data parfum dari file menggunakan getline dan >>.
            getline(file, parfume[i].nama, ',');
            file >> parfume[i].harga;
            file.ignore();
            getline(file, parfume[i].size_stok[0].size, ',');
            getline(file, parfume[i].size_stok[1].size, ',');
            getline(file, parfume[i].size_stok[2].size, ',');
            getline(file, stk1, ',');
            getline(file, stk2, ',');
            getline(file, stk3, '\n');

            // Mengonversi string stok menjadi integer menggunakan stringstream.
            stringstream stk1_int(stk1), stk2_int(stk2), stk3_int(stk3);
            stk1_int >> parfume[i].size_stok[0].stok;
            stk2_int >> parfume[i].size_stok[1].stok;
            stk3_int >> parfume[i].size_stok[2].stok;

            i++;
        }

        // Menutup file setelah selesai membaca.
        file.close();
    }
}


// Fungsi 'save_file_parfum' digunakan untuk menyimpan data parfum ke dalam file "parfum.txt".
void save_file_parfum()
{
    // Membuka file "parfum.txt" untuk ditulis (ios::out).
    file.open("parfum.txt", ios::out);

    int i = 0;

    // Loop while digunakan untuk iterasi melalui array 'parfume' dan menyimpan data ke dalam file.
    while (parfume[i].nama != "")
    {
        // Menyimpan informasi parfum, harga, dan stok untuk masing-masing ukuran ke dalam variabel.
        string nama = parfume[i].nama;
        int harga = parfume[i].harga;
        int stk1 = parfume[i].size_stok[0].stok;
        int stk2 = parfume[i].size_stok[1].stok;
        int stk3 = parfume[i].size_stok[2].stok;

        // Menulis data ke dalam file dengan format tertentu.
        file << nama << "," << harga << ","
             << "50 ML"
             << ","
             << "100 ML"
             << ","
             << "150 ML"
             << "," << stk1 << ","
             << stk2 << "," << stk3 << endl;

        i++;
    }

    // Menutup file setelah selesai menulis.
    file.close();
}


// Fungsi 'read_file_order' digunakan untuk membaca data order dari file "orderan.txt" dan mengisi linked list.
void read_file_order(Node **head, Node **tail)
{
    // Membuka file "orderan.txt" untuk mode baca (ios::in).
    file.open("orderan.txt", ios::in);

    // Memeriksa apakah file berhasil dibuka.
    if (!file.is_open())
    {
        // Jika file tidak dapat dibuka, maka file akan dibuat.
        file.open("orderan.txt", ios::out);
        file.close();
    }
    else
    {
        // Membaca data dari file hingga akhir (eof).
        while (!file.eof())
        {
            string nama, parfum, size;

            // Menggunakan getline untuk membaca data terpisah oleh koma (',') atau baris baru ('\n').
            getline(file, nama, ',');
            getline(file, parfum, ',');
            getline(file, size, '\n');

            // Mengecek apakah nama kosong, jika ya, keluar dari loop.
            if (nama == "")
            {
                break;
            }

            // Membuat node baru untuk menyimpan data order.
            Node *NodeBaru = new Node;

            // Mengisi data order ke dalam node baru.
            NodeBaru->ord.nama_akun = nama;
            NodeBaru->ord.nama_parfum = parfum;
            NodeBaru->ord.size = size;
            NodeBaru->next = NULL;

            // Menambahkan node baru ke dalam linked list.
            if (*head == NULL)
            {
                *head = NodeBaru;
            }
            else
            {
                (*tail)->next = NodeBaru;
            }
            *tail = NodeBaru;
        }
    }

    // Menutup file setelah selesai membaca.
    file.close();
}


// Fungsi 'save_file_order' digunakan untuk menyimpan data order ke dalam file "orderan.txt".
void save_file_order(Node *head)
{
    // Membuka file "orderan.txt" untuk penulisan.
    file.open("orderan.txt", ios::out);

    // Pointer 'temp' digunakan untuk mengiterasi melalui linked list 'head'.
    Node *temp = head;

    // Loop while digunakan untuk menulis setiap data order ke dalam file.
    while (temp != NULL)
    {
        // Mengambil data order dari node saat ini.
        string nama = temp->ord.nama_akun;
        string parfum = temp->ord.nama_parfum;
        string size = temp->ord.size;

        // Menulis data order ke dalam file dengan format yang ditentukan.
        file << nama << ',' << parfum << ',' << size << endl;

        // Pindah ke node selanjutnya dalam linked list.
        temp = temp->next;
    }

    // Menutup file setelah selesai penulisan.
    file.close();
}

// Fungsi 'read_file_riwayat' digunakan untuk membaca data riwayat dari file "riwayat.txt".
void read_file_riwayat()
{
    int i = 0;

    // Membuka file "riwayat.txt" untuk operasi membaca.
    file.open("riwayat.txt", ios::in);

    // Memeriksa apakah file berhasil dibuka.
    if (!file.is_open())
    {
        // Jika file tidak dapat dibuka, maka buat file baru.
        file.open("riwayat.txt", ios::out);
        file.close();
    }
    else
    {
        // Jika file berhasil dibuka, baca data dari file.
        while (!file.eof())
        {
            // Membaca data dari file menggunakan getline dengan pemisah ',' dan '\n'.
            getline(file, riwayat[i].nama_akun, ',');
            getline(file, riwayat[i].nama_parfum, ',');
            getline(file, riwayat[i].size, '\n');

            i++;
        }

        // Menutup file setelah selesai membaca.
        file.close();
    }
}

// Fungsi 'save_file_riwayat' digunakan untuk menyimpan data riwayat ke dalam file "riwayat.txt".
void save_file_riwayat()
{
    // Membuka file "riwayat.txt" untuk penulisan (ios::out).
    file.open("riwayat.txt", ios::out);

    int i = 0;

    // Menggunakan loop while untuk menulis setiap entri riwayat ke dalam file.
    while (riwayat[i].nama_akun != "")
    {
        // Mengambil data dari setiap entri riwayat.
        string nama = riwayat[i].nama_akun;
        string parfum = riwayat[i].nama_parfum;
        string size = riwayat[i].size;

        // Menulis data ke dalam file dengan format: nama,parfum,size.
        file << nama << "," << parfum << "," << size << endl;

        i++;
    }

    // Menutup file setelah selesai penulisan.
    file.close();
}

// Fungsi 'enqueue' digunakan untuk menambahkan pesanan baru ke dalam antrian.
void enqueue(Node **head, Node **tail, string spt, string uk, string cari)
{
    // Membuat node baru untuk menyimpan informasi pesanan.
    Node *NodeBaru = new Node;
    
    // Mengisi data pesanan pada node baru.
    NodeBaru->ord.nama_parfum = spt;
    NodeBaru->ord.nama_akun = cari;
    NodeBaru->ord.size = uk;
    
    // Menetapkan pointer 'next' node baru menjadi NULL karena node baru akan menjadi node terakhir.
    NodeBaru->next = NULL;

    // Memeriksa apakah antrian kosong.
    if (*head == NULL)
    {
        // Jika antrian kosong, maka node baru menjadi elemen pertama dan terakhir.
        *head = NodeBaru;
    }
    else
    {
        // Jika antrian tidak kosong, maka node baru ditambahkan ke belakang antrian.
        (*tail)->next = NodeBaru;
    }

    // Node baru menjadi elemen terakhir dalam antrian.
    *tail = NodeBaru;
}

// Fungsi 'dequeue' digunakan untuk memproses dan menghapus elemen pertama dari antrian.
void dequeue(Node **head)
{
    // Memeriksa apakah antrian kosong.
    if (*head == NULL)
    {
        bersih(); 
        cout << "| ========================== |" << endl;
        cout << "| ==  Tidak ada antrian   == |" << endl;
        cout << "| ========================== |" << endl;
        cout << "| ENTER..."; 
        getch();
        return;
    }

    bersih(); 
    cout << "==========================" << endl;
    cout << "| Antrian" << endl;
    cout << "==========================" << endl;

    // Menampilkan informasi dari elemen pertama dalam antrian.
    cout << "| Username : " << (*head)->ord.nama_akun << endl;
    cout << "| Parfum   : " << (*head)->ord.nama_parfum << endl;
    cout << "| Size     : " << (*head)->ord.size << endl;
    cout << "==========================" << endl;

    cout << "| Proses Orderan ?" << endl;
    cout << "==========================" << endl;
    cout << "| ENTER..." << endl;
    getch(); 

    // Menampilkan pilihan untuk memproses atau tidak memproses orderan.
    string orderan[]{
        "ya",
        "tidak"};
    int order = menu(orderan, 2, "yakin memproses orderan?");

    if (order == 1) // Jika admin memilih untuk memproses orderan
    {
        int index = banyak_riwayat();

        // Menyimpan informasi orderan ke dalam riwayat.
        riwayat[index].nama_akun = (*head)->ord.nama_akun;
        riwayat[index].nama_parfum = (*head)->ord.nama_parfum;
        riwayat[index].size = (*head)->ord.size;

        Node *temp = *head;
        *head = (*head)->next;
        delete temp; // Menghapus elemen pertama dari antrian.
    }

    // Menyimpan perubahan ke file setelah pemrosesan antrian.
    save_file_order(*head);
    save_file_riwayat();
}


// Fungsi 'display' digunakan untuk menampilkan informasi order pada layar.
void display(Node *head)
{
    bersih(); // Memanggil fungsi 'bersih' untuk membersihkan tampilan layar.

    // Memeriksa apakah antrian tidak kosong (head tidak NULL).
    if (head != NULL)
    {
        // Menampilkan judul dan garis pemisah di layar.
        cout << "==================================" << endl;
        cout << "| Orderan" << endl;
        cout << "==================================" << endl;

        // Menggunakan loop while untuk iterasi melalui setiap node dalam antrian.
        while (head != NULL)
        {
            // Menampilkan informasi dari setiap node, seperti username, nama parfum, dan ukuran.
            cout << "| Username : " << head->ord.nama_akun << endl;
            cout << "| Parfum : " << head->ord.nama_parfum << endl;
            cout << "| Size : " << head->ord.size << endl;

            // Pindah ke node berikutnya dalam antrian.
            head = head->next;
        }
    }
    else
    {
        // Jika antrian kosong, menampilkan pesan bahwa tidak ada antrian.
        bersih();
        cout << "| ========================== |" << endl;
        cout << "| ==  Tidak ada antrian   == |" << endl;
        cout << "| ========================== |" << endl;
    }
}

// Fungsi 'lihat_detail_akun' digunakan untuk menampilkan detail akun berdasarkan indeks yang diberikan.
void lihat_detail_akun(int see)
{
    bersih(); 

    // Menampilkan informasi detail akun, termasuk username dan nama.
    cout << "===========================" << endl;
    cout << "| " << akun[see - 1].username << endl;
    cout << "===========================" << endl;
    cout << "| Nama : " << akun[see - 1].Nama << endl;
    cout << "===========================" << endl;
    cout << "| ENTER..." << getch();
}


// Fungsi 'lihat_data_user' digunakan untuk menampilkan data pengguna.
void lihat_data_user()
{
    bersih(); 

    // Array 'akunz' digunakan untuk menyimpan nama pengguna dari akun yang ada.
    string akunz[banyak_akun()];

    // Memeriksa apakah terdapat akun yang tersimpan.
    if (banyak_akun() != 0)
    {
        // Loop 'for' digunakan untuk menampilkan daftar nama pengguna beserta nomor urutnya.
        for (int i = 0; i < banyak_akun(); i++)
        {
            cout << "| " << i + 1 << ". " << akun[i].username << endl;
            akunz[i] = akun[i].username;
        }

        // Memanggil fungsi 'menu' untuk memilih salah satu akun dari daftar.
        int see = menu(akunz, banyak_akun(), "| Data User");

        // Memanggil fungsi 'lihat_detail_akun' untuk menampilkan detail akun yang dipilih.
        lihat_detail_akun(see);
    }
}

// Fungsi 'display_riwayat' digunakan untuk menampilkan riwayat order pada layar.
void display_riwayat()
{
    bersih(); // Memanggil fungsi 'bersih' untuk membersihkan tampilan layar.

    // Menampilkan judul dan garis pemisah di layar.
    cout << "==================================" << endl;
    cout << "| Riwayat Order" << endl;
    cout << "==================================" << endl;

    // Menggunakan loop 'for' untuk iterasi melalui riwayat yang telah tersimpan.
    for (int i = 0; i < banyak_riwayat(); i++)
    {
        // Menampilkan informasi riwayat, seperti username, nama parfum, dan ukuran.
        cout << "| Username : " << riwayat[i].nama_akun << endl;
        cout << "| Parfum : " << riwayat[i].nama_parfum << endl;
        cout << "| Size : " << riwayat[i].size << endl;

        // Menampilkan garis pemisah setelah setiap entri riwayat.
        cout << "==================================" << endl;
    }
}

// Fungsi 'tambah_data' digunakan untuk menambahkan data parfum ke dalam array 'parfume'.
void tambah_data()
{
    bersih(); // Memanggil fungsi 'bersih' untuk membersihkan tampilan layar.
    int panjang = banyak_parfum(); // Mendapatkan jumlah parfum yang sudah ada.

    // Menampilkan header untuk proses penambahan data parfum.
    cout << "| ===================== |" << endl;
    cout << "| ==== Tambah data ==== |" << endl;
    cout << "| ===================== |" << endl;

    int jumlah;
    
    // Meminta input jumlah data yang ingin ditambahkan dari admin.
    cout << "| Masukkan banyak data yang ingin ditambah = ";
    cin >> jumlah;

    // Memastikan input jumlah adalah bilangan bulat.
    while (cin.fail())
    {
        fflush(stdin);
        cout << "| Mohon Input dengan bilangan !" << endl;
        cin.clear();
        cout << "| Masukkan banyak data yang ingin ditambah = ";
        cin >> jumlah;
    }

    string uk1 = "50 ML";
    string uk2 = "100 ML";
    string uk3 = "150 ML";

    // Loop untuk memproses penambahan data sebanyak yang diminta admin.
    for (int i = 0; i < jumlah; i++)
    {
        bersih();
        cout << "=========================" << endl;
        cout << "| Tambah data ke-" << i + 1 << " = " << endl;
        fflush(stdin);
        cout << "=========================" << endl;

        // Meminta input nama parfum.
        cout << "| Nama parfum    : ";
        getline(cin, parfume[panjang].nama);
        fflush(stdin);

        // Loop untuk memastikan input harga dan stok adalah bilangan bulat.
        while (true)
        {
            cout << "| Harga parfum   : ";
            cin >> parfume[panjang].harga;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "| Harga harus angka!" << endl;
                continue;
            }

            // Meminta input dan memastikan stok untuk masing-masing ukuran adalah bilangan bulat.
            cout << "| Stok 50 ML : ";
            cin >> parfume[panjang].size_stok[0].stok;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "| Stok harus angka!" << endl;
                continue;
            }
            parfume[panjang].size_stok[0].size = uk1;

            cout << "| Stok 100 ML : ";
            cin >> parfume[panjang].size_stok[1].stok;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "| Stok harus angka!" << endl;
                continue;
            }
            parfume[panjang].size_stok[1].size = uk2;

            cout << "| Stok 150 ML : ";
            cin >> parfume[panjang].size_stok[2].stok;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "| Stok harus angka!" << endl;
                continue;
            }
            parfume[panjang].size_stok[2].size = uk3;

            cout << "=========================" << endl;

            // Memastikan keluar dari loop setelah berhasil menambahkan data dan menyimpan ke file.
            break;
        }

        // Menyimpan data parfum ke dalam file.
        save_file_parfum();
        
        // Menambahkan panjang untuk mengakomodasi data baru.
        panjang++;
    }
}

// Fungsi 'menu_admin' digunakan untuk menampilkan menu admin dan mengelola operasi terkait admin.
void menu_admin(bool *admin_end, Node **head, Node **tail)
{
    bersih(); // Memanggil fungsi 'bersih' untuk membersihkan tampilan layar.

    // Array 'menu_adm' berisi daftar opsi menu yang dapat dipilih oleh admin.
    string menu_adm[] = {
        "Parfum",
        "Lihat Antrian",
        "Proses Antrian",
        "List User",
        "Riwayat Antrian",
        "Logout"};

    // Memanggil fungsi 'menu' untuk menampilkan menu dan mengembalikan pilihan yang dipilih oleh admin.
    int pilih = menu(menu_adm, 6, "| Admin");

    // Menggunakan pernyataan switch untuk mengeksekusi perintah yang sesuai berdasarkan pilihan admin.
    switch (pilih)
    {
    case 1:
        menu_parfum(); // Memanggil fungsi 'menu_parfum' untuk mengelola data parfum.
        break;
    case 2:
        display(*head); // Memanggil fungsi 'display' untuk menampilkan antrian.
        enter(); // Menunggu input dari admin sebelum melanjutkan.
        break;
    case 3:
        dequeue(head); // Memanggil fungsi 'dequeue' untuk memproses antrian.
        break;
    case 4:
        lihat_data_user(); // Memanggil fungsi 'lihat_data_user' untuk melihat data pengguna.
        break;
    case 5:
        display_riwayat(); // Memanggil fungsi 'display_riwayat' untuk menampilkan riwayat antrian.
        enter(); // Menunggu input dari admin sebelum melanjutkan.
        break;
    case 6:
        *admin_end = true; // Mengatur 'admin_end' menjadi 'true' untuk keluar dari sesi admin.
        break;
    }
}

//Fungsi ini digunakan untuk CRUD data parfume yang di pegang oleh admin.
void menu_parfum()
{
    // Membersihkan layar sebelum menampilkan menu parfum.
    bersih();

    // Array string yang berisi opsi-opsi menu parfum.
    string menu_parfum[] = {
        "Tambah Data",      // Opsi 1: Menu untuk menambahkan data parfum.
        "Lihat Data",       // Opsi 2: Menu untuk melihat data parfum.
        "Ubah Data",        // Opsi 3: Menu untuk mengubah data parfum.
        "Hapus Data",       // Opsi 4: Menu untuk menghapus data parfum.
        "Cari Data", // Opsi 5: Menu yang belum berfungsi untuk mencari data parfum.
        "Kembali"           // Opsi 6: Kembali ke menu sebelumnya.
    };

    bool kondisi = false;
    while (!kondisi)
    {
        // Menampilkan menu parfum dan meminta pengguna memilih opsi.
        int pilih = menu(menu_parfum, 6, "|        Pendataan Parfum        |");

        // Menggunakan struktur switch untuk menangani pilihan pengguna.
        switch (pilih)
        {
        case 1:
            // Memanggil fungsi tambah_data() untuk menambahkan data parfum.
            tambah_data();
            // Mengurutkan data parfum dengan shellSort().
            shellSort();
            // Menyimpan data parfum ke dalam file.
            save_file_parfum();
            enter();
            break;
        case 2:
            // Menampilkan data parfum dengan memanggil fungsi lihat_data_parfum(0).
            lihat_data_parfum(0);
            // Mengurutkan data parfum dengan shellSort().
            shellSort();
            // Menyimpan data parfum ke dalam file.
            save_file_parfum();
            enter();
            break;
        case 3:
            // Menampilkan data parfum dengan memanggil fungsi lihat_data_parfum(1).
            lihat_data_parfum(1);
            // Mengurutkan data parfum dengan shellSort().
            shellSort();
            // Menyimpan data parfum ke dalam file.
            save_file_parfum();
            enter();
            break;
        case 4:
            // Menampilkan data parfum dengan memanggil fungsi lihat_data_parfum(2).
            lihat_data_parfum(2);
            // Mengurutkan data parfum dengan shellSort().
            shellSort();
            // Menyimpan data parfum ke dalam file.
            save_file_parfum();
            enter();
            break;
        case 5:
            // Memanggil fungsi menu_cari() yang belum berfungsi untuk mencari data parfum.
            menu_cari();
            enter();
            break;
        case 6:
            // Mengubah nilai variabel kondisi menjadi true untuk kembali ke menu sebelumnya.
            kondisi = true;
            break;
        }
    }
}

//Fungsi ini digunakan untuk mengkonfirmasi dan memproses pesanan pelanggan, serta mengurangi stok parfum yang dipesan.
void menu_order(int index, string cari, Node **head, Node **tail, int index2)
{
    // Array string yang berisi opsi untuk konfirmasi pesanan.
    string orderan[]{
        "ya",
        "tidak"};

    // Menampilkan menu konfirmasi pesanan dan meminta pengguna untuk memilih (ya/tidak).
    int order = menu(orderan, 2, "Apakah yakin ingin order?");

    // Jika pengguna memilih "ya" (opsi 1):
    if (order == 1)
    {
        // Mendapatkan nama parfum dari indeks yang diberikan.
        string parfum = parfume[index].nama;

        // Mendapatkan ukuran dari indeks yang diberikan.
        string size = parfume[index].size_stok[index2].size;

        // Memasukkan pesanan ke dalam antrian dengan memanggil fungsi enqueue().
        enqueue(head, tail, parfum, size, cari);

        // Mengurangi stok parfum sesuai dengan pesanan yang dimasukkan.
        parfume[index].size_stok[index2].stok = parfume[index].size_stok[index2].stok - 1;

        // Membersihkan layar.
        bersih();

        // Menampilkan pesan konfirmasi bahwa pesanan telah dimasukkan.
        cout << "| ========================== |" << endl;
        cout << "| ==   Order Dimasukkan   == |" << endl;
        cout << "| ========================== |" << endl;
    }
    else
    {
        // Jika pengguna memilih "tidak" (opsi 2), keluar dari fungsi.
        return;
    }
}

//Fungsi ini digunakan untuk memilih parfum dan ukuran yang ingin dipesan, serta menghandle situasi ketika stok parfum habis.
void mengorder(string cari, Node **head, Node **tail)
{
    // Membersihkan layar sebelum menampilkan menu untuk memesan parfum.
    bersih();

    // Membuat array string yang akan digunakan untuk menampilkan daftar parfum yang tersedia.
    string prfm[banyak_parfum()];

    // Menampilkan daftar parfum yang tersedia dan menyimpan nama parfum dalam array prfm.
    for (int i = 0; i < banyak_parfum(); i++)
    {
        cout << "| " << i + 1 << ". " << parfume[i].nama << endl;
        prfm[i] = parfume[i].nama;
    }

    // Meminta pengguna untuk memilih salah satu parfum dari daftar.
    int see = menu(prfm, banyak_parfum(), "| Data parfum |");

    // Membuat array string yang akan digunakan untuk menampilkan pilihan ukuran parfum.
    string size[3];

    // Menampilkan pilihan ukuran parfum yang tersedia dan menyimpan ukuran dalam array size.
    for (int i = 0; i < 3; i++)
    {
        cout << "| " << i + 1 << ". " << parfume[see - 1].size_stok[i].size << endl;
        size[i] = parfume[see - 1].size_stok[i].size;
    }

    // Meminta pengguna untuk memilih ukuran parfum yang ingin dipesan.
    int uk = menu(size, 3, parfume[see - 1].nama) - 1;

    // Jika stok parfum tersedia (stok tidak sama dengan 0), maka pesanan dapat dimasukkan.
    if (parfume[see - 1].size_stok[uk].stok != 0)
    {
        // Memanggil fungsi menu_order() untuk mengkonfirmasi dan memproses pesanan.
        menu_order(see - 1, cari, head, tail, uk);
    }
    else
    {
        // Jika stok parfum habis, menampilkan pesan yang menginformasikan bahwa stok habis.
        string ulang[]{
            "ya",
            "tidak"};
        bersih();
        cout << "| ========================= |" << endl;
        cout << "| ==  Stok parfum Habis  == |" << endl;
        cout << "| ========================= |" << endl;
        cout << "| ENTER..." << getch();

        // Meminta pengguna apakah ingin mencoba mengorder ulang.
        int order = menu(ulang, 2, "| Apakah ingin mengorder ulang?");
        
        // Jika pengguna memilih "ya" (opsi 1), maka fungsi mengorder dipanggil kembali.
        if (order == 1)
        {
            mengorder(cari, head, tail);
        }
        else
        {
            // Jika pengguna memilih "tidak" (opsi 2), membersihkan layar.
            bersih();
        }
    }
}

//Fungsi ini digunakan untuk menampilkan daftar parfum yang tersedia dan melakukan tindakan berdasarkan nilai update, seperti mengubah, menghapus, atau melihat detail parfum.
void lihat_data_parfum(int update)
{
    // Membersihkan layar sebelum menampilkan data parfum.
    bersih();

    // Membuat array string yang akan digunakan untuk menampilkan daftar parfum yang tersedia.
    string prfm[banyak_parfum()];

    // Memeriksa apakah terdapat parfum yang tersedia.
    if (banyak_parfum() != 0)
    {
        // Menampilkan daftar parfum yang tersedia dan menyimpan nama parfum dalam array prfm.
        for (int i = 0; i < banyak_parfum(); i++)
        {
            cout << "| " << i + 1 << ". " << parfume[i].nama << endl;
            prfm[i] = parfume[i].nama;
        }

        // Meminta pengguna untuk memilih salah satu parfum dari daftar.
        int see = menu(prfm, banyak_parfum(), "| Data parfum |");

        // Berdasarkan nilai update, melakukan aksi yang sesuai:
        if (update == 1)
        {
            // Jika update adalah 1, memanggil fungsi ubah_data() untuk mengubah data parfum yang dipilih.
            ubah_data(see);
        }
        else if (update == 2)
        {
            // Jika update adalah 2, memanggil fungsi hapus_data() untuk menghapus data parfum yang dipilih.
            hapus_data(see);
        }
        else if (update == 3)
        {
            // Jika update adalah 3, tidak melakukan aksi apa pun.
        }
        else
        {
            // Jika update tidak sesuai dengan 1, 2, atau 3, memanggil fungsi lihat_detail() untuk melihat detail parfum yang dipilih.
            lihat_detail(see);
        }
    }
    else
    {
        // Jika tidak ada parfum yang tersedia, menampilkan pesan bahwa data kosong.
        bersih();
        cout << "| ========================== |" << endl;
        cout << "| ==        Kosong        == |" << endl;
        cout << "| ========================== |" << endl;
    }
}

//Fungsi ini menampilkan nama parfum, brand, dan stok untuk berbagai ukuran parfum yang tersedia.
void lihat_detail(int see)
{
    // Membersihkan layar sebelum menampilkan detail parfum.
    bersih();

    // Menampilkan nama parfum yang dipilih.
    cout << "========================" << endl;
    cout << "| " << parfume[see - 1].nama << endl;
    cout << "========================" << endl;

    // Menampilkan harga parfum dan stok untuk berbagai ukuran.
    cout << "| Harga : " << parfume[see - 1].harga << endl;
    cout << "| size 50 ML : " << parfume[see - 1].size_stok[0].stok << " Stok" << endl;
    cout << "| size 100 ML : " << parfume[see - 1].size_stok[1].stok << " Stok" << endl;
    cout << "| size 150 ML : " << parfume[see - 1].size_stok[2].stok << " Stok" << endl;
    cout << "========================" << endl;
}

// Fungsi ubah_data digunakan untuk mengubah data parfum yang dipilih
void ubah_data(int ubah)
{
    // Membersihkan layar sebelum mengubah data parfum.
    bersih();

    // Memeriksa apakah terdapat data parfum yang tersedia.
    if (banyak_parfum() != 0)
    {
        // Deklarasi variabel-variabel untuk menyimpan data yang akan diubah.
        string nama_baru;
        int harga_baru;
        int stk1_baru;
        int stk2_baru;
        int stk3_baru;

        // Menampilkan pesan untuk mengubah data parfum.
        cout << "=============================" << endl;
        cout << "|         UBAH DATA         |" << endl;
        cout << "=============================" << endl;

        // Meminta pengguna memasukkan data yang baru.
        cout << "| Nama      : ";
        getline(cin, nama_baru);
        fflush(stdin);

        // Loop untuk memastikan input harga, size 50 ML, size 100 ML, dan size 150 ML adalah angka.
        while (true)
        {
            cout << "| harga     : ";
            cin >> harga_baru;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "harga harus angka boss " << endl;
                continue;
            }
            cout << "| size 50 ML : ";
            cin >> stk1_baru;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "harga harus angka boss " << endl;
                continue;
            }
            cout << "| size 100 ML : ";
            cin >> stk2_baru;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "harga harus angka boss " << endl;
                continue;
            }
            cout << "| size 150 ML : ";
            cin >> stk3_baru;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "harga harus angka boss " << endl;
                continue;
            }
            break;
        }

        cout << "=============================" << endl;

        // Mengganti data parfum yang dipilih dengan data yang baru.
        parfume[ubah - 1].nama = nama_baru;
        parfume[ubah - 1].harga = harga_baru;
        parfume[ubah - 1].size_stok[0].stok = stk1_baru;
        parfume[ubah - 1].size_stok[1].stok = stk2_baru;
        parfume[ubah - 1].size_stok[2].stok = stk3_baru;
    }
    else
    {
        // Jika tidak ada data parfum yang tersedia, menampilkan pesan bahwa data tidak ditemukan.
        bersih();
        cout << "| ========================== |" << endl;
        cout << "| == Data tidak ditemukan == |" << endl;
        cout << "| ========================== |" << endl;
    }
}


//Fungsi hapus_data digunakan untuk menghapus data parfum yang dipilih. 
void hapus_data(int hapus)
{
    // Membersihkan layar sebelum menghapus data parfum.
    bersih();

    // Memeriksa apakah terdapat data parfum yang tersedia.
    if (banyak_parfum() != 0)
    {
        // Menggeser data parfum dari indeks yang akan dihapus ke indeks berikutnya.
        for (int i = hapus - 1; i < banyak_parfum(); i++)
        {
            parfume[i] = parfume[i + 1];
        }

        // Membersihkan layar.
        bersih();
        cout << "| ========================== |" << endl;
        cout << "| ==  Data telah dihapus  == |" << endl;
        cout << "| ========================== |" << endl;
    }
    else
    {
        // Jika tidak ada data parfum yang tersedia, menampilkan pesan bahwa data tidak ditemukan.
        bersih();
        cout << "| ========================== |" << endl;
        cout << "| == Data tidak ditemukan == |" << endl;
        cout << "| ========================== |" << endl;
    }
}

//Fungsi menu_cari digunakan untuk mencari data parfum berdasarkan nama. 
//Fungsi ini menampilkan detail parfum jika ditemukan atau pesan bahwa parfum tidak ditemukan jika pencarian tidak berhasil.
void menu_cari()
{
    // Membersihkan layar sebelum memulai pencarian parfum.
    bersih();

    // Variabel string untuk menyimpan nama parfum yang akan dicari.
    string masuk;

    // Mengurutkan data parfum menggunakan shellSort().
    shellSort();

    // Menampilkan pesan untuk memulai pencarian parfum.
    cout << "===================================" << endl;
    cout << "|          CARI PARFUM            |" << endl;
    cout << "===================================" << endl;
    cout << "| Nama parfum : ";

    // Membaca nama parfum yang akan dicari dari input pengguna.
    getline(cin, masuk);
    fflush(stdin);

    // Melakukan pencarian data parfum berdasarkan nama.
    int dapat = searching_data(masuk);

    // Jika data parfum tidak ditemukan (dapat == -1), tampilkan pesan bahwa parfum tidak ditemukan.
    if (dapat == -1)
    {
        bersih();
        cout << "| =============================== |" << endl;
        cout << "| ==  Parfum tidak ditemukan  == |" << endl;
        cout << "| =============================== |" << endl;
    }
    else
    {
        // Jika data parfum ditemukan, tampilkan detail parfum tersebut.
        bersih();
        cout << "========================" << endl;
        cout << "| " << parfume[dapat].nama << endl;
        cout << "========================" << endl;
        cout << "| Harga     : " << parfume[dapat].harga << endl;
        cout << "| size 50 ML : " << parfume[dapat].size_stok[0].stok << " Stok" << endl;
        cout << "| size 100 ML : " << parfume[dapat].size_stok[1].stok << " Stok" << endl;
        cout << "| size 150 ML : " << parfume[dapat].size_stok[2].stok << " Stok" << endl;
        cout << "========================" << endl;
    }
}

// Fungsi ini digunakan untuk mengurutkan data parfum menggunakan algoritma Shell Sort.
int shellSort()
{
    int n = banyak_parfum();

    // Algoritma Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            parfum temp = parfume[i];
            int j;

            // Memulai perbandingan dan penukaran data sesuai dengan nama parfum.
            for (j = i; j >= gap && parfume[j - gap].nama > temp.nama; j -= gap)
            {
                parfume[j] = parfume[j - gap];
            }

            // Menyimpan data yang telah diurutkan.
            parfume[j] = temp;
        }
    }

    // Setelah mengurutkan data, disarankan untuk menyimpan data yang telah diurutkan.
    save_file_parfum();

    // Mengembalikan nilai 0 (tidak ada masalah) sebagai tanda bahwa pengurutan selesai.
    return 0;
}


void order_parfum(string nama)
{
    // Fungsi ini digunakan untuk memesan parfum dengan nama yang diberikan.
    // Memanggil fungsi lihat_data_parfum(3) untuk melihat detail parfum dengan indeks 3.
    // Anda mungkin perlu menggantikan indeks 3 dengan indeks yang sesuai dengan data parfum yang ingin dipesan.
    lihat_data_parfum(3);
}

// 'NO_OF_CHARS' digunakan untuk menetapkan jumlah karakter yang mungkin dalam ASCII (256 karakter).
const int NO_OF_CHARS = 256;

// Fungsi untuk menghitung heuristik bad character
void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS])
{
    // Inisialisasi semua entri dalam bad character array ke -1
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badchar[i] = -1;
    }

    // Isi bad character array dengan indeks terakhir dari setiap karakter dalam pola
    for (int i = 0; i < size; i++)
    {
        badchar[(int)str[i]] = i;
    }
}

// Fungsi untuk melakukan pencarian menggunakan algoritma Boyer-Moore
int searchBoyerMoore(string pat, string txt)
{
    int M = pat.length(); // Panjang pola
    int N = txt.length(); // Panjang teks

    int badchar[NO_OF_CHARS] = {-1}; // Inisialisasi bad character array dengan -1

    // Mengisi bad character array menggunakan heuristik
    badCharHeuristic(pat, M, badchar);

    int s = 0; // Variabel perpindahan pola terhadap teks

    while (s <= (N - M))
    {
        int j = M - 1;

        // Memeriksa karakter dari belakang pola hingga depan pola
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            // Jika seluruh pola cocok dengan teks, mengembalikan posisi awal kecocokan
            return s;
            s += (s + M < N) ? M - badchar[txt[s + M]] : 1;
        }
        else
        {
            // Memindahkan pola dengan pergeseran berdasarkan karakter yang tidak cocok dalam teks
            s += max(1, j - badchar[txt[s + j]]);
        }
    }

    // Mengembalikan -1 jika tidak ada kecocokan yang ditemukan
    return -1;
}

// Fungsi untuk mencari data dalam array parfume berdasarkan nama parfum dengan algoritma Boyer-Moore
int searching_data(string cari)
{
    for (int i = 0; i < banyak_parfum(); i++)
    {
        string pat = cari; // Pola pencarian adalah string yang ingin dicari
        string txt = parfume[i].nama; // Teks adalah nama parfum dalam array pada indeks tertentu
        int result = searchBoyerMoore(pat, txt); // Menggunakan algoritma Boyer-Moore untuk mencocokkan pola dengan teks

        if (result != -1)
        {
            return i; // Jika hasil pencarian tidak -1 (ada kecocokan), kembalikan indeks item yang cocok dalam array parfume
        }
    }

    return -1; // Jika tidak ada kecocokan ditemukan, kembalikan nilai -1
}
//Fungsi searching_data digunakan untuk mencari data dalam array parfume berdasarkan nama parfum menggunakan algoritma Boyer-Moore.
//Fungsi ini melakukan iterasi melalui semua elemen dalam array parfume, mencocokkan nama parfum dengan pola yang dicari, dan jika kecocokan ditemukan, mengembalikan indeks item dalam array tersebut.
//Jika tidak ada kecocokan yang ditemukan, maka fungsi ini mengembalikan -1.


//fungsi see_order digunakan untuk menampilkan pesanan yang sesuai dengan nama pengguna yang diberikan. 
//Fungsi ini menggunakan linked list (dengan pointer head) untuk menyimpan dan mengakses pesanan. 
void see_order(string user, Node *head)
{
    // Membersihkan layar sebelum menampilkan pesanan.
    bersih();

    // Menampilkan pesan yang berisi informasi pengguna yang pesan parfum.
    cout << "==================================" << endl;
    cout << "| Orderan " << user << endl;
    cout << "==================================" << endl;

    // Menggunakan pointer "temp" untuk mengiterasi melalui linked list pesanan (Node).
    Node *temp = head;

    // Memeriksa apakah linked list pesanan kosong.
    if (temp == NULL)
    {
        cout << "KOSONG" << endl;
        getch();
        return;
    }

    int i = 0; // Variabel untuk menghitung jumlah pesanan.

    // Iterasi melalui linked list pesanan dan menampilkan pesanan yang sesuai dengan pengguna yang diberikan.
    while (temp != NULL)
    {
        if (temp->ord.nama_akun == user)
        {
            cout << "| Username : " << temp->ord.nama_akun << endl;
            cout << "| Parfum : " << temp->ord.nama_parfum << endl;
            cout << "| Size :" << temp->ord.size << endl;
            cout << "==================================" << endl;
            i++;
        }
        temp = temp->next;
    }

    // Jika tidak ada pesanan yang sesuai dengan pengguna, menampilkan pesan "KOSONG".
    if (i == 0)
    {
        cout << "| KOSONG" << endl;
    }
}

//Fungsi see_order_riwayat digunakan untuk menampilkan riwayat pesanan yang sesuai dengan nama pengguna yang diberikan.
//Fungsi ini mengiterasi melalui riwayat pesanan dan menampilkan riwayat yang sesuai dengan pengguna.
void see_order_riwayat(string user)
{
    // Membersihkan layar sebelum menampilkan riwayat pesanan untuk pengguna tertentu.
    bersih();

    // Menampilkan pesan yang berisi informasi riwayat pesanan untuk pengguna yang diberikan.
    cout << "==================================" << endl;
    cout << "| Riwayat Order " << user << endl;
    cout << "==================================" << endl;

    // Iterasi melalui riwayat pesanan (menggunakan banyak_riwayat() untuk menentukan jumlah riwayat).
    for (int i = 0; i < banyak_riwayat(); i++)
    {
        if (riwayat[i].nama_akun == user)
        {
            cout << "| Username : " << riwayat[i].nama_akun << endl;
            cout << "| Parfum : " << riwayat[i].nama_parfum << endl;
            cout << "| Size : " << riwayat[i].size << endl;
            cout << "==================================" << endl;
        }
    }
}

//Fungsi menu_user digunakan untuk menampilkan menu dan mengelola interaksi pengguna dalam konteks pengguna. 
//Fungsi ini memungkinkan pengguna untuk melihat katalog parfum, memesan parfum, melihat daftar pesanan yang sedang diproses, melihat riwayat pesanan, atau keluar dari akun. 
//Setiap pilihan pengguna akan memicu tindakan yang sesuai dalam program.
void menu_user(bool *user_end, string cari, Node **head, Node **tail)
{
    // Mendefinisikan menu pilihan untuk pengguna.
    string menu_user[]{
        "Lihat Katalog",
        "Order",
        "Lihat Orderan",
        "Lihat Riwayat Order",
        "Logout"};
    
    // Menampilkan menu dan meminta pengguna untuk memilih.
    int pilih = menu(menu_user, 5, cari);

    // Menangani pilihan pengguna berdasarkan nilai yang dipilih.
    switch (pilih)
    {
    case 1:
        // Menampilkan katalog parfum.
        lihat_data_parfum(0);
        enter();
        break;
    case 2:
        // Memproses pesanan parfum.
        mengorder(cari, head, tail);
        save_file_order(*head);
        enter();
        break;
    case 3:
        // Melihat daftar pesanan yang sedang diproses.
        see_order(cari, *head);
        enter();
        break;
    case 4:
        // Melihat riwayat pesanan.
        see_order_riwayat(cari);
        enter();
        break;
    case 5:
        // Keluar dari akun pengguna.
        *user_end = true;
        break;
    }
}

//Fungsi duplikat digunakan untuk memeriksa apakah ada username yang sama dalam daftar akun. 
//Fungsi ini mengembalikan nilai true jika ada duplikasi username, dan false jika tidak ada duplikasi. Ini berguna untuk memvalidasi pembuatan akun agar tidak terjadi duplikasi.
bool duplikat(string cari)
{
    // Fungsi ini digunakan untuk memeriksa apakah ada duplikasi username dalam daftar akun.

    // Iterasi melalui daftar akun untuk memeriksa setiap username.
    for (int i = 0; i < banyak_akun(); i++)
    {
        // Memeriksa apakah username yang dicari ada dalam daftar akun.
        if (cari == akun[i].username)
        {
            // Jika ditemukan username yang sama, mengembalikan true (ada duplikasi).
            return true;
        }
    }

    // Jika tidak ada username yang sama, mengembalikan false (tidak ada duplikasi).
    return false;
}

//Fungsi menu_registrasi digunakan untuk memungkinkan pengguna untuk melakukan registrasi akun. 
//Fungsi ini memvalidasi username untuk memastikan bahwa itu adalah unik dalam daftar akun sebelum menyimpan informasi akun baru dan menyimpan data akun ke file.
void menu_registrasi()
{

    // Variabel-variabel untuk menyimpan informasi akun yang akan diregistrasi.
    string uname, Nama, pw;

    // Membersihkan layar sebelum memulai proses registrasi.
    bersih();
    
    // Menampilkan pesan registrasi.
    cout << "========================" << endl;
    cout << "|      REGISTRASI      |" << endl;
    cout << "========================" << endl;

    // Meminta pengguna untuk memasukkan username.
    cout << "| Masukkan Username : ";
    getline(cin, uname);
    fflush(stdin);

    // Melakukan validasi untuk memastikan bahwa username yang dimasukkan adalah unik.
    while (duplikat(uname) != false)
    {
        // Jika username sudah ada, tampilkan pesan kesalahan dan minta username yang lain.
        bersih();
        cout << "========================" << endl;
        cout << "|      REGISTRASI      |" << endl;
        cout << "========================" << endl;
        cout << "| Masukkan Username : ";
        getline(cin, uname);
        fflush(stdin);
    }

    // Meminta pengguna untuk memasukkan nama dan password.
    cout << "| Masukkan Nama : ";
    getline(cin, Nama);
    fflush(stdin);
    cout << "| Masukkan Password : ";
    getline(cin, pw);
    fflush(stdin);

    // Mendapatkan indeks untuk akun baru dalam array akun.
    int i = 0;
    i = banyak_akun();

    // Menyimpan informasi akun yang baru diregistrasi.
    akun[i].username = uname;
    akun[i].Nama = Nama;
    akun[i].password = pw;

    // Menyimpan data akun ke file.
    save_file_akun();
}

//Fungsi bersih digunakan untuk menghapus tampilan layar konsol dan menciptakan tampilan kosong.
void bersih()
{
    system("cls");
}

//Fungsi keluar digunakan untuk mengakhiri program.
void keluar()
{
    bersih();
    cout << "==========================================" << endl;
    cout << "==  Terima kasih, sampai jumpa nanti !  ==" << endl;
    cout << "==========================================" << endl;
}

//Fungsi enter digunakan agar user mengklik enter dan tampilan akan masuk ke tampilan setelahnya.
void enter()
{
    // Menampilkan pesan "ENTER..." untuk memberi tahu pengguna untuk menekan tombol "Enter".
    cout << "| ENTER...";
    
    // Menggunakan fungsi getch() untuk menunggu sampai pengguna menekan tombol "Enter".
    getch();
    
    // Membersihkan input buffer dengan fflush(stdin) untuk menghindari masukan yang tidak diinginkan.
    fflush(stdin);
}

//Fungsi login_user mengelola proses login pengguna. 
//Fungsi ini memvalidasi username dan password yang dimasukkan oleh pengguna dengan data akun yang tersimpan dan 
//memungkinkan pengguna untuk mengakses menu pengguna jika kombinasi username dan password sesuai.
void login_user(Node **head, Node **tail)
{
    // Membersihkan layar sebelum memulai proses login.
    bersih();

    // Variabel-variabel untuk menyimpan username dan password yang dimasukkan oleh pengguna.
    string user;
    string pass;

    // Menampilkan pesan login.
    cout << "==================================" << endl;
    cout << "|            LOGIN               |" << endl;
    cout << "==================================" << endl;

    // Meminta pengguna untuk memasukkan username dan password.
    cout << "| Username : ";
    getline(cin, user);
    fflush(stdin);
    cout << "| Password : ";
    getline(cin, pass);
    fflush(stdin);

    // Variabel "i" digunakan untuk iterasi melalui daftar akun.
    int i = 0;

    // Iterasi melalui daftar akun untuk memeriksa apakah username dan password sesuai.
    while (i < banyak_akun())
    {
        if (user == akun[i].username && pass == akun[i].password)
        {
            // Jika sesuai, variabel "user_end" diatur sebagai false.
            bool user_end = false;

            // Memulai loop menu pengguna selama "user_end" masih false.
            while (!user_end)
            {
                menu_user(&user_end, user, head, tail);
            }

            // Mengembalikan kontrol setelah pengguna keluar dari menu pengguna.
            return;
        }
        i++;
    }

    // Jika kombinasi username dan password tidak sesuai, tampilkan pesan kesalahan.
    bersih();
    cout << "| ================================= |" << endl;
    cout << "| ==  Username / Password salah  == |" << endl;
    cout << "| ================================= |" << endl;

    // Menunggu pengguna menekan tombol "Enter" sebelum kembali ke menu utama.
    cout << "| ENTER...";
    getch();
}

//Fungsi login_admin mengelola proses login sebagai admin. 
//Fungsi ini memvalidasi username dan password yang dimasukkan oleh pengguna dengan kombinasi yang telah ditentukan untuk akun admin. 
//Jika sesuai, admin dapat mengakses menu admin.
void login_admin(Node **head, Node **tail)
{
    // Membersihkan layar sebelum memulai proses login.
    bersih();

    // Variabel-variabel untuk menyimpan username dan password yang dimasukkan oleh pengguna.
    string user;
    string pass;

    // Menampilkan pesan login.
    cout << "===================================" << endl;
    cout << "|             LOGIN               |" << endl;
    cout << "===================================" << endl;

    // Meminta pengguna untuk memasukkan username dan password.
    cout << "| Username : ";
    getline(cin, user);
    fflush(stdin);
    cout << "| Password : ";
    getline(cin, pass);
    fflush(stdin);

    // Variabel "i" digunakan untuk iterasi melalui daftar akun.
    int i = 0;

    // Iterasi melalui daftar akun untuk memeriksa apakah username dan password sesuai dengan akun admin.
    while (i < banyak_akun())
    {
        if (user == "a" && pass == "a")
        {
            // Jika sesuai, variabel "admin_end" diatur sebagai false.
            bool admin_end = false;

            // Memulai loop menu admin selama "admin_end" masih false.
            while (!admin_end)
            {
                menu_admin(&admin_end, head, tail);
            }

            // Mengembalikan kontrol setelah admin keluar dari menu admin.
            return;
        }
        i++;
    }

    // Jika kombinasi username dan password tidak sesuai, tampilkan pesan kesalahan.
    bersih();
    cout << "| ================================= |" << endl;
    cout << "| ==  Username / Password salah  == |" << endl;
    cout << "| ================================= |" << endl;

    // Menunggu pengguna menekan tombol "Enter" sebelum kembali ke menu utama.
    cout << "| ENTER...";
    getch();
}

//Fungsi ini memperlihatkan pilihan menu kepada admin atau pengguna.
void menu_utama(Node **head, Node **tail)
{
    // Array menu_utama berisi opsi-opsi yang tersedia dalam menu utama.
    string menu_utama[] = {
        "User",
        "Admin",
        "Registrasi",
        "Keluar"};
    
    // Variabel program_end digunakan untuk menentukan kapan program harus berakhir.
    bool program_end = false;

    // Loop utama program yang berjalan selama program_end masih false.
    while (!program_end)
    {
        // Menampilkan menu utama dan meminta pengguna untuk memilih opsi.
        int pilih = menu(menu_utama, 4, "|    Welcome To BYREDO store    |");

        // Switch statement untuk menentukan tindakan berdasarkan pilihan pengguna.
        switch (pilih)
        {
        case 1:
            // Jika pengguna memilih "User", panggil fungsi login_user untuk masuk sebagai pengguna.
            login_user(head, tail);
            break;
        case 2:
            // Jika pengguna memilih "Admin", panggil fungsi login_admin untuk masuk sebagai admin.
            login_admin(head, tail);
            break;
        case 3:
            // Jika pengguna memilih "Registrasi", panggil fungsi menu_registrasi untuk mendaftarkan akun baru.
            menu_registrasi();
            break;
        case 4:
            // Jika pengguna memilih "Keluar", atur program_end sebagai true untuk mengakhiri program.
            program_end = true;

            // Panggil fungsi keluar untuk menampilkan pesan perpisahan.
            keluar();
            break;
        }
    }
}

//Dalam main, data parfum, akun pengguna, pesanan, dan riwayat pesanan dibaca dari file.
//Kemudian, fungsi menu_utama dipanggil untuk memulai interaksi pengguna dengan program.
//Setelah pengguna selesai menggunakan program dan keluar, program mengembalikan nilai 0 sebagai tanda bahwa program telah selesai.
int main()
{
    // Inisialisasi pointer ke Node head dan tail untuk antrian pesanan.
    Node *head = NULL;
    Node *tail = NULL;

    // Membaca data parfum dari file.
    read_file_parfum();

    // Membaca data akun pengguna dari file.
    read_file_akun();

    // Membaca data pesanan dari file dan menginisialisasi antrian pesanan (queue).
    read_file_order(&head, &tail);

    // Membaca data riwayat pesanan dari file.

    read_file_riwayat();

    // Memanggil fungsi menu utama dan memulai eksekusi program.
    menu_utama(&head, &tail);

    // Mengembalikan nilai 0 sebagai keluaran dari program.
    return 0;
}