#include <iostream>
#include <stdexcept>

class dinamicArrayBoundException : public std::out_of_range {
public:
    explicit dinamicArrayBoundException(const std::string& msg) : std::out_of_range(msg) {}
};

template<typename T>
class dinamicArray {
private:
    T* arr;
    std::size_t size;
    std::size_t capacity;

public:
    // Конструктор створює масив із заданим початковим розміром
    explicit dinamicArray(std::size_t initialSize = 0)
        : size(initialSize), capacity(initialSize)
    {
        arr = (capacity > 0) ? new T[capacity]() : nullptr;
    }

    ~dinamicArray() {
        delete[] arr;
    }

    // Копіювальний конструктор
    dinamicArray(const dinamicArray& other)
        : size(other.size), capacity(other.capacity)
    {
        arr = (capacity > 0) ? new T[capacity]() : nullptr;
        for (std::size_t i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    // Оператор присвоєння
    dinamicArray& operator=(const dinamicArray& other) {
        if (this != &other) {
            T* newArr = (other.capacity > 0) ? new T[other.capacity]() : nullptr;
            for (std::size_t i = 0; i < other.size; ++i) {
                newArr[i] = other.arr[i];
            }
            delete[] arr;
            arr = newArr;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    T& operator[](std::size_t index) {
        if (index >= size) {
            throw dinamicArrayBoundException("Index out of bounds");
        }
        return arr[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= size) {
            throw dinamicArrayBoundException("Index out of bounds");
        }
        return arr[index];
    }

    bool operator==(const dinamicArray& other) const {
        if (size != other.size) return false;
        for (std::size_t i = 0; i < size; ++i) {
            if (arr[i] != other.arr[i]) return false;
        }
        return true;
    }

    bool operator!=(const dinamicArray& other) const {
        return !(*this == other);
    }

    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity) return;

        T* newArr = new T[newCapacity]();
        for (std::size_t i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

    void resize(std::size_t newSize) {
        if (newSize > capacity) {
            reserve(newSize);
        }
        size = newSize;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        arr[size] = value;
        ++size;
    }

    std::size_t getSize() const { return size; }
    std::size_t getCapacity() const { return capacity; }

    explicit operator bool() const {
        return size > 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const dinamicArray& arrayObj) {
        os << "[";
        for (std::size_t i = 0; i < arrayObj.size; ++i) {
            os << arrayObj.arr[i];
            if (i < arrayObj.size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, dinamicArray& arrayObj) {
        for (std::size_t i = 0; i < arrayObj.size; ++i) {
            is >> arrayObj.arr[i];
        }
        return is;
    }

    void insertion_sort(dinamicArray<T>& arr)
    {
        for (int i = 1; i < arr.getSize(); ++i)
        {
            T value = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > value)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = value;
        }
    }

};

int main() {
    try {
        dinamicArray<int> arr1(3);
        arr1[0] = 10;
        arr1[1] = 20;
        arr1[2] = 30;

        dinamicArray<int> arr2 = arr1;

        if (arr1 == arr2) {
            std::cout << "arr1 and arr2 are equal\n";
        }

        arr2[0] = 99;

        if (arr1 != arr2) {
            std::cout << "arr1 and arr2 are not equal\n";
        }

        // Перевірка виходу за межі у try...catch
        try {
            int k = arr1[4];
            std::cout << "Element at index 4: " << k << std::endl;
        }
        catch (const dinamicArrayBoundException& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        arr1 = arr2;
        std::cout << "After arr1 = arr2, arr1[0] is: " << arr1[0] << std::endl;

        arr1.resize(5);

        if (arr1) {
            std::cout << "arr1 is not empty\n";
        }

        std::cout << "arr1: " << arr1 << std::endl;

        dinamicArray<int> vec;
        vec.reserve(10);

        vec.push_back(5);
        vec.push_back(10);

        std::cout << "vec: " << vec << "\n";
        std::cout << "Size: " << vec.getSize() << ", Capacity: " << vec.getCapacity() << "\n";

		arr1.insertion_sort(arr1);
		std::cout << "Sorted arr1: " << arr1 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled error: " << e.what() << std::endl;
    }

    return 0;
}