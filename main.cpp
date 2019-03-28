#include <iostream>
#include "matrix.h"
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
using namespace std;

//Ralph Mehitang
//Cosc-320
//Joseph Anderson


matrixop<double> readFile(char* filename)
{
	string line;
	int numLines = 0;
	//matrixop<double> pointsMatrix;
	ifstream pointsFile;
      // matrixop<double>pointsMatrix;
	pointsFile.open("points100.dat");
	//if(pointsFile.is_open()){
		while(getline(pointsFile, line))
			numLines++;
		pointsFile.clear();
		pointsFile.seekg(0, ios::beg);
		matrixop<double>pointsMatrix(numLines, 2);
		bool isX = true;
		double temp = 0;
		int i = 0;
		while(pointsFile >> temp && i < numLines)
		{
			if(isX)
			{
				pointsMatrix[i][0] = temp;
				isX = false;
			}
			else
			{
				pointsMatrix[i][1] = temp;
				isX = true;
				i++;
			}
	//	}
	//pointsFile.close();

	}

	pointsFile.close();
	return pointsMatrix;

}
//issymmtric tst
template <class T>
bool issymmtric(matrixop<double> tmp){
matrixop<double>arr=tmp;
	for (int i = 0; i < tmp.getrows(); i++) {
		for (int j = 0; j < tmp.getcols(); j++) {
			if(tmp[i][j]!=arr[i][j]){
				return true;
			}

		}
	}
	return false;
}

int main(int argc, char** argv)
{
	char n;
if(argc != 2)
	{
		cout << "this program only takes 1 parameter please pass a second argument"<<endl;
		return 0;
	}
cout<<"Welcome to Ralph Mehitangs Project 1"<<endl;
	cout<< " For output of matrix subroutines enter a for least linear regression enter b: ";
	cin>>n;
	if(n=='a'){

int inrow;
int incol;
cout << "input the dimensions of the matrix you want " << '\n';
cout << "Rows" << '\n';
cin>>inrow;
cout << "Cols" << '\n';
cin>>incol;
//int randrval=rand()%50;	//initializing random values into matrix
//int randcval=rand()%50;
	matrixop<double> x(inrow, incol);
	//int anderson=1;
	cout<<"created matrix"<<endl;
for (int i = 0; i < x.getrows(); i++) {
	for (int j = 0; j < x.getcols(); j++) {
		int randrval=rand()%50;
		x[i][j]=randrval;
/*	if(i==j){
		x[i][j]=anderson;
		anderson++;
	}
	else
		x[i][j]=0;
		*/
	}
}
	cout<<"here is your original matrix"<<endl;
	cout<<x.printmatrix();
	cout<<"transposed matrix"<<endl;
	matrixop<double> val(x.getrows(),x.getcols());
	val=x.transpose();
	cout<<val.printmatrix();
	cout<<"------------------------------------"<<endl;
	 //output of adding
	 matrixop<double> add(x.getrows(),x.getcols());
	 cout<<"Matrix Addition Functionality"<<endl;
	 auto start = std::chrono::system_clock::now();
	 add=val+x;
	 auto end = std::chrono::system_clock::now();
	 cout<<add.printmatrix();
	 std::chrono::duration<double> elapsed_seconds = end-start;
	 std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	 std::cout << "finished at " << std::ctime(&end_time)
	 << "elapsed time: " << elapsed_seconds.count() << "s\n";
	 cout<<"------------------------------------"<<endl;
		//output of subtraction
		matrixop<double> sub(x.getrows(),x.getcols());
		cout<<"Matrix Subtraction Functionality"<<endl;
		 start = std::chrono::system_clock::now();
		sub=val-x;
		 end = std::chrono::system_clock::now();
		cout<<sub.printmatrix();
		elapsed_seconds = end-start;
		end_time = std::chrono::system_clock::to_time_t(end);
		std::cout << "finished at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";

 cout<<"------------------------------------"<<endl;
	//output of multiplication
	matrixop<double> j(x.getrows(),x.getcols());
	cout<<"Matrix Multiplication Functionality"<<endl;
	 start = std::chrono::system_clock::now();
	j=val*x;
	 end = std::chrono::system_clock::now();
	cout<<j.printmatrix();
 elapsed_seconds = end-start;
	end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "finished at " << std::ctime(&end_time)
	<< "elapsed time: " << elapsed_seconds.count() << "s\n";

	//inverse Functionality
	cout<<"------------------------------------"<<endl;
	cout<<"Matrix Inversion Functionality"<<endl;
	matrixop<double> tmp(1,1);
	 start = std::chrono::system_clock::now();
	tmp=j.inverse();
	 end = std::chrono::system_clock::now();
	matrixop<double>testv=j*tmp;
	cout<<"original matrix"<<endl;
	cout<<j.printmatrix();
	cout<<"inverse matrix"<<endl;
	cout<<tmp.printmatrix();
	cout<<"Identity matrix"<<endl;
	cout<<testv.printmatrix();
	elapsed_seconds = end-start;
	end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "finished at " << std::ctime(&end_time)
	<< "elapsed time: " << elapsed_seconds.count() << "s\n";
}
	if (n=='b'){

	 auto start = std::chrono::system_clock::now();

	matrixop<double> pointsMatrix = readFile(argv[1]);
	matrixop<double> b (pointsMatrix.getrows(), 1);
	for(int i = 0; i < pointsMatrix.getrows(); i++)
	{
		b[i][0] = pointsMatrix[i][pointsMatrix.getcols()-1];
		//pointsMatrix[i][pointsMatrix.cols-1] = 1;
	}
	for(int i = 0; i < pointsMatrix.getrows(); i++)
	{
		pointsMatrix[i][pointsMatrix.getcols() - 1] = 1;
	}
	matrixop<double> A = pointsMatrix.transpose();
	matrixop<double> I = (A * pointsMatrix);
	matrixop<double> InvI = I.inverse();
	matrixop<double>T = A * b;
	matrixop<double>TB= InvI * T;
	cout<<TB.printmatrix()<<endl;
	 auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "finished at " << std::ctime(&end_time)
	<< "elapsed time: " << elapsed_seconds.count() << "s\n";
}
}
