#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/********************************************************************************
*********************************************************************************
***                                                                           ***
***                           P R O T O T I P O S                             ***
***                                   D E                                     ***
***                            F U N C I O N E S                              ***
***                                                                           ***
*********************************************************************************
********************************************************************************/

void rewind(FILE *fichero); //Función que regresa el archivo al inicio

/********************************************************************************
*********************************************************************************
***                                                                           ***
***                          D E C L A R A C I Ó N                            ***
***                                   D E                                     ***
***                          E S T R U C T U R A S                            ***
***                                                                           ***
*********************************************************************************
********************************************************************************/

struct lista_orig{ //Declaramos la estructura de la cola con la lista de palabras original
	char palabra[30];
	struct lista_orig *sigptr;
};

typedef struct lista_orig LISTA_ORIG;
typedef LISTA_ORIG *LISTA_ORIG_PTR;

struct lista_depurada{
	char palabra[30];
	int total;
	struct lista_depurada *sigptr;
};

typedef struct lista_depurada LISTA_DPRD;
typedef LISTA_DPRD *LISTA_DPRD_PTR;

struct depura_duplicada{
	char palabra[30];
	char palabra_fon[30];
	int cont_palabra;
	int fon_repetido;
	struct depura_duplicada *sigptr;
};

typedef struct depura_duplicada DEPURA_DUP;
typedef DEPURA_DUP *DEPURA_DUP_PTR;

struct depura_de_codigo{
	char palabra[30];
	char palabra_fon[30];
	int cont_palabra;
	int fon_repetido;
	struct depura_de_codigo *sigptr;
};

typedef struct depura_de_codigo DEPURA_COD;
typedef DEPURA_COD *DEPURA_COD_PTR;

/********************************************************************************
*********************************************************************************
***                                                                           ***
***                       F U N C I O N E S      D E                          ***
***                              D E P U R A                                  ***
***                          Y      R E P O R T E                             ***
***                                                                           ***
*********************************************************************************
********************************************************************************/

void lista_a_estructura(FILE **lista, LISTA_ORIG_PTR *iniptr, LISTA_ORIG_PTR *finptr) //Función que guarda la lista en una cola.
{
	LISTA_ORIG_PTR nuevoptr;
	char palabrados[30];
	int i=0,j=1;
	
	while(feof (*lista) == 0 ) //Vamos a contar el total de palabras
        {
        	fgets(palabrados,30,*lista); //Nos recorremos a la siguiente palabra
        	i++; //Contamos la palabra
        }
	//Al haber una palabra en blanco, vamos a considerar hacerlo sin la última palabra (Que no contiene nada en realidad.
	rewind(*lista); //Regresamos la lista al inicio.
	while(j<i) //Mientras no lleguemos a la penúltima palabra del archivo.
        {
        	fgets(palabrados,30,*lista); //Recibimos la palabra de la lista

        	nuevoptr = (LISTA_ORIG_PTR) malloc(sizeof(LISTA_ORIG)); //Reservamos un espacio para la nueva palabra
			if(nuevoptr!=NULL) //Si tenemos espacio
			{
				strcpy(nuevoptr->palabra,palabrados); //Guardamos la palabra en la cola
				nuevoptr->sigptr=NULL;
				if((*iniptr)==NULL) //Si no tenemos palabras guardadas
				{
					(*iniptr)=nuevoptr; //La utilizamos como primer nodo
					(*finptr)=nuevoptr;
				}
				else //Si si tenemos palabras guardadas
				{
					(*finptr)->sigptr=nuevoptr;//La utilizamos como un nuevo nodo unicamente.
					(*finptr)=nuevoptr;
				}
			}
			j++;
        }
}

void imprime_lista(LISTA_ORIG_PTR iniptr) //Función que imprime la lista y elimina caracteres nulo.
{
	while(iniptr!=NULL)
	{
		iniptr->palabra[strlen(iniptr->palabra)-1]='\0'; //Eliminamos los caracteres nulo adicionales
		printf("%s\n",iniptr->palabra); //Mostramos la palabra actual
		iniptr=iniptr->sigptr; //Avanzamos a la siguiente palabra
	}
}

existe(char palabra[30], LISTA_DPRD_PTR iniptr2) //Función que verifica si la palabra ya existe
{
	while(iniptr2!=NULL) //Mientras no lleguemos al final de la lista DEPURADA
	{
		if(strcmp(palabra, (iniptr2->palabra)) == 0) //Comparamos la palabra que se esta revisando en la función anterior con la lista de palabras depuradas
			return 0; //Si ya esta, regresamos un cero para que ya no compare
		iniptr2=iniptr2->sigptr; //Avanzamos a la siguiente palabra de la lista original para que se compare con la que se esta revisando
	}
	return 1; //Si al terminar de comparar la palabra actual con todas las palabras de la lista depurada, no hay coincidencias, regresamos un uno para que se agregue.	
}

compara(char palabra[30], LISTA_DPRD_PTR *iniptr2, LISTA_DPRD_PTR *finptr2, LISTA_ORIG_PTR iniptr) //Función que crea la lista depurada y el reporte uno
{
	int i=0;
	char palabraaux[30];
	LISTA_ORIG_PTR auxiliar;
	LISTA_DPRD_PTR nuevoptr;
	
	auxiliar=iniptr; //Hacemos que auxiliar apunte al inicio para no perder la posición de iniptr y usarlo después
	nuevoptr = (LISTA_DPRD_PTR) malloc(sizeof(LISTA_DPRD)); //Reservamos un espacio para la nueva palabra de la lista depurada
	strcpy(nuevoptr->palabra, palabra); //Copiamos en el nuevo nodo, la palabra que estamos revisando
	nuevoptr->sigptr=NULL; //Le asignamos un valor nulo a sigptr
		
	while(auxiliar!=NULL) //Mientras auxiliar no llegue al final de la lista
	{
		strcpy(palabraaux,(auxiliar->palabra)); //Copiamos la palabra que esta siendo apuntada por auxiliar en palabraaux
		auxiliar=auxiliar->sigptr; //Avanzamos al siguiente elemento de la cola
		if(strcmp(palabra, palabraaux) == 0) //Si la palabra que vamos a agregar a la lista depurada, encuentra una repetición en la lista original
			i++; //Incrementa el numero de repeticiones en uno
	}
	nuevoptr->total=i; //Al final le asignamos el total de repeticiones al total del nuevo nodo
	if((*iniptr2) == NULL) //Si no tenemos ningun nodo antes de este
	{
		(*iniptr2)=nuevoptr; //Lo converimos en el primer nodo
		(*finptr2)=nuevoptr;
	}
	else // Si ya teníamos nodos
	{
		(*finptr2)->sigptr=nuevoptr; //Lo agregamos como un nuevo nodo.
		(*finptr2)=nuevoptr;
	}
}

