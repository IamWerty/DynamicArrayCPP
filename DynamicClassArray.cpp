#include <iostream>
#include <stdexcept>

class dinamicArrayBoundException : public std::out_of_range
{
public:
    dinamicArrayBoundException(const std::string& msg) : std::out_of_range(msg) {}
};

class dinamicArray
{
private:
    int* arr;
    unsigned int size;

public:
    dinamicArray(unsigned int s) : size(s)
    {
        arr = new int[size](); // init with zeros
    }
    ~dinamicArray()
    {
        delete[] arr;
    }

    // Copy Constructor
    dinamicArray(const dinamicArray& other) : size(other.size)
    {
        arr = new int[size];
        for (unsigned int i = 0; i < size; ++i)
        {
            arr[i] = other.arr[i];
        }
    }

    // Copy Assignment Operator
    dinamicArray& operator=(const dinamicArray& other)
    {
        if (this != &other) // Check for self-assignment (a = a)
        {
            delete[] arr;

            size = other.size;
            arr = new int[size];
            for (unsigned int i = 0; i < size; ++i)
            {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    // [] (Not for writing and reading: arr[0] = 5)
    int& operator[](unsigned int index)
    {
        if (index >= size)
        { throw dinamicArrayBoundException("Index out of bounds"); }
        else
        { return arr[index]; }
    }

    // [] (Constant - for reading from const objects)
    const int& operator[](unsigned int index) const
    {
        if (index >= size)
        { throw dinamicArrayBoundException("Index out of bounds"); }
        else
        { return arr[index]; }
    }

    // ==
    bool operator==(const dinamicArray& other) const
    {
        if (size != other.size)
        {
            return false;
        }
        for (unsigned int i = 0; i < size; ++i)
        {
            if (arr[i] != other.arr[i])
            {
                return false;
            }
        }
        return true;
    }

    // != (realized with ==)
    bool operator!=(const dinamicArray& other) const
    {
        return !(*this == other);
    }

    void resize(unsigned int newSize)
    {
        int* newArr = new int[newSize]();
        unsigned int minSize = (newSize < size) ? newSize : size;
        for (unsigned int i = 0; i < minSize; ++i)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        size = newSize;
    }

    unsigned int getSize() const
    {
        return size;
    }

    int getElement(int index, int size) {
        if (index < 0 || index >= size) {
            throw dinamicArrayBoundException("Index out of bounds");
        }
        return 42; // Умовне значення
    }
    
    // bool conversion 
    explicit operator bool() const
    {
        return size > 0;
    }
};

int main()
{
    dinamicArray arr1(3);
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;

    dinamicArray arr2 = arr1;

    
    if (arr1 == arr2)
    {
        std::cout << "arr1 and arr2 are equal\n";
    }

    // Змінюємо arr2
    arr2[0] = 99;

    // Перевірка оператора !=
    if (arr1 != arr2)
    {
        std::cout << "arr1 and arr2 are not equal\n";
    }
    try {
        int k = arr1[4]; // This will throw an exception since index 4 is out of bounds
		std::cout << "Element at index 4: " << k << std::endl;
    }
    catch (const dinamicArrayBoundException& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    // Checking the assignment operator =
    arr1 = arr2;
    std::cout << "After arr1 = arr2, arr1[0] is: " << arr1[0] << std::endl;
    
    return 0;
}