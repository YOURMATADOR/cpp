#include <iostream>

template <typename T>
class Vector
{
private:
    T *arr; // pointer to heap
    unsigned long int capacity;
    unsigned long int size;
    double maxlf;
    double minlf;
    bool canDoubleSize() const;
    bool canHalfSize() const;
    void resize(unsigned long int);

public:
    explicit Vector(long int = 10); // default value if not passed
    int Capacity() const { return this->capacity; }
    int Size() const { return (*this).size; }
    Vector<T> &GetReference();
    int at(int);
    int *atPointer(unsigned int);
    bool isEmpty();
    Vector<T> &Push(T);
    Vector<T> &Pop();
    Vector<T> &remove(T);
    Vector<T> &del(unsigned long int);
    long int find(T);
    Vector<T> &insert(unsigned int, T);
    Vector<T> &prepend(T);
};

template <typename T>
Vector<T>::Vector(long int capacity) : arr(new T[capacity]), size(0), capacity(capacity), maxlf(.7), minlf(.2) {}

template <typename T>
Vector<T> &Vector<T>::GetReference()
{
    return *this;
};

template <typename T> // O(1)
int Vector<T>::at(int index)
{
    if (index > this->capacity)
    {
        return -1;
    };
    return *(this->arr + index);
}

template <typename T> // O(1)
int *Vector<T>::atPointer(unsigned int index)
{
    if (index > this->capacity)
    {
        return nullptr;
    };
    return this->arr + index;
}

template <typename T> // O(1)
bool Vector<T>::isEmpty()
{
    if (this->size > 0)
    {
        return false;
    };
    return true;
}

template <typename T> // O(1)
bool Vector<T>::canDoubleSize() const
{
    double currentlf = (double)this->size / (double)this->capacity;
    if (currentlf >= this->maxlf)
    {
        return true;
    };
    return false;
}

template <typename T> // O(1)
bool Vector<T>::canHalfSize() const
{
    double currentlf = (double)this->size / (double)this->capacity;
    if (currentlf <= this->minlf)
    {
        return true;
    };
    return false;
}

template <typename T> // O(n)
void Vector<T>::resize(unsigned long int newCapacity)
{
    T *old = this->arr;
    T *newarr = new T[newCapacity];
    for (int i = 0; i < this->size; i++)
    {
        *(newarr + i) = *(this->arr + i);
    };
    this->capacity = newCapacity;
    delete[] old;
}

template <typename T> // O(1)
Vector<T> &Vector<T>::Push(T element)
{
    if (this->canDoubleSize())
        this->resize(this->capacity * 2);

    *(this->arr + this->size) = element;
    this->size++;
    return *this;
}

template <typename T> // O(1)
Vector<T> &Vector<T>::Pop()
{
    if (this->isEmpty())
        return *this;
    *(this->arr + this->size - 1) = 0;
    this->size--;
    if (this->canHalfSize())
        this->resize(this->capacity / 2);

    return *this;
}

template <typename T> // 
Vector<T> &Vector<T>::remove(T item)
{
    if (this->isEmpty())
        return *this;
    long int index = this->find(item);
    if (index > -1)
        this->del(index).remove(item);
    return *this;
}

template <typename T> // O(n)
Vector<T> &Vector<T>::del(unsigned long int index)
{
    if (this->isEmpty())
        return *this;
    if ((index + 1) > this->size)
        return *this;

    for (unsigned long int i = index; i < this->size - 1; i++)
    {
        *(this->arr + i) = *(this->arr + (unsigned long int)(i + 1));
    };
    *(this->arr + (unsigned long int)(this->size - 1)) = 0;
    this->size--;

    if (this->canHalfSize())
        this->resize(this->capacity / 2);
    return *this;
}

template <typename T> // O(n)
long int Vector<T>::find(T element)
{
    if (this->isEmpty())
        return -1;
    for (long int i = 0; i < this->size; i++)
    {
        if (*(this->arr + i) == element)
        {
            return i;
        }
    };
    return -1;
}

template <typename T> // O(n)
Vector<T> &Vector<T>::insert(unsigned int index, T element)
{
    if (!(index < size))
        return *this;
    if (this->canDoubleSize())
        this->resize(this->capacity * 2);

    T temp = *(this->arr + index);
    *(this->arr + index) = element;

    for (unsigned int i = index + 1; i < size; i++)
    {
        T temp2 = *(this->arr + i);
        *(this->arr + i) = temp;
        temp = temp2;
    };
    *(this->arr + size) = temp;
    this->size++;
    return *this;
}

template <typename T>// O(n)
Vector<T> &Vector<T>::prepend(T item)
{
    this->insert(0, item);
    return *this;
}

int main()
{

    int value{7};
    int *ptr{&value};

    std::cout << ptr << '\n';
    std::cout << ptr + 1 << '\n';
    std::cout << ptr + 2 << '\n';
    std::cout << ptr + 3 << '\n';
    Vector<int> v(3);
    v.GetReference();
    int pv = v.at(0);
    std::cout << v.atPointer(0) << std::endl;

    std::cout << v.isEmpty() << std::endl; // 1
    v.Push(1);
    std::cout << *(v).atPointer(0) << std::endl;
    v.Push(2);
    std::cout << *(v).atPointer(1) << v.atPointer(1) << std::endl;
    v.Push(3);
    v.Push(4);
    std::cout << v.isEmpty() << std::endl; // 0
    v.Pop();

    v.insert(1, 4).prepend(0); // 0,1,4,2,3
    int el = v.at(2);
    v.remove(4);
    v.Push(19); // 0,1,2,3
    el = v.at(2);
    int res = v.find(19);
    std::cout << el << std::endl;
    return 0;
}