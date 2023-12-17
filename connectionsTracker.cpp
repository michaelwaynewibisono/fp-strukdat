#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Nomor 1 (Class)
class PetaAbstract
{
    // Nomor 5 (Encapsulation: public)
public:
    virtual void tambahLintasan(int titik_awal, int titik_tujuan) = 0;
    virtual void tampilkanAdjList() = 0;
    virtual void tampilkanAdjMatrix() = 0;
    virtual vector<string> cariNilaiTitik(int titik) = 0;
    virtual ~PetaAbstract() {}
};

class AdjacencyMatrix
{
public:
    int **adj_matrix;
    int jumlah_titik;

    AdjacencyMatrix(int jumlah_titik)
    {
        this->jumlah_titik = jumlah_titik;
        adj_matrix = new int *[jumlah_titik];
        for (int i = 0; i < jumlah_titik; ++i)
        {
            adj_matrix[i] = new int[jumlah_titik];
            for (int j = 0; j < jumlah_titik; ++j)
            {
                adj_matrix[i][j] = 0;
            }
        }
    }

    ~AdjacencyMatrix()
    {
        for (int i = 0; i < jumlah_titik; ++i)
        {
            delete[] adj_matrix[i];
        }
        delete[] adj_matrix;
    }
};

class Peta : public PetaAbstract
{
private:
    int jumlah_titik;
    list<int> *adjacency_list;
    AdjacencyMatrix *adj_matrix; // Nomor 8 (Composition)

    vector<string> accounts = {"dwi", "agas", "sylvi", "afif", "michael"};

public:
    // Nomor 1 (Constructor)
    Peta(int jumlah_titik)
    {
        this->jumlah_titik = jumlah_titik;
        inisialisasiAdjList(jumlah_titik);
        adj_matrix = new AdjacencyMatrix(jumlah_titik);
    }

    // Nomor 1 (Destructor)
    ~Peta()
    {
        delete[] adjacency_list;
        delete adj_matrix;
    }

    // Nomor 2 (Adjacency List)
    void inisialisasiAdjList(int jumlah_titik)
    {
        adjacency_list = new list<int>[jumlah_titik];
    }

    // Implementasi dari fungsi-fungsi abstract dari kelas PetaAbstract
    // Nomor 4 (Abstract Class)
    void tambahLintasan(int titik_awal, int titik_tujuan) override
    {
        adjacency_list[titik_awal].push_back(titik_tujuan);
        adj_matrix->adj_matrix[titik_awal][titik_tujuan] = 1;
        adj_matrix->adj_matrix[titik_tujuan][titik_awal] = 1;
    }

    void tampilkanAdjList() override
    {
        for (int v = 0; v < jumlah_titik; v++)
        {
            cout << accounts[v] << " -> ";
            for (auto i : adjacency_list[v])
            {
                cout << accounts[i];
                if (i != adjacency_list[v].back())
                {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    }

    void tampilkanAdjMatrix() override
    {
        for (int i = 0; i < jumlah_titik; i++)
        {
            for (int j = 0; j < jumlah_titik; j++)
            {
                cout << adj_matrix->adj_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<string> cariNilaiTitik(int titik) override
    {
        vector<string> hasil;
        for (auto i : adjacency_list[titik])
        {
            hasil.push_back(accounts[i]);
        }
        return hasil;
    }

    // Overloading tambahLintasan untuk menerima nama titik sebagai string
    // Nomor 7 (Overloading)
    void tambahLintasan(string nama_awal, string nama_tujuan)
    {
        int titik_awal = -1, titik_tujuan = -1;
        for (int i = 0; i < accounts.size(); ++i)
        {
            if (accounts[i] == nama_awal)
                titik_awal = i;
            if (accounts[i] == nama_tujuan)
                titik_tujuan = i;
        }
        if (titik_awal != -1 && titik_tujuan != -1)
        {
            tambahLintasan(titik_awal, titik_tujuan);
        }
        else
        {
            cout << "Titik tidak ditemukan!" << endl;
        }
    }

    // Overloading cariNilaiTitik untuk menerima nama titik sebagai string
    // Nomor 7 (Overloading)
    vector<string> cariNilaiTitik(string nama)
    {
        vector<string> hasil;
        int num = 0;
        for (int i = 0; i < accounts.size(); ++i)
        {
            if (accounts[i] == nama)
            {
                for (auto val : adjacency_list[i])
                {
                    hasil.push_back(accounts[val]);
                    num++;
                }
                break;
            }
        }
        if (num == 0)
        {
            cout << "User tidak ditemukan" << endl;
            return {};
        }
        return hasil;
    }
};

int main()
{
    cout << "Social Media Connections" << endl;
    int jumlah_titik = 5;
    int jumlah_loop;
    int n1, n2;
    cout << "Masukkan jumlah actions: ";
    cin >> jumlah_loop;

    Peta petaKu(jumlah_titik); // Nomor 3 (Menginstansiasi Class)

    for (int i = 0; i < jumlah_loop; i++)
    {
        cin >> n1 >> n2;
        petaKu.tambahLintasan(n1, n2);
    }

    cout << "Adjacency List" << endl;
    petaKu.tampilkanAdjList();

    cout << "Adjacency Matrix" << endl;
    petaKu.tampilkanAdjMatrix();

    string cari_nama;
    cout << "Masukkan nama yang ingin diketahui username followingnya: ";
    cin >> cari_nama;

    cout << "Username " << cari_nama << " mengikuti: ";
    vector<string> hasil_pencarian = petaKu.cariNilaiTitik(cari_nama);
    for (const auto &nilai : hasil_pencarian)
    {
        cout << nilai;
        if (&nilai != &hasil_pencarian.back())
        {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}

/*
Social Media Connections
Masukkan jumlah actions: [14]
[
0 1
0 4
1 0
1 4
1 2
1 3
2 1
2 3
3 1
3 4
3 2
4 3
4 0
4 1
]
Adjacency List
dwi -> agas -> michael
agas -> dwi -> michael -> sylvi -> afif
sylvi -> agas -> afif
afif -> agas -> michael -> sylvi
michael -> afif -> dwi -> agas
Adjacency Matrix
0 1 0 0 1
1 0 1 1 1
0 1 0 1 0
0 1 1 0 1
1 1 0 1 0
Masukkan nama yang ingin diketahui username followingnya: [afif]
Username afif mengikuti: agas -> michael -> sylvi
*/