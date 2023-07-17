/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "gramatica_latino.y"


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




/* Line 189 of yacc.c  */
#line 136 "gramatica_latino.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMENTARIO = 258,
     SUMA = 259,
     RESTA = 260,
     MULTIPLICACION = 261,
     DIVISION = 262,
     IGUAL = 263,
     MAYORQUE = 264,
     MENORQUE = 265,
     MAYORIGUALQUE = 266,
     MENORIGUALQUE = 267,
     IGUALQUE = 268,
     YLOGICO = 269,
     OLOGICO = 270,
     NOLOGICO = 271,
     APERTURAPARENTESIS = 272,
     CIERREPARENTESIS = 273,
     SI = 274,
     OSI = 275,
     SINO = 276,
     MIENTRAS = 277,
     FIN = 278,
     IMPRIMIR = 279,
     NUMERICO = 280,
     NUMERICODECIMAL = 281,
     CADENA = 282,
     IDENTIFICADOR = 283
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 65 "gramatica_latino.y"

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



/* Line 214 of yacc.c  */
#line 215 "gramatica_latino.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 227 "gramatica_latino.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   127

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNRULES -- Number of states.  */
#define YYNSTATES  84

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    24,    31,    38,    47,    55,    61,    63,    66,    70,
      74,    77,    79,    83,    87,    91,    95,    99,   103,   107,
     111,   113,   117,   121,   123,   125,   127,   129,   132,   135,
     137,   141
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      30,     0,    -1,    31,    -1,    32,    -1,    31,    32,    -1,
      33,    -1,    43,    -1,    35,    -1,     3,    -1,    34,    -1,
      28,     8,    40,    -1,    22,    17,    38,    18,    31,    23,
      -1,    19,    17,    38,    18,    31,    23,    -1,    19,    17,
      38,    18,    31,    21,    31,    23,    -1,    19,    17,    38,
      18,    31,    37,    23,    -1,    20,    17,    38,    18,    31,
      -1,    36,    -1,    37,    36,    -1,    38,    14,    39,    -1,
      38,    15,    39,    -1,    16,    39,    -1,    39,    -1,    40,
       9,    40,    -1,    40,    11,    40,    -1,    40,    10,    40,
      -1,    40,    12,    40,    -1,    40,    13,    40,    -1,    17,
      39,    18,    -1,    40,     4,    41,    -1,    40,     5,    41,
      -1,    41,    -1,    41,     6,    42,    -1,    41,     7,    42,
      -1,    42,    -1,    28,    -1,    25,    -1,    26,    -1,     5,
      25,    -1,     5,    26,    -1,    27,    -1,    17,    40,    18,
      -1,    24,    17,    40,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   115,   116,   125,   126,   127,   129,   130,
     137,   182,   197,   204,   211,   220,   229,   229,   238,   244,
     250,   256,   266,   279,   292,   305,   318,   331,   341,   379,
     417,   427,   465,   513,   522,   551,   560,   569,   578,   587,
     594,   601
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMENTARIO", "SUMA", "RESTA",
  "MULTIPLICACION", "DIVISION", "IGUAL", "MAYORQUE", "MENORQUE",
  "MAYORIGUALQUE", "MENORIGUALQUE", "IGUALQUE", "YLOGICO", "OLOGICO",
  "NOLOGICO", "APERTURAPARENTESIS", "CIERREPARENTESIS", "SI", "OSI",
  "SINO", "MIENTRAS", "FIN", "IMPRIMIR", "NUMERICO", "NUMERICODECIMAL",
  "CADENA", "IDENTIFICADOR", "$accept", "codigo", "sentencias",
  "sentencia", "asignacion", "bucle_mientras", "condicional_si",
  "condicional_osi", "osi_encadenados", "condiciones", "relacionales",
  "expresion", "operacion", "tipos", "imprimir", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    29,    30,    31,    31,    32,    32,    32,    32,    32,
      33,    34,    35,    35,    35,    36,    37,    37,    38,    38,
      38,    38,    39,    39,    39,    39,    39,    39,    40,    40,
      40,    41,    41,    41,    42,    42,    42,    42,    42,    42,
      42,    43
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     6,     6,     8,     7,     5,     1,     2,     3,     3,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     1,     1,     1,     2,     2,     1,
       3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     8,     0,     0,     0,     0,     0,     2,     3,     5,
       9,     7,     6,     0,     0,     0,     0,     1,     4,     0,
       0,     0,    35,    36,    39,    34,     0,    21,     0,    30,
      33,     0,     0,     0,    10,    37,    38,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    27,    40,    18,    19,     0,
      28,    29,    22,    24,    23,    25,    26,    31,    32,     0,
       0,     0,    12,    16,     0,    11,     0,     0,    14,    17,
       0,    13,     0,    15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    11,    73,    74,    26,
      27,    28,    29,    30,    12
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -41
static const yytype_int8 yypact[] =
{
      47,   -41,    -9,    -6,     0,    32,    43,    47,   -41,   -41,
     -41,   -41,   -41,    56,    56,    60,    60,   -41,   -41,    20,
      73,    73,   -41,   -41,   -41,   -41,    -8,   -41,   114,    12,
     -41,    79,    60,     9,    52,   -41,   -41,   -41,    14,   104,
      73,    73,    47,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    47,    11,   -41,   -41,   -41,   -41,   -41,     2,
      12,    12,    52,    52,    52,    52,    52,   -41,   -41,    25,
      34,    47,   -41,   -41,    18,   -41,    56,    36,   -41,   -41,
      88,   -41,    47,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -40,    -7,   -41,   -41,   -41,   -20,   -41,   -13,
      71,   -12,    24,    29,   -41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      18,    31,    59,    33,    34,     1,    40,    41,    13,    39,
      42,    14,    69,    43,    44,    43,    44,    15,    50,    51,
      53,     2,    70,    71,     3,    72,     4,    54,     1,    56,
       5,    77,    55,    62,    63,    64,    65,    66,    70,     1,
      16,    78,    83,    17,     2,    35,    36,     3,    75,     4,
       1,    76,    18,     5,    79,     2,    43,    44,     3,    81,
       4,    19,    18,    80,     5,    19,     2,    60,    61,     3,
      18,     4,    20,    21,     0,     5,    18,    32,    19,    67,
      68,    22,    23,    24,    25,    22,    23,    24,    25,     0,
      21,    37,    38,    40,    41,     0,     0,    52,    22,    23,
      24,    25,    40,    41,     0,     0,    82,     0,    43,    44,
       0,    57,    58,    45,    46,    47,    48,    49,    43,    44,
       0,     0,    56,    45,    46,    47,    48,    49
};

