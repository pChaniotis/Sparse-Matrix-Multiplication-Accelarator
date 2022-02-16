#include <iostream>
#include "mc_scverify.h"
#include "ac_int.h"


typedef ac_int<8,false> int_ac;

#define ROW 0
#define COLUMN 1
#define VALUE 2


template<int r, int c>																	//-------methods---------
void CSR(const int_ac matrix[r][c], int_ac& NNZ, int_ac data[r * c][3]) {

	NNZ = 0;


	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (matrix[i][j] > 0) {
																				 
				data[NNZ][ROW] = i;
				data[NNZ][COLUMN] = j;
				data[NNZ][VALUE] = matrix[i][j];

				NNZ++;
			}
		}
	}
}
template<int r, int c>																	//-------methods---------
void CSC(const int_ac matrix[r][c], int_ac& NNZ, int_ac data[r * c][3]) {


	NNZ = 0;

	for (int j = 0; j < c; j++) {
		for (int i = 0; i < r; i++) {
			if (matrix[i][j] > 0) {
				//																 
				data[NNZ][ROW] = i;
				data[NNZ][COLUMN] = j;
				data[NNZ][VALUE] = matrix[i][j];

				NNZ++;
			}
		}
	}
}



template<int r, int c>
void printData(int_ac data[r*c][3], int_ac NNZ){
    std::cout << "\nDimension of Sparse Matrix: " << NNZ << " x " << 3;
    std::cout << "\nSparse Matrix: \nRow  Column  Value\n";
    
	for (int i = 0; i < NNZ; i++) {

    	std::cout << data[i][ROW] << " 	" << data[i][COLUMN] << "	" << data[i][VALUE] << "\n";
	}
}


template<int r, int c>
void printMatrix(int_ac C[r][c]){
	for(int i = 0;i<r;i++){
		for (int j=0; j<c; j++){
			std::cout<<C[i][j]<<"\t";
		}
		std::cout<<"\n";
	}
}


template<int rowA,int colA, int rowB,int colB> 
void CCS_BLOCK(multiply)(const int_ac a_data[colA*rowA][3], int a_NNZ, const int_ac b_data[colB*rowB][3], int b_NNZ, int_ac C[rowA][colB]){		


	for(int i = 0;i<rowA;i++){
		for (int j=0; j<colB; j++){
			C[i][j] = 0;
		}
	}
	
	int jRowChange = 0;
	int jStart = 0;

	for (int i = 0; i < a_NNZ; i++) {//iterate though a								
		if(i>0){
			if (a_data[i][COLUMN] > a_data[i - 1][COLUMN]) { //if a column changes

				jStart = jRowChange;
			}
		}
		for (int j = jStart; j < b_NNZ;j++) {									
			
			if( a_data[i][COLUMN] == b_data[j][ROW] ){//If b.row = a.column multiply values
				
				C[a_data[i][ROW]][b_data[j][COLUMN]] += a_data[i][VALUE] * b_data[j][VALUE];
			}
			else if (a_data[i][COLUMN] < b_data[j][ROW]) {//if b row  changes
				break;
				jRowChange = j;
			}
		
			
		}		
		
	}

}



CCS_MAIN(int argc,char** argv){
    
    

	int_ac a[4][3] =
	    {
	        {1, 0, 0},
	        {0, 0, 5},
	        {7, 0, 1},
	        {7, 0, 1}
	        
	    };
	    

	const int ra = 4;
	const int ca = 3;
	int_ac a_NNZ;
	int_ac a_data[ra*ca][3];
	CSC<ra,ca>(a,a_NNZ, a_data);
	 
  
	int_ac b[3][3] =
	    {
	        {0, 0, 2},
	        {0, 1, 1},
	        {8, 6, 0}

	    };
	
	const int rb = 3;
	const int cb = 3; 
	int_ac b_NNZ;
	int_ac b_data[rb*cb][3];
	CSR<rb,cb>(b,b_NNZ, b_data);
	
	int_ac C[ra][cb];
	
	multiply<ra,ca,rb,cb>(a_data, a_NNZ,b_data,b_NNZ,C);
	
	
	printMatrix<ra,cb>(C);
	
	//----------------------------------
	
	int_ac c[4][3] = 
	    {
	        {1, 0, 0},
	        {0, 0, 5},
	        {7, 0, 1},
	        {0, 0, 1}
	        
	    };
	    

	CSC<ra,ca>(c,a_NNZ, a_data);
	 
  
	int_ac d[3][3] = 
	    {
	        {0, 0, 2},
	        {0, 1, 1},
	        {0, 6, 0}

	    };
	
	CSR<rb,cb>(d,b_NNZ, b_data);
	
	
	multiply<ra,ca,rb,cb>(a_data, a_NNZ,b_data,b_NNZ,C);
	
	
	printMatrix<ra,cb>(C);
	

	

}
