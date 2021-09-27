# Análisis de complejidad temporal (Big-O)

## insertion

**Análisis de complejidad temporal**
Este algoritmo consiste en añadir un elemento en la lista, ya que debe recorrerla hasta el final para hacerlo, por lo que su complejidad en el peor de los casos es de O(n), sin embargo si el valor que desea añadir se encuentra en la primera posición su complejidad seria O(1), ya que es constante.

## search

**Análisis de complejidad temporal**
Este algoritmo recorre la lista uno a uno hasta dar con el valor que se busca y regresa su posición, por lo que su complejidad en el peor de los casos es O(n); si el valor buscado se encuentra en la primera posición de la lista su complejidad cambia a O(1) ya que no tiene que recorrerla mas.

## update

**Análisis de complejidad temporal**
En este algoritmo se remplaza el valor dado por un valor nuevo según donde se encuentre, su complejidad es de O(n) en el peor de los casos.

## deleteAt

**Análisis de complejidad temporal**
Este algoritmo recorre la lista hasta llegar al valor a eliminar y eliminarlo, por lo que su complejidad es de O(n) en el peor de los casos.
