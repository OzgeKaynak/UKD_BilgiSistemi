#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


#define MIN_LICENCE_NO 999
#define MAX_LICENCE_NO 10000
#define MIN_ID_NO 10
#define MAX_ID_NO 12
#define MIN_NAME 0
#define MAX_NAME 31
#define MIN_PLATE 0
#define MAX_PLATE 82
#define MAX_REGISTER_PLAYERS 100
#define MAX_CITY_PLAYER 100

#define PLAYER_FILE_NAME "sporcular.dat"
#define TOURNAMENTS_FILE_NAME "turnuva_genel.txt"
#define TOURNAMENTS_NAME "turnuvalar.dat"
#define ALL_TOURNAMENTS_NAME "tum_maclar.txt"
#define TOURNAMENTS_MATHCES_NAME "turnuva_maclar.txt"
#define COUNT_TOURNAMENT "count_tournament.txt"

typedef struct
{
	int licenceNo;
	char idNum[35];
	char name[35];
	int cityPlateNo;
	int UKDPoint;

} Player;

typedef struct
{
	char tournamentName[41];
	char toutnamentDate[11];
	char tournamentCity[16];
	float avarageUKD;
	Player players[MAX_REGISTER_PLAYERS];
} Tournaments;
typedef struct
{
	int tournamentNo;
	char tournamentName[41];
	char toutnamentDate[11];
	char tournamentCity[16];
} Tournament;


typedef struct
{
	int tournamentNo;
	int roundNo;
	int whiteLicenceNo;
	int blackLicenceNo;
	int result;
	float wUKDChange;
	float bUKDChange;
} AllGame;

typedef struct
{
	int roundNo;
	int whiteLicenceNo;
	int blackLicenceNo;
	int result;
	float wUKDChange;
	float bUKDChange;
} OneGame;

typedef enum { false = 0, true = 1 } bool;

//Global
float sumWUKDChange = 0;
float sumBUKDChange = 0;
int playerList[100] = { 0 };



// 1.Soru Yçin
void generalTournament();
void addFisrtPlayer(Player sample);
void addToutnament(char *tName, char *tDate, char *tCity);
char * strMatch(char *sample);
int countMatc(int i);

//MAin
FILE * openFile(char *fileName, char *mode);
bool isValid(int val, int minVal, int maxVal);
Player readPlayer(char * scope, int which);
void regularPrint();
int menu();
void createEmptyPlayer();

//1 in devamy
//Constructer Methot
void tournamentMathces();
void addAllMatchesFile(OneGame sample);
void updatePlayerUKD(float ukdChange, int licenceNo);
bool controlUKDChange();
void topon();

//9. soru sporcu ekleme

void addNewPlayer();
void addPlayer(Player sample, FILE * ptr, int val);
bool isPlayer(int licenceNo);
//9. soru son
void lisfOfPlayer();
char * whichCity(int plateNumber);

//Constructer Methot
void listOfInfo();
Player getRival(int licenceNo);
Tournament getTournament(int tournamentNo);
AllGame getGame(FILE *ptr);
Player getPlayerFor7Question(int licenceNo);


void listofCitiesPlayer();
void getPlayerList(int cityPlate);
void tournamentInfo();
bool isTournament(int tournamentNo);
bool isTournament1(int tournamentNo);
void onCity();
void cityUpdate();
void totalChange();
int sizeofArr(char *arr);
int main()
{
	setlocale(LC_ALL, "Turkish");

	createEmptyPlayer();  //Program dosyalarýn yaratýlmasý ile baþlýyor.
	int select;
	do{
		select = menu();
		if (select)
		{

			switch (select)
			{
			case 1:
				generalTournament();
				tournamentMathces();
				break;
			case 2:
				lisfOfPlayer();
				break;
			case 3:
				listOfInfo();
				break;
			case 4:
				listofCitiesPlayer();
				break;
			case 5:
				topon();
				break;
			case 6:
				onCity();
				break;
			case 7:
				tournamentInfo();
				break;
			case 8:
				totalChange();
				break;
			case 9:
				addNewPlayer();
				break;
			case 10:
				cityUpdate();
				break;
			}
		}
		else
			printf(" \n\n Program Tarafinizdan Sonlandirildi.");
	} while (select != 0);

	Player sample;
	FILE * playerPtr = fopen("sporcular.dat", "r+");
	printf("\n\n");
	printf("\n %-10s %-14s %-20s %-15s %-9s\n", "LISANS NO", "TC KIMLIK NO", "ADI SOYADI", "ILI", "UKD PUANI");
	printf(" ---------- -------------- ------------------ --------------- ---------\n");
	fread(&sample, sizeof(Player), 1, playerPtr);
	while (!feof(playerPtr))
	{
		if (sample.licenceNo != 0)
			printf(" %-10d %-14s %-20s %15d %-9d\n", sample.licenceNo, sample.idNum, sample.name, sample.cityPlateNo, sample.UKDPoint);
		fread(&sample, sizeof(Player), 1, playerPtr);
	}

	fclose(playerPtr);
	return 0;
}



