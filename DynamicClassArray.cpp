#include <iostream>

class dinamicArray
{
    private:
        int* arr;
        unsigned int size;
    public:
        dinamicArray(unsigned int s) : size(s)
        {
            arr = new int[size];
		}
        ~dinamicArray()
        {
            delete[] arr;
		}
        void resize(unsigned int newSize)
        {
            int* newArr = new int[newSize];
            unsigned int minSize = (newSize < size) ? newSize : size;
            for (unsigned int i = 0; i < minSize; ++i)
            {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            size = newSize;
		}
        void setValue(unsigned int index, int value)
        {
            if (index < size)
            {
                arr[index] = value;
            }
		}
        int getValue(unsigned int index) const
        {
            if (index < size)
            {
                return arr[index];
            }
			return 0; // Return 0 if index is out of bounds 
        }
        unsigned int getSize() const
        {
            return size;
        }
}
;
int main()
{
    std::cout << "Enter the size of the array: ";
	unsigned int size;
    std::cin >> size;
    dinamicArray arr(size);
    for (unsigned int i = 0; i < size; ++i)
    {
        arr.setValue(i, i * 10);
    }
    std::cout << "Array values: ";
    for (unsigned int i = 0; i < size; ++i)
    {
        std::cout << arr.getValue(i) << " ";
    }
    std::cout << std::endl;
    unsigned int newSize;
    std::cout << "Enter the new size of the array: ";
    std::cin >> newSize;
    arr.resize(newSize);
    std::cout << "Resized array values: ";
    for (unsigned int i = 0; i < arr.getSize(); ++i)
    {
        std::cout << arr.getValue(i) << " ";
    }
	std::cout << std::endl;
}