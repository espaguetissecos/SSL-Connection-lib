/*Required Headers*/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include "SSLlib.h"

int main()
{
 
    char str[100];
    char cert1[100];
    char cert2[100];
    char cert3[100];
    char aux1[100]="";
    char buf[100]="ey";
    char * buffer = NULL;
    int listen_fd, comm_fd, status,i=0,salir=1;
    int sockfd=0;
    SSL_CTX* ctx;
    SSL * ssl=NULL; 
    struct sockaddr_in ip4addr;
 
    //listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    sprintf(cert1, "./cert/root.pem");
    sprintf(cert2, "./cert/serverkey.pem");
    sprintf(cert3, "./cert/servercert.pem");
    
    //bzero( &servaddr, sizeof(servaddr));
 
    //servaddr.sin_family = AF_INET;
    //servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    //servaddr.sin_port = htons(22000);
    
    ctx = inicializar_nivel_SSL(&sockfd); 
    fijar_contexto_SSL(ctx, cert1,cert2,cert3);
    ssl=aceptar_canal_seguro_SSL(ctx,sockfd,8080,80,ip4addr);
    
    //bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    //listen(listen_fd, 10);
    //comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
    if(!evaluar_post_connectar_SSL(ssl)){
        ERR_print_errors_fp(stdout);
        return;
    }
    /*enviar_datos_SSL(ssl,buf);
    recibir_datos_SSL(ssl, buf);
    */
    while(salir){
		status = recibir_datos_SSL(ssl, &buffer);
		for(i = (strlen(buffer) - 1); buffer[i] != '\n'; i--);
		buffer[i + 1] = '\0';

		fflush(stdout);
		if (status > 0){
			fflush(stdout);
			enviar_datos_SSL(ssl, buffer);
		}
        if(strcmp(buffer,"exit")==0)
        	salir=0;
		free(buffer);
		buffer = NULL;
	}
    cerrar_canal_SSL(ssl,ctx,sockfd);

/*
 
    while(1)
    {
 
        bzero( str, 100);
 
        read(comm_fd,str,100);
 
        printf("Echoing back - %s",str);
 
        write(comm_fd, str, strlen(str)+1);
 
    }
*/
}