void crea_depura_y_reporte(LISTA_ORIG_PTR iniptr, LISTA_DPRD_PTR *iniptr2, LISTA_DPRD_PTR *finptr2) //Función que crea la lista depurada y el reporte uno
{
	LISTA_ORIG_PTR auxiliar;
	auxiliar=iniptr; //Creamos un auxiliar que apunte al mismo lugar que iniptr, ya que necesitamos enviar a iniptr a la función que compara
	if(iniptr != NULL) //Si el archivo no esta vacio
	{
		while(auxiliar != NULL) //Mientras no lleguemos al final de la lista
		{
			 if(existe((auxiliar->palabra), (*iniptr2))) //Verificamos si la palabra ya ha sido revisada antes
				compara((auxiliar->palabra), iniptr2, finptr2, iniptr); //Si es la primera vez que se revisa, buscamos repeticiones y depuramos la lista
			 auxiliar= auxiliar->sigptr; //Avanzamos a la siguiente palabra
		}
	}
}

void imprime_lista_depurada(LISTA_DPRD_PTR iniptr, FILE **depurauno, FILE **reporteuno) //Función que imprime la lista depurada y la guarda en un archivo.
{
	while(iniptr!=NULL) //Mientras no lleguemos al final de la cola
	{
		printf("%s, %d\n",iniptr->palabra, iniptr->total); //Mostramos la palabra actual y sus repeticiones
		fprintf((*depurauno), "%s\n", iniptr->palabra); //Guardamos la palabra actual en la lista depurada
		fprintf((*reporteuno), "%s, %d\n",iniptr->palabra, iniptr->total); //Guardamos la palabra actual y su total de repeticiones en el reporte 1.
		iniptr=iniptr->sigptr; //Avanzamos a la siguiente palabra
	}
}

/********************************************************************************
*********************************************************************************
***                                                                           ***
***                       F U N C I O N E S      D E                          ***
***                        O R D E N A M I E N T O                            ***
***                                                                           ***
*********************************************************************************
********************************************************************************/

void duplica_depurauno(LISTA_DPRD_PTR iniptr2,DEPURA_DUP_PTR *iniptr3, DEPURA_DUP_PTR *finptr3) //Función que ordena la lista
{
	DEPURA_DUP_PTR nuevoptr;
	DEPURA_DUP_PTR auxuno;
	DEPURA_DUP_PTR auxdos;
	
	//A TRAVÉS DEL MÉTODO DE INSERCIÓN DIRECTA, ORDENAMOS LA COLA
	
	while(iniptr2!=NULL) //Mientras no termine la cola
	{
		auxuno=(*iniptr3);
		auxdos=(*finptr3);
		
		nuevoptr = (DEPURA_DUP_PTR) malloc(sizeof(DEPURA_DUP)); //Creamos un nodo
		if(nuevoptr==NULL) //Si no se crea, no hay espacio en memoria
		{
		      printf("No hay espacio en memoria");
		}
		else //Si se crea...
		{
		       fflush(stdin);
		       strcpy(nuevoptr->palabra, iniptr2->palabra);	//Guardamos la palabra en el nuevo nodo	       
		       (nuevoptr->sigptr)=NULL;
		       
		       if(*iniptr3==NULL) //Si es el primer nodo...
		       {
		           *iniptr3=nuevoptr;
		           *finptr3=nuevoptr;
		       }
		       
		       else
		       {
		       		if(strcmp(nuevoptr->palabra,auxuno->palabra)<0) //Si va antes del primer nodo...
					{
						nuevoptr->sigptr=auxuno;
						*iniptr3=nuevoptr;
					}
						
		       	    else
					{
						if(strcmp(nuevoptr->palabra,auxdos->palabra)>0)//Si va después del último nodo...
						{
							auxdos->sigptr=nuevoptr;
							*finptr3=nuevoptr;
						}
						
						else
						{
							while(strcmp((nuevoptr->palabra),(auxuno->palabra))>0) //Si va enmedio...
							{
								auxuno=auxuno->sigptr;
							}
							
							auxdos=*iniptr3;
							while((auxdos->sigptr)!=(auxuno))
							{
								auxdos=auxdos->sigptr;
							}
							auxdos->sigptr=nuevoptr;
							nuevoptr->sigptr=auxuno;
							
						} 
						
					}
			   }
		}
		iniptr2=iniptr2->sigptr; //Nos recorremos al siguiente elemento
	}
}

void imprime_depurauno_dup(DEPURA_DUP_PTR iniptr3) //Función que imprime la lista duplicada
{
	while(iniptr3!=NULL) //Mientras no lleguemos al final de la cola
	{
		printf("%s\n",iniptr3->palabra); //Mostramos la palabra actual
		iniptr3=iniptr3->sigptr; //Avanzamos a la siguiente palabra
	}
}

