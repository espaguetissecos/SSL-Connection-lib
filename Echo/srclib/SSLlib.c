#include "SSLlib.h"

SSL_CTX* inicializar_nivel_SSL(int* sockfd){
    SSL_CTX* ret;
    
	SSL_load_error_strings();	
	SSL_library_init();
        ret =  SSL_CTX_new(SSLv23_method());
	ERR_print_errors_fp(stdout);
        *sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	return ret;
}

int fijar_contexto_SSL(SSL_CTX* ctx, const char* CAfile, const char* prvKeyFile,const char* certFile){
        
        char buf[1024]; 
        char CApath [1024];
  SSL_CTX_set_verify(ctx,SSL_VERIFY_PEER,NULL);
  
        sprintf(CApath, "%s%s", getcwd(buf, sizeof(buf)), "/cert/");       
        if (!SSL_CTX_load_verify_locations(ctx,CAfile,CApath))
		return 0;
	SSL_CTX_set_default_verify_paths(ctx);
	if(!SSL_CTX_use_certificate_chain_file(ctx, certFile)){
		return 0;
	}

        /*Verificamos la clave*/
	SSL_CTX_use_PrivateKey_file(ctx, prvKeyFile, SSL_FILETYPE_PEM);
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
	
	ERR_print_errors_fp(stdout);
	return 1;


}

SSL* conectar_canal_seguro_SSL(SSL_CTX* ctx,int sockfd,struct sockaddr res){
	SSL * ssl=NULL;
	int cnct=0;
	
        cnct= connect(sockfd, &res, sizeof(res));
	if (cnct==-1)
		return NULL;
	ssl=SSL_new(ctx);
	if(!SSL_set_fd(ssl, sockfd))
		return NULL;
	if(!SSL_connect(ssl))
		return NULL;
	ERR_print_errors_fp(stdout);
	return ssl;


}
SSL* aceptar_canal_seguro_SSL(SSL_CTX* ctx,int sockfd,int puerto,int tam,struct sockaddr_in ip4addr){
	SSL* ssl;
	int clientsocket=0;
        int listn;
        int ret;
	struct sockaddr_in addraux;
int addrlen;
	addraux.sin_family = AF_INET;
	addraux.sin_port = htons(puerto);
	addraux.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd, (struct sockaddr*)&addraux, sizeof(addraux))==-1)
		return NULL;        
	listn = listen(sockfd, tam);
        addrlen =sizeof(ip4addr);
	clientsocket=accept(sockfd, (struct sockaddr*)&ip4addr, (socklen_t*)&addrlen);
	
        
        
        ssl=SSL_new(ctx);
	
        if(ssl==NULL)
		return NULL;
	if(!SSL_set_fd(ssl, clientsocket))
		return NULL;
	ret=SSL_accept(ssl);
        if(!ret)
		return NULL;
	SSL_get_error(ssl,ret);
        ERR_print_errors_fp(stdout);

        
        
	return ssl;



}
int evaluar_post_connectar_SSL(SSL * ssl){
	if(SSL_get_peer_certificate(ssl)==NULL)
		return 0;
	if(SSL_get_verify_result(ssl)!=X509_V_OK)
		return 0;
	return 1;
}

int enviar_datos_SSL(SSL * ssl,const char * buf){
	if(!ssl || !buf)
		return -1;

    return SSL_write(ssl, buf, strlen(buf));
}

int recibir_datos_SSL(SSL * ssl, char ** buf){
	int size=8096;
	if(!ssl)
		return -1;
	if((*buf) == NULL)
		*buf = (char *) malloc(size * sizeof(char));
	else
		*buf = (char *) realloc(*buf, size * sizeof(char));

	if(*buf == NULL)
		return -1;

	return SSL_read(ssl, *buf, size);
}

void cerrar_canal_SSL(SSL *ssl,SSL_CTX *ctx, int sockfd){
	int check;
	while(!(check=SSL_shutdown(ssl))){
		if(check==-1)
			return;
	}
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	
        close(sockfd);
}
