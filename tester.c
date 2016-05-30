#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <assert.h>

int count_arg(char *inst){
  int c,i;
  c=0;
  for(i=0;i< strlen(inst); i++){
    if(isdigit(inst[i]) && !isdigit(inst[i+1]))c++;
  // count_arg ne compte pas le chiffre supperieure à 10 ex) 50 90 10
  // il y a deux condition pour compter ce chiffre
  }
  return c;
}

int applati(char * inst){
  int i,f,d;
  f=0;
  d=0;
  
  for(i=0; i < strlen(inst); i++){
    if(inst[i]=='(') d++;
    if(inst[i]==')') f++;
  }
  // printf("%d %d ",f,d);
  if(f==1 && d==1)return 0;
  else return 1;
}

int calcul_interpreteur_v1(char * inst){
  int i;
  int res = 0;
  int arg = count_arg(inst);
  char * fonction; 
  char * strVal;
  char * tmp;
  tmp = inst;
 
  fonction = strtok(tmp," ()");
  // addition
  if(!strcmp(fonction,"+"))
      for(i=0 ;i < arg;i++){
	strVal =strtok (NULL, " ()");
	res += atoi(strVal);
      }
  // soustraction
  if(!strcmp(fonction,"-"))
      for(i=0 ;i< arg;i++){
   	strVal = strtok (NULL, " ()");
    if(i == 0){
      res += atoi(strVal);
    }
    if(0 < i && i < arg-1){
      res -= atoi(strVal);}
   }
  //multiplication
  if(!strcmp(fonction,"*")){
    res = 1;
    for(i=0 ; i< arg; i++){
      strVal = strtok(NULL, " ()");
      res *= atoi(strVal);
    }
  }
  //division
  if(!strcmp(fonction,"/")){
    res = 1;
    for(i=0 ; i < arg; i++){
      strVal = strtok(NULL, " ()");
      if(i == 0){
	res *= atoi(strVal);
      }
      if( i > 0 && i < arg){
	res /= atoi(strVal);
      }
    }
  }
  return res;
}

int calcul_interpreteur_v2(char * inst){
   char * debut_point;
   char * fin_point;
   char prioritaire[100];
   char buffer[50];
   int res;
   int i;
   int str;
 encore:
   if(applati(inst)==0){
   res = calcul_interpreteur_v1(inst);
   return res; }

   fin_point = strchr(inst, ')');
   debut_point = fin_point;
   fin_point++;
   while('(' != *debut_point)debut_point--;
   
   for(i=0; debut_point != fin_point ;i++, debut_point++){
     prioritaire[i]=*debut_point;
   }
   res = calcul_interpreteur_v1(prioritaire);
   sprintf(buffer,"%d",res);
   
   fin_point = strchr(inst, ')');
   debut_point = fin_point;
   fin_point++;
   while('(' != *debut_point)debut_point--;
   //printf("%c",buffer[0]);
   str= strlen(buffer); // la taille de resultat 
   for(i=0; debut_point != fin_point ;i++,debut_point++){
     if(i==0)*debut_point=' ';
     else
     if(i==1)*debut_point=buffer[0];
     else
     if(i==2 && str > 1)*debut_point=buffer[1];
     else
     if(i==3 && str > 2)*debut_point=buffer[2];
     else
     if(i==4 && str > 3)*debut_point=buffer[3];
     else
     if(i==5 && str > 4)*debut_point=buffer[4];
     else
     if(i==6 && str > 5)*debut_point=buffer[5];
     else
     if(i==7 && str > 6)*debut_point=buffer[6];
     else
     if(i==8 && str > 7)*debut_point=buffer[7];
     else
     if(i==9 && str > 8)*debut_point=buffer[8];
     else *debut_point=' ';
   }
   
   // printf("%s\n",inst); // test pour voir le calcul 
     goto encore;
   
}  
   
