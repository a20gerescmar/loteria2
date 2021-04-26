#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* INTERFACE */

#define HB "\u2500"  //horizontal bar
#define BHB "\u2501" //big horizontal bar
#define VB "\u2502"  //vertical bar
#define BVB "\u2503"  //big vertical bar
#define HVB "\u253C" //Creu
#define LTC "\u250F" //Left Top corner
#define LBC "\u2514" //Left Bottom corner
#define RTC "\u2513" //Right Top corner
#define RBC "\u2518" //Right Bottom corner
#define SEPT "\u2533"
#define SEPB "\u2547"
#define TRBSB "\u2521"
#define TLBSB "\u2529"
#define TRL "\u2534"
#define TRB "\u251C"
#define TBL "\u2524"



/* QUANTITAT NUMEROS */

#define PRIMER 1
#define SEGON 1
#define TERCER 1
#define QUART 2
#define CINQUE 8
#define PREMIS_GRANS PRIMER + SEGON + TERCER + QUART + CINQUE
#define PEDREA 1794
#define PREMIS PREMIS_GRANS + PEDREA
#define NUM_MAX 100000
#define SERIES 172

/* PREMIS */

#define PEDREAS_A_IMPRIMIR 10
#define PREMIS_MAX 12
#define PRIMER_PREMI 20000
#define PRIMER_PREMI_APROXIMACIO 100
#define SEGON_PREMI 6250
#define SEGON_PREMI_APROXIMACIO 62.5
#define TERCER_PREMI 2500
#define TERCER_PREMI_APROXIMACIO 48
#define QUART_PREMI 1000
#define CINQUE_PREMI 300
#define DECENAS 5
#define CENTENES 5
#define PEDREA_PREMI 5
#define REINTEGRO 1

const char* nom[] = {"Vera","Juan Jose","Lidia","Yon","Bautista","Olivia","Ruben","Nayara","Adria","Naia","Laia","Aaron","Nil","Ivan","Yeray","Ismael","Nicolas","Josthyn","Camilo","Gerard"};

struct numeros_premiats
{
	int primer, segon, tercer, quart[QUART], cinque[CINQUE];
	int numeros_amb_premis;
	int premis[PREMIS];
};

struct premi
{
	float import;
	char motiu;
};

struct premis
{
	int quantitat;
	struct premi premis[PREMIS_MAX];
};

/* AMPLIACIO */

struct persona
{
	char nom[10];
  	int numero;
  	float import;
  	struct premis premis;
};

/* HELPERS */

void barra_horitzontal(int tamany);
void barra_horitzontal_taula(int tamany);
void barra_horitzontal_taula_light(int tamany);
void inicialitzar_struct_premis(struct numeros_premiats *numeros_premiats);
void inicialitzar_premis(int boles_premis[PREMIS]);
int menu();
int submenu_veure_premis();
int submenu_comprovar_premis();
void imprimir_premi(char text[12], int numero_premiat);
int demanar_numero();
void imprimir_premis_numero(struct premis premis);

/* FUNCIONS DE LA APLICACIÓ */

void realitzar_sorteig(struct numeros_premiats *numeros_premiats);
int treure_bola_numeros();
int comprovar_posicio_numeros(int num, struct numeros_premiats numeros_premiats);
int treure_bola_premis(int boles_premis[PREMIS], int premis_restants);
void guardar_dades_sorteig(int numero, int premi, struct numeros_premiats *numeros_premiats);
void mostrar_premis(struct numeros_premiats numeros_premiats, int pedreas, int mostrar_grans_premis);
int proxima_pedrea(int *ultima_pedrea, struct numeros_premiats numeros_premiats);
void comprovar_premis_numero(int numero ,struct premis *premis, struct numeros_premiats numeros_premiats);
void comprovar_premis_grans(int numero, struct premis *premis, struct numeros_premiats numeros_premiats);
void comprovar_aproximacions(int numero, struct premis *premis, struct numeros_premiats numeros_premiats);
void comprovar_centena(int numero, struct premis *premis, struct numeros_premiats numeros_premiats);
void comprovar_terminacio(int numero, struct premis *premis, struct numeros_premiats numeros_premiats);
void reintrego(int numero, struct premis *premis,struct numeros_premiats numeros_premiats);

/* AMPLIACIO */

void crear_colla (int num, struct persona colla[20], struct numeros_premiats numeros_premiats);
void mostrar_colla(int num, struct persona colla[20]);
float import_persona();
int num_premis();

