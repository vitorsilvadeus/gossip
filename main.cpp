#include"gossip.h"
using namespace std;

int main(int argc, char **argv){

	if(argc == 1){
		
		cliente(PORTA_PADRAO);
	
	}
	else if(argc == 2){

		if(!strcmp(argv[2],"-S")){
		
			servidor(PORTA_PADRAO);

		}
		else{

			cliente(atoi(argv[2]));	
		
		}
		
	}
        else if(argc == 3){
		if(!strcmp(argv[2],"-S")){

			servidor(atoi(argv[3]));		

		}
		else{

			cout << "Erro na chamada do programa" << endl;

		}

	}

	return(0);
}