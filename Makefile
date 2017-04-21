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

CC	= gcc

CFLAGS	= -Wall -g


DIR	= ~/G-2311-02-P3
TAR = G-2311-02-P3

#============================================================
# Archivos que componen el proyecto
#============================================================

EJECUTABLESSL = SSL
EJECUTABLE1	= server
EJECUTABLE2	= client
MAIN		= main.o
xchat2		= xchat2.o
CONNECTCLIENT   = connectClient.o
CONNECTSERVER   = connectServer.o
LIBS      	= -lircredes -lirctad -lpthread -lircinterface -lsoundredes -rdynamic -lcrypto -lssl
EXEC_NAME1 	= servidor
EXEC_NAME2 	= cliente
SRC			= src/
SRCLIB			= srclib/
INCL		= includes/
OBJ			= obj/
LIB		= lib/
SERVER	= server/
CLIENTE	= client/
CERTIF 		= cert/
CONTRASENYA	= Pareja02



all: dist $(EJECUTABLESSL) $(EJECUTABLE1) $(EJECUTABLE2) autores

server:    $(SERVER)$(OBJ)$(MAIN) $(SERVER)$(LIB)libConnectServer.a
	$(CC) -o $(EXEC_NAME1) $(SERVER)$(OBJ)$(MAIN) $(SERVER)$(LIB)libConnectServer.a $(LIBS)

client:    $(CLIENTE)$(OBJ)$(xchat2) $(CLIENTE)$(LIB)libClientFuncs.a
	$(CC) -o $(EXEC_NAME2) $(CLIENTE)$(OBJ)$(xchat2) `pkg-config --cflags gtk+-3.0` $(CLIENTE)$(LIB)libClientFuncs.a $(LIBS) `pkg-config --libs gtk+-3.0`


$(SERVER)$(OBJ)IRCcommands.o: $(SERVER)$(SRCLIB)IRCcommands.c
	$(CC) -c $< -o $@

$(SERVER)$(OBJ)SSLlib.o: $(SERVER)$(SRCLIB)SSLlib.c
	$(CC) -c $< -o $@

$(SERVER)$(OBJ)connectServer.o: $(SERVER)$(SRCLIB)connectServer.c
	$(CC) -c $< -o $@


$(SERVER)$(OBJ)main.o: $(SERVER)$(SRC)main.c
	$(CC) -c $< -o $@ 

$(SERVER)$(LIB)libConnectServer.a: $(SERVER)$(OBJ)connectServer.o $(SERVER)$(OBJ)IRCcommands.o $(SERVER)$(OBJ)SSLlib.o
	ar r $(SERVER)$(LIB)libConnectServer.a $(SERVER)$(OBJ)connectServer.o $(SERVER)$(OBJ)IRCcommands.o $(SERVER)$(OBJ)SSLlib.o
	
$(CLIENTE)$(OBJ)xchat2.o: $(CLIENTE)$(SRC)xchat2.c
	$(CC) -c $< -o $@ `pkg-config --cflags gtk+-3.0` -I./$(CLIENTE)includes/

$(CLIENTE)$(OBJ)clientfuncs.o: $(CLIENTE)$(SRCLIB)clientfuncs.c
	$(CC) -c $< -o $@ `pkg-config --cflags gtk+-3.0` -I./$(CLIENTE)includes/

$(CLIENTE)$(OBJ)SSLlib.o: $(CLIENTE)$(SRCLIB)SSLlib.c
	$(CC) -c $< -o $@ `pkg-config --cflags gtk+-3.0` -I./$(CLIENTE)includes/

$(CLIENTE)$(LIB)libClientFuncs.a: $(CLIENTE)$(OBJ)clientfuncs.o $(CLIENTE)$(OBJ)SSLlib.o
	ar r $(CLIENTE)$(LIB)libClientFuncs.a $(CLIENTE)$(OBJ)clientfuncs.o $(CLIENTE)$(OBJ)SSLlib.o
	
#===========================================================
# Generación de certificado y claves
#===========================================================
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
	
	
#============================================================
# Crea un archivo .tgz para distribuir el codigo
#============================================================
##Crea un archivo .tgz elmininando previamente el codigo objeto

dist: clean
	#@ cp $(DIR)/Makefile $(DIR)/G-2311-02-P1-makefile
	tar -cvf $(TAR).tar.gz ../$(TAR)


#============================================================
# Limpia los ficheros temporales
#============================================================

clean:
	#rm -f $(EXEC_NAME) $(MAIN) $(CONNECTSERVER)
	rm -f $(EXEC_NAME1) all $(SERVER)$(OBJ)*.o $(SERVER)$(LIB)*.a $(DIR)/*~ core $(DIR)/Makefile
	rm -f $(EXEC_NAME2) all $(CLIENTE)$(OBJ)*.o $(CLIENTE)$(LIB)*.a $(DIR)/*~ core $(DIR)/Makefile
	rm -f all $(CERTIF)*.pem $(CERTIF)*.srl
#============================================================
# Mensaje que aparece al ejecutar el MAKE, y que ayuda a identificar
# a los autores del trabajo
#============================================================

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
