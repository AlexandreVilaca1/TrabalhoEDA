#include "Header.h"
#include <stdio.h>
#include <stdbool.h>
/**
 * @brief Função principal que gerencia a execução do programa.
 * @author Alexandre Vilaça 26590
 * @date 25.05.2024
 *
 * @return Retorna 0 se a execução foi concluída com sucesso.
 */
int main() {
    Matrix* matrix;
    
    matrix = readMatrixFromFile("Numbers.txt");
    matrix = changeConstant(matrix, 2, 2, 33);
    matrix = insertNewRow(matrix);
    matrix = insertNewColumn(matrix);
    matrix = removeRow(matrix, 1);
    matrix = removeColumn(matrix, 1);
    displayMatrix(matrix);
    displayTabularListing(matrix);

    return 0;
}
    