int main(void)
{
	int opcio, opcio_submenu, opcio_subsubmenu, numero;
	struct numeros_premiats numeros_premiats;
	struct premis premis;
	struct persona colla[20];
	inicialitzar_struct_premis(&numeros_premiats);
	FILE *sorteig;
	char any[4];
	struct premi premi;


	srand(time(NULL));


	do {
		printf("De quin any vols consultar els premis: ");
		scanf("%d", &opcio);
		if(opcio < 0 || opcio > 9999) {
			printf("Error: Introdueix una data correct\n");
		}
	} while (opcio < 0 || opcio > 9999);

	sprintf(any, "%d", opcio);
	strcat(any, ".dat");
	


	sorteig = fopen(any, "r+b");

	if (sorteig == NULL)
    {
		realitzar_sorteig(&numeros_premiats);
		sorteig = fopen(any, "wb");
		fwrite(&numeros_premiats.premis[numeros_premiats.primer],sizeof(int),1,sorteig);
		fwrite(&numeros_premiats.premis[numeros_premiats.segon],sizeof(int),1,sorteig);
		fclose(sorteig);
    } else {
		while(fread(&numero, sizeof(int), 1, sorteig)) {
			printf ("num = %d", numero);
		}
		fclose(sorteig);
	}
	

	//menu del programa
	do
	{
		opcio = menu();

		switch (opcio)
		{
		case 1:
			do
			{
				opcio_submenu = submenu_veure_premis();
				switch (opcio_submenu)
				{
				case 1:
					mostrar_premis(numeros_premiats, 10, 1);
					break;

				case 2:
					mostrar_premis(numeros_premiats, 0, 1);
					break;

				case 3:
					printf("Quantes pedreas vols veure? ");
					scanf("%d", &opcio_subsubmenu);
					mostrar_premis(numeros_premiats, opcio_subsubmenu, 0);
					break;
				case 0:
					break;
				default:
					printf("La opcio escollida no és correcte\n");
					break;
				}
			} while (opcio_submenu != 0);
			break;
		case 2:
			do
			{
				opcio_submenu = submenu_comprovar_premis();
				switch (opcio_submenu)
				{
				case 1:
					opcio_subsubmenu = demanar_numero();
					comprovar_premis_numero(opcio_subsubmenu, &premis, numeros_premiats);
					imprimir_premis_numero(premis);
					break;

				case 2:
					printf("Quantes persones té la colla? ");
					scanf("%d", &opcio_subsubmenu);
					crear_colla(opcio_subsubmenu, colla, numeros_premiats);
					mostrar_colla(opcio_subsubmenu, colla);
					break;
				case 0:
					break;
				default:
					printf("La opcio escollida no és correcte\n");
					break;
				}
			} while (opcio_submenu != 0);
			break;
		case 0:
			printf("\033[0;91m");
			printf("\n\nPrograma finalitzat!!!\n");
		default:
			break;
		}
	} while (opcio != 0);

	return 1;
}

/* HELPERS */

/*
 * Imprimeix una barra horitzontal de la mida de la variable tamany
 * 
 * @PARAMS: tamany de la barra (enter)
 * 
 * FOR: imprimeix una barra horitzontal
 * FI FOR: quan "i" sigui igual al tamany
 */

void barra_horitzontal(int tamany)
{
	printf("\n");
	for (int i = 0; i < tamany; i++)
		printf("%s", HB);
	printf("\n");
}

/*
 * Imprimeix una barra horitzontal de la mida de la variable tamany sense salts de linia
 * 
 * @PARAMS: tamany de la barra (enter)
 * 
 * FOR: imprimeix una barra horitzontal
 * FI FOR: quan "i" sigui igual al tamany
 */

void barra_horitzontal_taula(int tamany)
{
	for (int i = 0; i < tamany; i++)
		printf("%s", BHB);
}

/*
 * Imprimeix una barra horitzontal de la mida de la variable tamany sense salt de linia i linia prima
 * 
 * @PARAMS: tamany de la barra (enter)
 * 
 * FOR: imprimeix una barra horitzontal
 * FI FOR: quan "i" sigui igual al tamany
 */

void barra_horitzontal_taula_light(int tamany)
{
	for (int i = 0; i < tamany; i++)
		printf("%s", HB);
}

/*
 * Inicialitza els valors del struct numeros_premiats
 * 
 * @PARAMS: un punter de l'struct numeros premiats, per poder fer canvis
 */