void lisfOfPlayer()
{
	char idNum[12];
	Player sample;
	int arrSize;
	do
	{
		do{
			fflush(stdin);
			printf("\n\n  Bilgilerini Gormek istediginiz Oyuncunun Tc Kimlik Numarasini Girin: \n\n >>>  ");
			scanf("%s", idNum);
			arrSize = sizeofArr(idNum);
		} while (!isValid(arrSize, MIN_ID_NO, MAX_ID_NO));
		fflush(stdin);
		sample = readPlayer(idNum, 0);

		if (sample.licenceNo != 0)
		{
			printf("\n %-10s %-14s %-25s %-15s %-9s\n", "LISANS NO", "TC KIMLIK NO", "ADI SOYADI", "ILI", "UKD PUANI");
			printf(" ---------- -------------- ------------------------- --------------- ---------\n");
			printf(" %-10d %-14s %-25s %-15d %-9d", sample.licenceNo, sample.idNum, sample.name, sample.cityPlateNo, sample.UKDPoint);

		}
		else
		{
			printf(" Boyle Bir Sporcu Bulunamamistir.\n");
		}
	} while (sample.licenceNo == 0);

}


//This function post what players city. It use plateNumber.
char * whichCity(int plateNumber)
{
	switch (plateNumber)
	{
	case 1: return "Adana";

	case 2: return "Adiyaman";

	case 3: return "Afyon";

	case 4: return "Agri";

	case 5: return "Amasya";

	case 6: return "Ankara";

	case 7: return "Antalya";

	case 8: return "Artvin";

	case 9: return "Aydin";

	case 10: return "Balikesir";

	case 11: return "Bilecik";

	case 12: return "Bingol";

	case 13: return "Bitlis";

	case 14: return "Bolu";

	case 15: return "Burdur";

	case 16: return "Bursa";

	case 17: return "Canakkale";

	case 18: return "Cankiri";

	case 19: return "Corum";

	case 20: return "Denizli";

	default: return  "giresun";  break;


	}
}



//Actual Methots

void listOfInfo()
{
	char licNo[100];
	int arrSize;
	Player sample;
	int select = 2;
	do
	{
		do{
			printf("\n\n  Bilgilerini Gormek Istediginiz Oyuncunun Lisans Numarasini Girin: \n ");
			regularPrint();
			scanf("%s", licNo);
			arrSize = sizeofArr(licNo);  // 2. ve 3. soruda ayný metodu kullanabilmek için bunlar char yapýldý.
		} while (!isValid(arrSize, 3, 5));
		fflush(stdin);
		sample = readPlayer(licNo, 1);

		if (sample.licenceNo != 0)
		{
			printf("\n %-10s %-14s %-25s %-15s %-9s\n", "LISANS NO", "TC KIMLIK NO", "ADI SOYADI", "ILI", "UKD PUANI");
			printf(" ---------- -------------- ------------------------- --------------- ---------\n");
			printf(" %-10d %-14s %-25s %-15d %-9d", sample.licenceNo, sample.idNum, sample.name, sample.cityPlateNo, sample.UKDPoint);
			break;

		}
		else
		{
			printf(" \n\n  Boyle Bir Sporcu Bulunamamistir.\n");
			continue;
		}

	} while (sample.licenceNo == 0);


	Player player;
	Tournament tournament;

	int licenceNo = atoi(licNo);

	FILE * ptr = openFile(ALL_TOURNAMENTS_NAME, "r+");

	AllGame allGame;
	allGame = getGame(ptr); //bir satýr okuduk.


	printf(" \n\n Katildigi Turnuvalar oynadigi Maclar: \n");
	while (!feof(ptr))  //sonua kadar git.
	{
		int i;
		for (i = 1; i <= countMatc(1); i++)  //toplam turnuva kadar okuyacak.
		{
			float matchPoint=0;
			float totalMatchPoint = 0;
			float ukd;
			float totalUKD = 0;

			tournament = getTournament(allGame.tournamentNo);
			printf(" \n  Turnuva Adi: %s\n  Tarihi: %s \n  Sehri %s\n\n  ", tournament.tournamentName, tournament.toutnamentDate, tournament.tournamentCity);

			printf("%5s%10s%10s%10s%10s","Tur No", "Rakip Adi Soyadi","Rakip UKD","Mac Puani","  UKD Degisimi\n");
			printf("------  ----------------  ---------  ---------  ------------\n");


			while (allGame.tournamentNo == i)
			{

				if (licenceNo == allGame.whiteLicenceNo)
				{
					player = getRival(allGame.blackLicenceNo);
					ukd = allGame.wUKDChange;
					totalUKD += ukd;

					if (allGame.result == 1)
					{
						matchPoint = 1;
					}
					if (allGame.result == 0)
					{
						matchPoint = 0.5;
					}
					totalMatchPoint += matchPoint;

					printf("%1d%20s%10d%10.2f%10.2f\n", allGame.roundNo, player.name, player.UKDPoint, matchPoint, ukd);

				}
				if (licenceNo == allGame.blackLicenceNo)
				{
					player = getRival(allGame.whiteLicenceNo);
					ukd = allGame.bUKDChange;
					totalUKD += ukd;

					if (allGame.result == 2)
					{
						matchPoint = 1;
					}
					if (allGame.result == 0)
					{
						matchPoint = 0.5;
					}

					printf("%1d%20s%10d%10.2f%10.2f\n", allGame.roundNo, player.name, player.UKDPoint, matchPoint, ukd);
				}


				allGame = getGame(ptr);
			}

			printf(" \nToplam Mac Puani: %f\n", totalMatchPoint);
			printf(" \nToplam UKD Degisimi %f\n", totalUKD);
		}
	}
	fclose(ptr);


}

