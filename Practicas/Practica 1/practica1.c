#include <stdio.h>
#include <dos.h>

int CFondo;
int CTexto;

// hace una pausa

void pausa(){
    union REGS inregs, outregs;

    inregs.h.ah=8;

    int86(0x21, &inregs, &outregs);
}

// Colocar el cursor en una posición determinada

void gotoxy(int x, int y){
    union REGS inregs, outregs;

    inregs.h.ah=0x02;
    inregs.h.bh=0x00;
    inregs.h.dh=y; // Coordenada y
    inregs.h.dl=x; // Coordenada x

    int86(0x10, &inregs, &outregs);
}

// Fijar el aspecto del cursor

void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah=0x01;

    switch(tipo_cursor){
        case 0: // Invisible
            inregs.h.ch=010;
            inregs.h.cl=000;
            break;
        case 1: // Normal
            inregs.h.ch=010;
            inregs.h.cl=010;
            break;
        case 2: // Grueso
            inregs.h.ch=000;
            inregs.h.cl=010;
            break;
    }

    int86(0x10, &inregs, &outregs);
}

// Fijar el modo de vídeo deseado

void setvideomode(int x){
    union REGS inregs, outregs;
    inregs.h.ah=0x00;
    inregs.h.al=x;
    int86(0x10, &inregs, &outregs);
}

// Obtener el modo de vídeo actual

void getvideomode(){
    union REGS inregs, outregs;
    int modo;
    int numColumnas;
    inregs.h.ah=0xF;
    int86(0x10, &inregs, &outregs);
    modo=outregs.h.al;
    numColumnas=outregs.h.ah;
    if(modo<=3 || modo==7){ 
        printf("Texto");
    }else{
        printf("Grafico");
    }
}

// Modificar el color de primer plano con el que se mostrarán los caracteres

void textcolor(int CTexto){
    union REGS inregs, outregs;

    inregs.h.ah=0x09;
    inregs.h.al=97;
    inregs.h.bl=CTexto;
    inregs.h.bh=0x00;
    inregs.x.cx=5;

    int86(0x10, &inregs, &outregs);
}

// Modificar el color de fondo con el que se mostrarán los caracteres

void textbackground(int CTexto, int CFondo){
    union REGS inregs, outregs;
    int color=CFondo << 4 | CTexto;

    inregs.h.ah=0x09;
    inregs.h.al=97;
    inregs.h.bl=color;
    inregs.h.bh=0x00;
    inregs.x.cx=5;

    int86(0x10, &inregs, &outregs);
}

// Borrar toda la pantalla

void clrscr(){
    union REGS inregs, outregs;

    inregs.h.ah=0x15;
    int86(0x10, &inregs, &outregs);
    inregs.h.ah=0x00;
    int86(0x10, &inregs, &outregs);
}

// Escribe un carácter en pantalla con el color actual

void cputchar(char c){
    union REGS inregs, outregs;

    inregs.h.ah=2;
    inregs.h.dl=c;

    int86(0x21, &inregs, &outregs);
}

// Obtiene un carácter de teclado y lo muestra en pantalla

int getche(){
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah=0x01;

    int86(0x21, &inregs, &outregs);

    caracter=outregs.h.al; // Código ASCII del carácter
    return caracter;
}

// Función para dibujar un cuadrado

void dibujarCuadrado(int fila1, int col1, int fila2, int col2, int ctexto, int cfondo){
    union REGS inregs, outregs;

    inregs.h.ah=0x06;
    inregs.h.al=0;
    inregs.h.bh=cfondo << 4 | ctexto;
    inregs.h.ch=fila1;
    inregs.h.cl=col1;
    inregs.h.dh=fila2;
    inregs.h.dl=col2;

    int86(0x10, &inregs, &outregs);
}

// Función principal

int main(){
    int temp, x, y, i;

    printf("\nCursor colocado en la posicion indicada");
    gotoxy(0x33, 0x03);
    pausa();

    printf("\nPulsa una tecla: ");
    temp=getche();

    printf("\nHas pulsado: ");
    cputchar((char)temp);

    printf("\nCursor invisible: ");
    setcursortype(0);
    pausa();
    printf("\nCursor normal: ");
    setcursortype(1);
    pausa();
    printf("\nCursor grueso: ");
    setcursortype(2);
    pausa();

    printf("\nEstableciendo modo de video");
    setvideomode(0x03);
    pausa();

    printf("\nModo de video actual: ");
    getvideomode();
    pausa();

    CFondo=2; // Verde
    CTexto=10; // Verde claro

    printf("\nCaracteres con colores: ");
    textcolor(CTexto);
    pausa();

    CTexto=1; // Azul

    printf("\nCaracteres y fondo con colores: ");
    textbackground(CTexto, CFondo);
    pausa();

    printf("\nCuadrado verde: ");
    dibujarCuadrado(5, 5, 10, 20, CTexto, CFondo);
    pausa();

    setvideomode(0x04);
    getvideomode();
    printf(" CGA");

    setvideomode(0x03); // Vuelta a modo texto

    // Borrar pantalla
    clrscr();
    printf("Pantalla borrada\n");
    pausa();

    return 0;
}