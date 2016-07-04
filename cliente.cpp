#include "gossip.h"
using namespace std;
 
void cliente(int porta)
{
	bool sair = false;
   	char buffer[BUFFSIZE];
	int descritor;
        char hello_clt[10] = "HELLO_CLT";
        char hello_srv[10] = "HELLO_SRV";
        char bye_srv[10] = "BYE_SRV\n";
        char bye_clt[10] = "BYE_CLT\n";
	 
	struct sockaddr_in meuEndereco;
	socklen_t cltlen;
	 
	//Criando o Socket
	 
	if ((descritor = socket(AF_INET, SOCK_DGRAM,0)) < 0){

		cout << "\nErro na criação do socket" << endl;
		exit(0);

	}

	meuEndereco.sin_family = AF_INET;
	//atribui endereço IP ao socket tratando endianees do processador com relação a rede
	meuEndereco.sin_addr.s_addr = htonl(INADDR_ANY);
	meuEndereco.sin_port = htons(porta);//atribui numero de porta ao socket tratando endianees do processador com relação a rede
        

	bzero(buffer,BUFFSIZE);

	
	do{		
                //Envia a mensagem de inicio para o server
		sendto(descritor, hello_srv, strlen(hello_srv) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));

	        //Recebe comfirmação do servidor
                cltlen = sizeof(struct sockaddr_in);
		recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&meuEndereco, &cltlen);
       
	}while(strcmp(buffer,hello_clt));

 	cout << "Handshake completo com o servidor" << endl;
        cout << "*************************** Servidor ***********************" << endl;

	do {
		cout << "\nCliente: ";
			
		//Limpa o buffer
                bzero(buffer,BUFFSIZE);
		cin >> buffer;
                sendto(descritor, buffer, strlen(buffer) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));    

	 	if (!strcmp(buffer,bye_srv)) {

			sendto(descritor, buffer, strlen(buffer) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));
			sair = true;

		}
		 
		cout << "\nServidor: ";
                cltlen = sizeof(struct sockaddr_in);
		recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&meuEndereco, &cltlen);
		cout << buffer << " ";

		if (!strcmp(buffer,bye_clt)) {
				
			sair = true;
		    	
		}
 
    	} while (!sair);
 

        cout << "\n\n=> Fim de papo!" << endl;
        close(descritor);
      
        exit(1);
}