//Rakip bilgisi getir.
Player getRival(int licenceNo)
{
	Player sample;

	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");

	fseek(ptr, (licenceNo - 1000)*sizeof(Player), SEEK_SET);
	fread(&sample, sizeof(Player), 1, ptr);

	return sample;
}


//turnuva bilgisi getir.
Tournament getTournament(int tournamentNo)
{
	Tournament sample;
	FILE * ptr = openFile(TOURNAMENTS_NAME, "r+");
	fseek(ptr, (tournamentNo - 1)*sizeof(Tournament), SEEK_SET);
	fread(&sample, sizeof(Tournament), 1, ptr);
	fclose(ptr);
	return sample;
}

//tüm maçlardan birer satýr oku.
AllGame getGame(FILE *ptr)
{
	AllGame allGame;
	fscanf(ptr, "%d %d %d %d %d %f %f\n", &allGame.tournamentNo, &allGame.roundNo, &allGame.whiteLicenceNo, &allGame.blackLicenceNo, &allGame.result, &allGame.wUKDChange, &allGame.bUKDChange);

	return allGame;
}
//Constructer Functions


//Actual Functions
void listofCitiesPlayer()
{
	int cityPlate;
	do
	{
		printf(" \n  Gormek Istediginiz Ilin Plaka Kodu: ");
		regularPrint();
		scanf("%d", &cityPlate);
	} while (!(cityPlate>0 && cityPlate<82));

	getPlayerList(cityPlate);

}

void getPlayerList(int cityPlate)
{


	Player sample;
	Player player1[MAX_CITY_PLAYER];
	int i = 0;
	for (i = 0; i<MAX_CITY_PLAYER; i++)
		player1[i].licenceNo = 0;

	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");

	int k = 0;

	fseek(ptr, 0 * sizeof(Player), SEEK_SET);

	fread(&sample, sizeof(Player), 1, ptr);
	while (!feof(ptr))
	{
		if (sample.licenceNo != 0 && sample.cityPlateNo == cityPlate)
		{
			player1[k] = sample;
			k++;
		}

		fread(&sample, sizeof(Player), 1, ptr);
	}
	fclose(ptr);

	//int j;
	//Player temp;
	//ZAten lisan noya göre kaydettiði için zaten sýralý geliyor ki bu ??? Gerek yoktu sýralamaa.
	//for (i = 1; i < k; i++) {
	//	for (j = 0; j < k; j++) {
	//		if (player1[j].licenceNo > player1[j + 1].licenceNo) {

	//			temp = player1[j];

	//			player1[j] = player1[j + 1];

	//			player1[j + 1] = temp;
	//		}
	//	}
	//}

	printf("\n %-10s %-14s %-20s %-15s %-9s\n", "LISANS NO", "TC KIMLIK NO", "ADI SOYADI", "ILI", "UKD PUANI");
	printf(" ---------- -------------- ---------------------- --------------- ---------\n");
	for (i = 0; i < k; i++) {
		if (player1[i].licenceNo != 0)
		{
			printf(" %-10d %-14s %-20s %-15d %-9d\n", player1[i].licenceNo, player1[i].idNum, player1[i].name, player1[i].cityPlateNo, player1[i].UKDPoint);
		}
	}



}
//c


//
void topon()
{
	Player sample;
	Player player1[MAX_CITY_PLAYER];
	int i = 0;
	for (i = 0; i<MAX_CITY_PLAYER; i++)
		player1[i].licenceNo = 0;
	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");

	int k = 0;



	fread(&sample, sizeof(Player), 1, ptr);
	while (!feof(ptr))
	{
		if (sample.licenceNo != 0)
		{
			player1[k] = sample;
			k++;
		}

		fread(&sample, sizeof(Player), 1, ptr);
	}
	fclose(ptr);
	//Yukarýda hepsini diziye attým.

	int j;
	Player temp;

	for (i = 1; i < k; i++) {
		for (j = 0; j < k; j++) {
			if (player1[j].UKDPoint < player1[j + 1].UKDPoint) {

				temp = player1[j];

				player1[j] = player1[j + 1];

				player1[j + 1] = temp;
			}
		}
	}
	printf("\n %-10s %-14s %-20s %-15s %-9s\n", "LISANS NO", "TC KIMLIK NO", "ADI SOYADI", "ILI", "UKD PUANI");
	printf(" ---------- -------------- ---------------------- --------------- ---------\n");
	for (i = 0; i < k; i++) {
		if (player1[i].licenceNo != 0 && i<10)
		{
			printf(" %-10d %-14s %-20s %-15d %-9d\n", player1[i].licenceNo, player1[i].idNum, player1[i].name,player1[i].cityPlateNo, player1[i].UKDPoint);
		}
		if (player1[i].licenceNo != 0 && i > 9 && player1[9].UKDPoint == player1[i].UKDPoint)
		{
			printf(" %-10d %-14s %-20s %-15d %-9d\n", player1[i].licenceNo, player1[i].idNum, player1[i].name, player1[i].cityPlateNo, player1[i].UKDPoint);
		}
	}


}

