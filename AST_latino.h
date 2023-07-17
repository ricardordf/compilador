// ----------------------------- GLOSARIO DE IMPORTS -------------------------------------------
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// ----------------------------- DECLARACION DE VARIABLES Y ESTRUCTURAS --------------------------------------------
extern FILE *yyout;
int contadorEtiqueta = 0;         // Variable para el control de las etiquetas 
int numMaxRegistros = 32;         // Variable que indica el numero maximo de registros disponibles
int nombreVariable = 0;           // Almacena el entero que se asociará al nombre de la variable


//Por defecto, tenemos 32 registros de tipo f para controlar los registros libres (true) o ocupados (false)
bool registros[32] = {[0 ... 29] = true, [30 ... 31] = true}; // Los registros 30 y 31 están reservados por defecto para imprimir por pantalla

// Estructura variable, se hará uso de la misma para almacenar y imprimir las variables del codigo latino
struct variable {
    float dato;
    int nombre; //limite de caracteres de la variable
    bool disponible;
};

struct variable variables[64]; // Declaramos el array de variables usando la estructura definida

// Estructura AST, se define la estructura de los nodos del arbol
struct ast
{
  struct ast *izq;     // Nodo izquierdo del arbol
  struct ast *dcha;    // Nodo derecho del arbol
  struct ast *aux;     // Nodo auxilar, para sentencias SI OSI SINO
  int tipoNodo;        // Almacena el tipo de nodo
  double valor;        // Almacena el valor del nodo 
  char *tipo;          // El tipo de dato que almacena: numericoDecimal, numerico o string
  int resultado;       // Registro donde está el resultado
  int nombreVar;       // Indica el nombre de la variable
};

//-----------------------------------------------  METODOS -------------------------------------------------------

// METODO "crearNombreVariable", incremente el valor de la variable "nombreVariable"
int crearNombreVariable(){
  return nombreVariable++; //retorna la variable y luego la incrementa
}

