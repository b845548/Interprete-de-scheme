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
    if(i >= 1) res -= atoi(strVal);
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

char * car_interpreteur(char * inst){
  char * debut_point;
  char * fin_point;
  char * extern_point;
  char * fonc_point;
 
  fonc_point = strstr(inst, "'(");
  debut_point = fonc_point;
  debut_point++;
  fin_point = indicateur_fin(debut_point);
  fin_point--;
  while('(' != *fonc_point)fonc_point--;
  extern_point=indicateur_fin(fonc_point);
  extern_point--;

  debut_point++;
  debut_point++; 
  //  while(!(isdigit(*debut_point) && *debut_point!=' ')){
  while(1){
    if('('==*debut_point)goto list;
    if(isdigit(*debut_point))goto valeur;
    debut_point++;
  }
  
 valeur:
   while(fonc_point != debut_point){
    *fonc_point = ' ';
     fonc_point++;
  }
  fin_point=debut_point;
  
  while(isdigit(*fin_point))fin_point++;
  
  while(extern_point != fin_point){
    fin_point++;
    *fin_point = ' ';
  }

  return inst;
   
 list:
  fin_point=indicateur_fin(debut_point);
  fin_point--;
  *debut_point=' ';
  
  while(extern_point != fin_point){
    fin_point++;
    *fin_point = ' ';
  }
  
  debut_point=strstr(inst,"'(");
  
 while(fonc_point != debut_point){
    *fonc_point = ' ';
     fonc_point++;
  }  
  return inst;  
}

char * cdr_interpreteur(char * inst){
  char * debut_point;
  char * fin_point;
  char * extern_point;
  char * fonc_point;
 
  fonc_point = strstr(inst, "'(");
  debut_point = fonc_point;
  debut_point++;
  fin_point = indicateur_fin(debut_point);
  fin_point--;
  while('(' != *fonc_point)fonc_point--;
  extern_point=indicateur_fin(fonc_point);
  extern_point--;

  debut_point++;
  debut_point++;
  //  while(!(isdigit(*debut_point) && *debut_point!=' ')){
  while(1){
    if('('==*debut_point)goto list;
    if(isdigit(*debut_point))goto valeur;
    debut_point++;
  }
  list:

  fin_point=indicateur_fin(debut_point);
  
  while(debut_point!=fin_point){
    *debut_point=' ';
    debut_point++;
  }
  *extern_point=' ';

  debut_point=strstr(inst,"'(");
  while(debut_point!=fonc_point){
    *fonc_point=' ';
    fonc_point++;
  }
 valeur:


  fin_point=debut_point;
  while(isdigit(*fin_point))fin_point++;

  while(debut_point != fin_point){
    fin_point--;
    *fin_point=' ';
  }
  *extern_point=' ';
  debut_point=strstr(inst,"'(");
  while(debut_point!=fonc_point){
    *fonc_point=' ';
    fonc_point++;
  }
 
  
    return inst;
  }

char * cons_interpreteur(char * inst){
  char * debut_point;
  char * fin_point;
  char * extern_point;
  char * fonc_point;
  fonc_point = strstr(inst, "'(");
  debut_point = fonc_point;
  while('(' != *fonc_point)fonc_point--;
  extern_point=indicateur_fin(fonc_point);
  extern_point--;
  *fonc_point=*debut_point;
  fonc_point++;
  *fonc_point='(';
  fonc_point++;
  while(!isdigit(*fonc_point)){
    *fonc_point=' ';
    fonc_point++;
  }
  *debut_point=' ';
  debut_point++;
  *debut_point=' ';  
  debut_point++;
  return inst;
}



char * liste_interpreteur(char * inst){
  char fonc[100];
  char * fonc_point;
  char * debut_point;
  int i=0;
  fonc_point=strstr(inst,"'(");  
  debut_point=fonc_point;
  debut_point--;
  while(*fonc_point!='(')fonc_point--;
  //  printf("fon %c\n",*fonc_point);
  while(debut_point != fonc_point){
    fonc[i]=*fonc_point;
    i++;
    fonc_point++;   }
  if(NULL!=strstr(fonc,"cons"))
    cons_interpreteur(inst);
  if(NULL!=strstr(fonc,"car"))
    car_interpreteur(inst);
  if(NULL!=strstr(fonc,"cdr"))
    cdr_interpreteur(inst);
    
  if(NULL!=strstr(fonc,"caar")){
    car_interpreteur(inst);
    car_interpreteur(inst);}
  if(NULL!=strstr(fonc,"caaar")){
    car_interpreteur(inst);
    car_interpreteur(inst);
    car_interpreteur(inst);}
  if(NULL!=strstr(fonc,"cadr")){
    cdr_interpreteur(inst);
    car_interpreteur(inst);}
  if(NULL!=strstr(fonc,"caddr")){
   cdr_interpreteur(inst);
   cdr_interpreteur(inst);
   car_interpreteur(inst);}
  if(NULL!=strstr(fonc,"cddr")){
   cdr_interpreteur(inst);
   cdr_interpreteur(inst);}
  if(NULL!=strstr(fonc,"cdddr")){
   cdr_interpreteur(inst);
   cdr_interpreteur(inst);
   cdr_interpreteur(inst);}
		     
  return inst;
}

