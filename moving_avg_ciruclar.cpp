#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<array>

void dummy_function (long int n);
double mean_array(double *array, int sample_size);
double *sin_function,*sin_window,*time_global;
int main()
{

    int i;
    int n=20000;
    dummy_function(n);
    sin_window=(double*)malloc(n*sizeof(double));

    int sample_size=250; 
    double sum[sample_size],time_window[sample_size];        
    for (i=0;i<sample_size;i++)
    {
        sum[i]=0.0;
        time_window[i]=0.0;
        
    }
    FILE *fp;
    fp=fopen("noise_window.out","w");
    for(i=0;i<n;i++)
    {
        sum[i%sample_size]=sin_function[i];        
        if(i>sample_size)
        {
            sin_window[i]=mean_array(sum,sample_size);
        }
        else
        {
            sin_window[i]=sin_function[i];
        }
        fprintf(fp,"%f\t%f\t%f\n",time_global[i],sin_function[i],sin_window[i]);
    }
    fclose(fp);
   
    
    return 0;
}

void dummy_function (long int n)
{
    srand((unsigned)time(NULL));

    int i;
    sin_function=(double*)malloc(n*sizeof(double));
    time_global=(double*)malloc(n*sizeof(double));
    double dt=1e-3;
    FILE *fp;
    fp=fopen("noise_signal","w");
    for(i=0;i<n;i++)
    {
        time_global[i]=dt*i;
        sin_function[i]=sin(time_global[i]) + sqrt(0.01) * rand();
        fprintf(fp,"%f\t%f\n",time_global[i],sin_function[i]);        
    } 
    fclose(fp);
}

double mean_array(double *array, int sample_size)
{
    
    double local_sum=0.0,answer=0.0;
    for (int k=0;k<sample_size;k++)
    {
        local_sum+=array[k];
    }
    answer=local_sum/sample_size;
    return answer;

}