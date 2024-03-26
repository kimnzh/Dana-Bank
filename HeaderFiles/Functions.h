void editDana(User *user) {
	int opsi;
	long int temp;

	printf("Opsi:\n");
	printf("1. Tambahkan nominal\n");
	printf("2. Kurangkan nominal\n");
	
	printf("Pilihan: ");
	scanf("%d", &opsi);
	switch(opsi) {
		case 1:
			printf("\nMasukkan nominal yang ingin ditambahkan: ");
			scanf("%ld", &temp);
			user->dana.saldoTotal += temp;
			updateAfterAlloc(user, 0);
			system("cls");
			printf("Dana berhasil ditambahkan!\n\n");
			break;
		case 2:
			printf("\nMasukkan nominal yang ingin dikurangkan: ");
			scanf("%ld", &temp);
			if (user->dana.saldoTotal - temp < 0) {
				system("cls");
				printf("Jumlah pengurangan terlalu besar!\n");
				printf("Gagal mengedit jumlah dana\n\n");
			} else {
				user->dana.saldoTotal -= temp;
				updateAfterAlloc(user, 0);
				system("cls");
				printf("Dana berhasil dikurangkan!\n\n");
			}
			break;
		default:
			printf("Gagal mengedit jumlah dana\n\n");
	}
}

void addAlokasiDana(User *user, int *size) {
	(*size)++;
	user->alloc = (Alloc *)realloc(user->alloc, (*size) * sizeof(Alloc));

	printf("Nama dana    : ");
	scanf(" %[^\n]", user->alloc[*size - 1].nama);
	printf("Nominal dana : ");
	scanf("%ld", &user->alloc[*size - 1].dana);
	
	if (user->alloc[*size - 1].dana > user->dana.saldoSisa) {
		(*size)--;
		user->alloc = (Alloc *)realloc(user->alloc, (*size) * sizeof(Alloc));
		system("cls");
		printf("Dana yang tersisa tidak cukup\n");
		printf("Gagal menambahkan data\n\n");
	} else {
		updateAfterAlloc(user, user->alloc[*size - 1].dana);
		percentUpdate(user, *size);
		system("cls");
		printf("Data berhasil ditambahkan!\n");
	}
}

void removeAlokasiDana(User *user, int *size) {
	int i, idx = 0;
	char idxString[50];
	long int danaRemove;

	if (*size == 0) {
		printf("Tidak ada data untuk dihapus\n\n");
	} else {
		do {
			showAllocation(*user, *size);

			printf("\nMasukkan index data yang ingin dihapus: ");
			scanf(" %[^\n]", idxString);
			idx = atoi(idxString);

			danaRemove = user->alloc[idx - 1].dana;
			for (i = idx - 1; i < *size; i++) {
				strcpy(user->alloc[i].nama, user->alloc[i + 1].nama);
				user->alloc[i].dana = user->alloc[i + 1].dana;
			}

			(*size)--;
			user->alloc = (Alloc *)realloc(user->alloc, (*size) * sizeof(Alloc));
			updateAfterRemove(user, danaRemove);
			percentUpdate(user, *size);
			
			system("cls");
		} while (idx < *size && idx > *size);

		printf("Alokasi dana ini berhasil dibatalkan\n\n");
	}
}

void showAllocation(User user, int size) {
	int i;
	
	if (size == 0) {
		printf("+========================+\n");
		printf("|     TIDAK ADA DATA     |\n");
		printf("+========================+\n");
	} else {
		printf("+======+============================+===============+=========+\n");
		printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
		printf("+======+============================+===============+=========+\n");

		for (i = 0; i < size; i++) {
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", i + 1, 3, ".", 26, user.alloc[i].nama, 13, user.alloc[i].dana, 6, user.alloc[i].percent);
			printf("+------+----------------------------+---------------+---------+\n");
		}
		
		printf("|        JUMLAH                     | %-*ld | 100.00%% |\n", 13, user.dana.danaAlloc);
		printf("+===================================+===============+=========+\n");
	}
}

