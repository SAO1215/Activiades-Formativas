# Análisis de complejidad temporal (Big-O)

## Put

**Análisis de complejidad temporal**

Esta función inserta elementos a una tabla de hash con prueba cuadrática, normelmente su complejida es de O(1) pero a medida se va llenando la tabla necesita iterar a través de cada valor hasta encontar un sitio (colisiones pues), por lo que su complejidad será de O(n) para el peor de sus casos.

## Get

**Análisis de complejidad temporal**

Esta función obtiene el elemento asociado a la llave dentro de la tabla hash, su complejidad es igual O(n).