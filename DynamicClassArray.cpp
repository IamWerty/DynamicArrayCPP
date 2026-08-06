#include <iostream>

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

    // 3. Оператор [] (Неконстантний - для запису та читання: arr[0] = 5)
    int& operator[](unsigned int index)
    {
        return arr[index];
    }

    // 3. Оператор [] (Константний - для читання з const об'єктів)
    const int& operator[](unsigned int index) const
    {
        return arr[index];
    }

    // 4. Оператор рівності ==
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

    // 5. Оператор нерівності != (реалізований через ==)
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
};

int main()
{
    dinamicArray arr1(3);
    arr1[0] = 10; // Використання оператора []
    arr1[1] = 20;
    arr1[2] = 30;

    // Перевірка копіюючого конструктора
    dinamicArray arr2 = arr1;

    // Перевірка оператора ==
    if (arr1 == arr2)
    {
        std::cout << "arr1 i arr2 однакові!\n";
    }

    // Змінюємо arr2
    arr2[0] = 99;

    // Перевірка оператора !=
    if (arr1 != arr2)
    {
        std::cout << "arr1 i arr2 тепер різні!\n";
    }

    // Перевірка оператора присвоєння =
    arr1 = arr2;
    std::cout << "Після arr1 = arr2, arr1[0] дорівнює: " << arr1[0] << std::endl;

    return 0;
}