/********************************************************************************
*********************************************************************************
***                                                                           ***
***                       F U N C I O N E S      D E                          ***
***                      C O N V E R S I Ó N        A                         ***
***                            F O N É T I C O                                ***
***                                                                           ***
*********************************************************************************
********************************************************************************/

void cambio_acentos (char palabra_fon[30]) //1. Reemplazar las vocales acentuadas por el código correspondiente. (á=1, é=2, í=3, ó=4, ú=5)
{ 
  int k = strlen(palabra_fon); 
  int i; 
  for( i =0; i<k; i++) 
 { 
   if( palabra_fon [i] == 'á') 
    { 
       palabra_fon [i]= '1'; 
    }
   if( palabra_fon [i] == 'é') 
    { 
       palabra_fon [i]= '2'; 
    }
    if( palabra_fon [i] == 'í') 
    { 
       palabra_fon [i]= '3'; 
    }
   if( palabra_fon [i] == 'ó') 
    { 
       palabra_fon [i]= '4'; 
    }
    if( palabra_fon [i] == 'ú') 
    { 
       palabra_fon [i]= '5'; 
    }
 } 
}

void cambio_qu(char palabra_fon[30]) //2. Reemplazar ‘qu’ por ‘K’
{ 
	int k = strlen(palabra_fon); 
	int i;
	int j;
	for(i =0; i<k; i++) 
	{ 
	   if(palabra_fon[i] == 'q') 
	   { 
	       if(palabra_fon[i+1] == 'u')
	       {
	       	    j=i;
				palabra_fon[j] = 'K';
	       	    j++;
	       	    while(j<k)
	       	    {
	       	    	palabra_fon[j]=palabra_fon[j+1];
	       	    	j++;
	       	    }
	       }
	   } 
	}
}

void cambio_ca (char palabra_fon[30]) //3. Reemplazar ‘ca’ por ‘Ka’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i =0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'c') 
	   { 
	      if( palabra_fon [i + 1] == 'a') 
	          palabra_fon[i]= 'K';
	   } 
	}
}

void cambio_co (char palabra_fon[30]) //4. Reemplazar ‘co’ por ‘Ko’
{ 
  int k = strlen(palabra_fon); 
  int i; 
  for( i =0; i<k; i++) 
 { 
   if( palabra_fon [i] == 'c') 
    { 
      if( palabra_fon [i + 1] == 'o') 
	     palabra_fon[i]= 'K'; 
    } 
  } 
}

void cambio_cu (char palabra_fon[30]) //5. Reemplazar ‘cu’ por ‘Ku’
{ 
  int k = strlen(palabra_fon); 
  int i; 
  for( i =0; i<k; i++) 
 { 
   if( palabra_fon [i] == 'c') 
    { 
      if( palabra_fon [i + 1] == 'u') 
	     palabra_fon[i]= 'K'; 
    } 
  } 
}

void cambio_ce (char palabra_fon[30]) //6. Reemplazar ‘ce’ por ‘Se’
{ 
  int k = strlen(palabra_fon); 
  int i; 
  for( i =0; i<k; i++) 
 { 
   if( palabra_fon [i] == 'c') 
    { 
      if( palabra_fon [i + 1] == 'e') 
	     palabra_fon[i]= 'S'; 
    } 
  } 
}

void cambio_ci (char palabra_fon[30]) //7. Reemplazar ‘ci’ por ‘Si’
{ 
  int k = strlen(palabra_fon); 
  int i; 
  for( i =0; i<k; i++) 
 { 
   if( palabra_fon [i] == 'c') 
    { 
      if( palabra_fon [i + 1] == 'i') 
	     palabra_fon[i]= 'S'; 
    } 
  } 
}

void cambio_ch(char palabra_fon[30]) //8. Reemplazar ‘ch’ por ‘C’
{ 
	int k = strlen(palabra_fon); 
	int i;
	int j;
	for(i =0; i<k; i++) 
	{ 
	   if(palabra_fon[i] == 'c') 
	   { 
	       if(palabra_fon[i+1] == 'h')
	       {
	       		j=i;
	       	    palabra_fon[j] = 'C';
	       	    j++;
	       	    while(j<k)
	       	    {
	       	    	palabra_fon[j]=palabra_fon[j+1];
	       	    	j++;
	       	    }
	       }
	   } 
	}
}

void cambio_v (char palabra_fon[30]) //9. Reemplazar ‘v’ por ‘B’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i=0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'v') 
	   {  
	        palabra_fon[i]= 'B';
	   } 
	}
}

void cambio_z (char palabra_fon[30]) //10. Reemplazar ‘z’ por ‘S’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i=0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'z') 
	   {  
	        palabra_fon[i]= 'S';
	   } 
	}
}

void cambio_w (char palabra_fon[30]) //11. Reemplazar ‘w’ por ‘U’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i=0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'w') 
	   {  
	        palabra_fon[i]= 'U';
	   } 
	}
}

void cambio_h (char palabra_fon[30]) //12. Eliminar ‘h’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i=0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'h') 
	   {  
	        while(i<k)
	       	{
	       		palabra_fon[i]=palabra_fon[i+1];
	       	    i++;
	       	}
	   } 
	}
}

void cambio_y (char palabra_fon[30]) //13. Reemplazar “y” por “I” si se encuentra: | a. Al final de la palabra | b. Sola
{ 
	int k = strlen(palabra_fon); 
	int i;
	if( palabra_fon[k-1] == 'y')
	{
		palabra_fon[k-1] = 'I';
	}
	if( palabra_fon[0] == 'y')
	{
		if( palabra_fon[1] == '\0')
		{
			palabra_fon[0] = 'I';
		}
	}
}

