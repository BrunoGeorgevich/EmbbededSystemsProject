#include "configure.h"

/*! \mainpage Página Principal
 *
 * \section intro_sec Descrição
 *
 * Este projeto foi delegado aos estudantes da turma de Sistemas Embarcados, no período de 2017.2, pelo professor da Universidade Federal de Alagoas (UFal) Rodrigo Peixoto. O estudo realizado aqui tem como principal proposta exercitar os conhecimentos aprendidos em sala de aula, referentes aos conceitos e técnicas no que tange o desenvolvimento de e para sistemas embarcados. Desta forma, foi proposto o desenvolvimento de cinco casos de teste, que contemplassem os conceitos aprendidos, anteriormente mencionados, e as funcionalidades presentes na placa utilizada, a MicroBit.
 * Os cinco casos de teste consistiam em:
    - Caso 01: Mostrar o texto "ECOM042.2017.2" no display de forma que ele fique passando no display.
    - Caso 02: Deve utilizar o acelerômetro para movimentar um ponto (apenas um led da matriz) que dependendo da posição da placa ele vai se mover;
    - Caso 03: Deve utilizar a bússola para mostrar onde está o norte magnético. Essa indicação deve ser feita na matriz de leds;
    - Caso 04: Mostrar a temperatura capturada pelo sensor da placa em graus célsius;
    - Caso 05: Deve utilizar o bluetooth para interagir com um aparelho externo (ex. celular ou computador) deve trocar dados nessa interação. Fica a critério do aluno definir como mostrar que a troca de dados ocorre de forma correta. Dica, pode mostrar na matriz de led o valor passado pelo outro computador.
 *
 *  Onde somente quatro se fizeram possíveis de serem implementados.
 *
 * \section install_sec Execução do Projeto
 *
 * Para execução do projeto desenvolvido para este projeto, deve-se baixá-lo do repositório online e instalar algumas depedências:
 * \code{.unparsed}
 * sudo apt-get install putty
 * git clone https://github.com/BrunoGeorgevich/EmbbededSystemsProject
 * \endcode
 *
 * Logo em seguida, deve-se entrar no diretório baixado, através do comando:
 * \code{.unparsed}
 * cd EmbbededSystemsProject
 * \endcode
 *
 * Para que então se possa compilar e gerar o binário referente a MicroBit:
 * \code{.unparsed}
 * cd build
 * cmake ..
 * make -j7
 * \endcode
 *
 * Caso todo o processo de compilação e geração tenha dado certo, agora basta copiar o binário gerado e copiá-lo para a MicroBit:
 * \code{.unparsed}
 * cp zephyr/zephyr.bin [CAMINHO PARA A SUA MICROBIT]
 * \endcode
 *
 * Tendo copiado o binário para a MicroBit a mesma irá reiniciar e desconectar do computador. Logo após ela automaticamente reconectar, execute a linha de comando abaixo para comunicar-se com ela via serial:
 * \code{.unparsed}
 * sudo putty /dev/ttyACM0 -serial -sercfg 115200,8,n,1,N
 * \endcode
 *
 * Para gerar a documentação para o mesmo, deve-se executar as seguites linhas de código:
 * \code{.unparsed}
 * cd ../src/ && doxygen dox_config
 * \endcode
 *
 */

int main() {
    init_sensors();
    configure_buttons();
    init_state_machine();

    while (PROGRAM_RUNS_CORRECTLY) {
        current_state->run();
    }

    return NO_ERRORS;
}
