#include "Forca.hpp"
#include <iostream>
#include <stdlib.h>

// CONSTRUTOR
Forca::Forca(std::string palavras, std::string scores) {
  this->m_arquivo_palavras = palavras;
  this->m_arquivo_scores = scores;
  this->m_tentativas_restantes = 6;
}

/*----- FUNÇÃO PARA IDENTIFICAÇÃO DA LETRA DENTRO DO ALFABETO --------*/
bool alfabetico(char letra_verificada) {
  bool esta_no_alfabeto;
  if ((letra_verificada >= 'a' && letra_verificada <= 'z') ||
      (letra_verificada >= 'A' || letra_verificada <= 'Z')) {
    esta_no_alfabeto = true;
  } else {
    esta_no_alfabeto = false;
  }
  return esta_no_alfabeto;
}

/*---------- FUNÇÃO PARA TRANSFORMAR EM MAIÚSCULO ----------*/
std::vector<std::string> Tranforma_Maiusculo(std::vector<std::string> nomes) {
  for (int i = 0; i < nomes.size(); i++) {
    char n_dinamico[nomes[i].size() + 1];
    strcpy(n_dinamico, nomes[i].c_str());
    for (int y = 0; n_dinamico[y] != '\0'; y++) {
      n_dinamico[y] = toupper(n_dinamico[y]);
    }
    std::string tmp_string(n_dinamico);
    nomes[i] = n_dinamico;
  }
  return nomes;
}

void Forca::carregar_arquivos(std::string palavras_arquivo,
                              std::string arquivo_scores) {
  std::cout << "Entramos na leitura de dados" << std::endl;
  // LEITURA DE DADOS DO ARQUIVO PALAVRAS
  std::ifstream dados;
  dados.open(palavras_arquivo,
             std::ios::out |
                 std::ios::in); /// - Abrindo arquivo também para gravação
  std::string nomes_dinamico;
  std::vector<std::string> nomes;
  std::vector<int> nomes_frequencias;

  char *ocorre;
  char *nomes_pointer;
  int retorno = 0;
  long long int inteiro;
  int contador = 0;
  int contador2 = 0;
  std::string numero; 
  std::locale loc;
  
  /*----------------------------------------------*/
  while (std::getline(dados, nomes_dinamico)) {
// VERSÃO ANTERIOR. ESTE É O OVERKILL
    char n_dinamico[nomes_dinamico.size() + 1];
    strcpy(n_dinamico, nomes_dinamico.c_str());
    ocorre = strpbrk(n_dinamico, "1234567890"); //primeira posição que tem número
    nomes_pointer = strstr(n_dinamico, ocorre);
    
    if (nomes_pointer != NULL) {
      std::string tmp_string(n_dinamico);
      nomes_dinamico = n_dinamico;
      nomes_dinamico.erase(nomes_dinamico.find(*nomes_pointer),
                           nomes_dinamico.size() - 1);
      // Converte a string para o inteiro:
      inteiro = atoi(ocorre);
      contador2++;
      nomes_frequencias.push_back(inteiro);
    }

    contador++;
    nomes.push_back(nomes_dinamico);

    /*
    int N = nomes_dinamico.size();
    int posicao_anterior = 1;
    std::size_t found = nomes_dinamico.find_first_of("1234567890");
    std::string espaco = " ";
     std::cout << "Esta linha contém " << nomes_dinamico.size() << " caracteres..." << std::endl;
    if(found!= std::string::npos){
       numero = nomes_dinamico.substr(found, nomes_dinamico.size()-1);
        nomes_dinamico.erase(found,nomes_dinamico.size()-1);
        inteiro = std::stoi(numero);
        nomes_frequencias.push_back(inteiro);
    }
*/
    /*
    for(int i = 0; i < N; i++){   //VERSÃO MELHORADA
      std::cout << "Esta linha contém " << nomes_dinamico.size() << " caracteres..." << std::endl;
      if(std::isdigit(nomes_dinamico[i],loc)){
        std::cout << "PASSEI "<< std::endl;
        numero = nomes_dinamico.substr(i, nomes_dinamico.size()-1);
        nomes_dinamico.erase(i,nomes_dinamico.size()-1);
        inteiro = std::stoi(numero);
        nomes_frequencias.push_back(inteiro);
        i = N-1;
       //;// break;
      }
    }
*/
  //  nomes.push_back(nomes_dinamico);
  }
  nomes = Tranforma_Maiusculo(nomes);
  for (int i = 0; i < nomes.size(); i++) { // nome.sice suspeito
    this->m_palavras.push_back(make_pair(nomes[i], nomes_frequencias[i]));
  }

  ////FUNÇÃO DE CARREGAMENTO DO ARQUIVO DE SCOREES //ATRIBUIÇÃO DE DADOS DO
  ///ARQUIVO SCORES ///////////////////////////////////
  std::ifstream dados_scores(arquivo_scores);
  std::string score_dinamico;
  char *ph;
  int flag = 0;
  std::string dificuldade, jogador_name;
  char *palavras_acertadas;
  std::vector<std::string> palavras_vector_acertadas;
  int pontuacao;

  while (std::getline(dados_scores, score_dinamico)) {
    char s_dinamico[score_dinamico.size()];
    strcpy(s_dinamico, score_dinamico.c_str());
    ph = std::strtok(s_dinamico, ";");
    while (ph != NULL) {
      if (flag == 0) { // primeira vez == DIFICULDADE
        dificuldade = ph;
      } else if (flag == 1) { // segunda vez == NOME
        jogador_name = ph;
      } else if (flag == 2) { // terceira vez == PALAVRAS
        palavras_acertadas = std::strtok(ph, ",");
        while (palavras_acertadas != NULL) {
          palavras_vector_acertadas.push_back(palavras_acertadas);
          palavras_acertadas = std::strtok(NULL, ",");
        }
      } else if (flag == 3) { // quarta vez == PONTUAÇÃO -> tem que ser int()
        std::string tmp_string(ph);
        pontuacao = std::stoi(ph);
      }
      flag++;
      ph = std::strtok(NULL, ";");
    }
    palavras_vector_acertadas.erase(palavras_vector_acertadas.begin(),
                                    palavras_vector_acertadas.end());
    flag = 0;
  }
}

