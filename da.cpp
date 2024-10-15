#include <iostream>
#include <cassert>
#include <cstdlib>
#include <conio.h>
#include <cstring>

template<typename T>
class Array {
private:
    int curSize = 0;
    int capacity = 0;
    T* data = NULL;
    
public:
    Array() : curSize(0), capacity(8) { data = (T*)(malloc(capacity * sizeof(T))); }

    Array(int cap) : curSize(0), capacity(cap) { data = (T*)(malloc(capacity * sizeof(T))); }

    ~Array() {
        clear();
        curSize = 0;
        free(data);
    }

    int insert(const T& value) { return insert(curSize, value); }

    int insert(int index, const T& value) {
        assert(index >= 0 && index <= curSize);

        if (curSize >= capacity) {
            int newCapacity = capacity * 2;

            T* newData = static_cast<T*>(malloc(newCapacity * sizeof(T)));
            if (!newData) {
                throw std::bad_alloc();
            }

            std::memcpy(newData, data, index * sizeof(T));
            newData[index] = value;
            std::memcpy(newData + index + 1, data + index, (curSize - index) * sizeof(T));

            clear();
            free(data);

            data = newData;
            capacity = newCapacity;
        } else {
            for (int i = curSize; i > index; --i)
                data[i] = std::move(data[i - 1]);
            data[index] = value;
        }

        ++curSize;
        return index;
    }

    void remove(int index) {
        assert(index >= 0 && index < curSize);

        for (int i = index; i < curSize - 1; ++i)
            data[i] = std::move(data[i + 1]);
        
        --curSize;
    }

    const T& operator[](int index) const {
        assert(index >= 0 && index < curSize);
        return data[index];
    }

    T& operator[](int index) {
        assert(index >= 0 && index < curSize);
        return data[index];
    }

    int size() const {
        return curSize;
    }

    class Iterator {
    private:
        T* ptr;
        T* end;
        bool isNotReverse = false;

    public:
        Iterator(T* ptr, T* end, bool isNotReverse) : ptr(ptr), end(end), isNotReverse(isNotReverse) {}

        const T& get() const { return *ptr; }

        void set(const T& value) { *ptr = value; }

        void next() {
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
        }

        bool hasNext() const { return ptr != end; }

        T& operator*() { return *ptr; }

        bool operator==(const Iterator& rhs) { 
            return ptr == rhs.ptr && end == rhs.end && isNotReverse == rhs.isNotReverse;
        }

        Iterator& operator++() { // префикс
            ++ptr;
            return *this;
        }
        
        Iterator operator++(int) { // постфикс
            Iterator temp = *this;
            ++ptr;
            return temp;
        }
        
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    class ConstIterator {
    private:
        const T* ptr;
        const T* end;
        bool isNotReverse = false;

    public:
        ConstIterator(const T* ptr, const T* end, bool isNotReverse) : 
        ptr(ptr), end(end), isNotReverse(isNotReverse) {}

        const T& get() const { return *ptr; }

        void next() {
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
        }

        bool hasNext() const { return ptr != end; }

        const T& operator*() const { return *ptr; }

        bool operator==(const ConstIterator& rhs) const { 
            return ptr == rhs.ptr && end == rhs.end && isNotReverse == rhs.isNotReverse;
        }

        ConstIterator& operator++() { // префикс
            ++ptr;
            return *this;
        }

        ConstIterator operator++(int) { // постфикс
            ConstIterator temp = *this;
            ++ptr;
            return temp;
        }

        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    };

    Iterator iterator() { return Iterator(data, data+curSize, true); }
    ConstIterator iterator() const { return ConstIterator(data, data+curSize, true); }
    Iterator reverseIterator() { return Iterator(data + curSize - 1, data - 1, false); }
    ConstIterator reverseIterator() const { return ConstIterator(data + curSize - 1, data - 1, false); }
    Iterator begin() { return Iterator(data, data+curSize, true); }
    ConstIterator cbegin() const { return ConstIterator(data, data+curSize, true); }
    Iterator end() { return Iterator(data + curSize, data, false); }
    ConstIterator cend() const { return ConstIterator(data + curSize, data, false); }

private:
    void clear() {
        for (int i = 0; i < curSize; ++i)
            data[i].~T();
    }
};


// int main(int argc, char* argv[])
// {
//     Array<int> a;
//     for (int i = 0; i < 10; ++i)
//         a.insert(i + 1);
//     for (int i = 0; i < a.size(); ++i)
//         a[i] *= 2;
//     for (auto it = a.iterator(); it.hasNext(); it.next())
//         std::cout << it.get() << std::endl;

//     getch();

//     return 0;
// }