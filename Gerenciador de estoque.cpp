#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Produto {
	private:
		int id;
		string nome;
		float valor;
		int quantidade;

	public:
		Produto(int i, string n, float v, int q) : id(i), nome(n), valor(v), quantidade(q) {}

        

		virtual void exibirInformacoes() const {
			cout << "ID: " << id << endl;
			cout << "Nome: " << nome << endl;
			cout << "Valor: " << valor << endl;
			cout << "Quantidade: " << quantidade << endl;
		}

		void adicionarEstoque(int qtd) {
			quantidade += qtd;
		}

		bool removerEstoque(int qtd) {
			if (qtd > quantidade) {
				cout << "Quantidade insuficiente em estoque!" << endl;
				return false;
			}
			quantidade -= qtd;
			return true;
		}

		// Getters
		int getID() const {
			return id;
		}
		string getNome() const {
			return nome;
		}
		float getValor() const {
			return valor;
		}
		int getQuantidade() const {
			return quantidade;
		}

virtual ~Produto() {}
};

class Alimento : public Produto {
	private:
		string validade;

	public:
		Alimento(int i, string n, float v, int q, string val) : Produto(i, n, v, q), validade(val) {}

		void exibirInformacoes() const override {
			Produto::exibirInformacoes();
			cout << "Validade: " << validade << endl;
		}
        ~Alimento() override {}
};

class Eletronico : public Produto {
	private:
		int garantia;

	public:
		Eletronico(int i, string n, float v, int q, int g) : Produto(i, n, v, q), garantia(g) {}

		void exibirInformacoes() const override {
			Produto::exibirInformacoes();
			cout << "Garantia: " << garantia << " meses" << endl;
		}
        ~Eletronico() override {}
};

class Estoque {
private:
    vector<Alimento*> alimentos;      // Lista de alimentos
    vector<Eletronico*> eletronicos;  // Lista de eletrônicos

public:
    void adicionarProdutos(Produto* produto) {
        // Identificar o tipo do produto e adicionar à lista correta
        if (Alimento* alimento = dynamic_cast<Alimento*>(produto)) {
            alimentos.push_back(alimento);
        } else if (Eletronico* eletronico = dynamic_cast<Eletronico*>(produto)) {
            eletronicos.push_back(eletronico);
        }
    }

    void removerProduto(int id) {
        // Verifica e remove de alimentos
        for (auto it = alimentos.begin(); it != alimentos.end(); ++it) {
            if ((*it)->getID() == id) {
                delete *it;
                alimentos.erase(it);
                cout << "Produto removido com sucesso!" << endl;
                return;
            }
        }
        // Verifica e remove de eletrônicos
        for (auto it = eletronicos.begin(); it != eletronicos.end(); ++it) {
            if ((*it)->getID() == id) {
                delete *it;
                eletronicos.erase(it);
                cout << "Produto removido com sucesso!" << endl;
                return;
            }
        }
        cout << "Produto com ID " << id << " nao encontrado!" << endl;
    }

    void listarProdutos() {
        if (alimentos.empty() && eletronicos.empty()) {
            cout << "Nao ha produtos no estoque!" << endl;
            return;
        }

        // Listar alimentos
        if (!alimentos.empty()) {
            cout << "Lista de Alimentos:" << endl;
            for (const auto& alimento : alimentos) {
                alimento->exibirInformacoes();
                cout << "---------------------------" << endl;
            }
        } else {
            cout << "Nenhum alimento em estoque." << endl;
        }

        // Listar eletrônicos
        if (!eletronicos.empty()) {
            cout << "Lista de Eletronicos:" << endl;
            for (const auto& eletronico : eletronicos) {
                eletronico->exibirInformacoes();
                cout << "---------------------------" << endl;
            }
        } else {
            cout << "Nenhum eletronico em estoque." << endl;
        }
    }

    ~Estoque() {
        for (auto alimento : alimentos) {
            delete alimento;
        }
        for (auto eletronico : eletronicos) {
            delete eletronico;
        }
    }
};


void Menu(int* opc) {
	cout<<"\n\n-------------------------------------------"<<endl;
	cout<<"Sistema De Estoque"<<endl;
	cout<<"1-Adicionar Produtos"<<endl;
	cout<<"2-Remover Produtos"<<endl;
	cout<<"3-Listar Produtos"<<endl;
	cout<<"0-Sair"<<endl;
	cout<<"Opcao: ";
	cin>> *opc;
}

void Produtos(int* id,float* valor,string* nome,int* quantidade) {

	cout << "ID: ";
	cin >> *id;
	cin.ignore();
	cout << "Nome: ";
	getline(cin, *nome);
	cout << "Preco: ";
	cin >> *valor;
	cout << "Quantidade: ";
	cin >> *quantidade;

}
int main() {

	Estoque est;

	int id;
	float valor;
	string nome;
	int quantidade;

	int opc;
	do {

		Menu(&opc);

		switch (opc) {
			case 1:
				int tipo;
				cout<<"\nEscolha o tipo de produto \n1-Alimento \n2-Eletronico \nTipo:";
				cin>>tipo;
				if(tipo == 1) {
					string validade;

					cout<<"\n"<<endl;
					Produtos(&id,&valor,&nome,&quantidade);
					cout<<"Informe a validade do produto:";
					fflush(stdin);
					getline(cin,validade);
					est.adicionarProdutos(new Alimento(id, nome, valor, quantidade, validade));
				} else {
					int garantia;
					
					cout<<"\n"<<endl;
					Produtos(&id,&valor,&nome,&quantidade);
					cout<<"Informe a garantia do produto:";
					cin>>garantia;

					est.adicionarProdutos(new Eletronico(id,nome,valor,quantidade,garantia));
				}
				break;

			case 2:
				int removeId;
				cout<<"Informe o Id do produto para remove-lo: ";
				cin>>removeId;
				est.removerProduto(removeId);
				break;

			case 3:
				cout<<"\n\n---------------------------\n";
				est.listarProdutos();
				break;

			case 0:
				cout<<"Fechando o programa...";
			default:
				cout<<"Escolha invalida!!!";
				break;
		}

	} while(opc != 0);


	return 0;
}