char * indicateur_fin(char * debut_point){
  char * fin_point;
  int count;
  fin_point= debut_point;
  count = 0;
  do{
    if(*fin_point=='(')count++;
    if(*fin_point==')')count--;
    fin_point++;
  }while(count);
  
  return fin_point;
}

struct ele{
  
  int val;
  struct ele * suivant;
};

typedef struct ele ele;
typedef struct ele * list;




int car(list l){
  if(l==(list)0){
    return -1;
  }
  else return(l->val);
}
list cdr(list l){
  if(l)
    return l->suivant;
  else
    return (list)0;
}
list cons(int val,list queue){
  list tete;
  tete=(list)malloc((size_t)sizeof(ele));
  tete->val= val;
  tete->suivant = queue;
  return tete;
}
int vide(list l){
  if(l==(list)0){
    return-1;
  }else return 0;
}

void affichage(list l){
  printf("'(");
  while(l){
   printf("%d",l->val);
   if(l->suivant != (list) 0 )printf(" ");
   l = cdr(l);
  }
  printf(")\n");

}


list list_interpreteur_v1(char * inst){
  char * fin_point;
  char * debut_point;
  char * strval;
  char * fonction;
  int first[100];
  int i;
  list nouveau=(list) 0;
  int arg = count_arg(inst);
  if(arg== 0) return (list) 0;
  //  printf("arg =%d\n",arg);
  fin_point = strchr(inst, ')');
  debut_point = fin_point;
  fin_point++;
   
   while('(' != *debut_point)debut_point--;
   strtok(inst," ()");
   for(i=0; i< arg;i++){
     strval=strtok(NULL," ()");
     first[i]=atoi(strval);
   }
     for(i--; i >= 0; i--){
     nouveau = cons(first[i],nouveau);
     }
   return nouveau;  
}

