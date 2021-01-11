
 /* Assinatura:
 *      Aluno: <Alessandro Euzébio e Daniel Corcino de Albuquerque>
 *      DRE: < 118168732 (Alessandro)  118188457 (Daniel)>
 *      versão do GCC utilizada: 9.2.0
 *
 */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdint.h>


/* O operador ^ (ou-exclusivo) testa se todos os bits sao iguais, retornando 0x0 quando isso for satisfeito,
ao atribuirmos y = 0 e comparamos esse valor com nossa entrada a partir da operacao -> !(x^y) teremos um retorno
igual a 0 para números de entrada diferentes de 0 e 1 para valores de entrada iguais a 0(o operador lógico de negação "!" é usado para essa validaçao).
Como queremos o retorno sendo o contrário, ou seja,  0 para números iguais a 0 e 1 para números diferentes de 0, usamos o operador "!" mais uma vez. */
int32_t naoEhZero(int32_t x){
    return !(!(x ^ 0x0));
}

/* O operador & irá realizar um and bit a bit. Dessa forma, ao realizarmos a operacao -> x & 0x1, iremos ter que os bits resultantes serão necessariamente todos 0, com
excecao do bit menos significativo. Caso o numero analisado seja par, seu bit menos significativo sera 0, caso seja impar, este bit sera 1 (isso acontece pois
esse é o unico bit que somaria um valor ímpar ao resultado final, logo ele so está presente se o numero for ímpar). Assim, se o numero for impar, a operacao
ira retornar 1, e caso seja par, a operacao irá retornar 0. Como queremos que o retorno seja o oposto do descrito anteriormente, adicionamos um "!" e assim, a
operacao fica: !(x & 0x1)*/
int32_t ehPar(int32_t x){
    return !(x & 0x1);
}

/*Ao utilizarmos y na operacao, sendo y igual ao divisor menos 1 e considerando que tal divisor seja uma potencia de 2, estamos fazendo com que os bits mais
significativos do divisor sejam setados para 0, assim, a operacao x & y terá como retorno os bits menos significativos, sendo estes exatamente o resultado
 da operacao resto (mod), ou seja, são aqueles que sobrariam ao fazer a divisao por 8.*/
int32_t mod8(int32_t x) {
    int32_t y = 7;
    return (x & y);
}

/*Aqui fizemos um deslocamento logico do numero de entrada em 31 bits à direita, assim temos que o bit de sinal do numero é levado para a posicao do bit menos
significativo, e todos os outros são preenchidos com 0. Após isso, realizamos um & lógico com o número binário 0000....0001. Dessa forma, se o bit de sinal
era 1 (numero negativo) temos 1 & 1 = 1, e se o bit de sinal era 0 (numero positivo) temos 0 & 1 = 0. Como o programa deseja o contrario, ou seja, saida 1 para
o numero positivo e 0 para o negativo, adicionar à expressao, o operador "!"*/
int32_t ehPositivo(int32_t x){
    x = (unsigned int) x;
    return !((x>>31) & 0x1);
}


/* Temos que na representaçao de numeros em complemento a dois, o bit mais significativo é aquele que representa o sinal do número, e os demais bits são setados
de modo que as potencias de 2 somadas componham o valor total do numero. Também sabemos que quando o número é negativo, seu bit de sinal é 1. Assim, ao realizarmos
a operacao ~ estaremos invertendo todos os bits, e o bit de sinal passa a ser 0, representando um numero positivo. Porem, essa simples troca iria gerar um numero
com modulo abaixo do valor original, uma vez que o 'bit de sinal' agora é 0 e não contribui para o valor total do numero. Para compensar esse fato, somamos 1 ao
valor final. Tambem podemos compreender essa soma pelo seguinte fato, a operacao (~) para qualquer valor inteiro em C corresponde a: -x -1. Logo ao somarmos 1
teremos -x -1 + 1 = -x*/
int32_t negativo(int32_t x){
    return (~x + 1);
}

/*Utilizando a tabela verdade chegamos ao resultado:

~(~x | ~y)

Ou seja, ao negar o x e o y e utilizar o operador | entre eles e negar esse valor obtemos o mesmo que fazer x & y */
int32_t bitwiseAnd(int32_t x, int32_t y) {
    return ~(~x | ~y);
}


/* A operacao x^y compara os numeros bit a bit verificando se estes soa iguais, caso sejam, 0x0 é retornado. Como queremos retornar 1 caso eles sejam iguais,
fazemos entao !(x^y)*/
int32_t ehIgual(int32_t x, int32_t y){
    return !(x ^ y);
}


