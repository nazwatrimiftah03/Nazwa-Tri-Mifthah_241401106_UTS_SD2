#include <iostream>
#include <string>
using namespace std;

struct Pesanan {
    string nama;
    string menu;
    int statusVIP; // 1 = biasa, 2 = VIP
    int waktuDatang;
};

void tampilkanPesanan(Pesanan arr[], int n) {
    cout << "\n=== DAFTAR PESANAN ===\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arr[i].nama << " - " << arr[i].menu;
        if (arr[i].statusVIP == 2) cout << " [VIP]";
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Masukkan jumlah pesanan: ";
    cin >> n;
    cin.ignore();

    Pesanan *data = new Pesanan[n];

    for (int i = 0; i < n; i++) {
        cout << "\nPesanan " << i + 1 << endl;
        cout << "Nama hewan: ";
        getline(cin, data[i].nama);
        cout << "Menu pesanan: ";
        getline(cin, data[i].menu);
        cout << "Status VIP (1=biasa, 2=VIP): ";
        cin >> data[i].statusVIP;
        cin.ignore();
        data[i].waktuDatang = i + 1;
    }

    // Urutkan berdasarkan aturan: VIP dulu, lalu urutan datang
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (data[j].statusVIP > data[i].statusVIP || 
                (data[j].statusVIP == data[i].statusVIP && data[j].waktuDatang < data[i].waktuDatang)) {
                Pesanan temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    tampilkanPesanan(data, n);
// menghapus memori
    delete[] data;
    return 0;
}