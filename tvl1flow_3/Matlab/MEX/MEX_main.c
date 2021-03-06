/*
 * Copyright (c) 2014, Paul-Darius Sarmadi <paul-darius.sarmadi@telecom-sudparis.eu>
 * Based on "main.c" by Javier Sánchez Pérez <jsanchez@dis.ulpgc.es>
 */
typedef char* char16_t;
#include "mex.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "../../tvl1flow_lib.c"


#define PAR_DEFAULT_OUTFLOW "flow.flo"
#define PAR_DEFAULT_TAU     0.25
#define PAR_DEFAULT_LAMBDA  0.15
#define PAR_DEFAULT_THETA   0.3
#define PAR_DEFAULT_NSCALES 100
#define PAR_DEFAULT_ZFACTOR 0.5
#define PAR_DEFAULT_NWARPS  5
#define PAR_DEFAULT_EPSILON 0.01
#define PAR_DEFAULT_VERBOSE 1

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if (!(nlhs==1))
	{
    	mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output required.");
    }
    if (!(nrhs==2 || nrhs==3))
    {
    	mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two double matrix and one optional structure are required.");
    }

	int i = 1;
	float tau     = PAR_DEFAULT_TAU;
	float lambda  = PAR_DEFAULT_LAMBDA;
	float theta   = PAR_DEFAULT_THETA;
	int   nscales = PAR_DEFAULT_NSCALES;
	float zfactor = PAR_DEFAULT_ZFACTOR;
	int   nwarps  = PAR_DEFAULT_NWARPS;
	float epsilon = PAR_DEFAULT_EPSILON;
	int   verbose = PAR_DEFAULT_VERBOSE;
	if (nrhs==3)
    {
      int tmp=0;
      double* ptr;
      for( tmp=0; tmp<mxGetNumberOfFields(prhs[2]);tmp++)
      {
        if ( strcmp(mxGetFieldNameByNumber(prhs[2],tmp),"tau")==0)
        {
          if (!(mxIsDouble(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0)))))
          {
              mexErrMsgTxt("A double argument was expected.");
          }
          if (mxGetNumberOfElements((mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0))))!=1)
          {
            mexErrMsgTxt("Only one value was expected.");
          }
          ptr=mxGetPr(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],tmp)));
          if (ptr[0]> 0 && ptr[0]< 0.25)
          {
            tau=ptr[0];
          }
          else
          {
              mexErrMsgTxt("The tau value is not acceptable. For more information, type \"help tvl1\"");
          }
        }
          if ( strcmp(mxGetFieldNameByNumber(prhs[2],tmp),"lambda")==0)
          {
              if (!(mxIsDouble(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0)))))
              {
                  mexErrMsgTxt("A double argument was expected.");
              }
              if (mxGetNumberOfElements((mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0))))!=1)
              {
                  mexErrMsgTxt("Only one value was expected.");
              }
              ptr=mxGetPr(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],tmp)));
              if (ptr[0]>0)
              {
                  lambda=ptr[0];
              }
              else
              {
                  mexErrMsgTxt("The lambda value is not acceptable. For more information, type \"help tvl1\"");
              }
          }
          if ( strcmp(mxGetFieldNameByNumber(prhs[2],tmp),"theta")==0)
          {
              if (!(mxIsDouble(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0)))))
              {
                  mexErrMsgTxt("A double argument was expected.");
              }
              if (mxGetNumberOfElements((mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0))))!=1)
              {
                  mexErrMsgTxt("Only one value was expected.");
              }
              ptr=mxGetPr(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],tmp)));
              if (ptr[0]>0)
              {
                  theta=ptr[0];
              }
              else
              {
                  mexErrMsgTxt("The theta value is not acceptable. For more information, type \"help tvl1\"");
              }
          }
          if ( strcmp(mxGetFieldNameByNumber(prhs[2],tmp),"nscales")==0)
          {
              if (!(mxIsDouble(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0)))))
              {
                  mexErrMsgTxt("A double argument was expected.");
              }
              if (mxGetNumberOfElements((mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0))))!=1)
              {
                  mexErrMsgTxt("Only one value was expected.");
              }
              ptr=mxGetPr(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],tmp)));
              if (ptr[0]>0)
              {
                  nscales=ptr[0];
              }
              else
              {
                  mexErrMsgTxt("The nscales value is not acceptable. For more information, type \"help tvl1\"");
              }
          }
          
          if ( strcmp(mxGetFieldNameByNumber(prhs[2],tmp),"zfactor")==0)
          {
              if (!(mxIsDouble(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0)))))
              {
                  mexErrMsgTxt("A double argument was expected.");
              }
              if (mxGetNumberOfElements((mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0))))!=1)
              {
                  mexErrMsgTxt("Only one value was expected.");
              }
              ptr=mxGetPr(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],tmp)));
              if (ptr[0]>0)
              {
                  zfactor=ptr[0];
              }
              else
              {
                  mexErrMsgTxt("The zfactor value is not acceptable. For more information, type \"help tvl1\"");
              }
          }
          
          if ( strcmp(mxGetFieldNameByNumber(prhs[2],tmp),"nwarps")==0)
          {
              if (!(mxIsDouble(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0)))))
              {
                  mexErrMsgTxt("A double argument was expected.");
              }
              if (mxGetNumberOfElements((mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0))))!=1)
              {
                  mexErrMsgTxt("Only one value was expected.");
              }
              ptr=mxGetPr(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],tmp)));
              if (ptr[0]>0)
              {
                  nwarps=ptr[0];
              }
              else
              {
                  mexErrMsgTxt("The nwarps value is not acceptable. For more information, type \"help tvl1\"");
              }
          }
          
          if ( strcmp(mxGetFieldNameByNumber(prhs[2],tmp),"epsilon")==0)
          {
              if (!(mxIsDouble(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0)))))
              {
                  mexErrMsgTxt("A double argument was expected.");
              }
              if (mxGetNumberOfElements((mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],0))))!=1)
              {
                  mexErrMsgTxt("Only one value was expected.");
              }
              ptr=mxGetPr(mxGetField(prhs[2],0,mxGetFieldNameByNumber(prhs[2],tmp)));
              if (ptr[0]>0)
              {
                  epsilon=ptr[0];
              }
              else
              {
                  mexErrMsgTxt("The epsilon value is not acceptable. For more information, type \"help tvl1\"");
              }
          }
          
      }
	}

	if (tau <= 0 || tau > 0.25) {
		tau = PAR_DEFAULT_TAU;
		if (verbose) mexPrintf("warning: "
				"tau changed to %g\n", tau);
	}
	if (lambda <= 0) {
		lambda = PAR_DEFAULT_LAMBDA;
		if (verbose) mexPrintf("warning: "
				"lambda changed to %g\n", lambda);
	}
	if (theta <= 0) {
		theta = PAR_DEFAULT_THETA;
		if (verbose) mexPrintf("warning: "
				"theta changed to %g\n", theta);
	}
	if (nscales <= 0) {
		nscales = PAR_DEFAULT_NSCALES;
		if (verbose) mexPrintf("warning: "
				"nscales changed to %d\n", nscales);
	}
	if (zfactor <= 0 || zfactor >= 1) {
		zfactor = PAR_DEFAULT_ZFACTOR;
		if (verbose) mexPrintf( "warning: "
				"zfactor changed to %g\n", zfactor);
	}
	if (nwarps <= 0) {
		nwarps = PAR_DEFAULT_NWARPS;
		if (verbose) mexPrintf( "warning: "
				"nwarps changed to %d\n", nwarps);
	}
	if (epsilon <= 0) {
		epsilon = PAR_DEFAULT_EPSILON;
		if (verbose) mexPrintf("warning: "
				"epsilon changed to %f\n", epsilon);
	}
    
	int    nx = mxGetN(prhs[0]);
	int    ny = mxGetM(prhs[0]);
	int    nx2 = mxGetN(prhs[1]);
	int    ny2 = mxGetM(prhs[1]);
	float *I0=malloc(nx*ny*sizeof(float));
	int tmpx, tmpy;
   for (tmpx=0; tmpx<nx; tmpx++) 
      for (tmpy=0; tmpy<ny; tmpy++) 
		   I0[tmpx+tmpy*nx] = (float)(mxGetPr(prhs[0]))[tmpy+tmpx*ny];

	float *I1=malloc(nx2*ny2*sizeof(float));
   for (tmpx=0; tmpx<nx2; tmpx++) 
      for (tmpy=0; tmpy<ny2; tmpy++) 
		   I1[tmpx+tmpy*nx] = (float)(mxGetPr(prhs[1]))[tmpy+tmpx*ny];

		if (nx == nx2 && ny == ny2)
	{

		const float N = 1 + log(hypot(nx, ny)/16.0) / log(1/zfactor);
		if (N < nscales)
			nscales = N;
		if (verbose)
		{
			mexPrintf(
				"tau=%f lambda=%f theta=%f nscales=%d "
				"zfactor=%f nwarps=%d epsilon=%g\n",
				tau, lambda, theta, nscales,
				zfactor, nwarps, epsilon);
		}

		float *u = xmalloc(2 * nx * ny * sizeof(*u));
		float *v = u + nx*ny;

		Dual_TVL1_optic_flow_multiscale(
				I0, I1, u, v, nx, ny, tau, lambda, theta,
				nscales, zfactor, nwarps, epsilon, verbose
		);
		mwSize dim = 3;
    	const mwSize dims[3]={ny,nx,2};
    	plhs[0]=mxCreateNumericArray(dim, dims,mxDOUBLE_CLASS,mxREAL);
    	double* pointeur=(double*)mxGetPr(plhs[0]);
      for (tmpy=0; tmpy<ny; tmpy++) 
         for (tmpx=0; tmpx<nx; tmpx++) 
         {
        	   pointeur[tmpy+tmpx*ny + 0    ]=(double)u[tmpx+tmpy*nx];
        	   pointeur[tmpy+tmpx*ny + nx*ny]=(double)v[tmpx+tmpy*nx];
         }
		free(I0);
		free(I1);
		free(u);
	} 
	else
	{
		mexErrMsgTxt("ERROR: input images size mismatch ");
	}
}
