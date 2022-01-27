#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>

typedef std::vector<int> vect;
typedef std::vector<std::vector<int> > matrix;

#define ROW 0
#define COLUMN 1
#define VALUE 2


class sparse{
	
	public:
	int r;
	int c;
	int NNZ;
	matrix data;
	
	public://-------methods---------
	

	
	sparse(const matrix& matrix){
 	
		NNZ = 0;
	 	r = matrix.size();
		c = matrix[0].size();
		
		for (int i = 0; i < r; i++){
	        for (int j = 0; j < c; j++){
	            if (matrix[i][j] > 0){
	                
	                vect pb;
	                
	                pb.push_back(i);
	                pb.push_back(j);
	                pb.push_back(matrix[i][j]);

					data.push_back(pb);//								  Insert to CSR
	 				NNZ++;
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
		}
		
		//																  	 Initalize an a.row x b.column matrix
		vect vec;
		vec.assign(b.c,0);
		
		matrix C;
		C.assign (this->r,vec);
		
		
		if(this->c != b.r){
		
			std::cout<<"\nIllegal matrix boundaries\n";
			return sparse(C);
		}
		
		//convert a to CSC
		//this->convertCSRToCSC();
		
		
		
		for(int i = 0;i < this->NNZ;i++){//										For every column in a
			
			for(int j = 0;j < b.NNZ;j++){//										For every row in b
				
				if( this->data[i][COLUMN] == b.data[j][ROW] ){//				If b.row = a.column
					
					C[this->data[i][ROW]][b.data[j][COLUMN]] += this->data[i][VALUE] * b.data[j][VALUE];
						
				//}else if(this->data[i][COLUMN] < b.data[j][ROW]){
				//	break;
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


matrix mul(matrix& a, matrix& b){
	
	int ra = a.size();
	int ca = a[0].size();

	int rb = b.size();
	int cb = b[0].size();	
	
	
	
	vect vec;
	vec.assign(cb,0);
		
	matrix C;
	C.assign (ra,vec);
	
	
	if(ca != rb){
		
		std::cout<<"\nIllegal matrix boundaries\n";
		return C;
	}
	
	
	
	std::cout<<"\nMatrix "<<ra<<"x"<<cb<<":"<<std::endl;
	
	for (int i = 0; i < ra; i++) {
        for (int j = 0; j < cb; j++) {

            for (int k = 0; k < rb; k++) {
            	
                C[i][j] += a[i][k] * b[k][j];
            }

            //std::cout << C[i][j] << "\t";
        }

        //std::cout << std::endl;
    }
	
	return C;

	
}

#define VALUE_RANGE 20 // MAXIMUM VALUE IN SPARSE MATRIX
#define SPARSITY 6 // OUT OF 10


matrix sparseMatrixGenerator(int r, int c){
	
	matrix m;
	vect v;
	int temp;
	for (int i=0; i < r; i++){
		for(int j=0; j < c; j++){
			temp = rand() % 10;
			temp = (temp/SPARSITY)* rand() % VALUE_RANGE;
			
			v.push_back(temp);     
		}
		m.push_back(v);
		v.clear();
	}
	return m;
}



int main(){
	
	

	
//	matrix a;
//    vect pb;
//    pb.push_back(0);
//    pb.push_back(1);
//    pb.push_back(7);
//    a.push_back(pb);
//    pb.push_back(2);
//    pb.push_back(0);
//    pb.push_back(1);
//    a.push_back(pb);
//    pb.push_back(4);
//    pb.push_back(1);
//    pb.push_back(0);
//    a.push_back(pb);
    
	    
//	matrix b;
//    pb.clear();
//    pb.push_back(0);
//    pb.push_back(1);
//    pb.push_back(7);
//    b.push_back(pb);
//    pb.push_back(2);
//    pb.push_back(0);
//    pb.push_back(1);
//    b.push_back(pb);
//    pb.push_back(4);
//    pb.push_back(1);
//    pb.push_back(0);
//    b.push_back(pb); 

	
matrix a = sparseMatrixGenerator(200,100);

matrix b = sparseMatrixGenerator(100,200);
	    
	    
	
	
	
	sparse obj_a(a);
	//obj_a.printData();
	
	sparse obj_b(b);
	//obj_b.printData();
	
	
	
	
	auto start = std::chrono::high_resolution_clock::now();
	//mul(a,b);
	
	//sparse obj_c = obj_a*obj_b;
	
	auto stop = std::chrono::high_resolution_clock::now();
	
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  
    std::cout << "Time taken by function: "<< duration.count() << " ms" << std::endl;
	
	obj_c.printData();
	

	
	
	
	
	

	
}

