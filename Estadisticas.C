//Realizado por Agustin Bravo, Serrano Gallego Gerardo y Nadine Peralta
/* CONSIGNA:
Se posee un archivo de los 26 departamentos del Chaco con datos de población urbana/rural con información obtenida en el censo 2010.

Se registró cada tipo de población (urbana - rural dispersa - rural agrupada) y su cantidad de habitantes que viven en viviendas con hacinamiento crítico (más de 3 personas por cuarto).

DEPARTAMENTOS: 
  nombre: AN(30) 
  pob_urb: entero 
  hacin_urb: entero
  pob_rur_agrup: entero
  hacin_rur_agrup: entero
  pob_rur_disp: entero
  hacin_rur_disp: entero
  pob_total: entero

Generar un algoritmo que muestre por pantalla:
  1. Listar el porcentaje de hacinamiento crítico de población urbana, rural dispersa, rural agrupada y total de cada departamento, y además los totales del Chaco.
  2. Mostrar el departamento con el mayor porcentaje de población total con hacinamiento crítico.
  3. Teniendo en cuenta cada total de población de Chaco, calcular en cual se registra un mayor porcentaje de hacinamiento crítico.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float porc_urbano, porc_ragrupado, porc_rdispersado, tot_urbano, tot_ragrupado, tot_rdispersado, tot_hacin_rdispersado, tot_hacin_ragrupado, tot_hacin_urbano, poblacion_total;
int i;   

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

struct departamento
{
  char nombre[30]; 
  int pob_urb;
  int hacin_urb;
  int pob_rur_agrup;
  int hacin_rur_agrup;
  int pob_rur_disp;
  int hacin_rur_disp;
  int pob_total;
};
struct departamento reg_departamento; //reg_departamento : DEPARTAMENTO;

struct t_porcentaje
{
  char nombre[30]; 
  float urb;
  float rur_agrup;
  float rur_disp;
};
struct t_porcentaje reg_porcentaje; //reg_porcentaje : t_porcentaje;
struct t_porcentaje a[26];
  
int j;

//Procedimientos

void calcular_porcentaje() //Calculo los porcentajes y acumulo totales
{
  porc_urbano = (reg_departamento.hacin_urb * 100)/reg_departamento.pob_urb;
  porc_ragrupado = (reg_departamento.hacin_rur_agrup * 100)/reg_departamento.pob_rur_agrup;
  porc_rdispersado = (reg_departamento.hacin_rur_disp * 100)/reg_departamento.pob_rur_disp;

  //Acumulo los totales de tipo de población en chaco
  tot_urbano = porc_urbano + tot_urbano;
  tot_ragrupado = porc_ragrupado + tot_ragrupado;
  tot_rdispersado = porc_rdispersado + tot_rdispersado;

  //Acumulo los totales de tipo de hacinamiento por población en chaco
  tot_hacin_urbano = reg_departamento.hacin_urb + tot_hacin_urbano;
  tot_hacin_rdispersado = reg_departamento.hacin_rur_disp + tot_hacin_rdispersado;
  tot_hacin_ragrupado = reg_departamento.hacin_rur_agrup + tot_hacin_ragrupado;

  //Acumulo el total de la población en chaco
  poblacion_total = reg_departamento.pob_total + poblacion_total;
}

void guardar_porcentajes() //Carga de Matriz 
{
  FILE *reg_departamento = NULL;
  reg_departamento  = fopen("./departamentos.data","r"); //Abrir el arch de entrada como lectura (ABRIR E/)
  int i;
  if(reg_departamento != NULL ) 
  {
    
      while (!feof(reg_departamento))
    //while (fread((&f, sizeof(struct departamento), 1, reg_departamento) == 1)) //Error del &f
    {
      for(i = 0; i < 26; i++) //Carga del arreglo
      {
        str(reg_departamento->nombre, reg_porcentaje.nombre);
        //reg_porcentaje.nombre = reg_departamento->nombre
        reg_porcentaje.urb = porc_urbano;
        reg_porcentaje.rur_disp = porc_rdispersado;
        reg_porcentaje.rur_agrup = porc_ragrupado;
        a[i] = reg_porcentaje;
      }
    }
    
    fclose(reg_departamento);
  
  }
  
  else
  {
    printf("Debe existir un archivo .dat llamado 'departamentos.dat' con los datos solicitados.\n");
    exit(1);
  }
}

void listar_porcentajes() // Punto 1 
{
  for(i = 0; i < 26; i++)
  {
    printf("DEPARTAMENTO %s \n", a[i].nombre);
    printf("Porcentaje de hacinamiento crítico en la población urbana %f \n", a[i].urb);
    printf("Porcentaje de hacinamiento crítico en la rural agrupada %f \n", a[i].rur_agrup);
    printf("Porcentaje de hacinamiento crítico en la rural dispersada %f \n", a[i].rur_disp);
  }
  printf("Total de hacinamiento crítico en la población urbana en la provincia del Chaco %f \n", tot_hacin_urbano);
  printf("Total de hacinamiento crítico en la población rural agrupada en la provincia del Chaco %f \n", tot_hacin_ragrupado);
  printf("Total de hacinamiento crítico en la población rural dispersada en la provincia del Chaco %f \n", tot_hacin_rdispersado);
}

void departamento_mayor() // Punto 2
{
  printf("");
}

void mayor_hacintamiento() // Punto 3
{
  printf("");
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
  printf("\t1 ------> Lista de porcentajes de cada tipo de población en Chaco \n");
  printf("\t2 ------> Mostrar el departamento con mayor porcentaje de población en hacintamiento crítico \n");
  printf("\t3 ------> Mostrar en qué tipo de población de Chaco se registra un mayor porcentaje de hacintamiento crítico \n");
  printf("\t4 ------> SALIR \n");
  reset();
}


int main() 
{
  int op, SALIR;
  char inputChar[3]; 

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
        // Lista de porcentajes de cada tipo de población en Chaco
        case 1:
          listar_porcentajes();
        break;
        //Mostrar el departamento con mayor porcentaje de población en hacintamiento crítico
        case 2:
          departamento_mayor();
        break;
        //Mostrar en qué tipo de población de Chaco se registra un mayor porcentaje de hacintamiento crítico
        case 3:
          mayor_hacintamiento();
        break;
        //SALIR: 
        case 4: 
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
  return 0;
}