void inicialitzar_struct_premis(struct numeros_premiats *numeros_premiats)
{
	numeros_premiats->numeros_amb_premis = 0;
}

/*
 * Posa les pilotes al bombo de premis
 * 
 * @PARAMS: un vector on es guardaran els premis
 */

void inicialitzar_premis(int boles_premis[PREMIS])
{
	for (int i = 0; i < PREMIS; i++)
		boles_premis[i] = i;
}

/*
 * Mostra el menu per pantalla
 * 
 * @RETURN: retorna la opcio escollida 
 */

int menu()
{
	int opcio;
	printf("\n\n    MENU");
	barra_horitzontal(12);
	printf("1. Veure premis\n");
	printf("2. Comprovar números\n");
	printf("0. Sortir\n\n");
	printf("Quina opció vols? ");
	scanf("%d", &opcio);
	return opcio;
}

/*
 * Mostra el submenumenu de veure premis per pantalla
 * 
 * @RETURN: retorna la opcio escollida 
 */

int submenu_veure_premis()
{
	int opcio;
	printf("\n\nVeure premis");
	barra_horitzontal(12);
	printf("1. Veure els grans premis i les primeres 10 pedreas\n");
	printf("2. Veure només els grans premis\n");
	printf("3. Veure només pedreas\n");
	printf("0. Tornar\n\n");
	printf("Quina opció vols? ");
	scanf("%d", &opcio);
	return opcio;
}

/*
 * Mostra el submenumenu de comprovar premis per pantalla
 * 
 * @RETURN: retorna la opcio escollida 
 */

int submenu_comprovar_premis() 
{
	int opcio;
	printf("\n\nComprovar números");
	barra_horitzontal(12);
	printf("1. Comprovar si un número ha estat premiat\n");
	printf("2. Comprovar els premis d'una colla\n");
	printf("3. Veure els premis acabats en un numero\n");
	printf("0. Tornar\n\n");
	printf("Quina opció vols? ");
	scanf("%d", &opcio);
	return opcio;
}

/*
 * Imprimeix el premi amb el nom d'aquest
 * 
 * @PARAMS: una cadena de caràcters (on esta el nom del premi) i un enter (amb el numero premiat)
 */

void imprimir_premi(char text[14], int numero_premiat)
{
	printf("%-14s -  %05d \n", text, numero_premiat);
}

/*
 * Demana al usuari que introdueixi un numero
 * 
 * @RETURN: el numero introduit per l'usuari
 */

int demanar_numero()
{
	int num;
	printf("Introdueix número a buscar: ");
	scanf("%d", &num);
	return num;
}

/*
 * Donat el registre de premis els mostra per pantalla
 * 
 * @PARAMS: registre de premis
 */

void imprimir_premis_numero(struct premis premis)
{
	float total = 0;
	if(premis.quantitat == 0) {
		printf("Aquest numero no ha estat premiat");
		return;
	}
		
	for(int i = 0; i < premis.quantitat; i++) {
		total += premis.premis[i].import;
		printf("\n  %.2f - %c", premis.premis[i].import, premis.premis[i].motiu);
	}
	printf("El total és: %f", total);
	
}

/* FUNCIONS DE LA APLICACIÓ */

/*
 * Realitza el sorteig
 * 
 * @PARAMS: el registre dels numeros premiats, per poder fer canvis
 * 
 * WHILE: quedin boles al bombo dels premis, 
 * 	treiem un numero del bombo de numeros,
 * 	treiem un numero del bombo de premis,
 * 	guardem els numeros i els premis,
 * END WHILE: quan no quedin boles al bombo de premis
 */

void realitzar_sorteig(struct numeros_premiats *numeros_premiats)
{
	int boles_premis[PREMIS], premis_restants, numero, premi;
	inicialitzar_premis(boles_premis);

	premis_restants = PREMIS;

	while (premis_restants)
	{

		numero = treure_bola_numeros(*numeros_premiats);
		premi = treure_bola_premis(boles_premis, premis_restants);
		guardar_dades_sorteig(numero, premi, numeros_premiats);
		premis_restants--;
	}
}

/*
 * Treu una pilota del bombo dels numeros que no hagi sortit
 *
 * @PARAMS: el registre dels numeros premiats (per comprovar si el numero ja han sortit)
 * 
 * WHILE: agafar un numero nou sempre que ja hagi sortit
 * END WHILE: quan el numero sortint no esta repetit 
 * 
 * @RETURN: retorna el numero sortint (no repetit)
 */

