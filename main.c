#include <stdio.h>
#include <string.h>


#define ARQUIVO_MATRICULA "matricula.txt"
#define ARQUIVO_CADASTRO "cadastro.bin"
#define CODIGO_PROFESSOR 1202

int matricula;

struct cadastro{
  int mat;
  char Nome[11];
  char Curso[16];
  float notas[4];
};





int menu (char *opcao, int *,int);
int verificador_chave(int );
int verificadormatricula(int *matricula);
void registrar (struct cadastro *Cadastro);
void escreve_arquivo(struct cadastro *Cadastro);
void ler_arquivo(struct cadastro *Cadastro,int,int,char*);
void imprimestr(const struct cadastro *Cadastro );
void mediadocurso(struct cadastro *Cadastro,int);
void desempenho(struct cadastro *Cadastro,int);
void atualizacadastro(struct cadastro *Altcadastro,int);
void atualizanota (struct cadastro *Altnotas );
void deletacadastro(struct cadastro*Delcadastro);

FILE *arqBin = NULL;//ver se isso vai da probelam ou melhor usar um emcada função
FILE *arqTxt = NULL;//guardar o número de matrículas criadas

int main(void) {
  char opcao;
  int a,sentinela = 1;

  printf("%10s\n","BEM VINDO AO SISTEMA INTEGRADO DE GESTÃO ACADEMICA");
  printf("---------------------------------------------------------\n");
  printf("\nAntes de começar, insira sua matrícula (se for docente, insira a sua senha padrão):");
    scanf(" %i",&matricula);
    a = verificador_chave(matricula);
    if(a==0 || a==2){ printf("\nBem-vindo discente!\n");}
    if (a==2){printf("\nEssa matrícula ainda não foi cadastrada, fale com a coordenação do seu curso.\n");}

  while (sentinela == 1){
    printf("\n---------------------------------------------------------\n");
    if (a ==1){
      printf("\nPor favor, escolha uma das opções abaixo:\n\n + Cadastrar aluno: A\n + Atualizar informação do(a) estudante: B\n + Deletar cadastro: C\n + Verificar Notas: D\n + Alterar notas: E\n + Listar dados: F\n + Desempenho estudantil:G \n + Encerrar o programa: H\n\nInsira a opção: ");
    }else{
      printf("\nPor favor, escolha uma das opções abaixo:\n\n + Cadastrar aluno*: A\n + Atualizar informação do(a) estudante*: B\n + Deletar cadastro*: C\n + Verificar Notas: D\n + Alterar Notas*: E\n + Listar dados**: F\n + Desempenho estudantil**:G \n + Encerrar o programa: H\n\n * Acesso indisponível para discentes\n** Acesso apenas algumas funcionalidades\n\nInsira a opção: ");
    }
    
   
    scanf(" %s",&opcao);
    menu(&opcao,&sentinela,a);
  }
  printf("\nObrigado pela preferência!");
  return 0;
}

int verificador_chave(int chave){
  int n, contador = 0;
  if (chave == CODIGO_PROFESSOR){
    printf("\n Bem vindo professor(a)!\n");
    return 1;
  }
  else if (chave >0 && chave <100){
   
    arqTxt =  fopen(ARQUIVO_MATRICULA,"r");
    while(1){
      fscanf(arqTxt," %i",&n);
      if (n == chave){
        contador +=1;
      }
      if (feof(arqTxt)) break;
    }
    if (contador ==0){return 2;}//não foi registrada a matrícula
    return 0;
    contador *= 0;
  }
  else{
    printf("\nEsse número é inválido. Por favor insira um valor existente:");
    int k;
    scanf(" %i", &k);
    return verificador_chave(k);
  }
}


