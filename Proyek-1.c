/*
Proyek-1
Program Deposito Bank beserta Alokasi Dana untuk Pengguna

Anggota Kelompok 1:
1. Daffa Sayra Firdaus (2306267151)
2. Muhamad Hakim Nizami (2306210001)

Tanggal : Kamis, 21 Maret 2024
Versi Program : 1.0

--FRAMEWORK--

--TO DO LIST--
	4. Buat dompet untuk setiap user
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "HeaderFiles/DefineStruct.h"
#include "HeaderFiles/MainMenu.h"
#include "HeaderFiles/Additional.h"
#include "HeaderFiles/Functions.h"
#include "HeaderFiles/SearchSort.h"
#include "HeaderFiles/FileHandling.h"
#include "HeaderFiles/StringManipule.h"

int main() {
	User user;
	user.alloc = NULL;

	int size = 0;

	user.dana.danaAlloc = 0;

	system("cls");

	programExpl(); // Penjelasan program ditampilkan sekali sebelum mulai

	readKartu(&user); // Membaca kartu milik user

	updateAfterAlloc(&user, 0); // Update nominal setelah alokasi data

	getAccessMain(user,&size);

	readData(&user, &size);

	mainMenu(user, &size);

	free(user.alloc);

	return 0;
}

