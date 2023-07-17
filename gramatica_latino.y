%{

// ----------------------------- GLOSARIO DE IMPORTS -------------------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tabla_simbolos.h"
#include "AST_latino.h"

// ----------------------------- DECLARACION DE VARIABLES Y ESTRUCTURAS -------------------------------------------

//Declaracion de variables "extern" sirve para declararlas como variables globales
FILE *yyout;
extern FILE* yyin;
extern int num_linea; //Almacena el numero de linea durante la ejecucion
extern tSimbolos tabla[256];
extern int indice; //Se almacena el índice de la tabla de tSimbolos
int contadorError = 0; //Almacena la cantidad de errores encontrados en la ejecucion
char* tipos[] = {"numerico", "numericoDecimal", "texto", "bool"}; //Para parsear el tipo que se detecta en flex al tipo del nodo


//-----------------------------------------------  METODOS -------------------------------------------------------

//Metodo que imprime la línea y el tipo de error
void errorRegistro(int resultado, int num_linea, int *contadorError, const char* info) {
    if (resultado == -1) {
        (*contadorError)++;
        printf("\n-------[ERROR REGISTRO]-------\n");
        printf("LINEA: %d \n", num_linea);
        printf("TIPO DE ERROR: %s \n", info);
        printf("---------------------\n");
    }
}

//Metodo de gestion de errores, se utiliza para los ELSE y otros
void erroresGenericos(int num_linea, int *contadorError, const char* info){
    (*contadorError)++;
    printf("\n-------[ERROR]-------\n");
    printf("LINEA: %d \n", num_linea);
    printf("TIPO DE ERROR: %s \n", info);
    printf("---------------------\n");
    exit(0); //Para la ejecucion
}

//Metodo de error, para controlar las divisiones entre 0
void errorDivision(int num_linea) {
    printf("\n-------[ERROR]-------\n");
    printf("LINEA: %d \n", num_linea);
    printf("TIPO DE ERROR: {algo / 0}\n");
    printf("---------------------\n");
    exit(0); //termina la ejecucion
}

//Metodo yyerror, generado por defecto
void yyerror(const char* s) {
    fprintf(stderr, "%s\n", s);
}


%}

/*Definicion de tipos y estructuras empleadas*/
%union {
  int enteroVal;
  float realVal;
  char* stringVal;
  struct atributos{
    int numerico;
    float numericoDecimal;
    char* texto;
    char* tipo;             //Define el tipo que se esta usando
    struct ast *n;          //Para almacenar los nodos del AST
  }tr;
}

/*Declaración de los TOKENS*/
%token COMENTARIO SUMA RESTA MULTIPLICACION DIVISION IGUAL MAYORQUE MENORQUE MAYORIGUALQUE MENORIGUALQUE IGUALQUE YLOGICO OLOGICO NOLOGICO APERTURAPARENTESIS CIERREPARENTESIS  SI OSI SINO MIENTRAS FIN IMPRIMIR  

/*Declaración de los TOKENS que provienen de FLEX con su respectivo tipo*/
%token <enteroVal> NUMERICO <realVal> NUMERICODECIMAL <stringVal> CADENA <stringVal> IDENTIFICADOR

/*Declaración de los TOKENS NO TERMINALES con su estructura*/
%type <tr> sentencias operacion tipos sentencia expresion asignacion condicional_si osi_encadenados condicional_osi bucle_mientras imprimir condiciones relacionales

/*Declaración de la precedencia siendo menor la del primero y mayor la del último*/
%left SUMA RESTA
%left MULTIPLICACION DIVISION  


%start codigo
%%

//-----------------------------------------------  PRODUCCIONES  -------------------------------------------------------

//PRODUCCION "codigo", formado por sentencias
//X --> S
codigo:
    sentencias  {
        if(contadorError != 0){ //Si la variable contadorError es distanta de 0, quiere decir que hay errores
            printf("\nSe han encontrado los siguientes errores: %d\n", contadorError);
        }
        else{  //en caso de no haber errores
            printf("\n *** NO se han encontrado errores! ***\n\n"); 
        }
        comprobarAST($1.n); 
        printf("\n[FINALIZADO]\n");     
    }
