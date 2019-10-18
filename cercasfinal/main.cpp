


#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include "synchPT.h"
#include <array>
#include <algorithm>
#include <vector>
using namespace std;

#define NUMTHRDS 100
int status;
int n = 256;
pthread_t thds[NUMTHRDS];

Mutex mutex;


struct puntos {
   int x;
   int y;
   int maxX;
   int maxY;
   
   
};

struct rectangulos {
   int x1;
   int y1;
   int x2;
   int y2;
   int perimetro;
   
};

int cC = 0, cM = 0;
int matX=0, matY=0;
int puntosbloqueados=0;
int main ( int argc, char *argv[] );
void *C ( void *arg );
void *M ( void *arg );
puntos rectfinal;

int main ( int argc, char *argv[] ) {

    matX=5;
    matY=5;
    puntosbloqueados=9;
  puntos block[puntosbloqueados];
  rectangulos rectfinal;
  rectfinal.perimetro=0;
  rectfinal.x1=0;
  rectfinal.y1=0;
  rectfinal.x2=0;
  rectfinal.y2=0;
  
  
  
  
  block[0].x=1;
  block[0].y=1;
  block[1].x=1;
  block[1].y=4;
  block[2].x=2;
  block[2].y=4;
  block[3].x=3;
  block[3].y=1;
  block[4].x=3;
  block[4].y=2;
  block[5].x=5;
  block[5].y=1;
  block[6].x=5;
  block[6].y=2;
  block[7].x=5;
  block[7].y=3;
  block[8].x=5;
  block[8].y=5;
  
  for(int i=0;i<(puntosbloqueados);i++){
      cout << "Punto block (" << block[i].x <<"," << block[i].y << ")"<< endl;
  }
  
  

  int totalmatusable=matX*matY-puntosbloqueados;
  
  puntos puntosver[totalmatusable];

int contador=0;
    bool bloqueop=false;
    for(int i=0;i<matX;i++){//crea la matriz con puntos usables sin los bloqueados
      bloqueop=false;
      for(int k=0;k<matY;k++){
          int xt=i+1;
          int yt=k+1;
          for(int p=0;p<puntosbloqueados;p++){
              if(xt==block[p].x && yt==block[p].y){
                  bloqueop=true;
                  p=puntosbloqueados;
              } 
              
              
          }
          
          if(bloqueop==true){
                  bloqueop=false;
              }else{
                  puntosver[contador].x=xt;
                  puntosver[contador].y=yt;
                  
                  contador++;
          }
          
          
      }
      
  }  
  for(int i=0;i<(totalmatusable);i++){
      cout << "Punto usable(" << puntosver[i].x <<"," << puntosver[i].y << ")"<< endl;
  }

  for(int i=0;i<(puntosbloqueados);i++){
      cout << "Punto block (" << block[i].x <<"," << block[i].y << ")"<< endl;
  }
  
  bool dospordos=false;
                
  for(int i=0;i<(totalmatusable);i++){
      bool finalm=false;
      int controlx=puntosver[i].x;
      int controly=puntosver[i].y;
      bool controlxf=false;
      bool controlyf=false;
      int testmaxx=0;
      int testmaxy=0;
      int transX=0;
      int transY=0;
      while(finalm==false){//controla si el punto tiene posibilidad de hacer un cuadrado
      
        if(controlx==matX && controlxf==false){
            controlxf=true;
            puntosver[i].maxX=controlx-puntosver[i].x;

        }

        if(controly==matY && controlyf==false){
            controlyf=true;
            puntosver[i].maxY=controly-puntosver[i].y;
            
        }

        if(controlyf==true && controlxf==true){

                finalm=true;
                if(puntosver[i].maxY>0 && puntosver[i].maxX>0){
                int xxt=puntosver[i].x;
                int yyt=puntosver[i].y;
                transY=puntosver[i].maxY;
                transX=puntosver[i].maxX;
                
                bool analisis=false;
                int dimx=2;
                int dimy=2;
                int contx=0;
                int conty=0;
                int movx=0;
                int movy=0;
                bool cambioX=false;
                bool bloqueopunto=false;
                while (analisis==false){ //analiza los diferentes cuadros posibles usando dimensiones
                    movx=dimx-1;
                    movy=dimy-1;
                    int perimetro=(movx)*2+(movy)*2;
                    
                    if(perimetro>rectfinal.perimetro){//si perimetro del rectangulo es menor no nos sirve
                        if(dospordos==false && rectfinal.perimetro<4){// intenta hacer un 2x2 
                           contx=puntosver[i].x+1; 
                           conty=puntosver[i].y+1;
                           bloqueopunto=false;
                           for(int p=0;p<puntosbloqueados;p++){
                                if(contx==block[p].x && conty==block[p].y){
                                    p=puntosbloqueados;
                                    bloqueopunto=true;
                                }

                            }
                           if(bloqueopunto==false){//crea el rectangulo 
                               rectfinal.perimetro=perimetro;
                               rectfinal.x1=puntosver[i].x;
                               rectfinal.y1=puntosver[i].y;
                               rectfinal.x2=contx;
                               rectfinal.y2=conty;
                               dospordos=true;
                               if(movx==puntosver[i].maxX && movy==puntosver[i].maxY){
                                   analisis=true;
                               }
                           
                           }
                        }else{//crea otro tipo de rectangulos, requieren mas trabajo
                            bool rectanguloposiblef=true;
                            int manX=0;
                            bool manXfin=false;
                            int manY=0;
                            bool manYfin=false;
                            int xvar=puntosver[i].x+manX;
                            int yvar=puntosver[i].y+manY;
                            int xfijo=puntosver[i].x+movx;
                            int yfijo=puntosver[i].y+movy;
                            while(rectanguloposiblef==true){
                                
                                //manejar la x
                                if(manX<movx){
                                    manX++;
                                    
                                    xvar+=manX;
                                    if(xvar<=matX){
                                        for(int p=0;p<puntosbloqueados;p++){
                                            if(xvar==block[p].x && yfijo==block[p].y){
                                                p=puntosbloqueados;
                                                rectanguloposiblef=false;
                                            }

                                         }
                                    }
                                    
                                }else{
                                    manXfin=true;
                                }
                                
                                
                                
                                
                                
                                //manejar la y
                                
                                
                                if(manY<movy){
                                    manY++;
                                    yvar+=manY;
                                    if(xvar<=matY){
                                        for(int p=0;p<puntosbloqueados;p++){
                                            if(xfijo==block[p].x && yvar==block[p].y){
                                                p=puntosbloqueados;
                                                rectanguloposiblef=false;
                                            }

                                        }
                                    }
                                    
                                }else{
                                    manYfin=true;
                                }
                                
                                
                                
                                if(manXfin==true && manXfin==true){//logro crear el rectangulo
                                    
                                    rectanguloposiblef=false;
                                    rectfinal.perimetro=perimetro;
                                    rectfinal.x1=puntosver[i].x;
                                    rectfinal.y1=puntosver[i].y;
                                    rectfinal.x2=xfijo;
                                    rectfinal.y2=yfijo;
                                    
                                }
                            }
                                
                        }
                        
                        
                              
                        
                    }else{
                       int maxXfin=puntosver[i].maxX;
                       int maxYfin=puntosver[i].maxY;
                             
                       if(maxXfin>=movx && cambioX==true){
                           if(maxXfin==movx){
                               analisis=true;
                           }else{
                                dimx++;
                                movx=dimx-1;
                           }
                               
                           cambioX=false;
                           dimy=2;
                           movy=dimy-1;
                       }
                       if(maxYfin>=movy){
                           if(maxYfin==movy){
                               cambioX=true;
                           }else{
                               dimy++;
                               movy=dimy-1;
                           }
                           
                           if(dimy==puntosver[i].maxY){
                               cambioX=true;
                           }
                       }
                        
                    }
                    
                    
                }
                
                
                
            }
                
        }

        if(controlxf==false){
             controlx++;
             int xt=controlx;
             int yt=puntosver[i].y;
             for(int p=0;p<puntosbloqueados;p++){
                 int bloqueox=block[p].x;
                 int bloqueoy=block[p].y;
                 
                if(xt==block[p].x && yt==block[p].y){
                    controlxf=true;
                    puntosver[i].maxX=controlx-puntosver[i].x-1;
                    testmaxx=puntosver[i].maxX;
                            
                    p=puntosbloqueados;
                } 


             }

        }

        if(controlyf==false){
             controly++;
             int xt=puntosver[i].x;
             int yt=controly;
             for(int p=0;p<puntosbloqueados;p++){
                if(xt==block[p].x && yt==block[p].y){
                    controlyf=true;
                    puntosver[i].maxY=controly-puntosver[i].y-1;
                    testmaxy=puntosver[i].maxY;
                    p=puntosbloqueados;
                } 


             }
        }
       
          
          
      }
      
    
      
  }
  for(int i=0;i<(totalmatusable);i++){
      cout << "Punto usable(" << puntosver[i].x <<"," << puntosver[i].y << ")"<< endl;
      cout << "Punto usable con max X=" << puntosver[i].maxX <<" y max Y=" << puntosver[i].maxY << endl;
  }
  
  
  cout << "El rectangulo con perimetro " << rectfinal.perimetro <<" y vertices (" << rectfinal.x1 << ","<<rectfinal.y1<< ") y ("<< rectfinal.x2 << ","<<rectfinal.y2<< ")"<< endl;
  
  /*
  long i;
  
  
  pthread_attr_t attr;
  
  pthread_attr_init ( &attr );
  pthread_attr_setdetachstate ( &attr, PTHREAD_CREATE_JOINABLE );

  for ( i = 0; i < NUMTHRDS; i++ ) {
    if ( 0 == ( rand() % 2 ) )
       pthread_create ( &thds[i], &attr, C, ( void * ) i );
    else
       pthread_create ( &thds[i], &attr, M, ( void * ) i );
  }

  pthread_attr_destroy ( &attr );

  for ( i = 0; i < NUMTHRDS; i++ ) {
    pthread_join ( thds[i], ( void ** ) &status );
  }

  mutex.~Mutex();
//  pthread_exit ( NULL );

  cout << "\n";
  cout << "  Normal end of execution.\n";
*/
  //return 0;
}

void *bloqueoPuntos ( void *args) {

     
   mutex.Lock();	// Lock access to cM and cC variables
   /*
                    for(int p=0;p<puntosbloqueados;p++){
                        if(xT==bloqueoarr[p].x && yT==bloqueoarr[p].y){
                            controlxf=true;
                            puntosver[i].maxX=controlx-puntosver[i].x;
                        } 


                    }
   */
   mutex.Unlock();
   pthread_exit ( ( void * ) 0 );
}

/*
void *M ( void *arg ) {

   
   long thread = (long) arg;

   mutex.Lock();	// Lock access to cM and cC variables
          
   mutex.Unlock();
   
   pthread_exit ( ( void * ) 0 );	// Finish this thread

  
}
 */