int menu (char *opcao,int*sentinela,int a){
  struct cadastro Cadastro,Altnotas,Delcadastro,Altcadastro;
  int mat,opDados,verificador;
  char curso[16];
  switch (*opcao){
    case 'A':
    case 'a':
    printf("\n---------------------------------------------------------\n");
      if (a==1){
        registrar (&Cadastro);
        escreve_arquivo(&Cadastro);
        
      }else{
        printf("\nDesculpe, mas está opção só é válida para Docentes\nRetornando ao MENU");
      }
      break;
    case 'B':
    case 'b':
    printf("\n---------------------------------------------------------\n");
      if (a==1){
        printf("\nPor favor, insira a matrícula do aluno(a):");
        scanf(" %i",&verificador);
      if (verificador_chave(verificador)== 2){
      printf("Matrícula não encontrada. Voltando ao menu.");}else{atualizacadastro(&Altcadastro,verificador);}
        
      }else{
        printf("\nDesculpe, mas está opção só é válida para Docentes\nRetornando ao MENU");
      }
      break;
    case 'C':
    case 'c':
    printf("\n---------------------------------------------------------\n");
       if (a==1){
        deletacadastro(&Delcadastro);
      }else{
        printf("\nDesculpe, mas está opção só é válida para Docentes\nRetornando ao MENU");
      }
      break;
    case 'D':
    case 'd':
      printf("\n---------------------------------------------------------\n");
      if (a==1){
        printf("\nInsira a matrícula do aluno:");
        scanf("%i",&mat);
        while(verificador_chave(mat) == 2){
          printf("\nMATRÍCULA NÃO FOI ENCONTRADA");
          printf("\nInsira a matrícula do aluno:");
          scanf(" %i",&mat);
        }
        ler_arquivo(&Cadastro,1, mat,curso);
      }
      else{
        if(a==2){
        printf("\nMATRÍCULA NÃO FOI ENCONTRADA");
      }
        printf("\n Essas são suas notas:");
        ler_arquivo(&Cadastro,1, matricula,curso);
      }
      break;
    case 'E':
    case 'e':
    printf("\n---------------------------------------------------------\n");
      if (a==1){
        atualizanota(&Altnotas);
      }else{
        printf("\nDesculpe, mas está opção só é válida para Docentes\nRetornando ao MENU");
      }
      break;
    case 'F':
    case 'f':
    printf("\n---------------------------------------------------------\n");
      if (a==1){
        printf("\n%20s\n\n +Todas as notas do sistema: 0\n +Por matrícula: 1\n +Por curso:2\n Insira a opção:","MENU DE DADOS");
        scanf("%i",&opDados);
        while (opDados >2 || opDados <0){printf("\nERRO\nInsira uma opção válida:");scanf(" %i",&opDados);}//verifica se está no intervalo

        if (opDados==1){
        printf("\nInsira a matrícula do aluno:");
          scanf("%i",&mat);
          while(verificador_chave(mat) == 2){
            printf("\nMATRÍCULA NÃO FOI ENCONTRADA");
            printf("\nInsira a matrícula do aluno:");
            scanf(" %i",&mat);
          }
          ler_arquivo(&Cadastro,opDados, mat,curso);
        }else if(opDados == 0){ler_arquivo(&Cadastro,opDados, mat,curso);}
        else if (opDados == 2){
          printf("Insira o nome do curso:");
          scanf(" %[^\n]",curso);
          ler_arquivo(&Cadastro,opDados, mat,curso);
        }
      
      }else{
        printf("\n%10s\n Seus dados:1\n Média do curso: 2\nOpção:","MENU");
        scanf(" %i",&opDados);
        if(opDados == 1){
          if(a==2){
          printf("\nMATRÍCULA NÃO FOI ENCONTRADA");
          } 
          printf("\n Essas são suas notas:");
          ler_arquivo(&Cadastro,1, matricula,curso);
        }else if(opDados == 2){
          mediadocurso(&Cadastro,matricula);
        }else{
          printf(" Opção indisponível, voltando ao meu");
        }
      }
  
      break;
    case 'G':
    case 'g':
    printf("\n---------------------------------------------------------\n");
     if (a==1){
        desempenho(&Cadastro,a);
      }else{
        printf("\n Você NÃO poderá visulaizar o nome dos alunos, apenas a quantidade para cada faixa de desempenho\n");
        desempenho(&Cadastro,a);
      }
      
      break;
    case 'H':
    case 'h':
    printf("\n---------------------------------------------------------\n");
      *sentinela = 0;
      printf("%35s","FIM DO PROGRAMA"); 
      printf("\n---------------------------------------------------------\n");
      break;
    default:
      printf("\nOPÇÃO INEXISTENTE!\nPor favor insira uma opção válida:");
      scanf(" %s",opcao);
      return menu(opcao,sentinela,a);
  }
  return 0; 
}


