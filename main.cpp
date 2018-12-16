#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>

double drand() {
return double( (rand() - RAND_MAX)/2 )/ double( RAND_MAX ); }

class simulation {
public:

    simulation();
//  simulation
    ~simulation();

    int* genNeigh(int i);

    
    double* mag();
    double* mag2();
    double* ener();
    double* ener2();

    double dEner(double relStep, int site);

    void init();
    void MCstep(int site, double b);

private:

    int L = 10;        // lat size
    int N = L*L;       // number of sites
    int NN = 4;        // number of nearest neighbors
    int J = 1;		   // coupling
    double amp = 1;    // amplitude of jump, range of [-amp/2,amp/2] radians 
    double **lat = new double*[N];

};

double simulation::dEner(double relStep, int site) {
    double dE = 0;
    double* dNewAngle = new double[1];
    dNewAngle[0] = lat[site][0]+relStep;
    for(int j=0;j<NN;j++) {
        dE += J*cos( lat[site][0] - lat[genNeigh(site)[j]][0] );
        dE -= J*cos( dNewAngle[0] - lat[genNeigh(site)[j]][0] );	
    }
    return dE;
}


double* simulation::mag() {
	double* res = new double[1];
	for(int i=0;i<N;i++) {
		res[0] += (double) lat[i][0];
        res[1] += (double) lat[i][1];
    }
    return res;
}


double* simulation::mag2() {
	double* res = new double[1];
	for(int i=0;i<N;i++) {
	for(int j=0;j<N;j++) {
		//res += (double) lat[i]*lat[j]; 
	}}	
	return res;
}


double* simulation::ener() {
	double* res = new double[1];
	for(int i=0;i<N;i++) {			
		for(int j=0;j<NN;j++) {
		//res += (double) lat[i]*lat[genNeigh(i)[j]]; 
		}
	}
	return res; 
}


double* simulation::ener2() {
	double* res = new double[1];
	for(int i1=0;i1<N;i1++) {
	for(int j1=0;j1<N;j1++) {
		for(int k1=0;k1<NN;k1++) { 
		for(int l1=0;l1<NN;l1++) {	
			//res += (double) lat[i1]*lat[genNeigh(i1)[k1]] * lat[j1]*lat[genNeigh(j1)[l1]];
			}}
		}}
	return res;
}

int* simulation::genNeigh(int i) {
    
   int* Neigh = new int[NN];    
    
        if( (i+1)%L == 0 )  Neigh[0]=i+1-L;
        else          Neigh[0]=i+1;

        if( ((i-1)%L == (L-1)) ||  ((i-1)%L == -1) )  Neigh[1]=i-1+L;
        else          Neigh[1]=i-1;
    
        if( (i+L) >= N)  Neigh[2]=(i+L-N)%N;
        else          Neigh[2]=i+L;

        if( (i-L) < 0)  Neigh[3]=(i-L+N)%N;
        else          Neigh[3]=i-L;
    
        return Neigh; 
}


void simulation::init() {
    for(int i=0;i<N;i++)
        lat[i][0]=2*M_PI*drand();
}

void simulation::MCstep(int site, double beta) {
    int pos = (int) N*drand();
    double deltaE = 0.;
    double w;
    double dStep = amp*(drand()-.5);
    deltaE += dEner(dStep,pos);
    double rd = drand();
    if (deltaE < 0) { w = 1.0 ; }
    else            { w = exp(-beta*deltaE) ; }
    if (rd<w) { lat[pos][0] = lat[pos][0]+dStep ; }			
}

int main(){	// example, can be modified as anyone likes
    return 0;
}
