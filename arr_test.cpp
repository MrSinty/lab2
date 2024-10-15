#include <gtest/gtest.h>
#include "da.cpp"

// Тест конструктора по умолчанию
TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

// Тест конструктора с параметром
TEST(ArrayTest, ConstructorWithCapacity) {
    Array<int> arr(20);
    EXPECT_EQ(arr.size(), 0);
}

// Тест вставки элемента в конец массива
TEST(ArrayTest, InsertToEnd) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

// Тест вставки элемента по индексу
TEST(ArrayTest, InsertAtIndex) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(0, 5);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);
}

// Тест удаления элемента
TEST(ArrayTest, RemoveAtIndex) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.remove(0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 20);
}

// Тест доступа по индексу
TEST(ArrayTest, AccessByIndex) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    // Проверим запись
    arr[0] = 30;
    EXPECT_EQ(arr[0], 30);
}

// Тест префиксного инкремента итератора
TEST(ArrayTest, IteratorPrefixIncrement) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    auto it = arr.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

// Тест постфиксного инкремента итератора
TEST(ArrayTest, IteratorPostfixIncrement) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    auto it = arr.begin();
    EXPECT_EQ(*it, 10);
    it++;
    EXPECT_EQ(*it, 20);
}

// Тест работы range-for цикла
TEST(ArrayTest, RangeForLoop) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    int expected[] = {1, 2, 3};
    int index = 0;
    for (int x : arr) {
        EXPECT_EQ(x, expected[index]);
        index++;
    }
    EXPECT_EQ(index, 3);
}

// Тест const-итератора
TEST(ArrayTest, ConstIterator) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    const Array<int>& constArr = arr;

    auto it = constArr.cbegin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

// Тест вставки элементов с перераспределением памяти
TEST(ArrayTest, InsertWithResize) {
    Array<int> arr(2);
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);  // Перераспределение памяти
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

// Тест удаления всех элементов
TEST(ArrayTest, RemoveAllElements) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.remove(0);
    arr.remove(0);  // Удаление последнего элемента
    EXPECT_EQ(arr.size(), 0);
}

// Тест работы итераторов для пустого массива
TEST(ArrayTest, EmptyArrayIterator) {
    Array<int> arr;
    auto it = arr.begin();
    EXPECT_EQ(it, arr.end());  // Итерируемый массив пуст, поэтому итераторы равны
}

// Тест работы постфиксного инкремента для константного итератора
TEST(ArrayTest, ConstIteratorPostfixIncrement) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    const Array<int>& constArr = arr;
    auto it = constArr.cbegin();
    EXPECT_EQ(*it, 10);
    it++;
    EXPECT_EQ(*it, 20);
}

// Тест обратного итератора
TEST(ArrayTest, ReverseIterator) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    auto it = arr.reverseIterator();
    EXPECT_EQ(*it, 3);
    it++;
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 1);
}