void searchDatabase(User user, int size) {
	if (size == 0) {
		printf("+========================+\n");
		printf("|     TIDAK ADA DATA     |\n");
		printf("+========================+\n");
	} else {
		int opsi;

		printf("\nOpsi:\n");
		printf("1. Search berdasarkan nama alokasi dana\n");
		printf("2. Search berdasarkan nominal alokasi dana\n");
		printf("3. Search berdasarkan persentase alokasi dana\n");
		
		printf("Pilihan: ");
		scanf("%d", &opsi);
		switch(opsi) {
			case 1:
				searchByNama(user, size);
				break;
			case 2:
				searchByNominal(user, size);
				break;
			case 3:
				searchByPercent(user, size);
				break;
			default:
				printf("Gagal mencari data\n\n");
		}
	}
}

void sortDatabase(User user, int size) {
	if (size == 0) {
		printf("+========================+\n");
		printf("|     TIDAK ADA DATA     |\n");
		printf("+========================+\n");
	} else {
		int opsi;

		printf("\nOpsi:\n");
		printf("1. Sort berdasarkan nama alokasi dana\n");
		printf("2. Sort berdasarkan nominal/persentase alokasi dana\n");
		printf("3. Sort berdasarkan waktu ditambahkannya data\n");
		printf("Pilihan: ");
		scanf("%d", &opsi);

		switch(opsi) {
			case 1:
				sortByNama(user, size);
				break;
			case 2:
				sortByNominal(user, size);
				break;
			case 3:
				sortByIndex(user, size);
				break;
			default:
				printf("Gagal mengurutkan data\n\n");
		}
	}
}

void programExpl() {
    printf("+================================================================================================+\n");
	printf("|                                   HARAP DIBACA DENGAN TELITI                                   |\n");
	printf("+================================================================================================+\n");
	printf("| 1. Program ini dibuat untuk mengelola keuangan user, dimana user dapat memasukkan dana yang    |\n");
	printf("|    dimiliki dan mengalokasikan dana tersebut untuk keperluan yang diinginkan oleh user.        |\n");
	printf("|    Alokasi dana yang dimaksud di sini adalah pemindahan dana ke dalam rekening akun bank       |\n");
	printf("|    lain yang haknya masih menjadi milik kita sehingga prosesnya masih bisa dibatalkan          |\n");
	printf("|    dengan mudah untuk menarik kembali dana yang berada di rekening bank lain. Contoh penerapan |\n");
	printf("|    dari praktik ini adalah Blue BCA.                                                           |\n");
	printf("| 2. Program juga bisa melakukan transfer dana ke rekening bank yang bukan miliknya, tetapi      |\n");
	printf("|    transfer dana ini tidak bisa dibatalkan karena berurusan dengan akun yang bukan milik       |\n");
	printf("|    atau hak kita, melainkan milik orang lain.                                                  |\n");
	printf("| 3. Demi keamanan user, masukan dana dan pengalokasian dana memerlukan akses password.          |\n");
	printf("| 4. User dapat melakukan searching serta sorting kepada data yang sudah dimasukkan sebelumnya   |\n");
	printf("|    TANPA harus memasukkan password                                                             |\n");
	printf("| 5. Setiap data yang dimasukkan oleh user akan masuk ke database dalam bentuk file dengan       |\n");
	printf("|    nama \"AllocationDatabase.txt\"                                                               |\n");
	printf("| 6. Jika Program tidak mendeteksi adanya kartu maka program akan memberikan opsi untuk keluar   |\n");
	printf("|    atau membuat akun/rekening bank baru                                                        |\n");
	printf("+================================================================================================+\n\n");

    printf("Press ANY key to continue!");
    getch();
    system("cls");
}

