// Puedo tener un automata que reconozca los tres tripos de lenguajes: Hexa, Decimal, Octal
// O se puede hacer tres automatas y realizar algo que me permita ver de que tipo de lenguaje es
// Los octales empiezan con 0, si es 0x es hexa, y sino es decimal
// El carater centinela tiene la capacidad de indicarme cuando termina una palabra

#include <stdio.h>
#include <ctype.h>

int columna(int c){
    switch (c){
        case '0':
            return 0;
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7':
            return 1;
        case '8': case '9':
            return 2;
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            return 3;
        case 'x': case 'X':
            return 4;
        case '+': case '-':
            return 5;
        default:
            return 6;
    }
}
// Para verificar si una cadena es octal, exa o decimal lo 
// que hacemos es ver que estado fue el que se acepto la misma
int verificar(char* cadena){
    static int tt[8][7] = {
        {3,2,2,7,7,1,7},
        {7,2,2,7,7,7,7},
        {2,2,2,7,7,7,7},
        {4,4,7,7,5,7,7},
        {4,4,7,7,7,7,7},
        {6,6,6,6,7,7,7},
        {6,6,6,6,7,7,7},
        {7,7,7,7,7,7,7}
    };
    int i = 0;
    int c = cadena[i];
    int estado = 0;
    while(c != '\0' && c != '@' && estado != 7){
        estado = tt[estado][columna(c)];   /* esta línea es la clave */
        i++;
        c = cadena[i];
    }
    switch(estado){
        case 2:          return 1;   /* decimal */
        case 3: case 4:  return 2;   /* octal   */
        case 6:          return 3;   /* hexa    */
        default:         return 0;   /* error   */
    }
}

// Nosotros fundamentamos nuestro automata en la matriz que hicimos
// En c no hay booleanos por ende devolvemos un 1 si True y un 0 si False
int esPalabra(char* cadena){
    // La tabla statica se carga una vez en memoria, optimiza la memoria dado que solo se jecuta una vez
    // Osea por mas que se invoque la funcion varias veces solo la primera vez se ejecuta la tabla
    // La coloco con llaves para tenerla harcodeada
    // Simpre coloco un vector de cararcteres dado que no van a ser solo numeros sino algun que oro caracter
    static int tt[8][7] = {
        {3,2,2,7,7,1,7},
        {7,2,2,7,7,7,7},
        {2,2,2,7,7,7,7},
        {4,4,7,7,5,7,7},
        {4,4,7,7,7,7,7},
        {6,6,6,6,7,7,7},
        {6,6,6,6,7,7,7},
        {7,7,7,7,7,7,7}

    };
    int estado = 0;
    int i = 0;
    int c = cadena[i];
    while(c != '\0' && c != '@' && estado != 7) {
        estado = tt[estado][columna(c)];
        i++;
        c = cadena[i];
    }
    switch(estado){
        case 2:          return 1;   /* decimal */
        case 3: case 4:  return 2;   /* octal   */
        case 6:          return 3;   /* hexa    */
        default:         return 0;   /* error   */
    }
}
/* devuelve 1 si hubo error lexico, 0 si esta todo bien */
int contarPalabras(char* p, int* dec, int* oct, int* hex){
    *dec = *oct = *hex = 0;
    while(1){
        int tipo = esPalabra(p);
        if(tipo == 0) return 1;              /* token invalido: error */
        if(tipo == 1) (*dec)++;
        else if(tipo == 2) (*oct)++;
        else (*hex)++;

        while(*p != '@' && *p != '\0') p++;
        if(*p == '\0') return 0;             /* termino sin errores */
        p++;
    }
}

int main(){
    char vector1[] = "31004@010@0xff";
    char vector2[] = "05@+300@-40@0Xff@180";
    char vector3[] = "90@044@0@0xf@15";
    int dec, oct, hex;

    if(contarPalabras(vector1, &dec, &oct, &hex))
        printf("Error lexico\n");
    else
        printf("Dec: %d  Oct: %d  Hex: %d\n", dec, oct, hex);

    /* repetir para vector2 y vector3 */
    return 0;
}