;

//PRODUCCION "sentencias", puede estar formado por una sentencia o un grupo de sentencias
//S --> D | S D
sentencias:
    sentencia
    | sentencias sentencia { //para hacerlo recursivo
        $$.n = crearNodoNoTerminal($1.n, $2.n, 22);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Sentencias - Lista de sentencias");
    }
;

//PRODUCCION "sentencia", puede estar formado por asignaciones, condicionales, bucles whiles, imprimir y comentarios
//D --> A | I | P | comentario | M
sentencia:   //Por defecto bison, asigna $1 a $$ por lo que no es obligatoria realizar la asignacion
    asignacion              
    | imprimir   
    | condicional_si 
    //En el comentario no se realiza ninguna accion, solo meterlo en el nodo del arbol        
    | COMENTARIO            { $$.n = crearNodoComentario(); printf("> [SENTENCIA] - Comentario\n");}
    | bucle_mientras        
;

//-------------------------------------------------------- ASIGNACION --------------------------------------------------------
//PRODUCCION "asignacion", formado por un identificador, un igual y una expresion
//A --> id = E 
asignacion:
    IDENTIFICADOR IGUAL expresion {
        printf("> [SENTENCIA] - Asignacion\n");
        //Aquí entra si ya está definido el simbolo
        if (buscarTabla(indice, $1, tabla) != -1) {  //Realiza la busqueda en la tabla de simbolos
            int pos = buscarTabla(indice, $1, tabla); //Declaramos una variable con el valor de la posicion del simbolos en la tabla
            printf("Modificado el valor de la variable: [%s]\n", tabla[pos].nombre); 
            if(strcmp($3.tipo, tipos[0]) == 0){ //comprobacion si es numerico
                tabla[pos].tipo = tipos[0]; tabla[pos].numerico = $3.numerico;
            }
            else if(strcmp($3.tipo, tipos[1]) == 0){ //comprobacion si es numericoDecimal
                tabla[pos].tipo = tipos[1]; tabla[pos].numericoDecimal = $3.numericoDecimal;
            }

            $$.n=crearNodoNoTerminal($3.n, crearNodoSobreescribir(tabla[pos].registro), 21);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - Asignacion");    

        }else{  //Creamos el nuevo simbolo ya que no se ha encontrado en la tabla de simbolos
                //En el ELSE entramos si el metodo buscarTabla devuelve -1

                //Para crear un nuevo simbolo de tipo numerico
                if(strcmp($3.tipo, tipos[0]) == 0){ //comprobacion si es numerico
                printf("Asignado el valor %d a la variable\n",$3.numerico);
                tabla[indice].nombre = $1; tabla[indice].tipo = tipos[0]; tabla[indice].numerico = $3.numerico; tabla[indice].registro = $3.n->resultado;
                indice++; //incrementamos el valor del inidice para pasar a la siguiente posicion y dejar la anterior guardada
                }

                //Para crear un nuevo simbolo de tipo numericoDecimal
                else if(strcmp($3.tipo, tipos[1]) == 0){ //comprobacion si es numericoDecimal
                printf("Asignado el valor %d a la variable\n",$3.numericoDecimal);
                tabla[indice].nombre = $1; tabla[indice].tipo = tipos[1]; tabla[indice].numericoDecimal = $3.numericoDecimal; tabla[indice].registro = $3.n->resultado;
                indice++; //incrementamos el valor del inidice para pasar a la siguiente posicion y dejar la anterior guardada
                }

            $$.n=crearNodoNoTerminal($3.n, crearNodoVacio(), 19);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - Asignacion - Nodo vacio");

        }
    }
;

//-------------------------------------------------------- BUCLE WHILE --------------------------------------------------------