//c


//
void onCity()
{
	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");

	Player sample;
	Player arr[MAX_CITY_PLAYER];
	int k = 0;
	fread(&sample, sizeof(Player), 1, ptr);
	int matrix[MAX_CITY_PLAYER][2];
	int i;

	for (i = 0; i<MAX_CITY_PLAYER; i++)
	{
		matrix[i][0] = 0;
		matrix[i][1] = 0;
	}

	for (i = 0; i < 81; i++)
	{
		matrix[i][0] = i + 1;
	}

	while (!feof(ptr))
	{
		if (sample.licenceNo != 0)
		{
			arr[k++] = sample;
			matrix[sample.cityPlateNo - 1][1] += 1;
		}

		fread(&sample, sizeof(Player), 1, ptr);
	}

	//ELimizde dolu tüm playerler mevcut.
	printf("  %10s %10s", "Il Plaka Kodu", "Oyuncu Sayisi\n");
	printf("  --------------"" ----------\n");

	for (i = 0; i < 81; i++)
	{
		if (matrix[i][1] != 0)
		{
			printf("%10d %10d\n", matrix[i][0], matrix[i][1]);
		}
	}


}
//c


//
void tournamentInfo()
{
	int tournamentNo;


	int select = -3;
	do
	{
		printf(" \n  Turnuva Numarasini Giriniz:\n");
		regularPrint();
		scanf("%d", &tournamentNo);

		if (isTournament1(tournamentNo)) //Varmý kontrolü boolean ile yapýldý.
		{
			Tournament sample = getTournament(tournamentNo); //Diðer sýnýflar için yazdýðýmýz mettotan çektik.
			printf("\n  %-10s  %-35s   %-10s  %-15s\n", "Turnuva No", "Turnuva Adi", "Tarih", "Sehir");
			printf("  ----------  ------------------------------------  ----------  -----------\n");
			printf("  %-10d  %-35s   %-10s  %-15s\n", sample.tournamentNo, sample.tournamentName, sample.toutnamentDate, sample.tournamentCity);
			break;
		}
		else
		{
			fflush(stdin);
			printf(" \n  Boyle Bir Turnuva Nolu Kayit Yoktur.\n");
			printf(" \n  Tekrar Girmek Icin 1'e Munuye Donmek Icin 2 ye Basin.\n");
			regularPrint();
			scanf("%d", &select);
		}
		if (select == 2)
			return 0;
	} while (select);


	FILE * ptr = openFile(ALL_TOURNAMENTS_NAME, "a+");
	AllGame allGame;

	rewind(ptr);
	printf("\n\n  %30s%30s\n", "Beyaz Oynayanlar", "Siyah Oynayanlar\n");
	printf("  %7s%17s%5s%10s%10s%15s%5s", "Tur No", "Ad Soyad", "UKD", "Mac Puani", "-", "Mac Puani", "Ad Soyad UKD\n");
	printf("  ------  ----------------  ----  -------- - -------- - --------------  ----\n");

	fscanf(ptr, "%d %d %d %d %d %f %f", &allGame.tournamentNo, &allGame.roundNo, &allGame.whiteLicenceNo, &allGame.blackLicenceNo, &allGame.result, &allGame.wUKDChange, &allGame.bUKDChange);
	while (!feof(ptr))
	{
		Player player1, player2;
		float matchPointW = 0, matchPointB = 0;
		if (tournamentNo == allGame.tournamentNo)
		{
			player1 = getPlayerFor7Question(allGame.whiteLicenceNo);
			player2 = getPlayerFor7Question(allGame.blackLicenceNo);
			if (allGame.result == 1)
			{
				matchPointW = 1;
			}
			if (allGame.result == 0)
			{
				matchPointB = 0.5;
				matchPointW = 0.5;
			}
			if (allGame.result == 2)
			{
				matchPointB = 1;
			}
			printf("%7d %17s %5d %10.2f %10.2f %15s %5d\n", allGame.roundNo, player1.name, player1.UKDPoint, matchPointW, matchPointB, player2.name, player2.UKDPoint);
		}
		fscanf(ptr, "%d %d %d %d %d %f %f", &allGame.tournamentNo, &allGame.roundNo, &allGame.whiteLicenceNo, &allGame.blackLicenceNo, &allGame.result, &allGame.wUKDChange, &allGame.bUKDChange);
	}

	fclose(ptr);

}

Player getPlayerFor7Question(int licenceNo)
{
	Player player;
	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");

	fseek(ptr, (licenceNo - 1000)*sizeof(Player), SEEK_SET);
	fread(&player, sizeof(Player), 1, ptr);
	fclose(ptr);
	return player;

}

bool isTournament(int tournamentNo)
{
	//txt dosyasýndaki son sayýya kadar bir deðer girdi ise o turnuva vardýr demektir.
	//onu getiren hazýr metodumuz mevcut.

	//1 parametresi dosyada yazan en son turnuva noyu alýyor.

	if (tournamentNo <= countMatc(1) && tournamentNo>0)
		return true;
	else
		return false;
}


