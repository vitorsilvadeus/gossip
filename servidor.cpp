#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
 
using namespace std;
 
int cliente(int porta)
{

 	struct sockaddr_in meuEndereco;	//Meu endereço
	struct sockaddr_in enderecoRemoto;//Endereço remoto
	int descritor;// descritor do socket 
	char buf[BUFSIZE];//buffer para troca de mensagens


	//criando um socket UDP

	if ((descritor = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Erro ao criar socket\n");
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&meuEndereco, 0, sizeof(meuEndereco));
	meuEndereco.sin_family = AF_INET;
	meuEndereco.sin_addr.s_addr = htonl(INADDR_ANY);
	meuEndereco.sin_port = htons(porta);

	if (bind(descritor, (struct sockaddr *)&meuEndereco, sizeof(meuEndereco)) < 0) {

		perror("Erro ao criar socket");

	}

	do{
		//Recebe comfirmação do cliente
		recvfrom(descritor, buffer, BUFLEN, 0, (struct sockaddr *)&enderecoRemoto, &servlen);
	}while(strcmp(buffer,"HELLO_SRV"))
 
                
	sendto(descritor, "HELLO_CLT", strlen("HELLO_CLT"), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    	cout << "Cliente: ";
        do {

            recvfrom(descritor, buffer, BUFLEN, 0, (struct sockaddr *)&enderecoRemoto, &servlen);

            cout << buffer << " ";

            if (*buffer == 27){
                
                sair = true;
		break;
            }
        } while (1);
 
        do {
            cout << "\nServidor: ";
            do {

                cin >> buffer;

                sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, servlen);
          
                if (*buffer == ESC) {

                    sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, servlen);              
                    isExit = true;
                    break;

                }
            } while (1);
 
            cout << "Cliente: ";
            do {

                recvfrom(descritor, buffer, BUFLEN, 0, (struct sockaddr *)&enderecoRemoto, &servlen);

                cout << buffer << " ";

                if (*buffer == ESC) {
                  
                    isExit = true;
		    break;

                }
            } while (1);
        } while (!sair);
  
    cout << "\n=> Fim de papo!!!.";
 
    close(descritor);
}



