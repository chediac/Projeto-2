// Leonardo Magalhães - 32318359
// Matheus Chediac Rodrigues - 32325746

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//------------VERIFICACOES-----------------
int verificar(int lin, int col, int M[lin][col], int cont){

  int guarda=0;
  if(lin == 1 && col == 1 && M[lin][col] == 1){return 1;}
  else if(cont==col){return 0;}

  int i;
  for(i=0; i<lin; i++){
    guarda += M[i][cont];

  }

  return verificar(lin, col, M, cont+1) + guarda;
}

// verificar se a matriz selecionada é toda Preta
bool verificar_preto(int num, int lin, int col){
  if(num == lin*col){return true;}
  else{return false;}
}
// verificar se a matriz selecionada é toda Branca
bool verificar_branco(int num){
  if(num==0){return true;}
  else{return false;}
}


// Função que dividirá a imagem em 4 partes
void cortar_em_4(int lin, int col, int V[lin][col]){

  int guarda_1 = 0;
  int guarda_2 = 0;
  int guarda_3 = 0;
  int guarda_4 = 0;

  int metade_lin = lin/2;
  int lin_menor = metade_lin;
  int lin_maior = lin - lin_menor;

  int metade_col = col/2;
  int col_menor = metade_col;
  int col_maior = col - col_menor;

  int i,j;

  //1º quadrante original
  int matriz_1[lin_maior][col_maior];

  for(i = 0; i<lin_maior;i++){
    for(j=0; j<col_maior;j++){
      matriz_1[i][j] = V[i][j];
      guarda_1 += V[i][j];
    }
  }
  int verificacao_1 = verificar(lin_maior, col_maior, matriz_1, 0);
  // passando a verificação nesse quadrante em específico para saber se é preta, branca ou se deve cortá-la novamente
  if (verificar_preto(verificacao_1, lin_maior, col_maior) == true){
    printf("P");
  }
  else if(verificar_branco(verificacao_1) == true){
    printf("B");
  }
  else{
    printf("X");
    cortar_em_4(lin_maior, col_maior, matriz_1);
    // se não for preta ou branca, chama a função novamente para cortar novamente em quadrantes menores
  }


  //2º quadrante original
  int matriz_2[lin_maior][col_menor];

  for(i = 0; i<lin_maior; i++){
    for(j=col_maior; j<col; j++){
      matriz_2[i][j-col_maior] = V[i][j];
      guarda_2 += V[i][j];
    }
  }

  int verificacao_2 = verificar(lin_maior, col_menor, matriz_2, 0);
  //se lin e col forem igual a 0, então o corte é diferente
  if (lin <= 1 || col <= 1) {
    if (V[lin][col] == 1) {
      printf("P");
      } else {
        printf("B");
    }
    return;
  }
    //Verifica se a matriz é composta por apenas 1
  else if (verificar_preto(verificacao_2, lin_maior, col_menor) == true){
    printf("P");
  }
  else if(verificar_branco(verificacao_2) == true){
    printf("B");
  }
  else{
    printf("X");
    cortar_em_4(lin_maior, col_menor, matriz_2);
  }

  //3o quadrante original
  int matriz_3[lin_menor][col_maior];

  for(i = lin_maior; i<lin; i++){
    for(j=0; j<col_maior; j++){
      matriz_3[i-lin_maior][j] = V[i][j];
      guarda_3 += V[i][j];

    }

  } 

  int verificacao_3 = verificar(lin_menor, col_maior, matriz_3, 0);

  if (lin <= 1 || col <= 1) {
    return;
  }
    //Verifica se a matriz é composta por apenas 1
  else if (verificar_preto(verificacao_3, lin_menor, col_maior) == true){
    printf("P");
  }
  else if(verificar_branco(verificacao_3) == true){
    printf("B");
  }
  else{
    printf("X");
    cortar_em_4(lin_menor, col_maior, matriz_3);
  }

  //4º quadrante original
  int matriz_4[lin_menor][col_menor];

  for(i = lin_maior; i<lin; i++){
    for(j=col_maior; j<col; j++){
      matriz_4[i-lin_maior][j-col_maior] = V[i][j];
      guarda_4 += V[i][j];
    }
  }
  int verificacao_4 = verificar(lin_menor, col_menor, matriz_4, 0);

  if (lin <= 1 || col <= 1) {
    return;
  }
    //Verifica se a matriz é composta por apenas 1
  else if (verificar_preto(verificacao_4, lin_menor, col_menor) == true){
    printf("P");
  }
  else if(verificar_branco(verificacao_4) == true){
    printf("B");
  }
  else{
    printf("X");
    cortar_em_4(lin_menor, col_menor, matriz_4);
  }

}
//Cria uma matriz com valores 1 e 0
void cria_matriz_aleatoria(int lin, int col,int V[lin][col]){
  int i, j;
  printf("\n");
  printf("\nMatriz a ser verificada:\n");
  for (int i = 0; i < lin; i++) {
      for (int j = 0; j < col; j++) {
        if(j%2 == 0){
          V[i][j] = 0;
        }
        else{
          V[i][j] = 1;
        }
        printf("%d\t", V[i][j]);
      }
      printf("\n");
  }
}

//Cria a matriz com o tamanho escolhido pelo usuário
void cria_matriz(int lin, int col,int V[lin][col]){
  int i, j;
  printf("\n");
  for(i=0; i<lin; i++){
    for(j=0; j<col; j++){
      printf("Digite o valor de [%d][%d]: ", i, j);
      scanf("%d", &V[i][j]);
    }
  }
  printf("\nMatriz a ser verificada:\n"); //imprime a matriz criada pelo usuário
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", V[i][j]);
        }
        printf("\n");
    }
}

//FUNÇÃO PRINCIPAL
int main(void){

  int linha, coluna, guarda_valor_0_1;
  int contador = 0;
  char valor[15];

  printf("Digite a instrução de criação entre (-m) ou (--manual): ");
  scanf("%s",valor);
  if(strcmp(valor, "-m") == 0){//escolhe a opção "-m" para fazer a leitura de uma imagem
    printf("Digite a linha: ");
    scanf("%d", &linha);

    printf("Digite a coluna: ");
    scanf("%d", &coluna);

    int matriz[linha][coluna];
    cria_matriz_aleatoria(linha, coluna, matriz);
    printf("\n");
    guarda_valor_0_1 = verificar(linha, coluna, matriz, contador);
    //Verifica se a matriz é composta por apenas 1
    if (verificar_preto(guarda_valor_0_1, linha, coluna) == true){
      printf("P");
    }
    //Verifica se a matriz é composta por apenas 0
    else if(verificar_branco(guarda_valor_0_1) == true){
      printf("B");
    }
    else{
      printf("X");
      cortar_em_4(linha, coluna, matriz);
    }
  }
  else if(strcmp(valor, "--manual") == 0){//opção de digitar a mão a imagem inteira
    printf("Digite a linha: ");
    scanf("%d", &linha);

    printf("Digite a coluna: ");
    scanf("%d", &coluna);

    int matriz[linha][coluna];
    cria_matriz(linha, coluna, matriz);
    printf("\n");
    guarda_valor_0_1 = verificar(linha, coluna, matriz, contador);

    //Verifica se a matriz é composta por apenas 1
    if (verificar_preto(guarda_valor_0_1, linha, coluna) == true){
      printf("P");
    }
    //Verifica se a matriz é composta por apenas 0
    else if(verificar_branco(guarda_valor_0_1) == true){
      printf("B");
    }
    else{
      printf("X");
      cortar_em_4(linha, coluna, matriz);
    }

  }

}