void registrar (struct cadastro *Cadastro){
  char nome[20];
  char curso [20];
  float n1,n2,n3,media;
  int mat,i,j,k;
  printf("\n%10s","Bem vindo ao cadastro de alunos");
  printf("\nPor favor insira as seguintes informações: ");
  printf("\n-Número de matrícula:");
  scanf(" %i",&mat);
  verificadormatricula(&mat);

  printf("-Nome (max 10 caract.):");
  scanf(" %[^\n]%n",nome,&i);
  while (i>11){
    printf("\nNome ultrapassa os 10 caracteres, tente novamente (abrevie, se necessário):");
    scanf(" %[^\n]%n",nome,&i);
  }

  printf("-Curso (máx 15 caract):");
  scanf(" %[^\n]%n",curso,&j);
  while (j>16){
    printf("\nO nome do curso ultrapassa os 15 caracteres, tente novamente ( abrevie, se necessário):");
    scanf(" %[^\n]%n",curso,&j);
  }

  printf("\n-Insira as notas de cada unidade:\nUnid.1:");
  scanf("%f",&n1);
  while (n1>10 || n1<0){
    printf("\nA nota deve estar no intervalo de 0 a 10. Por favor insira o valor coreto p/unidade 1:");
    scanf(" %f",&n1);
  }
  printf("Unid.2:");
  scanf(" %f",&n2);
  while (n2>10 || n2<0){
    printf("\nA nota deve estar no intervalo de 0 a 10. Por favor insira o valor coreto p/unidade 2:");
    scanf(" %f",&n2);
  }
  printf("Unid.3:");
  scanf(" %f",&n3);
  while (n3>10 || n3<0){
    printf("\nA nota deve estar no intervalo de 0 a 10. Por favor insira o valor coreto p/unidade 3:");
    scanf(" %f",&n3);
  }
  media = (n1+n2+n3)/3;
  
  //passando valores para struct
  (*Cadastro).mat = mat;
 for (k = 0;k <i;k++){
   (*Cadastro).Nome [k]= nome[k]; 
 } 
  for (k = 0;k <j;k++){
   (*Cadastro).Curso [k]= curso[k]; 
 } 
  Cadastro->notas[0] = n1;
 (*Cadastro).notas[1] = n2;
 (*Cadastro).notas[2] = n3;
 (*Cadastro).notas[3] = media;
}


void escreve_arquivo(struct cadastro *Cadastro){
  arqBin = fopen(ARQUIVO_CADASTRO,"ab+");
  if (!arqBin ){printf("ERRO");}
  fwrite(Cadastro,1,sizeof(struct cadastro),arqBin);
  fclose(arqBin);
}

void ler_arquivo(struct cadastro *Cadastro, int marcador, int mat,char *curso){
  int a,contador = 0,contador1=0;
  FILE *arqBinleitura = fopen(ARQUIVO_CADASTRO,"rb");
  if (!arqBinleitura){printf("ERRO LEITURA");}

  if (marcador == 0){
    while(1){
      fread(Cadastro,1,sizeof(struct cadastro),arqBinleitura);
      if (feof(arqBinleitura)) break;
      printf("\n**********************************************************\n");
      imprimestr(Cadastro);
    }
  }else if (marcador ==1){
    while(1){
      fread(Cadastro,1,sizeof(struct cadastro),arqBinleitura);
      if (Cadastro->mat == mat) break;
    }
    printf("\n**********************************************************\n");
    imprimestr(Cadastro);
  }else {
    while(1){
      fread(Cadastro,1,sizeof(struct cadastro),arqBinleitura);
      for (a=0;a<strlen(curso);a++){
        if(Cadastro->Curso[a] ==curso[a]) {
          contador +=1;
        }
      }
      if (feof(arqBinleitura)) break;
      if (contador == strlen(curso)){
        printf("\n**********************************************************\n");contador1+=1;
        imprimestr(Cadastro);}
      contador*=0;
      
    }
    if (contador1<=0){printf("\n Não foi encontrado o curso digitado\n");}
    contador1*=0;
  }
  rewind(arqBinleitura);
  fclose(arqBinleitura);
}

void imprimestr(const struct cadastro *Cadastro ){
  printf("%-15s%-15s%s\n%-15.2i%-15s%s\n\n%20s\n%-10s%-10s%-10s%s\n%-10.2f%-10.2f%-10.2f%.2f","Matricula","Nome","Curso",(*Cadastro).mat,(*Cadastro).Nome,Cadastro->Curso,"NOTAS","Unid.1","Unid.2","Unid.3","Média",(*Cadastro).notas[0],(*Cadastro).notas[1],(*Cadastro).notas[2],(*Cadastro).notas[3]);
}

