#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SDL.h"
#include "SDL_image.h"
#include "mirage_sdl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>


#define PI 3.14159265

int main(int argc, char** argv)
{
  //========================= FIELDS ===================================
  SDL_Surface* affichage, *top;
  SDL_Event event;
  SDL_Rect position;
  int continuer, choice, num, i, max;
  Uint32 color, color2;
  int state1,state2;
  int x1,x2,y1,y2;
  int r1,r2,g1,g2,b1,b2;

  //===================== INITIALISATION ===============================
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  atexit(SDL_Quit);
  affichage = SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE);
  SDL_FillRect(affichage, NULL, SDL_MapRGB(affichage->format, 255, 255, 255));
  if (affichage == NULL) 
  {
    fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption("Mirage", NULL);
  mkdir("tmp", S_IRWXU);


  //====================== AFFECTATION ================================
  i=max=0;
  char filename[100];
  top =  SDL_CreateRGBSurface(SDL_HWSURFACE, 1024, 768, 32, 0, 0, 0, 0);
  SDL_FillRect(top, NULL, SDL_MapRGB(top->format, 255, 255, 255));
  //SDL_FillRect(affichage, NULL, SDL_MapRGBA(affichage->format, 255, 255, 255,128));
  position.x = 0;
  position.y = 0;
  continuer=1, choice=0, num=6;
  color=ColorFromRGB(0,0,0,top);
  x1=0,x2=0,y1=0,y2=0;
  r1=0,r2=0,g1=0,g2=0,b1=0,b2=0;
  state1=0,state2=0;

  //======================= LOAD_IMAGE ================================
  if(argc>1)
  {
    printf("input image : %s\n", argv[1]);
    top =  IMG_Load(argv[1]);
  }
  if(argc>2)
  {
    printf("output image : %s\n", argv[2]);
  }
  SDL_SaveBMP(top, "tmp/top0.bmp");
  Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2,&color, &color2, top);
  //========================== BOUCLE =================================
	

 
  while (continuer)
  {
    // #####-> READ_STATE
    if(SDL_GetMouseState(&x2, &y2)&SDL_BUTTON(1)) //press
    {
      state2=1;
      if(!choice&&x2>50)
      {
        Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2,&color, &color2, top);
        FillCircle(x2,y2,num,color,top);
        SDL_BlitSurface(top, NULL, affichage, &position);
      }
    }
    if(!SDL_GetMouseState(&x2, &y2)&SDL_BUTTON(1)) //release
    {
      state2=0;
    }

    // #####-> HANDLE_STATE
    if(!state1&&state2) //clik
    {
      Read_tool(&choice,&num,&r1,&g1,&b1,&r2,&g2,&b2,&color, &color2, top);
      x1=x2;y1=y2;
      //printf("clik : %i %i\n",x1,y1);
    }
    
    if(!state1&&!state2) //released
    {

    }
    if(state1&&state2&&choice) //pressed
    {
      // ##### -> ON_DRAWING
      if(i>=0)
      {
        top =  SDL_CreateRGBSurface(SDL_HWSURFACE, 1024, 768, 32, 0, 0, 0, 0);
        //SDL_FillRect(affichage, NULL, SDL_MapRGB(top->format, 255, 255, 255));
        sprintf(filename, "tmp/top%d.bmp", i);
        top = IMG_Load(filename);
        //SDL_BlitSurface(top, NULL, affichage, &position);
      }
      else
      {
        SDL_FillRect(affichage, NULL, SDL_MapRGB(top->format, 255, 255, 255));
      }

      switch(choice)
      {
        case 1:
          DrawLine(x1,y1,x2,y2,color,top);
          break;
        case 2:
          DrawRectangle(x1,y1,x2-x1,y2-y1,color,top);
          break;
        case 3:
          FillRectangle(x1,y1,x2-x1,y2-y1,color,top);
          break;
        case 4:
          DrawCircle(x1,y1,(int)sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),color,top);
          break;
        case 5:
          FillCircle(x1,y1,(int)sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)), color,top);
          break;
        case 6:
          DrawPolygon(x1,y1,(int)sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),num, atan2(x2-x1,y2-y1), color,top);
          break;
        case 7:
          DegradeLinear(x1, y1, x2, y2, r1, g1, b1, r2, g2, b2,top);
          break;
        case 8:
          DegradeCirle(x1, y1, (int)sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)), r1, g1, b1, r2, g2, b2, top);
          break;
        case 9: 
          FillPolygon(x1,y1,(int)sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)),num, atan2(x2-x1,y2-y1), color,top);
          break;
      }
      SDL_BlitSurface(top, NULL, affichage, &position);
    }
    if(state1&&!state2) //unclik
    {
      i++;
      max=i;
      sprintf(filename, "tmp/top%d.bmp", i);
      SDL_SaveBMP(top, filename);
    }

    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        continuer = 0;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_c:
            SDL_FillRect(top, NULL, SDL_MapRGB(top->format, 255, 255, 255));
            SDL_FillRect(affichage, NULL, SDL_MapRGB(top->format, 255, 255, 255));
            break; 
          case SDLK_z:
            if(i<max){i++;}
            top =  SDL_CreateRGBSurface(SDL_HWSURFACE, 1024, 768, 32, 0, 0, 0, 0);
            SDL_FillRect(affichage, NULL, SDL_MapRGB(top->format, 255, 255, 255));
            sprintf(filename, "tmp/top%d.bmp", i);
            top = IMG_Load(filename);
            SDL_BlitSurface(top, NULL, affichage, &position);
            break; 

	case SDLK_i :
	 inverse(top);
	  break; 
	case SDLK_f :
	 plusfonce(top);
	  break; 
	
	case SDLK_c :
	 plusclaire(top);
	  break; 


	case SDLK_BACKSPACE :

	  if(i>0)
            {
              --i;
              top =  SDL_CreateRGBSurface(SDL_HWSURFACE, 1024, 768, 32, 0, 0, 0, 0);
              SDL_FillRect(affichage, NULL, SDL_MapRGB(top->format, 255, 255, 255));
              sprintf(filename, "tmp/top%d.bmp", i);
              top = IMG_Load(filename);
              SDL_BlitSurface(top, NULL, affichage, &position);
            }
            else
            {
              SDL_FillRect(affichage, NULL, SDL_MapRGB(top->format, 255, 255, 255));
            }
             break;
         //##### -> NUM_SELECT
          case SDLK_KP1:
              num = 1;
              break;
            case SDLK_KP2:
              num = 2;
              break;
            case SDLK_KP3:
              num = 3;
              break;
            case SDLK_KP4:
              num = 4;
              break;
            case SDLK_KP5:
              num = 5;
              break;
              case SDLK_KP6:
              num = 6;
              break;
            case SDLK_KP7:
              num = 7;
              break;
            case SDLK_KP8:
              num = 8;
              break;
            case SDLK_KP9:
              num = 9;
              break;
            default : break;
          }
    }

    SDL_Flip(affichage);
    state1=state2;
  }
  //printf("exit\n");
  
  if(argc>2)
  {
    SDL_SaveBMP(top, argv[2]);
  }
  else
  {
    SDL_SaveBMP(top, "output.bmp");
  }

  //SDL_WM_SetIcon(SDL_LoadBMP("iconee.bmp"), NULL);
  return EXIT_SUCCESS;
}

