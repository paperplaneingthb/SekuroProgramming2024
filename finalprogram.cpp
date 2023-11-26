#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

vector <double> vec_x;
vector <double> vec_y;
vector <double> redo_x;
vector <double> redo_y;
string inp = "start";
double drone_x = 0;
double drone_y = 0;
double movex;
double movey;
double v;
double t;
double theta;
bool quit = false;

void round2(double num)
{
	double rnum = num * 100;
	if (round(rnum) == floor(rnum))
	{
		cout << fixed << setprecision(2) << trunc(rnum) / 100;
	}
	else if (round(rnum) == ceil(rnum))
	{
		cout << fixed << setprecision(2) << trunc(rnum) / 100 + 0.01;
	}
}

void lokasi()
{
	cout << "(";
	round2(drone_x);		// print koordinat x drone
	cout << ", ";
	round2(drone_y);		// print koordinat y drone
	cout << ")" << endl;
}

void gerak1(double x, double y)
{
	drone_x += x;
	drone_y += y;
}

void gerak2(double vel, double time, double angle)
{
	double pi = 3.14159265;
	drone_x += vel * time * cos((angle / 180) * pi);
	drone_y += vel * time * sin((angle / 180) * pi);
}

int main()
{
	vec_x.push_back(0);
	vec_y.push_back(0);

	cout << "Selamat datang di simulasi drone 101." << endl;
	cout << "Pilihan masukan: " << endl;
	cout << "lokasi	 - Menampilkan lokasi drone saat ini. Lokasi awal adalah (0, 0)." << endl;
	cout << "gerak	 - Menggerakkan drone dengan parameter gerak horizontal dan vertikal." << endl;
	cout << "gerak_2	 - Menggerakkan drone dengan parameter kecepatan, waktu, dan sudut." << endl;	// Ini indentnya harus beda sendiri gak tau kenapa
	cout << "undo	 - Memindahkan drone ke posisi sebelumnya. Masukan 'lokasi' sekaligus dijalankan." << endl;
	cout << "redo	 - Memindahkan drone ke posisi sebelum undo. Masukan 'lokasi' sekaligus dijalankan." << endl;
	cout << "exit	 - Keluar dari simulasi." << endl;

	while (quit == false)
	{
		cout << endl;
		cout << ">> ";
		cin >> inp;
		if (inp == "lokasi")
		{
			cout << "Lokasi sekarang: ";
			lokasi();
		}
		else if (inp == "gerak")
		{
			cout << "Gerak horizontal (x): ";
			cin >> movex;
			cout << "Gerak vertikal (y): ";
			cin >> movey;
			gerak1(movex, movey);
			cout << "Drone berhasil digerakkan." << endl;
			vec_x.push_back(drone_x);
			vec_y.push_back(drone_y);
			redo_x.clear();
			redo_y.clear();
		}
		else if (inp == "gerak_2")
		{
			cout << "Kecepatan (v): ";
			cin >> v;
			cout << "Lama pergerakan (t): ";
			cin >> t;
			cout << "Sudut pergerakan (theta): ";
			cin >> theta;
			gerak2(v, t, theta);
			cout << "Drone berhasil digerakkan." << endl;
			vec_x.push_back(drone_x);
			vec_y.push_back(drone_y);
			redo_x.clear();
			redo_y.clear();
		}
		else if (inp == "undo")
		{
			// size == n maka indeks terakhir == n - 1
			// push back koordinat terakhir ke redo, lalu pop back
			if (vec_x.size() > 1)
			{
				redo_x.push_back(vec_x[vec_x.size() - 1]);
				redo_y.push_back(vec_y[vec_y.size() - 1]);
				vec_x.pop_back();
				vec_y.pop_back();
				drone_x = vec_x[vec_x.size() - 1];
				drone_y = vec_y[vec_y.size() - 1];
				cout << "Undo berhasil." << endl;
				cout << "Lokasi sekarang: ";
				lokasi();
			}
			else
			{
				cout << "Undo tidak bisa dijalankan." << endl;
			}
		}
		else if (inp == "redo")
		{
			if (redo_x.size() > 0)
			{
				vec_x.push_back(redo_x[redo_x.size() - 1]);
				vec_y.push_back(redo_y[redo_y.size() - 1]);
				drone_x = redo_x[redo_x.size() - 1];
				drone_y = redo_y[redo_y.size() - 1];
				cout << "Redo berhasil." << endl;
				cout << "Lokasi sekarang: ";
				lokasi();
				redo_x.pop_back();
				redo_y.pop_back();
			}
			else
			{
				cout << "Redo tidak bisa dijalankan." << endl;
			}
		}
		else if (inp == "exit")
		{
			quit = true;
		}
		else
		{
			cout << "Input tidak dapat diproses." << endl;
		}
	}
	cout << "Terimakasih sudah menggunakan simulasi drone 101." << endl;
	return 0;
}