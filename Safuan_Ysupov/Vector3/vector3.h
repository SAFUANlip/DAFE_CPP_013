#ifndef VECTOR_H
#define VECTOR_H


/*Обобщенное программирование - это создание кода. работающего
с разными типами. заданными в виде аргументов, причем эти типы
должны соответствовать специфическим синтаксическим и семантическим требованиям.*/

/*Обобщенное программирование поддерживается шаблонами, основываясь на разрешении вызовов времени компиляции. */

/*Объектно-ориентированное программирован11е поддерживается
иерархиями классов и виртуальными функциями. основываясь
на разрешении вызовов времени выполнения. */

/*Используйте шаблоны. когда важную роль играет производительность программы (например. при интенсивных вычислениях или в программах реального времени; подробнее об этом речь
пойдет в главах 24 и 25).*/

/*Используйте шаблоны. когда важна гибкость сочетания информации
из разных типов (например. в стандартной библиотеке С++: эта тема
будет обсуждаться в главах 20 и 21 ). */

#include<algorithm>
#include <iostream>
#include <memory>
using namespace std;

/*необходимо
пред,усмотреть объект. который будет владеть объектом класса vector<int>
и сможет его удалить, если возникнет исключение. В заголовочном файле <memory> стандартной библиотеки на этот случай предоставлен класс
unique_ptr.*/

//в итоге для работы с встроенными классами:
//allocator Создание контейнера с пользовательским распределителем
//дает возможность управлять выделением и освобождением памяти
//для элементов контейнера.

// класс vector _ base работает с памятью, а не
//с типизированными объектами.
template<typename T, typename A>struct vector_base
{
    A alloc;   //Распределение памяти
    T* elem;   //Начало выделенной памяти
    int sz;    //Количество элементов
    int space; //Размер выделенной памяти

    vector_base(){};
    vector_base(A& a, int n): //было const A& по Страусттрупу
        alloc{a}, elem{a.allocate(n)}, sz{n}, space{n}{}
    ~vector_base() {alloc.deallocate(elem,space);}
};

//template<class T> тоже самое template<typename T>
template<typename T, typename A=allocator<T>> class vector:private vector_base<T,A> //Element - набор требований, которым должен соответствовать элемент(не понятно)
{
    /*
     * Инвариант:
     * для 0<=n<sz значение elem[n] является n-м элементом
     * sz<=space;
     * усли sz<space, то после elem[sz-1] есть место
     * для (space-sz) чисел типа double
    */
    A alloc; //Работает с памятью, выделяемой для элементов
    int sz;          //Размер
    T* elem;    // Указатель на первый элемент (типа double)
    int space; //Количество элементов плюс "свободное место"/ "слоты" для новых элементов
               // (текущий выделенный размер)
public:

    vector():sz{0}, elem{nullptr}, space{0} {} //конструктор по умолчанию

    // Конструктор: размещаает в памяти s чисел
    // типа double, направляет на них указатель
    // elem и сохраняет s в член sz
    //Конструктор со словом explicit не допускает неявные преобразования
    explicit vector(int s): sz{s}, elem{new T[s]}, space{s}
    {
        for (int i=0; i<sz; i++) //инициализация элементов
            elem[i]=0;
    }

    vector(const vector& a); //Конструктор копирования
    vector& operator=(const vector& a); //Конструктор присваивания

    vector(vector&& a);          //Перемещающий конструктор (по книге почему-то const)
    vector& operator=(vector&&); //Перемещающее присваивание (по книге почему-то const)

    ~vector()  {delete[] elem;}        //Деструктор, освобождает память

    T& at(int n);       //доступ с проверкой
    const T& at(int n) const; //доступ с проверкой

    T &operator[](int n); //Для неконстантных векторов, Доступ без проверки
    const T& operator[](int n) const { return elem[n]; }//для константных векторов без проверки


    //Конструктор со списком инициализации
    vector(const initializer_list<T>& lst);
    int size() const { return sz; } //Текущий размер
    int capacity() const; //Узнать размер доступной памяти

    void reserve(int newalloc); //добавляет память для новых элементов
    void resize(int newsize, T val=T()); //resize () добавляет / удаляет элементы в зависимости от заданного им размера
    void push_back(const T& val); //Увеличивает размер вектора на 1
                              //инициализирует новый элемент значением d

    T get(int n) const { return elem[n]; } //Чтение
    void set(int n, T v) { elem[n] = v; } //Запись
};




#endif // VECTOR_H