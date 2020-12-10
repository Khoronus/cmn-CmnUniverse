///	@file FFT.hpp
///	Describe specific classes and functions for the FFT transformation
///	@brief Classes and functions for FFT


#ifndef CMNMATH_NUMERICSYSTEM_FFT_HPP__
#define CMNMATH_NUMERICSYSTEM_FFT_HPP__

#include <cmath>
#include <complex>

namespace CmnMath
{
namespace numericsystem
{


/** @brief Class to perform the FFT transformation.

    Class to perform the FFT transformation.
*/
class EstimateFFT
{
public:

	static const CMN_32S MAXID = 200;

private:
	static CMN_32S log2(CMN_32S N){         //funzione per calcolare il logaritmo in base 2 di un intero
			CMN_32S k=N,i=0;
			 
			while(k){
					k>>=1;
					i++;
			}
			return i-1;
	}                           
			 
	static CMN_32S check(CMN_32S n){       //usato per controllare se il numero di componenti del vettore di input è una potenza di 2
			return n > 0 && (n & (n-1)) == 0;
	}
			 
	static CMN_32S reverse(CMN_32S N,CMN_32S n){ //calcola il reverse number di ogni intero n rispetto al numero massimo N
			CMN_32S j,p=0;
				for(j=1;j<=log2(N);j++){
					if(n&(1<<(log2(N)-j)))
									p|=1<<(j-1);
									}
				return p;
	}
			 
	static void ordina(std::complex<CMN_64F> *f1, CMN_32S N){ //dispone gli elementi del vettore ordinandoli per reverse order
		std::complex<CMN_64F> f2[MAXID];
			for(CMN_32S i=0;i<N;i++)
					f2[i]=f1[reverse(N,i)];
			for(CMN_32S j=0;j<N;j++)
					f1[j]=f2[j];
	}
			 
	static void transform(std::complex<CMN_64F> *f, const CMN_32S N){ //calcola il vettore trasformato
			ordina(f,N);  //dapprima lo ordina col reverse order
			std::complex<CMN_64F> *W = new std::complex<CMN_64F>[N / 2]; //vettore degli zeri dell'unità 
			W[1]=std::polar(1.,-2.*3.1415/N);
			W[0]=1;
			for(CMN_32S i=2;i<N/2;i++)
					W[i]=pow(W[1],i);
			CMN_32S n=1;
			CMN_32S a=N/2;
			for(CMN_32S j=0;j<log2(N);j++){
					for(CMN_32S i=0;i<N;i++){
							if(!(i&n)){ 
								/*ad ogni step di raddoppiamento di n, vengono utilizzati gli indici */ 
								/*'i' presi alternativamente a gruppetti di n, una volta si e una no.*/
								std::complex<CMN_64F> temp = f[i];
								std::complex<CMN_64F> Temp = W[(i*a) % (n*a)] * f[i + n];
								f[i]=temp+Temp;
								f[i+n]=temp-Temp;
							}
					}
			n*=2;
			a=a/2;
			}
		delete[] W;
	}               
			 
public:
			 
	static void FFT(std::complex<CMN_64F> *f, CMN_32S N, CMN_64F d){
			transform(f,N);
			for(CMN_32S i=0;i<N;i++)
					f[i]*=d; //moltiplica il vettore per il passo in modo da avere il vettore trasformato effettivo
	}

	static CMN_32F IsMoving(std::complex<CMN_32F> *vec, CMN_32S N)	{
		CMN_32F maxdiff = 0;
		for (CMN_32S i = 1; i < N; ++i)
		{
			CMN_32F diff = std::fabs(std::fabs(vec[i].real()) - std::fabs(vec[0].real()));
			if (diff > maxdiff ) maxdiff = diff;
		}
		//if (maxdiff > vec[0].real()) return maxdiff;
		return maxdiff;
	}

	static CMN_64F IsMoving(std::complex<CMN_64F> *vec, CMN_32S N)	{
		CMN_64F maxdiff = 0;
		for (CMN_32S i = 1; i < N; ++i)
		{
			CMN_64F diff = std::abs(std::abs(vec[i].real()) - std::abs(vec[0].real()));
			if (diff > maxdiff) maxdiff = diff;
		}
		//if (maxdiff > vec[0].real()) return maxdiff;
		return maxdiff;
	}

};



}	// namespace numericsystem
}	// namespace CmnMath

#endif // CMNMATH_NUMERICSYSTEM_FFT_HPP__
