#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>
#include <random>
#include <limits>

#include "JeuDeLaVie.h"

using namespace std;
//using namespace seal;

int main(int argc, char const *argv[])
{
	cout<<"/Lancement de l'exemple de la Grenouille"<<endl;
	int largeur=5,longueur=5;
	bool** matrix;

	matrix = (bool**) malloc(largeur * sizeof(bool*));
	for(int i = 0; i < largeur; i++) {
		matrix[i] = (bool*) malloc(longueur * sizeof(bool));
	}

	largeur=longueur=initGrenouille(matrix);
	printMatrix(matrix,largeur,longueur);
	Globale(matrix,largeur,longueur,4);
	return 0;
}

void Globale(bool** matrix,int largeur,int longueur,int nbEtape){
	int compteur;
	int etape=0;
	bool** matrixNext;
	matrixNext = (bool**) malloc(largeur * sizeof(bool*));
	for(int i = 0; i < largeur; i++) {
		matrixNext[i] = (bool*) malloc(longueur * sizeof(bool));
	}
	while (etape<nbEtape){
		for (int i=0;i<largeur;i++){
			for (int j=0;j<longueur;j++){
				compteur=compteurLivingCell(matrix,largeur,longueur,i,j);
				if (compteur==2){
					matrixNext[i][j]=matrix[i][j];
				}
				else if (compteur==3){
					matrixNext[i][j]=true;
				}
				else {
					matrixNext[i][j]=false;
				}
			}
		}
		copyMatrix(matrix,matrixNext,largeur,longueur);
		cout<<"Après l'étape "<<etape<<endl;
		printMatrix(matrix,largeur,longueur);
		etape+=1;
	}
	

}

int compteurLivingCell(bool **matrix,int largeur,int longueur,int posC,int posL){
	int compteur =0;
	for (int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if (i==0 && j==0){
				continue;
			}
			else if (matrix[(posC+i+largeur)%largeur][(posL+j+longueur)%longueur]){
				compteur+=1;
			}
		}
	}
	return compteur;
}

void initToZero(bool** matrix,int largeur,int longueur){
	for (int i=0;i<largeur;i++){
		for (int j=0;j<longueur;j++){
			matrix[i][j]=false;
		}
	}
}

int initGrenouille(bool** matrix){
	//bool matrix[4][4];
	initToZero(matrix,5,5);
	matrix[2][0]=matrix[1][1]=matrix[1][2]=matrix[2][1]=matrix[2][2]=matrix[1][3]=true;
	return 5;
}

void printMatrix(bool** matrix,int largeur,int longueur){
	for (int i=0;i<largeur;i++){
		for (int j=0;j<longueur;j++){
			cout<<" "<<matrix[i][j];
		}
		cout<<""<<endl;
	}
}

void copyMatrix(bool** matrix,bool** matrixNext,int largeur,int longueur){
	for (int i=0;i<largeur;i++){
		for (int j=0;j<longueur;j++){
			matrix[i][j]=matrixNext[i][j];
		}
	}
	cout<<"Copy Done "<<endl;
}