void cambio_r (char palabra_fon[30]) //14. Reemplazar “r” por “W” si se encuentra: |a. Después de las consonantes “L, N, S” | b. Al principio de las palabras
																				  //c. Después del prefijo “sub”
{ 
	int k = strlen(palabra_fon); 
	int i; 
	for( i =0; i<k; i++) 
	{ 
		if( palabra_fon [i] == 'l') 
	    { 
			if( palabra_fon [i + 1] == 'r') 
				palabra_fon[i+1]= 'W'; 
	    }
		if( palabra_fon [i] == 'n') 
	    { 
			if( palabra_fon [i + 1] == 'r') 
				palabra_fon[i+1]= 'W'; 
	    }
		if( palabra_fon [i] == 's') 
	    { 
			if( palabra_fon [i + 1] == 'r') 
				palabra_fon[i+1]= 'W'; 
	    }   
  	}
	if(palabra_fon[0] == 'r')
		palabra_fon[0] = 'W';
	if( palabra_fon [0] == 's') 
    { 
		if( palabra_fon [1] == 'u')
		{ 
			if( palabra_fon [2] == 'b')
			{ 
				if( palabra_fon [3] == 'r')
				{ 
					palabra_fon[3]= 'W';
				}
			}
		}
    }   
}

void cambio_rr(char palabra_fon[30]) //15. Reemplazar ‘rr’ por ‘W’
{ 
	int k = strlen(palabra_fon); 
	int i;
	int j;
	for(i =0; i<k; i++) 
	{ 
	   if(palabra_fon[i] == 'r') 
	   { 
	       if(palabra_fon[i+1] == 'r')
	       {
	       		j=i;
	       	    palabra_fon[j] = 'W';
	       	    j++;
	       	    while(j<k)
	       	    {
	       	    	palabra_fon[j]=palabra_fon[j+1];
	       	    	j++;
	       	    }
	       }
	   } 
	}
}

void cambio_ll(char palabra_fon[30]) //15. Reemplazar ‘rr’ por ‘W’
{ 
	int k = strlen(palabra_fon); 
	int i;
	int j;
	for(i =0; i<k; i++) 
	{ 
	   if(palabra_fon[i] == 'l') 
	   { 
	       if(palabra_fon[i+1] == 'l')
	       {
	       		j=i;
	       	    palabra_fon[j] = 'Y';
	       	    j++;
	       	    while(j<k)
	       	    {
	       	    	palabra_fon[j]=palabra_fon[j+1];
	       	    	j++;
	       	    }
	       }
	   } 
	}
}

void cambio_enie (char palabra_fon[30]) //16. Reemplazar ‘ñ’ por ‘V’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i=0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'ñ') 
	   {  
	        palabra_fon[i]= 'V';
	   } 
	}
}

void cambio_x1 (char palabra_fon[30]) //17. Reemplazar “x” por “Z” (sonido /sh/) en los casos: | a. Xola, axiote, Uxmal
{ 
    if(strcmp(palabra_fon,"xola") == 0) 
    {  
         strcpy(palabra_fon,"Zola\0");
    }
	if(strcmp(palabra_fon,"axiote") == 0) 
    {  
         strcpy(palabra_fon,"aZiote\0");
    }
	if(strcmp(palabra_fon,"uxmal") == 0) 
    {  
         strcpy(palabra_fon,"uZmal\0");
    }    
}

void cambio_x2 (char palabra_fon[30]) //18. Reemplazar “x” por “S” si se encuentra: | a. Al principio de la palabra
{ 
	int k = strlen(palabra_fon); 
	int i;
    if( palabra_fon [0] == 'x') 
    {  
         palabra_fon[i]= 'S';
    } 
}

void cambio_x3(char palabra_fon[30]) //19. Reemplazar “x” por “KS” si se encuentra: | a. Entre vocales | b. Antes de una consonante
                                                                                    //c. Al final de una palabra
{ 
	int k = strlen(palabra_fon); 
	int i;
	int j;
	for(i =0; i<k; i++) 
	{
	   if(palabra_fon[i] == 'x') 
	   { 
	       if(palabra_fon[i+1] == 'b' || palabra_fon[i+1] == 'c' || palabra_fon[i+1] == 'd' || palabra_fon[i+1] == 'f' || palabra_fon[i+1] == 'g' || palabra_fon[i+1] == 'h'
		   							  || palabra_fon[i+1] == 'j' || palabra_fon[i+1] == 'k' || palabra_fon[i+1] == 'l' || palabra_fon[i+1] == 'm' || palabra_fon[i+1] == 'n'
									  || palabra_fon[i+1] == 'ñ' || palabra_fon[i+1] == 'p' || palabra_fon[i+1] == 'q' || palabra_fon[i+1] == 'r' || palabra_fon[i+1] == 's'
									  || palabra_fon[i+1] == 't' || palabra_fon[i+1] == 'v' || palabra_fon[i+1] == 'w' || palabra_fon[i+1] == 'x' || palabra_fon[i+1] == 'y'
									  || palabra_fon[i+1] == 'z')
	       {
	       	    palabra_fon[i] = 'K';
	       	    while(k>i)
	       	    {
	       	    	palabra_fon[k]=palabra_fon[k-1];
	       	    	k--;
	       	    }
	       	    palabra_fon[i+1] = 'S';
	       }
	   }
	   
		if(palabra_fon[i]=='x')
		{
			if(palabra_fon[i+1] == 'a' || palabra_fon[i+1] == 'e' || palabra_fon[i+1] == 'i' || palabra_fon[i+1] == 'o' || palabra_fon[i+1] == 'u')
			{
				if(palabra_fon[i-1] == 'a' || palabra_fon[i-1] == 'e' || palabra_fon[i-1] == 'i' || palabra_fon[i-1] == 'o' || palabra_fon[i-1] == 'u')
				{
					palabra_fon[i] = 'K'; 
					while(k>i) 
					{ 
					palabra_fon[k+1]=palabra_fon[k];
					k--; 
					} 
					palabra_fon[i+1] = 'S';
				}
			}
		}
		
	   
	   if(palabra_fon[k-1] == 'x')
	   {
	   		palabra_fon[k-1] = 'K';
	   		palabra_fon[k] = 'S';
	   		palabra_fon[k+1] = '\0';
	   }
	}
}