void attendreTouche(void)
{
  SDL_Event event;

  do
    SDL_WaitEvent(&event);
  while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}

void setPixelVerif(int x, int y, Uint32 coul, SDL_Surface *s)
{
  if (x >= 0 && x < s->w &&
      y >= 0 && y < s->h)
    setPixel(x, y, coul, s);
}

void setPixel(int x, int y, Uint32 pixel, SDL_Surface *surface)
{
  int nbOctetsParPixel = surface->format->BytesPerPixel;
    
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    
  switch(nbOctetsParPixel)
  {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      }
      else
      {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
    case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

void Read_tool(int *choice, int *num,
              int *r1,int *g1,int *b1,
              int *r2,int *g2,int *b2,
              Uint32 *c1, Uint32 *c2, SDL_Surface *top)
{
  int fd;
  static const char filename[] = "tmp/tool";
  fd = open(filename,O_RDONLY);
  char line[128];
  read(fd, line, 128);

  *choice = atoi(strtok (line," "));
  *num = atoi(strtok (NULL," "));

  *r1 = atoi(strtok (NULL," "));
  *g1 = atoi(strtok (NULL," "));
  *b1 = atoi(strtok (NULL," "));
  *r2 = atoi(strtok (NULL," "));
  *g2 = atoi(strtok (NULL," "));
  *b2 = atoi(strtok (NULL," "));

  *c1 = ColorFromRGB(*r1, *g1, *b1, top);

  *c2 = ColorFromRGB(*r2, *g2, *b2, top);

  close(fd);
}

void effacerEcran(SDL_Surface *s)
{
  SDL_FillRect(s, NULL, 0);
}

Uint32 ColorFromRGB(int r, int g, int b, SDL_Surface *s)
{
  return SDL_MapRGB(s->format,r,g,b);
}

void FillRectangle(int x, int y, int w, int h, Uint32 coul, SDL_Surface *s)
{
  SDL_Rect r;
  if(w<0)
  {
    x+=w;
    w*=-1;
  }
  if(h<0)
  {
    y+=h;
    h*=-1;
  }
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  SDL_FillRect(s, &r, coul);
}

void DrawRectangle(int x, int y, int w, int h, Uint32 coul,SDL_Surface *s)
{
  DrawLine(x,y,x,y+h,coul,s);
  DrawLine(x,y,x+w,y,coul,s);
  DrawLine(x+w,y+h,x,y+h,coul,s);
  DrawLine(x+w,y+h,x+w,y,coul,s);
}

void swap(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void DrawLine(int x1, int y1, int x2, int y2, Uint32 coul, SDL_Surface *s)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) 
  {
    /* parcours par l'axe vertical */

    if (y1 > y2) 
    {
      swap(&x1, &x2);
      swap(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    setPixelVerif(x, y, coul, s);

    for (y = y1+1; y <= y2; ++y) 
    {
      if (d >= 0) 
      {
        x += xincr;
        d += aincr;
      } 
      else
        d += bincr;
        setPixelVerif(x, y, coul, s);
    }
  } 
  else 
  {
    /* parcours par l'axe horizontal */
    
    if (x1 > x2) {
      swap(&x1, &x2);
      swap(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    setPixelVerif(x, y, coul,s);

    for (x = x1+1; x <= x2; ++x) 
    {
      if (d >= 0) 
      {
        y += yincr;
        d += aincr;
      } 
      else
        d += bincr;

      setPixelVerif(x, y, coul,s);
    }
  }    
}

void DrawCircle(int cx, int cy, int rayon, int coul, SDL_Surface *s)
{
  int d, y, x;

  //d = 3 - (2 * rayon);
  d = rayon-1;
  x = 0;
  y = rayon;

  while (y >= x) 
  {
    setPixelVerif(x+cx,y+cy,coul,s);
    setPixelVerif(y+cx,x+cy,coul,s);
    setPixelVerif(-x+cx,y+cy,coul,s);
    setPixelVerif(-y+cx,x+cy,coul,s);
    setPixelVerif(x+cx,-y+cy,coul,s);
    setPixelVerif(y+cx,-x+cy,coul,s);
    setPixelVerif(-x+cx,-y+cy,coul,s);
    setPixelVerif(-y+cx,-x+cy,coul,s);
    if(d>=2*x)
    {
      d=d-2*x-1;
      x++;
    }
    else if(d<=2*(rayon-y))
    {
      d=d+2*y-1;
      y--;
    }
    else
    {
      d=d+2*(y-x-1);
      y--;
      x++;
    }
  }
}

void FillCircle(int cx, int cy, int rayon, int coul, SDL_Surface *s)
{
  int d, y, x;

  //d = 3 - (2 * rayon);
  d = rayon-1;
  x = 0;
  y = rayon;

  while (y >= x) 
  {
    DrawLine(-x+cx,y+cy,x+cx,y+cy,coul, s);
    DrawLine(-y+cx,x+cy,y+cx,x+cy,coul, s);
    DrawLine(-x+cx,-y+cy,x+cx,-y+cy,coul, s);
    DrawLine(-y+cx,-x+cy,y+cx,-x+cy,coul, s);
    if(d>=2*x)
    {
      d=d-2*x-1;
      x++;
    }
    else if(d<=2*(rayon-y))
    {
      d=d+2*y-1;
      y--;
    }
    else
    {
      d=d+2*(y-x-1);
      y--;
      x++;
    }
  }
}

void DegradeCirle(int cx, int cy, int rayon,
                  int r1, int g1, int b1, int r2, int g2, int b2,
                  SDL_Surface *s)
{
  for (int i = rayon; i>0;--i)
  {
    DrawCircle(cx, cy, i, 
      ColorFromRGB(
        r1+(r2-r1)*(rayon-i)/rayon,
        g1+(g2-g1)*(rayon-i)/rayon,
        b1+(b2-b1)*(rayon-i)/rayon
        ,s), s);
  }
  DrawCircle(cx, cy, 0, 
      ColorFromRGB(
        r1+(r2-r1),
        g1+(g2-g1),
        b1+(b2-b1)
        ,s), s);
}


void DegradeLinear(int x1, int y1, int x2, int y2,
                  int r1, int g1, int b1, int r2, int g2, int b2,
                  SDL_Surface *s)
{
  if(x1<x2)
  {
    for (int i = x1; i < x2; ++i)
      DrawLine(i, y1,i, y2, 
        ColorFromRGB(
          r1+(r2-r1)*(i-x1)/(x2-x1),
          g1+(g2-g1)*(i-x1)/(x2-x1),
          b1+(b2-b1)*(i-x1)/(x2-x1),s),
          s);
  }
  else
  {
    for (int i = x2; i < x1; ++i)
      DrawLine(i, y1,i, y2, 
        ColorFromRGB(
          r1+(r2-r1)*(i-x1)/(x2-x1),
          g1+(g2-g1)*(i-x1)/(x2-x1),
          b1+(b2-b1)*(i-x1)/(x2-x1),s),
          s);
  }

  
}

typedef struct s_list  *list;
struct s_list
{
    int                 x,y;
    list                next;
};

list add(list l, int x, int y)
{
  list t = malloc(sizeof (struct s_list));
  t->x=x;
  t->y=y;
  t->next=l;
  return t;
}

void DrawPolygon(int cx, int cy, int rayon, int n, double d, int coul, SDL_Surface *s)
{
  if(n>0)
  {
    int x, y, x2, y2,X,Y;
    list l = NULL, t=NULL;
    for (int i = 0; i < n; ++i)
    {
      double angle = (360/n+i*360/n)*PI/180 - d;
      x = (int)(cos(angle)*rayon)+cx;
      y = (int)(sin(angle)*rayon)+cy;
      l=add(l,x,y);
    }
    x=l->x;
    y=l->y;
    X=x;Y=y;
    t=l;
    l=l->next;
    free(t);
    while(l)
    {
      x2=l->x;
      y2=l->y;
      DrawLine(x,y,x2,y2,coul, s);
      x=x2;
      y=y2;
      t=l;
      l=l->next;
      free(t);
    }
    DrawLine(x,y,X,Y,coul, s);
  }
}

void FillPolygon(int cx, int cy, int rayon, int n, double d, int coul, SDL_Surface *s)
{
  for (int i = 0; i < rayon; ++i)
  {
    DrawPolygon(cx, cy, i, n, d, coul, s);
  }
}



void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /*Ici p est l'adresse du pixel que l'on veut modifier*/
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch(nbOctetsParPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}


Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /* Ici p est l'adresse du pixel que l'on veut connaitre */
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;

        /*Ne devrait pas arriver, mais évite les erreurs*/
        default:
            return 0; 
    }
}

Uint8 addVal(Uint8 composante, int valeur)
{
    int tampon; /*Variable entière qui sert de tampon*/
    tampon=(int)composante + valeur;
 /*On fait en sorte que tampon reste dans l'intervalle [0,255] */
    if (tampon>255) {tampon=255;} else if (tampon<0) {tampon=0;}
 /*Avec l'opérateur cast (Uint8) on tranforme tampon en un entier de type Uint8*/
    return (Uint8)tampon;
}


void inverse(SDL_Surface *surface)
{ /*x et y sont les index permettant de se déplacer dans l'image*/
    int x,y;
    /*r,g,b,a vont stocker les composantes d'un pixel*/
    int r,g,b,a;
    /*pixel stocke le code couleur d'un pixel*/
    Uint32 pixel;

    /*On bloque la surface pour pouvoir travailler dessus */
    SDL_LockSurface(surface);
    /*Double boucle pour parcourir l'intégralité de l'image.*/
    for (y=0;y<surface->h;y++)
    {
        for (x=0;x<surface->w;x++)
        {
            /*On récupère le code couleur du pixel.*/
            pixel=obtenirPixel(surface,x,y);
            /*On extrait les composantes rouge, vert, bleu et alpha*/
            SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

	    /*On ajoute/soustrait la quantité voulue aux 3 composantes rouge, vert, bleu.*/
            r=255-r;
            g=255-g;
            b=255-b;
 

            /*On retransforme les 4 composantes en un seul code couleur dans pixel */
            pixel=SDL_MapRGBA(surface->format, r, g, b, a);
            /*On injecte le code couleur pixel dans le pixel correspondant*/
            definirPixel(surface, x, y, pixel);
	    r =0;
	    b = 0;
	    g= 0;
        }
    }
    /*On libère la surface, elle peut désormais être réutilisée pour autre chose*/
    SDL_UnlockSurface(surface);


}


void plusfonce(SDL_Surface *surface)
{ 
  int x,y;
int r,g,b,a;
Uint32 pixel;
 SDL_LockSurface(surface);
  for (y=0;y<surface->h;y++)
    {
        for (x=0;x<surface->w;x++)
	  {   pixel=obtenirPixel(surface,x,y);
             SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
	     ///////////////////////
	     r=(r/2)+(r/3);
	     g=(g/2)+(g/3);
	     b=(b/2)+(b/3);
	     if ( r <0 && b < 0 && g <0 )
	       { r= 0; b=0; g=0;}
	     if ( r>255 && b >255 && g >255)
	       { r = 255; b = 255; g =255;}


	   
             ////////////////////
            pixel=SDL_MapRGBA(surface->format, r, g, b, a);
	    definirPixel(surface, x, y, pixel);
	    r =0;
	    b = 0;
	    g= 0;
        }
    }
    SDL_UnlockSurface(surface);
}

void plusclaire(SDL_Surface *surface)
{ 
  int x,y;
 Uint8 r,g,b,a;
Uint32 pixel;
 SDL_LockSurface(surface);
  for (y=0;y<surface->h;y++)
    {
        for (x=0;x<surface->w;x++)
	  {   pixel=obtenirPixel(surface,x,y);
             SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
	     ///////////////////////
	     r=addVal(r,r/4);
	     g=addVal(g,g/4);
	     b=addVal(bb/4;
	     ////////////////////



	     pixel=SDL_MapRGBA(surface->format, r, g, b, a);
	     definirPixel(surface, x, y, pixel);

	     r =0;
	     b = 0;
	     g = 0;

        }
    }
    SDL_UnlockSurface(surface);
}

