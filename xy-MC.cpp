#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>
	
double drand() {
    return double( rand() )/ double( RAND_MAX ); }

int L = 10;     // lattice size
int N = L*L;    // number of sites
int NN = 4;     // number of nearest neighbors
int J = 1;		// coupling
double dAmp = 1;// amplitude of jump
double *lattice = new double[N];
int **Neigh = new int*[N];

void genNeigh(int **Neigh, int N, int L) {
    for(int i=0;i<N;i++) {
        if( (i+1) % L == 0 )  Neigh[i][0]=i-L+1;
        else          Neigh[i][0]=i+1;

        if( (i-1) < 0)  Neigh[i][1]=i-1+L;
        else          Neigh[i][1]=i-1;

        if( (i+L) >= N)  Neigh[i][2]=i+L-N;
        else          Neigh[i][2]=i+L;

        if( (i-L) < 0)  Neigh[i][3]=i-L+N;
        else          Neigh[i][3]=i-L;
}}

		
double dEnergy(double dRandStep ,int iRandSite) {
    double dE = 0;
    double dNewAngle = lattice[iRandSite]+dRandStep;
    double J = 1;
    for(int j=0;j<NN;j++){	dE += J*cos( (double) lattice[iRandSite] - (double) lattice[Neigh[iRandSite][j]] );
							dE -= J*cos( dNewAngle - (double) lattice[Neigh[iRandSite][j]] );	}
	return dE;
}

void neighInit(){
	for(int i=0;i<N;i++) {
		Neigh[i] = new int[NN]; }
	genNeigh(Neigh,N,L);
}

void setStartPos(){
	for(int i=0;i<N;i++)
	lattice[i]=2*M_PI*drand();
}

void step(double beta) {

// radians check mod 2pi
for(int i=0;i<N;i++)
	if( lattice[i] > 2*M_PI || lattice[i] < 0 ) {
		if( lattice[i] > 2*M_PI )
			lattice[i]=lattice[i]-2*M_PI;
		if( lattice[i] < 0 )
			lattice[i]=lattice[i]+2*M_PI;
	}
	
	int pos = (int) N*drand();
        double deltaE = 0.;
 	    double w;
		double dStep = dAmp*(drand()-.5);
        deltaE += dEnergy(dStep,pos);
	    double rd = drand();
	    if (deltaE < 0) { w = 1.0 ; }
	    else            { w = exp(-beta*deltaE) ; }
      	if (rd<w) { lattice[pos] = lattice[pos]+dStep ; }			
}


int main(){
	
	neighInit();
	setStartPos();

    for(int j=0;j<NN;j++){  std::cout<<Neigh[0][j]<<" "; }
    for(int j=0;j<NN;j++){  std::cout<<Neigh[1][j]<<" "; }
	
		//for(int i=0;i<10000;i++)
		//step(1.0);

    return 0;
}
