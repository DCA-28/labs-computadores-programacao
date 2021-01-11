# Laboratório sobre manipulação de operações bitwise

Programa com a finalidade de executarmos operações rotineiras na programação, porém, com o viés de atuarmos em um nível mais baixo, trabalhando exclusivamente com operadores bitwise. Dessa forma, conseguimos obter um código mais otimizado, uma vez que as operações executadas de tal maneira podem acarretar num ganho de performance considerável.

Por exemplo, temos que o cálculo de determinado número % 8, quando realizado da maneira tradicional, tem um desempenho em média 62% mais baixo quando comparado a seguinte implementação:

# Markdown

```
int32_t mod8(int32_t x) {
    int32_t y = 7;
    return (x & y);
}
´´´
A explicação da lógica para a construção dessa função, assim como para as demais funções do laboratório que visam otimizações, está presente na forma de comentários elucidativos no código.
