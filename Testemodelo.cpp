#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Definição das dimensões da pousada (Ex: 3 andares, 5 quartos por andar)
const int ANDARES = 3;
const int QUARTOS = 5;
const int MAX_CAPACIDADE = 4;

// STRUCTS (Registros)
struct Data {
    int dia;
    int mes;
    int ano;
};

struct Hospede {
    string nome;
    string cpf;
    Data nascimento;
    string telefone;
};

struct Hospedagem {
    int numeroQuarto;
    int andar;
    Hospede hospede;
    Data entrada;
    Data saida;
    bool ativa = false;       // true se o hospede já fez check-in
    bool reserva = false;     // true se for apenas uma reserva futura
};

struct Quarto {
    int numero;
    int andar;
    string tipo;  // Padrão ou Premium (com varanda/vista para o mar)
    int capacidade;
    float valorDiaria;
    int situacao;   // 1 = "Livre", 2 = "Ocupado", 3 = "Reservado"
};

// MATRIZ para o Prédio e VETOR para o Histórico/Lista de Hospedagens
Quarto pousada[ANDARES][QUARTOS];
Hospedagem hospedagens[ANDARES*QUARTOS];

// PROTÓTIPOS DAS FUNÇÕES
void inicializarPousada();
void menu();
void cadastrarQuartos();
void realizarReserva();
void converterReservaCheckin();
void realizarCheckinDireto();
void alterarDados();
void realizarCheckout();
void relatorioGeral();
void relatorioOcupacaoGanhos();
void consultarQuartos();

// FUNÇÃO PRINCIPAL
int main() {
    // Configura a saída do terminal para 2 casas decimais em valores monetários
    cout << fixed << setprecision(2);
    
    inicializarPousada();
    menu();
    
    return 0;
}

void inicializarPousada() {
    for (int i = 0; i < ANDARES; i++) {
        for (int j = 0; j < QUARTOS; j++) {
            pousada[i][j].andar = i + 1;
            pousada[i][j].numero = ((i + 1) * 100) + (j + 1); // Ex: Quarto 101, 102, 201...
            pousada[i][j].situacao = 1;
            pousada[i][j].capacidade = MAX_CAPACIDADE;
        }
    }
}

void menu() {
    int opcao;
    do {
        cout << "\n===== GERENCIADOR DE POUSADA =====\n";
        cout << "1. Cadastrar/Ajustar Detalhes dos Quartos\n";
        cout << "2. Realizar Reserva Antecipada\n";
        cout << "3. Confirmar Check-in (ou Converter Reserva)\n";
        cout << "4. Alterar Dados de Hospede/Reserva\n";
        cout << "5. Realizar Check-out (Emissão de Resumo)\n";
        cout << "6. Consulta de Quartos (Filtros)\n";
        cout << "7. Relatório Geral de Ocupação\n";
        cout << "8. Relatório Financeiro e de Ganhos\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1: cadastrarQuartos(); break;
            case 2: realizarReserva(); break;
            case 3: converterReservaCheckin(); break;
            case 4: alterarDados(); break;
            case 5: realizarCheckout(); break;
            case 6: consultarQuartos(); break;
            case 7: relatorioGeral(); break;
            case 8: relatorioOcupacaoGanhos(); break;
            case 0: cout << "Encerrando o sistema...\n"; break;
            default: cout << "Opcao inválida!\n";
        }
    } while (opcao != 0);
}