int treure_bola_numeros(struct numeros_premiats numeros_premiats)
{

	int num_bola = 0;

	do
	{
		num_bola = rand() % NUM_MAX;
	} while (comprovar_posicio_numeros(num_bola, numeros_premiats));

	return num_bola;
}

/*
 * Comprova si un numero ja esta premiat
 *
 * @PARAMS: el registre dels numeros premiats i el numero a comprovar
 * 
 * FOR: recorre els numeros que han sortit
 * 	IF: si el numero a buscar es el numero de la posicio "i" dels numeros ja premiats retornem 1
 * END FOR: al acabar de recorrer el vector de numeros premiats 
 * 
 * @RETURN: 1 si esta repetit i 0 si no ho esta
 */

int comprovar_posicio_numeros(int num, struct numeros_premiats numeros_premiats)
{
	for (int i = 0; i < numeros_premiats.numeros_amb_premis; i++)
	{
		if (num == numeros_premiats.premis[i])
			return 1;
	}

	return 0;
}

/*
 * Treu una pilota del bombo dels premis
 *
 * @PARAMS: un vector amb les boles del bombo dels premis, i la quantitat de boles que restan per sortir
 * 
 * quan es treu una bola es canvia de posicio per la de premis restants -1
 * 
 * @RETURN: retorna el numero sortint
 */

int treure_bola_premis(int boles_premis[PREMIS], int premis_restants)
{
	int numero, premi;
	numero = rand() % premis_restants;
	premi = boles_premis[numero];
	boles_premis[numero] = boles_premis[premis_restants - 1];
	boles_premis[premis_restants - 1] = premi;
	return premi;
}

/*
 * 	Guarda les dades del sorteig, la bola dels numeros amb la bola dels premis,
 * 		si es un gran premi tambe guarda la posicio en el gran premi corresponent
 * 
 * 	@PARAMS: numero que ha sortit de bombo dels numeros, premi que ha sortit del bombo dels premis, i el registre amb els numeros premiats
 * 
 * 	IF: si el premi es un gran premi es va a buscar quin gran premi es
 * 		IF: si es primer premi es guarda la posicio en PRIMER PREMI
 * 		IF: si es segon premi es guarda la posicio en SEGON PREMI
 * 		IF: si es tercer premi es guarda la posicio en TERCER PREMI
 * 		IF: si es un quart premi es guarda la posicio en la posicio corresponent del vector QUART PREMI
 * 		IF: si es un cinque premi es guarda la posicio en la posicio corresponent del vector CINQUE PREMI
 */

void guardar_dades_sorteig(int numero, int premi, struct numeros_premiats *numeros_premiats)
{
	numeros_premiats->premis[numeros_premiats->numeros_amb_premis] = numero;
	if (premi < PREMIS_GRANS)
	{
		if (premi < PRIMER)
			numeros_premiats->primer = numeros_premiats->numeros_amb_premis;
		else if (premi < PRIMER + SEGON)
			numeros_premiats->segon = numeros_premiats->numeros_amb_premis;
		else if (premi < PRIMER + SEGON + TERCER)
			numeros_premiats->tercer = numeros_premiats->numeros_amb_premis;
		else if (premi < PRIMER + SEGON + TERCER + QUART)
			numeros_premiats->quart[premi - (PRIMER + SEGON + TERCER)] = numeros_premiats->numeros_amb_premis;
		else if (premi < PRIMER + SEGON + TERCER + QUART + CINQUE)
			numeros_premiats->cinque[premi - (PRIMER + SEGON + TERCER + QUART)] = numeros_premiats->numeros_amb_premis;
	}
	numeros_premiats->numeros_amb_premis++;
}

/*
 * 	Donat els numeros premiats t'imprimeix els premis grans i les primeres PEDREAS_A_IMPRIMIR
 * 
 * 	@PARAMS: el registre amb els numeros premiats
 * 
 * 	FOR: recorre el vector de dels quarts premis per imprimir els quarts premis
 * 	FOR: recorre el vector de dels cinquens premis per imprimir els cinquens premis
 * 	FOR: recorre les primeres PEDREAS_A_IMPRIMIR i les imprimeix
 */