/* Ao realizar um deslocamento de k bits a esquerda: x << k, temos o equivalente a uma multiplicacao de x por 2^k. Porem, como nesse caso queremos realizar
uma multiplicacao por um numero que nao é uma potencia de dois, precisamos ajustar o resutado. Assim, ao fazermos 2^3 iremos multiplicar o numero por 8,
e como queremos que essa multiplicacao seja por 7, no final, subtraimos do resultado o proprio numero (tiramos uma "parcela" das 8 "parcelas" que foram
somadas ao numero)*/
int32_t mult7(int32_t x){
    return ((x << 3) - x);
}


/*Vamos usar o 1 para nossa funcao de comparacao bit a bit por ele ter seu ultimo bit como 1 e o restante como 0. Assim, fazemos seu deslocamento
 * até a posicao a posicao p pra em seguida compararmos bit a bit. Logo, o & irá comparar bit a bit, retornando 1 apenas quando eles forem iguais.
 * Apos a comparacao é feito um shift a direita para termos um retorno ao bit menos significativo. */
int32_t bitEmP(int32_t x, uint8_t p) {
    return !(!((x&(1<<p))>>p));
}


/* Para obtermos apenas o byte desejado, vamos usar a máscar 0x000000FF, que equivale a uma sequencia binaria apenas com 1's, ou seja: 11111111.
 * Ao deslocarmos a direita o numero x por uma "quantidade" de vezes igual a  p << 3 (sendo equivalente a p * 8) obteremos como resultado apenas
 * os bits na posicao desajada (no caso o byte desejado). Temos a obtencao de tal byte, pois um algarismo no sistema hexadecimal corresponde
 * a 8 bits, e ao deslocarmos x por (p << 3) estamos "andando" os bytes necessarios. Por ultimo, ao realizarmos o & com a máscara 11111111, teremos
 * como retorno exatamente o byte desejado.*/
int32_t byteEmP(int32_t x, uint8_t p){
     return (x >> (p << 3)) & 0xFF;
}

/* Sabemos que a representacao binaria do numero em hexa: 0x7FFFFFFF é igual a 01111111111111111111111111111111, logo, se somamos com este
 * numero em hexadecimal o unico numero no qual o bit mais significativo nao passara a ser 1 é o 0. No caso de numero negativos vamos ter
 * o bit de sinal passando de 1 a 0 apos a realizacao da soma. Utilizamos a operacao | foi usado para que nos numeros negativos tenhamos
 * o bit mais significativo sendo 1 novamente. Por ultimo realizamos um descolando com o shift de 31 bits e o valor passa entao a ser -1
 * se o bit mais signficativo era 1 ou se ja fosse 0. Como estamos a uma unidade, em modulo, da resposta final, somamos 1 no fim.*/
 int32_t negacaoLogica(int32_t x) {
     return 1+(((x+0x7FFFFFFF) | x ) >> 31);
 }

void teste(int32_t saida, int32_t esperado) {
    static uint8_t test_number = 0;
    test_number++;
    if(saida == esperado)
        printf(ANSI_COLOR_GREEN "PASSOU! Saída: %-10d\t Esperado: %-10d\n" ANSI_COLOR_RESET,
               saida, esperado);

    else
        printf(ANSI_COLOR_RED "%d: FALHOU! Saída: %-10d\t Esperado: %-10d\n" ANSI_COLOR_RESET,
               test_number, saida, esperado);
}