// METODO "comprobarValorNodo", se escribe el lenguaje máquina (por tipo de nodo) desde árbol completo generado al nivel del axioma de la gramática
// 
double comprobarValorNodo(struct ast *n, int contadorEtiquetaLocal)
{
  double dato;

  //TIPO NODO 1 - Nueva hoja en el arbol
  if (n->tipoNodo == 1) {
    dato = n->valor;
    printf("# [AST] - Registro $f%d ocupado para var_%d = %.3f \n", n->resultado, n->nombreVar, dato);
    fprintf(yyout, "lwc1 $f%d, var_%d\n", n->resultado, n->nombreVar);
  
  //TIPO NODO 2 - Nuevo comentario
  } else if (n->tipoNodo == 2) {
    dato = 0;

  //TIPO NODO 3 - Nueva suma
  }  else if (n->tipoNodo == 3) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) + comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# [AST] - El resultado de la suma se ha almacenado en $f%d\n", n->resultado);
    fprintf(yyout, "add.s $f%d, $f%d, $f%d\n", n->resultado, n->izq->resultado, n->dcha->resultado); //se utiliza add.s para + en ASM
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)

  //TIPO NODO 4 - Nueva resta
  } else if (n->tipoNodo == 4) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) - comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# [AST] - El resultado de la resta se ha almacenado en $f%d\n", n->resultado);
    fprintf(yyout, "sub.s $f%d, $f%d, $f%d\n", n->resultado, n->izq->resultado, n->dcha->resultado); //se utiliza sub.s para - en ASM
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)
  
  //TIPO NODO 5 - Nueva multiplicacion
  } else if (n->tipoNodo == 5) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) * comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# [AST] - El resultado de la multiplicacion se ha almacenado en $f%d\n", n->resultado); //se utiliza mul.s para * en ASM
    fprintf(yyout, "mul.s $f%d, $f%d, $f%d\n", n->resultado, n->izq->resultado, n->dcha->resultado);
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)

  //TIPO NODO 6 - Nueva division
  } else if (n->tipoNodo == 6) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) / comprobarValorNodo(n->dcha, contadorEtiquetaLocal); // base l expon r devuelve l^r
    printf("# [AST] - El resultado de la division se ha almacenado en $f%d\n", n->resultado);
    fprintf(yyout, "div.s $f%d, $f%d, $f%d\n", n->resultado, n->izq->resultado, n->dcha->resultado); //se utiliza div.s para / en ASM
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)
  
  //TIPO NODO 7 - Nuevo mayorque
  } else if (n->tipoNodo == 7) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) > comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# [AST] - El resultado del mayorque se ha almacenado en $f%d\n", n->resultado);
    fprintf(yyout, "c.lt.s $f%d, $f%d\n", n->dcha->resultado, n->izq->resultado); //se utiliza c.lt.s en ASM
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)
  
  //TIPO NODO 8 - Nuevo mayorigualque
  } else if (n->tipoNodo == 8) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) >= comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# [AST] - El resultado del mayorigualque se ha almacenado en $f%d\n", n->resultado);
    fprintf(yyout, "c.le.s $f%d, $f%d\n", n->dcha->resultado, n->izq->resultado); //se utiliza c.le.s en ASM
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)
  
  //TIPO NODO 9 - Nuevo menorque
  } else if (n->tipoNodo == 9) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) < comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# [AST] - El resultado del menorque se ha almacenado en $f%d\n", n->resultado);
    fprintf(yyout, "c.lt.s $f%d, $f%d\n", n->izq->resultado, n->dcha->resultado); //se utiliza c.lt.s en ASM intercambiando registro para el <
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)
  
  //TIPO NODO 10 - Nuevo menorigualque
  }  else if (n->tipoNodo == 10) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) <= comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# # [AST] - El resultado del menorigualque se ha almacenado en $f%d\n", n->izq->valor, n->dcha->valor, n->resultado, dato);
    fprintf(yyout, "c.le.s $f%d, $f%d\n", n->izq->resultado, n->dcha->resultado); //se utiliza c.le.s en ASM intercambiando registro para el <=
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)

  //TIPO NODO 11 - Nuevo igualque
  } else if (n->tipoNodo == 11) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal) == comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    printf("# [AST] - El resultado del igualque se ha almacenado en $f%d\n", n->resultado);
    fprintf(yyout, "c.eq.s $f%d, $f%d\n", n->izq->resultado, n->dcha->resultado); //se utiliza c.eq.s para == en ASM
    fprintf(yyout, "mov.s $f%d, $f%d\n", n->resultado, n->izq->resultado); 
    borrarReg(n->izq, n->dcha); //borrado de registros (se ponen a true)

  //TIPO NODO 12 - Nueva condicion
  } else if (n->tipoNodo == 12) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal);

  //TIPO NODO 13 - Nuevo SI
  } else if (n->tipoNodo == 13) {
    contadorEtiquetaLocal = contadorEtiqueta;
    contadorEtiqueta++; //Para que la siguiente sentencia 
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal); // las condiciones del IF en el nodo izquierdo
    fprintf(yyout, "bc1f si_%d\n", contadorEtiquetaLocal); //se utiliza bc1f para saltar a una etiqueta si no se cumple la condicion
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal); // las sentencias del IF en el nodo derecho
    fprintf(yyout, "si_%d:\n", contadorEtiquetaLocal);
 
  //TIPO NODO 14 - Nuevo SI + SINO
  } else if (n->tipoNodo == 14) {
    contadorEtiquetaLocal = contadorEtiqueta; contadorEtiqueta += 2;
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal); // las condiciones del IF en el nodo izquierdo
    fprintf(yyout, "bc1f sino_%d\n", contadorEtiquetaLocal); //Para saltar al ELSE cuando no se cumple la condicion del IF
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal); // las sentencias del IF en el nodo derecho  
    fprintf(yyout, "j sin_%d\n", contadorEtiquetaLocal + 1); // Al terminar las sentencias del IF tenemos que saltar a su etiqueta de cierre
    fprintf(yyout, "sino_%d:\n", contadorEtiquetaLocal);
    comprobarValorNodo(n->aux, contadorEtiquetaLocal); // las sentencias del ELSE en el nodo derecho
    fprintf(yyout, "sin_%d:\n", contadorEtiquetaLocal + 1);
  
  //TIPO NODO 15 Nuevo OSI
  }else if (n->tipoNodo == 15) {
    contadorEtiquetaLocal = contadorEtiqueta; contadorEtiqueta++;
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal); 
    fprintf(yyout, "bc1f osi_%d\n", contadorEtiquetaLocal);
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    fprintf(yyout, "osi_%d:\n", contadorEtiquetaLocal);
  
  //TIPO NODO 16 Nuevo SI + OSI encadenados (sigue la misma estructura que el SI + SINO)
  }else if (n->tipoNodo == 16) {
    contadorEtiquetaLocal = contadorEtiqueta; contadorEtiqueta += 2; 
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal); 
    fprintf(yyout, "bc1f osi_%d\n", contadorEtiquetaLocal);
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    fprintf(yyout, "j sin_%d\n", contadorEtiquetaLocal + 1);
    fprintf(yyout, "osi_%d:\n", contadorEtiquetaLocal);
    comprobarValorNodo(n->aux, contadorEtiquetaLocal);
    fprintf(yyout, "sin_%d:\n", contadorEtiquetaLocal + 1);
    
  //TIPO NODO 17 - Nuevo mientras
  }else if (n->tipoNodo == 17) {
    contadorEtiquetaLocal = contadorEtiqueta; contadorEtiqueta += 2;
    fprintf(yyout, "mientras_%d:\n", contadorEtiquetaLocal);   // volvemos a la primera etiqueta del mientras
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal);
    fprintf(yyout, "bc1f mientras_%d\n", contadorEtiquetaLocal + 1); 
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal); 
    fprintf(yyout, "j mientras_%d\n", contadorEtiquetaLocal);
    fprintf(yyout, "mientras_%d:\n", contadorEtiquetaLocal + 1);
  
  //TIPO NODO 18 - Nuevo imprimir
  } else if (n->tipoNodo == 18) {
    comprobarValorNodo(n->izq, contadorEtiquetaLocal);
    funcionImprimir(n->izq);

  //TIPO NODO 19 - Nueva asignación 
  }else if (n->tipoNodo == 19) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal);

  //TIPO NODO 20 - Nueva variable
  } else if (n->tipoNodo == 20) {
    dato = n->valor;

  //TIPO NODO 21 - Nuevo sobreescribir
  } else if (n->tipoNodo == 21) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal);
    printf("# [AST] - Moviendo registro $f%d al nuevo registro $f%d \n", n->izq->resultado, n->dcha->resultado);
    // Con la operación evaluada, se que en n->resultado esta el registro con el resultado
    // Movemos el nuevo resultado al registro original
    fprintf(yyout, "mov.s $f%d, $f%d\n", n->dcha->resultado, n->izq->resultado);
    
  //TIPO NODO 22 - Lista de sentencias
  } else if (n->tipoNodo == 22) {
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal); 
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal);   
  
  //TIPO NODO 23 - Nuevo operador Y
  } else if (n->tipoNodo == 23) {
    contadorEtiquetaLocal = contadorEtiqueta; contadorEtiqueta++;
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal);
    fprintf(yyout, "bc1f y_%d\n", contadorEtiquetaLocal); //Saltar al final del AND cuando sea falso
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    fprintf(yyout, "bc1f y_%d\n", contadorEtiquetaLocal); //Saltar al final del AND cuando sea falso
    fprintf(yyout, "y_%d:\n", contadorEtiquetaLocal); //Final del AND
  
  //TIPO NODO 24 - Nuevo operador O
  } else if (n->tipoNodo == 24) {
    contadorEtiquetaLocal = contadorEtiqueta; contadorEtiqueta++;
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal);
    fprintf(yyout, "bc1t o_%d\n", contadorEtiquetaLocal); //Saltar al final del AND cuando sea verdadero
    comprobarValorNodo(n->dcha, contadorEtiquetaLocal);
    fprintf(yyout, "bc1t o_%d\n", contadorEtiquetaLocal); //Saltar al final del AND cuando sea verdadero
    fprintf(yyout, "o_%d:\n", contadorEtiquetaLocal); //Final del OR
  
  }
    //TIPO NODO 25 - Nuevo operador NO
    /*else if (n->tipoNodo == 25) {
    fprintf(yyout,"#Entramos en operador NO\n");
    contadorEtiquetaLocal = contadorEtiqueta; contadorEtiqueta++;
    dato = comprobarValorNodo(n->izq, contadorEtiquetaLocal);
    fprintf(yyout, "bc1t sin_%d\n", contadorEtiquetaLocal);//Si se cumple saltar al IF más cercano
  }
  */
  return dato; //Devolvemos el valor
}

