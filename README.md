# 🏨 Gerenciador de Quartos de Pousada - Pousada Beira Mar

## 📌 Sobre o Projeto

O **Gerenciador de Quartos de Pousada** é um sistema desenvolvido em **C++** para auxiliar no controle de hospedagens de uma pousada.

O sistema permite administrar quartos, reservas, check-ins, check-outs e relatórios de ocupação, utilizando conceitos da disciplina de **Algoritmos e Estruturas de Dados**.

O projeto utiliza estruturas como matrizes, registros (`struct`), vetores, funções, condicionais e estruturas de repetição.

---

# 👥 Integrantes

* Giulianna Viana Santana Amendoeira
* Luíza Castro Nere
* Matheus Nogueira Pereira

---

# 🎯 Objetivo

O objetivo do sistema é informatizar o controle de uma pousada, permitindo:

* Gerenciamento dos quartos;
* Controle de disponibilidade;
* Cadastro de hóspedes durante reservas ou hospedagens;
* Realização de reservas;
* Controle de check-in e check-out;
* Cálculo de valores de hospedagem;
* Geração de relatórios administrativos.

---

# ⚙️ Funcionalidades Implementadas

## 🛏️ Configuração de quartos existentes

O sistema permite configurar os quartos da pousada contendo:

* Número do quarto;
* Andar;
* Tipo do quarto;
* Capacidade máxima;
* Valor da diária;
* Situação atual.

Os quartos possuem três estados:

* Livre;
* Ocupado;
* Reservado.

---

# 📅 Sistema de reservas

Permite realizar reservas antecipadas antes do check-in.

A reserva armazena:

* Dados do hóspede;
* Quarto escolhido;
* Data de entrada;
* Data de saída.

Durante a reserva o sistema verifica:

* Existência do quarto;
* Disponibilidade;
* Conflitos de ocupação.

---

# 🔑 Check-in

O sistema permite:

## Conversão de reserva

Uma reserva existente pode ser transformada em hospedagem ativa.

Alterações permitidas:

* Data de saída;
* Informações da hospedagem.

Após o check-in:

```
Reservado → Ocupado
```

---

## Check-in direto

Também é possível realizar hospedagem sem reserva prévia.

O sistema valida:

* Se o quarto está livre;
* Se a quantidade de hóspedes respeita a capacidade máxima.

---

# 🚪 Check-out

Ao realizar o check-out o sistema:

* Finaliza a hospedagem;
* Libera o quarto;
* Calcula o valor da estadia.

O resumo apresentado contém:

* Nome do hóspede;
* CPF;
* Quarto utilizado;
* Quantidade de diárias;
* Valor bruto;
* Desconto aplicado;
* Valor final.

---

# 💰 Cálculo de hospedagem

O valor é calculado através de:

```
Quantidade de diárias × Valor da diária
```

Possíveis descontos:

* 10% para estadias a partir de 7 dias;
* 20% para estadias a partir de 14 dias.

---

# 🔎 Consulta de quartos

Permite consultar quartos por:

* Número;
* Andar;
* Situação.

Exibe informações como:

* Tipo;
* Capacidade;
* Valor da diária;
* Status atual.

---

# 📊 Relatórios

## Relatório geral da pousada

Apresenta:

* Quantidade de quartos livres;
* Quantidade de quartos ocupados;
* Quantidade de quartos reservados;
* Hospedagens ativas.

---

## Relatório financeiro

Permite consultar informações de hospedagens realizadas em determinado período mensal.

Exibe:

* Quantidade de hospedagens;
* Quartos ocupados;
* Valor arrecadado.

---

# 🧠 Estruturas de Dados Utilizadas

## Matrizes

A pousada é representada como uma matriz:

```
Linhas → Andares
Colunas → Quartos
```

Exemplo:

```
1º andar:
101 | 102 | 103 | 104 | 105
```

---

## Structs

São utilizadas estruturas para representar:

### Quarto

Guarda:

* Número;
* Andar;
* Tipo;
* Capacidade;
* Valor;
* Situação.

### Hospede

Guarda:

* Nome;
* CPF;
* Telefone;
* Data de nascimento.

### Hospedagem

Guarda:

* Quarto;
* Hóspede;
* Datas;
* Estado da hospedagem.

---

# 🛠️ Tecnologias utilizadas

* Linguagem C++
* Programação estruturada
* Terminal/Console

---

# 📚 Conceitos aplicados

✔ Matrizes

✔ Vetores

✔ Registros (`struct`)

✔ Funções

✔ Estruturas condicionais

✔ Estruturas de repetição

✔ Manipulação de dados em memória

✔ Validação de informações