int boolean_interpreteur(char * inst){
  char * fonc_point;
  char * val_point;
  char str_b[100];
  char str_a[100];
  int a,b,i;
  
  //fonc_point=profond_indicateur_debut(inst);
  if(NULL!=strstr(inst," = "))fonc_point=strstr(inst," = ");
  if(NULL!=strstr(inst,"(="))fonc_point=strstr(inst,"(=");
  if(NULL!=strstr(inst,">="))fonc_point=strstr(inst,">=");
  if(NULL!=strstr(inst,"<="))fonc_point=strstr(inst,"<=");
  if(NULL!=strstr(inst,"< "))fonc_point=strstr(inst,"< ");
  if(NULL!=strstr(inst,"> "))fonc_point=strstr(inst,"> ");
  
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
  //  printf("val %d\n",b);
  //printf("val %c\n",*val_point);   
  //printf("fonc %c\n",*fonc_point);
  /* if(NULL!=strstr(fonc_point," = ")||NULL!=strstr(fonc_point,"(= ")){ */
  /*   // printf("#t\n"); */
  /*   return 1;} */
  /* else { */
  /*   //printf("#f\n"); */
  /*   return 0;} */

  if(NULL!=strstr(fonc_point,"<="))
      if(a<=b){
	//printf("#t\n");
	return 1;}
      else {
	//printf("#f\n");
	return 0;}
   else if(NULL!=strstr(fonc_point,"<"))
 if(a<b){
   //printf("#t\n");
   return 1;}
         else {
	   //printf("#f\n");
	   return 0;}
   else if(NULL!=strstr(fonc_point,">="))
 if(a>=b){
   //printf("#t\n");
   return 1;}
         else {
	   //printf("#f\n");
	   return 0;}
   else if(NULL!=strstr(fonc_point,">"))
 if(a>b){
   return 1;}
 else {
   //printf("#f\n");
   return 0;}

}


char * indicateur_debut(char *fin_point){
  char * debut_point=fin_point;
  int count;
  count=0;
  do{
    if(')'==*debut_point)count++;
    if('('==*debut_point)count--;
    debut_point--;
  }while(count);
  debut_point++;
  return debut_point;
}


char * if_interpreteur(char * inst){
  char * list_point;
  char * fonc_point;
  char * inst_point;
  char * fin_point;
  char * extern_point;
  char * debut_point;
  
  if(boolean_interpreteur(inst)) {
  fonc_point=strstr(inst,"if");
 debut_point=fonc_point;
  while('('!=*fonc_point)fonc_point--;
  extern_point=indicateur_fin(fonc_point);
  extern_point--;

 while('('!=*debut_point)debut_point++;
 fin_point=indicateur_fin(debut_point);
 debut_point=fin_point;
 while(1){       
   if('('==*debut_point)goto instt;
   if(isdigit(*debut_point))goto numt;
   debut_point++;  
  }

  
  numt:

 //while(')'!=*fin_point)fin_point++;
   
    while(isdigit(*fin_point))fin_point++;

    extern_point=indicateur_fin(fonc_point);
  
    while(debut_point!=fonc_point){
      debut_point--;
    *debut_point=' ';
    }
  
    while(fin_point!=extern_point){
      fin_point++;
      *fin_point=' ';
    }
     return inst;
    
  instt:
    debut_point=strstr(inst,"if");
    while('('!=*debut_point)debut_point++;

    fin_point=indicateur_fin(debut_point);
    fin_point--;

    while('('==*fin_point)fin_point--;
    debut_point=fin_point;
    fin_point=indicateur_fin(debut_point);
       fin_point--;
    
    debut_point=indicateur_fin(fin_point);
    debut_point--;
    list_point=fin_point;
    fin_point--;
    while(fin_point!=fonc_point){
      fin_point--;
      *fin_point=' ';
    }
    while(debut_point!=extern_point){
      debut_point++;
      *debut_point=' ';
  }
    list_point--;
  if(NULL==strstr(inst,"'("))*list_point=' ';// si ce n'est pas une liste
    
    return inst;


  }
  else

  fonc_point=strstr(inst,"if");
  while('('!=*fonc_point)fonc_point--;
  extern_point=indicateur_fin(fonc_point);
  extern_point--;
  //  printf("fonc_point %c\n",*fonc_point);
  //printf("extern_point %c\n",*extern_point);
  fin_point=extern_point;
  fin_point--;

  while(1){                      // false
    if(')'==*fin_point)goto instf;
    if(isdigit(*fin_point))goto numf;
    fin_point--;
  }
 numf: 
  
  debut_point=fin_point;
  while(extern_point != fin_point){
    fin_point++;
    *fin_point=' ';
  }

  while(isdigit(*debut_point))debut_point--;
  while(debut_point!=fonc_point){
      debut_point--;
     *debut_point=' ';
   }   

    return inst;
   
 instf:
 
  debut_point=indicateur_debut(fin_point);
  //  printf("debut_point %c\n",*debut_point);
  // printf("fin_point %c\n",*fin_point);

  while(extern_point != fin_point){
    fin_point++;
    *fin_point=' ';
  }
  debut_point--;// list point
  list_point=debut_point;
  while(debut_point!=fonc_point){
      debut_point--;
     *debut_point=' ';
   }
  if(NULL==strstr(inst,"'("))*list_point=' ';// si ce n'est pas une liste

  return inst;
    
}