void mostrar_premis(struct numeros_premiats numeros_premiats, int pedreas, int mostrar_grans_premis)
{
	int ultima_pedrea = 0;
	printf("\n\nNÚMEROS PREMIATS: ");
	barra_horitzontal(20);
	if (mostrar_grans_premis)
	{
		imprimir_premi("PRIMER PREMI", numeros_premiats.premis[numeros_premiats.primer]);
		imprimir_premi("SEGON PREMI", numeros_premiats.premis[numeros_premiats.segon]);
		imprimir_premi("TERCER PREMI", numeros_premiats.premis[numeros_premiats.tercer]);
		for (int i = 0; i < QUART; i++)
			imprimir_premi("QUART PREMI", numeros_premiats.premis[numeros_premiats.quart[i]]);
		for (int i = 0; i < CINQUE; i++)
			imprimir_premi("CINQUE PREMI", numeros_premiats.premis[numeros_premiats.cinque[i]]);
	}
	for (int i = 0; i < pedreas && i < PEDREA-1; i++)
	{
		imprimir_premi("PEDREA", proxima_pedrea(&ultima_pedrea, numeros_premiats));
		ultima_pedrea++;
	}
}

/*
 * Diu el següent número premiat, que no sigui cap dels grans premis
 * 
 * @PARAMS: un punter amb la posicio a comprovar i l'struct dels numeros premiats
 * 
 * RECURSIVA: es crida a ella mateixa canviant la posicio a comprovar
 * FI RECURSIVITAT: el numero de la posició no sigui un gran premi
 * 
 * PRIMER IF: comprova si la posicio a comprovar es la del primer segon o tercer numero
 * 
 * PRIMER FOR: recorre el vector de les posicions dels quarts premis
 * 	SEGON IF: comprova si la posicio a comprovar es la posicio del quart premi en la posicio "i" del vector
 * FI PRIMER FOR: quan "i" es igual a QUART(que es 2)
 * 
 * SEGON FOR: recorre el vector de les posicions dels cinquens premis
 * 	TERCER IF: comprova si la posicio a comprovar es la posicio del cinque premi en la posicio "i" del vector
 * FI SEGON FOR: quan "i" es igual a CINQUE(que es 8)
 *
 * @RETURN: quan acaba la recursivitat retorna la proxima pedrea del vector de numeros_premiats.premis 
 */

int proxima_pedrea(int *ultima_pedrea, struct numeros_premiats numeros_premiats)
{
	if (*ultima_pedrea == numeros_premiats.primer || *ultima_pedrea == numeros_premiats.segon || *ultima_pedrea == numeros_premiats.tercer)
	{
		*ultima_pedrea = *ultima_pedrea + 1;
		return proxima_pedrea(ultima_pedrea, numeros_premiats);
	}
	for (int i = 0; i < QUART; i++)
	{
		if (*ultima_pedrea == numeros_premiats.quart[i])
		{
			*ultima_pedrea = *ultima_pedrea + 1;
			return proxima_pedrea(ultima_pedrea, numeros_premiats);
		}
	}
	for (int i = 0; i < CINQUE; i++)
	{
		if (*ultima_pedrea == numeros_premiats.cinque[i])
		{
			*ultima_pedrea = *ultima_pedrea + 1;
			return proxima_pedrea(ultima_pedrea, numeros_premiats);
		}
	}
	return numeros_premiats.premis[*ultima_pedrea];
}

/*
 * A partir d'un numero comprovar tots els premis que poden tenir
 * 
 * @PARAMS: numero a buscar, registre amb els premis, i registre amb els numeros premiats
 */

void comprovar_premis_numero(int numero ,struct premis *premis, struct numeros_premiats numeros_premiats) 
{
	comprovar_premis_grans(numero, premis, numeros_premiats);
	comprovar_aproximacions(numero, premis, numeros_premiats);
	comprovar_centena(numero, premis, numeros_premiats);
	comprovar_terminacio (numero, premis, numeros_premiats);
	reintrego(numero,premis,numeros_premiats);
}

/*
 * Donat un numero comprova si coincideix amb algun premi amb els numeros premiats de forma directa
 * 
 * @PARAMS: numero a buscar, registre amb els premis, i registre amb els numeros premiats
 */

