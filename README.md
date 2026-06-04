# 🏨 Gerenciador de Quartos de Pousada

## 📌 Sobre o Projeto

O **Gerenciador de Quartos de Pousada** é um sistema desenvolvido em **C++** com o objetivo de auxiliar na administração de uma pousada, permitindo o controle de quartos, hóspedes, reservas e hospedagens.

O sistema foi desenvolvido como trabalho final da disciplina **Algoritmos e Estruturas de Dados**, aplicando conceitos fundamentais de programação, como vetores, matrizes, registros, funções, estruturas condicionais e de repetição.

---

## 👥 Integrantes

* Giulianna Viana Santana Amendoeira
* Luíza Castro Nere
* Matheus Nogueira Pereira

---

## 🎯 Objetivo

Automatizar e organizar as principais atividades de uma pousada, oferecendo funcionalidades para:

* Cadastro e gerenciamento de quartos;
* Cadastro de hóspedes;
* Realização de reservas;
* Check-in e check-out;
* Controle de ocupação;
* Relatórios gerenciais;
* Consulta de disponibilidade.

---

## ⚙️ Funcionalidades

### 🛏️ Gerenciamento de Quartos

* Cadastro de quartos contendo:

  * Número do quarto;
  * Andar;
  * Tipo do quarto;
  * Capacidade máxima de hóspedes;
  * Valor da diária;
  * Situação atual (Disponível, Reservado ou Ocupado).

* Consulta de quartos por:

  * Número;
  * Andar;
  * Situação;
  * Período de disponibilidade.

---

### 👤 Gerenciamento de Hóspedes

* Cadastro de hóspedes;
* Alteração de informações cadastrais;
* Consulta de dados dos hóspedes.

Dados armazenados:

* Nome;
* CPF;
* Data de nascimento;
* Telefone.

---

### 📅 Sistema de Reservas

* Cadastro de reservas futuras;
* Associação entre hóspede e quarto;
* Definição das datas de entrada e saída previstas;
* Controle de quartos reservados sem ocupação imediata.

---

### 🔑 Check-in

* Conversão de uma reserva em hospedagem ativa;
* Possibilidade de atualizar informações da hospedagem no momento da entrada;
* Alteração de:

  * Data de check-out;
  * Quantidade de diárias;
  * Informações do hóspede.

#### Validações

O sistema impede:

* Reservar um quarto já ocupado;
* Reservar um quarto já reservado para o mesmo período;
* Realizar check-in em quarto indisponível;
* Exceder a capacidade máxima de hóspedes do quarto.

---

### 🚪 Check-out

Ao finalizar uma hospedagem, o sistema:

* Libera o quarto;
* Atualiza os registros da pousada;
* Emite um resumo da hospedagem contendo:

  * Dados do hóspede;
  * Quarto utilizado;
  * Quantidade de diárias;
  * Valor bruto;
  * Desconto aplicado;
  * Valor final a pagar.

---

### 💰 Cálculo de Hospedagem

O sistema realiza automaticamente:

* Cálculo do valor total das diárias;
* Aplicação de descontos conforme regras definidas;
* Geração do valor final da hospedagem.

---

### 📊 Relatórios

#### Relatório Geral da Pousada

Exibe:

* Quantidade total de quartos;
* Quartos disponíveis;
* Quartos ocupados;
* Quartos reservados;
* Total de hóspedes registrados.

#### Relatório de Ocupação e Ganhos

Permite informar duas datas e apresenta:

* Quantidade de hospedagens realizadas;
* Quartos ocupados no período;
* Taxa de ocupação;
* Valor total arrecadado.

---

## 🧠 Estruturas de Dados Utilizadas

### Matrizes

Representação física da pousada:

* Linhas → Andares;
* Colunas → Quartos.

Exemplo:

| Andar | Quartos       |
| ----- | ------------- |
| 1º    | 101, 102, 103 |
| 2º    | 201, 202, 203 |

---

### Registros (Structs)

Utilizados para armazenar informações de:

* Hóspedes;
* Quartos;
* Reservas;
* Estadias.

---

### Vetores

Utilizados para:

* Lista de hóspedes;
* Lista de quartos;
* Lista de reservas;
* Histórico de hospedagens.

---

### Funções

Exemplos:

```cpp
cadastrarQuarto();
cadastrarHospede();
realizarReserva();
fazerCheckin();
fazerCheckout();
listarQuartos();
consultarDisponibilidade();
gerarRelatorio();
calcularValor();
```

---

### Estruturas Condicionais

Utilizadas para:

* Validações;
* Controle de disponibilidade;
* Aplicação de descontos;
* Verificação de capacidade dos quartos.

---

### Estruturas de Repetição

Utilizadas para:

* Menus;
* Pesquisas;
* Relatórios;
* Percorrer vetores e matrizes.

---

## 📋 Menu Principal

```text
1. Cadastrar Quarto
2. Cadastrar Hóspede
3. Realizar Reserva
4. Consultar Reservas
5. Fazer Check-in
6. Fazer Check-out
7. Alterar Dados de Hóspede
8. Consultar Quartos
9. Relatório Geral da Pousada
10. Relatório de Ocupação e Ganhos
11. Listar Hóspedes
12. Sair
```

---

## 💻 Tecnologias Utilizadas

* Linguagem C++
* Programação Estruturada
* Compilador GCC/G++
* Terminal/Console

---

## 📚 Conceitos da Disciplina Aplicados

✔ Variáveis e tipos de dados

✔ Estruturas condicionais

✔ Estruturas de repetição

✔ Vetores

✔ Matrizes

✔ Registros (struct)

✔ Modularização com funções

✔ Entrada e saída de dados

✔ Validação de informações

✔ Manipulação de dados em memória

---

## 📄 Observação

Projeto desenvolvido exclusivamente para fins acadêmicos na disciplina de Algoritmos e Estruturas de Dados.