// METODO "comprobarAST", imprime el codigo .asm y generas sus respectivos pasos
comprobarAST(struct ast *n)
{
  imprimirVariables(); //Metodo que realiza la impresion de la parte de variables para Mips
  fprintf(yyout, "\n#--------------------- Ejecuciones ---------------------");
  fprintf(yyout, "\n.text\n");
  fprintf(yyout, "lwc1 $f31, zero\n");
  comprobarValorNodo(n, contadorEtiqueta); //Comprueba el valor del nodo
}

// METODO "imprimir", imprime el codigo .asm que hace referencia a la funcion imprimir de latino
funcionImprimir(struct ast *n)
{
  fprintf(yyout, "li $v0, 2\n"); //entero
  fprintf(yyout, "add.s $f12, $f31, $f%d\n", n->resultado); // Mover del registro n al registro 30 (es el que empleamos para imprimir)
  fprintf(yyout, "mov.s $f30, $f12  #Movemos el registro 12 al 30 iniciado a false\n");
  fprintf(yyout, "syscall #Llamada al sistema\n");
  saltoLinea(); //Introducimos un salto de linea
}

// METODO "imprimirVariables", imprime el archivo .asm la estructura del .data
// Recorrer los registros y devolver la posicion del primero que esté libre
imprimirVariables(){
  fprintf(yyout, "\n#-------------- Declaracion de variables --------------"); 
  fprintf(yyout, "\n.data \n");
  fprintf(yyout, "saltoLinea: .asciiz \"\\n\"\n"); //Variable salto de linea
  fprintf(yyout, "zero: .float 0.0\n"); //Se inserta una variable auxiliar var_0 con valor 0.000
  //Bucle que recorre el array de variables y las imprime en el archivo .asm
  for (int i = 0; i < 64; i++) {
      if(variables[i].disponible == true){
        fprintf(yyout, "var_%d: .float %.3f\n", variables[i].nombre, variables[i].dato);
      }
  }
}