void cambio_j (char palabra_fon[30]) //20. Reemplazar ‘j’ por ‘X’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i=0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'j') 
	   {  
	        palabra_fon[i]= 'X';
	   } 
	}
}

void cambio_ge (char palabra_fon[30]) //21. Reemplazar ‘ge’ por ‘Xe’
{ 
  int k = strlen(palabra_fon); 
  int i; 
  for( i =0; i<k; i++) 
 { 
   if( palabra_fon [i] == 'g') 
    { 
      if( palabra_fon [i + 1] == 'e') 
	     palabra_fon[i]= 'X'; 
    } 
  } 
}

void cambio_gi (char palabra_fon[30]) //22. Reemplazar ‘gi’ por ‘Xi’
{ 
  int k = strlen(palabra_fon); 
  int i; 
  for( i =0; i<k; i++) 
 { 
   if( palabra_fon [i] == 'g') 
    { 
      if( palabra_fon [i + 1] == 'i') 
	     palabra_fon[i]= 'X'; 
    } 
  } 
}

void cambio_gue(char palabra_fon[30]) //23. Reemplazar ‘gue’ por ‘Ge’
{ 
	int k = strlen(palabra_fon); 
	int i;
	int j;
	for(i =0; i<k; i++) 
	{ 
	   if(palabra_fon[i] == 'g') 
	   { 
	       if(palabra_fon[i+1] == 'u')
	       {
	       	   if(palabra_fon[i+2] == 'e')
		       {
		       		j=i;
		       	    palabra_fon[j] = 'G';
		       	    j++;
		       	    while(j<k)
		       	    {
		       	    	palabra_fon[j]=palabra_fon[j+1];
		       	    	j++;
		       	    }
		       }
	       }
	   } 
	}
}

void cambio_gui(char palabra_fon[30]) //24. Reemplazar ‘gui’ por ‘Gi’
{ 
	int k = strlen(palabra_fon); 
	int i;
	int j;
	for(i =0; i<k; i++) 
	{ 
	   if(palabra_fon[i] == 'g') 
	   { 
	       if(palabra_fon[i+1] == 'u')
	       {
	       	   if(palabra_fon[i+2] == 'i')
		       {
		       		j=i;
		       	    palabra_fon[j] = 'G';
		       	    j++;
		       	    while(j<k)
		       	    {
		       	    	palabra_fon[j]=palabra_fon[j+1];
		       	    	j++;
		       	    }
		       }
	       }
	   } 
	}
}

void cambio_u_dieresis (char palabra_fon[30]) //25. Reemplazar ‘ü’ por ‘U’
{ 
	int k = strlen(palabra_fon); 
	int i;
	for( i=0; i<k; i++) 
	{ 
	   if( palabra_fon [i] == 'ü') 
	   {  
	        palabra_fon[i]= 'U';
	   } 
	}
}

void conversor_a_fonetico(DEPURA_DUP_PTR iniptr3) //Función que llama a todos los conversores de letra, para convertir del alfabeto español, al fonético.
{
	while(iniptr3!=NULL) //Mientras no lleguemos al final de la cola. Llama a todas las funciones.
	{
		strcpy(iniptr3->palabra_fon,iniptr3->palabra);
		cambio_acentos(iniptr3->palabra_fon); //Realizamos cada uno de los cambios.
		cambio_qu(iniptr3->palabra_fon);
		cambio_ca(iniptr3->palabra_fon);
		cambio_co(iniptr3->palabra_fon);
		cambio_cu(iniptr3->palabra_fon);
		cambio_ce(iniptr3->palabra_fon);
		cambio_ci(iniptr3->palabra_fon);
		cambio_ch(iniptr3->palabra_fon);
		cambio_v(iniptr3->palabra_fon);
		cambio_z(iniptr3->palabra_fon);
		cambio_w(iniptr3->palabra_fon);
		cambio_h(iniptr3->palabra_fon);
		cambio_y(iniptr3->palabra_fon);
		cambio_r(iniptr3->palabra_fon);
		cambio_rr(iniptr3->palabra_fon);
		cambio_ll(iniptr3->palabra_fon);
		cambio_enie(iniptr3->palabra_fon);
		cambio_x1(iniptr3->palabra_fon);
		cambio_x2(iniptr3->palabra_fon);
		cambio_x3(iniptr3->palabra_fon);
		cambio_j(iniptr3->palabra_fon);
		cambio_ge(iniptr3->palabra_fon);
		cambio_gi(iniptr3->palabra_fon);
		cambio_gue(iniptr3->palabra_fon);
		cambio_gui(iniptr3->palabra_fon);
		cambio_u_dieresis(iniptr3->palabra_fon);
		
		iniptr3=iniptr3->sigptr; //recorrete al siguiente elemento
	}
}

void contador_fon(DEPURA_DUP_PTR iniptr3)
{
     DEPURA_DUP_PTR actual;
     DEPURA_DUP_PTR auxiliar;
     int i = 0;
     actual = iniptr3;
     
     while(actual!=NULL) //En el contador de palabra fonética ponemos 0 en todas las palabras
     {
          actual->fon_repetido=0;
          actual=actual->sigptr; //Avanzamos                 
     }
     
     if(iniptr3!=NULL) //Hasta que no termine la lista
     {
         actual=iniptr3; //Guardamos la posición actual de iniptr3
         
         while(actual!=NULL) //Mientras actual no termine de recorrer la lista
         {
             auxiliar=iniptr3; //Le asigamos a auxiliar, la posición de iniptr3
             if(actual->fon_repetido==0) //Si no tiene código fonético
             {
                 i++; //Incrementamos a i
                 while(auxiliar!=NULL) //Mientras auxiliar no termine de recorrer
                 {                
                     if(strcasecmp((auxiliar->palabra_fon),(actual->palabra_fon)) == 0) //Comparamos la palabra de auxiliar con la de actual
                     {
                         auxiliar->fon_repetido=i; //Si son iguales, les ponemos el mismo código fonético
                     }
                     auxiliar=(auxiliar->sigptr); //Recorremos a auxiliar
                 }
                 
             }
             actual=actual->sigptr; //Recorremos a actual
         }
     }
}