// 1. Cadastro/Configuração dos Quartos da Pousada
void cadastrarQuartos() {
    int num;
    cout << "\n--- CONFIGURAR QUARTO ---\n";
    cout << "Digite o número do quarto que deseja configurar: ";
    cin >> num;
    
    int andarIdx = (num / 100) - 1;
    int quartoIdx = (num % 100) - 1;
    int erro = 0;
    
    // Validação se o quarto existe na matriz
    if (andarIdx >= 0 && andarIdx < ANDARES && quartoIdx >= 0 && quartoIdx < QUARTOS) {
        cout << "Tipo do Quarto (Padrão ou Premium): ";
        cin.ignore();
        getline(cin, pousada[andarIdx][quartoIdx].tipo);
        do {
            erro = 0;
            if (pousada[andarIdx][quartoIdx].tipo == "Padrão" || 
                pousada[andarIdx][quartoIdx].tipo == "padrão" || 
                pousada[andarIdx][quartoIdx].tipo == "Padrao" ||
                pousada[andarIdx][quartoIdx].tipo == "padrao") {
                    pousada[andarIdx][quartoIdx].valorDiaria = 150.00;
            } else if (pousada[andarIdx][quartoIdx].tipo == "Premium" || 
                    pousada[andarIdx][quartoIdx].tipo == "premium") {
                    pousada[andarIdx][quartoIdx].valorDiaria = 250.00;
            } else {
                cout << "\nTipo inválido!" << endl;
                erro = 1;
            }
        } while(erro == 1);

        do {
            cout << "Capacidade de Hóspedes: ";
            cin >> pousada[andarIdx][quartoIdx].capacidade;
            if (pousada[andarIdx][quartoIdx].capacidade > MAX_CAPACIDADE) {
                cout << "\nO valor excede a capacidade máxima dos quartos!" << endl;
            }
        } while(pousada[andarIdx][quartoIdx].capacidade > MAX_CAPACIDADE);

        cout << "Quarto configurado com sucesso!\n";
    } else {
        cout << "Erro: Quarto não encontrado!\n";
    }
}

// 2. Realização de reservas antes do check-in
void realizarReserva() {
    int num;
    Data hoje;
    char barra;
    cout << "\n--- REALIZAR RESERVA ANTECIPADA ---\n";
    cout << "\nDigite a data de hoje (DD/MM/AAAA): ";
    cin >> hoje.dia >> barra >> hoje.mes >> barra >> hoje.ano;

    cout << "Digite o número do quarto desejado: ";
    cin >> num;

    int andarIdx = (num / 100) - 1;
    int quartoIdx = (num % 100) - 1;

    if (andarIdx < 0 || andarIdx >= ANDARES || quartoIdx < 0 || quartoIdx >= QUARTOS) {
        cout << "Quarto inexistente!\n";
        return;
    }

    // Validação de segurança no momento da reserva
    if (pousada[andarIdx][quartoIdx].situacao != 1) {
        if(pousada[andarIdx][quartoIdx].situacao == 2) {
            cout << "Erro: Este quarto já está ocupado!\n";
            return;
        } else if(pousada[andarIdx][quartoIdx].situacao == 3) {
            cout << "Erro: Este quarto já está reservado!\n";
            return;
        }
    }

    Hospedagem novaReserva;
    novaReserva.andar = andarIdx;
    novaReserva.numeroQuarto = num;
    
    cout << "Nome do Hóspede: ";
    getline(cin, novaReserva.hospede.nome);
    cout << "CPF: ";
    getline(cin, novaReserva.hospede.cpf);
    cout << "Data de nascimento (DD/MM/AAAA): ";
    cin >> novaReserva.hospede.nascimento.dia >> barra >> 
           novaReserva.hospede.nascimento.mes >> barra >> 
           novaReserva.hospede.nascimento.ano;
    cin.ignore();
    cout << "Telefone: ";
    getline(cin, novaReserva.hospede.telefone);
    cout << "Data de entrada (DD/MM/AAAA): ";
    cin >> novaReserva.entrada.dia >> barra
        >> novaReserva.entrada.mes >> barra 
        >> novaReserva.entrada.ano;

    cout << "Data de saída (DD/MM/AAAA): ";
    cin >> novaReserva.saida.dia >> barra
        >> novaReserva.saida.mes >> barra 
        >> novaReserva.saida.ano;

    novaReserva.ativa = false;
    novaReserva.reserva = true;

    // Atualiza a situação na matriz do prédio
    pousada[andarIdx][quartoIdx].situacao = 3;
    
    hospedagens[andarIdx*quartoIdx] = novaReserva;

    cout << "Reserva efetuada com sucesso para o Quarto " << num << "!\n";
}