//PRODUCCION "bucle_mientras", se representa la estructura del bucle mientras en latino
//M --> mientras ( C ) S fin
bucle_mientras:
    MIENTRAS APERTURAPARENTESIS condiciones CIERREPARENTESIS sentencias FIN {
        printf("> [SENTENCIA] - Mientras\n");
        //Llamamos a la funcion crearNodoTerminal y le pasamos os nodos y el numero que corresponde para el comprobarTipoNodo
        $$.n = crearNodoNoTerminal($3.n, $5.n, 17);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Bucle - Mientras");
    }
;

//-------------------------------------------------------- IF COMPLETO --------------------------------------------------------

//PRODUCCION "condicional_si", se contemplan todas las posibilidades
//P --> si ( C ) S fin | si ( C ) S sino S fin | si ( c ) S Y fin
condicional_si:

    //Estructura para el SI
    SI APERTURAPARENTESIS condiciones CIERREPARENTESIS sentencias FIN {
        printf("> [SENTENCIA] - SI\n");
        $$.n = crearNodoNoTerminal($3.n, $5.n, 13);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicional - SI");
        }

    //Estructura para el SI con SINO 
    | SI APERTURAPARENTESIS condiciones CIERREPARENTESIS sentencias SINO sentencias FIN {
        printf("> [SENTENCIA] - SI + SINO\n");
        $$.n = crearNodoSino($3.n, $5.n, $7.n); //llamada a metodo crearNodoSino que utiliza el nodo auxiliar
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicional - SI + SINO");
        }

    //Estructura para el SI con OSI
    | SI APERTURAPARENTESIS condiciones CIERREPARENTESIS sentencias osi_encadenados FIN  {
        printf("> [SENTENCIA] - SI + OSI\n");
        $$.n = crearNodoOsiEncadenado($3.n, $5.n, $6.n); //llamada a metodo crearNodoOsiEncandenado que utiliza el nodo auxiliar
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicional - SI + OSI");
        }
;

//PRODUCCION "condicional_osi", representa las estructura de OSI en latino
//Y --> osi ( C ) S 
condicional_osi: OSI APERTURAPARENTESIS condiciones CIERREPARENTESIS sentencias {
    printf("OSI\n");
    $$.n = crearNodoNoTerminal($3.n, $5.n, 15);
    errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicional - OSI");
    }
;

//PRODUCCION "osi_encandenados", se contemplan la posibilidades de un solo OSI o varios OSI encadenados
//Z --> Y | Z Y
osi_encadenados: condicional_osi | osi_encadenados condicional_osi  { printf("OSI ENCADENADOS\n"); }
;

//----------------------------------------------- CONDICIONES LOGICAS ---------------------------------------------
//PRODUCCION "condiciones", en esta gramática se representa las expresiones AND / OR / NOT
//C --> C oplogico R
condiciones: 

    //Operador AND logico
    condiciones YLOGICO relacionales {
        printf("+ Condicion YLOGICO &&\n");
        $$.n = crearNodoY($1.n, $3.n);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Logico - AND");
    }
    //Operador OR logico
    | condiciones OLOGICO relacionales {
        printf("+ Condicion OLOGICO ||\n");
        $$.n = crearNodoO($1.n, $3.n);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Logico - OR");
    }
    //Operador NOT logico
    | NOLOGICO relacionales {
        printf("+ Condicion NOLOGICO !\n");
        //$$.n = crearNodoNo($2.n);  //a probrar en el AST
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Logico - NOT");
    }
    //Puede estar formado por mas relacionaes
    | relacionales
;