void imprime_fonetico(DEPURA_DUP_PTR iniptr3, FILE **listacod, FILE **reportedos, FILE **listaclass) //Función que imprime la lista duplicada
{
	int i=0;
	while(iniptr3!=NULL) //Mientras no lleguemos al final de la cola
	{
		i++; //Incrementamos en uno el total de palabras
		iniptr3->cont_palabra=i; //Almacenamos el consecutivo de palabra, en la cola
		printf("%s, %s, %d, %d\n",iniptr3->palabra, iniptr3->palabra_fon, iniptr3->cont_palabra, iniptr3->fon_repetido); //Mosytramos la palabra, la palabra codificada, y el consecutivo de palabra.
		fprintf((*listacod), "%s, %s\n",iniptr3->palabra, iniptr3->palabra_fon); //Guardamos la palabra, y la palabra codificada en l lista codificada.
		fprintf((*listaclass), "%s, %s, %d, %d\n",iniptr3->palabra, iniptr3->palabra_fon, iniptr3->cont_palabra, iniptr3->fon_repetido); //Guardamos la palabra, la palabra codificada, el codigo de palabra y el código de palabra fonético.
        iniptr3=iniptr3->sigptr; //Avanzamos a la siguiente palabra 
	}
	fprintf((*reportedos), "Total de palabras codificadas: %d\n", i); //Guardamos el total de palabras en el archivo.
}

void crea_equalcode(DEPURA_DUP_PTR iniptr3, FILE **equalcode) //Funcion que busca los codigos foneticos iguales
{
     int i=0, j=0;
     int auxiliar=0;
     DEPURA_DUP_PTR ap1;
     
     ap1=iniptr3;//Le asignamos a ap1 la posición de iniptr3
     while(ap1!=NULL) //Mientrass ap1 no termine
     {
         if((ap1->fon_repetido)>auxiliar) //Si el codigo fonetico de ap1 es mayor que auxiliar
               auxiliar=ap1->fon_repetido; //Auxiliar se le asigna el codigo de fon repetido
         ap1=ap1->sigptr; //Avanzamos a ap1
     }
     while(i<auxiliar) //Mientras i sea menor que el codigo fonético más grande
     {
         j=0;
         i++;
         ap1=iniptr3; //ap1 apunta al mismo lugar que iniptr3
         while(ap1!=NULL) //Mientras ap1 no termine de recorrer
         {
             if((ap1->fon_repetido) == i) //Si el contador fonetico de ap1 es igual a i
             {
                  j++; //Incrementamos a j
             }
             ap1=ap1->sigptr; //Avanzamos a ap1
         }
         if(j>1) //Si J es mayor que 1
         {
             ap1=iniptr3; //ap1 apunta a iniptr3
             while(ap1!=NULL) //Mientras ap1 no termine de recorrer
             {
                 if((ap1->fon_repetido) == i) //Si el contador fonetico de ap1 es igual a 1i
                      fprintf((*equalcode), "%s, %s, %d, %d\n",ap1->palabra, ap1->palabra_fon, ap1->cont_palabra, ap1->fon_repetido); //Guardamos en equalcode los diferentes atributos de cada palabra
                 ap1=ap1->sigptr; //Avanzamos a ap1
             }
         }
         
     }                   
}

void crea_diferentcode(DEPURA_DUP_PTR iniptr3, FILE **diferentcode, DEPURA_COD_PTR *iniptr4, DEPURA_COD_PTR *finptr4) //funcion que guarda las palabras con diferente codigo fonético
{
     int i=0;
     int auxiliar=0;
     DEPURA_DUP_PTR ap1;
     DEPURA_COD_PTR nuevoptr;
     
     ap1=iniptr3;
     while(ap1!=NULL) //Mientras no termine de recorrer
     {
         if((ap1->fon_repetido)>auxiliar)
               auxiliar=ap1->fon_repetido; //Vamos a buscar el contador fonetico más grande
         ap1=ap1->sigptr;
     }
     
     while(i<auxiliar) //Mientras no lleguemos al último contador fonético
     {
         i++;
         ap1=iniptr3;
            while(ap1!=0) //Mientras ap1 sea diferente de 0
            {
                if((ap1->fon_repetido)==i) //Si el contaddor fonetico de ap1 es igual a i
                {
                     fprintf((*diferentcode), "%s, %s, %d, %d\n",ap1->palabra, ap1->palabra_fon, ap1->cont_palabra, ap1->fon_repetido); //Guardamos la palabra en diferentcode
                     nuevoptr = (DEPURA_COD_PTR) malloc(sizeof(DEPURA_COD)); //Creamos un nodo
                     strcpy((nuevoptr->palabra),(ap1 -> palabra)); //Llenamos el nodo
					 strcpy((nuevoptr->palabra_fon),(ap1 -> palabra_fon));
                     nuevoptr->cont_palabra = ap1 -> cont_palabra;
                     nuevoptr->fon_repetido = ap1 -> fon_repetido;
                     if(*iniptr4==NULL) //Si es el primer nodo...
					 {
					    *iniptr4=nuevoptr; 
					    *finptr4=nuevoptr;
					 }
					 else //Si no es el primer nodo
					 {
					 	(*finptr4)->sigptr=nuevoptr;
						(*finptr4)=nuevoptr;
					 }
                     break;
                }                             
            ap1=ap1->sigptr; //Avanzamos a ap1
            }
     }                  
}

