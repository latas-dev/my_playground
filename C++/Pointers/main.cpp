#include <stdlib.h>
#include <iostream>

// RAII: 
// + Add Constructors and Destructors
// + Always use shared pointers.
// + Always use references.
// + Pass as const when value is large (+8 bytes / + 64 bits)
// + RAW POINTERS ONLY WHEN NECESSARY
template <typename T>
class DynamicArray 
{
    size_t  m_size;
    T *     m_array;

public:
    DynamicArray(size_t size)
        : m_size(size)
        , m_array(new T[size])
    {
    }
    ~DynamicArray()
    {
        delete [] m_array;
    }

    // T get(size_t index) const 
    // {
    //     return m_array[index];
    // }

    // void set(size_t index, T val) 
    // {
    //     m_array[index] = val;
    // }

    void print() const
    {
        for(size_t i = 0; i < m_size; ++i)
        {
            std::cout << i << " " << m_array[i] << "\t" << &m_array[i] << "\n"; 
        }
        std::cout << "\n";
    }

    T & operator [] (size_t index)
    {
        return m_array[index];
    } 

    const T & operator [] (size_t index) const
    {
        return m_array[index];
    }
    
};

void printPointer(const int &p)
{
    std::cout << &p << " " << p << " " << sizeof(p) << "\n";

}

int main(int argc, char **argv) 
{
    size_t my_size = 10;

    DynamicArray<int> my_array(my_size);

    my_array.print();

    for(auto i = 0; i < my_size; ++i)
    {
        my_array[i] = 10;
    }

    my_array.print();

    DynamicArray<float> float_arr(5);
    for(size_t i = 0; i < 5; ++i)
    {
            float_arr[i] = (float) i / 2;
    } 
    float_arr.print();
    // int *arr1 = (int *)malloc(10 * sizeof(int));
    // int *arr2 = (int *)calloc(10, sizeof(int));

    // for(size_t i = 0; i < 10; i++)
    // {
    //     printPointer(arr1[i]);
    // }

    // std::cout << std::endl;

    // for(size_t i = 0; i < 10; i++)
    // {
    //     printPointer(arr2[i]);
    // }

    // std::cout << std::endl;
    // std::cout << std::endl;

    // int arr3[10] = {};
    // int *arr4 = new int[10];

    //     for(size_t i = 0; i < 10; i++)
    // {
    //     printPointer(arr3[i]);
    // }

    // std::cout << std::endl;

    // for(size_t i = 0; i < 10; i++)
    // {
    //     printPointer(arr4[i]);
    // }

    // free(arr1);
    // free(arr2);
    // free(arr4);

    return 0;
}