// METODO "saltoLinea", incorpora un salto de linea en la salida de nuestro codigo
saltoLinea(){
	fprintf(yyout, "li $v0, 4\n");                      //especifica al registro $v0 que va a imprimir una cadena de caracteres
	fprintf(yyout, "la $a0, saltoLinea\n");             //carga en $a0 el valor del salto de linea
	fprintf(yyout, "syscall #Llamada al sistema\n");

}

// METODO "sinMemoria", comprueba si queda memoria disponible
sinMemoria(struct ast *n){
  if(!n){
    printf("\n---[ERROR MEMORIA]---\n");
    printf("TIPO DE ERROR: No hay memoria disponible!\n");
    printf("-------------\n");
    exit(0);
  }
  /*else{
    printf("No hay desbordamiento de memoria!\n");
  }*/
}

// METODO "encontrarReg", comprueba si el registro está libre y devuelve su posicion
// Recorrer los registros y devolver la posicion del primero que esté libre
encontrarReg()
{
  int posicion = 0;
  while (posicion <= (numMaxRegistros - 1) && registros[posicion] == 0) {  // registros[posicion] == 0, evita recorrer todo el array
    posicion++;
  }
  registros[posicion] = 0;
  return posicion; //retorna la posicion donde se encuentra el registro libre
}

