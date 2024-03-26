void searchByNama(User user, int size) {
    int cek, i, j, k, ada = 0;
    char search[100];

	long int sumDana = 0;
	float sumPercent = 0;

	printf("\nMasukkan nama yang ingin dicari: ");
	scanf(" %[^\n]", &search);
	
	system("cls");
	printf("Kunci : %s\n\n");
	printf("+======+============================+===============+=========+\n");
	printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
	printf("+======+============================+===============+=========+\n");
	
	for (i = 0; i < size; i++){
		cek = 0;

		for (j = 0; cek < strlen(search) && j < strlen(user.alloc[i].nama); j++) {
			if (tolower(search[cek]) == tolower(user.alloc[i].nama[j]))
				cek++;
			else
				cek = 0;
		}

		if (cek == strlen(search)){
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", i + 1, 3, ".", 26, user.alloc[i].nama, 13, user.alloc[i].dana, 6, user.alloc[i].percent);
			printf("+------+----------------------------+---------------+---------+\n");

			sumDana += user.alloc[i].dana;
			sumPercent += user.alloc[i].percent;
			ada++;
		}
	}

	if (ada == 0) {
		printf("|        TIDAK ADA DATA                                       |\n");
		printf("+=============================================================+\n");
	} else {
		printf("|        JUMLAH                     | %-*ld | %-*.2f%% |\n", 13, sumDana, 6, sumPercent);
		printf("+===================================+===============+=========+\n");
	}
}

void searchByNominal(User user, int size) {
	int i, j = 0;
	long int bottom, top;

	long int sumDana = 0;
	float sumPercent = 0;

	printf("\nMasukkan batas bawah : ");
	scanf("%ld", &bottom);
	printf("Masukkan batas atas  : ");
	scanf("%ld", &top);
	
	system("cls");
	printf("Range : %ld s/d %ld\n\n", bottom, top);
	printf("+======+============================+===============+=========+\n");
	printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
	printf("+======+============================+===============+=========+\n");

	for (i = 0; i < size; i++) {
		if (user.alloc[i].dana >= bottom && user.alloc[i].dana <= top){
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", i + 1, 3, ".", 26, user.alloc[i].nama, 13, user.alloc[i].dana, 6, user.alloc[i].percent);
			printf("+------+----------------------------+---------------+---------+\n");

			sumDana += user.alloc[i].dana;
			sumPercent += user.alloc[i].percent;
			j++;
		}
	}

	if (j == 0){
		printf("|        TIDAK ADA DATA                                       |\n");
		printf("+=============================================================+\n");
	} else {
		printf("|        JUMLAH                     | %-*ld | %-*.2f%% |\n", 13, sumDana, 6, sumPercent);
		printf("+===================================+===============+=========+\n");
	}
}

void searchByPercent(User user, int size) {


	int i, j = 0;
	float bottom, top;

	long int sumDana = 0;
	float sumPercent = 0;

	printf("\nMasukkan batas bawah : ");
	scanf("%f", &bottom);
	printf("Masukkan batas atas  : ");
	scanf("%f", &top);
	
	system("cls");
	printf("Range : %.2f s/d %.2f\n\n", bottom, top);
	printf("+======+============================+===============+=========+\n");
	printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
	printf("+======+============================+===============+=========+\n");

	for (i = 0; i < size; i++) {
		if (user.alloc[i].percent >= bottom && user.alloc[i].percent <= top){
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", i + 1, 3, ".", 26, user.alloc[i].nama, 13, user.alloc[i].dana, 6, user.alloc[i].percent);
			printf("+------+----------------------------+---------------+---------+\n");

			sumDana += user.alloc[i].dana;
			sumPercent += user.alloc[i].percent;
			j++;
		}
	}

	if (j == 0){
		printf("|        TIDAK ADA DATA                                       |\n");
		printf("+=============================================================+\n");
	} else {
		printf("|        JUMLAH                     | %-*ld | %-*.2f%% |\n", 13, sumDana, 6, sumPercent);
		printf("+===================================+===============+=========+\n");
	}
}

