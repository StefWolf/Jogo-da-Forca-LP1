#include <iostream>
#include <locale>
#include "Forca.hpp"

void clear(){
  std::cout<< "\033[2J\033[1;1H";
}
void limpabuffer(){
  char c;
  while((c=getchar()) != '\n' && c != EOF);
}

using namespace std;
int main(int argc, char *argv[]){
    std::srand(time(nullptr));
    Forca forca((std::string)argv[1],(std::string) argv[2]); 
    std::cout << ">>> Lendo arquivos de palavras [" << (std::string)argv[1] <<"] e scores [" << (std::string)argv[2] << "], por favor aguarde..." << std::endl;
    std::cout << ANSI_COLOR_BLUE "⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯" ANSI_COLOR_RESET << std::endl;
  
    forca.carregar_arquivos((std::string)argv[1], (std::string)argv[2]);
    auto valid = forca.eh_valido();
  
    if(!valid[0].first){ //sai do programa ao encontrar um erro
        cout<<"Erro "<<valid[0].second<<endl;
        exit(-1);
    } else {
        for(int i = 0; i < valid.size(); i++){
          if(valid[i].first == false){
            std::cout<<ANSI_COLOR_RED "Opa! Algo não está de acordo.\n" ANSI_COLOR_RESET<<std::endl;
            for(int print = 0; print < valid.size(); print++){ //Trazer log de todos os erros
              std::cout<<valid[print].first<<" - "<<valid[print].second<<std::endl;
            }
            exit(-1);
          } 
        }
      }
    
    std::cout << ANSI_COLOR_GREEN">>> Arquivos OK ✅ \n Iniciando o jogo..." ANSI_COLOR_RESET << std::endl;
    std::cout << ANSI_COLOR_BLUE "⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯" ANSI_COLOR_RESET << std::endl;
    std::this_thread::sleep_for(2000ms);
  clear();
  
  int flag_boneco = 0;
  int flag_palpite = 0;
    while(true){
      int op;
        /*imprime o menu principal e a escolha do usuário*/
      std::cout<<"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"<<std::endl;
      std::cout<<"▇▇▇▇▇▇▇▇▇▓▒░"<<ANSI_COLOR_YELLOW<< "ＢＥＭ" <<ANSI_COLOR_BLUE<< " ＶＩＮＤＯ（Ａ）" <<ANSI_COLOR_GREEN<< " ＡＯ" <<ANSI_COLOR_CYAN<< " ＪＯＧＯ" <<ANSI_COLOR_RED<< " ＤＡ"<<ANSI_COLOR_MAGENTA<< " ＦＯＲＣＡ"<<ANSI_COLOR_RESET<< "░▒▓▇▇▇▇▇▇▇▇▇ "<< std::endl;
      std::cout<<"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"<<std::endl;
      std::cout << ANSI_COLOR_BLUE "                        1 - INICIAR JOGO " ANSI_COLOR_RESET << std::endl;
      std::cout << ANSI_COLOR_BLUE "                        2 - SCORES ANTETIORES" ANSI_COLOR_RESET << std::endl;
      std::cout << ANSI_COLOR_BLUE "                        3 - SAIR " ANSI_COLOR_RESET << std::endl;
      std::cout << ">>> Sua escolha: ";
      std::cin >> op;

      clear();
      
        if(op == 1){
            std::cout<<"▇▇▇▇▇▇▇▇▇▓▒░        SELEÇÃO DE DIFICULDADE         ░▒▓▇▇▇▇▇▇▇▇▇ "<< std::endl;
            std::cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << std::endl;
            std::cout << ANSI_COLOR_GREEN "    1 - Fácil    " << ANSI_COLOR_BLUE "    2 - Médio    " <<  ANSI_COLOR_RED "    3 - Difícil" ANSI_COLOR_RESET << std::endl;
            
            int escolha;
            std::cout << ANSI_COLOR_MAGENTA " >> SUA ESCOLHA: " ANSI_COLOR_RESET <<std::endl;
            std::cin >> escolha;

            clear();
          
            Forca::Dificuldade d;
            if(escolha == 1){
                std::cout << ANSI_COLOR_GREEN "▇▇▇▇▇▇▇▇▇ INICIANDO O JOGO NO NÍVEL FÁCIL, SERÁ QUE VOCÊ CONHECE ESSA PALAVRA? ▇▇▇▇▇▇▇▇▇" ANSI_COLOR_RESET << std::endl;
                d = Forca::Dificuldade::FACIL;
            }else if(escolha == 2){
                std::cout << ANSI_COLOR_GREEN "▇▇▇▇▇▇▇▇▇ INICIANDO O JOGO NO NÍVEL MÉDIO, SERÁ QUE VOCÊ CONHECE ESSA PALAVRA? ▇▇▇▇▇▇▇▇▇" ANSI_COLOR_RESET << std::endl;
                d = Forca::Dificuldade::MEDIO;
            }else if(escolha == 3){
                std::cout << ANSI_COLOR_GREEN "▇▇▇▇▇▇▇▇▇ INICIANDO O JOGO NO NÍVEL DIFÍCIL, SERÁ QUE VOCÊ CONHECE ESSA PALAVRA? ▇▇▇▇▇▇▇▇▇" ANSI_COLOR_RESET << std::endl;
                d = Forca::Dificuldade::DIFICIL;
            }
            forca.set_dificuldade(d);
            //PARA RODAR O JOGO
             while(true){ //ENQUANTO O USER ESTIVER JOGANDO       
                string p = forca.proxima_palavra(); 
                limpabuffer(); 
                while (!forca.rodada_terminada()){
                    string palavra_m_jogada = forca.get_palavra_jogada();
                    for(int i = 0; i < palavra_m_jogada.length();i++){
                        std::cout << palavra_m_jogada[i];
                        std::cout << " ";
                    }
                    std::cout << std::endl;
                    std::cout<< ANSI_COLOR_BLUE "_____________" ANSI_COLOR_RESET<<std::endl;
                    std::cout << ANSI_COLOR_BLUE ">> Pontos: " << forca.get_pontos_partida() << ANSI_COLOR_RESET << std::endl; //colocar os pontos aqui
                    std::cout<<"_____________"<<std::endl;
                    string palpite;
                    std::cout<< ANSI_COLOR_BLUE ">> Palpite: " ANSI_COLOR_RESET <<std::endl;
                    std::cin >> palpite;
                    clear();

                    //DEIXA O PALPITE EM MAIÚSCULO
                    char * palp_char = new char[palpite.length()+1];
                    std::strcpy(palp_char, palpite.c_str());
                    palp_char[0] = toupper(palp_char[0]);
                    std::string palpite_string(palp_char);
                    
                    std::pair<bool,bool>result_palpite = forca.palpite(palpite_string);
                    int tentativas = forca.get_tentativas_restantes();
                    int pontos = forca.get_pontos_partida();
                    //CONDICIONAIS DE VERIFICAÇÃO DO RESULTADO result_palpite
                    bool mais_de_uma_letra = false;
                    int quantidade_letras = 0;
                    if((result_palpite.first == true) && (result_palpite.second == true)){//ainda não foi jogada
                      std::string palavra_jogada = forca.get_palavra_jogada();
                      std::string palavra_atual = forca.get_palavra_atual();

                      //PARA SABER QUANTAS LETRAS IGUAIS TEM NA PALAVRA
                      for(int i = 0; i < palavra_atual.size(); i++){
                          if(palavra_atual[i] == palp_char[0]){
                            quantidade_letras++;
                            if(quantidade_letras >= 2){
                              mais_de_uma_letra = true;
                            }
                            palavra_jogada[i] = palp_char[0];
                            
                          }
                      }
                      quantidade_letras = 0;
                      //////////////////VERIFICAÇÃO SE A LETRA JÁ NÃO FOI MOSTRADA PARA O USUÁRIO
                      //PARA SABER SE JÁ APARECEU ALGUMA NO M_PALAVRA_JOGADA
                      std::string palavra_underscores = forca.get_palavra_jogada();
                      bool apareceu = false;
                      for(int i = 0; i < palavra_underscores.size(); i++){
                        if(palavra_underscores[i] == palp_char[0]){
                          //então já tá amostrada
                          std::cout << palavra_underscores[i] << std::endl;
                          apareceu = true;
                        }
                      }
                      
                      if((apareceu == true) && (mais_de_uma_letra == false)){
                        forca.set_pontos_partida(pontos); //Então, a única aparição desta letra foi a que apareceu ao user, ele não ganha ponto por digitá-la no seu palpite
                        apareceu = false;
                        mais_de_uma_letra = true;
                      }else{
                        forca.set_pontos_partida(pontos+2); //caso não, ele ganha
                      }
                      ////////////////////////////////////////////
                      forca.set_palavra_jogada(palavra_jogada);
                    }else if(result_palpite.first == true && result_palpite.second == false){//palpite já foi lançado e a letra não pertence a palavra
                      forca.set_pontos_partida(pontos-1); 
                  
                    }else if(result_palpite.first == false && result_palpite.second == true){ //a letra não pertence a palavra
                      std::cout << "Perdeu uma tentativa" << std::endl;
                      forca.set_tentativas_restantes(tentativas--);
                    }
                    delete[] palp_char;
                }
               
                if(forca.get_palavra_atual().compare(forca.get_palavra_jogada())==0){ //se acertou toda a palavra
                  bool ja_tem = false;
                  ///VERIFICAÇÃO SE O USUÁRIO JÁ NÃO ACERTOU ESSA PALAVRA
                  std::vector<std::string> vetor_testes = forca.get_palavras_acertadas();
                  for(int i = 0; i < forca.get_palavras_acertadas().size(); i++){
                    if(vetor_testes[i].compare(forca.get_palavra_atual())==0){
                      ja_tem = true;
                    }
                  }
                  if(ja_tem == false){
                    forca.palavras_acertadas_do_jogador(forca.get_palavra_atual());
                  }
                  clear();  
                  std::cout << "Deseja continuar jogando?"<< ANSI_COLOR_GREEN <<"| 1- SIM |" << ANSI_COLOR_RED <<"| 2- NÃO |" ANSI_COLOR_RESET<<std::endl;
                  int opcao;
                  std:: cin >> opcao;
                  clear();
                  //CONDICIONAL DE SEGURANÇA CONTRA A QUEBRA DO CÓDIGO. 
                  bool rodar_while = false;
                  if(opcao <= 0 || opcao >=3){
                    rodar_while = true;
                    clear();
                  }
                  while(rodar_while){ 
                    std::cout << "Essa opção é inválida" << std::endl;
                    std::cout << "Por favor, digite novamente a sua escolha: " << ANSI_COLOR_GREEN <<"| 1- SIM |" << ANSI_COLOR_RED <<"| 2- NÃO |" ANSI_COLOR_RESET<<std::endl;
                    std:: cin >> opcao;
                    if(opcao ==1 || opcao==2){
                      break;
                    }
                    clear();
                  }
                  ////////////////////////////// CONFERE A OPÇÃO ESCOLHIDA
                    if (opcao == 2){
                      break;
                    } else if(opcao == 1){
                      forca.reset_rodada();    
                    }
                        
                }else{//perdeu, é um GAME OVER
                  clear(); 
                  forca.game_over();
                  std::cout<<std::endl;
                  std::cout << ANSI_COLOR_GREEN "Esta era a palavra correta: " << forca.get_palavra_atual() << ANSI_COLOR_RESET<<std::endl;
                    break;
                }
            } 
              
            /*ler informações do jogador para o score e gravar no arquivo*/
              std::cout << "Por favor, informe o seu nome: ";
              std::string error;
              std::string nome_jogador;
              std::cin >> nome_jogador;
             // std::cin >> error;
             // std::cout << nome_jogador << std::endl;
             // std::size_t found =  nome_jogador.find(" "); 
          /*
              if(found!=std::string::npos){
                std::cin >> error;
                break;
              } */
              while(nome_jogador.find(";")!=std::string::npos){
                std::cout << ANSI_COLOR_RED "Por favor, informe o seu nome: " ANSI_COLOR_RESET;
                std::cin >> nome_jogador;
              //  std::cin >> error;
              }
              while(nome_jogador.size()==1){
                std::cout << ANSI_COLOR_RED "Por favor, informe o seu nome: " ANSI_COLOR_RESET;
                std::cin >> nome_jogador;
               /* if(nome_jogador.find(" ")!=std::string::npos){
                  std::cin >> error;
                  break;
                } */
              }
            //std::cout << nome_jogador << std::endl;
              //TRANFERE O NOME PARA MAIÚSCULO
          
              std::locale loc;
              for(int i = 0; i < nome_jogador.size(); i++){
                if(nome_jogador[i] == ' '){
                  nome_jogador[i] = nome_jogador[i];
                }else{
                  std::toupper(nome_jogador[i],loc); 
                }
              }
          
              clear(); 
              
              //GRAVAR AS INFORMAÇÕES DO JOGADOR NO ARQUIVO
              std::ofstream f_out;
              f_out.open("scores.txt",ios::app);
  
              if(!f_out.good()){
                return -1;
              }else{
                string dificuldade_jogador = std::to_string(d); 
                if(d == 1){
                  dificuldade_jogador = "FÁCIL";
                }else if(d==2){
                  dificuldade_jogador = "MÉDIO";
                }else if(d==3){
                  dificuldade_jogador = "DIFÍCIL";
                }
                f_out << dificuldade_jogador << ";" << nome_jogador << ";";
                
                std::vector<std::string> vetor_pal_acertadas = forca.get_palavras_acertadas();
                if(vetor_pal_acertadas.size()>0){
                  for(int i = 0; i < forca.get_palavras_acertadas().size(); i++){
                    if(i+1 == forca.get_palavras_acertadas().size()){
                      f_out << vetor_pal_acertadas[i] << ";";
                    }else{
                      f_out << vetor_pal_acertadas[i] << ",";   
                    }
                  }
                }else{
                  f_out << ";";
                }
                
                f_out << forca.get_pontos_partida() << std::endl;
              }
              f_out.close();
              forca.proximo_jogador(); 
            
        }else if(op == 2){
          forca.mostrarScore();
        }else if(op == 3) { //se o usuário digitar qualquer outro número além de 3, ele saí do jogo também
          exit(-1);
        }else if(op <= 0 || op > 3){
          std::cout << ANSI_COLOR_RED "Opção inválida!! " ANSI_COLOR_RESET << std::endl;
        }
    }
    return 0;
}