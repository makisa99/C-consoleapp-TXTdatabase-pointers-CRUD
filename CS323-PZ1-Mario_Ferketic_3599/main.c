#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
typedef struct Zaposleni {
	char ime[35];
	char prezime[35];
	char pozicija[35];
	char JMBG[14];
	int plata;
} Zaposleni;

void setValuesFajl(Zaposleni* zap, FILE* f) { //Postavljanje vrednosti u fajl
	printf("Unesite ime zaposlenog: ");
	scanf_s("%s", &zap->ime, 35);
	printf("Unesite prezime zaposlenog: ");
	scanf_s("%s", &zap->prezime, 35);
	printf("Unesite poziciju zaposlenog: ");
	scanf_s("%s", &zap->pozicija, 35);
	printf("Unesite JMBG zaposlenog: ");
	scanf_s("%s", &zap->JMBG, 14);

	printf("Unesite platu zaposlenog: ");
	scanf_s("%d", &zap->plata);

	fprintf(f, "\n%s %s %s %s %d",
		zap->ime, zap->prezime, zap->pozicija, zap->JMBG, zap->plata);
	printf("\n");
};
void setValuesFajl2(Zaposleni* zap, FILE* f, int* prvi) { //Postavljanje vrednosti kada se deletuje
	if (*prvi != 0) {
		fprintf(f, "\n%s %s %s %s %d",
			zap->ime, zap->prezime, zap->pozicija, zap->JMBG, zap->plata);
	}
	else {
		fprintf(f, "%s %s %s %s %d",
			zap->ime, zap->prezime, zap->pozicija, zap->JMBG, zap->plata);
	}
}

void getValues(const Zaposleni* zap) { //Uzimanje vrednosti iz Zaposlenih
	printf("Ime zaposlenog: %s\n", zap->ime);
	printf("Prezime zaposlenog: %s\n", zap->prezime);
	printf("Pozicija zaposlenog: %s\n", zap->pozicija);
	printf("JMBG zaposlenog: %s\n", zap->JMBG);
	printf("Plata zaposlenog: %d", zap->plata);
	printf("\n");
	printf("\n");
}

void citaj_osobu(Zaposleni* zap, FILE* f) { //Citanje svake osobe 
	fscanf(f, "%s %s %s %s %d", zap->ime, zap->prezime, zap->pozicija, zap->JMBG, &zap->plata);
}
Zaposleni* uradi(int* brojac, Zaposleni* niz) { //Popunjavanje Array-a
	*brojac = 0;
	FILE* fp;
	if ((fp = fopen("Baza.txt", "r")) == NULL)
	{
		fprintf(stderr, "Greska pri otvaranju fajla!");
		return 1;
	}
	niz = (Zaposleni*)malloc(sizeof(Zaposleni));
	if (niz == NULL) {
		printf("Greska - nemoguce je alocirati memoriju\n");
	}
	while (!feof(fp)) {
		niz = realloc(niz, (*brojac + 1) * sizeof(Zaposleni));
		if (niz == NULL) {
			printf("greska");
		}
		Zaposleni z1;
		citaj_osobu(&z1, fp);
		niz[*brojac] = z1;
		(*brojac)++;
	}
	fclose(fp);
	return niz;
}
int main()
{
	int brojac = 0;
	Zaposleni* niz;

	int izbor = 1;
	while (izbor != 0) { //Da bi mogli da vrtimo koliko god zelimo
		printf("0 - Kraj Programa\n1 - Ispis\n2 - Upis\n3 - Ispis i delete\n\n");
		scanf("%d", &izbor);
		printf("\n");
		switch (izbor) {
		case 0: //kada je 0 onda ugasi program
			return 0;
			break;
		case 1: //Ispis
			niz = uradi(&brojac, &niz);
			for (int i = 0; i < brojac; i++) {
				getValues(&niz[i]);
			}
			break;
		case 2: //Upis
			printf(""); // Greska u kompajleru
			FILE* fupis;
			fupis = fopen("Baza.txt", "a");
			Zaposleni l2;
			setValuesFajl(&l2, fupis);
			printf("Uspesno ste uneli\n\n");
			fclose(fupis);
			break;
		case 3: //Ispis i delete
			niz = uradi(&brojac, &niz);
			for (int i = 0; i < brojac; i++) {
				getValues(&niz[i]);
			}
			printf("Upisite JMBG koji zelite da obrisete: ");
			char onajJMBG[13];
			scanf("%s", &onajJMBG);
			FILE* fupis2;
			int prvi = 0; //Zbog prvog entera
			int biloga = 0;
			fupis2 = fopen("Baza.txt", "w");
			for (int i = 0; i < brojac; i++) {
				if (strcmp(niz[i].JMBG, onajJMBG) != 0) {
					setValuesFajl2(&niz[i], fupis2, &prvi);
					prvi = 1;
				}
				else {
					biloga = 1;
				}
			}
			fclose(fupis2);
			if (biloga == 1) {
				printf("Uspesno ste obrisali zaposlenog sa JMBG %s\n\n", onajJMBG);
			}
			else {
				printf("Ne postoji\n");
			}
			
			break;
		default: printf("Greska, pokusajte ponovo\n");
		}
	}
	return 0;
}