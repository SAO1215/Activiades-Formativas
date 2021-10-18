# Análisis de complejidad temporal (Big-O)

## push

**Análisis de complejidad temporal**

Esta funcion añade un elemento en el arbol, sin embargo no necesita recorrerlo por completo sino que se depende del nivel en el que este, por lo que su complejidad es de O(log(n)).

## pop

**Análisis de complejidad temporal**

Esta funcion quita un elemto en el arbol, por lo que al igual que el metodo anterior no debe recorrerlo entero sino por nivel, por lo que su complejidad es de O(log(n)).

## top

**Análisis de complejidad temporal**

Esta funcion regresa el dato de mayor prioridad en el arbol, solo usa una operacion y es constante en todos los casos, asi que su complejidad es de O(1).

## empty

**Análisis de complejidad temporal**

Esta funcion verifica que este vacio, igualando el contador a 0, es solo una operacion, por lo que su complejidad es de O(1) en el peor de los casos.

## size

**Análisis de complejidad temporal**

Esta funcion obtiene cuanto lugares esta ocupando el arbol actual, en terminos practicos se trata de un getter ya que esa información ya esta en el arbol, y su complejidad es de O(1). 
