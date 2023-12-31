#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>
#include <string.h>

using namespace std;

#define SYSTEMTIME clock_t

bool test = false;
 
void OnMult(int m_ar, int m_br) 
{
	
	SYSTEMTIME Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;



	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);



    Time1 = clock();

	for(i=0; i<m_ar; i++)
	{	for( j=0; j<m_br; j++)
		{	temp = 0;
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}


    Time2 = clock();
	if(!test){
		sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
		cout << st;
	}else {
		sprintf(st, "%3.3f,", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
		cout << st;
	}

	// display 10 elements of the result matrix tto verify correctness
	if(!test){
		cout << "Result matrix: " << endl;
		for(i=0; i<1; i++)
		{	for(j=0; j<min(10,m_br); j++)
				cout << phc[j] << " ";
		}
		cout << endl;
	}
	

    free(pha);
    free(phb);
    free(phc);
	
	
}

// add code here for line x line matriz multiplication
void OnMultLine(int m_ar, int m_br)
{
    SYSTEMTIME Time1, Time2;
	
	char st[100];
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;



	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);



    Time1 = clock();

	//code here
	for(i=0; i<m_ar; i++) {
		for(k=0; k<m_br; k++) {
			for(j=0; j<m_ar; j++) {
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j];
			}
		}
	}



    Time2 = clock();
	if(!test){
		sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
		cout << st;
	}else {
		sprintf(st, "%3.3f,", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
		cout << st;
	}
		

	// display 10 elements of the result matrix tto verify correctness
	if(!test){
		cout << "Result matrix: " << endl;
		for(i=0; i<1; i++)
		{	for(j=0; j<min(10,m_br); j++)
				cout << phc[j] << " ";
		}
		cout << endl;
	}
	

    free(pha);
    free(phb);
    free(phc);
    
}

