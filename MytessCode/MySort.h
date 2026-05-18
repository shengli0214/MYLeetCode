#pragma once
#include <stdint.h>

#include <array>
#include <cstddef>
#include <iostream>
#include <list>
#include <map>
#include <stack>
#include <stdexcept>
#include <vector>
namespace mysort {
// class MySort
// {
// public:
// 	MySort(std::initializer_list<int> list);
// 	~MySort();

// 	void insert_sort();
// 	void merge_sort();
// 	void mysortPrint();

// private:
// 	std::vector<int> vec;
// };
// class MySort{

// }
template <typename T>
void insert_sort(std::vector<T>& vec) {
  for (auto i = 1; i != vec.size(); ++i) {
    int key_value = vec[i];
    auto j = i - 1;
    while ((j >= 0) && (key_value < vec[j])) {
      vec[j + 1] = vec[j];
      j--;
    };
    vec[j + 1] = key_value;
  };
};

template <typename T>
void mysortPrint(std::vector<T>& vec) {
  std::cout << "[";
  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    std::cout << " " << *iter << " ";
  }
  std::cout << "]" << std::endl;
};

template <typename T>
void merge_sort(std::vector<T>& vec, int x, int y, std::vector<T>& bak_vec) {
  if (x + 1 < y) {
    auto m = (x + y) / 2;  // x + (y-x)/2
    auto p = x;
    auto q = m;
    auto i = x;
    merge_sort(vec, x, m, bak_vec);
    merge_sort(vec, m, y, bak_vec);
    while (p < m || q < y) {
      if (q >= y || (p < m) && (vec[p] <= vec[q])) {
        bak_vec[i++] = vec[p++];
      } else {
        bak_vec[i++] = vec[q++];
      }
    };
    for (i = x; i < y; i++) {
      vec[i] = bak_vec[i];
    };
  };
};
inline int left(int i) { return ((i + 1) << 1) - 1; };
inline int right(int i) { return (i + 1) << 1; };
inline int parent(int i) { return ((i - 1) >> 1); }

template <typename T>
void swap(std::vector<T>& arr, int i, int j) {
  auto temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
};
/*Maintain the heip property*/
template <typename T>
void max_heapify(std::vector<T>& A, int i, int heap_size) {
  T largest;
  auto l = left(i);
  auto r = right(i);
  if (l < heap_size && A[l] > A[i]) {
    largest = l;
  } else {
    largest = i;
  }
  if (r < heap_size && A[r] > A[largest]) {
    largest = r;
  }
  if (largest != i) {
    swap(A, i, largest);
    max_heapify(A, largest, heap_size);
  }
};
template <typename T>
void build_max_heap(std::vector<T>& A) {
  auto heap_size = A.size();
  for (int i = heap_size / 2 - 1; i != -1; i--) {
    max_heapify(A, i, heap_size);
  };
};

template <typename T>
void heap_sort(std::vector<T>& A) {
  build_max_heap(A);
  int heapsize = A.size();
  for (auto i = heapsize - 1; i != 0; i--) {
    swap(A, 0, i);
    heapsize--;
    max_heapify(A, 0, heapsize);
  };
};

/*
int partition(int *array, int low, int high) {
    int val = array[low];
    while(low < high) {
      while(low<high && array[high]>=val) --high;
     swap(&array[low], &array[high]);
     while(low<high && array[low]<=val) ++low;
     swap(&array[low], &array[high]);
   }
   return low;
 }
  void Quicksort(int *array, int b, int e) {
    if (b >= e) return;
   int p = partition(array, b, e);
    Quicksort(array, b, p-1);
    Quicksort(array, p+1, e);
 }
*/
template <typename T>
size_t quick_partation(std::vector<T>& arr, size_t high, size_t low) {
  //   if (low <= high) {
  //     throw "low >= high"
  //   }
  //   T pivot = arr[low];
  size_t separate_index = low + 1;
  for (size_t i{low + 1}; i <= high; ++i) {
    if (arr.at(i) < arr.at(low)) {
      std::swap(arr, i, separate_index);
      ++separate_index;
    }
  }
  std::swap(arr, low, separate_index - 1);
  return separate_index - 1;
}

template <typename T>
std::int32_t lomuto_partition(std::vector<T>& arr, std::int32_t low,
                              std::int32_t high) {
  T pivot = arr.at(high);
  std::int32_t index{high - 1};
  for (std::int32_t j{low};j < high;++j) {
    if (arr.at(j) <= pivot) {
		++index;
		std::swap(arr,index,j);
    }
	std::swap(arr,high,index+1);
  }
  return index;
}

template <typename T>
std::int32_t lomuto_partition(T* arr, std::int32_t low,
                              std::int32_t high) {
  T pivot = arr.at(high);
  std::int32_t index{high - 1};
  for (std::int32_t j{low};j < high;++j) {
    if (arr.at(j) <= pivot) {
		++index;
		std::swap(arr,index,j);
    }
	std::swap(arr,high,index+1);
  }
  return index;
}


template <typename T>
void QuicksortNonRecur(T* array, std::int32_t b, std::int32_t e) {
  if (b >= e) {
    return;
  }
  std::stack<std::pair<std::int32_t, std::int32_t> > stk;
  stk.push(std::make_pair(b, e));
  while (!stk.empty()) {
    std::pair<std::int32_t, std::int32_t> pair = stk.top();
    stk.pop();
    if (pair.first >= pair.second) {
      continue;
    }
    std::int32_t p = lomuto_partition(array, pair.first, pair.second);
    if (p < pair.second) stk.push(std::make_pair(p + 1, e));
    if (p > pair.first) stk.push(std::make_pair(b, p - 1));
  }
}

}  // namespace mysort