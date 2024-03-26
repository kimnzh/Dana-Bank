void mainMenu(User user, int *size) {
	int opsi = -1;
	char opsiString[50];
	long int danaTotal;

	do {
		danaTotal = user.dana.saldoTotal;
		printf("++===========================++========================================++\n");
		printf("|| BANK PROGLAN SYARIAH      ||       MAIN MENU ATM BANK PROGLAN       ||\n");
		printf("||         MANAGEMENT SYSTEM |+===+====================================+|\n");
		printf("|+===========================+| 1 | Setor/tarik dana yang tersedia     ||\n");
		printf("|| Username                  || 2 | Tambah alokasi dana                ||\n");
		printf("||  %                     -*s|| 3 | Batalkan alokasi dana              ||\n", 25, user.name);
		printf("||===========================||   |                                    ||\n");
		printf("|| Saldo                     || 4 | Tampilkan riwayat alokasi dana     ||\n");
		printf("|| %                     -*ld|| 5 | Search riwayat alokasi dana        ||\n", 26, user.dana.saldoTotal);
		printf("|| Dana Alokasi              || 6 | Sort riwayat dana yang teralokasi  ||\n");
		printf("|| %                     -*ld||   |                                    ||\n", 26, user.dana.danaAlloc);
		printf("|| Saldo Tersisa             || 7 | Panduan Penggunaan Program         ||\n");
		printf("|| %                     -*ld|| 8 | Transfer saldo ke rekening lain    ||\n", 26, user.dana.saldoSisa);
		printf("|+===========================+|   |                                    ||\n");
		printf("|| Jumlah Alokasi Dana       || 9 | Edit username dan password*        ||\n");
		printf("|| %                      -*d|| 0 | Exit program                       ||\n", 26, *size);
		printf("++===========================++===+====================================++\n\n");
	
		printf("* : Memerlukan akses password\n\n");
	
		printf("Pilihan: ");
		scanf(" %[^\n]", opsiString);
		opsi = atoi(opsiString);

		switch(opsi) {
			case 0:
				writeData(user, *size);
				system("cls");
				updateKartu(user, danaTotal);
				databaseUpdate(user);
				printf("Terimakasih Karena sudah menggunakan program ini!\n\n");
				printf("Press ANY key to continue!");
				getch();
				break;
			case 1:
				system("cls");
				editDana(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 2:
				system("cls");
				addAlokasiDana(&user, size);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 3:
				system("cls");
				removeAlokasiDana(&user, size);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 4:
				system("cls");
				showAllocation(user, *size);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 5:
				system("cls");
				searchDatabase(user, *size);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 6:
				system("cls");
				sortDatabase(user, *size);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 7:
				system("cls");
				programExpl();
				break;
			case 8:
				system("cls");
				transferSaldo(&user);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			case 9:
				system("cls");
				editNamePass(&user, size);
				printf("Press ANY key to continue!");
				getch();
				system("cls");
				break;
			default:
				printf("Input tidak valid\n");
				printf("Press ANY key to continue!");
				getch();
				system("cls");
		}
	} while (opsi != 0);
}
