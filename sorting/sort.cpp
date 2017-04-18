#include <iostream>
#include <vector>

using namespace std;

class Sort {
public:
    void print(vector<int>& arr) {
        for (int v : arr)
            cout << v << " ";
        cout << endl;
    }
    virtual void sort(vector<int>& arr) = 0;
protected:
    void swap(vector<int>& arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
};

class MergeSort : public Sort {
public:
    void sort(vector<int>& arr) {
        mergesort(arr, 0, arr.size() - 1);
    }

private:
    void mergesort(vector<int>& arr, int start, int end) {
        if (start == end)
            return;

        int length = end - start;
        int mid = start + (length / 2);

        mergesort(arr, start, mid);
        mergesort(arr, mid + 1, end);

        merge(arr, start, mid, end);
    }

    void merge(vector<int>& arr, int start, int mid, int end) {
        int i = start;
        int j = mid + 1;

        vector<int> sorted_arr;
        while (i <= mid && j <= end) {
            if (arr[i] < arr[j]) {
                sorted_arr.push_back(arr[i]);
                i++;
            }
            else {
                sorted_arr.push_back(arr[j]);
                j++;
            }
        }

        while (i <= mid) {
            sorted_arr.push_back(arr[i]);
            i++;
        }

        while (j <= end) {
            sorted_arr.push_back(arr[j]);
            j++;
        }

        int sorted_index = 0;
        for (int index = start; index <= end; index++) {
            arr[index] = sorted_arr[sorted_index];
            sorted_index++;
        }
    }
};

class InsertionSort : public Sort {
public:
    void sort(vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (arr[i] < arr[j]) {
                    swap(arr, i, j);
                    i = j;
                }
            }
        }
    }
};

class QuickSort : public Sort {
public:
    void sort(vector<int>& arr) {
      quicksort(arr, 0, arr.size()-1);
    }
private:
    int partitioning(vector<int>& arr, int start, int end) {
        int pivot = arr[end];
        int i = start - 1;

        for (int j = start; j < end; j++) {
          if (arr[j] <= pivot) {
            i++;
            swap(arr, i, j);
          }
        }

        int pos = i+1;
        swap(arr, pos, end);

        return pos;
    }

    void quicksort(vector<int>& arr, int start, int end) {
      if (start < end) {
        rand_pivot(arr, start, end);
        int pivot = partitioning(arr, start, end);

        quicksort(arr, start, pivot - 1);
        quicksort(arr, pivot + 1, end);
      }
    }

    void rand_pivot(vector<int>& arr, int start, int end) {
      int pivot = rand()%(end - start);

      swap(arr, start + pivot, end);
    }
};

class Test {
public:
    static void run(Sort& s, vector<int> arr) {
        s.sort(arr);
        s.print(arr);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        arr[i] = v;
    }

/*    MergeSort ms;
    Test::run(ms, arr);
    InsertionSort is;
    Test::run(is, arr);*/
    QuickSort qs;
    Test::run(qs, arr);
}
