# Análisis de complejidad temporal (Big-O)

## add

**Análisis de complejidad temporal**

Esta funcion añade un elemento en el arbol,  su complejidad es de O(log(n)) ya que no necesita recorrer todo el arbolo sino que divide este proceso y va por niveles.

## remove

**Análisis de complejidad temporal**

Esta funcion elimina un elemento, para esto no recorre uno a uno sino que como la función anterior se va dividiendo el trabajo por lo que su complejidad es de O(log(n)).

## find

**Análisis de complejidad temporal**

Esta funcion verifica un elemento exista, para esto no va comparando el valor con todos los elemetos de arbol sino que de va guiando por el valor para hacer su recorrido, su complejidad es de O(log(n)).

## size

**Análisis de complejidad temporal**

Esta funcion obtiene el total de elementos en el arbol actual su complejidad es de O(1) ya que solo realiza una operacion. 