void comprovar_premis_grans(int numero, struct premis *premis, struct numeros_premiats numeros_premiats)
{

	int ultima_pedrea = 0;

	if (numero == numeros_premiats.premis[numeros_premiats.primer])
	{

		premis->premis[0].import = PRIMER_PREMI;
		premis->premis[0].motiu = '1';

		premis->quantitat = 1;

		return;
	}

	if (numero == numeros_premiats.premis[numeros_premiats.segon])
	{

		premis->premis[0].import = SEGON_PREMI;
		premis->premis[0].motiu = '2';

		premis->quantitat = 1;

		return;
	}

	if (numero == numeros_premiats.premis[numeros_premiats.tercer])
	{
		premis->premis[0].import = TERCER_PREMI;
		premis->premis[0].motiu = '3';

		premis->quantitat = 1;

		return;
	}

	for (int i = 0; i < QUART; i++)
	{
		if (numero == numeros_premiats.premis[numeros_premiats.quart[i]])
		{
			premis->premis[0].import = QUART_PREMI;
			premis->premis[0].motiu = '4';

			premis->quantitat = 1;

			return;
		}
	}

	for (int i = 0; i < CINQUE; i++)
	{
		if (numero == numeros_premiats.premis[numeros_premiats.cinque[i]])
		{
			premis->premis[0].import = CINQUE_PREMI;
			premis->premis[0].motiu = '5';

			premis->quantitat = 1;

			return;
		}
	}

	for (int i = 0; i < PEDREA; i++)
	{
		if (numero == proxima_pedrea(&ultima_pedrea, numeros_premiats))
		{
			premis->premis[0].import = PEDREA_PREMI;
			premis->premis[0].motiu = 'p';

			premis->quantitat = 1;

			return;
		}
		ultima_pedrea++;
	}

	premis->quantitat = 0;

	return;
}

/*
 * Si donat un numero es el anterior o el seguent al primer, segon o tercer premi:
 * 
 * @PARAMS: Numero a buscar, el registre de premis i el registre de numeros premiats
 * 
 * PRIMER IF: Es el seguent o anterior al primer premi es suma el premi
 * SEGON IF: Es el seguent o anterior al segon premi es suma el premi
 * TERCER IF: Es el seguent o anterior al tercer premi es suma el premi
*/

void comprovar_aproximacions(int numero, struct premis *premis, struct numeros_premiats numeros_premiats)
{

	if (numero == (numeros_premiats.premis[numeros_premiats.primer] + 1) || numero == (numeros_premiats.premis[numeros_premiats.primer] - 1))
	{
		premis->premis[premis->quantitat].import = PRIMER_PREMI_APROXIMACIO;
		premis->premis[premis->quantitat].motiu = 'a';
		premis->quantitat = premis->quantitat + 1;
	}

	if (numero == (numeros_premiats.premis[numeros_premiats.segon] + 1) || numero == (numeros_premiats.premis[numeros_premiats.segon] - 1))
	{
		premis->premis[premis->quantitat].import = SEGON_PREMI_APROXIMACIO;
		premis->premis[premis->quantitat].motiu = 'a';
		premis->quantitat = premis->quantitat + 1;
	}

	if (numero == (numeros_premiats.premis[numeros_premiats.tercer] + 1) || numero == (numeros_premiats.premis[numeros_premiats.tercer] - 1))
	{
		premis->premis[premis->quantitat].import = TERCER_PREMI_APROXIMACIO;
		premis->premis[premis->quantitat].motiu = 'a';
		premis->quantitat = premis->quantitat + 1;
	}
}

/*
 * Donat un numero, i els numeros premiats diu si les centenes del coincideixen amb les centenes del primer, segon, terer, i quarts premis
 * 
 * @PARAMS: numero a buscar, el registre de premis, i el registre de numeros premiats
 */

void comprovar_centena(int numero, struct premis *premis, struct numeros_premiats numeros_premiats)
{
	int centena = numero / 100;
	if(premis->quantitat == 0 || (premis->quantitat>0 && premis->premis[0].motiu != '1'))
	{
		if (centena == (numeros_premiats.premis[numeros_premiats.primer] / 100))
		{
			premis->premis[premis->quantitat].import = CENTENES;
			premis->premis[premis->quantitat].motiu = 'c';
			premis->quantitat = premis->quantitat + 1;
		}
	}
	if(premis->quantitat == 0 || (premis->quantitat>0 && premis->premis[0].motiu != '2'))
	{
		if (centena == (numeros_premiats.premis[numeros_premiats.segon] / 100))
		{
			premis->premis[premis->quantitat].import = CENTENES;
			premis->premis[premis->quantitat].motiu = 'c';
			premis->quantitat = premis->quantitat + 1;
		}
	}
	if(premis->quantitat == 0 || (premis->quantitat>0 && premis->premis[0].motiu != '3'))
	{
		if (centena == (numeros_premiats.premis[numeros_premiats.tercer] / 100))
		{
			premis->premis[premis->quantitat].import = CENTENES;
			premis->premis[premis->quantitat].motiu = 'c';
			premis->quantitat = premis->quantitat + 1;
		}
	}
	if(premis->quantitat == 0 || (premis->quantitat>0 && premis->premis[0].motiu != '4'))
	{
		for (int i = 0; i < QUART; i++)
		{
			if (centena == (numeros_premiats.premis[numeros_premiats.quart[i]] / 100))
			{
				premis->premis[premis->quantitat].import = CENTENES;
				premis->premis[premis->quantitat].motiu = 'c';
				premis->quantitat = premis->quantitat + 1;
			}
		}
	}
}

