
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TAMANHO 150

//Função para encontrar o minimo de uma coluna da matriz caracteristicas.
float min(float caracteristicas[][4], int col) {
  float minimo = caracteristicas[0][col];
    for(int i = 0; i < TAMANHO; i++) {
      if(caracteristicas[i][col] < minimo) {
        minimo = caracteristicas[i][col];
      }
    }
  return minimo;
}

//Função para encontrar o maximo de uma coluna da matriz caracteristicas.
float max(float caracteristicas[][4], int col) {
  float maximo = caracteristicas[0][col];
    for(int i = 0; i < TAMANHO; i++) {
      if(caracteristicas[i][col] > maximo) {
        maximo = caracteristicas[i][col];
      }
    }
  return maximo;
}

//Função para encontrar a media de uma coluna da matriz caracteristicas.
float media(float caracteristicas[][4], int col) {
  float soma = 0;
  for(int i = 0; i < TAMANHO; i++) {
    soma += caracteristicas[i][col];
  }
  float media = soma / TAMANHO;
  return media;
}

//Função para encontrar o desvio padrão de uma coluna da matriz caracteristicas.
float DP(float matriz[][4], int coluna) {
    float media = 0.0, variancia = 0.0;

    for (int l = 0; l < TAMANHO; l++) {
        media += matriz[l][coluna];
    }
    media /= TAMANHO;

    for (int l = 0; l < TAMANHO; l++) {
        variancia += pow(matriz[l][coluna] - media, 2);
    }

    variancia /= 149;

    float desvioPadrao = sqrt(variancia);

    return desvioPadrao;
}

//Fornece o resumo da base de dados.
void picao1(float caracteristicas[][4], char classes[][100]) {
  int setosa = 0;
  int virginica = 0;
  int versicolor = 0;
  
  printf("Resumo base de dados iris: %d\n\n", TAMANHO);
  printf("Comprimento sepala: \n");
  printf("Minimo: %.1f\nMaximo: %.1f\nMedia: %.3f\nDP: %.3f\n\n", min(caracteristicas, 0), max(caracteristicas, 0), media(caracteristicas, 0), DP(caracteristicas, 0));
  printf("Largura sepala: \n");
  printf("Minimo: %.1f\nMaximo: %.1f\nMedia: %.3f\nDP: %.3f\n\n", min(caracteristicas, 1), max(caracteristicas, 1), media(caracteristicas, 1), DP(caracteristicas, 1));
  printf("Comprimento petala:\n");
  printf("Minimo: %.1f\nMaximo: %.1f\nMedia: %.3f\nDP: %.3f\n\n", min(caracteristicas, 2), max(caracteristicas, 2), media(caracteristicas, 2), DP(caracteristicas, 2));
  printf("Largura petala: \n");
  printf("Minimo: %.1f\nMaximo: %.1f\nMedia: %.3f\nDP: %.3f\n\n", min(caracteristicas, 3), max(caracteristicas, 3), media(caracteristicas, 3), DP(caracteristicas, 3));
  printf("Tipos: \n");

  for(int i = 0; i < TAMANHO; i++) {
    if(strncmp(classes[i], "setosa", 4) == 0) {
      setosa++;
    } else if(strncmp(classes[i], "virginica", 4) == 0) {
      virginica++;
    } else {
      versicolor++;
    }
  }

  printf("Setosa: %d ocorrências\nVirginica: %d ocorrências\nVersicolor: %d ocorrências", setosa, virginica, versicolor);
}

//Calcula a distancia entre um ponto e outro.
float Distancia(float ponto1[], float ponto2[]){
  float sum = 0.0;
  for(int i = 0; i < 4; i++){
    sum += pow(ponto1[i] - ponto2[i], 2);
  }
  return sqrt(sum);
}

//identifica o index da linha da matriz onde está a classe mais proxima.
int classe(float caracteristicas[][4], float medi[]){
  float menordist = Distancia(caracteristicas[0], medi);
  int mdist = 0;
  for(int i = 0; i < TAMANHO; i++){
    float dist = Distancia(caracteristicas[i], medi);
    if(dist < menordist){
      menordist = dist;
      mdist = i;
    }
  }
  return mdist;
}