//-----------------------------------------------  RELACIONALES ---------------------------------------------
//PRODUCCION "relacionales", en esta gramática se representa las expresiones > / < / >= / <= / ==
//Los operadores relaciones contemplan comparaciones entre numericos, es decir, enteros
//R --> E oprel E | ( R ) 
relacionales: 
    
    //Operador relacional >   
    expresion MAYORQUE expresion {
        printf("> [CONDICION] - MAYORQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp($1.tipo, tipos[2]) == 0 || strcmp($3.tipo, tipos[2]) == 0) { //verifica si $1.tipo o $3.tipo son iguales a numericoDecimal
            erroresGenericos(num_linea, &contadorError, "Condicion - MAYORQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            $$.n = crearNodoNoTerminal($1.n, $3.n, 7);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicion - MAYORQUE");
            $$.tipo = tipos[3];
        }  
    }

    //Operador relacional >= 
    | expresion MAYORIGUALQUE expresion {
        printf("> [CONDICION] - MAYORIGUALQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp($1.tipo, tipos[2]) == 0 || strcmp($3.tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - MAYORIGUALQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            $$.n = crearNodoNoTerminal($1.n, $3.n, 8);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicion - MAYORIGUALQUE");
            $$.tipo = tipos[3];
        }
    }

    //Operador relacional < 
    | expresion MENORQUE expresion   {
        printf("> [CONDICION] - MENORQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp($1.tipo, tipos[2]) == 0 || strcmp($3.tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - MENORQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            $$.n = crearNodoNoTerminal($1.n, $3.n, 9);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicion - MENORQUE");
            $$.tipo = tipos[3];
        }
    }

    //Operador relacional <= 
    | expresion MENORIGUALQUE expresion {
        printf("> [CONDICION] - MENORIGUALQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp($1.tipo, tipos[2]) == 0 || strcmp($3.tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - MENORIGUALQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            $$.n = crearNodoNoTerminal($1.n, $3.n, 10);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicion - MENORIGUALQUE");
            $$.tipo = tipos[3];
        }
    }

    //Operador relacional == 
    | expresion IGUALQUE expresion {
        printf("> [CONDICION] - IGUALQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp($1.tipo, tipos[2]) == 0 || strcmp($3.tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - IGUALQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            $$.n = crearNodoNoTerminal($1.n, $3.n, 11);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Condicion - IGUALQUE");
            $$.tipo = tipos[3];
        }
    }

    //Parenteris (), en latino no son obligatorios en las condiciones por ello se ponen como opcionales
    | APERTURAPARENTESIS relacionales CIERREPARENTESIS {
        $$ = $2; printf("\n> [RELACIONALES] - Parentesis: ( - )\n");}
;

//-----------------------------------------------  EXPRESION ---------------------------------------------
//PRODUCCION "expresion", en esta gramática se representa la suma, resta y otros terminos
//E --> E op O | O
expresion:
    
    //SUMA
    expresion SUMA operacion {

        //Suma de numerico + numerico
        if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[0]) == 0) { //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numerico / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 3); 
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - SUMAR numerico / numerico");
            $$.tipo = tipos[0]; $$.numerico = $1.numerico + $3.numerico;      
        }

        //Suma de numerico + numericoDecimal
        else if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numerico / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 3);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - SUMAR numerico / numericoDecimal");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numerico + $3.numericoDecimal;
        }

        //Suma de numericoDecimal + numericoDecimal
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numericoDecimal / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 3);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - SUMAR numericoDecimal / numericoDecimal");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numericoDecimal;
        }
        
        //Suma de numericoDecimal + numerico
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[0]) == 0){ //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numericoDecimal / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 3);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - SUMAR numericoDecimal / numerico");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "No se puede realizar la suma");
        }
    }
    //RESTA
    | expresion RESTA operacion {
        
        //Resta de numerico - numerico
        if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[0]) == 0) {  //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numerico / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 4);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - RESTAR numerico / numerico");
            $$.tipo = tipos[0]; $$.numerico = $1.numerico + $3.numerico;
        }

        //Resta de numerico - numericoDecimal
         else if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[1]) == 0){   //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numerico / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 4);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - RESTAR numerico / numericoDecimal");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numerico + $3.numericoDecimal;
        }

        //Resta de numericoDecimal - numericoDecimal
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numericoDecimal / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 4);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - RESTAR numericoDecimal / numericoDecimal");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numericoDecimal;
        }

        //Resta de numericoDecimal - numerico
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[0]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numericoDecimal / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 4);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - RESTAR numericoDecimal / numerico");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "No se puede realizar la resta");
        }
    }
    
    | operacion { $$ = $1; }  //una expresion puede ser un operacion, un subnivel para realizar la jerarquia de operaciones
;

