#include <iostream>
#include <string>
using namespace std;

struct Node {
    string namaBarang;
    int harga;
    int jumlah;
    Node *next;
};

Node* buatNode(string nama, int harga, int jumlah) {
    Node *baru = new Node;
    baru->namaBarang = nama;
    baru->harga = harga;
    baru->jumlah = jumlah;
    baru->next = NULL;
    return baru;
}

void tambahBelakang(Node* &head, string nama, int harga, int jumlah) {
    Node *baru = buatNode(nama, harga, jumlah);
    if (head == NULL) {
        head = baru;
        return;
    }
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = baru;
}

void tambahDepan(Node* &head, string nama, int harga, int jumlah) {
    Node *baru = buatNode(nama, harga, jumlah);
    baru->next = head;
    head = baru;
}

void tambahSetelah(Node* &head, string target, string nama, int harga, int jumlah) {
    Node *temp = head;
    while (temp != NULL && temp->namaBarang != target) {
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "Barang " << target << " tidak ditemukan.\n";
        return;
    }
    Node *baru = buatNode(nama, harga, jumlah);
    baru->next = temp->next;
    temp->next = baru;
}

void hapusBarang(Node* &head, string nama) {
    if (head == NULL) {
        cout << "Keranjang kosong!\n";
        return;
    }
    if (head->namaBarang == nama) {
        Node *hapus = head;
        head = head->next;
        delete hapus;
        cout << "Barang " << nama << " berhasil dihapus.\n";
        return;
    }
    Node *temp = head;
    while (temp->next != NULL && temp->next->namaBarang != nama) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        cout << "Barang tidak ditemukan.\n";
        return;
    }
    Node *hapus = temp->next;
    temp->next = hapus->next;
    delete hapus;
    cout << "Barang " << nama << " berhasil dihapus.\n";
}

void tampilkan(Node* head) {
    cout << "\n=== ISI KERANJANG ===\n";
    Node *temp = head;
    int totalHarga = 0, totalBarang = 0;
    while (temp != NULL) {
        cout << temp->namaBarang << " - Rp" << temp->harga 
            << " x" << temp->jumlah << endl;
        totalHarga += temp->harga * temp->jumlah;
        totalBarang++;
        temp = temp->next;
    }
    cout << "\nTotal barang: " << totalBarang << endl;
    cout << "Total harga: Rp" << totalHarga << endl;
}

int main() {
    Node *head = NULL;
    int n;
    cout << "Masukkan jumlah barang awal: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string nama;
        int harga, jumlah;
        cout << "\nBarang " << i + 1 << endl;
        cout << "Nama: ";
        getline(cin, nama);
        cout << "Harga: ";
        cin >> harga;
        cout << "Jumlah: ";
        cin >> jumlah;
        cin.ignore();
        tambahBelakang(head, nama, harga, jumlah);
    }

    char hapus;
    cout << "\nApakah ingin menghapus barang? (y/n): ";
    cin >> hapus;
    cin.ignore();
    if (hapus == 'y' || hapus == 'Y') {
        string namaHapus;
        cout << "Masukkan nama barang yang ingin dihapus: ";
        getline(cin, namaHapus);
        hapusBarang(head, namaHapus);
    }

    tampilkan(head);
    return 0;
}
