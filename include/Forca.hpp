#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

/*------- PALHETA DE CORES --------*/
#define ANSI_COLOR_RED      "\x1b[31m" 
#define ANSI_COLOR_GRAY     "\e[0;37m"
#define ANSI_COLOR_RESET   "\x1b[0m" 
#define ANSI_COLOR_GREEN	"\e[0;32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
/*--------------------------------*/
 
class Forca {
    public:
        enum Dificuldade{ 
            FACIL=1, MEDIO, DIFICIL
        };
    private:
        //TODO: armazenar os scores? ---logo abaixo temos os atributos privado da classe 
       
        std::vector< std::pair<std::string, int> > m_palavras; //<! palavras e sua ocorrência no Corpus
        
        std::string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras
 
        Dificuldade m_dificuldade = Dificuldade::FACIL; //<! dificuldade atual do jogo
 
        std::vector< std::string > m_palavras_do_jogo; //<! container “Palavras do Jogo”
        std::vector< char > m_letras_palpitadas; //<! contem as letras palpitadas pelo jogador
        std::string m_palavra_atual; //<! palavra sendo jogada “atualmente”
        std::string m_palavra_jogada; //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
        int m_pontos_partida;  //Pontos da partida
        int m_tentativas_restantes; //TODO: armazenar tentativas restantes

        std::vector<std::string> palavras_acertadas;
    public:
        
        Forca( std::string palavras, std::string scores );

        std::vector<std::pair<bool, std::string>> eh_valido();

        void carregar_arquivos(std::string palavras_arquivo, std::string arquivo_scores); 
 
        void set_dificuldade(Dificuldade d);
 
        std::string proxima_palavra();
 
        /**
         * Retorna a palavra atual que está sendo jogada.
         *  este método __Diferente do método proxima_palavra(),não atualiza__ o atributo
         * m_palavra_atual, apenas retorna o atributo m_palavra_jogada que é a palavra no
         * formato  "_ _ _ _ ... _" contendo todas as letras
         * já acertadas/sorteadas ao invés de “_”.
         * @return a palavra atualmente sendo jogada.
         */
        std::string get_palavra_jogada();

        std::string get_palavra_atual();
 

        std::pair<bool, bool> palpite(std::string palpite);
 
        bool rodada_terminada();
 
        void reset_rodada();
 
        /**
         * Retorna a quantidade de tentativas restantes.
         * @return a quantidade de tentativas restantes.
         */
        int get_tentativas_restantes();

        //FUNÇÕES ADICIONADAS
        int busca(char *S, std::string palavra);

        void SorteioPalavras();

        void interfaceBoneco();

        void mostrarScore();

        void set_palavra_jogada(std::string palavra_jogada);

        void set_tentativas_restantes(int tentativas);

        int get_pontos_partida();

        void set_pontos_partida(int pontos);

        void set_letras_palpitadas(char letra);

        void palavras_acertadas_do_jogador(std::string palavra);

        std::vector<std::string> get_palavras_acertadas();

        void set_m_letras_palpitadas(std::string palpite);

        void proximo_jogador();

        std::string get_m_palavra_jogada();

        void game_over();
        
        void limpabuffer();
};