//-----------------------------------------------  EXPRESION ---------------------------------------------
//PRODUCCION "terminoi", en esta gramática se representa la multiplicacion, division y otros tipos
//O --> O op K | K
operacion:

    //En el caso de que uno de los tipos sea numericoDecimal, el resultado se trata siempre como numericoDecimal
    //MULTIPLICACION
    operacion MULTIPLICACION tipos {
        //Multiplicacion de numerico * numerico
        if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[0]) == 0) { //comprobacion del tipo 
            printf("> [OPERACION] - MULTIPLICACION {numerico / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 5);            
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numerico / numerico");
            $$.tipo = tipos[0]; $$.numerico = $1.numerico + $3.numerico;
        }

        //Multiplicacion de numerico * numericoDecimal
        else if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - MULTIPLICACION {numerico / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 5);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numerico / numericoDecimal");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numerico + $3.numericoDecimal;
        }

        //Multiplicacion de numericoDecimal * numericoDecimal
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[1]) == 0){   //comprobacion del tipo
            printf("> [OPERACION] - MULTIPLICACION {numericoDecimal / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 5);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numericoDecimal / numericoDecimal");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numericoDecimal;
        }

        //Multiplicacion de numericoDecimal * numerico
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[0]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - MULTIPLICACION {numericoDecimal / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 5);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numericoDecimal / numerico");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "No se pueden multiplicar los operandos");
        }
    }

    //DIVISION
    | operacion DIVISION tipos {
        
        //CONTROL DE ERRORES - Division entre 0
        //EL primer IF / ELSE IF se utilizan para comprobar las divisiones entre 0
        if (strcmp($3.tipo, tipos[0]) == 0 && $3.numerico == 0) { //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {algo / 0}\n");
            errorDivision(num_linea); //llamada a metodo que devuelve el error y para la ejecucion
        }
        else if (strcmp($3.tipo, tipos[1]) == 0 && $3.numericoDecimal == 0) { //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {algo / 0.0}\n");
            errorDivision(num_linea); //llamada a metodo que devuelve el error y para la ejecucion
        }
        
        //Division de numerico / numerico
        else if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[0]) == 0) { //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numerico / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 6);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numerico / numerico");
            $$.tipo = tipos[0]; $$.numerico = $1.numerico + $3.numerico;
        }

        //Division de numerico / numericoDecimal
        else if (strcmp($1.tipo, tipos[0]) == 0 && strcmp($3.tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numerico / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 6); 
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numerico / numericoDecimal");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numerico + $3.numericoDecimal;
        }

        //Division de numericoDecimal / numericoDecimal
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numericoDecimal / numericoDecimal}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 6); 
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numericoDecimal / numericoDecimal"); 
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numericoDecimal;
        }
        
        //Division de numericoDecimal / numericoDecimal
        else if (strcmp($1.tipo, tipos[1]) == 0 && strcmp($3.tipo, tipos[0]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numericoDecimal / numerico}\n");
            $$.n = crearNodoNoTerminal($1.n, $3.n, 6); 
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numericoDecimal / numerico");
            $$.tipo = tipos[1]; $$.numericoDecimal = $1.numericoDecimal + $3.numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "Los datos proporcionados en la division no son validos");
        }
    }
    | tipos {$$ = $1;} //la produccion operacion puede ser tipos, un subnivel para realizar la jerarquia de operaciones
;

