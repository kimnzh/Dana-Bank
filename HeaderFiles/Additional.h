void initNamePass(User *user) {
	char confirm[50] = "";
	
	printf("Masukkan username   : ");
	scanf(" %[^\n]", user->name);
	printf("\nMasukkan password   : ");
	scanf(" %[^\n]", user->pass);
	printf("Konfirmasi password : ");
	scanf(" %[^\n]", &confirm);
	printf("\nHarap Masukkan saldo awal : ");
	scanf("%ld", &user->dana.saldoTotal);
	
	while(strcmp(user->pass, confirm) != 0) {
		system("cls");
		
		printf("Gagal menyimpan username dan password\nSilahkan masukkan kembali\n\n");
		printf("Masukkan username   : ");
		scanf(" %[^\n]", user->name);
		printf("\nMasukkan password   : ");
		scanf(" %[^\n]", user->pass);
		printf("Konfirmasi password : ");
		scanf(" %[^\n]", &confirm);
		printf("\nHarap Masukkan saldo awal : ");
		scanf("%ld", &user->dana.saldoTotal);
	}

	FILE *database;

    database = fopen("Databases/Database.txt","a");

    fprintf(database,"%s\n",user->name);
    fprintf(database,"%s\n",user->pass);
    fprintf(database,"%s\n",user->rekening);
    fprintf(database,"%ld\n\n",user->dana.saldoTotal);

    fclose(database);

	system("cls");
	printf("Username dan password berhasil disimpan\n\n");
	printf("Press ANY key to continue!");
	getch();
	system("cls");
}

void updateAfterAlloc(User *user, long int danaAlloc) {
	user->dana.danaAlloc += danaAlloc;
	user->dana.saldoSisa = user->dana.saldoTotal - user->dana.danaAlloc;
}

void updateAfterRemove(User *user, long int danaRemove) {
	user->dana.danaAlloc -= danaRemove;
	user->dana.saldoSisa = user->dana.saldoTotal - user->dana.danaAlloc;
}

void getAccess(User user,int *size) {
	int i, ch;
	char buffer[50];

	do {
		i = 0;
		printf("Masukkan PASSWORD: ");

		do {
			ch = getch();
			if (ch == ' ' || ch == 27) {
				continue;
			} else if (ch == '\b') {
				if (i > 0) {
					printf("\b \b");
					--i;
				} else {
					continue;
				}
			} else if (ch == '\r' || ch == '\t') {
				break;
			} else if (ch == 0 || ch == 224) {
				ch = getch();
				continue;
			} else {
				buffer[i++] = ch;
				printf("*");
			}
		} while(1);

		buffer[i] = '\0';
		printf("\n");

		if (strcmp(user.pass, buffer) != 0) {
			system("cls");
			printf("PASSWORD yang dimasukkan salah\n\n");
			printf("Press ANY key to continue!");
			getch();
			system("cls");
		} else if (strcmp(user.pass, buffer) == 0) {
			system("cls");
			return;
		}
	} while (strcmp != 0);
}

void percentUpdate(User *user, int size) {
	int i;

	for (i = 0; i < size; i++) {
		user->alloc[i].percent = ((float)user->alloc[i].dana / (float)user->dana.danaAlloc) * 100;
	}
}

void getAccessMain(User user,int *size) {
	int i, ch;
	char buffer[50];

	do {
		i = 0;
		printf("Masukkan PASSWORD: ");

		do {
			ch = getch();
			if (ch == ' ' || ch == 27) {
				continue;
			} else if (ch == '\b') {
				if (i > 0) {
					printf("\b \b");
					--i;
				} else {
					continue;
				}
			} else if (ch == '\r' || ch == '\t') {
				break;
			} else if (ch == 0 || ch == 224) {
				ch = getch();
				continue;
			} else {
				buffer[i++] = ch;
				printf("*");
				}
		} while (1);

		buffer[i] = '\0';
		printf("\n");

		if (strcmp(user.pass, buffer) != 0) {
			system("cls");
			printf("PASSWORD yang dimasukkan salah\n\n");
			printf("Press ANY key to continue!");
			getch();
			system("cls");
		} else if (strcmp(user.pass, buffer) == 0) {
			system("cls");
			return;
		}
	} while (strcmp(user.pass, buffer) != 0);
}

void namePassUpdate(User user, char namaTemp[], char passTemp[], int opsi) {
	char source[] = "Databases/Database.txt";
	char destination[] = "Databases/Database.txt";

	UserData users[MAX_USERS];
	int i = 0, numUsers = 0;
	char line[100];

	FILE *file;
			
	file = fopen(source, "r");

	if (file == NULL) {
		printf("File gagal dibuka!\n");
		return;
	}
	
	while (!feof(file)) {
		fscanf(file, "%[^\n]\n", users[i].name);
		fscanf(file, "%[^\n]\n", users[i].pass); 
		fscanf(file, "%ld\n\n", &users[i].saldo);
		numUsers++;
		i++;
	}
	
	fclose(file);

	switch (opsi) {
		case 1:
			for (i = 0; i < numUsers; i++) {
				if (strcmp(namaTemp, users[i].name) == 0) {
					strcpy(users[i].name, user.name);
					break;
				}	
			}
			break;
		case 2:
			for (i = 0; i < numUsers; i++) {
				if (strcmp(passTemp, users[i].name) == 0) {
					strcpy(users[i].name, user.name);
					break;
				}	
			}
			break;
	}

	file = fopen(destination, "w");
	
	if (file == NULL) {
		printf("File gagal dibuka!\n");
		return;
	}

	for (i = 0; i < numUsers; i++) {
		fprintf(file, "%s\n", users[i].name);
		fprintf(file, "%s\n", users[i].pass);
		fprintf(file, "%ld\n\n", users[i].saldo);
	}

	fclose(file);
}

void generateRekening(char *code, int length) {
    const char charset[] = "0123456789";

    for (int i = 0; i < length; i++) {
        int index = rand() % (int)(sizeof(charset) - 1);
        code[i] = charset[index];
    }

    code[length] = '\0';
}