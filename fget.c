/* fgets example */
#include <stdio.h>
#include <string.h>

char * detecteur_fonction_define(char * inst){
   FILE * pFile;
   char mystring [100];
   int i;
   pFile = fopen ("schemefile.txt","r");
   if (pFile == NULL) perror ("Error opening file");
   else {
     for(i=0; i< 20 ;i++){
     if ( fgets (mystring , 100, pFile) != NULL )
       if(NULL !=strstr(mystring,"fonctionA")){
	 printf("trouvé\n");
	 goto sort;
       }
    
     printf("%s",mystring);

     }
   sort:

     printf("%s",mystring);
     fclose (pFile);
     return mystring;
   }

   int main(){


   }
