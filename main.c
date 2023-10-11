#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int size;
    float *x;
    float *xp;
    float **a;
    float *b;
    float *delta;
    int flag = 1; //first-check variable



    while(1){
        int flag = 1;
        printf("Enter the amount of equations: ");
        scanf("%d", &size);
        a = (float **)malloc(size * sizeof(float*));
        b = (float*)malloc(size * sizeof(float));
        delta = (float*)malloc(size * sizeof(float));

        while(1){

            if (a == NULL || b == NULL) {
                printf("Memory allocation failed\n");
                return 1;
            }

            for(int i = 0; i < size; i++){
                a[i] = (float*)malloc(size * sizeof(float));
                if (a[i] == NULL){
                    printf("Memory allocation failed\n");
                    return 1;
                }

                for (int j = 0; j < size; j++) {
                    printf("Enter value for the a%d%d: ", i+1, j+1);
                    scanf("%f", &a[i][j]);
                }
                printf("Enter value for the b%d: ", i+1);
                scanf("%f", &b[i]);
                printf("\n");

            }
        //End of creating SOE
        //Initiate checking procedure
            float scheck = 0.0;

            for(int i = 0; i < size; i++){
                scheck = 0.0;
                for (int j = 0; j < size; j++){
                    if(j != i){
                        scheck += a[i][j];
                    }

                }
                if (a[i][i] <= scheck){

                    flag = 0;
                }

            }
            if (flag == 1){
                break;
            }
            else if(flag == 0){
                printf("Could not converge. Please, enter another values.\n");
            }
        }
        //Creating the System of equations

        //STOP NAHUY
        float eps;

        while(1){
            printf("\nPlease, enter the accuracy (0-1): ");
            scanf("%f", &eps);
            if(eps <= 0 || eps > 1){
                printf("Error. Please, enter the accuracy correctly");
            }
            else{break;}
        }

        float max = 2*eps;

        //Creating starting values array
        xp = (float*)malloc(size*sizeof(float));
        x = (float*)malloc(size*sizeof(float));

        for(int i = 0; i < size; i++){
            xp[i] = b[i]/a[i][i];
        }
        //ALGORITM NAHUY IDI
        while(max > eps){
            for(int i = 0; i < size; i++){
                float sum = 0.0;
                for (int j = 0; j < size; j++){
                    if(j!=i){
                        sum+=a[i][j]*xp[j];
                    }
                }

                x[i] = (b[i] - sum)/(a[i][i]);
            }
            for(int i = 0; i < size; i++){
                delta[i] = fabs(x[i] - xp[i]);
            }

            max = delta[0];
            for(int i = 0; i < size; i++){
                if(delta[i] > max){
                    max = delta[i];
                }
            }



            for(int i = 0; i < size; i++){
                xp[i] = x[i];
            }

        }
        for(int i = 0; i < size; i++){
            printf("x%d : %f\n", i+1, xp[i]);
        }

        //Cleaning the memory
        for (int i = 0; i < size; i++) {
            free(a[i]);
        }
        free(a);
        free(b);
        free(xp);
        free(x);
        free(delta);
        printf("\n");

        char answer;
        printf("Enter Y, if you want to continue. To exit, enter N:");
        while(1){
            scanf("%s", &answer);
            if(answer == 'Y'){
                break;
            }
            else if(answer == 'N'){
                flag = 2;
                break;
            }
            else{
                printf("Error. Please enter the answer again. Y/N:");
            }
        }
        if (flag == 2){
            break;
        }



    }
    printf("\nExecuted successfully. Press any key to exit.");



    getch();

    return 0;
}

