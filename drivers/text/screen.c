#include "screen.h"
#include "string.h"

/**Stocke les attributs de couleurs, clignotements, d'un charactère*/
static uint_8 kAttr=DEFAULT_KATTR;

/**Pointeur vers la mémoire vidéo*/
static volatile uchar *video=(uchar *)VIDEO_MEM;

/**Postion x*/
static int kX=0;
/**Position y*/
static int kY=0;

void cls (void)
 {
    /*for (i = 0; i < COLUMNS * LINES * 2; i++)
        *(video + i) = 0;*/
    memset((void *) video, 0, VIDEO_SIZE);
 }

void scrollup(unsigned int nbLines)
{
	uchar * video_iterator,*tmp;

	for(video_iterator= (uchar *) video; video_iterator<(uchar*)VIDEOLIM ; video_iterator+=2){
			tmp = (uchar*) (video_iterator+nbLines*COLUMNS*2);

			if (tmp<(uchar*)VIDEOLIM) {
				*video_iterator = *tmp;
				*(video_iterator+1) = *(tmp+1);
			}
			else {
				*video_iterator = 0;
				*(video_iterator+1) = DEFAULT_KATTR;
			}
	}

	kY-=nbLines;
	if(kY<0)
		kY=0;
}

void putchar (unsigned char c)
{
	if (c==10) {	/* CR-NL */
		kX=0;
		kY++;
	}
	else if (c==9) {	/* TAB */
		kX += TAB_SIZE - (kX % TAB_SIZE);
	}
	else if (c==13) {	/* CR */
		kX=0;
	}
	else {		/* autres caracteres */
		video = (unsigned char*) ((uchar *) VIDEO_MEM+2*kX+160*kY);
		*video = c;
		*(video+1) = kAttr;

		kX++;
		if(kX>79){
			kX = 0;
			kY++;
		}
	}

	if (kY>24)
		scrollup(kY-24);
}

void setAttribute(char foreground, char background, char overIntensity, char blink)
{
    kAttr = foreground & (overIntensity << 4) & (background << 5) & (blink << 8);
}
