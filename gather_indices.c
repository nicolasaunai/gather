

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RNM (double)rand()/((double)RAND_MAX)


int main(void)
{

    int ixy1,ixy2,ixy3,ixy4;
    int ix,iy;
    int nx,ny;
    double w1,w2,w3,w4;
    int npart;
    double dix,diy;
    int ixd,iyd;
    double *x,*y;
    double xm,ym;
    double dx,dy;
    double odx,ody;
    double *dens;
    double *dens2;
    clock_t start,end;
    float sec;
    int repeat;


    repeat = 100;
    npart = 1000000;

    nx = 2002;
    ny = 2002;
    xm = 40.;
    ym = 40.;

    dx = xm/(double)(nx-2);
    dy = ym/(double)(ny-2);
    odx = 1./dx;
    ody = 1./dy;

    x = calloc(npart,sizeof *x);
    y = calloc(npart,sizeof *y);

    dens  = calloc(nx*ny, sizeof *dens);
    dens2 = calloc(nx*ny, sizeof *dens);

    for (int ip=0; ip < npart; ip++)
    {
        x[ip] = RNM*xm;
        y[ip] = RNM*ym;
    }


    start = clock();
    do
    {
        for (int ip=0; ip < npart; ip++)
        {
            ixd = x[ip]*odx + 1;
            iyd = y[ip]*ody + 1;

            ix = (int)ixd;
            iy = (int)iyd;

            dix = ixd - ix;
            diy = iyd - iy;

            w3 = dix*diy;
            w2 = diy-w3;
            w4 = dix-w3;
            w1 = 1 - dix - diy + w3;

            ixy1 = iy + ix*ny;
            ixy2 = ixy1 + 1;
            ixy3 = ixy2 + ny;
            ixy4 = ixy3 - 1;

            dens2[ixy1] += w1;
            dens2[ixy2] += w2;
            dens2[ixy3] += w3;
            dens2[ixy4] += w4;
        }
        repeat = repeat -1;
    }
    while (repeat != 0);
    end = clock();

    sec = (float)(end-start)/CLOCKS_PER_SEC;
    printf("time = %f seconds\n",sec);


    repeat = 100;

    start = clock();
    do
    {
        for (int ip=0; ip < npart; ip++)
        {
            ixd = x[ip]*odx + 1;
            iyd = y[ip]*ody + 1;

            ix = (int)ixd;
            iy = (int)iyd;

            dix = ixd - ix;
            diy = iyd - iy;

            w1 = (1.0-dix)*(1.0-diy);
            w2 = (1.0-dix)*(    diy);
            w3 = (    dix)*(    diy);
            w4 = (    dix)*(1.0-diy);


            ixy1 = iy   + (ix  )*ny;
            ixy2 = iy+1 + (ix  )*ny;
            ixy3 = iy+1 + (ix+1)*ny;
            ixy4 = iy   + (ix+1)*ny;

            dens[ixy1] += w1;
            dens[ixy2] += w2;
            dens[ixy3] += w3;
            dens[ixy4] += w4;
        }

        repeat = repeat-1;
    }
    while(repeat != 0);
    end = clock();

    sec = (float)(end-start)/CLOCKS_PER_SEC;

    printf("time = %f seconds\n",sec);



    free(dens);
    free(dens2);
    free(x);
    free(y);
    return 0;
}




