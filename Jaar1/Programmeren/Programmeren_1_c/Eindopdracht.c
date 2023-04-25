#include "lenaArray.h"                      
#include <stdio.h>
const char *tekens = ".:-=+*#%@";     
const int arraySize = 512;
const int smallArray = 300;
const int subset = 100;
const int grijsVerschil = 32;          
int som = 0;                                
int kleinSom = 0;
int gemiddelde = 0; 
int kleinGemiddelde= 0;                 
int grootLena();
int kleinLena();
void omgekeerdLena();

int grootLena(){
    //de array uitlezenn en voor elke grijswaarde een bijbehorend teken printen
    //ook worden alle grijswaarde uit de array bij elkaar opgetelt   
    for(int rij = 0; rij < arraySize; rij++){              
        for(int kolom = 0; kolom < arraySize; kolom++){    
            int grijswaarde = lena[rij][kolom];         
            som  += lena[rij][kolom];                   
            printf("%c", tekens[grijswaarde/grijsVerschil]);       
        }
        printf("\n");                                   
    }
    gemiddelde = som / (arraySize * arraySize);
    return gemiddelde;
}

int kleinLena(){
    int kleinLena[smallArray][smallArray];
    //de array uitlezenn en voor elke grijswaarde een bijbehorend teken printen
    //ook worden alle grijswaarde uit de array bij elkaar opgetelt
    for(int subRij = 0; subRij < smallArray; subRij++){                                                         
        for(int subkolom = 0; subkolom < smallArray; subkolom++){                                             
            kleinLena[subRij][subkolom] = lena[subset + subRij][subset + subkolom];       
            kleinSom  += kleinLena[subRij][subkolom];                                                               
            int grijswaarde = kleinLena[subRij][subkolom];                                                          
            printf("%c", tekens[grijswaarde/grijsVerschil]);                                                                               
        } 
        printf("\n");                                           
    }
    kleinGemiddelde = kleinSom / (smallArray * smallArray); 
    return kleinGemiddelde;
}

void omgekeerdLena(){
    //de array achterstevoren uitlezenn en voor elke grijswaarde een bijbehorend teken printen
    for(int rij = 0; rij < arraySize; rij++){               
        for(int kolom = 512; kolom > 0; kolom--){      
            int grijswaarde = lena[rij][kolom];         
            printf("%c", tekens[grijswaarde/grijsVerschil]);       
        }
        printf("\n");                                   
    }
}

int main(){
    grootLena();
    kleinLena();
    printf("de gemiddelde grijswaarde is: ");
    printf("%d\n", gemiddelde);                                     
    printf("de gemiddelde grijswaarde van de verkleinde lena is: ");
    printf("%d\n", kleinGemiddelde);
    omgekeerdLena();
    return 0;
}