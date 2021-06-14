#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;
struct alkohol {
	string alko;
	int ilosc;
	char godz[7];
	int min;
	int h;
	double procenty;
	double dost_alko_ml;
	double dost_alko_mg;
	double stezenie;
	double lacznie;
	double min_wytrzezw;
	double h_wytrzezw;
	double obecne_mg;
};
void procenty(alkohol alko[], int n);
void wpisywanie_do_txt() {
	string do_txt;
	getline(cin, do_txt);
	fstream projektowy;
	projektowy.open("projekt.txt", ios::out);
	projektowy << do_txt;
	projektowy.close();
}					

void przypisanie_do_zmiennych(int& usuwanie, double& plec, alkohol alko[], int& masa, int& ilosc_alko)
{
	string plec_chwilowa;
	string niepotrzebne;
	fstream projektowy;
	projektowy.open("projekt.txt", ios::in);
	projektowy >> plec_chwilowa;
	cout << plec_chwilowa;
	/*      wybor plci          */
	if (plec_chwilowa == "Kobieta:" || plec_chwilowa == "kobieta:")
	{
		usuwanie = 8;
		plec = 0.6;
	}
	else {
		usuwanie = 10;
		plec = 0.7;
	}
	projektowy >> niepotrzebne;
	projektowy >> masa;
	projektowy >> niepotrzebne;
	while (projektowy >> alko[ilosc_alko].alko)
	{
		projektowy >> alko[ilosc_alko].ilosc;
		projektowy >> alko[ilosc_alko].godz;
		procenty(alko, ilosc_alko);
		cout << alko[ilosc_alko].alko << " " << alko[ilosc_alko].ilosc <<" "<< alko[ilosc_alko].godz <<" "<< alko[ilosc_alko].procenty << endl;
		
		ilosc_alko++;
	}

	projektowy.close();
}
void procenty(alkohol alko[], int n)
{
	if (alko[n].alko == "piwo")
	{
		alko[n].procenty = 6;
	}
	else if (alko[n].alko == "wino")
	{
		alko[n].procenty = 12;
	}
	else if (alko[n].alko == "wódka"|| alko[n].alko =="w¢dka")
	{
		alko[n].procenty = 40;
	}
	else if (alko[n].alko == "cydr")
	{
		alko[n].procenty = 2;
	}
}
void zmiana_czasu(alkohol alko[], int ilosc_alko)
{
	for (int i = 0; i < ilosc_alko; i++)
	{
		alko[i].h = alko[i].godz[2] - '0';
		alko[i].h *= 10;
		alko[i].h = alko[i].h + alko[i].godz[3] - '0';
		alko[i].min = alko[i].godz[4] - '0';
		alko[i].min *= 10;
		alko[i].min = alko[i].min + alko[i].godz[5] - '0';
		
	}
}
void dost_ml(alkohol alko[], int ilosc_alko)
{
	for (int i = 0; i < ilosc_alko; i++)
	{
		alko[i].dost_alko_ml = alko[i].ilosc * alko[i].procenty*0.01;
		cout << alko[i].dost_alko_ml << "ml ";
	}
}

void dost_mg(alkohol alko[], int ilosc_alko)
{
	for (int i = 0; i < ilosc_alko; i++)
	{
		alko[i].dost_alko_mg = alko[i].dost_alko_ml * 0.79;
		cout << alko[i].dost_alko_mg << "mg ";
	}

}

