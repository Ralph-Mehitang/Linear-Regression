#include <iostream>
#include "matrix.h"
#include <cstddef>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;
//constructors
template <class T>
matrixop<T>::matrixop(int m,int n){

	if(m<=0||n<=0){
		cout<<"you cannot make an array that has invalid rows and columns"<<endl;
		exit(-1);
	}
		rows=m;

		cols=n;

		data=new T*[rows];

		for (int i = 0; i < rows; i++) {

			data[i]=new T[cols];

		}
		for (int i = 0; i < rows; i++) {

			for (int j = 0; j < cols; j++) {

				data[i][j]=0;


	}
//	data=pushdata();
}
}
//allocating function
template <class T>
T** matrixop<T>::pushdata()const{
	T**arr=new T*[rows]; //creating array to store rows
	for (int i = 0; i < rows; i++)
	{
		arr[i]=new T[cols]();
//		for(int j=0;j<cols; j++)
//			arr[i][j]=0;
	}
	return arr;
}
//destructor will go through and delete each row
template<class T>
matrixop<T>::~matrixop(){
	for (int i = 0; i <rows; i++)
	{
		delete[] data[i];
	}
	delete [] data;
}
//copy contructor
template <class T>
matrixop<T>::matrixop(const matrixop& copy){

	rows=copy.rows;
	cols=copy.cols;
	data=new T*[rows];
	for (int i = 0; i < rows; i++){

		data[i]=new T[cols];
	}
	for (int i = 0; i < rows; i++) {
		/* code */
		for (int j = 0; j < cols;j++)
		{
			data[i][j]=copy.data[i][j];
		}
	}
}

//= operator
template <class T>
 matrixop<T>& matrixop<T>::operator=(const matrixop &right){

	//free space if it was in use
	for(int i=0; i<rows; i++){
		delete[]data[i];
	}
	delete [] data;
//	cout << rows << endl;
//	cout << cols << endl;
	//	cout << tp.rows << endl;
	rows=right.rows;
	cols=right.cols;
	data = new T*[rows];

	for(int i=0; i<rows; i++){
	//	cout << "in first loop"<< endl;
	//	cout << "in for loop in =" << endl;
		data[i]= new T[cols];
	}
	for (int i = 0; i < rows; i++) {
		/* code */
		for(int j=0; j<cols; j++){
	//		cout << "in second loop =" << endl;
	//		cout << "in second loop"<< endl;
			data[i][j]=right.data[i][j];
		}
	}

	return *this;
}
template <class T>
void matrixop<T>::swap(matrixop<T>& temp){
	T** t=data;
	data=temp.data;
	temp.data=t;
}
template<class T>
ostream& operator<<(ostream& temp, matrixop<T>& val){
	return temp <<val.printmatrix();
}

template<class T>
matrixop<T> matrixop<T>::operator *(matrixop<T>& val) {
	if(cols!=val.rows){
		cout<<"the number of columns on the left hand side is not equal to the number on the right hand side"<<endl;
		exit(-1);
	}
	matrixop<T> temp(rows,val.cols);
	for (int i = 0; i <rows; i++)
	{
		for (int j = 0; j < val.cols; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				temp[i][j]+=data[i][k]*val.data[k][j]; //multiplies each position of the matrix
			}
		}
	}
	return temp;
}
template <class T>
matrixop<T> matrixop<T>::operator + ( matrixop<T>& val){
	if (rows!=val.rows||cols!=val.cols){
		cout<<"the rows and columns do not match"<<endl;
		exit(-1);
	}
	matrixop<T> temp(rows,cols);
	for (int i = 0; i <rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp[i][j]=data[i][j]+val.data[i][j];
		}
	}
	return temp;
}

template <class T>
matrixop<T> matrixop<T>::operator - (matrixop<T>& val){
	if (rows!=val.rows||cols!=val.cols){
		cout<<"the rows and columns do not match"<<endl;
		return *this;
	}
	matrixop<T> temp(this->getrows(),this->getcols());
	for (int i = 0; i < val.getrows(); i++)
	{
		for (int j = 0; j < val.getcols(); j++)
		{
			temp[i][j]=this->data[i][j]-val.data[i][j];
		}
	}
	return temp;
}
template <class T>
T*& matrixop<T>::operator[] (const int& r)const{
	//cout << "in bracket operator"<<endl;
	return data[r];
}

template <class T>
matrixop<T> matrixop <T>::scalar ( double v) {
	matrixop<T> tp(rows,cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
		tp[i][j]=double(v*data[i][j]);
		}
	}
	return tp;
}