bool isTournament1(int tournamentNo)
{

	FILE *ptr = openFile("turnuvalar.dat", "r+");
	Tournament sample1;
	bool flag = false;
	int sayac = 0;
	fseek(ptr, (tournamentNo-1)*sizeof(Tournament), SEEK_SET);
	fread(&sample1, sizeof(Tournament), 1, ptr);

	if (sample1.tournamentNo == tournamentNo)
		return true;
	else
		return false;
}

//BO? DOSYA ÜRETME
void createEmptyPlayer()
{
	Player sample = { 0, "", "", 0, 0 };


	Tournament sample2 = { 0, "", "", "" };

	//when program started if sporcular.dat not exist,create empty file.
	FILE * ptrPlayer = fopen(PLAYER_FILE_NAME, "r+");
	if (ptrPlayer == NULL)
	{
		FILE * ptr = openFile(COUNT_TOURNAMENT, "w");
		fprintf(ptr, "%d", 0); //program ilk açyldy?ynda countu syfyrlyyorum.

		ptrPlayer = fopen(PLAYER_FILE_NAME, "w");
		int i;
		for (i = 0; i <9000; i++)
			addPlayer(sample, ptrPlayer, 0);

		FILE * ptrTrv = fopen(TOURNAMENTS_NAME, "w");

		for (i = 0; i < 100; i++)
		{
			fwrite(&sample2, sizeof(Tournament), 1, ptrTrv);
		}
		FILE * ptrAllTrv = fopen(ALL_TOURNAMENTS_NAME, "w");


		fclose(ptr);
		fclose(ptrPlayer);
		fclose(ptrTrv);
		fclose(ptrAllTrv);
	}

}
//BO? DOSYA ÜRETME SON


//Di?er Gerekli Dosyalar //
//This function automatically opens files
FILE * openFile(char *fileName, char *mode)
{
	FILE * ptr = fopen(fileName, mode);
	if (!ptr)
	{
		printf(" Sorry...\"%s\" File Not Found!\n", fileName);
		printf(" Program Exit.\n");
		char wait = getc(stdin);
		exit(0);
	}
	else
		return ptr;
}

//To the input of the input validation function.
bool isValid(int val, int minVal, int maxVal)
{
	return (val > minVal && val < maxVal) ? true : false;
}

//Stringi Sonundkai alt satyrdan kurtarmak için yapyldy.
int sizeofArr(char *arr)
{
	int count = 0;
	int i;
	for (i = 0; arr[i] != NULL; i++)
	{
		count++;
	}
	return count;
}

//if your file incule the searching Player, this function return that.
// the "which" paramter define which function call.
Player readPlayer(char *scope, int which)
{
	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");
	Player sample;
	int flag = 0;
	while (!feof(ptr))
	{
		fread(&sample, sizeof(Player), 1, ptr);
		if (which == 0 && !memcmp(scope, sample.idNum, 12))
		{
			flag = 1;
			break;
		}
		else if (which == 1 && sample.licenceNo == atoi(scope))
		{
			flag = 1;
			break;
		}
	}
	fclose(ptr);
	if (flag)
		return sample;
	else
	{
		sample.licenceNo = 0;
		return sample;
	}

}


void regularPrint()
{
	printf("\n  >>>  ");
}


//String sonundaki alt satyry yok etmek için yazyldy.
char * strMatch(char *sample)
{
	int a = strlen(sample);
	char c[100] = "";
	int i;
	for (i = 0; i < a - 1; i++)
	{
		c[i] = sample[i];
	}
	return c;
}


int menu()
{

	int select;
	do
	{

		printf("\n\n   -------------------------------------------------------------------------");
		printf("\n * 1. Biten bir turnuvaya iliskin bilgilerin sisteme aktarilmasi\n");
		printf(" * 2. Bir oyuncunun bilgilerinin listelenmesi\n");
		printf(" * 3. Bir oyuncunun bilgilerinin ve katildigi turnuvalarda oynadigi maclarin listelenmesi\n");
		printf(" * 4. Bir ildeki tum oyuncularin listelenmesi\n");
		printf(" * 5. UKD puani en yuksek 10 oyuncunun listelenmesi \n");
		printf(" * 6. Illerdeki oyuncu sayilarinin listelenmesi\n");
		printf(" * 7. Bir turnuvanin bilgilerinin ve turnuvada oynanan maclarin listelenmesi\n");
		printf(" * 8. Tum maclardaki beyaz-siyah karsilastirmasi\n");
		printf(" * 9. Yeni bir oyuncunun eklenmesi\n");
		printf(" *10. Bir oyuncunun ilinin guncellenmesi\n");
		printf(" *11. Cikmak icin 0 'a Bas:   \n\n");
		printf("\n   -------------------------------------------------------------------------");
		regularPrint();
		scanf("%d", &select);

	} while (select > 10 || select < 0);
	system("CLS");
	return select;
}
//Gerekli Dosyalar Son


