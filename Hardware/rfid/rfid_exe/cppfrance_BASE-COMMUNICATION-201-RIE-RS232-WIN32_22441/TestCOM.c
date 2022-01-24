/******************************************************************************
  TestCOM.c :
  
   fonctions de base pour l'envoi et la r�ception de donner sur un port
   s�rie RS232.
******************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*=============================================================================
  D�finition de constantes
=============================================================================*/
#define RX_SIZE         4096    /* taille tampon d'entr�e  */
#define TX_SIZE         4096    /* taille tampon de sortie */
#define MAX_WAIT_READ   30    /* temps max d'attente pour lecture (en ms) */
#define MAX_BOUCLE		150   // 30 * 150 = 4500 ms = 4.5 sec


/*=============================================================================
  Variables globales.
=============================================================================*/

/* Handle du port COM ouvert */
HANDLE g_hCOM = NULL;
LPWORD g_hCOM2 = NULL;

/* D�lais d'attente sur le port COM */
COMMTIMEOUTS g_cto =
{
    MAX_WAIT_READ,  /* ReadIntervalTimeOut          */
    0,              /* ReadTotalTimeOutMultiplier   */
    MAX_WAIT_READ,  /* ReadTotalTimeOutConstant     */
    0,              /* WriteTotalTimeOutMultiplier  */
    0               /* WriteTotalTimeOutConstant    */
};

/* Configuration du port COM */
DCB g_dcb =
{
    sizeof(DCB),        /* DCBlength            */
    115200,               /* BaudRate             */
    TRUE,               /* fBinary              */
    FALSE,              /* fParity              */
    FALSE,              /* fOutxCtsFlow         */
    FALSE,              /* fOutxDsrFlow         */
    DTR_CONTROL_DISABLE, /* fDtrControl          */
    FALSE,              /* fDsrSensitivity      */
    FALSE,              /* fTXContinueOnXoff    */
    FALSE,              /* fOutX                */
    FALSE,              /* fInX                 */
    FALSE,              /* fErrorChar           */
    FALSE,              /* fNull                */
    RTS_CONTROL_DISABLE, /* fRtsControl          */
    FALSE,              /* fAbortOnError        */
    0,                  /* fDummy2              */
    0,                  /* wReserved            */
    0x100,              /* XonLim               */
    0x100,              /* XoffLim              */
    8,                  /* ByteSize             */
    NOPARITY,           /* Parity               */
    ONESTOPBIT,         /* StopBits             */
    0x11,               /* XonChar              */
    0x13,               /* XoffChar             */
    '?',                /* ErrorChar            */
    0x1A,               /* EofChar              */
    0x10                /* EvtChar              */
};

/*=============================================================================
  Fonctions du module.
=============================================================================*/
BOOL OpenCOM    (int nId);
BOOL CloseCOM   ();
BOOL ReadCOM    (void* buffer, int nBytesToRead, int* pBytesRead);
BOOL WriteCOM   (void* buffer, int nBytesToWrite, int* pBytesWritten);

/******************************************************************************
  main : point d'entr�e du programme.
******************************************************************************/
int main(int argc, char** argv)
{
    /* variables locales */
    char buffer[256];
    int nId, nChoice, nBytesWritten, nBytesRead;
	BOOL isRead;
	int i;

	if(argc != 2) {
		printf("ERROR NO PORT\n");
		return 0;
	}

	// On attribue le port
	nId = atoi(argv[1]);

    /* tentative d'ouverture */
    //printf("Ouverture et configuration du port COM%d...\r\n", nId);
	if(!OpenCOM(nId)) {
		return 0;
	}

	i=0;
	do
	{
		isRead = FALSE;
		if(ReadCOM(buffer, sizeof(buffer)-1, &nBytesRead)) {
			buffer[nBytesRead] = '\0';
			if(nBytesRead == 63) {
				if(
					buffer[ 0] == 'L' &&
					buffer[ 1] == '1' &&
					buffer[21] == 'L' &&
					buffer[22] == '2' &&					
					buffer[42] == 'L' &&
					buffer[43] == '3')
					isRead = TRUE;
			}
		}
		i++;
	}while(!isRead && i < MAX_BOUCLE);

	if(i == MAX_BOUCLE) printf("TIMEOUT\n");
	else printf("%s", buffer);

    CloseCOM();

    return 0;
}

/******************************************************************************
  OpenCOM : ouverture et configuration du port COM.
  entr�e : nId : Id du port COM � ouvrir.
  retour : vrai si l'op�ration a r�ussi, faux sinon.
******************************************************************************/
BOOL OpenCOM(int nId)
{
    /* variables locales */
    char szCOM[16];

    /* construction du nom du port, tentative d'ouverture */
    sprintf(szCOM, "COM%d", nId);
    g_hCOM = CreateFile(szCOM, GENERIC_READ|GENERIC_WRITE, 0, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
	g_hCOM2 = g_hCOM;
    if(g_hCOM == INVALID_HANDLE_VALUE)
    {
        printf("CAN T OPEN PORT\n", nId);
        return FALSE;
    }

    /* affectation taille des tampons d'�mission et de r�ception */
    SetupComm(g_hCOM, RX_SIZE, TX_SIZE);

    /* configuration du port COM */
    if(!SetCommTimeouts(g_hCOM, &g_cto) || !SetCommState(g_hCOM, &g_dcb))
    {
        printf("CAN T CONFIG PORT\n", nId);
        CloseHandle(g_hCOM);
        return FALSE;
    }

    /* on vide les tampons d'�mission et de r�ception, mise � 1 DTR */
    PurgeComm(g_hCOM, PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT);
    EscapeCommFunction(g_hCOM, SETDTR);
    return TRUE;
}

/******************************************************************************
  CloseCOM : fermeture du port COM.
  retour : vrai si l'op�ration a r�ussi, faux sinon.
******************************************************************************/
BOOL CloseCOM()
{
    /* fermeture du port COM */
    CloseHandle(g_hCOM);
    return TRUE;
}

/******************************************************************************
  ReadCOM : lecture de donn�es sur le port COM.
  entr�e : buffer       : buffer o� mettre les donn�es lues.
           nBytesToRead : nombre max d'octets � lire.
           pBytesRead   : variable qui va recevoir le nombre d'octets lus.
  retour : vrai si l'op�ration a r�ussi, faux sinon.
-------------------------------------------------------------------------------
  Remarques : - la constante MAX_WAIT_READ utilis�e dans la structure
                COMMTIMEOUTS permet de limiter le temps d'attente si aucun
                caract�res n'est pr�sent dans le tampon d'entr�e.
              - la fonction peut donc retourner vrai sans avoir lu de donn�es.
******************************************************************************/
BOOL ReadCOM(void* buffer, int nBytesToRead, int* pBytesRead)
{
    return ReadFile(g_hCOM2, buffer, nBytesToRead, pBytesRead, NULL);
}

/******************************************************************************
  WriteCOM : envoi de donn�es sur le port COM.
  entr�e : buffer        : buffer avec les donn�es � envoyer.
           nBytesToWrite : nombre d'octets � envoyer.
           pBytesWritten : variable qui va recevoir le nombre d'octets
                           envoy�s.
  retour : vrai si l'op�ration a r�ussi, faux sinon.
******************************************************************************/
BOOL WriteCOM(void* buffer, int nBytesToWrite, int* pBytesWritten)
{
    /* �criture sur le port */
    return WriteFile(g_hCOM2, buffer, nBytesToWrite, pBytesWritten, NULL);
}