/*--------------------- FUNÇÃO É VÁLIDO()----------------------------*/
std::vector<std::pair<bool, std::string>> Forca::eh_valido() {

  /*std::vector<std::pair<bool, std::string>> eh_valido();*/
  std::vector<std::pair<bool, std::string>> palavra_valida;
  /*------- ARQUIVO DE PALAVRAS -----*/

  std::string palavras_dinamicas;
  int temInvalid = 0;

  std::ifstream obj_palavra(this->m_arquivo_palavras); // levando caminho do arquivo para obj

  if (!obj_palavra) {
    palavra_valida.push_back(
        std::make_pair(false, ANSI_COLOR_RED "Arquivo " +
                                  this->m_arquivo_palavras + " inexistente"));
    temInvalid++;
  } else {

    /*--------SCANEANDO PALAVRAS DO JOGO-----------*/
    for (int i = 0; i < this->m_palavras.size(); i++) {

      /*Separar cada m_palavra por caracteres em letras_scan*/
      std::string palavra_temp = this->m_palavras[i].first;
      char letra[palavra_temp.length()];
      strcpy(letra,
             palavra_temp.c_str()); // Copiando a palavra para array de letras

      std::size_t found = palavra_temp.find_first_not_of(
          "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- "); // ou seja,
                                                                     // encontre
                                                                     // os
                                                                     // números
      for (int cont_letra = 0; cont_letra < palavra_temp.length() - 1;
           cont_letra++) { // o -1 é para não contar com o espaço no final da
                           // palavra
        if (cont_letra >= found) {
          if (letra[cont_letra] == ' ' || letra[cont_letra] == '-') {
            palavra_valida.push_back(std::make_pair(
                false, ANSI_COLOR_RED "Palavra com caractere incorreto na "
                                      "linha " ANSI_COLOR_RESET +
                           std::to_string(i + 1)));
            temInvalid++;
          }
        }

        /*-----Aqui devo colocar a verificação de A - Z-------*/
        if (alfabetico(letra[cont_letra]) == false) {
          palavra_valida.push_back(std::make_pair(
              false, ANSI_COLOR_RED "Palavra com caractere fora do alfabeto na "
                                    "linha " ANSI_COLOR_RESET +
                         std::to_string(i + 1)));
        }
      }
      /*------ bloqueio de error ---- */

      if (this->m_palavras[i].first.size() <= 4) {
        palavra_valida.push_back(std::make_pair(
            false, ANSI_COLOR_RED "Palavra com caracteres insuficientes na "
                                  "linha " ANSI_COLOR_RESET +
                       std::to_string(i + 1)));
        temInvalid++;
      }
      /*---------------------------------- COMPARAÇÃO FREQUENCIAS
       * -------------------------------*/

      std::ifstream dados;
      dados.open(this->m_arquivo_palavras,
                 std::ios::out |
                     std::ios::in); /// - Abrindo arquivo também para gravação
      std::string nomes_dinamico;
      std::vector<std::string> nomes;
      std::vector<int> nomes_frequencias;

      char *ocorre;
      char *nomes_pointer;
      int retorno = 0;
      long int inteiro;

      for (int n = 0; std::getline(dados, nomes_dinamico); n++) {
        char n_dinamico[nomes_dinamico.size() + 1];
        strcpy(n_dinamico, nomes_dinamico.c_str());
        ocorre = strpbrk(n_dinamico, "1234567890");
        nomes_pointer = strstr(n_dinamico, ocorre);
        if (nomes_pointer != NULL) { // MODIFICAÇÃO DE COPIA PARA COMPARAÇÃO DA
                                     // FREQUENCIA BRUTA E FREQUENCIA DO ATRIBUTO
          if (ocorre != std::to_string(this->m_palavras[n].second)) {
        
            palavra_valida.push_back(std::make_pair(
                false, ANSI_COLOR_RED "Palavra com frequência inválida na "
                                      "linha " ANSI_COLOR_RESET +
                           std::to_string(n + 1)));
            std::cout << std::to_string(n + 1) << std::endl;
          }
        } else {
          std::cout << "Sorry. We dont have these numbers";
          retorno = -1;
        }
      }
    }
    /*--------------------------------------------*/

    palavra_valida.push_back(
        std::make_pair(true, ANSI_COLOR_GRAY
                       "Arquivo de Palavras Existente" ANSI_COLOR_RESET));
  }

  /*------- ARQUIVO DE SCORES -----*/
  std::ifstream dados_score;
  std::string Linhas_Score;

  dados_score.open(this->m_arquivo_scores, std::ios::out | std::ios::in);
  if (!dados_score) {

    palavra_valida.push_back(std::make_pair(
        false, ANSI_COLOR_RED "Arquivo " + this->m_arquivo_scores +
                   " inexistente " ANSI_COLOR_RESET));
    temInvalid++;
  } else {
    for (int i = 0; getline(dados_score, Linhas_Score); i++) {

      /*Contar se temos exatamente 3 ; */
      char letras_score[Linhas_Score.size()];
      int contador_ponto_virgula = 0;
      strcpy(letras_score, Linhas_Score.c_str());

      for (int cont_letras = 0; cont_letras < Linhas_Score.size();
           cont_letras++) {
        if (letras_score[cont_letras] == ';') { // letras_score[cont_letras] ==
                                                // 0
          contador_ponto_virgula++;
          if (letras_score[cont_letras - 1] == NAN ||
              letras_score[cont_letras - 2] == ';') {
            palavra_valida.push_back(std::make_pair(
                false, ANSI_COLOR_RED "Campo vazio na linha " ANSI_COLOR_RESET +
                           std::to_string(i + 1)));
            temInvalid++;
          }
        }
      }
      if (contador_ponto_virgula != 3) {
        palavra_valida.push_back(std::make_pair(
            false,
            ANSI_COLOR_RED
                "Score com ; diferente de 3 campos na linha " ANSI_COLOR_RESET +
                std::to_string(i + 1)));
        temInvalid++;
      }

      /*Encontrar meio de ele identificar se um dos campos está vazio*/
    }
    palavra_valida.push_back(std::make_pair(
        true, ANSI_COLOR_GRAY "Arquivo de Scores existente" ANSI_COLOR_RESET));
  }
  if (temInvalid == 0) {
    palavra_valida.push_back(std::make_pair(
        true, ANSI_COLOR_GRAY "Tudo está de acordo!" ANSI_COLOR_RESET)); ///?
  }
  return palavra_valida;
}
/*----------------------------- FIM DA FUNÇÃO EH_VALIDO
 * ---------------------------------------*/