//1.Soru Ba?langyç
void generalTournament()
{
	FILE * trnmtsPtr = openFile(TOURNAMENTS_FILE_NAME, "r+");



	//Dosyadan satyr satyr okuyor ve turnuva genel bilgilerini aktaryyor.
	Tournaments sampleTrnmnt;
	fgets(sampleTrnmnt.tournamentName, 100, trnmtsPtr);
	strcpy(sampleTrnmnt.tournamentName, strMatch(sampleTrnmnt.tournamentName));
	//Sondaki alt satyr kysmyny sildim.
	fgets(sampleTrnmnt.toutnamentDate, 100, trnmtsPtr);
	strcpy(sampleTrnmnt.toutnamentDate, strMatch(sampleTrnmnt.toutnamentDate));

	fgets(sampleTrnmnt.tournamentCity, 100, trnmtsPtr);
	strcpy(sampleTrnmnt.tournamentCity, strMatch(sampleTrnmnt.tournamentCity));

	char str[100] = "";
	fgets(str, 100, trnmtsPtr);
	strcpy(str, strMatch(str));
	sampleTrnmnt.avarageUKD = atof(str);  //burada floata çeviriyoruz sayyyy.

	int count = 0;   //dosya sonuna kadar okuyoruz. lisasly futbolculary almak için.
	while (!feof(trnmtsPtr))
	{
		int licenceNo;
		fscanf(trnmtsPtr, "%d", &licenceNo);
		sampleTrnmnt.players[count].licenceNo = licenceNo;
		playerList[count++] = licenceNo; //2. ksyymda turnuvaya katylanlar arasyndan lisans no çekmek için yapylyyor.
	}
	fclose(trnmtsPtr);
	addToutnament(sampleTrnmnt.tournamentName, sampleTrnmnt.toutnamentDate, sampleTrnmnt.tournamentCity); //Turnuva daty güncelliyor.
	printf(" \"%s\" Adli Turnuva Sisteme Kaydedildi.\n", sampleTrnmnt.tournamentName);
}
void addToutnament(char *tName, char *tDate, char *tCity)
{

	Tournament sample; // Örnek de?i?kene içerik dolduruluyor.
	strcpy(sample.tournamentCity, tCity);
	strcpy(sample.tournamentName, tName);

	sample.tournamentNo = countMatc(0);
	strcpy(sample.toutnamentDate, tDate);

	//Turnuva.dat dosyasynyn sonuna eri?mek için bu uygulandy.
	FILE * ptrTrv = openFile(TOURNAMENTS_NAME, "r+");
	int v = countMatc(1);
	fseek(ptrTrv, (v - 1)*sizeof(Tournament), SEEK_SET);
	fwrite(&sample, sizeof(Tournament), 1, ptrTrv);
	fclose(ptrTrv);
	fflush(stdin);
	//Güncelledi mi ?
	FILE *ptr = openFile("turnuvalar.dat", "r+");
	Tournament sample1;

	int sayac = 0;
	fseek(ptr, sayac*sizeof(Tournament), SEEK_SET);
	fread(&sample1, sizeof(Tournament), 1, ptr);

	while (!feof(ptr))
	{
		if (sample1.tournamentNo > 0)
		{
			printf("Turnuva no: %d \nTurnuva Adi %s \nTurnuva Sehri %s \nTurnuva Tarihi: %s sayac : %d\n\n\n", sample1.tournamentNo, sample1.tournamentName, sample1.tournamentCity, sample1.toutnamentDate, sayac);
			sayac++;
		}
		else
			break;

		fseek(ptr, (sayac)*sizeof(Tournament), SEEK_SET);
		fread(&sample1, sizeof(Tournament), 1, ptr);
	}
	fclose(ptr);
}


int countMatc(int i)  // Hangi turnuvayy dolduraca?y gücenlik için txt de tutuluyor.
{
	int c = 1;
	FILE * ptr = openFile(COUNT_TOURNAMENT, "r+");
	int count;
	fscanf(ptr, "%d", &count); //dosyada halihazyrda yazylan countu alyyorum. Model gönderece?im.
	c = count;
	fclose(ptr);


	//E?er sadece sayyyy ö?renmek için ça?yrylyyor ise. Ö?renip kapanmaly.
	if (i)
		return c;
	else
	{
		FILE * ptr2 = openFile(COUNT_TOURNAMENT, "w+"); //üzerine yeniden yazmak için bunu kullanyyorum.
		count += 1;
		fprintf(ptr2, "%d", count);
		fclose(ptr2);

		return count;
	}


}
//1. ilkSoru Bitiþ
//1. soru devam
void tournamentMathces()
{

	Player sample3;
	FILE * playerPtr = fopen("sporcular.dat", "r+");
	printf("\n\n");
	printf("\n %-10s %-14s %-20s %-15s %-9s\n", "LISANS NO", "TC KIMLIK NO", "ADI SOYADI", "ILI", "UKD PUANI");
	printf(" ---------- -------------- ------------------ --------------- ---------\n");
	fread(&sample3, sizeof(Player), 1, playerPtr);
	while (!feof(playerPtr))
	{
		if (sample3.licenceNo != 0)
			printf(" %-10d %-14s %-20s %15d %-9d\n", sample3.licenceNo, sample3.idNum, sample3.name, sample3.cityPlateNo, sample3.UKDPoint);
		fread(&sample3, sizeof(Player), 1, playerPtr);
	}

	fclose(playerPtr);

	FILE * ptr = openFile(TOURNAMENTS_MATHCES_NAME, "r+");
	OneGame sample;
	while (!feof(ptr))
	{
		fscanf(ptr, "%d %d %d %d %f %f", &sample.roundNo, &sample.whiteLicenceNo, &sample.blackLicenceNo, &sample.result, &sample.wUKDChange, &sample.bUKDChange);

		//Beyaz ve siyah takýmlarýn ukd deðiþimleri GLOBAL.
		sumBUKDChange += sample.bUKDChange;
		sumWUKDChange += sample.wUKDChange;

		addAllMatchesFile(sample);

		updatePlayerUKD(sample.wUKDChange, sample.whiteLicenceNo);

		updatePlayerUKD(sample.bUKDChange, sample.blackLicenceNo);

	}

	if (true)
	{
		printf(" \n Turnuva Bilgileri Basarili Bir Bicimde Sisteme Eklenmistir.\n");
		printf(" \n Bir Sonraki Turnuva No: %d\n", countMatc(1) + 1);
	}




}