// 3. Conversão de uma reserva em check-in & Validações de Check-in
void converterReservaCheckin() {
    cout << "\n--- ENTRADA / CHECK-IN ---\n";
    cout << "1. Converter Reserva Existente\n2. Novo Check-in Direto\nEscolha: ";
    int esc;
    cin >> esc;
    cin.ignore();

    if (esc == 1) {
        string cpfBusca;
        cout << "Digite o CPF do titular da reserva: ";
        getline(cin, cpfBusca);

        for (int i = 0; i < (ANDARES*QUARTOS); i++) {
            if (hospedagens[i].hospede.cpf == cpfBusca && hospedagens[i].reserva) {
                int a = hospedagens[i].andar;
                int q = (hospedagens[i].numeroQuarto % 100) - 1;

                cout << "Reserva localizada! Quarto " << hospedagens[i].numeroQuarto << "\n";
                cout << "Deseja ajustar a data de saída? (S ou N): ";
                char sn, barra;
                cin >> sn;
                if(sn == 'S' || sn == 's') {
                    cout << "Digite a nova data de saída (DD/MM/AAAA): ";
                    cin >> hospedagens[i].saida.dia >> barra
                        >> hospedagens[i].saida.mes >> barra
                        >> hospedagens[i].saida.ano;
                }
                
                int hospedes;
                cout << "Quantidade de hóspedes que vão entrar no quarto: ";
                cin >> hospedes;
                
                // Validação de capacidade do quarto
                if (hospedes > pousada[a][q].capacidade) {
                    cout << "Erro: Quantidade de pessoas excede a capacidade máxima do quarto (" << pousada[a][q].capacidade << ")!\n";
                    return;
                }

                hospedagens[i].reserva = false;
                hospedagens[i].ativa = true;
                pousada[a][q].situacao = 2;

                cout << "Check-in da reserva concluído com sucesso!\n";
                return;
            }
        }
        cout << "Nenhuma reserva ativa encontrada para este CPF.\n";
    } else {
        realizarCheckinDireto();
    }
}

void realizarCheckinDireto() {
    int num;
    char barra;
    Data hoje;
    cout  << "Digite a data de hoje (DD/MM/AAAA): ";
    cin >> hoje.dia >> barra >> hoje.mes >> barra >> hoje.mes;

    cout << "Digite o número do quarto para Check-in imediato: ";
    cin >> num;
    cin.ignore();

    int andarIdx = (num / 100) - 1;
    int quartoIdx = (num % 100) - 1;

    if (andarIdx < 0 || andarIdx >= ANDARES || quartoIdx < 0 || quartoIdx >= QUARTOS) {
        cout << "Quarto inválido!\n";
        return;
    }

    // Validação imposta pelo professor: Impedir check-in em quarto ocupado/reservado
    if (pousada[andarIdx][quartoIdx].situacao != 1) {
        if(pousada[andarIdx][quartoIdx].situacao == 2) {
            cout << "Erro: Este quarto já está ocupado!\n";
            return;
        } else if(pousada[andarIdx][quartoIdx].situacao == 3) {
            cout << "Erro: Este quarto já está reservado!\n";
            return;
        }
    }

    int hospedes;
    cout << "Quantidade de hóspedes: ";
    cin >> hospedes;
    cin.ignore();

    if (hospedes > pousada[andarIdx][quartoIdx].capacidade) {
        cout << "Erro: Capacidade máxima excedida! Limite: " << pousada[andarIdx][quartoIdx].capacidade << " pessoas.\n";
        return;
    }

    Hospedagem h;
    h.andar = andarIdx;
    h.numeroQuarto = num;
    cout << "Nome do Hóspede: "; 
    getline(cin, h.hospede.nome);
    cout << "CPF: "; 
    getline(cin, h.hospede.cpf);
    cout << "Telefone: "; 
    getline(cin, h.hospede.telefone);
    cout << "Data de entrada (DD/MM/AAAA): ";
    cin >> h.entrada.dia >> barra
        >> h.entrada.mes >> barra 
        >> h.entrada.ano;
    cout << "Data de saída (DD/MM/AAAA): ";
    cin >> h.saida.dia >> barra
        >> h.saida.mes >> barra 
        >> h.saida.ano;

    h.ativa = true;
    h.reserva = false;
    pousada[andarIdx][quartoIdx].situacao = 2;
    hospedagens[andarIdx*quartoIdx] = h;
    cout << "Check-in direto realizado com sucesso!\n";
}