void transferSaldo(User *user) {
	char name[MAX_NAME_LENGTH];
	char pass[MAX_NAME_LENGTH];
	char source[] = "Databases/Database.txt";
	char destination[] = "Databases/Database.txt";

	char rekeningInp[MAX_REKENING_LENGTH];
	long int saldoInp;

	UserData users[MAX_USERS];
	int i, numUsers, idx;
	
	FILE *file;

	file = fopen(source, "r");

	if (file == NULL) {
		printf("File gagal dibuka!\n");
		exit(0);
	}

	for (i = 0; !feof(file); i++) {
		fscanf(file, "%d\n", &users[i].index);
		fscanf(file, "%[^\n]\n", users[i].name);
		fscanf(file, "%[^\n]\n", users[i].pass); 
		fscanf(file, "%[^\n]\n", users[i].rekening); 
		fscanf(file, "%ld\n\n", &users[i].saldo);
	}
	
	fclose(file);

	numUsers = i;
		
	printf("Masukkan nomor rekening yang ingin dituju   : ");
	scanf(" %[^\n]", rekeningInp);

	for(i = 0; i < numUsers; i++) {
		if (strcmp(users[i].rekening, rekeningInp) == 0) {
			idx = i;
			break;
		}
	}

	if (i == numUsers) {
		printf("\nNomor rekening tidak ditemukan");
		printf("\nGagal transfer saldo\n\n");
		return;
	}

	printf("\nNama tujuan : %s", users[idx].name);
	printf("\nSaldo anda  : %ld\n\n", user->dana.saldoSisa);

	do {
		printf("Masukkan jumlah saldo yang ingin ditransfer : ");
		scanf("%ld", &saldoInp);
		if (user->dana.saldoSisa < saldoInp) {
			printf("Jumlah melebihi saldo yang tersedia, harap masukkan angka yang lebih kecil\n");
		}
	} while (user->dana.saldoSisa < saldoInp);

	users[idx].saldo += saldoInp;
    user->dana.saldoTotal -= saldoInp;
    user->dana.saldoSisa -= saldoInp;

	for(i = 0; i < numUsers; i++) {
		if (strcmp(users[i].name, user->name) == 0) {
			users[i].saldo = user->dana.saldoTotal;
			break;
		}
	}

	file = fopen(destination, "w");
	
	if (file == NULL) {
		printf("File gagal dibuka!\n");
		return;
	}

	for (i = 0; i < numUsers; i++) {
		fprintf(file, "%d\n", users[i].index);
		fprintf(file, "%s\n", users[i].name);
		fprintf(file, "%s\n", users[i].pass);
		fprintf(file, "%s\n", users[i].rekening);
		fprintf(file, "%ld\n\n", users[i].saldo);
	}

	fclose(file);

	system("cls");
	printf("Transfer saldo berhasil!\n\n");
}

void editNamePass(User *user, int *size) {
	int opsi, i, j, found;

	UserData users[MAX_USERS];
    char name[MAX_NAME_LENGTH];
	char namaTemp[MAX_NAME_LENGTH];
	char passTemp[MAX_NAME_LENGTH];
	
	int numUsers = 0;
	
	strcpy(namaTemp, user->name);
	strcpy(passTemp, user->pass);
	printf("\nOpsi:\n");
	printf("1. Ubah username\n");
	printf("2. Ubah password\n");

	printf("Pilihan: ");
	scanf("%d", &opsi);

	switch(opsi) {
		case 1:
			getAccess(*user, size);
			printf("Masukkan username baru: ");
			scanf(" %[^\n]", user->name);
			
			namePassUpdate(*user, namaTemp, passTemp, opsi);

			printf("Username berhasil diubah!\n\n");
			break;
		case 2:
			getAccess(*user, size);
			
			char confirm[50];
			
			printf("\nMasukkan password baru   : ");
			scanf("%s", user->pass);
			printf("Konfirmasi password baru : ");
			scanf("%s", &confirm);
			
			while(strcmp(user->pass, confirm) != 0) {
				system("cls");
				
				printf("Gagal menyimpan password\nSilahkan masukkan kembali\n");
				printf("\nMasukkan password baru   : ");
				scanf("%s", user->pass);
				printf("Konfirmasi password baru : ");
				scanf("%s", &confirm);
			}

			namePassUpdate(*user, namaTemp, passTemp, opsi);
			
			system("cls");
			printf("Password berhasil diubah!\n\n");
			break;
		default:
			printf("Gagal mengubah data\n\n");
	}
}
