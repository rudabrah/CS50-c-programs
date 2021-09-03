//This i a C-program that ciphers text using the vigenere methode

#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int shift(char c);

 
int main(int argc, string argv[])
{

        if(argc != 2) {
    
        printf("Usage: ./vigenere keyboard\n");
        return 1;
     }
   

    int lengde = strlen(argv[1]);
    int key[lengde];
  
  for(int i = 0; i < lengde; i++){
      
      if (isalpha(argv[1][i])){
          //printf("Success");
          key[i] = (int) argv[1][i] %65 %32;
          
           // printf("%i\n", key[i]);
      
          
      }
    else{
         printf("Usage: ./vigenere keyboard\n");
         return 1;
      }
  }
    
      
    
    //string inputarg = argv[1];
      //printf("%s", inputarg);
  
         string s = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int ii = 0, n = strlen(s), x = 0; ii < n; ii++)
    {
        x = x % lengde;
        if (isupper(s[ii]))
        {
            if ((s[ii] + key[x]) >90){
                 printf("%c", (s[ii] + key[x])-26);
                x++;
            }
            else {
                printf("%c", s[ii] + key[x]);
                x++;
            }
            
        }
        else if (islower(s[ii])){
                       if ((s[ii] + key[x]) >122){
                 printf("%c", (s[ii] + key[x])-26);
                           x++;
            }
            else {
                printf("%c", s[ii] + key[x]);
                x++;
            }
        }
        else
        {
            printf("%c", s[ii]);
        }
        
    }
    printf("\n");
     
     
   
}
