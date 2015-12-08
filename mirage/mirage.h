Uint32 getpixel(SDL_Surface *surface, int x, int y);
void attendreTouche(void);
void setPixel(int x, int y, Uint32 coul,SDL_Surface *s);
void effacerEcran(SDL_Surface *s);
void actualiser(SDL_Surface *s);
Uint32 ColorFromRGB(int r, int g, int b, SDL_Surface *s);
void DrawLine(int x1, int y1, int x2, int y2, Uint32 coul,SDL_Surface *s);
void DrawRectangle(int x, int y, int w, int h, Uint32 coul,SDL_Surface *s);
void FillRectangle(int x, int y, int w, int h, Uint32 coul,SDL_Surface *s);
void DrawCircle(int cx, int cy, int rayon, int coul,SDL_Surface *s);
void FillCircle(int cx, int cy, int rayon, int coul,SDL_Surface *s);
void DegradeCirle(int cx, int cy, int rayon,
                  int r1, int g1, int b1, int r2, int g2, int b2,SDL_Surface *s);
void DegradeLinear(int x1, int y1, int x2, int y2,
                  int r1, int g1, int b1, int r2, int g2, int b2,SDL_Surface *s);
void DrawPolygon(int cx, int cy, int rayon, int n, double d, int coul,SDL_Surface *s);
void FillPolygon(int cx, int cy, int rayon, int n, double d, int coul, SDL_Surface *s);
int main();