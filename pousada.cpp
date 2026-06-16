#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int ANDARES = 2;
const int QUARTOS = 10;

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Hospede {
    string nome;
    string cpf;
    string telefone;
    Data nascimento;
};

struct Quarto {
    int codigo;
    int andar;
    int capacidade;
    float custoDiaria;
    int situacao; // 1 = ocupado; 2 = reservado; 3 = disponivel
};

struct Reserva {
    Hospede hosp;
    int num_quarto;
    Data entrada;
    Data saida;
    int quantidade;
};

struct Estadia {

};

void cadastrarQuarto(Quarto q) {

}

void cadastrarHospede(Hospede h) {

}

void fazerReserva(Reserva r) {

}

void checkin() {

}

void checkout() {

}

void listarQuartos(Quarto quartos[QUARTOS][ANDARES]) {

}

void listarReservas(Reserva reservas[]) {

}
