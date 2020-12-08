﻿//Векторы и динамически выделяемая память
#include <iostream>
using namespace std;


class vector
{
    int sz;          //Размер
    double* elem;    // Указатель на первый элемент (типа double)
public:
    vector(int s) :           //Конструктор
        sz{ s },              // Инициализация члена sz
        elem{ new double[s] }   // Инициализация члена elem
    {
        for (int i = 0; i < s; i++)  // инициализация
            elem[i] = 0;            // элементов
    }

    vector(initializer_list<double> lst)
        :sz{lst.size()},
        elem{new double[sz]}
    {
        copy(lst.begin(), lst.end(), elem);
    }
    ~vector()           //Деструктор, освобождает память
    {
        delete[] elem;
    }
    // Конструктор: размещаает в памяти s чисел
    // типа double, направляет на них указатель
    // elem и сохраняет s в член sz

    int size() const { return sz; } //Текущий размер
    double get(int n) const { return elem[n]; } //Чтение
    void set(int n, double v) { elem[n] = v; } //Запись
};
// Деструктор. 
/*Точно так же как конструктор неявно вызывается при создании объекта класса, деструктор неявно вызывается, когда объект выходит за пределы области видимости. Конструктор гарантирует, что объект будет правильно
создан и проинициализирован. Деструктор, наоборот, гарантирует, что
объект будет правильно очищен перед тем, как будет уничтожен.*/

void f(void* pv)
{
    void* pv2 = pv; // Правильно(тип void* для этого
                    // и предназна чен)
        //double * pd = pv; // Ошибка : невозможно привести тип
                    // void* к douЫe *
        //*pv = 7;    // Ошибка : невозможно разыменовать void*
                    // (тип объекта, на который указывает pv,
                    // неизвестен)
        //pv[2] = 9;  // Ошибка : void* нельзя индексировать
    int* pi = static_cast<int*>(pv); // ОК: явное преобразование 
    /*Оператор static_cast позволяет явно преобразовать указатели связанных
типов один в другой, например такие, как void* или douЫe**/
}

/*
* В языке С++ предусмотрены два оператора приведения типов, которые
потенциально еще хуже оператора static_cast.
• Оператор reinterpret_cast может преобразовать тип в совершенно
другой, никак не связанный с ним, например int в douЫe*.
• Оператор const cast позволяет отбросить квалификатор const. 
*/

int main()
{
    vector v(5);
    for (int i = 0; i < v.size(); ++i)
    {
        v.set(i, 1.1 * 1);
        cout << "v[" << i << "]==" << v.get(i) << endl;
    }
    int x = v.size();
    double d = v.get(3);
    cout << x << ' ' << d;

    /*Как и оператор . (точка) . оператор -> (стрелка) можно использовать
для доступа к данным-членам и функциям-членам. Поскольку встроенные
типы, такие как int и douЫe, не имеют членов, оператор -> к ним не применяется. Операторы "точка" и "стрелка" часто называют операторами
доступа к членам класса (member access operators).*/
    //оператор -> (стрелка) для доступа к
    //своим членам с помощью указателя на объект
    vector* p = new vector(4);
    int x = p->size();
    double d = p->get(3);

    void* pvl = new int; // О!\: int* превращается в void*
    void* pv2 = new double[10]; // ОК: douЬle* превращается в void* 

    /*• Присвоение чего - либо указателю изменяет значение указателя,
        а не объекта, на который он указывает.
        • Для того чтобы получить указатель, как правило, необходимо
        использовать оператор new или& .
        • Для доступа к объекту, на который указывает указатель, используются операторы* и[] .
        • Присвоение ссылке нового значения изменяет значение объекта, на
        который она ссылается, а не саму ссылку.
        • После инициализации ссылку невозможно перенаправить на другой
        объект.
        • Присваивание ссылок выполняет глубокое копирование(новое значение присваивается объекту.на который указывает ссылка); присваивание указателей не использует глубокое копирование(новое
            значение присваивается указателю, а не объекту).
        • Нулевые указатели представляют опасность.*/
    int х = 10;
    int* р = &х; // Для получения указа теля нужен опера тор &
    *р = 7;  // Для присвоения зна чения переменной х
             // через указатель р используется *
    int х2 = *р;  // Считываем зна чение х с помощью указа теля р
    int* р2 = &х2;  // Получаем указатель на другую переменную
                    // типа int
    р2 = р;      // Указа тели р2 и р указывают на переменную х
    р = &х2;     // Указа тель р указывает на другой объект 
    
    // Соответствующий пример для ссылок 
    int y = 10;
    int& r = y; // Символ & означает тип, а не инициализатор
    r = 7;      // Присвоение зна чения переменной у
                // с помощью ссылки r (опера тор * не нужен)
    int y2 = r; // Считываем переменную у с помощью ссылки r
                // (оператор * не нужен)
    int& r2 = y2; // Ссылка на другую переменную типа int
    r2 = r;       // значение переменной у присваивается
                  // переменной у2
    //r = &y2;    // Ошибка : нельзя изменить значение ссылки
                  // (нельзя присвоить int* ссылке int&)
   
}
/*
При создании объекта класса vector в динамической памяти оператор
new выполняет следующие действия:
• сначала выделяет память для объекта класса vector;
• затем вызывает конструктор класса vector, чтобы инициализировать объект; этот конструктор выделяет память для элементов объекта класса vector и инициализирует их.
Удаляя объект класса vector, оператор delete выполняет следующие действия:
• сначала вызывает деструктор класса vector; этот деструктор, в свою
очередь, вызывает деструкторы элементов (если таковые имеются), а
затем освобождает память, занимаемую элементами вектора;
• затем освобождает память, занятую объектом класса vector. 
*/

/*тип void* означает "указатель на ячейку памяти, тип которой компилятору неизвестен". Он используется тогда, когда необходимо
передать адрес из одной части программы в другую. причем каждая из них ничего не знает о типе объекта, с которым работает другая
часть. */