void stezenie(int ilosc_alko, alkohol alko[], int masa, double plec, int usuwanie){

	for (int i = 0; i < ilosc_alko; i++)
	{
		double h_chwil = 0;
		double min_chwil = 0;
		if (i == 0)
		{
			alko[i].obecne_mg = alko[i].dost_alko_mg;
			alko[i].lacznie = alko[i].obecne_mg / (masa * plec);
		}
		else {

			if (alko[i-1].min <= alko[i].min) {
				min_chwil = alko[i].min - alko[i-1].min;
				h_chwil = alko[i].h - alko[i-1].h;
				double stracone = (h_chwil + (min_chwil / 60)) * plec;
				alko[i].obecne_mg = alko[i - 1].obecne_mg - stracone + alko[i].dost_alko_mg;
				alko[i].lacznie = alko[i].obecne_mg / (masa * plec);
			}
			else if (alko[i - 1].min > alko[i].min) {
				int h = alko[i].h;
				int min = alko[i].min;
				h--;
				min = min + 60;
				min_chwil = min - alko[i-1].min;
				h_chwil = h - alko[i-1].h;
				double stracone = (h_chwil + (min_chwil / 60)) * plec;
				alko[i].obecne_mg = alko[i - 1].obecne_mg - stracone + alko[i].dost_alko_mg;
				alko[i].lacznie = alko[i].obecne_mg / (masa * plec);
			}


		}


	}

}
void liczenie_trzezwosci(int ilosc_alko, alkohol alko[], int masa, double plec, int usuwanie, int &min_02, int &h_02)
{
	double gram_alko = alko[ilosc_alko - 1].obecne_mg;
	double h = (gram_alko - 0.2 * (masa * plec)) / usuwanie;
	int godziny = h;
	int min = (h - godziny) * 60;
	godziny = godziny + alko[ilosc_alko - 1].h;
	
	min = min + godziny + alko[ilosc_alko - 1].min;
	if (min >= 60)
	{
		godziny++;
		min -= 60;
	}
	if (godziny >= 24) {
		godziny = godziny - 24;
	}
	min_02 = min;
	h_02 = godziny;
	
}
void tabelka(int ilosc_alko, alkohol alko[])
{
	cout << "\n-------------------------------------------------------------------------------" << endl;
	cout << " godz:   |  rodzaj alkoholu  | ilosc | ilosc promili | godzina wytrzezwienia: |" << endl;
		for (int i = 0; i < ilosc_alko; i++)
		{
			cout << alko[i].h << ":" << alko[i].min << "    |      " << alko[i].alko << "   |     " << alko[i].ilosc<<"     |      "<< alko[i].lacznie << "  |   " << alko[i].h_wytrzezw << ":" << alko[i].min_wytrzezw<<"   |"<<endl;
	}

}
void wytrzezwienie(alkohol alko[], int ilosc_alko, double plec, int masa, int usuwanie)
{	
	for (int i = 0; i < ilosc_alko; i++)
	{
		double h=0;
		int min=0;
		double g_alko = alko[i].lacznie * masa * plec;
		while (g_alko > usuwanie)
		{
			g_alko -= usuwanie;
			h++;
		}
		min = (g_alko / usuwanie) * 60;
		while (min >= 60)
		{
			min = min - 60;
			h++;
		}
		
		alko[i].min_wytrzezw = alko[i].min + min;
		if (alko[i].min_wytrzezw >= 60)
		{
			alko[i].min_wytrzezw -= 60;
			h++;
		}
		alko[i].h_wytrzezw = alko[i].h + h;
		if (alko[i].h_wytrzezw >= 24) {
			alko[i].h_wytrzezw -= 24;
		}
	}
}
void rysowanie_wykresu(int ilosc_alko, alkohol alko[], int min_02, int h_02)
{	int przerwa = 50 / (ilosc_alko);
	int nr_alko = 0;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < 49; i++)
	{
		
		double ilosc_gwiazd = alko[nr_alko].lacznie * 16;
		cout << alko[nr_alko].h << ":" << alko[nr_alko].min;
		if (alko[nr_alko].min == 0)
		{
			cout << "0";
		}
		cout << "  |";
		for (int b = 0; b < ilosc_gwiazd; b++)
		{
			cout << "*";
		}
		int k = 0;
		cout << endl;
		while ( k < przerwa && i<49)
		{
			cout<<"       |" << endl;
			k++;
			i++;
			
		}
		
		nr_alko++;


	}
	if (alko[ilosc_alko - 1].h_wytrzezw < 10)
	{
		cout << " ";
	}
	cout << alko[ilosc_alko-1].h_wytrzezw << ":" << alko[ilosc_alko-1].min_wytrzezw << "  |" << endl;
	for (double i = 0; i < 8; i++)
	{
		cout << " ";
	}
	for (double i = 0; i < 80; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (double i = 0; i < 8; i++)
	{
		cout << " ";
	}
	int promilek=1;
	for (int i = przerwa; i < 80; i=i+przerwa-1)
	{
		for (double j = 0; j < przerwa-1; j++)
		{
			cout << " ";
		}
		cout << promilek;
		promilek++;
		
	}
	cout << endl;
	cout << "                                      promile";
}
int main()
{	int usuwanie=0;
	double plec=0;
	int masa=0;
	int ilosc_alko=0;
	int h_02;
	int min_02;
	alkohol alko[100];
	wpisywanie_do_txt();
	przypisanie_do_zmiennych(usuwanie, plec, alko, masa, ilosc_alko);
	zmiana_czasu(alko, ilosc_alko);
	dost_ml(alko, ilosc_alko);
	dost_mg(alko, ilosc_alko);
	stezenie(ilosc_alko, alko, masa, plec, usuwanie);
	cout << alko[ilosc_alko-1].lacznie;
	wytrzezwienie(alko, ilosc_alko, plec, masa, usuwanie);
	system("cls");
	tabelka(ilosc_alko, alko);
	liczenie_trzezwosci(ilosc_alko, alko, masa, plec, usuwanie, min_02, h_02);
	rysowanie_wykresu(ilosc_alko, alko, min_02, h_02);
	cout << endl;
	cout << "Bedziesz mial 0,2 promila o godz: " << h_02 << ":" << min_02;
	





	return 0;
}