#include <iostream>
using namespace std;

struct Aluno{
	string nome;
	string cpf;
	int idade;
};

bool alunoIgual(Aluno aluno1, Aluno aluno2){
	return aluno1.nome == aluno2.nome && aluno1.cpf == aluno2.cpf && aluno1.idade == aluno2.idade;
}

struct NoArvore{
	int key;
	Aluno aluno;
	NoArvore *esquerda;
	NoArvore *direita;
};

void exibirArvore(NoArvore *raiz){
	if(raiz != NULL){
		exibirArvore(raiz -> esquerda);
		cout << raiz -> key << " ";
		exibirArvore(raiz -> direita);
	}
}

NoArvore *inserir(NoArvore *&raiz, int chave, string nome, string cpf, int idade){
	if(raiz == NULL){
		Aluno aluno;
		aluno.nome = nome;
		aluno.cpf = cpf;
		aluno.idade = idade;
		NoArvore *novoNo = new NoArvore;
		novoNo -> key = chave;
		novoNo -> aluno = aluno;
		novoNo -> esquerda = NULL;
		novoNo -> direita = NULL;
		raiz = novoNo;
		return raiz;
	} else if(chave < raiz -> key){
		return inserir(raiz->esquerda, chave, nome, cpf, idade);
	} else if(chave > raiz -> key){
		return inserir(raiz->direita, chave, nome, cpf, idade);
	}else{
		cout << "Chave ja existe." << endl;
	}
}

NoArvore *busca(NoArvore *raiz, int chave){
	if(raiz == NULL){
		cout << "Aluno nao encontrado" << endl;
		return raiz;
	}else if(raiz -> key == chave){
		cout << "Nome: " << raiz -> aluno.nome << endl;
		cout << "CPF: " << raiz -> aluno.cpf << endl;
		cout << "Idade: " << raiz -> aluno.idade << endl;
		return raiz;
	} else if(chave < raiz -> key){
		busca(raiz -> esquerda, chave);
	} else {
		busca(raiz -> direita, chave);
	}
}

void *deletar(NoArvore *&raiz, int chave){
	if(chave > raiz -> key){
		deletar(raiz -> direita, chave);
	}else if(chave < raiz -> key){
		deletar(raiz -> esquerda, chave);
	} else {
		NoArvore *aux = raiz;
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			raiz = NULL;
			delete raiz;
		}else if(raiz -> esquerda == NULL){
			NoArvore *aux = raiz;
			raiz = raiz -> direita;
			delete aux;
		}else if(raiz -> direita == NULL){
			NoArvore *aux = raiz;
			raiz = raiz -> esquerda;
			delete aux;
		}else{
			NoArvore *aux = raiz;
			NoArvore *maiorEsquerda = raiz -> esquerda;
			while(maiorEsquerda -> direita != NULL){
				maiorEsquerda = maiorEsquerda -> direita;
			}
			deletar(raiz, maiorEsquerda->key);
			raiz = maiorEsquerda;
			if(aux -> esquerda != raiz){
				raiz -> esquerda = aux -> esquerda;
			}
			raiz -> direita = aux -> direita;
			aux = NULL;
			delete aux;
		}
	}
}

bool isBST(NoArvore *raiz){
	if(raiz != NULL){
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			return true;
		}else if(raiz -> direita == NULL){
			if(raiz -> esquerda -> key >= raiz -> key){
				return false;
			}
			return isBST(raiz-> esquerda);
		}else if(raiz -> esquerda == NULL){
			if(raiz -> direita -> key <= raiz -> key){
				return false;
			}
			return isBST(raiz-> direita);
		}else{
			if(raiz -> direita -> key <= raiz -> key || raiz -> esquerda -> key >= raiz -> key){
				return false;
			}
			return isBST(raiz->esquerda) && isBST(raiz -> direita);
		}
	}else{
		return true;
	}
}

