#ifndef MATRIX_h
#define MATRIX_h
#include <stdlib.h>
#include <string>
using namespace std;

template <class T>
class matrixop{
private:
		T** data;
		int cols;
		int rows;
	public:
		matrixop(int,int);
		matrixop(const matrixop&);
		T** pushdata()const;
		~matrixop(); //destructor
		void swap(matrixop&);

		T*& operator [] (const int&) const;
		matrixop& operator=(const matrixop &right);
		matrixop operator * ( matrixop&) ;
		matrixop operator + ( matrixop&) ;
		matrixop operator - ( matrixop&) ;
		matrixop operator * ( int&);
		matrixop scalar(double);
		template <class D>
		friend 	ostream& operator <<(ostream&, matrixop<D>&);
		matrixop pad();
		matrixop transpose();
		matrixop inverse();
		string printmatrix()const;
		//matrixop readFile();
		//void progrun();
		bool checkp(int);
		matrixop generatematrix();
		matrixop splitmatrix(int,int,int,int);
		int getrows();
		int getcols();
};
#endif
