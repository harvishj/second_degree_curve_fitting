//
//  main.c
//  Projection
//
//  Created by Harvish Jariwala on 04/11/19.
//  Copyright © 2019 Harvish Jariwala. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void vector_print_off (int, double *);
void printMat(int rs,int cs,double** mat);
void matrix_x_vector(int n, double y[], double **A, double *atb);
void matrix_x_vector_pointer(int n, double *y, double A[n][n], double *atb);

int main(int argc, const char * argv[]){
    
    double  **a, **at, **ata, *result;
    int rows,cols;
    
    
    
    double y[19][1], x[19];

    y[0][0] = 68; x[0] = 160;
    y[1][0] = 78; x[1] = 155;
    y[2][0] = 56; x[2] = 143;
    y[3][0] = 70; x[3] = 162;
    y[4][0] = 72; x[4] = 170;
    y[5][0] = 78; x[5] = 175;
    y[6][0] = 68; x[6] = 167;
    y[7][0] = 54; x[7] = 163;
    y[8][0] = 43; x[8] = 156;
    y[9][0] = 71; x[9] = 172;
    y[10][0] = 65; x[10] = 180;
    y[11][0] = 59; x[11] = 159;
    y[12][0] = 63; x[12] = 169;
    y[13][0] = 62; x[13] = 157;
    y[14][0] = 90; x[14] = 161;
    y[15][0] = 45; x[15] = 171;
    y[16][0] = 62; x[16] = 181;
    y[17][0] = 57; x[17] = 177;
    y[18][0] = 80; x[18] = 140;
    
    

    
    printf("\n==================================== Welcome to Matrix =======================================\n\n");
    
    
    rows = 19;
    cols = 3;
    
    double atb[3][1];
    
    
    a = (double**)calloc(rows,sizeof(double));
    for(int i=0;i<rows;i++){
        a[i]= (double*)calloc(cols,sizeof(double));
    }
    
    
    at = (double**)calloc(cols,sizeof(double));
    for(int i=0;i<cols;i++){
        at[i]= (double*)calloc(rows,sizeof(double));
    }
    
    
    ata = (double**)calloc(3,sizeof(double));
    for(int i=0;i<3;i++){
        ata[i]= (double*)calloc(3,sizeof(double));
    }
    
    //atb = (double*)calloc(3,sizeof(double));
    
    result = (double*)calloc(3,sizeof(double));
    
    //Assigning value to A
    for(int i=0; i<19; i++){
        a[i][2] = x[i]*x[i];
        a[i][1] = x[i];
        a[i][0] = 1;
    }
    
    //Assigning value to AT
    for (int c = 0; c < rows; c++){
         for(int d = 0 ; d < cols ; d++){
             at[d][c] = a[c][d];
       }
    }
    
    
    //Multiplying At and A
    for(int i=0; i<cols; i++){
        for(int j=0; j<cols; j++){
            ata[i][j] = 0;
            for(int k=0; k<rows; k++){
                ata[i][j]+=at[i][k]*a[k][j];
            }
        }
    }
    
    
    printf("\nMatrix A :\n");
    printMat(19, 3, a);
    
    
    
    
    printf("\nMatrix AtA\n");
    printMat(3, 3, ata);
    
    double sum=0;
    
    //Multiplying AT and b
    for(int i=0; i<3; i++){
        for(int j=0; j<1; j++){
            for(int k=0; k<rows; k++){
                sum+=at[i][k]*y[k][j];
            }
            atb[i][j] = sum;
            sum=0;
        }
    }
    
    
    printf("\nATb : \n");
    for(int i=0;i<3;i++){
        printf("%lf \n",atb[i][0]);
    }
    
    for(int i=0;i<3;i++){
        ata[i][3] = atb[i][0];
    }
    
    printf("\nMatrix AtA\n\n");
    printMat(3, 3, ata);
    
    double inverse[3][3], determinant=0;
    
    for(int i=0;i<3;i++){
         determinant = determinant + (ata[0][i]*(ata[1][(i+1)%3]*ata[2][(i+2)%3] - ata[1][(i+2)%3]*ata[2][(i+1)%3]));
    }
    
    for(int i=0;i<3;i++){
       for(int j=0;j<3;j++)
           inverse[i][j] = ((ata[(i+1)%3][(j+1)%3] * ata[(i+2)%3][(j+2)%3]) - (ata[(i+1)%3][(j+2)%3]*ata[(i+2)%3][(j+1)%3]))/ determinant;
        printf("\n");
    }
    
    printf("The AT A Inverse is : \n");
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%lf ", inverse[i][j]);
        }
        printf("\n");
    }
    
    sum=0;
    //Multiplying (ATA inverse) and (ATb)
    for(int i=0; i<3; i++){
        for(int j=0; j<1; j++){
            for(int k=0; k<3; k++){
                sum+=inverse[i][k]*atb[k][j];
            }
            result[i] = sum;
            sum=0;
        }
    }
    
    
    printf("\n\nThe final solution is : \n\n");
    for(int i=0;i<3;i++){
        printf("%lf \n", result[i]);
    }
    
    
    FILE *fp;
    
    fp = fopen("gnuplot.txt", "w");
    
    fprintf(fp, "# x \t f(x) \n");
    for(int i=130;i<190;i++){
        fprintf(fp, "%d \t %lf \n", i, (result[2]*i*i + result[1]*i + result[0]));
    }
    
    fclose(fp);
    
    fp = fopen("datapoints.txt", "w");
    
    fprintf(fp, "# x \t f(x) \n");
    for(int i=0;i<19;i++){
        fprintf(fp, "%lf \t %lf \n", x[i], y[i][0]);
    }

    system("clear");
    
    
    
    
    fclose(fp);
}



void matrix_x_vector_pointer(int n, double *y, double A[n][n], double *atb){
    
    for (int i=0; i<n; i++){
      for (int j=0; j<n; j++){
        atb[i] += A[j][i] * y[i];
      }
    }
}




void matrix_x_vector(int n, double y[n], double **A, double *atb){
    
    for (int i=0; i<n; i++){
      for (int j=0; j<n; j++){
        atb[i] += A[j][i] * y[i];
      }
    }
}

void vector_print_off (int n, double *a){
    
    for(int i=0;i<n;i++){
        
        printf("%lf \n", a[i]);
        
    }
    
}

void printMat(int rs,int cs,double** mat){
    printf("\n");
    for(int i=0;i<rs;i++){
        for(int j=0;j<cs;j++){
            printf("%.2lf ",mat[i][j]);
        }
        printf("\n");
    }
}