int verificadormatricula(int *matricula){
  int contador,n;
  if (*matricula >0 && *matricula <100){
    if((arqTxt = fopen(ARQUIVO_MATRICULA,"r"))==NULL){
      arqTxt = fopen(ARQUIVO_MATRICULA,"a+");
      fprintf(arqTxt,"%i\n",*matricula);
      rewind(arqTxt);
      fclose(arqTxt);
    
    }else{
      while(1){
        fscanf(arqTxt,"%i",&n);
        if (n == *matricula){
          printf("\nESSA MATRÍCULA JÁ FOI REGISTRADA. Insira um valor diferente:");
          scanf(" %i",matricula);
          return verificadormatricula(matricula);
          break;
        }
        if (feof(arqTxt)) break;
      }
      rewind(arqTxt);
      fclose(arqTxt);
      arqTxt = fopen(ARQUIVO_MATRICULA,"a");
      fprintf(arqTxt,"%i\n",*matricula);
      rewind(arqTxt);
      fclose(arqTxt);
    }
    
    return 0;
  }else{
    printf("\nEsse número é inválido. Por favor insira uma matrícula existente (no intervalo de 1 a 99):");
    scanf(" %i",matricula);
    return verificadormatricula(matricula);
  }
}


void mediadocurso(struct cadastro *Cadastro,int mat){
  float soma = 0;
  int contador = 0,i,comparador = 0,a;
  char receptor [16];
  FILE*ponteirobin = fopen(ARQUIVO_CADASTRO, "rb");
  if(!ponteirobin){printf("\nERRO NO MÉDIA CURSO");}
  while (1){
    fread(Cadastro,1,sizeof(struct cadastro),ponteirobin);
    if (Cadastro->mat == mat){
      for (i = 0;i <strlen(Cadastro->Curso);i++){//pega o curso do aluno
        receptor[i] = Cadastro->Curso[i];
      }
      a = strlen(Cadastro->Curso);
    }
    if (feof(ponteirobin)) break;
  }
  rewind(ponteirobin);
  fclose(ponteirobin);
  ponteirobin = fopen(ARQUIVO_CADASTRO, "rb");
  if(!ponteirobin){printf("\nERRO NO MÉDIA CURSO");}
  while(1){
    fread(Cadastro,1,sizeof(struct cadastro),ponteirobin);
    if (feof(ponteirobin)) break;
    for (i = 0;i <a;i++){//verifica se o curso é o mesmo
      if(receptor[i] == Cadastro->Curso[i]){
        comparador +=1;
      }
    }
    if(comparador == a){//recebe a média do aluno do msm curso
      soma += Cadastro->notas[3];
      contador+=1;
    }
    comparador *=0;
  }
  rewind(ponteirobin);
  fclose(ponteirobin);
  
  printf("-----------------------------\n+ CURSO -> %s\n+ MÉDIA: %.2f\nNº ALUNOS: %i\n",receptor,soma/contador,contador); 
  contador *=0;
  comparador *=0;
}


void desempenho(struct cadastro *Cadastro,int a){
  int contador5mais =0,contadormenor5 = 0,contador0 = 0,cont0 = 0,b; 
  FILE* ponteiro = fopen(ARQUIVO_CADASTRO, "rb");
  if(!ponteiro){printf("\nERRO NO MÉDIA DESEMPENHO");}
  if(a==1){printf("\n  PESSOAS QUE TIRARAM 0:\n%-8s%-12s\n","Mat","Nome");}
  while(1){
    fread(Cadastro,1,sizeof(struct cadastro),ponteiro);
    if(feof(ponteiro)) break;
    for(b=0;b<3;b++){
      if (Cadastro->notas[b]== 0){
        contador0+=1;
      }
    }
    if (a==1 && contador0>0){printf("%-8.2i%-12s\n",Cadastro->mat,Cadastro->Nome);}
    if (contador0>0){cont0 ++;}
    contador0*=0;
  }
  rewind(ponteiro);
  if(a==1){printf("\n  MÉDIAS A PARTIR DE 5:\n%-8s%-12s%s\n","Mat","Nome","Média");}
  while (1){
    fread(Cadastro,1,sizeof(struct cadastro),ponteiro);
    if(feof(ponteiro)) break;
    if(Cadastro->notas[3] >=5){
      contador5mais +=1;
      if(a==1){printf("%-8.2i%-12s%.2f\n",Cadastro->mat,Cadastro->Nome,Cadastro->notas[3]);}
    }
    
  }
  rewind(ponteiro);
  if(a==1){printf("\n  MÉDIAS MENORES DE 5:\n%-8s%-12s%s\n","Mat","Nome","Média");}
  while(1){
    fread(Cadastro,1,sizeof(struct cadastro),ponteiro);
    if(feof(ponteiro)) break;
    if(Cadastro->notas[3] <5){
      contadormenor5 +=1;
       if(a==1){printf("%-8.2i%-12s%.2f\n",Cadastro->mat,Cadastro->Nome,Cadastro->notas[3]);}
      }
  }

  rewind(ponteiro);
  fclose(ponteiro);
 
  printf("\n");
   printf("\n%32s\n================================================\n%-15s|%-11s|  Alunos com nota 0\n%5.2i%11s%4.2i%-7s|%10.2i\n","Resumo das médias","Alunos 5 ou +"," Alunos <5",contador5mais,"|",contadormenor5,"",cont0);
  contador5mais*=0;
  contadormenor5 *=0;
  cont0*=0;
}