/********************************************************************************
*********************************************************************************
***                                                                           ***
***                       F U N C I O N E S      D E                          ***
***                        C R E A C I O N       D E                          ***
***                               G R U P O S                                 ***
***                                                                           ***
*********************************************************************************
********************************************************************************/

void recorrido_de_comparaciones (char palabra_fon[], char palabra[], int cont_palabra, int fon_repetido, int i, DEPURA_COD_PTR actual, FILE **similarcode, char aux[], DEPURA_COD_PTR respaldo) //Funcion que busca palabras similares
{
	actual=respaldo; //Regresamos a actual al inicio
	while(actual != NULL) //Mientras actual no termine de recorrer
	{
		if(strcasecmp((palabra_fon),(actual->palabra_fon)) == 0) //Si la palabra alterada es igual a la actual
		{
			if((actual -> cont_palabra) != cont_palabra) //Si la palabra que revisamos no es la misma que la que alteramos
				fprintf((*similarcode), "%s|%s|%d|%d|g%d|%s|%s|%d|%d\n", palabra, aux, cont_palabra, fon_repetido, i, (actual -> palabra), (actual -> palabra_fon), (actual -> cont_palabra), (actual -> fon_repetido)); //Guardamos la similitud
		}
		actual= actual->sigptr; //Avanzamos
	}
}

void letra_pre_palabra (DEPURA_COD_PTR iniptr3, char palabra_fon[], char palabra[], int cont_palabra, int fon_repetido, FILE **similarcode, DEPURA_COD_PTR respaldo) 
{ 
 	int k = strlen(palabra_fon);
	char aux[k];  
	iniptr3=respaldo;
    k++; //Para que agregue una letra al final
    strcpy(aux, palabra_fon);
    while(k>0) //Mientras el final de palabra no llegue al inicio
	 {
		 palabra_fon[k]=palabra_fon[k-1]; //Pasamos la letra anterior a la que estamos, a donde estamos
		  k--; //Nos regresamos una letra
	 } 
	palabra_fon[0] = ' '; //Cuando liberemos el primer carácter, le ponemos un “ “
	
	palabra_fon[0]='a'; //Luego ya haces los cambios con cada letra
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='b';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='c';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='d';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='e';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='f';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='g';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='i';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='k';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='l';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='m';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='n';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='o';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='p';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='r';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='s';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='t';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='u';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='v';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo); 
	
	palabra_fon[0]='w';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo); 
    
    palabra_fon[0]='x';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);  
    
    palabra_fon[0]='y';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);   
    
    palabra_fon[0]='z';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='1';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='2';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='3';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='4';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[0]='5';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, 1, iniptr3, similarcode, aux, respaldo);
    
    strcpy(palabra_fon, aux);   // Regresamos la palabra a como estaba originalmente 
       
}

void letra_in_palabra(DEPURA_COD_PTR iniptr3, char palabra_fon[], char palabra[], int cont_palabra, int fon_repetido, FILE **similarcode, DEPURA_COD_PTR respaldo) //Funcion que busca similitudes en las letras dentro de la palbra
{
	int k, i;
	iniptr3=respaldo;
	k = strlen(palabra_fon); //Medimos el tamaño de la palabra
	char aux[k];
	for(i=0; i<k; i++) //Mientras no acabemos de recorrer la palabra 
	{
	   strcpy(aux, palabra_fon); //Respaldamos la palabra
	    palabra_fon[i]='a'; //Luego ya haces los cambios con cada letra
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo); //Llamamos a recorrido de comparaciones
	    
	    palabra_fon[i]='b';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='c';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='d';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='e';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='f';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='g';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='i';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='k';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='l';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='m';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='n';
	     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='o';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='p';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='r';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='s';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='t';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='u';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='v';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo); 
		
		palabra_fon[i]='w';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo); 
	    
	    palabra_fon[i]='x';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);  
	    
	    palabra_fon[i]='y';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);   
	    
	    palabra_fon[i]='z';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='1';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='2';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='3';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='4';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	    
	    palabra_fon[i]='5';
	    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (i+2), iniptr3, similarcode, aux, respaldo);
	   strcpy(palabra_fon, aux); //Regresamos a la palabra original a como estaba
	}
}

void letra_post_palabra(DEPURA_COD_PTR iniptr3, char palabra_fon[], char palabra[], int cont_palabra, int fon_repetido, FILE **similarcode, DEPURA_COD_PTR respaldo) //Funcion que busca coincidencias de letra al final de la palabra
{ 
 	int k = strlen(palabra_fon);
	char aux[k];  
	iniptr3=respaldo;
    
    strcpy(aux, palabra_fon); //Copiamos en aux palabra_fon
    
    palabra_fon[k + 1] = palabra_fon[k]; //Agregamos un caracter a la palabra
    palabra_fon[k] = ' '; //En el último caracter ponemos un espacio
	
	palabra_fon[k]='a'; //Luego ya haces los cambios con cada letra
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo); //Llamamos a recorrido de comparaciones
    
    palabra_fon[k]='b';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='c';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='d';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='e';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='f';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='g';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='i';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='k';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='l';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='m';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='n';
     recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='o';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='p';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='r';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='s';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='t';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='u';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='v';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo); 
	
	palabra_fon[k]='w';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo); 
    
    palabra_fon[k]='x';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);  
    
    palabra_fon[k]='y';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);   
    
    palabra_fon[k]='z';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='1';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='2';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='3';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='4';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    palabra_fon[k]='5';
    recorrido_de_comparaciones (palabra_fon, palabra, cont_palabra, fon_repetido, (k+2), iniptr3, similarcode, aux, respaldo);
    
    strcpy(palabra_fon, aux); //Regresamos la palabra fonetica a como estaba antes de los cambios
       
}

