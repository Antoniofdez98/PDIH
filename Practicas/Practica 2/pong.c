#include<ncurses.h>
#include<unistd.h>

#define DELAY 60000

void inicio(){                                                      
    initscr();
    keypad(stdscr,true);                                            
    noecho();
    curs_set(FALSE);                                                
    mvprintw(4,10,"JUGADOR 1:");    
    mvprintw(5,10,"CONTROLES: W arriba, S abajo");     
    mvprintw(6,10,"JUGADOR 2:");    
    mvprintw(7,10,"CONTROLES: I arriba, K abajo");     
    mvprintw(8,10,"PULSA Q PARA PARA TERMINAR LA PARTIDA");         
    mvprintw(9,10,"PULSA P PARA PAUSA");                            
    box(stdscr,'|','-');                                            
    getch();
    nodelay(stdscr,1);
    clear();
}

void pausa(int puntos1, int puntos2){                                         
    clear();
    mvprintw(5,5,"PAUSA. PULSA CUALQUIER TECLA PARA CONTINUAR");    
    mvprintw(6,5,"RESUMEN: %i vs %i",puntos1,puntos2);                        
    box(stdscr,'|','-');                                            
    nodelay(stdscr,0);
    getch();
}

void final(int puntos1, int puntos2){                                                   
    nodelay(stdscr,0);
    clear();
    box(stdscr,'|','-');                                                    
    if (puntos1 > puntos2){                                                           
        mvprintw(7,32,"GANADOR: JUGADOR 1");                          
    }
    else if(puntos1 < puntos2){                                                       
        mvprintw(7,32,"GANADOR: JUGADOR 2\n");                          
    }
    else{                                                                   
        mvprintw(7,38,"EMPATE\n");                                      
    }
    mvprintw(9,38, "%i vs %i",puntos1,puntos2);      
    refresh();
    getch();
}

void barras(int columnas, int pos1, int pos2){       
    int i;
    for (i = 0; i < 5; i++){                        
	    mvprintw(pos1+i, 2, "|");                   
	    mvprintw(pos2+i, columnas-2, "|");          
    }
}


int main (){
    int i;                              
    int x = 35, y = 10;
    bool quit = false;
    int pause = 0;
    int jugador1 = 0;
    int jugador2 = 0;
    int puntuacion_ganadora = 10;
    int fils, cols;
    int y1= 10, y2= 10;
    
    int next_x = 0;
    int directionx = 1;
    int next_y = 0;
    int directiony = 1;

    int tecla = 0;

    inicio();
    getmaxyx(stdscr,fils,cols);
    int max_y = fils, max_x = cols; 

    while(quit == false){       
        clear();
        nodelay(stdscr,1);
        mvprintw(y,x,"o");
        mvprintw(0,cols/2,"%i vs %i",jugador1,jugador2); 
        barras(cols, y1, y2);
        refresh();

        tecla = getch();
        switch(tecla){
            case 'q':
                final(jugador1,jugador2);
                quit = true;
                break;
            case 'p':
                pausa(jugador1,jugador2);
                break;
            case 's':
                if(y1 + 5 == fils){
                    y1 = fils - 5;
                }
                else{
                    y1 += 1;
                }
                break;
            case 'w':
                if(y1 == 0){
                    y1 = 0;
                }
                else{
                    y1 -= 1;
                }
                break;
            case 'k':
                if(y2 + 5 == fils){
                    y2 = fils - 5;
                }
                else{
                    y2 += 1;
                }
                break;
            case 'i':
                if(y2 == 0){
                    y2 = 0;
                }
                else{
                    y2 -= 1;
                }
                break;
        }

        usleep(DELAY);

        next_x = x + directionx;
        next_y = y + directiony;

        if(next_x == max_x-2 || next_x == 2){
            if(next_y == y1 || next_y == y1+1 || next_y == y1+2 || next_y == y1+3 || next_y == y1+4){
                directionx *= -1;
            }
            if(next_y == y2 || next_y == y2+1 || next_y == y2+2 || next_y == y2+3 || next_y == y2+4){
                directionx *= -1;
            }
        }

        if(next_x >= max_x || next_x <= 0) {
            directionx *= -1;
            
            x = cols/2, y = fils/2;

            if(next_x == max_x){
                jugador1 += 1;
            }else if(next_x == 0){
                jugador2 += 1;
            }
        } else {
            x += directionx;
        }

        if (next_y >= max_y || next_y < 0) {
            directiony *= -1;
        } else {
            y += directiony;
        }

        if(jugador1 == puntuacion_ganadora || jugador2 == puntuacion_ganadora){
            final(jugador1,jugador2);
            quit = true;
        }
    }

    endwin();
    return 0;
}