void atualizacadastro(struct cadastro *Altcadastro,int verificador){
  int a,b,k;
  char nome [11],curso[16];

  FILE*arqBin1 = fopen(ARQUIVO_CADASTRO,"rb");
  if(!arqBin1){printf("\nERRO1");}
  FILE*tempbin = fopen("temp.bin","wb");
  if(!tempbin){printf("\nERRO2");}
  FILE* arqTxt1 = fopen(ARQUIVO_MATRICULA,"r");
  if(!arqTxt1){printf("\nERRO3");}
  FILE *temptxt = fopen("temp.txt","w");
  if(!temptxt){printf("\nERRO3");}

  
    
  while (1){
    fread(Altcadastro,1,sizeof(struct cadastro),arqBin1);
    if(feof(arqBin1))break;
    if (verificador == (*Altcadastro).mat){
      printf("\n%-15s%-15s%s\n%-15.2i%-15s%s\n\n","Matrícula","Nome","Curso",(*Altcadastro).mat,(*Altcadastro).Nome,(*Altcadastro).Curso);
     
    }
  }
  rewind(arqBin1);
  printf("  Alterar\n+Matrícula:0\n+Nome:1\n+Curso:2\n Insira a opção: ");
  scanf(" %i",&a);
  while (a<0 || a>2){
    printf("\nDigite corretamente:");
    scanf("%i",&a);
  }
  switch (a){
    case 0:
      printf("\nInsira a nova matrícula:");
      scanf("%i",&b);
      if (verificador_chave(b)!=2){printf("Desculpa,essa matríula já existe. Voltando ao MENU");break;} 
      //mudando no binário
      while (1){
        fread(Altcadastro,1,sizeof(struct cadastro),arqBin1);
        if(feof(arqBin1))break;
        if (verificador == (*Altcadastro).mat){
          (*Altcadastro).mat = b;
          fwrite(Altcadastro,1,sizeof(struct cadastro),tempbin);
          continue;
        }
        fwrite(Altcadastro,1,sizeof(struct cadastro),tempbin);
      }
      rewind(arqBin1);
      
      //mudando texto
      while(1){
        fscanf(arqTxt1,"%i",&k);
        if(feof(arqTxt1)) break;
        if (k == verificador){
          fprintf(temptxt,"%i\n",b);
          continue;
        }
        fprintf(temptxt,"%i\n",Altcadastro->mat);
      }
      fclose(temptxt);
      fclose(arqTxt1);
      remove(ARQUIVO_MATRICULA);
      rename("temp.txt",ARQUIVO_MATRICULA);
      break;

    case 1:
      printf("\nEscreva o novo nome (max. 10 caract):");
      scanf(" %[^\n]",nome);
      while (1){
        fread(Altcadastro,1,sizeof(struct cadastro),arqBin1);
        if(feof(arqBin1))break;
        if (verificador == (*Altcadastro).mat){
          strcpy(Altcadastro->Nome,nome);
          fwrite(Altcadastro,1,sizeof(struct cadastro),tempbin);
          continue;
        }
        fwrite(Altcadastro,1,sizeof(struct cadastro),tempbin);
      }
      rewind(arqBin1);
      break;
    case 2:
      printf("\nEscreva o novo curso(max. 15 caract):");
      scanf(" %[^\n]",curso);
      while (1){
        fread(Altcadastro,1,sizeof(struct cadastro),arqBin1);
        if(feof(arqBin1))break;
        if (verificador == (*Altcadastro).mat){
          strcpy(Altcadastro->Curso,curso);
          fwrite(Altcadastro,1,sizeof(struct cadastro),tempbin);
          continue;
        }
        fwrite(Altcadastro,1,sizeof(struct cadastro),tempbin);
      }
      rewind(arqBin1);
      break;
    }
  fclose(arqBin);
  fclose(tempbin);
  remove(ARQUIVO_CADASTRO);
  rename("temp.bin",ARQUIVO_CADASTRO);
}

  

