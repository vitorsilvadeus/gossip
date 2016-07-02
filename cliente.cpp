#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h> 
 
#define ENTER 13
#define BUFFSIZE 2048

using namespace std;
 
void client(int porta)
{
	bool sair = false;
   	char buffer[BUFFSIZE];
	int descritor;
        const char *host = "vitor-X451MA";
	 
	struct sockaddr_in meuEndereco,enderecoRemoto;
	struct hostent *hp;//Informações do host
	socklen_t servlen = sizeof(enderecoRemoto);
	 
	//Criando o Socket
	 
	if ((descritor = socket(AF_INET, SOCK_STREAM,0)) < 0){

		cout << "\nErro na criação do socket" << endl;
		exit(0);

	}

	memset((char *)&meuEndereco, 0, sizeof(meuEndereco));//Deixa sinalizado que o S.O pode escolher o IP
	meuEndereco.sin_family = AF_INET;
	//atribui endereço IP ao socket tratando endianees do processador com relação a rede
	meuEndereco.sin_addr.s_addr = htonl(INADDR_ANY);
	meuEndereco.sin_port = htons(porta);//atribui numero de porta ao socket tratando endianees do processador com relação a rede

	if (bind(descritor, (struct sockaddr *)&meuEndereco, sizeof(meuEndereco)) < 0) {

		cout << "=>Erro ao vincular socket" << endl;

	}

	hp = gethostbyname(host);//pega o endereço do servidor a partir de seu nome
	
	if (!hp) {

        	cout << "=>Erro ao obter endereço de " << inet_ntoa(enderecoRemoto.sin_addr);
                exit(0);

	}
	//SOCKET DO SERVIDOR
	memset((char *) &enderecoRemoto, 0, sizeof(enderecoRemoto));
	enderecoRemoto.sin_family = AF_INET;
	enderecoRemoto.sin_port = htons(SERVICE_PORT);

	//Coloca o endereço do host na estrutura de endereço do server
	memcpy((void *)&enderecoRemoto.sin_addr, hp->h_addr_list[0], hp->h_length);

	

	do{
		//Envia a mensagem de inicio para o server
		sendto(descritor, "HELLO_SRV", strlen("HELLO_SRV"), 0, (struct sockaddr *)&enderecoRemoto, sizeof(enderecoRemoto));

	        //Recebe comfirmação do servidor
		recvfrom(descritor, buffer, BUFFSIZE, 0, (struct sockaddr *)&enderecoRemoto, &servlen);

	}while(strcmp(buffer,"HELLO_CLT"));
 	
	do {
		cout << "Cliente: ";
		do {
			cin >> buffer;
		    	sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, servlen);    
		    	if (!strcmp(buffer,"BYE_SRV")) {

				sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, servlen); 
				sair = true;
                                break;

		    	}
		} while (1);
		 
		cout << "Servidor: ";
		do {

		    	recvfrom(descritor, buffer, BUFFSIZE, 0, (struct sockaddr *)&enderecoRemoto, &servlen);
			cout << buffer << " ";

		    	if (!strcmp(buffer,"BYE_CLT")) {
				
				sair = true;
				break;
		    	}
	 
		} while (1);
 
    	} while (!sair);
 

        cout << "\n\n=> Fim de papo com" << host;
        close(descritor);
      
        exit(1);
}