int fonction_detecteur(char * inst){
  char * debut_point;
  debut_point=profond_indicateur_debut(inst);
  //printf("0"); 
  if(strstr(inst,"(")==NULL && strstr(inst,"#")!=NULL && strstr(inst,"'(")==NULL && strstr(inst,")")==NULL && strstr(inst,"car")==NULL && strstr(inst,"cdr")==NULL &&NULL==strstr(inst,"cddr") &&NULL==strstr(inst,"cdddr")&& NULL==strstr(inst,"caddr")&&NULL==strstr(inst,"cadr")&& NULL==strstr(inst,"caaar")&&  NULL==strstr(inst,"caar")&& strstr(inst,"cons")==NULL && strstr(inst,"+")==NULL && strstr(inst,"-")==NULL && strstr(inst,"*")==NULL && strstr(inst,"/")==NULL && strstr(inst,"if")==NULL && strstr(inst,"<")==NULL && strstr(inst,">")==NULL && strstr(inst,"=")==NULL)return 0;
  // caractere #f or #t  
  printf("1");
  if(strstr(inst,"(")!=NULL && strstr(inst,"'(")==NULL && strstr(inst,")")!=NULL && strstr(inst,"car")==NULL && strstr(inst,"cdr")==NULL && strstr(inst,"cons")==NULL &&NULL==strstr(inst,"cddr") &&NULL==strstr(inst,"cdddr")&& NULL==strstr(inst,"caddr")&& NULL==strstr(inst,"cadr")&& NULL==strstr(inst,"caaar")&&  NULL==strstr(inst,"caar")&& strstr(inst,"+")==NULL && strstr(inst,"-")==NULL && strstr(inst,"*")==NULL && strstr(inst,"/")==NULL && strstr(inst,"if")==NULL && strstr(inst,"#")==NULL && ((strstr(inst,"<")!=NULL || strstr(inst,">")!=NULL || strstr(inst,"=")!=NULL)) )return 1;
  // calcul boolean
   printf("2");
  if(strstr(inst,"(")==NULL && strstr(inst,"'(")==NULL && strstr(inst,")")==NULL && strstr(inst,"car")==NULL && strstr(inst,"cdr")==NULL && strstr(inst,"cons")==NULL &&NULL==strstr(inst,"cddr") &&NULL==strstr(inst,"cdddr")&& NULL==strstr(inst,"caddr")&&NULL==strstr(inst,"cadr")&& NULL==strstr(inst,"caaar")&& NULL==strstr(inst,"caar")&& strstr(inst,"+")==NULL && strstr(inst,"-")==NULL && strstr(inst,"*")==NULL && strstr(inst,"/")==NULL && strstr(inst,"if")==NULL && strstr(inst,"#")==NULL && strstr(inst,"<")==NULL && strstr(inst,">")==NULL && strstr(inst,"=")==NULL )return 2;// une val existe 
  printf("3");
  if(strstr(inst,"'(")!=NULL &&NULL==strstr(inst,"cddr") &&NULL==strstr(inst,"cdddr")&& NULL==strstr(inst,"caddr")&&NULL==strstr(inst,"cadr")&& NULL==strstr(inst,"caaar")&&  NULL==strstr(inst,"caar") && strstr(inst,"car")==NULL && strstr(inst,"cdr")==NULL&& strstr(inst,"cons")==NULL && strstr(inst,"if")==NULL && strstr(inst,"<")==NULL && strstr(inst,">")==NULL && strstr(inst,"=")==NULL )return 3;//"'(1 2 3 4 5 6 7 8 9)"= liste
   printf("4");

  if(strstr(inst,"(")!=NULL && strstr(inst,"'(")==NULL && strstr(inst,")")!=NULL && strstr(inst,"car")==NULL && strstr(inst,"cdr")==NULL && strstr(inst,"cons")==NULL &&NULL==strstr(inst,"cddr") &&NULL==strstr(inst,"cdddr")&& NULL==strstr(inst,"caddr")&&NULL==strstr(inst,"cadr")&& NULL==strstr(inst,"caaar")&&  NULL==strstr(inst,"caar")&& (strstr(inst,"+")!=NULL || strstr(inst,"-")!=NULL || strstr(inst,"*")!=NULL || strstr(inst,"/")!=NULL ) && strstr(inst,"if")==NULL && strstr(inst,"#")==NULL && strstr(inst,"<")==NULL && strstr(inst,">")==NULL && strstr(inst,"=")==NULL )return 4;
   printf("5");
 
  if(strstr(inst,"(")!=NULL && strstr(inst,"'(")!=NULL && strstr(inst,")")!=NULL && (strstr(inst,"car")!=NULL || strstr(inst,"cdr")!=NULL || strstr(inst,"cons")!=NULL
										     || NULL!=strstr(inst,"cddr") || NULL!=strstr(inst,"cdddr") || NULL!=strstr(inst,"caddr") || NULL!=strstr(inst,"cadr") || NULL!=strstr(inst,"caaar") ||  NULL!=strstr(inst,"caar")) && strstr(inst,"+")==NULL && strstr(inst,"-")==NULL && strstr(inst,"*")==NULL && strstr(inst,"/")==NULL && strstr(inst,"if")==NULL && strstr(inst,"#")==NULL && strstr(inst,"<")==NULL && strstr(inst,">")==NULL && strstr(inst,"=")==NULL )return 5;// list
  printf("6");
  
if(strstr(inst,"(")!=NULL && strstr(inst,")")!=NULL && strstr(inst,"if")!=NULL)return 6;// if
// printf("7");
   
 printf(" Mauvaise syntaxe!\n");
 return -1; // le cas de mauvais syntaxe
}

