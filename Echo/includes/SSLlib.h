/*************************************************************
* Proyecto: REDES II
* Fichero: SSLLIB.h
* Fecha: 04/02/2016
* Descripcion: Declaracion de las cabeceras y definiciones del proyecto
* Integrantes: Francisco Andreu Sanz, Javier Martínez Hernández
*************************************************************/

#ifndef SSLLIB_H_
#define SSLLIB_H_ 

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <openssl/rand.h>
#include <openssl/x509v3.h>
#include <openssl/ssl.h>

/**
 *
 * @brief Inicializa protocolo SSL
 * @page inicializar_nivel_SSL \b inicializar_nivel_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b SSL_CTX* \b inicializar_nivel_SSL \b (\b int * sock\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Esta función se encargará de inicializar las librerías SSL así
 * como crear el socket.
 *
 * @section return RETURN
 * Devuelve el Context si sale bien, o NULL en otro caso.
 *	
 * @section seealso VER TAMBIÉN
 * \b fijar_contexto_SSL(3), \b conectar_canal_seguro_SSL(3), \b aceptar_canal_seguro_SSL(3),
 * \b evaluar_post_connectar_SSL(3), \b enviar_datos_SSL(3), \b  recibir_datos_SSL(3), \b cerrar_canal_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
SSL_CTX* inicializar_nivel_SSL(int * sock);

/**
 *
 * @brief fija el contexto de una conexion SSL
 * @page fijar_contexto_SSL \b fijar_contexto_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b int \b fijar_contexto_SSL \b (\b SSL_CTX* ctx, \b const char* CAfile, 
 * \b const char* prvKeyFile, \b const char* certFile\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Esta función se encargará de inicializar correctamente el contexto que será utilizado para
 * la creación de canales seguros mediante SSL. 
 *
 * @section return RETURN
 * Devuelve 1 si sale bien, o 0 en otro caso.
 *	
 * @section seealso VER TAMBIÉN
 * \b inicializar_nivel_SSL(3), \b conectar_canal_seguro_SSL(3), \b aceptar_canal_seguro_SSL(3),
 * \b evaluar_post_connectar_SSL(3), \b enviar_datos_SSL(3), \b  recibir_datos_SSL(3), \b cerrar_canal_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
int fijar_contexto_SSL(SSL_CTX* ctx, const char* CAfile, const char* prvKeyFile,const char* certFile);

/**
 *
 * @brief realiza la conexion mediante SSL. Solo desde el cliente
 * @page conectar_canal_seguro_SSL \b conectar_canal_seguro_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b SSL* \b conectar_canal_seguro_SSL \b (\b SSL_CTX* ctx, \b int sockfd, 
 * \b struct sockaddr res \b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Teniendo un contexto SSL y un socket esta función se encargará de
 * obtener un canal de comunicacion seguro SSL con el handshake.
 *
 * @section return RETURN
 * Devuelve instancia SSL* si sale bien, o NULL en otro caso.
 *	
 * @section seealso VER TAMBIÉN
 * \b inicializar_nivel_SSL(3), \b fijar_contexto_SSL(3), \b aceptar_canal_seguro_SSL(3),
 * \b evaluar_post_connectar_SSL(3), \b enviar_datos_SSL(3), \b  recibir_datos_SSL(3), \b cerrar_canal_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
SSL* conectar_canal_seguro_SSL(SSL_CTX* ctx,int sock,struct sockaddr res);

/**
 *
 * @brief monta un servidor TCP con conexion SSL
 * @page aceptar_canal_seguro_SSL \b aceptar_canal_seguro_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b SSL* \b aceptar_canal_seguro_SSL \b (\b SSL_CTX* ctx, \b cint sockfd, \b int puerto, \b int tam,
 *  \b struct sockaddr_in ip4addr\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Dado un contexto SSL y un descriptor de socket esta función se encargará de
 * las llamadas a bind, listen y accept, todo ello siguiendo el prot. SSL
 *
 * @section return RETURN
 *  Devuelve NULL en caso de error o la estructura SSL* inicializada  en caso de exito.
 *	
 * @section seealso VER TAMBIÉN
 * \b inicializar_nivel_SSL(3), \b fijar_contexto_SSL(3), \bconectar_canal_seguro_SSL(3), \b evaluar_post_connectar_SSL(3),
 * \b enviar_datos_SSL(3), \b  recibir_datos_SSL(3), \b cerrar_canal_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
SSL* aceptar_canal_seguro_SSL(SSL_CTX* ctx,int sockfd,int puerto,int tam,struct sockaddr_in ip4addr);

/**
 *
 * @brief fija el contexto de una conexion SSL
 * @page evaluar_post_connectar_SSL \b evaluar_post_connectar_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b int \b evaluar_post_connectar_SSL \b (\b SSL* ssl\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Esta función comprobará que el canal de co-
 * municación se puede establecer(y de forma segura).
 *
 * @section return RETURN
 * Devuelve 0 en caso de error o 1 en caso de exito  .
 *	
 * @section seealso VER TAMBIÉN
 * \b inicializar_nivel_SSL(3), \b conectar_canal_seguro_SSL(3), \b aceptar_canal_seguro_SSL(3),
 * \b fijar_contexto_SSL(3), \b enviar_datos_SSL(3), \b  recibir_datos_SSL(3), \b cerrar_canal_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
int evaluar_post_connectar_SSL(SSL * ssl);

/**
 *
 * @brief Envia datos de forma segura con SSL
 * @page enviar_datos_SSL \b enviar_datos_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b int \b enviar_datos_SSL \b (\b SSL* ssl, \b char* buf, 
 * \b const char* prvKeyFile, \b const char* certFile\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Esta función será el equivalente a la función de envío de mensajes que se realizó en la
 * práctica 1(Serv.IRC) o 2, pero será utilizada para enviar datos a través del canal seguro. Es importante que sea genérica y
 * pueda ser utilizada independientemente de los datos que se vayan a enviar.
 *
 * @section return RETURN
 * Devuelve 0 en caso de error o 1 en caso de exito  .
 *	
 * @section seealso VER TAMBIÉN
 * \b inicializar_nivel_SSL(3), \b conectar_canal_seguro_SSL(3), \b aceptar_canal_seguro_SSL(3),
 * \b evaluar_post_connectar_SSL(3), \b enviar_datos_SSL(3), \b  recibir_datos_SSL(3), \b cerrar_canal_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
int enviar_datos_SSL(SSL * ssl,const char * buf);

/**
 *
 * @brief recibe datos mediante el socket de com. con SSL
 * @page recibir_datos_SSL \b recibir_datos_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b int \b recibir_datos_SSL \b (\b SSL* buff, \b char* buf \b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Esta función será el equivalente al RECV que se realizó en la
 * práctica 1(Serv.IRC) o 2, pero será utilizada para enviar datos a través del canal seguro.
 *
 * @section return RETURN
 * Devuelve 0 en caso de error o 1 en caso de exito  .
 *	
 * @section seealso VER TAMBIÉN
 * \b inicializar_nivel_SSL(3), \b fijar_contexto_SSL(3), \b conectar_canal_seguro_SSL(3), \b aceptar_canal_seguro_SSL(3),
 * \b evaluar_post_connectar_SSL(3), \b enviar_datos_SSL(3), \b   cerrar_canal_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
int recibir_datos_SSL(SSL * ssl, char ** buf);

/**
 *
 * @brief cierra el canal de com. SSL
 * @page cerrar_canal_SSL \b fijar_contexto_SSL
 *
 * @section SYNOPSIS
 * 	\b #include \b "SSLlib.h"
 *
 *	\b void \b cerrar_canal_SSL \b (\b SSL_CTX* ctx, \b SSL* ssl, 
 * \b int sockfd\b )
 * 
 * @section descripcion DESCRIPCIÓN
 *	
 * Esta función liberará todos los recursos y cerrará el canal de comunicación seguro creado
 * previamente.
 *
 * @section return RETURN
 * void
 *	
 * @section seealso VER TAMBIÉN
 * \b inicializar_nivel_SSL(3), \b fijar_contexto_SSL(3), \b conectar_canal_seguro_SSL(3), \b aceptar_canal_seguro_SSL(3),
 * \b evaluar_post_connectar_SSL(3), \b enviar_datos_SSL(3), \b  recibir_datos_SSL(3) \b
 * @section authors AUTOR
 * Francisco Andreu Sanz (francisco.andreu@estudiante.uam.es)
 * Javier Martinez Hernandez (javier.martinez@estudiante.uam.es)
*/
void cerrar_canal_SSL(SSL *ssl,SSL_CTX *ctx, int sockfd);


#endif /* SSLLIB_H_ */
