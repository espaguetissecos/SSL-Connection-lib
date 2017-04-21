/*Required Headers*/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include "SSLlib.h"

int main()
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    char str[100];
    char cert1[100];
    char cert2[100];
    char cert3[100];
    char aux1[100]="";
    char buf[100]="ey";
    char message[1092];
    char *buffer = NULL;
    int listen_fd, comm_fd,salir=1;
    struct addrinfo hints, *res;
    SSL_CTX* ctx;
    SSL * ssl=NULL; 
    struct sockaddr_in ip4addr;
 
    //listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    strcpy(aux1,getenv("HOME"));
    sprintf(cert1, "./cert/root.pem");
    sprintf(cert2, "./cert/clientkey.pem");
    sprintf(cert3, "./cert/clientcert.pem");
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    printf("inicializar_nivel_SSL\n");
    fflush(stdout);
    ctx = inicializar_nivel_SSL(&sockfd);

    printf("fijar_contexto\n");
    fflush(stdout);
    fijar_contexto_SSL(ctx, cert1, cert2,cert3);
    
    printf("get_addrinfo\n");
        fflush(stdout);
    if(getaddrinfo("localhost", "8080", &hints, &res) != 0){
            return;
    }
    printf("conectar_canal_seguro_SSL\n");
    fflush(stdout);
    ssl=conectar_canal_seguro_SSL(ctx,sockfd,*(res->ai_addr));
    printf("evaluar_post_connectar_SSL\n");
    fflush(stdout);
    evaluar_post_connectar_SSL(ssl);
    //sockfd=socket(AF_INET,SOCK_STREAM,0);
    //bzero(&servaddr,sizeof servaddr);
    /*printf("recibir_datos_SSL\n");
    fflush(stdout);
    recibir_datos_SSL(ssl, buf);
    printf("enviar_datos_SSL\n");
    fflush(stdout);
    enviar_datos_SSL(ssl, buf);
    printf("cerrar\n");
    fflush(stdout);
    */
    while (salir) {

        printf("Introduce mensaje:");
        fgets(message, 8096, stdin);
        strcat(message, "\n\0");
        enviar_datos_SSL(ssl, message);
        recibir_datos_SSL(ssl, &buffer);
        message[strcspn(buffer, "\r\n\t")] = 0;
        printf("Mensaje recibido -> %s\n", buffer);
        printf("----------------------\n");
        if(strcmp(buffer,"exit")==0)
        	salir=0;
        free(buffer);
        buffer = NULL;
        fflush(stdout);
    }
    cerrar_canal_SSL(ssl,ctx,sockfd);
    freeaddrinfo(res);
/*
        
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);
 
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
 
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 
    while(1)
    {
        bzero( sendline, 100);
        bzero( recvline, 100);
        fgets(sendline,100,stdin); //stdin = 0 , for standard input 
 
        write(sockfd,sendline,strlen(sendline)+1);
        read(sockfd,recvline,100);
        printf("%s",recvline);
    }
*/
  
}
