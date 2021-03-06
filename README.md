SPbAU_CPP
=========

#### Задание 1. Merge sort. ####

Реализовать алгоритм merge sort для сортировки произвольных контейнеров.
Специализировать алгоритм так, чтобы для некоторых контейнеров он работал эффективнее.
Например: list vs vector

#### Задание 2. HashMap. ####

* HashMap<TKey, TValue, TTraits = SomeDefaultTraits<TKey>>, TKey - тип ключа, TValue - тип значения
* TTraits - некоторый тип, определяющий как именно будет вычисляться хеш-значение для ключа, а также сравнение с другими ключами. Реализация по-умолчанию должна уметь работать со всеми встроенными типами
* Для упрощения реализации количество ячеек в массиве можно считать константным
* Обязательные для реализации функции
** begin()/end() - функции, возвращающие итераторы начала/конца таблицы. Тип итерируемых элементов - std::pair<TKey, TValue>
** TValue & operator[](TKey) - оператор, возращающий значение по ключу. Если такого ключа в коллекции нет - он создается вместе со значением TValue по-умолчанию.
** iterator lower_bound(TKey) - возвращает итератор на искомый элемент. Если такого нет - возвращает итератор, равный end()
** iterator insert(std::pair<TKey, TValue>) - помещает пару ключ-значение в таблицу. Возвращает итератор на место, в которое элемент был вставлен. Если в таблице уже существует пара с таким же ключем - сгенерировать ошибку. Например, поделив на ноль =)
** void remove(TKey) - угадайте с трех раз 
* Дополнительно
** Представляемая реализация должна работать с любыми примитивными типами "из коробки" т.е. без явного указания traits.
** Помимо примитивных типов, реализовать поддержку std::string и любого своего поля, хеш для когорого считается из более чем двух полей.
** Для вычисления хеша запрещается использовать готовые функции из std. (std::hash_value)
** Протестировать как минимум на следующем коде: 

```cpp
HashMap<int, int> hm;  
for (int i = 0; i < N; ++i) hm[i] = i;
for (int i = 0; i < N; ++i) if (i != hm[i]) std::cout << ...;  
```
Где N в несколько (>=4) раз больше числа "бакетов". 

#### Задание 3. Iterator. ####

Реализовать итератор, "ходящий" по строке, пропуская цифры. В частности код:

```cpp
std::string s = "aa44a";
std::copy(magic1, magic2, std::ostreambuf_iterator<char>(std::cout));
```

Должен вывести на экран "aaa". (magic1&2 - это собственно способ задания итератора. Он остается на ваше усмотрение) 

#### Задание 4.  Algorithms. ####

Предлагается реализовать следующие алгоритмы STL для двух категорий итераторов: RandomAccessIterator и ForwardIterator

```cpp
std::rotate // in-place
std::reverse // in-place
std::random_shuffle // in-place
```