void addAllMatchesFile(OneGame sample)
{
	FILE * ptr = openFile(ALL_TOURNAMENTS_NAME, "a+");
	AllGame sample1;

	rewind(ptr);
	fscanf(ptr, "%d %d %d %d %d %f %f", &sample1.tournamentNo, &sample1.roundNo, &sample1.whiteLicenceNo, &sample1.blackLicenceNo, &sample1.result, &sample1.wUKDChange, &sample1.bUKDChange);
	while (!feof(ptr))
	{	//dosyanýn sonuna kadar okuyor.
		fscanf(ptr, "%d %d %d %d %d %f %f", &sample1.tournamentNo, &sample1.roundNo, &sample1.whiteLicenceNo, &sample1.blackLicenceNo, &sample1.result, &sample1.wUKDChange, &sample1.bUKDChange);
	}
	int a = (int)sample.wUKDChange;
	int b = (int)sample.bUKDChange;
	fprintf(ptr, "%d %d %d %d %d %d %d\n", countMatc(1), sample.roundNo, sample.whiteLicenceNo, sample.blackLicenceNo, sample.result, a, b);
	//Turnuva no'nun en son halini. kacinciturnuva.txt icinden alacaðýz.

	fclose(ptr);
}

void updatePlayerUKD(float ukdChange, int licenceNo)
{
	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");
	Player sample;

	fseek(ptr, (licenceNo - 1000)*sizeof(Player), SEEK_SET);
	fread(&sample, sizeof(Player), 1, ptr);

	//printf(" \n %d Lisan Nolu UKD: %.2f", sample.licenceNo, sample.name, sample.UKDPoint);
	sample.UKDPoint += (int)ukdChange;

	//printf(" \n Þimdiki Ukd Puaný: %d", (int)sample.UKDPoint);
	fseek(ptr, (licenceNo - 1000)*sizeof(Player), SEEK_SET);
	fwrite(&sample, sizeof(Player), 1, ptr);

	fclose(ptr);
}

bool controlUKDChange()
{
	FILE * ptr = openFile(PLAYER_FILE_NAME, "r+");
	int i;
	for (i = 0; playerList[i] != 0; i++) // Yukarda icine sýfýr atandýgý icin.
	{
		Player sample;
		fseek(ptr, (playerList[i] - 1000)*sizeof(Player), SEEK_SET);
		fread(&sample, sizeof(Player), 1, ptr);

		if (sample.UKDPoint < 1000)
		{
			sample.UKDPoint = 0;
			fseek(ptr, (playerList[i] - 1000)*sizeof(Player), SEEK_SET);
			fwrite(&sample, sizeof(Player), 1, ptr);
		}
	}
	fclose(ptr);

	return true;
}
//1. soru devam son
//Turnuca bitti?inde turnuva.dat y güncelleyecek.





//9. soru baslangic:
//Function is used to add new Player. Another method to send data to prepare.
void addNewPlayer()
{
	bool flag = true;
	Player sample = { 0, "", "", 0, 0 };
	int licenceNo, arrSize;
	do
	{
		printf("\n Oyuncunun Lisans Numarasi:(1000-9999) \n ");
		regularPrint();
		scanf("%d", &licenceNo);

		if (isValid(licenceNo, MIN_LICENCE_NO, MAX_LICENCE_NO) == false)
		{
			printf(" Sinir Degerlerin Disinda Girdiniz. Lutfen Yeniden,\n");
			continue;
		}
		else if (isPlayer(licenceNo))
		{
			printf(" Girmek Istediginiz Bu Kayit Doludur. Lutfen Yeniden,\n");
			continue;
		}
		else
			flag = false;
	} while (flag);

	do
	{
		fflush(stdin);
		printf("\n TC Kimlik No:\n ");
		regularPrint();
		scanf("%s", sample.idNum);
		arrSize = sizeofArr(sample.idNum);
	} while (!isValid(arrSize, MIN_ID_NO, MAX_ID_NO));

	do
	{
		fflush(stdin);
		printf("\n Adi Soyadi:\n ");
		regularPrint();
		gets(sample.name);
		arrSize = sizeofArr(sample.name);
	} while (!isValid(arrSize, MIN_NAME, MAX_NAME));

	do
	{
		fflush(stdin);
		printf("\n Il Plaka Kodu:\n ");
		regularPrint();
		scanf("%d", &sample.cityPlateNo);
	} while (!isValid(sample.cityPlateNo, MIN_PLATE, MAX_PLATE));

	do
	{
		fflush(stdin);
		printf("\n UKD Puanini Girin:\n ");
		regularPrint();
		scanf("%d", &sample.UKDPoint);
	} while (sample.UKDPoint<0);


	sample.licenceNo = licenceNo;

	FILE * ptrPlayer = openFile(PLAYER_FILE_NAME, "r+");
	addPlayer(sample, ptrPlayer, licenceNo);
	fclose(ptrPlayer);
	printf("\n Yeni Oyuncu Basariyla Sisteme Kaydedildi.!\n");
}

