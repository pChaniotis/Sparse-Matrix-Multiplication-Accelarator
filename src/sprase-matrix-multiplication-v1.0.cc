#include <iostream>
#include <vector>

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

					data.push_back({i,j,matrix[i][j]});//					  Insert to CSR
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
			matrix error = {{0,0},{0,0}};
			return sparse(error);
		}
		
		//																   Initalize an a.row x b.column matrix
		vect vec;
		vec.assign(b.c,0);
		
		matrix C;
		C.assign (this->r,vec);
		
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


matrix mul(matrix& a, matrix& b){
	
	int ra = a.size();
	int ca = a[0].size();

	int rb = b.size();
	int cb = b[0].size();	
	
	if(ca != rb){
		
		std::cout<<"\nIllegal matrix boundaries\n";
		return {{0,0},{0,0}};
	}
	
	vect vec;
	vec.assign(cb,0);
		
	matrix C;
	C.assign (ra,vec);
	
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



int main(){
	
	

	
	matrix a =
	    {
	        {1, 0, 0},
	        {0, 0, 5},
	        {7, 0, 1},
	        {7, 0, 1}
	        
	    };
	    
	    
	matrix b =
	    {
	        {0, 0, 2},
	        {0, 1, 1},
	        {8, 6, 0}

	    };
	
	
	
	    
	    
	
	
	sparse obj_a(a);
	obj_a.printData();
			
	sparse obj_b(b);
	obj_b.printData();
	
	
	
	mul(a,b);
	
	sparse obj_c = obj_a*obj_b;
	obj_c.printData();
	

	
	
	
	
	

	
}