//-----------------------------------------------  TIPOS  ---------------------------------------------
/*PRODUCCION "tipos", en esta gramática se represetan los tipos de datos:
- identificadores (variables) - numeros enteros o decimales positivos o negativos
- cadenas de texto - estructura parentesis
K --> id | num | numnegativo | cadena | parentesis */
tipos: 
    IDENTIFICADOR {
        printf(" IDENTIFICADOR %s\n",$1);
        //Buscamos en la tabla el identificador
        if(buscarTabla(indice, $1, tabla) != -1){     //En este IF entra si buscarTabla devuelve la posicion
            int pos = buscarTabla(indice, $1, tabla);
            //Para si es de tipo numerico
            if(tabla[pos].tipo==tipos[0]){
                $$.tipo = tabla[pos].tipo; $$.numerico=tabla[pos].numerico; 
                $$.n = crearVariableTerminal(tabla[pos].numerico, tabla[pos].registro);  //Creamos un nodo terminal con los numeros   
            }
            //Para si es de tipo numericoDecimal
            else if(tabla[pos].tipo==tipos[1]){
                $$.tipo = tabla[pos].tipo; $$.numericoDecimal=tabla[pos].numericoDecimal;
                $$.n = crearVariableTerminal(tabla[pos].numericoDecimal, tabla[pos].registro); //Creamos un nodo terminal con los numeros        
            }
            //Para si es de tipo texto
            else if(tabla[pos].tipo==tipos[2]){
                $$.tipo = tabla[pos].tipo;
            }
            else{
                erroresGenericos(num_linea, &contadorError, "No se ha podido identificar la variable");
                }
        }
        else{  //Este ELSE entra cuando la variable no se ha definido previamente
            erroresGenericos(num_linea, &contadorError, "Variable no definida anteriormente");
        }
    }

    //Numero entero normal
    |NUMERICO {
        $$.numerico = $1;
        printf("\n> [TIPO] - Numerico Positivo: %ld\n", $$.numerico);
        $$.n = crearNodoTerminal($1);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Asignacion - NUMERICO"); 
        $$.tipo = tipos[0]; 
    }

    //Numero decimal normal
    | NUMERICODECIMAL {
        $$.numericoDecimal = $1;
        printf("\n> [TIPO] - NumericoDecimal: %.3f\n", $$.numericoDecimal); 
        $$.n = crearNodoTerminal($1);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Asignacion - NUMERICO DECIMAL"); 
        $$.tipo = tipos[1];  
    }

    //Numero entero negativo (se representa con el no terminal RESTA (-) mas el NUMERICO)
    | RESTA NUMERICO {
        $$.numerico = -$2;
        printf("\n> [TIPO] - Numerico Negativo: %ld\n", $$.numerico);
        $$.n = crearNodoTerminal(-$2);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Asignacion - RESTA NUMERICO");
        $$.tipo = tipos[0];
    }

    //Numero decimal negativo (se representa con el no terminal RESTA (-) mas el NUMERICODECIMAL)
    | RESTA NUMERICODECIMAL {
        $$.numericoDecimal = -$2;
        printf("\n> [TIPO] - NumericoDecimal Negativo: %.3f\n", $$.numericoDecimal);
        $$.n = crearNodoTerminal(-$2);
        errorRegistro($$.n->resultado, num_linea, &contadorError, "Asignacion - RESTA NUMERICO DECIMAL"); 
        $$.tipo = tipos[1];
    }

    //Cadena de texto - no se contemplan operaciones con ellas 
    | CADENA  {
        $$.texto = $1;
        printf("\n> [TIPO] - Cadena: %s\n", $$.texto);
        $$.tipo = tipos[2];
    }

    //Parenteris (), en latino no son obligatorios en las condiciones por ello se ponen como tipo
    | APERTURAPARENTESIS expresion CIERREPARENTESIS { $$ = $2; printf("\n> [TIPO] - Parentesis: ( - )\n"); }
;

//-----------------------------------------------  IMPRIMIR  ---------------------------------------------
//Representa la estructura del print en lenguaje latino
//I --> imprimir ( E ) 
imprimir: 
    IMPRIMIR APERTURAPARENTESIS expresion CIERREPARENTESIS { 
            printf("> [SENTENCIA] - Imprimir\n");
            $$.n = crearNodoNoTerminal($3.n, crearNodoVacio(), 18);
            errorRegistro($$.n->resultado, num_linea, &contadorError, "Operacion - Imprimir");         
        }
;

%% 

//--------------------------------------------------- METODO MAIN -----------------------------------------------
int main(int argc, char** argv) {
    yyin = fopen(argv[1], "rt");            //Apertura del archivo codigo.latino
    yyout = fopen( "./latino.asm", "wt" );  //Para el archivo .ASM con nombre "latino.asm"
	yyparse();
    fclose(yyin);
    return 0;
}
