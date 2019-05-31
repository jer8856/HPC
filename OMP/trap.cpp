//trapezoide method integration using openmp
#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;
double wtime;

int main(int argc, char **argv)
{
    wtime = omp_get_wtime ( );   
    int a = 0;
    int b = 1000;
    long int n = 99999999;

    double dx = (double)(b-a)/n;
    double approx = (sin(a)+sin(b))/2.0;
    double x_i = 0.0;
    int i;

    #pragma omp parallel for private(x_i) reduction(+:approx)  num_threads(4)
    for(i=1; i<n; i++)
    {
        x_i = a + i*dx;
        approx += sin(x_i);
    }
    
    wtime = omp_get_wtime ( ) - wtime;
    cout << "Elapsed cpu time for main computation: " <<wtime << " seconds.\n";
    cout<< "Result: "<< dx*approx<<endl;
    
    return 0;
    
}
