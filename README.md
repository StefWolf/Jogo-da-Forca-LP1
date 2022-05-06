# JOGO DA FORCA

Desenvolvimento de um jogo da forca em C++ para o trabalho da unidade 1 da disciplina de **Linguagem de Programação I**

**Alunas**:
- Juliana Freire Pequeno de Santiago Carvalho
- Stefane de Assis Orichuela

## RESUMO

O jogo da forca foi desenvolvido com uma interface simples, colorida e interativa, onde um jogador, durante a partida terá até seis chances para acertar a palavra ocultada. A cada acerto, ele recebe determinada pontuação que será mostrada quando o usuário querer acessá-la.

## NOTAS DE DESENVOLVIMENTO:

- [x] Classe Forca.
- [x] Definição de Palheta de Cores.
- [x] Criação de um Main funcional.
- [x] Funções de testes de validação de arquivos (Palavras, Scores, Boneco, Arte do Game Over)
- [x] Validação dos conteúdos do arquivo Scores e de Palavras
- [x] Geração da tabela de scores para o console
- [x] Funções que geram as artes do jogo. 
- [x] Identificação das Letras palpitadas.
- [x] Identificação da dificuldade do jogo.

## FICARAM PENDENTES (LIMITAÇÕES)

- [ ] Retorno após a geração da tabela de scores
- [ ] Permitir digitar nome de jogador composto

# IMPLEMENTAÇÃO DO TESTE

## Como executar os testes?
Digite no console:

``` 
   bash program.sh
```

Segue abaixo os testes feitos para validação das funções e funcionalidades do jogo:

### Carregar Arquivo:
- **ARQUIVO DE PALAVRAS SEM PALAVRAS:** Execute um arquivo de palavras sem palavras chamado test_erros com ./program test_erros.txt scores.txt, ele retornará "Sorry. We dont have these numbers".
### Eh Válido:
- **ARQUIVOS INEXISTENTES:** Digite ./program arquivo_aleatorio.txt arquivo_aleatorio.txt, ele retornará um aviso indicando que o arquivo não foi encontrado.
- **PALAVRAS INVÁLIDAS NO ARQUIVO DE PALAVRAS:** Coloque um "-" ou " " dentre uma das palavras do arquivo de palavras.txt
### Sorteio Palavras:
- **DIFICULDADE INVÁLIDA:** Digite um número superior ao 3 quando pedir a dificuldade do jogo, ele retornará "Nível de dificuldade inválido! Por favor fale com o técnico".
### Palpite:
- **LETRA DIGITADA ANTERIORMENTE:** Digite uma letra que já foi digitada anteriormente na mesma partida e ele retornará "ERROR! Essa letra já foi palpitada anteriormente"
- **LETRA DIGITADA ANTERIORMENTE:** Erre uma rodada do jogo digitando uma letra incorreta, ele retornará "ERROU!".
### Main
- **NOME DO JOGADOR COM CARACTERE INVÁLIDO:** Ao selecionar seu nome no final do jogo, digite-o com (;) ou somente com uma letra e retornará "Por favor, informe o seu nome:"  
- **DIFICULDADE INVÁLIDA:** Digitando uma numeração que não está de acordo com a das dificuldades ele retornará: "Nível de dificuldade inválido! Por favor fale com o técnico"
- **SELEÇÃO DO MENU INVÁLIDO:** Selecionando um número diferente do menu 1, 2, 3, retornará "Opção inválida!!"
- **INVALIDO CONTINUAÇÃO OU NÃO DO JOGO:** Ao final da partida ao escolher entre Continuar Jogando ou não, digite um valor que seja diferente tanto de 1 quanto de 2 e ele retornará a pergunta novamente até que o usuário digite uma das duas alternativas. 