void busca_similitudes (DEPURA_COD_PTR iniptr3, FILE **similarcode, DEPURA_COD_PTR respaldo) //Funcion quue llama a las funciones de busqueda
{
	int k;
	k=0;
	while(iniptr3 != NULL) //Mientras no termine de recorrer
	{
		printf("%s\n",iniptr3->palabra_fon); //Imprimimos la palabra actual
		letra_pre_palabra(iniptr3, iniptr3 -> palabra_fon, iniptr3 -> palabra, iniptr3 -> cont_palabra, iniptr3 -> fon_repetido, similarcode, respaldo);
		letra_in_palabra(iniptr3, iniptr3 -> palabra_fon, iniptr3 -> palabra, iniptr3 -> cont_palabra, iniptr3 -> fon_repetido, similarcode, respaldo);
		letra_post_palabra(iniptr3, iniptr3 -> palabra_fon, iniptr3 -> palabra, iniptr3 -> cont_palabra, iniptr3 -> fon_repetido, similarcode, respaldo);
		
		iniptr3 = iniptr3 -> sigptr; //Avanzamos
	}
}

void main()
{
	FILE *lista; //Declaramos un apuntador a la lista original (Entrada)
	FILE *depurauno; //Declaramos un apuntador a la lista depurada (Salida)
	FILE *reporteuno; //Declaramos un apuntador al reporte 1 (Salida)
	FILE *listacod;
	FILE *reportedos;
	FILE *listaclass;
	FILE *equalcode;
	FILE *diferentcode;
	FILE *similarcode;
	
	LISTA_ORIG_PTR iniptr=NULL; //Creamos el apuntador al inicio de la cola
	LISTA_ORIG_PTR finptr=NULL; //Creamos el apuntador al fin de la cola
	
	LISTA_DPRD_PTR iniptr2=NULL; //Creamos el apuntador al inicio de la cola
	LISTA_DPRD_PTR finptr2=NULL; //Creamos el apuntador al fin de la cola 
	
	DEPURA_DUP_PTR iniptr3=NULL; //Creamos el apuntador al inicio de la cola
	DEPURA_DUP_PTR finptr3=NULL; //Creamos el apuntador al fin de la cola 
	
	DEPURA_COD_PTR iniptr4=NULL; //Creamos el apuntador al inicio de la cola
	DEPURA_COD_PTR finptr4=NULL; //Creamos el apuntador al fin de la cola 
	 
    char palabra[30]; //Declaramos una cadena donde se almacenarán temporalmente las palabras
 
    lista = fopen("lista.txt","r+"); //Abrimos el archivo como lectura y además estructura
    depurauno = fopen("depurauno.txt","w+"); //Abrimos el archivo como lectura y escritura
    reporteuno = fopen("reporteuno.txt","w+"); //Abrimos el archivo como lectura y escritura
    listacod = fopen("listacod.txt","w+");//Abrimos el archivo como lectura y escritura
    reportedos = fopen("reportedos.txt","w+");//Abrimos el archivo como lectura y escritura
    listaclass = fopen("listaclass.txt","w+");//Abrimos el archivo como lectura y escritura
    equalcode = fopen("equalcode.txt","w+");
    diferentcode = fopen("diferentcode.txt","w+");
    similarcode = fopen("similarcode.txt","w+");
 	 	
    if (lista != NULL) //Revisamos que si se encuentre el archivo
    {
    	while(feof (lista) == 0 ) //Nos recorremos al final de la lista
        {
        	fgets(palabra,30,lista); //Nos recorremos a la siguiente palabra
        }
		if(strcmp(palabra," ")!=0)
			fprintf(lista, "\n "); //Guardamos la palabra actual en la lista depurada

        rewind(lista); //Regresamos al inicio de la lista
        
        //GUARDAMOS LA LISTA EN LA ESTRUCTURA Y EMPAREJAMOS LAS PLABRAS PARA QUE TODAS TENGAN CRACTER NULO.
        
        lista_a_estructura(&lista, &iniptr, &finptr);
        
        //MOSTRAMOS LA LISTA ORIGINAL EN PANTALLA Y ELIMINAMOS LOS CARACTERES NULO ADICIONALES
        
    	printf("Lista Original\n");
        imprime_lista(iniptr);    
        
        //DEPURAMOS LA LISTA 
        
        crea_depura_y_reporte(iniptr, &iniptr2, &finptr2);
        
        //IMPRIMINOS LA LISTA DEPURADA Y LA GUARDAMOS EN EL ARCHIVO. TAMBIÉN GUARDAMOS EL REPORTE
        
        printf("\n\nLista Depurada\n");
        
        imprime_lista_depurada(iniptr2, &depurauno, &reporteuno);
        
        //DUPLIMAMOS LA LISTA ORDENADA Y DEPURADA.
        
		printf("\n\nLista Ordenada\n");
		duplica_depurauno(iniptr2,&iniptr3, &finptr3);
        imprime_depurauno_dup(iniptr3);
        
        //REALIZAMOS EL CAMBIO DE ESPAÑOL A FONÉTICO Y CONTAMOS EL TOTAL DE PALABRAS
        
        conversor_a_fonetico(iniptr3);   
	    printf("\n\nEspanol y Fonetico\n");
        contador_fon(iniptr3);	    
        imprime_fonetico(iniptr3, &listacod, &reportedos, &listaclass);
        
        //REALIZAR EL ARCHIVO EQUALCODE
        
        crea_equalcode(iniptr3, &equalcode);
        crea_diferentcode(iniptr3, &diferentcode, &iniptr4, &finptr4);
        
        //CREAMOS LOS GRUPOS
        
        busca_similitudes(iniptr4, &similarcode, iniptr4);
    }
    
    
    else
    {
        printf("No hay archivo");
        getch();
    }
    
    getch();
    
    //Cerramos los archivos
    fclose(lista);
    fclose(depurauno);
    fclose(reporteuno);
    fclose(listacod);
    fclose(reportedos);
}
