#include "sorting.h"


namespace sorting {

	//************
	// QuickSort *
	//************      
	int partition(std::vector<int>& arr, int low, int high) {
		auto x = arr[high];
		auto i = low - 1;
		for (auto j = low; j < high; j++) {
			if (arr[j] <= x) {
				++i;
				std::swap(arr[i], arr[j]);
			}
		}
		std::swap(arr[i + 1ll], arr[high]);
		return i + 1;
	}

	void QuickSort(std::vector<int>& arr, int low, int high) {
		if (low < high) {
			auto pivot = partition(arr, low, high);
			QuickSort(arr, low, pivot - 1);
			QuickSort(arr, pivot + 1, high);
		}
	}
	

	//************
	// MergeSort *
	//************

	void Merge(vector<int> &arr, vector<int> &tmp, int low, int pivot, int high) {

	//variablen 

		int l_start = low;
		int l_end = pivot +1;
		int r_start = pivot + 1;
		int r_end = high +1;

		//zeiger auf aktuelle position
		int l_ptr = l_start;
		int r_ptr = r_start;
		int t_ptr = l_start;

		while (l_ptr != l_end || r_ptr != r_end) { //solange beide enden nicht erreicht sind (beide seiten false)

			if (l_ptr == l_end) {
				tmp[t_ptr] = arr[r_ptr];
				t_ptr++;
				r_ptr++;
			}

			else if (r_ptr == r_end) {
				tmp[t_ptr] = arr[l_ptr];
				l_ptr++;
				t_ptr++;
			}
			
			
			//in tmp einfügen
			else if (arr[l_ptr] < arr[r_ptr]) { //nur wenn nicht ein ende erreicht
				tmp[t_ptr] = arr[l_ptr];
				l_ptr++;
				t_ptr++;
			}
			else {
				tmp[t_ptr] = arr[r_ptr];
				t_ptr++;
				r_ptr++;
			}
		}

		//tmp in arr einfügen
		for (t_ptr = l_start; t_ptr < r_end; t_ptr++) {
			arr[t_ptr] = tmp[t_ptr];
		}
	}

	void MergeSort(vector<int> &arr, vector<int> &tmp, int low, int high) { //aufteilen
		if (low < high) {

			size_t pivot = size_t(std::floor((low + high) / 2));
			MergeSort(arr,tmp, low, pivot);				//linke seite inkl. pivot
			MergeSort(arr,tmp , pivot + 1, high);		//rechte seite ohne pivot
			Merge(arr,tmp, low, pivot, high);
		}
	}


	//************
	// Heapsort  *
	//************

	int leftChildIndex(int idx) {
		return 2 * idx + 1;
	}

	void percolateDown(std::vector<int>& arr, int i, int N)
	{
		int child;
		int tmp;
		for (tmp = arr[i]; leftChildIndex(i) < N; i = child) {
			child = leftChildIndex(i);
			if (child != N - 1 && arr[child] < arr[child + 1ll]) {
				child++;
			}
			if (tmp < arr[child]) {
				arr[i] = arr[child];
			}
			else {
				break;
			}
		}
		arr[i] = tmp;
	}

	void HeapSort(vector<int> & arr, int n) { // gibt array und größe
	
			// Heap aufbauen
			for (int i = n / 2; i >= 0; i--) {
				percolateDown(arr, i, n);
			}
			// Sortieren
			for (int i = n - 1; i > 0; i--) {
				std::swap(arr[0], arr[i]);
				percolateDown(arr, 0, i);
			}
	}


	//************
	// Shellsort * //Hibbardfolge aufteilen _> aufteilungen immer kleinere bereiche
	//************
	void ShellSort(vector<int> &arr, int n){
		if (n <= 1) { //sonst endlosschleife
			return;
		}

		//Hibbardfolge maximum in n finden (start)
		int start;
		for (start = 1; n - 1 > start; start = (start *2) +1) { }

		// Schleife über die Abstandsfolge
		for (int gap = start; gap > 0; gap =(gap -1)/2) {
			// Insertion Sort von Elementen mit Abstand gap 
			for (int i = gap; i < n; i++) {

				int tmp = arr[i];
				int j = i;

				for (; j >= gap && tmp < arr[j - gap]; j -= gap) {
					arr[j] = arr[j - gap];
				}
				arr[j] = tmp;
			} 
			// Elemente sind im Abstand gap sortiert
		}
	}


  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