void atualizanota (struct cadastro *Altnotas ){
  int m,unidade;
  
  arqBin = fopen(ARQUIVO_CADASTRO, "rb");
  if (!arqBin){printf("\nERRO NAS NOTAS");}
  FILE*temp = fopen("temp.bin", "w");
  if (!temp){printf("\nERRO NAS NOTAS");}

  printf("\nInsira a matrícula do aluno:");
  scanf(" %i",&m);
  verificador_chave(m);
  while (1){
    fread(Altnotas,1, sizeof(struct cadastro),arqBin);
    if (feof(arqBin)) break;
    if (m == Altnotas->mat){
      printf("\n\n%20s\n%-10s%-10s%-10s%s\n%-10.2f%-10.2f%-10.2f%.2f\n","NOTAS","Unid.1","Unid.2","Unid.3","Média",(*Altnotas).notas[0],(*Altnotas).notas[1],(*Altnotas).notas[2],(*Altnotas).notas[3]);
      printf("\n+Qual unidade deseja alterar?");
      scanf(" %i",&unidade);
      while (unidade <1 && unidade>3){
        printf("\nEscolha uma unid. existente:");
        scanf (" %i",&unidade);
      }
      switch (unidade){
        case 1:
          printf("\n Digite a nova nota da Unid1:");
          scanf(" %f", &(*Altnotas).notas[0]);
          break;
        case 2:
          printf(" Digite a nova nota da Unid2:");
          scanf(" %f", &(*Altnotas).notas[1]);
          break;
        case 3:
          printf(" Digite a nova nota da Unid3:");
          scanf(" %f", &(*Altnotas).notas[1]);
          break;
      }
      (*Altnotas).notas[3] = ((*Altnotas).notas[0] +(*Altnotas).notas[1]+(*Altnotas).notas[2])/3;
      fwrite(Altnotas, 1, sizeof(struct cadastro),temp);
      continue;
    }
    fwrite(Altnotas, 1, sizeof(struct cadastro),temp);
  }
  fclose(temp);
  fclose(arqBin);
  remove(ARQUIVO_CADASTRO);
  rename("temp.bin",ARQUIVO_CADASTRO);
}


void deletacadastro(struct cadastro* Delcadastro){
  int mk;
  
  
  printf("\n+Insira a matrícula a ser deletada:");
  scanf("%d", &mk);
 
  verificador_chave(mk);
  
 
  arqBin = fopen(ARQUIVO_CADASTRO, "rb");
  if (!arqBin){printf("\nERRO NAS NOTAS");}
  FILE*temp1 = fopen("temp.bin", "w");
  if (!temp1){printf("\nERRO NAS NOTAS");}
  FILE*temptxt = fopen("temptxt.txt", "w");
  if (!temptxt){printf("\nERRO NAS NOTAS");}
  FILE*ARQTXT = fopen(ARQUIVO_MATRICULA, "r");
   if (!ARQTXT){printf("\nERRO NAS MATRICULAS");}

  while (1){
    fscanf(ARQTXT, "%i",&Delcadastro->mat);
    if(feof(ARQTXT)){break;}
    if(mk == Delcadastro->mat){
      printf("Removendo aluno %s\n", Delcadastro->Nome);
      continue;
    }
    fprintf(temptxt,"%i\n",Delcadastro->mat);
  }
  fclose(temptxt);
  fclose(ARQTXT);
  remove(ARQUIVO_MATRICULA);
  rename("temptxt.txt",ARQUIVO_MATRICULA);

  while (1){
    fread(Delcadastro,1, sizeof(struct cadastro),arqBin);
    if(feof(arqBin)){break;}
    if (Delcadastro->mat == mk){
      printf("\n A matrícula %.2i foi deletada",mk);
      continue; 
    }
    fwrite(Delcadastro, 1,sizeof(struct cadastro),temp1);
  }
  
  fclose(temp1);
  fclose(arqBin);
  remove(ARQUIVO_CADASTRO);
  rename("temp.bin",ARQUIVO_CADASTRO);
}