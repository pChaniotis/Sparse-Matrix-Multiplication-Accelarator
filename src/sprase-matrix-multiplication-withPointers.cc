#include <iostream>
#include <array>



#define ROW 0
#define COLUMN 1
#define VALUE 2


class sparse{
	
	public:
	int r;
	int c;
	int NNZ;
	int** data;
	
	public://-------methods---------
	


	sparse(int** matrix){
 	
 		NNZ = 0;
	 	r = 10;
		c = 10;
		std::cout<<r<<" "<<c;
		
		for (int i = 0; i < r; i++){
	        for (int j = 0; j < c; j++){
	            if (matrix[i][j] > 0){

					data[NNZ][ROW] = i;//					  Insert to CSR
					data[NNZ][COLUMN] = j;
					data[NNZ][VALUE] = matrix[i][j];
	 				NNZ++;
	 				std::cout<<" "<<data[NNZ][VALUE]<<" ";
				}
			}
		}						
	}
	

	void convertCSRToCSC(){ 
	    int i, j; 
	    for (i = 0; i < NNZ-1; i++)     
		    for (j = 0; j < NNZ-i-1; j++)// 							   	Last i elements are already in place 
		        if (data[j][COLUMN] > data[j+1][COLUMN]) 
		            data[j].swap(data[j+1]);

    }
    
    
    
    
    sparse operator*(const sparse& b){
		
		
		if(this->c != b.r){
		
			std::cout<<"\nIllegal matrix boundaries\n";
			
			array<array<int,100>, 100> error;
			
			return sparse(error);
		}
		
		//																   Initalize an a.row x b.column matrix
		
		array<array<int,100>, 100> C;
		
		
		//convert a to CSC
		this->convertCSRToCSC();
		
		
		
		for(int i = 0;i < this->NNZ;i++){//									For every column in a
			
			for(int j = 0;j < b.NNZ;j++){//									For every row in b
				
				if( this->data[i][COLUMN] == b.data[j][ROW] ){//				If b.row = a.column
					
					C[this->data[i][ROW]][b.data[j][COLUMN]] += this->data[i][VALUE] * b.data[j][VALUE];
						
				}else if(this->data[i][COLUMN] < b.data[j][ROW]){
					break;
				}
				
			}		
			
		}
		
		return sparse(C);
	}
	
	void printData(){
	    std::cout << "\nDimension of Sparse Matrix: " << NNZ << " x " << 3;
	    std::cout << "\nSparse Matrix: \nRow  Column  Value\n";
	 
	    
		for (int i = 0; i < NNZ; i++) {
	
	    	std::cout << data[i][ROW] << " 	" << data[i][COLUMN] << "	" << data[i][VALUE] << "\n";
		}
	}
	
	
	
};


array<array<int,100>, 100> mul(array<array<int,100>, 100>& a, array<array<int,100>, 100>& b){
	
	int ra = a.size();
	int ca = a[0].size();

	int rb = b.size();
	int cb = b[0].size();	
	

	
	array<array<int,100>, 100> C;
	
	std::cout<<"\nMatrix "<<ra<<"x"<<cb<<":"<<std::endl;
	
	for (int i = 0; i < ra; i++) {
        for (int j = 0; j < cb; j++) {

            for (int k = 0; k < rb; k++) {
            	
                C[i][j] += a[i][k] * b[k][j];
            }

            std::cout << C[i][j] << "\t";
        }

        std::cout << std::endl;
    }
	
	return C;

	
}

#define VALUE_RANGE 100 // MAXIMUM VALUE IN SPARSE MATRIX
#define SPARSITY 8 // OUT OF 10
#include <stdlib.h>

array<array<int,100>, 100> sparse_Matrix_Generator(int r, int c){
	
	array<array<int,100>, 100> m;
	int temp;
	for (int i=0; i < r; i++){
		for(int j=0; j < c; j++){
			temp = rand() % 10;
			temp = (temp/SPARSITY)* rand() % VALUE_RANGE;
			m[i][j] = temp;
		}
	}
	return m;
}


int main(){
	
	

	
	array<array<int,100>, 100> a;
	
	array<array<int,100>, 100> b;
	
	a = sparse_Matrix_Generator(100,100);
	
	b = sparse_Matrix_Generator(100,100);
	
	
	
	
	    
	    
	
	
	sparse obj_a(a);
//	obj_a.printData();
//			
//	sparse obj_b(b);
//	obj_b.printData();
//	
//	
//	
//	mul(a,b);
//	
//	sparse obj_c = obj_a*obj_b;
//	obj_c.printData();
	

	
	
	
	
	

	
}


