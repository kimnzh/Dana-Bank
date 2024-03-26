#ifndef DEFINE_H
#define DEFINE_H
#define MAX_USERS 100
#define MAX_NAME_LENGTH 50
#define MAX_PASS_LENGTH 50
#define MAX_REKENING_LENGTH 20

typedef struct {
	long int saldoTotal;
	long int danaAlloc;
	long int saldoSisa;
} Dana;

typedef struct {
	char nama[100];
	long int dana;
	float percent;
} Alloc;

typedef struct {
	int index;
	char name[MAX_NAME_LENGTH];
	char pass[MAX_PASS_LENGTH];
	char rekening[MAX_REKENING_LENGTH];
	Dana dana;
	Alloc *alloc;
} User;

typedef struct {
	int index;
    char name[MAX_NAME_LENGTH];
    char pass[MAX_NAME_LENGTH];
	char rekening[MAX_REKENING_LENGTH];
    long int saldo;
} UserData;

// Graphical
void mainMenu(User user, int *size);

// Function untuk opsi user
void editDana(User *user);
void addAlokasiDana(User *user, int *size);
void removeAlokasiDana(User *user, int *size);
void showAllocation(User user, int size);
void searchDatabase(User user, int size);
void sortDatabase(User user, int size);
void programExpl();
void transferSaldo(User *user);
void editNamePass(User *user, int *size);

// Additional
void initNamePass(User *user);
void updateAfterAlloc(User *user, long int danaAlloc);
void updateAfterRemove(User *user, long int danaRemove);
void getAccess(User user, int *size);
void getAccessMain(User user,int *size);
void percentUpdate(User *user, int size);
void namePassUpdate(User user, char namaTemp[], char passTemp[], int opsi);
void generateRekening(char *code, int length);

// Search and Sort
void searchByNama(User user, int size);
void searchByNominal(User user, int size);
void searchByPercent(User user, int size);
void sortByNama(User user, int size);
void sortByNominal(User user, int size);
void sortByIndex(User user, int size);

// File Handling
void databaseSearch(User *user);
void databaseUpdate(User user);
void writeData(User user, int size);
void readData(User *user, int *size);
void readKartu(User *user);
void updateKartu(User user, long int danaTotal);

// String Manipulation
void lowercase(char *string);
void append(char *string, char append[]);

#endif