void sortByNama(User user, int size) {
	int i, j, opsi;
	char tempString1[MAX_NAME_LENGTH];
	char tempString2[MAX_NAME_LENGTH];

	int tempIdx;
    char safe[100];
	long int temp;
	float tempPercent;
	
	User sort;
	int idx[size];

	sort.alloc = (Alloc *)malloc(size * sizeof(Alloc));

	for (i = 0; i < size; i++) {
		strcpy(sort.alloc[i].nama, user.alloc[i].nama);
		sort.alloc[i].dana = user.alloc[i].dana;
		sort.alloc[i].percent = user.alloc[i].percent;
		idx[i] = i + 1;
	}

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
			strcpy(tempString1, sort.alloc[j].nama);
			strcpy(tempString2, sort.alloc[j + 1].nama);
			lowercase(tempString1);
			lowercase(tempString2);
            if (strcmp(tempString1, tempString2) > 0) {
            	tempIdx = idx[j];
				idx[j] = idx[j + 1];
				idx[j + 1] = tempIdx;
				
				strcpy(safe, sort.alloc[j].nama);
                strcpy(sort.alloc[j].nama, sort.alloc[j + 1].nama);
                strcpy(sort.alloc[j + 1].nama, safe);
                
                temp = sort.alloc[j].dana;
                sort.alloc[j].dana = sort.alloc[j + 1].dana;
                sort.alloc[j + 1].dana = temp;
                
				tempPercent = sort.alloc[j].percent;
                sort.alloc[j].percent = sort.alloc[j + 1].percent;
                sort.alloc[j + 1].percent = tempPercent;
            }
        }
    }

	printf("\nOpsi:\n");
		printf("1. Ascending (A - Z)\n");
		printf("2. Descending (Z - A)\n");
		printf("Pilihan: ");
		scanf("%d", &opsi);

	system("cls");

	if (opsi == 1){
		printf("Diurutkan berdasarkan nama secara Ascending\n\n");
		printf("+======+============================+===============+=========+\n");
		printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
		printf("+======+============================+===============+=========+\n");
		for (i = 0; i < size; i++) {
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", idx[i], 3, ".", 26, sort.alloc[i].nama, 13, sort.alloc[i].dana, 6, sort.alloc[i].percent);
			printf("+------+----------------------------+---------------+---------+\n");
		}
	} else {
		printf("Diurutkan berdasarkan nama secara Descending\n\n");
		printf("+======+============================+===============+=========+\n");
		printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
		printf("+======+============================+===============+=========+\n");
		for (i = size - 1; i >= 0; i--) {
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", idx[i], 3, ".", 26, sort.alloc[i].nama, 13, sort.alloc[i].dana, 6, sort.alloc[i].percent);
			printf("+======+============================+===============+=========+\n");
		}		
	}
	printf("|        JUMLAH                     | %-*ld | 100.00%% |\n", 13, user.dana.danaAlloc);
	printf("+===================================+===============+=========+\n");
}

