#include <iostream>

typedef int int_ac;

#define ROW 0
#define COLUMN 1
#define VALUE 2


class sparse{
	
	public:
	int_ac r;
	int_ac c;
	int_ac NNZ;
	int_ac data[10000][3];
	
	public://-------methods---------
	
	
	
	sparse(const int_ac [100][100] matrix ,int_ac& r, int_ac& c){
 	
		NNZ = 0;
	 	this->r = r;
		this->c = c;
		
		for (int i = 0; i < r; i++){
	        for (int j = 0; j < c; j++){
	            if (matrix[i][j] > 0){

										//					  Insert to CSR
					data[NNZ][ROW] = i;
					data[NNZ][COLUMN] = j;
					data[NNZ][VALUE] = matrix[i][j];
					
	 				NNZ++;
				}
			}
		}						
	}
	

    
       
    
    sparse operator*(const sparse& b){
		
		
		if(this->c != b.r){
		
			std::cout<<"\nIllegal matrix boundaries\n";
		}
		
		//																   Initalize an a.row x b.column matrix
	
		int_ac C[100][100];

	
		
		
		
		for(int i = 0;i < this->NNZ;i++){//									For every column in a
			
			for(int j = 0;j < b.NNZ;j++){//									For every row in b
				
				if( this->data[i][COLUMN] == b.data[j][ROW] ){//				If b.row = a.column
					
					C[this->data[i][ROW]][b.data[j][COLUMN]] += this->data[i][VALUE] * b.data[j][VALUE];
				}
				
			}		
			
		}
		
		int_ac ra = this->r;
		int_ac cb = b.c;
		
		return sparse(C,ra,cb);
	}
	
	void printData(){
	    std::cout << "\nDimension of Sparse Matrix: " << NNZ << " x " << 3;
	    std::cout << "\nSparse Matrix: \nRow  Column  Value\n";
	 
	    
		for (int i = 0; i < NNZ; i++) {
	
	    	std::cout << data[i][ROW] << " 	" << data[i][COLUMN] << "	" << data[i][VALUE] << "\n";
		}
	}
	
	
	
};


//matrix mul(matrix& a, int_ac ra, int_ac ca, matrix& b, int_ac rb , int_ac cb){
//	
//	
//	if(ca != rb){
//		
//		std::cout<<"\nIllegal matrix boundaries\n";
//		return {{0,0},{0,0}};
//	}
//	
//	vect vec;
//	vec.assign(cb,0);
//		
//	matrix C;
//	C.assign (ra,vec);
//	
//	std::cout<<"\nMatrix "<<ra<<"x"<<cb<<":"<<std::endl;
//	
//	for (int i = 0; i < ra; i++) {
//        for (int j = 0; j < cb; j++) {
//
//            for (int k = 0; k < rb; k++) {
//            	
//                C[i][j] += a[i][k] * b[k][j];
//            }
//
//            std::cout << C[i][j] << "\t";
//        }
//
//        std::cout << std::endl;
//    }
//	
//	return C;
//
//	
//}



int main(){
	
	

	
	int_ac a[4][3] =
	    {
	        {1, 0, 0},
	        {0, 0, 5},
	        {7, 0, 1},
	        {7, 0, 1}
	        
	    };
	    
	    
	int_ac b[3][3] =
	    {
	        {0, 0, 2},
	        {0, 1, 1},
	        {8, 6, 0}

	    };
	
	
	
	    
	    
	
	
	sparse obj_a(a,4,3);
	obj_a.printData();
			
	sparse obj_b(b,3,3);
	obj_b.printData();
	
	
	
	mul(a,b);
	
	sparse obj_c = obj_a*obj_b;
	obj_c.printData();
	

	
	
	
	
	

	
}


