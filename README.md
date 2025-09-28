# Overview
Данный проект посвящен изучению структуры данных -- кэш. Проект написан на языке C++. В качестве системы сборки и тестирования использованы CMake и CTest.

## Installation
Для установки репозитория на свой компьютер на системах Linux для начала скопируйте адрес репозитория, после чего введите в консоль:
```bash
git clone <project_address>
```
Для того, чтобы скомпилировать проект, воспользуйтесь CMake, введя команду:
```bash
cmake --build .
```
Если вы хотите собрать проект и запустить тесты, то введите:
```bash
cmake --build . --target run_tests
```
После чего проект соберется и запустятся тесты.
В репозитории представлено две программы. А именно -- LFUCache и IdealCache. Для того, чтобы собрать конкретную программу, стоит зайти в соответсвующую директорию и ввести вышеописанные команды.

## Efficiency
UPD: количество попаданий IdealCache выросло с прошлой версии на 3 хита.

| Алгоритм | Попадания | Промахи | Эффективность (Hit Ratio) |

|--------------------|-----------|---------|---------------------------|

| **Идеальный (OPT)** | **749** | 254 | **74.9%** |

| **LFU** | **507** | 493 | **50.7%** |

## The guts
Последнее обновление заключает в себе оптимизацию идеального кэша. Как показали тесты, кэш не выдерживает конкуренции с кэшами моих комрадов, по этой причине, были выдвинуты следующие оптимизации.

### Меньшее количество обращений к памяти
```cpp
size_t  optimal_page()
{
	size_t hits =  0;

	for (size_t index =  0; index < data_amount; index++)
	{
		if (search(data[index]))
		{
			hits++;
			continue;
		}

		auto data_frequency_iterator = DataFrequency.find(data[index]);
		if (data_frequency_iterator->second ==  1) continue;

		if (capacity > Cache.size())
		{
			Cache.emplace(data[index], data[index]);
		}
		else
		{
			auto cache_key =  predict(index +  1);
			Cache.erase (cache_key);
			Cache.emplace(data[index], data[index]);
		}
	}
	return hits;
}
```
Выше представлен изначальный фрагмент реализации идеального кэша (он же алгоритм Белади и OPT). В данном фрагменте кода можно увидеть несколько проблем. Первое, что бросается в глаза, так это частое обращение к памяти при использовании ``` data[index] ```. Для того, чтобы этого не происходило, используем локальную переменную ``` int data_element = data[index]```.

В данном фрагменте кода есть ошибка, связанная с обработкой случаев, когда в будущем не найдено этого же элемента. Я принял решение отойти от реализации чистого алгоритма Белади и добавил ```std::unordered_map``` с счетчиком частоты для каждого элемента ```data```. Это позволяет мне не записывать в кэш те элементы, которые встретятся единожды. Эта оптимизация сразу дает выйгрыш в тех случаях, когда в потоке данных встречаются много страниц "одиночек", которые встречаются только один раз. В классическом алгоритме Белади они бы добавлялись в кэш, вытесняя другие страницы, которые могут встретиться. В моем же случае они просто отбрасываются.

```cpp
class  IdealCache
{
private:
	size_t capacity;
	size_t data_amount;
	std::vector<int> data;
	std::unordered_map<size_t, size_t> DataFrequency;
	std::unordered_map<size_t, int> Cache;
	...
```
В хэш таблицу DataFrequency записывается частота каждого элемента при вводе, что организуется в методе ```read_data()```

Таким образом, конечный метод ```optimal_page``` выглядит следующим образом
```cpp
size_t  optimal_page()
{
	size_t hits =  0;
	for (size_t index =  0; index < data_amount; index++)
	{
		int data_element = data[index];
		if (search(data_element))
		{
			hits++;
			continue;
		}

		auto data_frequency_iterator = DataFrequency.find(data_element);
		if (data_frequency_iterator->second ==  1) continue;
		if (capacity > Cache.size())
		{
			Cache.emplace(data_element, data_element);
		}
		else
		{
			auto cache_key =  predict(index +  1);
			Cache.erase (cache_key);
			Cache.emplace(data_element, data_element);
		}
	}
	return hits;
}
```
## Used Literature and Articles
https://stackoverflow.com/questions/55451825/why-is-vector-faster-than-unordered-map
https://stackoverflow.com/questions/8277050/optimizing-stdvector-operator-vector-access-when-it-becomes-a-bottlenec
https://www.geeksforgeeks.org/cpp/complexity-guarantees-of-the-standard-containers-cpp/
https://julien.jorge.st/posts/en/effortless-performance-improvements-in-cpp-std-unordered_map/
https://www.geeksforgeeks.org/dsa/optimal-page-replacement-algorithm/
https://www.geeksforgeeks.org/dsa/least-frequently-used-lfu-cache-implementation/