void sortByNominal(User user, int size) {
	int i, j, opsi;

	int tempIdx;
    char safe[100];
	long int temp;
	float tempPercent;
	
	User sort;
	int idx[size];

	sort.alloc = (Alloc *)malloc(size * sizeof(Alloc));

	for (i = 0; i < size; i++) {
		strcpy(sort.alloc[i].nama, user.alloc[i].nama);
		sort.alloc[i].dana = user.alloc[i].dana;
		sort.alloc[i].percent = user.alloc[i].percent;
		idx[i] = i + 1;
	}

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (sort.alloc[j].dana > sort.alloc[j + 1].dana) {
            	tempIdx = idx[j];
				idx[j] = idx[j + 1];
				idx[j + 1] = tempIdx;
				
				strcpy(safe, sort.alloc[j].nama);
                strcpy(sort.alloc[j].nama, sort.alloc[j + 1].nama);
                strcpy(sort.alloc[j + 1].nama, safe);
                
                temp = sort.alloc[j].dana;
                sort.alloc[j].dana = sort.alloc[j + 1].dana;
                sort.alloc[j + 1].dana = temp;
                
				tempPercent = sort.alloc[j].percent;
                sort.alloc[j].percent = sort.alloc[j + 1].percent;
                sort.alloc[j + 1].percent = tempPercent;
            }
        }
    }

	printf("\nOpsi:\n");
		printf("1. Ascending\n");
		printf("2. Descending\n");
		printf("Pilihan: ");
		scanf("%d", &opsi);

	system("cls");

	if (opsi == 1){
		printf("Diurutkan berdasarkan nominal/persentase secara Ascending\n\n");
		printf("+======+============================+===============+=========+\n");
		printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
		printf("+======+============================+===============+=========+\n");
		for (i = 0; i < size; i++) {
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", idx[i], 3, ".", 26, sort.alloc[i].nama, 13, sort.alloc[i].dana, 6, sort.alloc[i].percent);
			printf("+======+============================+===============+=========+\n");
		}
	} else {
		printf("Diurutkan berdasarkan nominal/persentase secara Descending\n\n");
		printf("+======+============================+===============+=========+\n");
		printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
		printf("+======+============================+===============+=========+\n");
		for (i = size - 1; i >= 0; i--) {
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", idx[i], 3, ".", 26, sort.alloc[i].nama, 13, sort.alloc[i].dana, 6, sort.alloc[i].percent);
			printf("+------+----------------------------+---------------+---------+\n");
		}		
	}
	printf("|        JUMLAH                     | %-*ld | 100.00%% |\n", 13, user.dana.danaAlloc);
	printf("+===================================+===============+=========+\n");
}

void sortByIndex(User user, int size) {
	int i, j, opsi;

	int tempIdx;
    char safe[100];
	long int temp;
	float tempPercent;
	
	User sort;
	int idx[size];

	sort.alloc = (Alloc *)malloc(size * sizeof(Alloc));

	for (i = 0; i < size; i++) {
		strcpy(sort.alloc[i].nama, user.alloc[i].nama);
		sort.alloc[i].dana = user.alloc[i].dana;
		sort.alloc[i].percent = user.alloc[i].percent;
		idx[i] = i + 1;
	}

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (idx[j] > idx[j + 1]) {
            	tempIdx = idx[j];
				idx[j] = idx[j + 1];
				idx[j + 1] = tempIdx;
				
				strcpy(safe, sort.alloc[j].nama);
                strcpy(sort.alloc[j].nama, sort.alloc[j + 1].nama);
                strcpy(sort.alloc[j + 1].nama, safe);
                
                temp = sort.alloc[j].dana;
                sort.alloc[j].dana = sort.alloc[j + 1].dana;
                sort.alloc[j + 1].dana = temp;
                
				tempPercent = sort.alloc[j].percent;
                sort.alloc[j].percent = sort.alloc[j + 1].percent;
                sort.alloc[j + 1].percent = tempPercent;
            }
        }
    }

	printf("\nOpsi:\n");
		printf("1. Ascending (Terlama - Terbaru)\n");
		printf("2. Descending (Terbaru - Terlama)\n");
		printf("Pilihan: ");
		scanf("%d", &opsi);

	system("cls");

	if (opsi == 1){
		printf("Diurutkan dari data terlama s/d terbaru\n\n");
		printf("+======+============================+===============+=========+\n");
		printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
		printf("+======+============================+===============+=========+\n");
		for (i = 0; i < size; i++) {
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", idx[i], 3, ".", 26, sort.alloc[i].nama, 13, sort.alloc[i].dana, 6, sort.alloc[i].percent);
			printf("+======+============================+===============+=========+\n");
		}
	} else {
		printf("Diurutkan dari data terbaru s/d terlama\n\n");
		printf("+======+============================+===============+=========+\n");
		printf("| Idx. | Nama Alokasi               | Nominal       | %%       |\n");
		printf("+======+============================+===============+=========+\n");
		for (i = size - 1; i >= 0; i--) {
			printf("| %d%-*s | %-*s | %-*ld | %-*.2f%% |\n", idx[i], 3, ".", 26, sort.alloc[i].nama, 13, sort.alloc[i].dana, 6, sort.alloc[i].percent);
			printf("+------+----------------------------+---------------+---------+\n");
		}		
	}
	printf("|        JUMLAH                     | %-*ld | 100.00%% |\n", 13, user.dana.danaAlloc);
	printf("+===================================+===============+=========+\n");
}