/*
 * Donat un numero, i els numeros premiats diu si les dos ultimes xifres coincideixen amb les dos ultimes xifres del primer, segon i/o terer
 * 
 * @PARAMS: numero a buscar, el registre de premis, i el registre de numeros premiats
 */

void comprovar_terminacio (int numero, struct premis *premis, struct numeros_premiats numeros_premiats)
{
	int terminacio = numero % 100;
	if (premis->quantitat == 0 || (premis->quantitat > 0 && premis->premis[0].motiu != '1'))
	{
		if (terminacio == (numeros_premiats.premis[numeros_premiats.primer] % 100))
		{
			premis->premis[premis->quantitat].import = DECENAS;
			premis->premis[premis->quantitat].motiu = 't';
			premis->quantitat = premis->quantitat + 1;
		}
	}
	if (premis->quantitat == 0 || (premis->quantitat > 0 && premis->premis[0].motiu != '2'))
	{
		if (terminacio == (numeros_premiats.premis[numeros_premiats.segon] % 100))
		{
			premis->premis[premis->quantitat].import = DECENAS;
			premis->premis[premis->quantitat].motiu = 't';
			premis->quantitat = premis->quantitat + 1;
		}
	}
	if (premis->quantitat == 0 || (premis->quantitat > 0 && premis->premis[0].motiu != '3'))
	{
		if (terminacio == (numeros_premiats.premis[numeros_premiats.tercer] % 100))
		{
			premis->premis[premis->quantitat].import = DECENAS;
			premis->premis[premis->quantitat].motiu = 't';
			premis->quantitat = premis->quantitat + 1;
		}
	}
}

/*
 * Donat un numero, i els numeros premiats diu si la ultima xifra coincideix amb la ultima xifra del primer, segon i/o terer
 * 
 * @PARAMS: numero a buscar, el registre de premis, i el registre de numeros premiats
 */

void reintrego(int numero, struct premis *premis,struct numeros_premiats numeros_premiats) {
	
	
	int num_reintegro = numero % 10;
	
	if(premis->quantitat == 0 || (premis->quantitat > 0 && premis->premis[0].motiu != '1')) {
		if(num_reintegro == (numeros_premiats.premis[numeros_premiats.primer] % 10)) {
			premis->premis[premis->quantitat].import = REINTEGRO;
			premis->premis[premis->quantitat].motiu = 'r';
			premis->quantitat = premis->quantitat + 1;
		}
	}
}

/* AMPLIACIO */

/*
 * Genera una colla del tamany assignat, i comprova si te premi
 * 
 * @PARAMS: numero de persones a la colla, el registre de la colla, i el registre de numeros premiats
 */

void crear_colla (int num, struct persona colla[20], struct numeros_premiats numeros_premiats)
{
  	int pos_array[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}, pos, tmp;
  	
	for (int i = 0; i < num; i++) {
      	pos = rand()%(20-i);
		strcpy(colla[i].nom, nom[pos_array[pos]]);
      	tmp = pos_array[pos];
      	pos_array[pos] = pos_array[20-i-1];
      	pos_array[20-i-1] = tmp;
      	colla[i].numero = num_premis();
        colla[i].import = import_persona();
		comprovar_premis_numero(colla[i].numero ,&colla[i].premis, numeros_premiats);
    }
}

/*
 * Retrona un numero aleatori entre 5 i 60 sempre multiple de 5
 * 
 * @RETURN: l'import que juga la persona
 */

float import_persona() 
{
	float num_import;
	num_import= ((rand() % 12)+1)*5.0;  
	return num_import;
}

/*
 * Retrona un numero aleatori entre 0 i 99999
 * 
 * @RETURN: numero amb que juga la persona
 */

int num_premis() {

	int num_premi = 0;
  	num_premi= rand() % 100000;
  	return num_premi;
}

