/* El programa solicita las coordenadas a gráfica
Autor: Arturo Zúñiga L */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    int n;
    //se crea y abre el archivo dotos2.txt en modo escritura
    //para almacenar los valores x y y
    FILE *datos = fopen("datos2.txt", "w");
    // lista de comandos para configurar la gráfica de gnuplot
    char *configGnuplot[] = {"set title \"Titulo\"",
                              "set xlabel \"x\"",
                              "set ylabel \"y\"",
                              "plot 'datos2.txt' with lines"};

    
    printf("numero de pares coordenados: ");
    scanf("%d", &n);

    float x[n];
    float y[n];
    float num, num1;

    //se capturan los valores de x y y
    for(int i=0; i<n; i++) {
        printf("(X, Y): ");
        scanf("%f %f", &num, &num1);
        x[i]=num;
        y[i]=num1;
    }

    // se guardan x y y en el archivo creado previamente
    for (int i=0; i<n; i++)
        fprintf(datos, "%lf %lf \n", x[i], y[i]);

    // ejecuta gnuplot y se envian los comandos (incluido el archivo de los datos) a gráficar
    FILE *ventanaGnuplot = popen ("gnuplot -persist", "w");    
    for (int i=0; i<4; i++){ //el valor de 4 es el número de parámetros de la variable configGnuplot
        fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
 }
    fclose(datos);  //cierra el archivo
    return 0;
}