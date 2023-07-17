                        
#-------------- Declaracion de variables --------------
.data 
saltoLinea: .asciiz "\n"
zero: .float 0.0
var_0: .float 3.000
var_1: .float 4.000
var_2: .float 10.000
var_3: .float 0.500
var_4: .float 0.500
var_5: .float 10.000
var_6: .float 10.000

#--------------------- Ejecuciones ---------------------
.text
lwc1 $f31, zero
lwc1 $f1, var_0
lwc1 $f2, var_1
sub.s $f3, $f1, $f2
li $v0, 2
add.s $f12, $f31, $f3
mov.s $f30, $f12  #Movemos el registro 12 al 30 iniciado a false
syscall #Llamada al sistema
li $v0, 4
la $a0, saltoLinea
syscall #Llamada al sistema
lwc1 $f9, var_2
lwc1 $f10, var_3
mul.s $f11, $f9, $f10
li $v0, 2
add.s $f12, $f31, $f11
mov.s $f30, $f12  #Movemos el registro 12 al 30 iniciado a false
syscall #Llamada al sistema
li $v0, 4
la $a0, saltoLinea
syscall #Llamada al sistema
lwc1 $f18, var_4
lwc1 $f21, var_5
lwc1 $f24, var_6
div.s $f25, $f21, $f18
add.s $f26, $f24, $f25
li $v0, 2
add.s $f12, $f31, $f26
mov.s $f30, $f12  #Movemos el registro 12 al 30 iniciado a false
syscall #Llamada al sistema
li $v0, 4
la $a0, saltoLinea
syscall #Llamada al sistema