// PARA INICIALIZAR A DIFICULDADE DO JOGO --MAIN
void Forca::set_dificuldade(Forca::Dificuldade d) { this->m_dificuldade = d; }

int Forca::busca(char *S, std::string palavra) {
  for (int i = 0; i < this->m_palavras.size(); i++) {
    if (palavra.compare(this->m_palavras[i].first) == 0) {
      return this->m_palavras[i].second;
    }
  }
  return 0;
}

/* ----------------------- FUNÇÃO SORTEIO DE PALAVRAS
 * -------------------------*/
void Forca::SorteioPalavras() {
  this->m_palavras_do_jogo.resize(1); //é eisso mesmo?
  int frequencia_media = 0;
  int frequencia_atual = 0;
  for (int i = 0; i < this->m_palavras.size(); i++) {
    frequencia_media = frequencia_media + this->m_palavras[i].second;
  }
  frequencia_media = frequencia_media / this->m_palavras.size();
  // SEGUNDA PARTE
  int x;
  std::string palavra;
  char *S;
  /*------ DIFICULDADE FÁCIL ----*/
  switch (this->m_dificuldade) {
  case FACIL: {
    for (int i = 0; this->m_palavras_do_jogo.size() < 10; i++) {
      x = std::rand() % this->m_palavras.size();
      palavra = this->m_palavras[x].first;
      frequencia_atual = busca(S, palavra);
      if (frequencia_atual > frequencia_media) {
        this->m_palavras_do_jogo.push_back(palavra);
      }
    }
    // EMBARALHAR A ORDEM
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->m_palavras_do_jogo.begin(),
                 this->m_palavras_do_jogo.end(),
                 std::default_random_engine(seed));

    this->m_palavra_atual = this->m_palavras_do_jogo[0];
    this->m_palavras_do_jogo.erase(this->m_palavras_do_jogo.begin() + 0);
    break;
  }
    /*------DIFICULDADE MÉDIA--------*/
  case MEDIO: {
    int flag = 0;
    int flag_maior_media = 0;
    for (int i = 0; this->m_palavras_do_jogo.size() < 20; i++) {
      while (flag < 7 ||
             flag_maior_media < 13) { // frequencias menores do que a média
        x = std::rand() % this->m_palavras.size();
        palavra = this->m_palavras[x].first;
        frequencia_atual = busca(S, palavra);

        if (frequencia_atual < frequencia_media) {
          if (flag < 7) {
            this->m_palavras_do_jogo.push_back(palavra);
            flag++;
          }
        } else if (frequencia_atual >= frequencia_media) {
          if (flag_maior_media < 13) {
            this->m_palavras_do_jogo.push_back(palavra);
            flag_maior_media++;
          }
        }
      }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->m_palavras_do_jogo.begin(),
                 this->m_palavras_do_jogo.end(),
                 std::default_random_engine(seed));
    this->m_palavra_atual = this->m_palavras_do_jogo[0];
    this->m_palavras_do_jogo.erase(this->m_palavras_do_jogo.begin() + 0);
    break;
  }
    /*----------DIFICULDADE HARDCORE--------*/
  case DIFICIL: {
    int flag_menor_media = 0;
    int flag_maior_media = 0;
    for (int i = 0; this->m_palavras_do_jogo.size() < 30; i++) {
      while (flag_menor_media < 23 || flag_maior_media < 7) {
        x = std::rand() % this->m_palavras.size();
        palavra = this->m_palavras[x].first;
        frequencia_atual = busca(S, palavra);
        if (frequencia_atual < frequencia_media) {
          if (flag_menor_media < 23) {
            this->m_palavras_do_jogo.push_back(palavra);
            flag_menor_media++;
          }
        } else if (frequencia_atual >= frequencia_media) {
          if (flag_maior_media < 7) {
            this->m_palavras_do_jogo.push_back(palavra);
            flag_maior_media++;
          }
        }
      }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->m_palavras_do_jogo.begin(),
                 this->m_palavras_do_jogo.end(),
                 std::default_random_engine(seed));
    this->m_palavra_atual = this->m_palavras_do_jogo[0];
    this->m_palavras_do_jogo.erase(this->m_palavras_do_jogo.begin() + 0);
    break;
  }
  default: {
    std::cout << ANSI_COLOR_RED "Nível de dificuldade inválido! Por favor fale com o técnico" ANSI_COLOR_RESET<< std::endl;
    break;
  }
  }
}
/*---------------- FUNÇÃO PROXIMA PALAVRA ---------------------*/
std::string Forca::proxima_palavra() {
  this->m_tentativas_restantes = 6;
  SorteioPalavras();
  std::string prox_palavra = this->m_palavra_atual;
  this->m_palavra_jogada = prox_palavra;
  std::size_t found;
  std::size_t found2 = this->m_palavra_jogada.find("-");
  std::string espaco = " ";

  found = this->m_palavra_jogada.find_first_not_of(
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ  ");
  found2 = this->m_palavra_jogada.find_first_of(" ");
  if (found2 != std::string::npos || found != std::string::npos) {
    if (found != std::string::npos) { //É O TRAÇO
      this->m_palavra_jogada.replace(
          this->m_palavra_jogada.begin() + found,
          this->m_palavra_jogada.end() -
              (this->m_palavra_jogada.size() - 1 - found),
          "-");
      for (int i = 0; i < found; i++) {
        this->m_palavra_jogada.replace(
            this->m_palavra_jogada.begin() + i,
            this->m_palavra_jogada.end() -
                (this->m_palavra_jogada.size() - 1 - i),
            "_");
      }
      for (int i = found + 1; i < this->m_palavra_jogada.size(); i++) {
        if (this->m_palavra_jogada[i] != ' ') {
          this->m_palavra_jogada.replace(
              this->m_palavra_jogada.begin() + i,
              this->m_palavra_jogada.end() -
                  (this->m_palavra_jogada.size() - 1 - i),
              "_");
        }
      }

    } else if (found2 !=
               std::string::npos) { //É O ESPAÇO. AQUI CONSIDERO QUE SÓ PODE TER
                                    //OU TRAÇO OU O ESPAÇO. NUNCA TRAÇO E ESPAÇO
                                    //(nO CASO, TALVEZ SIM PELO FOR NO ALGORITMO
                                    //DO TRAÇO, MAS ENFIM, AQUI PARECE ISSO)
      this->m_palavra_jogada.replace(
          this->m_palavra_jogada.begin() + found2,
          this->m_palavra_jogada.end() -
              (this->m_palavra_jogada.size() - 1 - found2),
          " ");

      for (int i = 0; i < found2; i++) {
        this->m_palavra_jogada.replace(
            this->m_palavra_jogada.begin() + i,
            this->m_palavra_jogada.end() -
                (this->m_palavra_jogada.size() - 1 - i),
            "_");
      }

      for (int i = found2 + 1; i < this->m_palavra_jogada.size(); i++) {
        if (this->m_palavra_jogada[i] != ' ') {
          this->m_palavra_jogada.replace(
              this->m_palavra_jogada.begin() + i,
              this->m_palavra_jogada.end() -
                  (this->m_palavra_jogada.size() - 1 - i),
              "_");
        }
      }
    }
  } else {
  }

  // SEGUNDA PARTE -> APARECER AS LETRAS DE ACORDO C A DIFICULDADE PARA O
  // USUÁRIO
  if (this->m_dificuldade == FACIL) {
    int consoantes_na_tela = std::max(1, (int)(this->m_palavra_jogada.size() / 5));
    int flag = 0;
    std::vector<int> pos_consoantes;
    std::string palavra_next_without_consoantes = prox_palavra;
    std::size_t consoantes =
        palavra_next_without_consoantes.find_first_not_of("aeiou- ");

    if (consoantes != std::string::npos) {
      for (int i = 0; i < prox_palavra.size(); i++) {
        if (consoantes != std::string::npos) {
          pos_consoantes.resize(flag + 1);
          pos_consoantes[flag] = consoantes;
          palavra_next_without_consoantes.replace(
              palavra_next_without_consoantes.begin() + pos_consoantes[flag],
              palavra_next_without_consoantes.begin() + pos_consoantes[flag] +
                  1,
              "a"); // substituo a consoante pela letra a na palavra
          consoantes = palavra_next_without_consoantes.find_first_not_of(
              "aeiou "); // para encontrar a próxima consoante
          flag++;
        }
      }

      int x = rand() % pos_consoantes.size();
      for (int i = 0; i < consoantes_na_tela; i++) {
        this->m_palavra_jogada[pos_consoantes[x]] =
            prox_palavra[pos_consoantes[x]];
        x = rand() % pos_consoantes.size();
      }
    }

  } else if (this->m_dificuldade == MEDIO) {
    std::string palavra_next_vogais = prox_palavra;
    std::size_t vogal = palavra_next_vogais.find_first_not_of(
        "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ ");
    std::vector<int> pos_vogais;
    int flag = 0;
    if (vogal != std::string::npos) {
      for (int i = 0; i < prox_palavra.size(); i++) {
        if (vogal != std::string::npos) {
          pos_vogais.resize(flag + 1);
          pos_vogais[flag] = vogal;
          palavra_next_vogais.replace(
              palavra_next_vogais.begin() + pos_vogais[flag],
              palavra_next_vogais.begin() + pos_vogais[flag] + 1, "J");
          vogal = palavra_next_vogais.find_first_not_of(
              "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ ");
          flag++;
        }
      }
      int x = rand() % pos_vogais.size();
      this->m_palavra_jogada[pos_vogais[x]] = prox_palavra[pos_vogais[x]];
    }
  }
  /* ->> PARA FACILITAR EM CÁLCULOS A POSTERIORI, FAREMOS APENAS O PRINT DESSA
     FORMA NO MAIN
      //ADICIONA OS ESPAÇOS PARA MELHOR VISUALIZAÇÃO
      for(int i = 0; i < this->m_palavra_jogada.size();i++){
            if(i%2!=0){
                this->m_palavra_jogada.insert(i," ");
            }
      }
  */
  return this->m_palavra_jogada;
}

/*------------------------ FUNÇÃO DE PALPITE
 * -------------------------------------*/
std::pair<bool, bool> Forca::palpite(std::string palpite) {
  std::pair<bool, bool> return_palpite;
  bool check = true;
  char letras_Palavra[this->m_palavra_atual.size()];
  strcpy(
      letras_Palavra,
      this->m_palavra_atual.c_str()); // Copiando a palavra para array de letras

  if (this->m_letras_palpitadas.size() == 0) {
    this->m_letras_palpitadas.push_back(palpite[0]);
    // acho que é um caso em que a palavra  nunca foi palpitada e existe na
    // string
  } else {

    for (auto letras_doBanco_palpite : this->m_letras_palpitadas) {
      if (palpite[0] ==
          letras_doBanco_palpite) { // se palpite ja for palpitado antes
        check = false;              // aqui
        int letra_repetida_acertada = 0;
        for (auto letra : letras_Palavra) {
          if (letra == letras_doBanco_palpite) {
            std::cout << ANSI_COLOR_RED
                "ERROR! Essa letra que pertence a palavra já foi palpitada anteriormente" ANSI_COLOR_RESET
                      << std::endl;
            return_palpite = std::make_pair(true, false);
            letra_repetida_acertada++;
            break;
          }
        }
        if (letra_repetida_acertada ==
            0) { // Existe letras palpitadas repetidas iguais a palavra?
                 // senão...
          std::cout << ANSI_COLOR_RED
              "a e não pertence a palavra" ANSI_COLOR_RESET
                    << std::endl;
          return_palpite =
              std::make_pair(false, false); // letra palpitada e errada
          break;
        }
      }
    }
  }

  bool letra_igual = false;
  if (check == true) { // se ele continuar true
    this->m_letras_palpitadas.push_back(
        palpite[0]); // quer dizer que ele nao foi chamado entao incrementa
    for (int i = 0; i < this->m_palavra_atual.size(); i++) {
      if (letras_Palavra[i] == palpite[0]) {
        letra_igual = true;
      }
    }
  }
  if (check == true) {
    if (letra_igual == true) {
      std::cout << ANSI_COLOR_GREEN "ACERTOU! Continue assim 😃" ANSI_COLOR_RESET <<std::endl;
      return_palpite = std::make_pair(true, true);
    } else {
      std::cout << ANSI_COLOR_RED "ERROU! 😡" ANSI_COLOR_RESET <<std::endl;
      return_palpite = std::make_pair(false, true);
      this->m_tentativas_restantes--;
      this->m_pontos_partida--;
      interfaceBoneco();
    }
  }

  return return_palpite;
}

/*------------------ FUNÇÃO DA INTERFACE DO BONECO -----------------*/

void Forca::interfaceBoneco() {
  std::ifstream boneco;
  boneco.open("boneco.txt", std::ios::out | std::ios::in);
  std::cout << ANSI_COLOR_RED "Você ainda tem "
            << this->m_tentativas_restantes << " tentativas restantes" ANSI_COLOR_RESET << std::endl;
  if (!boneco) {
    std::cout << ANSI_COLOR_RED
        "Arquivo boneco.txt não encontrado" ANSI_COLOR_RESET
              << std::endl;
    exit(-1);
  } else {
    std::string exibe_boneco;
    switch (this->m_tentativas_restantes) {
    case 6:
      for (int i = 0; getline(boneco, exibe_boneco); i++) { // SOMENTE A CORDA
        if (i < 5) {
          std::cout << exibe_boneco << std::endl;
        }
      }
      break;
    case 5:
      for (int i = 0; getline(boneco, exibe_boneco); i++) { // A CABEÇA
        if (i <= 12) {
          std::cout << exibe_boneco << std::endl;
        }
      }
      break;
    case 4:
      for (int i = 0; getline(boneco, exibe_boneco); i++) { // O CORPO
        if (i <= 20) {
          std::cout << exibe_boneco << std::endl;
        }
      }
      break;
    case 3:
      for (int i = 0; getline(boneco, exibe_boneco);
           i++) { // PRIMEIRA PERNA 22 - 52
        if (i >= 22 && i <= 51) {
          std::cout << exibe_boneco << std::endl;
        }
      }
      break;
    case 2:
      for (int i = 0; getline(boneco, exibe_boneco);
           i++) { // AS DUAS PERNAS 53 - 82
        if (i >= 53 && i <= 82) {
          std::cout << exibe_boneco << std::endl;
        }
      }
      break;
    case 1:
      for (int i = 0; getline(boneco, exibe_boneco);
           i++) { // PRIMEIRO BRAÇO 85 - 114
        if (i >= 85 && i <= 114) {
          std::cout << exibe_boneco << std::endl;
        }
      }
      break;
    case 0:
      for (int i = 0; getline(boneco, exibe_boneco); i++) { // TUDO 116 - 145
        if (i >= 116 && i <= 145) {
          std::cout << exibe_boneco << std::endl;
        }
      }
      break;
    }
  }
}
/*------------ FUNÇÃO ATUALIZAÇÃO DA QUANTIDADE DE LINHAS DO ARQUIVO SCORES -------------------*/
int quantidadeLinhas(){
  std::ifstream arquivo_scores;
   std::string scores_tela;
  int quantidade_linhas = 0;
  arquivo_scores.open("scores.txt", std::ios::out | std::ios::in);
  for (quantidade_linhas = 0; getline(arquivo_scores, scores_tela); quantidade_linhas++){}
  return quantidade_linhas; //mudei por conta da última linha
}

/*------------- FUNÇÃO DE MOSTRAR SCORES NA TELA EM CONSTRUÇÃO ---------------*/

void Forca::mostrarScore() {
  std::ifstream scores;
  scores.open("scores.txt", std::ios::out | std::ios::in);
  std::string scores_tela;
  std::string scores_tela_tamanho;
  int tamanho_arquivo = quantidadeLinhas(); //a última linha do arquivo sempre é 'zerada', coloquei o -1 para ver se era isso que tava dando errado
  int espaco_dificuldade[50];
  int espaco_jogador[50];
  int espaco_pontos[50];
  int espaco_palavras[50];


  if (!scores) { // Vai que deletem o arquivo scores quando tiver em execução...
    std::cout << ANSI_COLOR_RED
        "Arquivo scores.txt não encontrado" ANSI_COLOR_RESET<< std::endl;
  } else {
    std::string matriz_scores[tamanho_arquivo][4];
    
    for (int i = 0; getline(scores, scores_tela); i++) {
        std::string campo_dinamico_palavras;
        std::string campo_dinamico_dificuldade;
        std::string campo_dinamico_jogador;
        std::string campo_dinamico_pontos;
  
        espaco_dificuldade[i] = 0;
        espaco_jogador[i] = 0;
        espaco_pontos[i] = 0;
        espaco_palavras[i] = 0;
  
        int encontrar_vazio = 0; //encontre campos vazios na palavra.
        char encontrar_ponvi[scores_tela.size()];
        std::strcpy(encontrar_ponvi,scores_tela.c_str()); // Copiando a linha para array de letras
        int achamos_ponvi = 0;
  
        for (int pont = 0; pont <= sizeof encontrar_ponvi; pont++) {
          
          if (encontrar_ponvi[pont] == ';') {
            achamos_ponvi++; 
          } else {
            switch (achamos_ponvi) {
            case 0:
              campo_dinamico_dificuldade += encontrar_ponvi[pont];
              espaco_dificuldade[i]++;
              break;
            case 1:
              campo_dinamico_jogador += encontrar_ponvi[pont];
              espaco_jogador[i]++;
              break;
            case 2:
              if(encontrar_ponvi[pont] == ' '){
                encontrar_vazio++;
              }
              if (encontrar_ponvi[pont] == ',') {
                campo_dinamico_palavras += ' ';
              } 
              else {
                campo_dinamico_palavras += encontrar_ponvi[pont];
              }
              espaco_palavras[i]++;
              break;
            case 3:
              campo_dinamico_pontos += encontrar_ponvi[pont];
              espaco_pontos[i]++;
              break;
            }
          }
        }
        /*--------------- PREENCHER <nenhuma> EM CAMPOS VAZIOS DE PALAVRAS ---------------*/
        if(encontrar_vazio == espaco_palavras[i]){
          campo_dinamico_palavras = "<nenhuma>";
        }
        
        /*--------------------------INCREMENTAÇÃO NA MATRIZ SCORES------------------------*/
        matriz_scores[i][0] = campo_dinamico_dificuldade;
        matriz_scores[i][1] = campo_dinamico_jogador;
        matriz_scores[i][2] = campo_dinamico_palavras;
        matriz_scores[i][3] = campo_dinamico_pontos;        

      
    } //----
    std::cout << "Dificuldade     |      Jogador     |     Pontos      |  Palavras"
              << std::endl;
    for (int linha = 0; linha < tamanho_arquivo; linha++) {
      espaco_dificuldade[linha] = 12 - espaco_dificuldade[linha]; //quanto de espaço precisa
      espaco_jogador[linha] = 12 - espaco_jogador[linha];
      espaco_pontos[linha] = 12 - espaco_pontos[linha];
      /*DIFICULDADE*/
      for(int i = 0; i < espaco_dificuldade[linha]; i++){
        matriz_scores[linha][0] +=" ";
      } 
      /*JOGADOR*/
      for(int a = 0; a < espaco_jogador[linha]; a++){
        matriz_scores[linha][1] +=" ";
      } 
      /*PONTOS*/
      for(int b = 0; b < espaco_pontos[linha]; b++){
        matriz_scores[linha][3] +=" ";
      } 
      
      std::cout<< ANSI_COLOR_GRAY "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" ANSI_COLOR_RESET <<std::endl;
      std::cout << ANSI_COLOR_RED << matriz_scores[linha][0] << ANSI_COLOR_YELLOW << "     ▇ " << ANSI_COLOR_MAGENTA << matriz_scores[linha][1]<<"     ▇ " << ANSI_COLOR_BLUE << matriz_scores[linha][3] << "     ▇ "<< ANSI_COLOR_YELLOW << matriz_scores[linha][2] << ANSI_COLOR_RESET <<std::endl;
    }
  }
}

/* ----- FUNÇÃO PARA MOSTRAR REALMENTE QUAL É A PALAVRA QUE TAVA SENDO JOGADA
 * ATUALMENTE */

std::string Forca::get_palavra_atual() {
  /* No caso de Game Over, mostrar palavra que estava sendo jogada */
  return this->m_palavra_atual;
}

std::string Forca::get_palavra_jogada() { return this->m_palavra_jogada; }

void Forca::set_palavra_jogada(std::string palavra_jogada) {
  this->m_palavra_jogada = palavra_jogada;
}

int Forca::get_tentativas_restantes() { return this->m_tentativas_restantes; }

void Forca::set_tentativas_restantes(int tentativas) {
  this->m_tentativas_restantes = tentativas;
}

void Forca::set_pontos_partida(int pontos) { this->m_pontos_partida = pontos; }

int Forca::get_pontos_partida() { return this->m_pontos_partida; }

bool Forca::rodada_terminada() {
  if (this->m_palavra_jogada == this->m_palavra_atual ||
      this->m_tentativas_restantes == 0) {
    return true;
  } else {
    return false;
  }
}

void Forca::reset_rodada() {
  this->m_tentativas_restantes = 5;
  this->m_letras_palpitadas.clear();
}

void Forca::proximo_jogador() {
  this->m_tentativas_restantes = 6;
  this->m_letras_palpitadas.clear();
  this->m_palavra_jogada = " ";
  this->m_palavra_atual = " ";
  this->m_pontos_partida = 0;
  this->palavras_acertadas.clear();
}

void Forca::set_letras_palpitadas(char letra) {
  this->m_letras_palpitadas.push_back(letra);
}

void Forca::palavras_acertadas_do_jogador(std::string palavra) {
  this->palavras_acertadas.push_back(palavra);
}

std::vector<std::string> Forca::get_palavras_acertadas() {
  return this->palavras_acertadas;
}

void Forca::set_m_letras_palpitadas(std::string palpite) {
  this->m_letras_palpitadas.push_back(palpite[0]);
}

void Forca::game_over(){ //imprime a arte GAME OVER
  std::ifstream arquivo_over;
  arquivo_over.open("gameover.txt", std::ios::out | std::ios::in);
  std::string arte_game_over;
  if(!arquivo_over){
    std::cout<< ANSI_COLOR_RED "Arquivo gameover.txt não encontrado, por favor falar com o técnico" ANSI_COLOR_RESET<<std::endl;
  } else{
    for(int i = 0; getline(arquivo_over, arte_game_over); i++){
      std::cout<< ANSI_COLOR_RED << arte_game_over << ANSI_COLOR_RESET <<std::endl;
    }
  }
}