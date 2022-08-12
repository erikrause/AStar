# Алгортим поиска пути A*

## Использование

Запуск:

```
AStarConsole.exe %sizeX %sizeY
```

- Сгенерируется сетка размера (sizeX, sizeY) со случайно заданными весами (вес узла визуализируется оттенками **синего**, таким образом темные ячейки - наихудший путь). 
- Правой кнопкой мыши можно задать узлам максимальный вес.
- Левой кнопкой мыши выбираются начальная и конечная позиции.
- После нажатия **Enter** алгоритм найдет кратчайший путь от начальной до конечной позиции (путь визуализируется **красным** цветом, а обработанные узлы - **зеленым**).

<p align="center"><img src="https://github.com/erikrause/AStar/blob/main/examples/grid.png" width="50%"></p>
<p align="center"><img src="https://github.com/erikrause/AStar/blob/main/examples/path.png" width="50%" align="center"></p>

## Описание

Для визуализации используется библиотека SFML.

В [AStarConsole.cpp](https://github.com/erikrause/AStar/blob/main/AStarConsole/AStarConsole.cpp) находится точка входа и происходит логика визуализации.

Поиск пути происходит в конструкторе класса [AStar](https://github.com/erikrause/AStar/blob/main/AStarLib/AStar.cpp).

Для поиска элементов с минимальной эвристикой из очереди непроверенных узлов в качестве контейнера используется двоичная куча [BinaryHeapContainer](https://github.com/erikrause/AStar/blob/main/ContainerLib/BinaryHeapContainer.h).
