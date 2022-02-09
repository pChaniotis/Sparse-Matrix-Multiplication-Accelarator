#include <iostream>

typedef int int_ac;

#define ROW 0
#define COLUMN 1
#define VALUE 2


template<int r, int c>
class sparse{
	
	public:
	int_ac NNZ;
	int_ac data[r*c][3];
	
	public:																			//-------methods---------
	sparse(const int_ac matrix [r][c]){
 	
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
	
	
	void printData(){
	    std::cout << "\nDimension of Sparse Matrix: " << NNZ << " x " << 3;
	    std::cout << "\nSparse Matrix: \nRow  Column  Value\n";
	    
		for (int i = 0; i < NNZ; i++) {
	
	    	std::cout << data[i][ROW] << " 	" << data[i][COLUMN] << "	" << data[i][VALUE] << "\n";
		}
	}
};


template<int rowA,int colA,int rowB,int colB>
sparse<rowA,colB> multiply(const sparse<rowA,colB>& a, const sparse<rowB,colB>& b){

	int_ac C[rowA][colB];
	for(int i = 0;i<rowA;i++){
		for (int j=0; j<colB; j++){
			C[i][j] = 0;
		}
	}

	for(int i = 0;i < a.NNZ;i++){//										For every column in a
		
		for(int j = 0;j < b.NNZ;j++){//									For every row in b
			
			if( a.data[i][COLUMN] == b.data[j][ROW] ){//				If b.row = a.column
				
				C[a.data[i][ROW]][b.data[j][COLUMN]] += a.data[i][VALUE] * b.data[j][VALUE];
			}
			
		}		
		
	}
	
	sparse<rowA,colB> obj(C);
	
	return obj;
}




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
	
	const int_ac ra = 4;
	const int_ac ca = 3;
	const int_ac rb = 3;
	const int_ac cb = 3;
	    

	sparse<ra,ca> obj_a(a);
	obj_a.printData();
	
	sparse<rb,cb> obj_b(b);
	obj_b.printData();
	
	
	sparse<ra,cb> obj_c = multiply<ra,ca,rb,cb>(obj_a,obj_b);
	obj_c.printData();
	

}


