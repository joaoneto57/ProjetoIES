#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int senha, prioridade=100, normal=100, i, Total=0, Totalprioridade=100, Totalnormal=100;
    time_t now;
    struct tm *local;
    
    time(&now);
    local = localtime(&now);
    
    
    // Gerador de senha
    
    
    do{
    printf("Para gerar a senha digite:  1- Prioridade  2- Normal  0- Finalizar\n");
    scanf("%d", &senha);
    
    if(senha==1){
        printf("Senha: P%d\n", prioridade);
        printf("Data atual: %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        printf("Hora atual: %02d:%02d\n\n", local->tm_hour, local->tm_min);
        prioridade++;
        Totalprioridade++;
        Total++;
    }
    
    if(senha==2){
        printf("Senha: N%d\n", normal);
        printf("Data atual: %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        printf("Hora atual: %02d:%02d\n\n", local->tm_hour, local->tm_min);
        normal++;
        Totalnormal++;
        Total++;
    }
    
    if(senha==0){
        break;
    }
    }while(senha!='0');
    
    
    
    // Chamada da senha
    
    
    
    prioridade=normal=100;
    
    for(i=0; i<Total; i++) {
        
        for(i=0; i<2; i++){
            if(Totalprioridade>=prioridade){
            printf("\nP%d\n", prioridade);
            prioridade++;
            }
            else{
                
            }
        }
        
        if(Totalnormal>=normal) {
        printf("\nN%d\n", normal);
        normal++;
        }
        else{
            
        }
        
    }

    return 0;
}
