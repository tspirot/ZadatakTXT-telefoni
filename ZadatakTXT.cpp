#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>

// funkcija koja vraca broj telefona u fajlu sa cenom od-do
int brTel(FILE* pft, float min, float max)
{
	char marka[31], model[31];
	float cena;
	int brt = 0;
	while (!feof(pft))
	{
		fscanf_s(pft, "%s %s %f", marka, 30, model, 30, &cena);
		if (cena > min && cena < max)
			brt++;
	}
	return brt;
}
int main()
{
	FILE* pftelefoni, * pfcene;
	char marka[31], model[31], mar[31];
	float cena, kurs, cenaod, cenado;
	int n, i;
	// 1. UNOS PODATAKA I KREIRANJE telefoni.txt
	fopen_s(&pftelefoni, "telefoni.txt", "w");
	if (pftelefoni == NULL)
	{
		printf("Greska pri kreiranju fajla telefoni.txt");
		_getch();
		return 1;
	}
	printf("Unesi broj telefona:\n");
	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
	{
		printf("Unesi marku telefona:\n");
		scanf_s("%s", marka, 30);
		printf("Unesi model telefona:\n");
		scanf_s("%s", model, 30);
		printf("Unesi cenu telefona (EUR):\n");
		scanf_s("%f", &cena);
		fprintf(pftelefoni, "%s %s %.2f\n", marka, model, cena);
	}
	fclose(pftelefoni);
	// 2 CITANJE PODATAKA IZ telefoni.txt I KREIRANJE cene.txt
	// sa telefonima date marke i cene od-do
	fopen_s(&pftelefoni, "telefoni.txt", "r");
	if (pftelefoni == NULL)
	{
		printf("Greska pri otvaranju fajla telefoni.txt");
		_getch();
		return 1;
	}
	fopen_s(&pfcene, "cene.txt", "w");
	if (pfcene == NULL)
	{
		printf("Greska pri kreiranju fajla cene.txt");
		_getch();
		return 1;
	}
	printf("Kurs EUR-a:\n");
	scanf_s("%f", &kurs);
	printf("Unesi cenu od EUR:\n");
	scanf_s("%f", &cenaod);
	printf("Unesi cenu do EUR:\n");
	scanf_s("%f", &cenado);
	printf("Unesi marku za upis:\n");
	scanf_s("%s", mar, 30);
	while (!feof(pftelefoni))
	{
		if(fscanf_s(pftelefoni, "%s %s %f", marka, 30, model, 30, &cena) == 3)
			if (cena > cenaod && cena < cenado && strstr(marka, mar))
				fprintf(pfcene, "%s %s %.2f\n", marka, model, cena * kurs);
	}
	// 3. Ispis broja telefona u fajlu sa cenom od-do
	fseek(pftelefoni, 0, SEEK_SET);
	printf("Broj tel od %.2f do %.2f je %d\n",
		cenaod, cenado, brTel(pftelefoni, cenaod, cenado));
	fclose(pfcene);
	fclose(pftelefoni);
	return 0;
}