//This funtion used according to the parameters from the two functions.
void addPlayer(Player sample, FILE * ptr, int val)
{
	fflush(stdin);
	if (val)
	{
		fseek(ptr, (val - 1000)*sizeof(Player), SEEK_SET);
	}
	fwrite(&sample, sizeof(Player), 1, ptr);
}

bool isPlayer(int licenceNo)
{
	FILE * ptr = openFile(PLAYER_FILE_NAME, "r");
	Player sample = { 0, "", "", 0, 0 };
	fflush(stdin);
	fseek(ptr, (licenceNo - 1000)*sizeof(Player), SEEK_SET);
	fread(&sample, sizeof(Player), 1, ptr);
	fclose(ptr);
	if (sample.licenceNo == licenceNo)
		return true;
	else
		return false;
}
//9. soru bitis

//10. Soru

void cityUpdate()
{
	Player sample = { 0, "", "", 0, 0 };
	int licenceNo;
	do
	{
		printf("\n Ýlini Degistirecegin Oyuncunun Lisans Numarasi:(1000-9999) \n ");
		regularPrint();
		scanf("%d", &licenceNo);

		if (isValid(licenceNo, MIN_LICENCE_NO, MAX_LICENCE_NO) == false)
		{
			printf(" Sinir Degerlerin Disinda Girdiniz. Lutfen Yeniden,\n");
			continue;
		}
	} while (!isPlayer(licenceNo));

	FILE *ptr = fopen(PLAYER_FILE_NAME, "r+");
	fseek(ptr, (licenceNo - 1000)*sizeof(Player), SEEK_SET);
	fread(&sample, sizeof(Player), 1, ptr);

	printf(" \n Oyuncunun Simdiki Il Nosu: %d\n", sample.cityPlateNo);

	int nPlateNo;
	do
	{
		fflush(stdin);
		printf("\n Il Plaka Kodu:\n ");
		regularPrint();
		scanf("%d", &nPlateNo);
	} while (!isValid(nPlateNo, MIN_PLATE, MAX_PLATE));

	sample.cityPlateNo = nPlateNo;

	fseek(ptr, (licenceNo - 1000)*sizeof(Player), SEEK_SET);
	fwrite(&sample, sizeof(Player), 1, ptr);

	fclose(ptr);
}


//8. soru

void totalChange()
{
	float matchPoint = 0.0;
	float wTotalMatchPoint = 0.0;
	float bTotalMatchPoint = 0.0;
	float wUKDChange = 0.0;
	float bUKDChange = 0.0;

	FILE * ptr = openFile(ALL_TOURNAMENTS_NAME, "a+");
	AllGame allGame;

	rewind(ptr);
	fscanf(ptr, "%d %d %d %d %d %f %f", &allGame.tournamentNo, &allGame.roundNo, &allGame.whiteLicenceNo, &allGame.blackLicenceNo, &allGame.result, &allGame.wUKDChange, &allGame.bUKDChange);
	while (!feof(ptr))
	{
		if (allGame.result == 1)
		{
			matchPoint = 1;
			wTotalMatchPoint += matchPoint;

		}
		if (allGame.result == 0)
		{
			matchPoint = 0.5;
			wTotalMatchPoint += matchPoint;
			bTotalMatchPoint += matchPoint;

		}
		if (allGame.result == 2)
		{
			matchPoint = 1;
			bTotalMatchPoint += matchPoint;

		}
		wUKDChange += allGame.wUKDChange;
		bUKDChange += allGame.bUKDChange;
		fscanf(ptr, "%d %d %d %d %d %f %f", &allGame.tournamentNo, &allGame.roundNo, &allGame.whiteLicenceNo, &allGame.blackLicenceNo, &allGame.result, &allGame.wUKDChange, &allGame.bUKDChange);
	}

	fclose(ptr);

	printf("%15s %15s %15s\n", " ", "Beyaz Oynayanlar", "Siyah Oynayanlar");
	printf("%15s %15f %15f\n", "Toplam Mac Puani", wTotalMatchPoint, bTotalMatchPoint);
	printf("%15s %15f %15f\n", "Toplam UKD Degisimi", wUKDChange, bUKDChange);


}