// 4. Alterar dados de um hóspede antes do check-out
void alterarDados() {
    string cpfBusca;
    char barra;
    bool erro = true;
    cout << "\n--- ALTERAR DADOS DO HÓSPEDE / HOSPEDAGEM ---\n";
    cout << "Digite o CPF do Hóspede: ";
    getline(cin, cpfBusca);

    for (int i = 0; i < (QUARTOS*ANDARES); i++) {
        if (hospedagens[i].hospede.cpf == cpfBusca && hospedagens[i].reserva) {
            cout << "Modificando dados de: " << hospedagens[i].hospede.nome << "\n";
            cout << "Novo Nome: "; 
            getline(cin, hospedagens[i].hospede.nome);
            cout << "Novo Telefone: "; 
            getline(cin, hospedagens[i].hospede.telefone);
            cout << "Nova data de entrada (DD/MM/AAAA): ";
            cin >> hospedagens[i].entrada.dia >> barra
                >> hospedagens[i].entrada.mes >> barra 
                >> hospedagens[i].entrada.ano;
            cout << "Nova data de saída (DD/MM/AAAA): ";
            cin >> hospedagens[i].saida.dia >> barra
                >> hospedagens[i].saida.mes >> barra 
                >> hospedagens[i].saida.ano;
            cout << "Dados corrigidos e atualizados!\n";
            erro = false;
            return;
        }
    }
    if(erro){
        cout << "Hóspede ativo ou reserva não localizada.\n";
    }
}

// 5. Emissão de resumo da hospedagem no Check-out e cálculo com descontos
void realizarCheckout() {
    int num;
    cout << "\n--- PROCESSAR CHECK-OUT ---\n";
    cout << "Digite o número do quarto para saída: ";
    cin >> num;

    int andarIdx = (num / 100) - 1;
    int quartoIdx = (num % 100) - 1;

    for (int i = 0; i < (ANDARES*QUARTOS); i++) {
        if (hospedagens[i].numeroQuarto == num && hospedagens[i].ativa) {
            int qtDiarias = hospedagens[i].saida.dia - hospedagens[i].entrada.dia;
            float valorBruto = qtDiarias * pousada[andarIdx][quartoIdx].valorDiaria;
            float desconto = 0.0;

            // Desconto para estadias longas
            if (qtDiarias >= 14) {
                desconto = valorBruto * 0.20; // 20% de desconto para mais de duas semanas
            } else if (qtDiarias >= 7) {
                desconto = valorBruto * 0.10; // 10% de desconto para mais de uma semana
            }

            float valorFinal = valorBruto - desconto;

            // Relatório da Hospedagem
            cout << "\n====================================\n";
            cout << "        RESUMO DA HOSPEDAGEM        \n";
            cout << "====================================\n";
            cout << "Titular: " << hospedagens[i].hospede.nome << "\n";
            cout << "CPF: " << hospedagens[i].hospede.cpf << "\n";
            cout << "Quarto Utilizado: " << num << " (Andar " << andarIdx + 1 << ")\n";
            cout << "Quantidade de Diárias: " << qtDiarias << "\n";
            cout << "Valor Bruto: R$ " << valorBruto << "\n";
            cout << "Desconto Aplicado: R$ " << desconto << "\n";
            cout << "VALOR FINAL A PAGAR: R$ " << valorFinal << "\n";
            cout << "====================================\n";

            // Liberação física e lógica
            pousada[andarIdx][quartoIdx].situacao = 1; // Quarto Livre
            hospedagens[i].ativa = false; // Finalizada
            return;
        }
    }
    cout << "Nenhum hóspede ativo encontrado no quarto " << num << ".\n";
}