static const yytype_int8 yycheck[] =
{
       7,    14,    42,    15,    16,     3,    14,    15,    17,    21,
      18,    17,    52,     4,     5,     4,     5,    17,     6,     7,
      32,    19,    20,    21,    22,    23,    24,    18,     3,    18,
      28,    71,    18,    45,    46,    47,    48,    49,    20,     3,
       8,    23,    82,     0,    19,    25,    26,    22,    23,    24,
       3,    17,    59,    28,    74,    19,     4,     5,    22,    23,
      24,     5,    69,    76,    28,     5,    19,    43,    44,    22,
      77,    24,    16,    17,    -1,    28,    83,    17,     5,    50,
      51,    25,    26,    27,    28,    25,    26,    27,    28,    -1,
      17,    20,    21,    14,    15,    -1,    -1,    18,    25,    26,
      27,    28,    14,    15,    -1,    -1,    18,    -1,     4,     5,
      -1,    40,    41,     9,    10,    11,    12,    13,     4,     5,
      -1,    -1,    18,     9,    10,    11,    12,    13
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    19,    22,    24,    28,    30,    31,    32,    33,
      34,    35,    43,    17,    17,    17,     8,     0,    32,     5,
      16,    17,    25,    26,    27,    28,    38,    39,    40,    41,
      42,    38,    17,    40,    40,    25,    26,    39,    39,    40,
      14,    15,    18,     4,     5,     9,    10,    11,    12,    13,
       6,     7,    18,    40,    18,    18,    18,    39,    39,    31,
      41,    41,    40,    40,    40,    40,    40,    42,    42,    31,
      20,    21,    23,    36,    37,    23,    17,    31,    23,    36,
      38,    23,    18,    31
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 100 "gramatica_latino.y"
    {
        if(contadorError != 0){ //Si la variable contadorError es distanta de 0, quiere decir que hay errores
            printf("\nSe han encontrado los siguientes errores: %d\n", contadorError);
        }
        else{  //en caso de no haber errores
            printf("\n *** NO se han encontrado errores! ***\n\n"); 
        }
        comprobarAST((yyvsp[(1) - (1)].tr).n); 
        printf("\n[FINALIZADO]\n");     
    ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 116 "gramatica_latino.y"
    { //para hacerlo recursivo
        (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (2)].tr).n, (yyvsp[(2) - (2)].tr).n, 22);
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Sentencias - Lista de sentencias");
    ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 129 "gramatica_latino.y"
    { (yyval.tr).n = crearNodoComentario(); printf("> [SENTENCIA] - Comentario\n");;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 137 "gramatica_latino.y"
    {
        printf("> [SENTENCIA] - Asignacion\n");
        //Aquí entra si ya está definido el simbolo
        if (buscarTabla(indice, (yyvsp[(1) - (3)].stringVal), tabla) != -1) {  //Realiza la busqueda en la tabla de simbolos
            int pos = buscarTabla(indice, (yyvsp[(1) - (3)].stringVal), tabla); //Declaramos una variable con el valor de la posicion del simbolos en la tabla
            printf("Modificado el valor de la variable: [%s]\n", tabla[pos].nombre); 
            if(strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0){ //comprobacion si es numerico
                tabla[pos].tipo = tipos[0]; tabla[pos].numerico = (yyvsp[(3) - (3)].tr).numerico;
            }
            else if(strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){ //comprobacion si es numericoDecimal
                tabla[pos].tipo = tipos[1]; tabla[pos].numericoDecimal = (yyvsp[(3) - (3)].tr).numericoDecimal;
            }

            (yyval.tr).n=crearNodoNoTerminal((yyvsp[(3) - (3)].tr).n, crearNodoSobreescribir(tabla[pos].registro), 21);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - Asignacion");    

        }else{  //Creamos el nuevo simbolo ya que no se ha encontrado en la tabla de simbolos
                //En el ELSE entramos si el metodo buscarTabla devuelve -1

                //Para crear un nuevo simbolo de tipo numerico
                if(strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0){ //comprobacion si es numerico
                printf("Asignado el valor %d a la variable\n",(yyvsp[(3) - (3)].tr).numerico);
                tabla[indice].nombre = (yyvsp[(1) - (3)].stringVal); tabla[indice].tipo = tipos[0]; tabla[indice].numerico = (yyvsp[(3) - (3)].tr).numerico; tabla[indice].registro = (yyvsp[(3) - (3)].tr).n->resultado;
                indice++; //incrementamos el valor del inidice para pasar a la siguiente posicion y dejar la anterior guardada
                }

                //Para crear un nuevo simbolo de tipo numericoDecimal
                else if(strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){ //comprobacion si es numericoDecimal
                printf("Asignado el valor %d a la variable\n",(yyvsp[(3) - (3)].tr).numericoDecimal);
                tabla[indice].nombre = (yyvsp[(1) - (3)].stringVal); tabla[indice].tipo = tipos[1]; tabla[indice].numericoDecimal = (yyvsp[(3) - (3)].tr).numericoDecimal; tabla[indice].registro = (yyvsp[(3) - (3)].tr).n->resultado;
                indice++; //incrementamos el valor del inidice para pasar a la siguiente posicion y dejar la anterior guardada
                }

            (yyval.tr).n=crearNodoNoTerminal((yyvsp[(3) - (3)].tr).n, crearNodoVacio(), 19);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - Asignacion - Nodo vacio");

        }
    ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 182 "gramatica_latino.y"
    {
        printf("> [SENTENCIA] - Mientras\n");
        //Llamamos a la funcion crearNodoTerminal y le pasamos os nodos y el numero que corresponde para el comprobarTipoNodo
        (yyval.tr).n = crearNodoNoTerminal((yyvsp[(3) - (6)].tr).n, (yyvsp[(5) - (6)].tr).n, 17);
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Bucle - Mientras");
    ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 197 "gramatica_latino.y"
    {
        printf("> [SENTENCIA] - SI\n");
        (yyval.tr).n = crearNodoNoTerminal((yyvsp[(3) - (6)].tr).n, (yyvsp[(5) - (6)].tr).n, 13);
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicional - SI");
        ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 204 "gramatica_latino.y"
    {
        printf("> [SENTENCIA] - SI + SINO\n");
        (yyval.tr).n = crearNodoSino((yyvsp[(3) - (8)].tr).n, (yyvsp[(5) - (8)].tr).n, (yyvsp[(7) - (8)].tr).n); //llamada a metodo crearNodoSino que utiliza el nodo auxiliar
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicional - SI + SINO");
        ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 211 "gramatica_latino.y"
    {
        printf("> [SENTENCIA] - SI + OSI\n");
        (yyval.tr).n = crearNodoOsiEncadenado((yyvsp[(3) - (7)].tr).n, (yyvsp[(5) - (7)].tr).n, (yyvsp[(6) - (7)].tr).n); //llamada a metodo crearNodoOsiEncandenado que utiliza el nodo auxiliar
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicional - SI + OSI");
        ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 220 "gramatica_latino.y"
    {
    printf("OSI\n");
    (yyval.tr).n = crearNodoNoTerminal((yyvsp[(3) - (5)].tr).n, (yyvsp[(5) - (5)].tr).n, 15);
    errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicional - OSI");
    ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 229 "gramatica_latino.y"
    { printf("OSI ENCADENADOS\n"); ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 238 "gramatica_latino.y"
    {
        printf("+ Condicion YLOGICO &&\n");
        (yyval.tr).n = crearNodoY((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n);
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Logico - AND");
    ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 244 "gramatica_latino.y"
    {
        printf("+ Condicion OLOGICO ||\n");
        (yyval.tr).n = crearNodoO((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n);
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Logico - OR");
    ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 250 "gramatica_latino.y"
    {
        printf("+ Condicion NOLOGICO !\n");
        //$$.n = crearNodoNo($2.n);  //a probrar en el AST
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Logico - NOT");
    ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 266 "gramatica_latino.y"
    {
        printf("> [CONDICION] - MAYORQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[2]) == 0 || strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[2]) == 0) { //verifica si $1.tipo o $3.tipo son iguales a numericoDecimal
            erroresGenericos(num_linea, &contadorError, "Condicion - MAYORQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 7);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicion - MAYORQUE");
            (yyval.tr).tipo = tipos[3];
        }  
    ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 279 "gramatica_latino.y"
    {
        printf("> [CONDICION] - MAYORIGUALQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[2]) == 0 || strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - MAYORIGUALQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 8);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicion - MAYORIGUALQUE");
            (yyval.tr).tipo = tipos[3];
        }
    ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 292 "gramatica_latino.y"
    {
        printf("> [CONDICION] - MENORQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[2]) == 0 || strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - MENORQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 9);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicion - MENORQUE");
            (yyval.tr).tipo = tipos[3];
        }
    ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 305 "gramatica_latino.y"
    {
        printf("> [CONDICION] - MENORIGUALQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[2]) == 0 || strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - MENORIGUALQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 10);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicion - MENORIGUALQUE");
            (yyval.tr).tipo = tipos[3];
        }
    ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 318 "gramatica_latino.y"
    {
        printf("> [CONDICION] - IGUALQUE\n");
        //Las expresiones solo pueden ser de tipo numerico, con que uno de los dos sea numericoDecimal, ya saltariamos al metodo de error
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[2]) == 0 || strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[2]) == 0) {  //comprobacion del tipo
            erroresGenericos(num_linea, &contadorError, "Condicion - IGUALQUE");
        } else { //son de tipo numerico, por lo que si podemos continuar
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 11);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Condicion - IGUALQUE");
            (yyval.tr).tipo = tipos[3];
        }
    ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 331 "gramatica_latino.y"
    {
        (yyval.tr) = (yyvsp[(2) - (3)].tr); printf("\n> [RELACIONALES] - Parentesis: ( - )\n");;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 341 "gramatica_latino.y"
    {

        //Suma de numerico + numerico
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0) { //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numerico / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 3); 
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - SUMAR numerico / numerico");
            (yyval.tr).tipo = tipos[0]; (yyval.tr).numerico = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numerico;      
        }

        //Suma de numerico + numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numerico / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 3);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - SUMAR numerico / numericoDecimal");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }

        //Suma de numericoDecimal + numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numericoDecimal / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 3);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - SUMAR numericoDecimal / numericoDecimal");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }
        
        //Suma de numericoDecimal + numerico
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0){ //comprobacion del tipo
            printf("> [OPERACION] - SUMA {numericoDecimal / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 3);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - SUMAR numericoDecimal / numerico");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "No se puede realizar la suma");
        }
    ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 379 "gramatica_latino.y"
    {
        
        //Resta de numerico - numerico
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0) {  //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numerico / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 4);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - RESTAR numerico / numerico");
            (yyval.tr).tipo = tipos[0]; (yyval.tr).numerico = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numerico;
        }

        //Resta de numerico - numericoDecimal
         else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){   //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numerico / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 4);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - RESTAR numerico / numericoDecimal");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }

        //Resta de numericoDecimal - numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numericoDecimal / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 4);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - RESTAR numericoDecimal / numericoDecimal");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }

        //Resta de numericoDecimal - numerico
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - RESTA {numericoDecimal / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 4);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - RESTAR numericoDecimal / numerico");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "No se puede realizar la resta");
        }
    ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 417 "gramatica_latino.y"
    { (yyval.tr) = (yyvsp[(1) - (1)].tr); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 427 "gramatica_latino.y"
    {
        //Multiplicacion de numerico * numerico
        if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0) { //comprobacion del tipo 
            printf("> [OPERACION] - MULTIPLICACION {numerico / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 5);            
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numerico / numerico");
            (yyval.tr).tipo = tipos[0]; (yyval.tr).numerico = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numerico;
        }

        //Multiplicacion de numerico * numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - MULTIPLICACION {numerico / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 5);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numerico / numericoDecimal");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }

        //Multiplicacion de numericoDecimal * numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){   //comprobacion del tipo
            printf("> [OPERACION] - MULTIPLICACION {numericoDecimal / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 5);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numericoDecimal / numericoDecimal");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }

        //Multiplicacion de numericoDecimal * numerico
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - MULTIPLICACION {numericoDecimal / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 5);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - MULTIPLICAR numericoDecimal / numerico");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "No se pueden multiplicar los operandos");
        }
    ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 465 "gramatica_latino.y"
    {
        
        //CONTROL DE ERRORES - Division entre 0
        //EL primer IF / ELSE IF se utilizan para comprobar las divisiones entre 0
        if (strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0 && (yyvsp[(3) - (3)].tr).numerico == 0) { //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {algo / 0}\n");
            errorDivision(num_linea); //llamada a metodo que devuelve el error y para la ejecucion
        }
        else if (strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0 && (yyvsp[(3) - (3)].tr).numericoDecimal == 0) { //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {algo / 0.0}\n");
            errorDivision(num_linea); //llamada a metodo que devuelve el error y para la ejecucion
        }
        
        //Division de numerico / numerico
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0) { //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numerico / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 6);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numerico / numerico");
            (yyval.tr).tipo = tipos[0]; (yyval.tr).numerico = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numerico;
        }

        //Division de numerico / numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[0]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numerico / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 6); 
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numerico / numericoDecimal");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numerico + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }

        //Division de numericoDecimal / numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[1]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numericoDecimal / numericoDecimal}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 6); 
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numericoDecimal / numericoDecimal"); 
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numericoDecimal;
        }
        
        //Division de numericoDecimal / numericoDecimal
        else if (strcmp((yyvsp[(1) - (3)].tr).tipo, tipos[1]) == 0 && strcmp((yyvsp[(3) - (3)].tr).tipo, tipos[0]) == 0){  //comprobacion del tipo
            printf("> [OPERACION] - DIVISION {numericoDecimal / numerico}\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(1) - (3)].tr).n, (yyvsp[(3) - (3)].tr).n, 6); 
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - DIVIDIR numericoDecimal / numerico");
            (yyval.tr).tipo = tipos[1]; (yyval.tr).numericoDecimal = (yyvsp[(1) - (3)].tr).numericoDecimal + (yyvsp[(3) - (3)].tr).numerico;
        }
        else{
            erroresGenericos(num_linea, &contadorError, "Los datos proporcionados en la division no son validos");
        }
    ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 513 "gramatica_latino.y"
    {(yyval.tr) = (yyvsp[(1) - (1)].tr);;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 522 "gramatica_latino.y"
    {
        printf(" IDENTIFICADOR %s\n",(yyvsp[(1) - (1)].stringVal));
        //Buscamos en la tabla el identificador
        if(buscarTabla(indice, (yyvsp[(1) - (1)].stringVal), tabla) != -1){     //En este IF entra si buscarTabla devuelve la posicion
            int pos = buscarTabla(indice, (yyvsp[(1) - (1)].stringVal), tabla);
            //Para si es de tipo numerico
            if(tabla[pos].tipo==tipos[0]){
                (yyval.tr).tipo = tabla[pos].tipo; (yyval.tr).numerico=tabla[pos].numerico; 
                (yyval.tr).n = crearVariableTerminal(tabla[pos].numerico, tabla[pos].registro);  //Creamos un nodo terminal con los numeros   
            }
            //Para si es de tipo numericoDecimal
            else if(tabla[pos].tipo==tipos[1]){
                (yyval.tr).tipo = tabla[pos].tipo; (yyval.tr).numericoDecimal=tabla[pos].numericoDecimal;
                (yyval.tr).n = crearVariableTerminal(tabla[pos].numericoDecimal, tabla[pos].registro); //Creamos un nodo terminal con los numeros        
            }
            //Para si es de tipo texto
            else if(tabla[pos].tipo==tipos[2]){
                (yyval.tr).tipo = tabla[pos].tipo;
            }
            else{
                erroresGenericos(num_linea, &contadorError, "No se ha podido identificar la variable");
                }
        }
        else{  //Este ELSE entra cuando la variable no se ha definido previamente
            erroresGenericos(num_linea, &contadorError, "Variable no definida anteriormente");
        }
    ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 551 "gramatica_latino.y"
    {
        (yyval.tr).numerico = (yyvsp[(1) - (1)].enteroVal);
        printf("\n> [TIPO] - Numerico Positivo: %ld\n", (yyval.tr).numerico);
        (yyval.tr).n = crearNodoTerminal((yyvsp[(1) - (1)].enteroVal));
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Asignacion - NUMERICO"); 
        (yyval.tr).tipo = tipos[0]; 
    ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 560 "gramatica_latino.y"
    {
        (yyval.tr).numericoDecimal = (yyvsp[(1) - (1)].realVal);
        printf("\n> [TIPO] - NumericoDecimal: %.3f\n", (yyval.tr).numericoDecimal); 
        (yyval.tr).n = crearNodoTerminal((yyvsp[(1) - (1)].realVal));
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Asignacion - NUMERICO DECIMAL"); 
        (yyval.tr).tipo = tipos[1];  
    ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 569 "gramatica_latino.y"
    {
        (yyval.tr).numerico = -(yyvsp[(2) - (2)].enteroVal);
        printf("\n> [TIPO] - Numerico Negativo: %ld\n", (yyval.tr).numerico);
        (yyval.tr).n = crearNodoTerminal(-(yyvsp[(2) - (2)].enteroVal));
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Asignacion - RESTA NUMERICO");
        (yyval.tr).tipo = tipos[0];
    ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 578 "gramatica_latino.y"
    {
        (yyval.tr).numericoDecimal = -(yyvsp[(2) - (2)].realVal);
        printf("\n> [TIPO] - NumericoDecimal Negativo: %.3f\n", (yyval.tr).numericoDecimal);
        (yyval.tr).n = crearNodoTerminal(-(yyvsp[(2) - (2)].realVal));
        errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Asignacion - RESTA NUMERICO DECIMAL"); 
        (yyval.tr).tipo = tipos[1];
    ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 587 "gramatica_latino.y"
    {
        (yyval.tr).texto = (yyvsp[(1) - (1)].stringVal);
        printf("\n> [TIPO] - Cadena: %s\n", (yyval.tr).texto);
        (yyval.tr).tipo = tipos[2];
    ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 594 "gramatica_latino.y"
    { (yyval.tr) = (yyvsp[(2) - (3)].tr); printf("\n> [TIPO] - Parentesis: ( - )\n"); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 601 "gramatica_latino.y"
    { 
            printf("> [SENTENCIA] - Imprimir\n");
            (yyval.tr).n = crearNodoNoTerminal((yyvsp[(3) - (4)].tr).n, crearNodoVacio(), 18);
            errorRegistro((yyval.tr).n->resultado, num_linea, &contadorError, "Operacion - Imprimir");         
        ;}
    break;



/* Line 1464 of yacc.c  */
#line 2081 "gramatica_latino.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 608 "gramatica_latino.y"
 

//--------------------------------------------------- METODO MAIN -----------------------------------------------
int main(int argc, char** argv) {
    yyin = fopen(argv[1], "rt");            //Apertura del archivo codigo.latino
    yyout = fopen( "./latino.asm", "wt" );  //Para el archivo .ASM con nombre "latino.asm"
	yyparse();
    fclose(yyin);
    return 0;
}