void affichage_boolean(char *inst){
  if(strstr(inst,"#t")!=NULL)printf("#t\n");  
  else printf("#f\n");
}
void affichage_boulean_calcul(char *inst){
  if(1==boolean_interpreteur(inst))printf("#t\n");
  else printf("#f\n");
}
void affichage_valeur(char *inst){
  printf("%d\n",atoi(inst));
}

void affichage_liste(char *inst){
  char * debut_point;
  char * suiv_point;
  char * val;
  int arg,i;
  arg=count_arg(inst);
  //  printf(" arg = %d\n",arg);
  debut_point=strtok(inst," ");
   printf("%s ",debut_point);
  for(;debut_point !=NULL;){

     if('('==*debut_point){
	printf("%s",debut_point);
      }
      if(')'==*debut_point){
	printf("%s",debut_point);
      }
      if(isdigit(*debut_point)){
	printf("%s ",debut_point);
      }     
 debut_point=strtok(NULL," ");
  }
  printf("\n");
}

void affichage_calcul(char * inst){
  printf("%d\n",calcul_interpreteur_v2(inst));
}



void instruction_traiteur(char *inst){
 Exec:
  switch(fonction_detecteur(inst)){
    case 0://affichage boolean caractere       
      affichage_boolean(inst);
      return; break;
    case 1://instruction simple boolean
      affichage_boulean_calcul(inst);
      return; break;
    case 2://affichage val    
      affichage_valeur(inst);
      return; break;
    case 3://affichage d'une liste
      affichage_liste(inst);
      return; break;
    case 4://calcul
      affichage_calcul(inst);
	return; break;
    case 5: //list_car,cons,cdr       
      liste_interpreteur(inst);
      goto Exec;
      break;
    case 6: //if
      if_interpreteur(inst);
      goto Exec;
      break;
  default://fonction inconnu
    break;
  }
}

jmp_buf ebuf;

void main(){
   char inst0[100]="     #f            ";
  char inst1[100]="     (< 0 3)       ";
  char inst2[100]="       4           ";
  char inst3[100]="          '(1   2  ( 3 )   4 ( (     5 ) 6 )     7   8 9)";
  char inst4[100]="(+ 15 (+ 15 16) (+5 12))";
  char inst5[100]="(car (cdr (cdr '( 1548 2 5 48))))";
  char inst6[100]="(if (= 5 4) 5 (+ 5 (+ 5454 5448 54   )  ))";
  
  char recv[100];
  system("clear");  
  printf("<Interprète en Scheme>\n");
  setjmp(ebuf);
  printf(">");
  gets(recv);
  instruction_traiteur(recv);
  longjmp(ebuf,0);
  
    
  //   instruction_traiteur(inst5);
 
}