char * instruction_interperteur_v3(char * inst){
  char * debut_point;
  char * fin_point;
  char * extern_point;
  char * ele_point;
  char * detect;
  char * fonc_point;

  detect = strstr(inst, "'(");
  detect--;
   while('(' != *detect)detect--;
   detect++;
   goto car;
   if(detect==strstr(inst,"car"))goto car;
   printf("passée car\n");
   if(detect==strstr(inst,"cdr"))goto cdr;
   printf("passée cdr\n");
   if(detect==strstr(inst,"cons"))goto cons;
   printf("Aucun operateur\n");
   return inst;
   
  printf("erreur de ne pas pouvoir sauter\n");
  

  car:
  debut_point= strstr(inst,"'(");
  extern_point = debut_point;
  extern_point--;
  while('(' != *extern_point){
    //  *extern_point=' ';
    extern_point--;
  }
  // goto zone(car) simple
  debut_point++;
  debut_point++;

  //  while(!(isdigit(*debut_point) && *debut_point!=' ')){
  while(1){
    if('('==*debut_point)goto complexeCar;
    if(isdigit(*debut_point))goto simpleCar;
    debut_point++;
  }
 simpleCar:
  fonc_point=indicateur_fin(extern_point);
  while(extern_point != debut_point){
    *extern_point = ' ';
    extern_point++;
  }
  
  debut_point++;
  extern_point--;
  while(fonc_point != debut_point){
    *debut_point = ' ';
    debut_point++;
  }
  *debut_point = ' ';
  
  // printf("inst :%s\n",inst);
  
  return inst;
  
 complexeCar:   // &&&&&&&&&& supprime la fonction le dernier parenthese

 debut_point--;
 debut_point--;
  debut_point++;
  ele_point=debut_point;
  ele_point++;
  while('('!=*ele_point)ele_point++;
  *ele_point=' ';
 
  debut_point= strstr(inst,"'(");
  while('(' != *debut_point)debut_point++;
  
  fin_point=indicateur_fin(debut_point);
  debut_point= strstr(inst,"'(");

  extern_point = debut_point;
  extern_point--;
  while('(' != *extern_point){
     *extern_point=' ';
    extern_point--;
  }
  fonc_point=indicateur_fin(extern_point);
 
  *extern_point=' '; 
   fin_point++;
   while(fonc_point != fin_point){
     *fin_point=' ';
     fin_point++;
   }
    *fin_point=' ';

    //printf("inst :%s\n",inst);
  return inst;
  
 cdr:
  debut_point=strstr(inst,"'(");
  debut_point++;
  debut_point++;
   
  while(1){
    if('('==*debut_point)goto complexeCdr;
    if(isdigit(*debut_point))goto simpleCdr;
    debut_point++;
  }

 simpleCdr:
 
  while(*debut_point !=' '){
    *debut_point=' ';
    debut_point++;
  }//supprime valeur

  debut_point = strstr(inst,"'(");
  extern_point = debut_point;
  

  //printf("inst :%s\n",inst);
  return inst;

 complexeCdr:

  // printf("Debut de complexeCdr\n");
  debut_point=strstr(inst,"'(");
  debut_point ++;
  debut_point ++;
  //   printf("debut %c\n",*debut_point);
   
  while('('!=*debut_point)debut_point++;
  fin_point=indicateur_fin(debut_point);
  printf("debut %c\n",*debut_point);
  while(debut_point != fin_point){
    *debut_point=' ';
    debut_point++;

  }
  debut_point=strstr(inst,"'(");
  extern_point=debut_point;
  extern_point--;
  while('('!=*extern_point)extern_point--;
  
  fonc_point=indicateur_fin(extern_point);
  
  //  printf("extern_point %c\n",*extern_point);
  
  while(extern_point != debut_point){
    *extern_point=' ';
  extern_point++;
  
  }
  // printf("extern_point %c\n",*extern_point);
  fonc_point--;
  while(')' != *fonc_point)fonc_point--;
  //printf("fonc_point %c\n",*fonc_point);
  *fonc_point=' ';
  //printf("inst :%s\n",inst);

  return inst;


  
  
cons:
  
  // cons 
  // goto zone(cons)
  printf("debut de cons\n");
  debut_point=strstr(inst,"'(");
  extern_point = debut_point;
  extern_point--;
  while('(' != *extern_point){
    //  *extern_point=' ';
    extern_point--;
  }
  *extern_point = *debut_point;
  extern_point++;
  *extern_point = '(';
  extern_point++;
  *extern_point = ' ';
  extern_point++;
  *extern_point = ' ';
  extern_point++;
  *extern_point = ' ';
  extern_point = strrchr(inst,')');
  *extern_point = ' ';
 

  *debut_point=' ';
  debut_point++;
  *debut_point=' ';
  debut_point++;
  // printf("inst :%s\n",inst);
  goto car;
  return inst;
}

jmp_buf ebuf;


void main(){
  /*  int resultat;
  list list ;
  char * inst;
  char * pointeur;
  char recv[100];
  list = (list);
  system("clear");  
  printf("<Interprète en Scheme>\n");
  setjmp(ebuf);
  printf(">");
  gets(recv);
  pointeur=strstr(recv,"'(");
  if(pointeur!=NULL){

    
  inst=instruction_interperteur_v3(recv);


  
   if(NULL==strstr(recv,"'(")){
  list=list_interpreteur_v1(inst);
  affichage(list);}
  else
  printf("%c",*inst);
  longjmp(ebuf,0);
  }
 else
  resultat =calcul_interpreteur_v2(recv);
  printf("%d\n",resultat); 
  longjmp(ebuf,0);*/
  char inst[100]="'(              5  5 8         9 5 7  15 ) ";
  list list = (list);
  // printf("%s\n",instruction_interperteur_v3(inst));
  list=list_interpreteur_v1(inst);
  affichage(list);
  list= cons(9,list);
  list=cdr(list);
  affichage(list);
 list->val
   car(list)
}