/*
 * Imprimeix per pantalla la colla, en forma de taula 
 * 
 * @PARAMS: numero de persones que comprenen la colla, i el registre de la colla
 */

void mostrar_colla(int num, struct persona colla[20]) 
{
	float premi_total = 0, premi_ind[20], diners_total = 0, participacio;
	for(int i = 0; i < num; i++) {
		premi_ind[i] = 0;
		for(int y = 0; y < colla[i].premis.quantitat; y++) {
			premi_ind[i] += colla[i].premis.premis[y].import * colla[i].import;
		}
		premi_total += premi_ind[i];
		diners_total += colla[i].import;
    }
    participacio = premi_total / diners_total;
    
    printf("%s",LTC);
    barra_horitzontal_taula(19);
	printf("%s",SEPT);
	barra_horitzontal_taula(9);
	printf("%s",SEPT);
	barra_horitzontal_taula(14);
	printf("%s",SEPT);
	barra_horitzontal_taula(17);
	printf("%s",SEPT);
	barra_horitzontal_taula(13);
	printf("%s",RTC);

    printf("\n%s        ANY        %s MEMBRES %s    DINERS    %s      PREMI      %s DISTRIBUCIO %s\n", BVB, BVB, BVB, BVB, BVB, BVB);
	
	printf("%s",TRBSB);
    barra_horitzontal_taula(19);
	printf("%s",SEPB);
	barra_horitzontal_taula(9);
	printf("%s",SEPB);
	barra_horitzontal_taula(14);
	printf("%s",SEPB);
	barra_horitzontal_taula(17);
	printf("%s",SEPB);
	barra_horitzontal_taula(13);
	printf("%s",TLBSB);
	
	printf("\n%s              2021 %s      %2d %s       %6.2f %s     %11.2f %s      %6.2f %s\n", VB, VB, num, VB, diners_total, VB, premi_total, VB, participacio, VB);

	printf("%s",LBC);
    barra_horitzontal_taula_light(19);
	printf("%s",TRL);
	barra_horitzontal_taula_light(9);
	printf("%s",TRL);
	barra_horitzontal_taula_light(14);
	printf("%s",TRL);
	barra_horitzontal_taula_light(17);
	printf("%s",TRL);
	barra_horitzontal_taula_light(13);
	printf("%s",RBC);

	printf("\n\n");
	
	printf("%s",LTC);
    barra_horitzontal_taula(19);
	printf("%s",SEPT);
	barra_horitzontal_taula(9);
	printf("%s",SEPT);
	barra_horitzontal_taula(14);
	printf("%s",SEPT);
	barra_horitzontal_taula(17);
	printf("%s",SEPT);
	barra_horitzontal_taula(13);
	printf("%s",RTC);

    printf("\n%s        NOM        %s MEMBRES %s    DINERS    %s      PREMI      %s DISTRIBUCIO %s\n", BVB, BVB, BVB, BVB, BVB, BVB);
	
	printf("%s",TRBSB);
    barra_horitzontal_taula(19);
	printf("%s",SEPB);
	barra_horitzontal_taula(9);
	printf("%s",SEPB);
	barra_horitzontal_taula(14);
	printf("%s",SEPB);
	barra_horitzontal_taula(17);
	printf("%s",SEPB);
	barra_horitzontal_taula(13);
	printf("%s",TLBSB);
	
	for(int i = 0; i < num; i++) {
		if(i != 0) {
			printf("%s",TRB);
			barra_horitzontal_taula_light(19);
			printf("%s",HVB);
			barra_horitzontal_taula_light(9);
			printf("%s",HVB);
			barra_horitzontal_taula_light(14);
			printf("%s",HVB);
			barra_horitzontal_taula_light(17);
			printf("%s",HVB);
			barra_horitzontal_taula_light(13);
			printf("%s",TBL);

		}
		printf("\n%s %-9s         %s   %5d %s       %6.2f %s     %11.2f %s      %6.2f %s\n", VB, colla[i].nom, VB, colla[i].numero, VB, colla[i].import, VB, premi_ind[i], VB, participacio*colla[i].import, VB);
	}
	printf("%s",LBC);
	barra_horitzontal_taula_light(19);
	printf("%s",TRL);
	barra_horitzontal_taula_light(9);
	printf("%s",TRL);
	barra_horitzontal_taula_light(14);
	printf("%s",TRL);
	barra_horitzontal_taula_light(17);
	printf("%s",TRL);
	barra_horitzontal_taula_light(13);
	printf("%s",RBC);
}