bool sameBST(NoArvore *raiz1, NoArvore *raiz2){
	if(raiz1==NULL){
		if(raiz2!=NULL){
			return false;
		}
		return true;
	}
	if(raiz1 -> key == raiz2 -> key && alunoIgual(raiz1 -> aluno, raiz2 -> aluno)){
		return sameBST(raiz1 -> esquerda, raiz2 -> esquerda) && sameBST(raiz1 -> direita, raiz2 -> direita);
	}
	return false;
}

int main() {
	NoArvore *no1 = NULL;
	inserir(no1, 15, "Francisco", "89372873289", 20);
	cout << "Inseri a raiz: ";
	exibirArvore(no1);
	cout << endl;
	inserir(no1, 22, "Pedro", "3982738273", 27);
	inserir(no1, 27, "Thiago", "2938293893", 32);
	inserir(no1, 2, "Jose", "3827382733", 19);
	inserir(no1, 10, "João", "92839382938", 44);
	cout << "Inseri alguns alunos: ";
	exibirArvore(no1);
	cout << endl;
	cout << "Busca aluno da chave 2: " << endl;
	busca(no1, 2);
	cout << "Deletei o aluno da chave 15: " << endl;
	deletar(no1, 15);
	exibirArvore(no1);
	cout << endl;
	cout << boolalpha;
	cout << "Eh uma arvore BST? " << isBST(no1) << endl;
	
	//Arvore com mesmos elementos da anterior
	NoArvore *noCopia = NULL;
	inserir(noCopia, 15, "Francisco", "89372873289", 20);
	inserir(noCopia, 22, "Pedro", "3982738273", 27);
	inserir(noCopia, 27, "Thiago", "2938293893", 32);
	inserir(noCopia, 2, "Jose", "3827382733", 19);
	inserir(noCopia, 10, "João", "92839382938", 44);
	deletar(noCopia, 15);
	cout << "Arvore Original: ";
	exibirArvore(no1);
	cout << endl;
	cout << "Arvore Copia: ";
	exibirArvore(noCopia);
	cout << endl;
	cout << "Original e Copia sao iguais? " << sameBST(no1, noCopia)<< endl;
	//Arvore nao BST
	
	Aluno aluno2;
	aluno2.nome = "Joao";
	aluno2.cpf = "123";
	aluno2.idade = 12;
	NoArvore *no2 = new NoArvore;
	no2 -> key = 2;
	no2 -> aluno = aluno2;
	no2 -> esquerda = NULL;
	no2 -> direita = NULL;
	
	Aluno aluno3;
	aluno3.nome = "Maria";
	aluno3.cpf = "123";
	aluno2.idade = 12;
	NoArvore *no3 = new NoArvore;
	no3 -> key = 3;
	no3 -> aluno = aluno3;
	no3 -> esquerda = NULL;
	no3 -> direita = NULL;
	
	Aluno aluno4;
	aluno4.nome = "Pedro";
	aluno4.cpf = "123";
	aluno4.idade = 12;
	NoArvore *no4 = new NoArvore;
	no4 -> key = 4;
	no4 -> aluno = aluno4;
	no4 -> esquerda = NULL;
	no4 -> direita = NULL;
	
	Aluno aluno5;
	aluno5.nome = "Francisco";
	aluno5.cpf = "123";
	aluno5.idade = 12;
	NoArvore *no5 = new NoArvore;
	no5 -> key = 5;
	no5 -> aluno = aluno5;
	no5 -> esquerda = NULL;
	no5 -> direita = NULL;
	
	Aluno aluno6;
	aluno2.nome = "Marta";
	aluno2.cpf = "123";
	aluno2.idade = 12;
	NoArvore *no6 = new NoArvore;
	no6 -> key = 6;
	no6 -> aluno = aluno6;
	no6 -> esquerda = NULL;
	no6 -> direita = NULL;
	
	no2 -> esquerda = no3;
	no2 -> direita = no4;
	no3 -> esquerda = no5;
	no3 -> direita = no6;
	
	cout << "Nova arvore: ";
	exibirArvore(no2);
	cout << endl;
	cout << "eh BST?" << isBST(no2) << endl;
	return 0;
}
