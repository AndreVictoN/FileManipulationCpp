//André Victor Gonçalves Nascimento - Info 2 - 09/07/2024

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class Movel{
private:
	int posX;
	int posY;
	int velX;
	int velY;

	string imagem;

public:
	Movel(){
		posX = 0;
		posY = 0;
		velX = 0;
		velY = 0;

		imagem = "";
	}

	Movel(int x, int y, int vx, int vy, string img){
		posX = x;
		posY = y;
		velX = vx;
		velY = vy;

		imagem = img;
	}

	//outra opção de verificar vírgulas e trocar por espaços:
	/*void movel(string linha){
		int position;

		while(linha.find_first_of(',') < linha.length()){
			position = linha.find_first_of(',');

			linha.replace(position, 1, " ");
		}

		stringstream stris(linha);

		stris >> posX >> posY >> velX >> velY >> imagem;
	}*/

	void movel(string linha){
		replace(linha.begin(), linha.end(),',',' ');

		stringstream stris(linha);

		stris >> posX >> posY >> velX >> velY >> imagem;
	}

	void mover(int tempo){
		posX += velX * tempo;
		posY += velY * tempo;
	}

	void setPosX(int x){
		posX = x;
	}

	void setPosY(int y){
		posY = y;
	}

	int getPosX(){

		return posX;
	}

	int getPosY(){

		return posY;
	}

	string toString(){
		stringstream ss;

		ss << posX << "," << posY << "," << velX << "," << velY << "," << imagem;

		return ss.str();
	}
};

vector<Movel> carregaMoveis(string caminho){
	vector<Movel> moveis;

	//string file;

	ifstream ar(caminho.c_str());

	if(!ar.is_open()){
		cout << "Erro ao abrir arquivo." << endl;

		return moveis;
	}

	string line;

	while(getline(ar,line)){


		if(line[0] != 'p'){
			//file += strtemp;
			//file += "\n";

			Movel movel;
			movel.movel(line);

			moveis.push_back(movel);

		}
	}

	ar.close();

	return moveis;
}

//Opção para criar um arquivo novo:

/*void salvaMoveis(string newCaminho, vector<Movel> newMoveis){
	ofstream output(newCaminho.c_str());

	output << "posX,poxY,velX,velY,imagem" << endl;

	for(size_t i = 0; i < newMoveis.size(); i++){
		output << newMoveis[i].toString() << endl;
	}

	output.close();
}*/

void salvaMoveis(string caminho, vector<Movel> newMoveis){
	ofstream output(caminho.c_str());

	if(!output.is_open()){
		cout << "Erro ao abrir arquivo." << endl;

		return;
	}

	output << "posX,poxY,velX,velY,imagem" << endl;

	for(size_t i = 0; i < newMoveis.size(); i++){
		output << newMoveis[i].toString() << endl;
	}

	output.close();
}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	//Chama função de carregar dados.
	vector<Movel> moveis = carregaMoveis("moveis.csv");

	if(moveis.empty()){
		return 0;
	}

	for(size_t i = 0; i < moveis.size(); i++)
	{
		cout << moveis[i].toString() << endl;
	}

	cout << endl;

	//Atualiza os dados com a função mover.
	for(size_t i = 0; i < moveis.size(); i++){
		moveis[i].mover(i);
	}
	
	cout << "Atualizados:" << endl;

	for(size_t i = 0; i < moveis.size(); i++)
	{
		cout << moveis[i].toString() << endl;
	}

	//Salva os dados no arquivo novamente.

	//salvaMoveis("newMoveis.csv", moveis);

	salvaMoveis("moveis.csv", moveis);


	return 0;
}
