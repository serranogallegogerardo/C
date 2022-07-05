#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define codtec "MaquinaExpendedora2020"

// Variables globales
int contTemp, intento, i, j, ventas;

struct golosina
{
  int precio;
  char nombre[8];
  int marca;
  int tipo;
  int stock;
};
struct golosina reg_golosina; // reg_golosina : GOLOSINA;
struct golosina m[10][3];

// --- COLORES ---
void reset () {
  printf("\033[0m");
}

void TIPOGRAFIA_AMAR (){
  printf("\033[1;33m");
  printf("\033[4m");
}

void TIPOGRAFIA_CYAN (){
  printf("\033[1m"); // bold();
  printf("\x1b[36m"); // cyan();
  printf("\033[4m"); // subrayar();
}

void TIPOGRAFIA_BASE() {
  printf("\033[1m");
  printf("\033[4m");
}

void TIPOGRAFIA_ROJA (){
  printf("\033[1m"); 
  printf("\033[1;31m");
}

void TIPOGRAFIA_AMARILLO (){
  printf("\033[1m");
  printf("\033[01;33m");
}

void TIPOGRAFIA_VERDE (){
  printf("\033[1m");
  printf("\033[1;32m");
}

// Procedimientos
void cargarGolosinas()
{
  FILE *a_ent;
  char caracter;
  a_ent  = fopen("./entrada.dat","r");
  int i_n, i_j;
  if (a_ent != NULL)
  {
    while (fread(&reg_golosina, sizeof(struct golosina), 1, a_ent) == 1)
    {
     j = reg_golosina.tipo; // columna
     i = reg_golosina.marca; // fila
     m[i][j].stock = reg_golosina.stock;
     m[i][j].precio = reg_golosina.precio;
     // i_n ; j_n
      for(i_n = 0; i_n < 8; i_n++)
      {
        m[i][j].nombre[i_n] = reg_golosina.nombre[i_n]; 
      }
    }
	  fclose(a_ent);
  }
  else
  {
    printf("Debe existir un archivo .dat llamado 'entrada.dat' con los datos solicitados.\n");
    exit(1);
  }
}     

//Error de numero que no está en el menú
void ERROR() {
  TIPOGRAFIA_ROJA();
  printf("ERROR! Opción inexistente \n");
  reset();
}

void MOSTRAR_MENU(){
  TIPOGRAFIA_AMARILLO();
  printf("\n----------------------MENU---------------------- \n");
  TIPOGRAFIA_AMAR();
  printf("\nSeleccione la opción que desee\n");
  reset();
  printf("\033[1m");
  printf("\t1 ------> Pedir golosinas \n");
  printf("\t2 ------> Mostrar golosinas \n");
  printf("\t3 ------> Rellenar golosinas \n");
  printf("\t4 ------> Apagar maquina \n");
  reset();
}
void MOSTRAR_GOLOSINA()
{
  TIPOGRAFIA_CYAN();
  printf("    NOMBRE    |    PRECIO    |    CÓDIGO    \n");
  reset();
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 3; j ++)
    {
      if (m[i][j].stock > 0)
      {
        printf("   %s         $ %d            %d%d    \n", m[i][j].nombre, m[i][j].precio, i+1,j+1); 
      }
    }
  }
}

void RETIRAR_GOLOSINA(int prim, int seg)
{
  if (m[prim][seg].stock > 0)
  {
    printf("Entregando golosina...\n");
    reset();
    m[prim][seg].stock = m[prim][seg].stock - 1;
    ventas = ventas + m[prim][seg].precio;
    TIPOGRAFIA_VERDE();
    printf("¡Listo! \n \n");
    reset();
  }
  else
  {
    TIPOGRAFIA_ROJA();
    printf("Lo lamentamos, nos hemos quedado sin stock de esta golosina");
    reset();
  }
  return;
}
// Recibe: int prim, int seg
void RELLENAR_GOLOSINA (int prim, int seg){  
  int cantRellenar;
  char cantReponerChar[2];
  printf("\tIngrese la cantidad que desea reponer: ");
  fgets(cantReponerChar, 3, stdin);
  if(cantReponerChar[strlen(cantReponerChar)-1]!='\n')
  {
    getchar();
  }
  printf("\n");
  cantRellenar = atoi(cantReponerChar);
  if (m[prim][seg].stock == 5) {
    TIPOGRAFIA_ROJA();
    printf("El stock ha alcanzado su límite, no es posible reponer \n");
    reset();
    return;
  } 
  else 
  {
    if (cantRellenar < 1)
    {
      TIPOGRAFIA_ROJA();
      printf("\n Error el número ingresado no es válido \n");
      reset();
      printf("Ingrese un número mayor \n");
    }
    else 
    {
      if (m[prim][seg].stock + cantRellenar > 5)
      {
        TIPOGRAFIA_ROJA();
        printf("Error, la cantidad ingresada supera el límite \n ");
        reset();
        RELLENAR_GOLOSINA(prim, seg);
        return;
      }
      else 
      {
        m[prim][seg].stock = m[prim][seg].stock + cantRellenar;
        TIPOGRAFIA_VERDE();
        printf("El stock ha sido repuesto exitosamente \n");
        reset();
      }
    }
  }
}