int main() {
    puts(ANSI_COLOR_BLUE "Primeiro lab - bits" ANSI_COLOR_RESET);
    puts("");

    puts("Teste: ehZero");
    teste(naoEhZero(0), 0);
    teste(naoEhZero(1), 1);
    teste(naoEhZero(1024), 1);
    teste(naoEhZero(-1), 1);
    teste(naoEhZero(-2), 1);
    teste(naoEhZero(-2147483648), 1);
    teste(naoEhZero(2147483647), 1);
    puts("");

    puts("Teste: ehPar");
    teste(ehPar(2), 1);
    teste(ehPar(1), 0);
    teste(ehPar(3), 0);
    teste(ehPar(13), 0);
    teste(ehPar(100), 1);
    teste(ehPar(125), 0);
    teste(ehPar(1024), 1);
    teste(ehPar(2019), 0);
    teste(ehPar(2020), 1);
    teste(ehPar(-1), 0);
    teste(ehPar(-27), 0);
    teste(ehPar(-1073741825), 0);
    teste(ehPar(1073741824), 1);
    teste(ehPar(2147483647), 0);
    teste(ehPar(-2147483648), 1);
    teste(ehPar(0), 1);
    puts("");

    puts("Teste: mod8");
    teste(mod8(0), 0);
    teste(mod8(4), 4);
    teste(mod8(7), 7);
    teste(mod8(8), 0);
    teste(mod8(-1), 7);
    teste(mod8(-8), 0);
    teste(mod8(2147483647), 7);
    teste(mod8(-2147483648), 0);
    puts("");

    puts("Teste: ehPositivo");
    teste(ehPositivo(-1), 0);
    teste(ehPositivo(1), 1);
    teste(ehPositivo(2037), 1);
    teste(ehPositivo(-2037), 0);
    teste(ehPositivo(-2147483648), 0);
    teste(ehPositivo(-2147483648/2), 0);
    teste(ehPositivo(2147483647), 1);
    puts("");

    puts("Teste: negativo");
    teste(negativo(0), 0);
    teste(negativo(1), -1);
    teste(negativo(-1), 1);
    teste(negativo(2147483647), -2147483647);
    teste(negativo(-2147483647), 2147483647);
    teste(negativo(-2147483648), 2147483648);
    puts("");

    puts("Teste: bitwiseAnd");
    teste(bitwiseAnd(1, 3), 1);
    teste(bitwiseAnd(-1, 0), 0);
    teste(bitwiseAnd(-1, 0x7FFFFFFF), 0x7FFFFFFF);
    teste(bitwiseAnd(0b0100, 0b1100), 0b0100);
    puts("");

    puts("Teste: ehIgual");
    teste(ehIgual(1,1), 1);
    teste(ehIgual(1,0), 0);
    teste(ehIgual(0,1), 0);
    teste(ehIgual(-1,1), 0);
    teste(ehIgual(-1,-1), 1);
    teste(ehIgual(2147483647,-1), 0);
    teste(ehIgual(2147483647,-2147483647), 0);
    teste(ehIgual(2147483647,-2147483648), 0);
    teste(ehIgual(2147483647,-2147483648), 0);
    puts("");

    puts("Teste: mult7");
    teste(mult7(1), 7);
    teste(mult7(7), 49);
    teste(mult7(3), 21);
    teste(mult7(-1), -7);
    teste(mult7(-306783378), -2147483646);
    teste(mult7(306783378), 2147483646);
    puts("");

    puts("Teste: bitEmP");
    teste(bitEmP(1, 0), 1);   //    b01 => retorna 1
    teste(bitEmP(1, 1), 0);   //    b01 => retorna 0
    teste(bitEmP(2, 0), 0);   //    b10 => retorna 0
    teste(bitEmP(2, 1), 1);   //    b10 => retorna 1
    teste(bitEmP(9, 2), 0);   //  b1001 => retorna 0
    teste(bitEmP(-4194305, 22), 0);
    teste(bitEmP(9, 3), 1);
    teste(bitEmP(16, 3), 0);
    teste(bitEmP(0x1 << 5, 4), 0);
    teste(bitEmP(0x1 << 31, 31), 1);
    teste(bitEmP(-1073741825, 30), 0);
    teste(bitEmP(-1073741825, 31), 1);
    puts("");

    puts("Teste: byteEmP");
    teste(byteEmP(0x766B, 1), 0x76);
    teste(byteEmP(0x766B, 0), 0x6B);
    teste(byteEmP(0x8420, 0), 0x20);
    teste(byteEmP(0x12345678, 3), 0x12);   // retorna 0x12
    teste(byteEmP(0x12345678, 2), 0x34);   // retorna 0x34
    teste(byteEmP(0x12345678, 1), 0x56);   // retorna 0x56
    teste(byteEmP(0x12345678, 0), 0x78);   // retorna 0x78
    teste(byteEmP(0x321, 1), 0x03);        // retorna 0x03
    teste(byteEmP(0x321, 0), 0x21);        // retorna 0x21
    puts("");

    puts("Teste: negacaoLogica");
    teste(negacaoLogica(0), 1);
    teste(negacaoLogica(1), 0);
    teste(negacaoLogica(-1), 0);
    teste(negacaoLogica(64), 0);
    teste(negacaoLogica(-64), 0);
    teste(negacaoLogica(2147483647), 0);
    teste(negacaoLogica(-2147483648), 0);
    puts("");
}