// add code here for block x block matriz multiplication
void OnMultBlock(int m_ar, int m_br, int bkSize)
{
	if(bkSize > m_ar){
		perror("The given Block Size is greater than the array capacity"); 
		return; 
	}
	if(m_ar % bkSize != 0){
		perror("The given matrix size cannot be divided into smaller block chunks"); 
		return; 
	}

	SYSTEMTIME Time1, Time2;
	
	char st[100];

	//Allocates Arrays
    double *pha, *phb, *phc;
	int elemstotal = m_ar*m_br; 

    pha = (double *)malloc(elemstotal * sizeof(double));
	phb = (double *)malloc(elemstotal * sizeof(double));
	phc = (double *)malloc(elemstotal * sizeof(double));

	//Inserts values into the arrays

	for(int i=0; i<m_ar; i++)
		for(int j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;


	for(int i=0; i<m_br; i++)
		for(int j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	Time1 = clock();

	//Block Multiplication Implementation

	int i=0, j=0, k=0, x=0, y=0, z=0; 

	//"Block division" part
	for(i; i<m_ar; i+=bkSize){
		for(j; j<m_br; j+=bkSize){
			for(k; k<m_ar; k+=bkSize){
				//Block Multiplication using exercise 2 aproach 
				for(x = i; x<i+bkSize; x++){
					for(y = j; y<j+bkSize; y++){
						for(z = k; z<k+bkSize; z++){
							phc[x*m_ar+z] += pha[i*m_ar+y] * phb[y*m_ar+z];
						}
					}
				}
			}
		}
	}


	Time2 = clock();
	if(!test){
		sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
		cout << st;
	}else {
		sprintf(st, "%3.3f,", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
		cout << st;
	}
		

	// display 10 elements of the result matrix tto verify correctness
	if(!test){
		cout << "Result matrix: " << endl;
		for(i=0; i<1; i++)
		{	for(j=0; j<min(10,m_br); j++)
				cout << phc[j] << " ";
		}
		cout << endl;
	}

    free(pha);
    free(phb);
    free(phc);
}


void handle_error (int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void init_papi() {
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}


int main (int argc, char *argv[])
{

	char c;
	int lin, col, blockSize;
	int op;
	
	int EventSet = PAPI_NULL;
  	long long values[7];
  	int ret;
	//bool test = false;

	if(argc > 1) 
		if (strcmp(argv[1], "-test") == 0 || strcmp(argv[1], "-t") == 0){
			test = true;
			cout << "Matrix,BlockSize,Time,L1DCM,L2DCM,L1ICM,L2ICM,L1TCM,L2TCM,TOTINS\n";
		}
			
		else {
			cout << "Usage: ./matrixproduct [-t|-tests]\n";
			return -1;
		}
	

	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		std::cout << "FAIL" << endl;


	ret = PAPI_create_eventset(&EventSet);
		if (ret != PAPI_OK) cout << "ERROR: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
	if (ret != PAPI_OK) cout << "ERROR: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) cout << "ERROR: PAPI_L2_DCM" << endl;

	//custom
	ret = PAPI_add_event(EventSet,PAPI_L1_ICM);
	if (ret != PAPI_OK) cout << "ERROR: PAPI_L1_ICM" << endl;

	ret = PAPI_add_event(EventSet,PAPI_L2_ICM);
	if (ret != PAPI_OK) cout << "ERROR: PAPI_L2_ICM" << endl;

	ret = PAPI_add_event(EventSet,PAPI_L1_TCM);
	if (ret != PAPI_OK) cout << "ERROR: PAPI_L1_TCM" << endl;

	ret = PAPI_add_event(EventSet,PAPI_L2_TCM);
	if (ret != PAPI_OK) cout << "ERROR: PAPI_L2_TCM" << endl;

	ret = PAPI_add_event(EventSet,PAPI_TOT_INS);
	if (ret != PAPI_OK) cout << "ERROR: PAPI_L2_INS" << endl;


	op=1;
	do {
		if(!test){
			cout << endl << "1. Multiplication" << endl;
			cout << "2. Line Multiplication" << endl;
			cout << "3. Block Multiplication" << endl;
			cout << "Selection?: ";
		}
		
		cin >>op;
		if (op == 0)
			break;
		if(!test)
			printf("Dimensions: lins=cols ? ");
   		cin >> lin;
   		col = lin;

		if(test)
			cout << lin << ',';


		// Start counting
		ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERROR: Start PAPI" << endl;

		switch (op){
			case 1: 
				if(test) cout << "0,";
				OnMult(lin, col);
				break;
			case 2:
			if(test) cout << "0,";
				OnMultLine(lin, col);  
				break;
			case 3:
				if(!test)
					cout << "Block Size? ";
				cin >> blockSize;
				if(test)
					cout << blockSize << ',';
				OnMultBlock(lin, col, blockSize);  
				break;

		}

  		ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERROR: Stop PAPI" << endl;
		if(!test){
			printf("L1 DCM: %lld \n",values[0]);
  			printf("L2 DCM: %lld \n",values[1]);
			printf("L1 ICM: %lld \n",values[2]);
			printf("L2 ICM: %lld \n",values[3]);
			printf("L1 TCM: %lld \n",values[4]);
			printf("L2 TCM: %lld \n",values[5]);
			printf("TOT INS: %lld \n",values[6]);
		}else{
			printf("%lld,",values[0]);
			printf("%lld,",values[1]);
			printf("%lld,",values[2]);
			printf("%lld,",values[3]);
			printf("%lld,",values[4]);
			printf("%lld,",values[5]);
  			printf("%lld\n",values[6]);
		}
  		

		ret = PAPI_reset( EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL reset" << endl; 



	}while (op != 0);

	ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
	if ( ret != PAPI_OK )
		std::cout << "FAIL remove event" << endl; 

	ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
	if ( ret != PAPI_OK )
		std::cout << "FAIL remove event" << endl;

	//custom
	ret = PAPI_remove_event( EventSet, PAPI_L1_ICM );
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	ret = PAPI_remove_event( EventSet, PAPI_L2_ICM );
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	ret = PAPI_remove_event( EventSet, PAPI_L1_TCM );
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	ret = PAPI_remove_event( EventSet, PAPI_L2_TCM );
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	ret = PAPI_remove_event( EventSet, PAPI_TOT_INS );
	if (ret != PAPI_OK)
		std::cout << "FAIL remove event" << endl;

	 

	ret = PAPI_destroy_eventset( &EventSet );
	if ( ret != PAPI_OK )
		std::cout << "FAIL destroy" << endl;

	

}