// METODO "borrarReg", pone a true de nuevo el registro para que pueda volver a usarse
borrarReg(struct ast *izq, struct ast *dcha) { 
  registros[izq->resultado] = true; registros[dcha->resultado] = true; 
}

//METODO "crearNodoVacio", crea un nuevo nodo sin contenido
struct ast *crearNodoVacio()
{
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = NULL; n->dcha = NULL; n->tipoNodo = NULL; 
  return n;
}

// METODO "crearNodoTerminal", crear una nueva hoja en el arbol AST
struct ast *crearNodoTerminal(double valor)
{                   
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = NULL; n->dcha = NULL; n->tipoNodo = 1; n->valor = valor;
  n->resultado = encontrarReg(); //Hacemos llamada al metodo para buscar un nuevo registro
  n->nombreVar = crearNombreVariable();
  printf("# [AST] - Registro $f%d ocupado para var_%d = %.3f\n", n->resultado, n->nombreVar, n->valor);
  variables[n->resultado].dato = n->valor; variables[n->resultado].nombre = n->nombreVar; variables[n->resultado].disponible = true;
  return n;
}

// METODO "crearNodoNoTerminal", crea un nuevo nodo, asignamos sus hijos y tipo, y buscamos nuevo registro
struct ast *crearNodoNoTerminal(struct ast *izq, struct ast *dcha, int tipoNodo)
{     
  struct ast *n = malloc(sizeof(struct ast)); // Crea un nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = izq; n->dcha = dcha; n->tipoNodo = tipoNodo; // Asignamos al nodo genérico sus hijos y tipo
  n->resultado = encontrarReg(); //Hacemos llamada al metodo para buscar un nuevo registro
  return n;
}

// METODO "crearVariableTerminal", crear el nodo hoja para una variable ya creada
struct ast *crearVariableTerminal(double valor, int registro)
{                                               
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = NULL; n->dcha = NULL; n->tipoNodo = 20; n->valor = valor;
  n->resultado = registro;
  return n;
}

// METODO "crearNodoComentario", crear una nueva hoja para un comentario
struct ast *crearNodoComentario()
{                                               
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = NULL; n->dcha = NULL; n->tipoNodo = 2; n->valor = 0;
  return n;
}

// METODO "crearNodoSino", crear un nuevo nodo hoja para una sentencia SI + SINO
struct ast *crearNodoSino(struct ast *izq, struct ast *dcha, struct ast *aux)
{                                             
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = izq; n->dcha = dcha; n->tipoNodo = 14; n->aux = aux;
  n->resultado = encontrarReg();
  return n;
}

// METODO "crearNodoOsi", crear un nuevo nodo hoja para una sentencia SI + SINO
struct ast *crearNodoOsiEncadenado(struct ast *izq, struct ast *dcha, struct ast *aux)
{                                             
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = izq; n->dcha = dcha; n->tipoNodo = 16; n->aux = aux;
  n->resultado = encontrarReg();
  return n;
}

// METODO "crearNodoSobreescribir", crear un nuevo nodo hoja para sobreescribir el 
// registro de una variable ya declarada anteriormente
struct ast *crearNodoSobreescribir(int registro)
{
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = NULL; n->dcha = NULL; n->resultado = registro;
  return n;
}

// METODO "crearNodoY", crear un nuevo nodo AND
struct ast *crearNodoY(struct ast *izq, struct ast *dcha){
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = izq; n->dcha = dcha; n->tipoNodo = 23;
  return n;
}

// METODO "crearNodoO", crear un nuevo nodo de tipo OR
struct ast *crearNodoO(struct ast *izq, struct ast *dcha){
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = izq; n->dcha = dcha;
  n->tipoNodo = 24;
  return n;
}

// METODO "crearNodoNo", crear un nuevo nodo de tipo NOT 
struct ast *crearNodoNo(struct ast *izq){
  struct ast *n = malloc(sizeof(struct ast)); // Asigna memoria dinamicamente para el nuevo nodo
  /*sinMemoria(n); // La funcion comprueba si queda memoria disponible
  n->izq = izq; n->dcha = NULL; n->tipoNodo = 25;*/
  return n;
}