void PEDIR_GOLOSINA (int mostrarMenu)
{
  int primer_dig, segundo_dig;
  char inputChar[3];

  if (mostrarMenu == 0)
  {
    TIPOGRAFIA_CYAN();
    printf("    NOMBRE    |    PRECIO     \n");
    reset();
    for (i = 0; i <10; i++)
    {
      for (j = 0; j < 3; j ++)
      { 
        if (m[i][j].stock > 0)
        {
          printf("   %s          $ %d    \n", m[i][j].nombre, m[i][j].precio); 
        }
      }
    } 
  } 
  printf("\x1b[36m");
  printf("\n Ingrese el número de código de la golosina que desea:\t");
  reset();
  fgets(inputChar, 4, stdin);
  if(inputChar[strlen(inputChar)-1]!='\n')
  {
    getchar();
  } 
  int cod = atoi(inputChar);
  if (cod < 11 || cod > 103)
  {
    ERROR();
    printf("\n");
    if (intento <= 2)
    {
      intento = intento +1;
      PEDIR_GOLOSINA (mostrarMenu);
    }
    else
    {
      printf("\033[1m");
      printf("\n Ha excedido el límite de intentos \n");
      reset();
      intento = 0;
      return;
    }
  } 
  else
  {
    printf("\n");
    primer_dig = round(cod/10);
    segundo_dig = cod%10;
    if (segundo_dig > 3)
    {
      ERROR();
      usleep(1500000);
      PEDIR_GOLOSINA(1);
    }
    else
    {
      RETIRAR_GOLOSINA(primer_dig-1, segundo_dig-1);
    }
  }
}

void STOCK()
{
  char deseoChar[1];
  int posRell, primDig, segDig, deseo;
  char posRellChar[3];

  printf("\nIngrese la posicion de la golosina (XXX) donde x sea un entero: "); 
  if (fgets(posRellChar, 4, stdin))
  {
    if(posRellChar[strlen(posRellChar)-1]!='\n')
    {
      getchar();
    }
    posRell = atoi(posRellChar);
    printf("\n");
    primDig = round(posRell/10);
    segDig = posRell%10;

    if (posRell > 103)
    {
      ERROR();
      if (intento <= 1)
      {
        intento = intento +1;
        STOCK();
      }
      else
      {
        printf("\033[1m");
        printf("\n Ha excedido el límite de intentos \n");
        reset();
        return;
      }
    } 
    else 
    {
      if(m[i][j].stock < 5)
      {
        RELLENAR_GOLOSINA(primDig-1, segDig-1);
        
      }
      else
      {
        TIPOGRAFIA_ROJA();
        printf("El stock ha alcanzado su límite, no es posible reponer \n");
        reset();
        printf("- ¿Desea reponer el stock de alguna otra golosina? 1 = 'Sí' | 0 = 'NO' \n ");
        if (fgets(deseoChar, 2, stdin))
        {
          if(deseoChar[strlen(deseoChar)-1]!='\n')
          {
            getchar();
          }
          deseo= atoi(deseoChar);
          if (deseo == 1)
          { 
            STOCK();
          }
          return;
        }
      }
    }
  }
}

//primDig, segDig
void VERIFICAR_CONTRA()
{
  char contraIngresado[22];
  printf("\nIngrese la contraseña: ");
  fgets(contraIngresado, 23, stdin);

  if(contraIngresado[strlen(contraIngresado)-1]!='\n')
  {
    getchar();
  }

  if ( strcmp(contraIngresado, codtec ) == 0 )
  {
    TIPOGRAFIA_CYAN();
    printf("\nBienvenid@,");
    reset();
    STOCK();
  }
  else
  {
    if (contTemp <= 1)
    {
      TIPOGRAFIA_ROJA();
      printf("Contraseña incorrecta.\n");
      reset();
      contTemp = contTemp +1;
      VERIFICAR_CONTRA();
    }
    else
    {
      printf("\033[1m");
      printf("\n Ha excedido el límite de intentos \n");
      return;
    }
  }
}

void ACTUALIZAR_GOLOSINAS()
{
  FILE *a_sal;
  long int currPos;
  a_sal  = fopen("./entrada.dat","r+b");

  while(fread(&reg_golosina, sizeof(struct golosina), 1, a_sal)==1) 
  {
    j = reg_golosina.tipo; 
    i = reg_golosina.marca; 
    reg_golosina.stock = m[i][j].stock;
    currPos = ftell(a_sal); 
    fseek(a_sal, currPos - sizeof(reg_golosina),SEEK_SET); 
    fwrite(&reg_golosina,sizeof(struct golosina),1,a_sal);
  } 
  fclose(a_sal); 
}
  
int main(void)
{
  // VARIABLES LOCALES DEL MAIN
  int op, SALIR;
  char inputChar[3]; 
  cargarGolosinas();

  intento= 0;
  ventas = 0;
  SALIR = 0;
  while(SALIR != 1)
  {
    MOSTRAR_MENU();
    TIPOGRAFIA_BASE();
    printf("\nElección:\t");
    reset();
    fgets(inputChar, 3, stdin);
    reset();
    if(inputChar[strlen(inputChar)-1]!='\n')
    {
      getchar();
    }

    int op = atoi(inputChar);
    if ( op == 0 )
    {
      ERROR();
    }
    else
    {
      printf("\n");
      switch(op)
      {
        // Pedir golosina
        case 1:
          PEDIR_GOLOSINA(0);
        break;
        //Mostrar golosinas3
        case 2:
          MOSTRAR_GOLOSINA();
        break;
        //Rellenar golosinas
        case 3:
          contTemp = 0;
          VERIFICAR_CONTRA();
        break;
        //Apagar máquina: 
        case 4: 
          printf("Las ventas totales fueron de $ %d\n", ventas);
          printf("\033[1m");
          printf("\n¡Hasta luego! \n");
          SALIR = 1;
        break;

        default:
          ERROR();
          reset();
        break;
      }
    }
  }
  ACTUALIZAR_GOLOSINAS();
  return 0;
} 