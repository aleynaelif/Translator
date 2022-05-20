#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"


char * remove_dot_comma (char *str);
void ceviri(char* input, char* sozluk, int one, int two);

int  main(int argc, char *argv[] )  {  

   char* lang, *input, *sozluk;
   int one = 1, two = 2;
   
   if(argc < 4){  
      printf("No argument passed through command line.\n");
      exit(1);
   }  
   else if(argc == 4){  

      lang = argv[1];
      input = argv[2];
      sozluk = argv[3];
//iki dili çevirmek için de aynı fonksiyon kullanılıyor sadece parametrelerinin yeri farklı
      if(strcmp(lang,"eng") == 0)
         ceviri(input, sozluk, two, one);
      else if(strcmp(lang,"tr") == 0)
         ceviri(input, sozluk, one, two);
   }
   else{
      printf("Too much argument!");
      exit(1);
   } 

   return 0;
}  

char * remove_dot_comma (char *str){
// nokta ve virgülü kaldırmak için yazılan fonksiyon
   char *r, *w;
   for (w = r = str; *r; r++) {
      if (*r != '.' && *r!=',') {
         *w++ = *r;
      }
   }
   *w = '\0';
   return str;
}

void ceviri(char* input, char* sozluk, int one, int two){
//çeviriyi yapan fonskiyon
   IS is_input, is_sozluk;
   Dllist dl_output ,tmp;
   int i,flag=0, ceviri_var = 0, ceviri_yok = 0;
   FILE *fptr;

   fptr = fopen("../B201210387/txt/output.txt","w");
//output dosyasını açıyor

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   is_input = new_inputstruct(input);
   is_sozluk = new_inputstruct(sozluk);
   dl_output = new_dllist();

   if (is_input == NULL){
      perror(input);
      exit(1);
   }
   else if (is_sozluk == NULL){
      perror(sozluk);
      exit(1);
   }

   //inputta alınan her bir kelime için sözlük dosyasını baştan sona tarar
   //karşılığı bulunduysa çevirisi bulunamadıysa input dlle eklenir
   //birden fazla karşılığı olan kelimelerde ilk bulunan çeviri dikkate alınır

   while(get_line(is_input) >= 0) {
      for (i = 0; i < is_input->NF; i++) {
         while(get_line(is_sozluk) >= 0){

            is_input->fields[i] = remove_dot_comma (is_input->fields[i]);

            if(strcmp(is_sozluk->fields[one],is_input->fields[i]) == 0 && flag !=1){
                  dll_append(dl_output, new_jval_s(strdup(is_sozluk->fields[two])));
                  ceviri_var++;
                  flag = 1;
            }
         }
         if(strcmp(is_sozluk->fields[one],is_input->fields[i]) != 0 && flag !=1){
            dll_append(dl_output, new_jval_s(strdup(is_input->fields[i]))); 
            ceviri_yok ++; 
         }
         
         flag = 0;
         fseek(is_sozluk->f, 0, SEEK_SET);
      }
      dll_append(dl_output, new_jval_s(strdup("\n")));
   }
   // elde edilen dll output.txtye bastırılır
   
   dll_traverse(tmp, dl_output) 
   fprintf(fptr,"%s ",tmp->val.s);

      printf("Karsilastirilan kelime sayisi: %d \n", ceviri_var + ceviri_yok);
      printf("Cevirisi basarili kelime sayisi: %d\n", ceviri_var);
      printf("Cevirisi yapilamamis kelime sayisi: %d\n",ceviri_yok);
   

      jettison_inputstruct(is_input);
      jettison_inputstruct(is_sozluk);
      fclose(fptr);
}
