#include <iostream>

typedef int int_ac;

#define ROW 0
#define COLUMN 1
#define VALUE 2



template<int r, int c>																	//-------methods---------
void sparse(const int_ac matrix [r][c],int_ac &NNZ, int_ac data[r*c][3]){


	NNZ = 0;
	
	for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (matrix[i][j] > 0){
				//																 Insert to CSR
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


template<int rowA,int colA, int rowB,int colB>
void multiply(const int_ac a_data[colA*rowA][3], int a_NNZ, const int_ac b_data[colB*rowB][3], int b_NNZ, int_ac C[rowA][colB]){		


	for(int i = 0;i<rowA;i++){
		for (int j=0; j<colB; j++){
			C[i][j] = 0;
		}
	}
	
	for(int i = 0;i < a_NNZ;i++){//										For every column in a
		
		for(int j = 0;j < b_NNZ;j++){//									For every row in b
			
			if( a_data[i][COLUMN] == b_data[j][ROW] ){//				If b.row = a.column
				
				C[a_data[i][ROW]][b_data[j][COLUMN]] += a_data[i][VALUE] * b_data[j][VALUE];
			}
			
		}		
		
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



int main(){

	int_ac a[4][3] =
	    {
	        {1, 0, 0},
	        {0, 0, 5},
	        {7, 0, 1},
	        {7, 0, 1}
	        
	    };
	    
	const int_ac ra = 4;
	const int_ac ca = 3;
	
	int a_NNZ;
	int_ac a_data[ra*ca][3];
	sparse<ra,ca>(a,a_NNZ, a_data);
	    
	int_ac b[3][3] =
	    {
	        {0, 0, 2},
	        {0, 1, 1},
	        {8, 6, 0}

	    };
	
	const int_ac rb = 3;
	const int_ac cb = 3;
	
	int b_NNZ;
	int_ac b_data[rb*cb][3];
	sparse<rb,cb>(b,b_NNZ, b_data);
	
	int_ac C[ra][cb];
	
	multiply<ra,ca,rb,cb>(a_data, a_NNZ,b_data,b_NNZ,C);	
	
	
	printMatrix<ra,cb>(C);
	std::cin.get();

	

}


