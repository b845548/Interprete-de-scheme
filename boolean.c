#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <assert.h>
   /*   for(i=0; i< 10 ; i++,detect++)
   fonction[i]=*detect;
   if(NULL!=strstr(fonction,"cons"))goto cons;
   if(NULL!=strstr(fonction,"cdr"))goto cdr;
   if(NULL!=strstr(fonction,"car"))goto car;
   
*/

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

char * profond_indicateur_debut(char * inst){
  int count;
  int max;
  char * debut_point;
  char * max_point;
  debut_point=inst;
  count=0;
  max=0;
  // (1 2 (3) (4) (5 (6) 7) 8)
  // 1    2 1 2 1 2  3 2  1  0
  do{
    if('('==*debut_point)count++;
    if(')'==*debut_point)count--;
    if(count > max){
      max=count;
      max_point=debut_point;
     
	     }debut_point++;
  }while(count);
  //  printf("%c",*max_point);
  return max_point;
}

int boolean_interpreteur(char * inst){
  char * fonc_point;
  char * val_point;
  char str_b[100];
  char str_a[100];
  int a,b,i;
  printf("inst : %s\n",inst);

  fonc_point=profond_indicateur_debut(inst);
  val_point=fonc_point;

  while(!isdigit(*val_point)) val_point++;
  for(i=0; *val_point!=' ';i++,val_point++){
    str_a[i]=*val_point;
  }
  a=atoi(str_a);
  val_point++;
  while(!isdigit(*val_point)) val_point++;
    for(i=0; *val_point!=')';i++,val_point++){
   str_b[i]=*val_point;
  }
  b=atoi(str_b);
  //printf("val %d\n",b);
  //printf("val %c\n",*val_point);
   
  //printf("fonc %c\n",*fonc_point);
 
   if(NULL!=strstr(fonc_point,"<="))
      if(a<=b){printf("#t\n");return 1;}
      else {printf("#f\n");return 0;}
   else if(NULL!=strstr(fonc_point,"<"))
 if(a<b){printf("#t\n");return 1;}
         else {printf("#f\n");return 0;}
   else if(NULL!=strstr(fonc_point,">="))
 if(a>=b){printf("#t\n");return 1;}
         else {printf("#f\n");return 0;}
   else if(NULL!=strstr(fonc_point,">"))
 if(a>b){printf("#t\n");
   return 1;}
 else {printf("#f\n");return 0;}

}


char * if_interpreteur(char * inst){
  char * fonc_point;
  char * inst_point;
  char * fin_point;
  char * extern_point;
  char * debut_point;
  
  printf("%s\n",inst);
  fonc_point=strstr(inst,"if");
  // printf(" %d\n",boolean_interpreteur(instcopy));
  
  inst_point=fonc_point;
  while('('!=*inst_point)inst_point++; 
  //  printf("point %c\n",*inst_point);
  debut_point = indicateur_fin(inst_point);
  // printf("debut %c\n",*debut_point);

  debut_point++;
  if(boolean_interpreteur(inst)) {
    while(1){                       // true
    if('('==*debut_point)goto inst;
    if(isdigit(*debut_point))goto num;
    debut_point++;
  }
  num: 
    fin_point=debut_point;
    fin_point++;
    while(isdigit(*fin_point))fin_point++;
    fonc_point--;
    extern_point=indicateur_fin(fonc_point);
    debut_point--;

    while(debut_point!=fonc_point){
      *debut_point=' ';
      debut_point--;
    }
    *fonc_point=' ';

    while(fin_point!=extern_point){
      *fin_point=' ';
      fin_point++;
    }
    *extern_point=' ';
    return inst;
    
  inst:
    printf(" debut de\n");
    fin_point = indicateur_fin(debut_point);
    printf(" fin %c\n",*fin_point);
    fonc_point--;
    extern_point=indicateur_fin(fonc_point);
    debut_point--;
    while(debut_point!=fonc_point){
      *debut_point=' ';
      debut_point--;
    }
    *fonc_point=' ';
    fin_point++;
    while(fin_point!=extern_point){
      *fin_point=' ';
      fin_point++;
    }
    *extern_point=' ';

	 return inst;
  }

}
/// true num num marche
/// true num list marche
/// true inst inst marche
/// true inst num marche
/// false num num X method ) la fin de parenthese if trouve un nombre avance
/// false inst inst X
/// false num ist marche
/// false inst num X
void main(){
  char inst[100]="(if (> 5 4) (+ 15 16) (+5 12))";
  printf("evaluation : %s\n",if_interpreteur(inst));
  
}
