#============================================================
# Proyecto: REDES II
# Fichero: Makefile
# Fecha: 02/04/2016
# Descripcion: Makefile
# Integrantes: Francisco Andreu Sanz, Javier Martínez Hernández
#============================================================

#============================================================
# Entorno de desarrollo y opciones
#============================================================

# Compilador
CC	= gcc
# Opciones de compilacion
## -wall: indica que se muestren todas las advertencias al compilar
## -g: genera informacion de depuracion
CFLAGS	= -Wall -g

## Sirve para la generacion del archivo de distribucion
DIR	= ~/servidorEcho
TAR = servidorEcho

#============================================================
# Archivos que componen el proyecto
#============================================================

EJECUTABLES	= SSL client server
client		= client.o
server 		= server.o

CONNECTSERVER   = connectClient.o
LIBS      	= -lpthread -lssl -lcrypto
EXEC_NAME_CLIENT 	= client
EXEC_NAME_SERVER 	= server
SRC			= src/
SRCLIB			= srclib/
INCL		= includes/
OBJ			= obj/
LIB		= lib/
CERTIF 		= cert/
CONTRASENYA	= Pareja02
#============================================================
#Construccion de los ejecutables
#============================================================

all: dist $(EJECUTABLES) autores

client:    $(OBJ)$(client) $(LIB)libSSLlib.a
	$(CC) -o $(EXEC_NAME_CLIENT) $(OBJ)$(client) $(LIB)libSSLlib.a $(LIBS)

server:    $(OBJ)$(server) $(LIB)libSSLlib.a
	$(CC) -o $(EXEC_NAME_SERVER) $(OBJ)$(server) $(LIB)libSSLlib.a $(LIBS)

#============================================================
# Generacion de los .o                                       
#============================================================
## Para cada archivo .c se genera un .o
## Un archivo .o depende del archivo .c y todos los .h propios que se incluyan en el .c

#main.o: $(INCL)connectServer.h $(SRC)main.c
#	@echo Compilando main.c...
	#$(CC) $(CFLAGS) -c -lircredes $(SRC)main.c

$(OBJ)$(client): $(SRC)client.c
	$(CC) -c $< -o $@ -I./includes/ $(LIBS)

$(OBJ)$(server): $(SRC)server.c
	$(CC) -c $< -o $@ -I./includes/ $(LIBS)

$(OBJ)SSLlib.o: $(SRCLIB)SSLlib.c
	$(CC) -c $< -o $@ -I./includes/ $(LIBS)

$(LIB)libSSLlib.a: $(OBJ)SSLlib.o
	ar r $(LIB)libSSLlib.a $(OBJ)SSLlib.o 
#============================================================
# Crea un archivo .tgz para distribuir el codigo
#============================================================
##Crea un archivo .tgz elmininando previamente el codigo objeto

dist: clean
	#@ cp $(DIR)/Makefile $(DIR)/G-2311-02-P1-makefile


#============================================================
# Limpia los ficheros temporales
#============================================================

clean:
	#rm -f $(EXEC_NAME) $(MAIN) $(CONNECTSERVER)
	rm -f $(EXEC_NAME_CLIENT)  $(EXEC_NAME_SERVER) all $(OBJ)*.o $(CERTIF)*
#============================================================
# Mensaje que aparece al ejecutar el MAKE, y que ayuda a identificar
# a los autores del trabajo
#============================================================

SSL:
	clear
	@echo "/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"
	@echo "Creacion del certif."
	@echo "/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"
	openssl genrsa -out $(CERTIF)rootkey.pem 2048
	openssl req -new -x509 -key $(CERTIF)rootkey.pem -out $(CERTIF)rootcert.pem -subj "/C=ES/ST=MADRID/L=MADRID/O=UAM/CM=CERTIFICATE/CN=Javier"
	cat $(CERTIF)rootcert.pem $(CERTIF)rootkey.pem > $(CERTIF)root.pem
	openssl x509 -subject -issuer -noout -in $(CERTIF)root.pem

#Cliente
	openssl genrsa -out $(CERTIF)clientkey.pem 2048
	openssl req -new -key $(CERTIF)clientkey.pem -out $(CERTIF)clientreq.pem -subj "/C=ES/ST=MADRID/L=MADRID/O=UAM/CM=CERTIFICATE/CN=Javi"
	openssl x509 -req -in $(CERTIF)clientreq.pem -CA $(CERTIF)root.pem -CAkey $(CERTIF)root.pem -CAcreateserial -out $(CERTIF)clientcert.pem
	cat $(CERTIF)clientcert.pem $(CERTIF)clientkey.pem $(CERTIF)rootcert.pem > $(CERTIF)client.pem
	openssl x509 -subject -issuer -noout -in $(CERTIF)client.pem

#Servidor
	openssl genrsa -out $(CERTIF)serverkey.pem 2048
	openssl req -new -key $(CERTIF)serverkey.pem -out $(CERTIF)serverreq.pem -subj "/C=ES/ST=MADRID/L=MADRID/O=UAM/CM=CERTIFICATE/CN=Javi"
	openssl x509 -req -in $(CERTIF)serverreq.pem -CA $(CERTIF)root.pem -CAkey $(CERTIF)root.pem -CAcreateserial -out $(CERTIF)servercert.pem
	cat $(CERTIF)servercert.pem $(CERTIF)serverkey.pem $(CERTIF)rootcert.pem > $(CERTIF)server.pem
	openssl x509 -subject -issuer -noout -in $(CERTIF)server.pem


autores:
	@echo "-----------------------------------------------------------------------"
	@echo "Practica Redes2 grupo 2311 desarrollado por el equipo 02 compuesto por:"
	@echo "Andreu Sanz, Francisco y Martínez Hernández, Javier"
	@echo "-----------------------------------------------------------------------"

#============================================================
# Ayuda
#============================================================

ayuda:
	@echo Uso: make [objetivo]
	@echo "make \t\t Make all"
	@echo "make dist \t Genera el archivo de distribucion .tgz"
	@echo "make limpia \t Limpia los ficheros temporales"