// 6. Consulta de quartos por número, andar ou situação
void consultarQuartos() {
    cout << "\n--- CONSULTA FILTRADA DE QUARTOS ---\n";
    cout << "Filtrar por:\n1. Numero do Quarto\n2. Andar\n3. Situacao (1: Livre, 2: Ocupado, 3: Reservado)\n3. Período\nEscolha: ";
    int filtro;
    cin >> filtro;
    cin.ignore();

    if (filtro == 1) {
        int num;
        cout << "Digite o número: "; 
        cin >> num;
        int a = (num / 100) - 1; 
        int q = (num % 100) - 1;
        if (a >= 0 && a < ANDARES && q >= 0 && q < QUARTOS) {
            cout << "Quarto " << num << " | Tipo: " << pousada[a][q].tipo 
                 << " | Capacidade: " << pousada[a][q].capacidade 
                 << " | Diária: R$ " << pousada[a][q].valorDiaria;
            if (pousada[a][q].situacao == 1) {
                cout << " | Status: Livre";
            } else if (pousada[a][q].situacao == 2) {
                cout << " | Status: Ocupado";
            } else {
                cout << " | Status: Reservado";
            }

        } else 
            cout << "Quarto não existe.\n";
    } 
    else if (filtro == 2) {
        int andar;
        cout << "Digite o andar: "; 
        cin >> andar;
        if (andar >= 1 && andar <= ANDARES) {
            for (int j = 0; j < QUARTOS; j++) {
                cout << "Quarto " << pousada[andar-1][j].numero 
                     << " | Tipo: " << pousada[andar-1][j].tipo 
                 << " | Capacidade: " << pousada[andar-1][j].capacidade 
                 << " | Diária: R$ " << pousada[andar-1][j].valorDiaria;
                if (pousada[andar-1][j].situacao == 1) {
                    cout << " | Status: Livre";
                } else if (pousada[andar-1][j].situacao == 2) {
                    cout << " | Status: Ocupado";
                } else {
                    cout << " | Status: Reservado";
                }
            }
        } else cout << "Andar inválido.\n";
    } 
    else if (filtro == 3) {
        string sit;
        cout << "Digite a situação desejada (Livre, Ocupado, Reservado): ";
        getline(cin, sit);
        for (int i = 0; i < ANDARES; i++) {
            for (int j = 0; j < QUARTOS; j++) {
                if (pousada[i][j].situacao == sit) {
                    cout << "Quarto " << pousada[i][j].numero << " está " << sit << "\n";
                }
            }
        }
    }
}

// 7. Relatório Geral da Pousada
void relatorioGeral() {
    int livres = 0, ocupados = 0, reservados = 0;
    int totalHospedesAtivos = 0;

    for (int i = 0; i < ANDARES; i++) {
        for (int j = 0; j < QUARTOS; j++) {
            if (pousada[i][j].situacao == "Livre") livres++;
            else if (pousada[i][j].situacao == "Ocupado") ocupados++;
            else if (pousada[i][j].situacao == "Reservado") reservados++;
        }
    }

    // Conta quantos hóspedes estão registrados em estadias ativas no momento
    for (size_t i = 0; i < listaHospedagens.size(); i++) {
        if (listaHospedagens[i].ativa) totalHospedesAtivos++;
    }

    cout << "\n--- RELATÓRIO GERAL DA POUSADA ---\n";
    cout << "Quartos Livres: " << livres << "\n";
    cout << "Quartos Ocupados: " << ocupados << "\n";
    cout << "Quartos Reservados: " << reservados << "\n";
    cout << "Total de Hóspedes Titulares Ativos: " << totalHospedesAtivos << "\n";
}

// 8. Relatório de ocupação e ganhos simulado
void relatorioOcupacaoGanhos() {
    cout << "\n--- RELATÓRIO FINANCEIRO (SIMULADO DE PERÍODO) ---\n";
    string dataInicio, dataFim;
    cout << "Informe a data de início (DD/MM/AAAA): "; getline(cin, dataInicio);
    cout << "Informe a data de término (DD/MM/AAAA): "; getline(cin, dataFim);

    int totalHospedagensRealizadas = 0;
    int quartosOcupadosNoPeriodo = 0;
    float totalArrecadado = 0.0;

    // Varre nosso vetor/histórico para consolidar os dados financeiros
    for (size_t i = 0; i < listaHospedagens.size(); i++) {
        int a = listaHospedagens[i].andar;
        int q = (listaHospedagens[i].numeroQuarto % 100) - 1;
        
        float vBruto = listaHospedagens[i].qtdeDiarias * pousada[a][q].valorDiaria;
        if (listaHospedagens[i].qtdeDiarias >= 7) vBruto *= 0.90; // Aplica o desconto no cálculo

        totalArrecadado += vBruto;
        totalHospedagensRealizadas++;
        if (listaHospedagens[i].ativa) {
            quartosOcupadosNoPeriodo++;
        }
    }

    cout << "\nResultados para o período entre " << dataInicio << " e " << dataFim << ":\n";
    cout << "Quantidade de Hospedagens Processadas: " << totalHospedagensRealizadas << "\n";
    cout << "Quartos Ativos no Momento: " << quartosOcupadosNoPeriodo << "\n";
    cout << "Valor Total Arrecadado/Previsto: R$ " << totalArrecadado << "\n";
}