/* El programa genera 20 números aleatorio y los gráfica
Autor: Arturo Zúñiga L.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main ()
{
    float xy[20][2];
    //se crea y abre el archivo dos.txt en modo escritura
    //para almacenar los valores x y y de los números aleatorios
    FILE *datos = fopen("datos.txt", "w");
    // lista de comandos para configurar la gráfica de gnuplot
    char *configGnuplot[] = {"set title \"Titulo\"",
                              "set xlabel \"x\"",
                              "set ylabel \"y\"",
                              "plot 'datos.txt' with lines"};

    srand(time(NULL)); //inicializa el generador de números aleatorios
    
    for (int i=0; i<20; i++) //para generar 20 números aleatorios
    {
        //genera números aleatorios entre 0 y 100 para x
        xy[i][0] = (((float) rand()) / (float) RAND_MAX)*100.0;
        //genera números aleatorio entre 0 y 100 para y
        xy[i][1] = (((float) rand()) / (float) RAND_MAX)*100.0;
    }
    bool cambio=false;
    int len=20; //tamaño inicial del arreglo a ordenar
    float aux;
    //ciclo para ordena de menor a mayoy las coordenads de los números aleatorios
     while(1) { 
        for(int i=1; i<len; i++) {
            if(xy[i-1][0] > xy[i][0]) {
                // mueve a x
                aux=xy[i][0];
                xy[i][0]=xy[i-1][0];
                xy[i-1][0]=aux;
                // mueve a y
                aux=xy[i][1];
                xy[i][1]=xy[i-1][1];
                xy[i-1][1]=aux;
                cambio=true;
            }
        }
        if(!cambio) break; //sale de la iteración, si ya esta ordenado
        --len; //se va decremenatando la busqueda porque los últimos elementos ya estan ordenados
        cambio=false;
    }
    // se guardan x y y en el archivo creado previamente
    for (int i=0; i<20; i++)
        fprintf(datos, "%lf %lf \n", xy[i][0], xy[i][1]);
    
    // ejecuta gnuplot y envia los comandos (incluido el archivo de los datos) a gráficar
    FILE *ventanaGnuplot = popen ("gnuplot -persist", "w");    
    for (int i=0; i<4; i++){ //el valor de 4 es el número de parámetros de la variable configGnuplot
        fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
 }
    fclose(datos);  //cierra el archivo
    return 0;
}