template <class T>
matrixop<T> matrixop<T>::pad()
{

	int tmp=ceil(log2(rows));
	int val=(pow(2,tmp));

	matrixop<T> Y(val,val);
	for (int i = 0; i <Y.rows; i++)
	{
		for (int j = 0; j <Y.cols; j++)
		{
			if (i<rows&&j<cols)
			{
				Y.data[i][j]=data[i][j];
			}
			else if(i==j){
				Y.data[i][j]=1;
			}

			else{
				Y.data[i][j]=0;
			}
		}

	}
	return Y;
}
//transposed function
template <class T>
matrixop<T> matrixop<T>::transpose(){
//	cout << "Transpose function" << endl;
	matrixop<T> temp(this->cols, this->rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp[j][i]=data[i][j];
		}
	}
	return temp;

}
//checking to see if power of 2
template<class T>
bool matrixop<T>::checkp(int n){
bool check=true;
while(n!=1){
	if(n%2==0)
	{
		n=n/2;
		continue;
	}
	else{
		check=false;
		break;
	}
}
return check;
}
template <class T>
matrixop<T> matrixop<T>::splitmatrix(int trow,int tcol,int brow,int bcols){
matrixop<T> tmp(rows/2,cols/2);
for(int i=trow;i<=brow;i++){
	for(int j=tcol;j<=bcols;j++){
		tmp.data[i-trow][j-tcol]=data[i][j];
	}
}
return tmp;

}
template <class T>
matrixop<T> matrixop<T>::inverse(){

	matrixop<T> Q =*this;
	bool isp=checkp(rows);
	if(!isp){
		Q = Q.pad();


	}

matrixop<T> val(this->getrows(), this->getcols());
	if(rows==1&&cols==1){
		if(data[0][0] != 0){
//			matrixop<T> val(this->getrows(),this->getcols());
			val.data[0][0] = 1/ this->data[0][0];
		return val;
	}

return *this;
	}

	matrixop<T> B=Q.splitmatrix(0,0,(Q.rows/2)-1,(Q.cols/2)-1);
	matrixop<T> C=Q.splitmatrix(Q.rows/2,0,Q.rows-1,(Q.cols/2)-1);
	matrixop<T> Ct=Q.splitmatrix(0,Q.cols/2,(Q.rows/2)-1,Q.cols-1);
	matrixop<T> D=Q.splitmatrix(Q.rows/2,Q.cols/2,Q.rows-1,Q.cols-1);

	//printing to see if the matrices have been split properly
/*
	std::cout<<B.printmatrix();
	printf("\n");
	std::cout<<C.printmatrix();

	std::cout<<Ct.printmatrix();

	std::cout<<D.printmatrix()
	*/
	matrixop<T> Binverse=B.inverse();
	matrixop<T> W=C*Binverse;
	matrixop<T>Wt=Binverse * Ct;
	matrixop<T> X=W*Ct;
	matrixop<T> S=D-X;
	matrixop<T> V=S.inverse();
	matrixop<T> Y=V*W;
	matrixop<T> Yt=Y.transpose();
	matrixop<T> L= Yt.scalar(-1);
	matrixop<T> U= Y.scalar(-1);
	matrixop<T> Z = Wt* Y;
	matrixop<T> R=Binverse + Z;
//cout<<"made it past splitting the matrix"<<endl;
//reassemble the matrices
	matrixop<T> tmp (Q.rows,Q.cols);
	for (int i = 0; i < tmp.rows/2; i++) {
		for (int j = 0; j < tmp.cols/2; j++) {
			tmp[i][j]=R[i][j];
		}
	}
	for (int i = tmp.rows/2; i < tmp.rows; i++) {
		for (int j = 0; j < tmp.cols/2; j++) {
			tmp[i][j]=U[i-tmp.cols/2][j];
		}
	}
	for (int i = 0; i < tmp.rows/2; i++) {
		for (int j = tmp.cols/2; j < tmp.cols; j++) {
			tmp[i][j]=L[i][j-tmp.cols/2];
		}
	}
	for (int i = tmp.rows/2; i < tmp.rows; i++) {
		for (int j = tmp.cols/2; j < tmp.cols; j++) {
			tmp[i][j]=V[i-tmp.rows/2][j-tmp.cols/2];
		}
	}
	matrixop<T> newmatrix(this->getrows(),this->getcols());
	for (int i = 0; i < this->getrows(); i++) {
		for (int j = 0; j< this->getcols(); j++) {
			newmatrix[i][j]=tmp[i][j];
		}
	}
	return newmatrix;
}

template <class T>
string matrixop<T>::printmatrix()const{
	string send="";
	for (int i = 0; i < rows; i++)
	{
		send+="|";
		for (int j = 0; j < cols; j++)
		{
			send +=to_string(data[i][j])+" ";
			//send +="|\n";
		}
		send +="|\n";

	}
	return send += "\n";
}
template <class T>
int matrixop<T>::getrows(){

	return rows;
}

template <class T>
int matrixop<T>::getcols(){

	return cols;
}
