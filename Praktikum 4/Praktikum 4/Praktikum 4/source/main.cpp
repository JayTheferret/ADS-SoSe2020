//Zusammenarbeit mit : Cinzia-Jacqueline Mai, Jasmin Bauer.

#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>

#include "sorting.h"
#include "hashtable.h"

using namespace std;

//benchmark functions
void benchmark_heapsort();
void benchmark_mergesort();
void benchmark_quicksort();
void benchmark_shellsort();


int main(int argc, char** argv) {

  Catch::Session().run();
 // std::cin.get();

  //Hashtabelle Kollisionsausgabe:

  HashTable Kollision = HashTable(1000);

  for (int i = 0; i < 200; i++) {
	  Kollision.insert(1000 + rand()%500);
  }
  cout << "Anzahl der Kollisionen: " << Kollision.getCollisionCount() << endl;
  
//----------
  
  std::vector<int> tmp;
  

 
  vector<int> list = {9,5,7,3,8,1,6,2,4 };
  vector<int> sz(list);
  tmp.resize(list.size());
  sorting::MergeSort(sz,tmp, 0, sz.size()-1);

//----------

  char input;

  cout << "Press Y to start Benchmarking." << endl;
  cin >> input;

  if (input == 'Y') {
	  //benchmarks
	  cout << "Benchmarking Heapsort..." << endl;
	  benchmark_heapsort();

	  cout << "Benchmarking Mergesort..." << endl;
	  benchmark_mergesort();

	  cout << "Benchmarking Quicksort..." << endl;
	  benchmark_quicksort();

	  cout << "Benchmarking Shellsort..." << endl;
	  benchmark_shellsort();
  }

  

 

  return 0;
}

//executes benchmark for heapsort
void benchmark_heapsort() {

	//file stream
	ofstream heapsort_measurement;
	heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		//std::cout << "Running Heapsort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::HeapSort(V, n);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		heapsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	heapsort_measurement.close();
}

//executes benchmark for mergesort
void benchmark_mergesort() {

	//file stream
	ofstream mergesort_measurement;
	mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		//std::cout << "Running Mergesort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//create temp array
		vector<int> tmp;
		tmp.resize(n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::MergeSort(V, tmp, 0,V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		mergesort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	mergesort_measurement.close();
}

//executes benchmark for quicksort
void benchmark_quicksort() {

  //file stream
  ofstream quicksort_measurement;
  quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

  //benchmark parameters / variables
  double dtime;
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;

  vector<int> V;

  //actual benchmark loop
  for (int n = n_start; n<=n_end; n += n_step) {
	
	//"progress bar"
    //std::cout << "Running Quicksort with n: " << n << std::endl;

	//generate n random integers
	sorting::randomizeVector(V, n);

	//start measurement
    dtime = omp_get_wtime();
    
	//execzute sorting algorithm
    sorting::QuickSort(V,0,V.size()-1);

	//stop time
    dtime = omp_get_wtime() - dtime;

	//write to file
    quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
  }

  //close file handle
  quicksort_measurement.close();
}

//executes benchmark for shellsort
void benchmark_shellsort() {

	//file stream
	ofstream shellsort_measurement;
	shellsort_measurement.open("shellsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		//std::cout << "Running Shellsort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::ShellSort(V, n);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		shellsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	shellsort_measurement.close();
}