//Retorna a classe similar.
int picao2(float caracteristicas[][4]){
  float medida[4];
  char medidas[4][100] = {
  "Comprimento sepala",
  "Largura sepala",
  "Comprimento petala",
  "Largura petala"
  };
  printf("Digite as 4 medidas em centimetros:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: ", medidas[i]);
        scanf("%f", &medida[i]);
    }
  int similar = classe(caracteristicas, medida);
  return similar;
}

//Dado um número inteiro pelo usuário, verifica os k especimes mais proximos.
void knn(float caracteristicas[][4], char classes[][100]) {
  int setosa = 0, versicolor = 0, virginica = 0, k;
  printf("Quantas amostrar voce quer comparar: ");
  scanf("%d", &k);
  if(k == 150) {
    k--;
  } else if(k % 2 == 0) {
      k++;
  }
  float medida[4];
  char medidas[4][100] = {
  "Comprimento sepala",
  "Largura sepala",
  "Comprimento petala",
  "Largura petala"
  };
  printf("Digite as 4 medidas em centimetros:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: ", medidas[i]);
        scanf("%f", &medida[i]);
    }
  for(int i = 0; i < k; i++) {
    int busca = classe(caracteristicas, medida);
    if(strncmp(classes[busca], "setosa", 4) == 0) {
      setosa++;
    }if(strncmp(classes[busca], "virginica", 4) == 0) {
      virginica++;
    }if (strncmp(classes[busca], "versicolor", 4) == 0){
      versicolor++;
    }
    for(int j = 0; j < 4; j++) {
      caracteristicas[busca][j] = 0.0;
    }
  }
  if(setosa > virginica && setosa > versicolor) {
    printf("Setosa é a especie mais proxima.\n");
  } else if(virginica > setosa && virginica > versicolor) {
    printf("Virginica é a especie mais proxima.\n");
  } else {
    printf("Versicolor é a especie mais proxima\n\n");
  }
}

void copiarMatriz(float origem[][4], float destino[][4]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < 4; j++) {
            destino[i][j] = origem[i][j];
        }
    }
}

int main() {
  //Lê o arquivo iris e declara os arrays e matrizes.
  FILE* arquivo;
  char atributos[5][100];
  float caracteristicas[TAMANHO][4];
  float caracteristicas_2[TAMANHO][4];
  char classes[TAMANHO][100];
  
  arquivo = fopen("iris.csv", "r");
  if(arquivo == NULL) {
    printf("Erro ao abrir arquivo. \n");
    return 1;
  }

  //lê a primeira linha para armazenar os nomes das colunas em "atributos".
  char linha[100];
  fgets(linha, sizeof(linha), arquivo);

  char *token = strtok(linha, ",");
  int i = 0;
  while(token != NULL) {
    strcpy(atributos[i], token);
    token = strtok(NULL, ",");
    i++;
  }

//lê os 4 primeiros itens de cada linha, a partir da sedunda linha, e a armazena os valores em "caracteristicas". Em seguida, lê o último e quinto item e armazena em "classes".
  i = 0;
  while(fgets(linha, sizeof(linha), arquivo) != NULL) {
    token = strtok(linha, ",");
    int j = 0;
    while(token != NULL) {
      if(j < 4) {
        caracteristicas[i][j] = atof(token);
      } else {
        strcpy(classes[i], token);
      }
      token = strtok(NULL, ",");
      j++;
    }
    i++;
  }

    
  //Dada uma escolha de opção pelo usuário, inicia um dos 4 casos abaixo
  while(1) {
    copiarMatriz(caracteristicas, caracteristicas_2);
    int picao;
    printf("Digite uma das opcoes abaixo:  \n\n[1] - Mostrar estatisticas\n[2] – Classificar amostra\n[3] – Sair\n[4] - Busca KNN\n\nopcao: ");
    scanf("%d", &picao);
    switch(picao) {
      //Chama a função picao 1 para retornar um resumo do banco de dados.
        case 1:
            picao1(caracteristicas, classes);
            break;
      //Chama a função picao 2, para buscar a amostra mais proxima, e dado o index, imprimi a classe mais proxima da amostra dada.
        case 2:
            printf("\namostra mais proxima: %s\n", classes[picao2(caracteristicas)]);
            break;
      //Encerra o programa.
        case 3:
            printf("Programa finalizado");
            return 0;
      //Chama a função knn que dada uma amostra e um némero inteiro pelo usário, verifica as k amostras mais proximas.
      case 4:
            knn(caracteristicas_2, classes);
    }
  }
  //fecha o arquivo.
  fclose(arquivo);
  return 0;
}