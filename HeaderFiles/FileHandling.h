void databaseSearch(User *user) {
	int index;
	char name[MAX_NAME_LENGTH];
	char pass[MAX_NAME_LENGTH];
	char rekening[MAX_REKENING_LENGTH];
	char source[] = "Databases/Database.txt";
	long int saldo;

	int i;
	char line[100];
	
	FILE *file;

	file = fopen(source, "r");

	if (file == NULL) {
		printf("File gagal dibuka!\n");
		exit(0);
	}

	while (!feof(file)) {
		fscanf(file, "%d\n", index);
		fscanf(file, "%[^\n]\n", name);
		fscanf(file, "%[^\n]\n", pass); 
		fscanf(file, "%[^\n]\n", rekening); 
		fscanf(file, "%ld\n\n", &saldo);
		if (strcmp(user->name, name) == 0) {
			break;
		}
	}

	fclose(file);

	if (strcmp(user->name, name) == 0) {
		user->index = index;
		strcpy(user->pass, pass);
		strcpy(user->rekening, rekening);
		user->dana.saldoTotal = saldo;
	} else {
		printf("Username tidak ditemukan");
		exit(0);
	}
}

void databaseUpdate(User user) {
	char name[MAX_NAME_LENGTH];
	char pass[MAX_NAME_LENGTH];
	char source[] = "Databases/Database.txt";
	char destination[] = "Databases/Database.txt";

	UserData users[MAX_USERS];
	int i, numUsers;
	
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
		if (strcmp(user.name, users[i].name) == 0) {
			users[i].saldo = user.dana.saldoTotal;
		}
	}
	
	fclose(file);

	numUsers = i;

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
}

void writeData(User user, int size) {
    int i;
    char *destination = "Databases/AllocationDatabase.txt";
    
    FILE *file;

    file = fopen(destination, "w");

    if (file == NULL) {
        printf("File gagal dibuka!\n");
        exit(0);
    }

    fprintf(file, "%d\n", size);
    fprintf(file, "%ld\n\n", user.dana.saldoTotal);

    for (i = 0; i < size; i++) {
        fprintf(file, "%s\n", user.alloc[i].nama);
        fprintf(file, "%ld\n\n", user.alloc[i].dana);
    }

    fclose(file);

    system("cls");
    printf("Berhasil menyimpan data!\n\n");
}

void readData(User *user, int *size) {
    int i;
    char *source = "Databases/AllocationDatabase.txt", opsi;

    int buffInt;
    long int buffLongInt;
    char buffString[100];
    
    FILE *file;

    file = fopen(source, "r");

    if (file == NULL) {
        printf("File gagal dibuka!\n");
        return;
    }

    fscanf(file, "%d\n", &buffInt);
    fscanf(file, "%ld\n\n", &buffLongInt);

    *size = buffInt;
    user->dana.saldoTotal = buffLongInt;

    user->alloc = (Alloc *)realloc(user->alloc, (*size) * sizeof(Alloc));

    for (i = 0; !feof(file); i++) {
        fscanf(file, "%[^\n]\n", &buffString);
        fscanf(file, "%ld\n\n", &buffLongInt);
        strcpy(user->alloc[i].nama, buffString);
        user->alloc[i].dana = buffLongInt;
        user->dana.danaAlloc += buffLongInt;
    }

    updateAfterAlloc(user, 0);
    percentUpdate(user, *size);

    fclose(file);

    system("cls");
    printf("Berhasil mengambil data!\n\n");
}

void readKartu(User *user) {
	int i, opsi = -1;
	char opsiString[50];
	char source[] = "Card.txt";

    FILE *file;

    char scanLine[100];

    file = fopen(source, "r");
	
    if (file == NULL) {

		do {
			printf("+==========================+\n");
			printf("| Kartu TIDAK Terdeteksi!! |\n");
			printf("+==========================+\n\n");

			printf("Apakah Anda ingin membuat akun baru?\n");
			printf("1. Ya\n");
			printf("2. Tidak\n");
			printf("Jika tidak, maka program ini akan ditutup\n\n");

			printf("Masukkan pilihan: ");
			scanf("% [^\n]", opsiString);
			opsi = atoi(opsiString);

			switch(opsi) {
				case 1:
					initNamePass(user);
					break;
				case 2:
					exit(0);
				default:
					printf("Input tidak valid\n");
					printf("Press ANY key to continue!");
					getch();
					system("cls");
			}
		} while (opsi != 1);

    } else {
		printf("+====================+\n");
		printf("| Kartu Terdeteksi!! |\n");
		printf("+====================+\n\n");

		fgets(scanLine, sizeof(scanLine), file);
		fgets(scanLine, sizeof(scanLine), file);
		fgets(scanLine, sizeof(scanLine), file);
		fgets(scanLine, sizeof(scanLine), file);
		fgets(scanLine, sizeof(scanLine), file);
		sscanf(scanLine, "|   | Username : %[^.]", user->name);
		
		fclose(file);
    
		databaseSearch(user);
	}
}

void updateKartu(User user, long int danaTotal) {
	char buff[MAX_NAME_LENGTH];
	char ch = '.';
	char destination[] = "Card.txt";
	int i;
	
	FILE *file;

	file = fopen(destination, "w");

	strcpy(buff, user.name);
	strncat(buff, &ch, 1);

	fprintf(file, " _______________________________________________\n");
	fprintf(file, "|              Premium Member Card              |\n");
	fprintf(file, "|    -----=============================-----    |\n");
	fprintf(file, "|    _______________________________________    |\n");
	fprintf(file, "|   | Username : %-*s|   |\n", 27, buff);
	fprintf(file, "|   | Saldo    : Rp.%-*ld|   |\n", 24, user.dana.saldoTotal);
	fprintf(file, "|   |                                       |   |\n");
	fprintf(file, "|   | No Rek.  ");
	for (i = 0; i < 16; i++) {
		if (i % 4 == 0)
			fprintf(file, " ");
		fprintf(file, "%c", user.rekening[i]);
	}
	fprintf(file, "         |   |\n");
	fprintf(file, "|   |_______________________________________|   |\n");
	fprintf(file, "|                                               |\n");
	fprintf(file, "|                       BANK PROGLAN SYARIAH    |\n");
	fprintf(file, "|_______________________________________________|");

	fclose(file);
}

