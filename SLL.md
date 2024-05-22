## Documentación de Lista Ligada Sencilla

### Interfaz

---

La interfaz comienza con las directivas del compilador:

```C++
#ifndef SLLLIST_H
#define SLLLIST_H

#include <iostream>
#include <utility>
```

Estas directivas indican el inicio de SLLList.h, archivo en el cual se encuentra la declaración de los elementos de nuestra clase.

En primer lugar, `#ifndef SLLLIST_H` indica al compilador que el bloque de código siguiente solo se deberá compilar si no se ha definido SLLLIST_H. `#define SLLLIST_H` define SLLLIST_H, de tal manera que las primeras dos líneas indican al compilador que si SLLLIST_H no ha sido definido, deberá definirlo y proceder con el código. En segundo lugar, las directivas `#include <iostream>` y `#include <utility>` introducen las librerías de iostream y utility respectivamente.

Iostream es una librería que contiene funciones para controlar el flujo de información que entra y sale del programa através de los métodos estándar, mediante objetos como std::cin y std::cout los cuales leen y escriben a la consola. Utility por otro lado, es un conjunto de librerías que contienen distintas funciones y objetos de todo tipo para realizar tareas comunes. Para este objeto se utilizarán elementos de esta librería como initializer_list, logic_error, entre otros.

Enseguida se declara nuestro objeto, SLLList, el cuál es un template con typename Object para ser utilizado con distintos tipos de dato.

```C++
template<typename Object>
class SLList {
public:
    struct Node {
        Object data;
        Node *next;

        Node(const Object &d = Object{}, Node *n = nullptr);

        Node(Object &&d, Node *n = nullptr);
    };
```

El primer objeto público que se declara es una estructura de nombre Node, la cual se utilizará para contener el dato de tipo Object, así como un puntero que se utilizará para manterner la dirección del siguiente nodo en la lista.

También se declaran 2 constructores. El constructor paramétrico, el cuál toma un objeto del tipo de typename, y un puntero para al nodo siguiente y se usa para copiar el valor de Object. Tiene como defaults un objeto vacío y un nullptr; y el constructor de movimiento con un objeto, el cual cumple el mismo propósito que el constructor de copia, pero en lugar de copiar el objeto, lo mueve directamente.

Enseguida tenemos una subclase pública llamada iterator.

```C++
public:
    class iterator {
    public:
        iterator();

        Object &operator*();

        iterator &operator++();

        const iterator operator++(int);

        bool operator==(const iterator &rhs) const;

        bool operator!=(const iterator &rhs) const;

    private:
        Node *current;

        iterator(Node *p);

        friend class SLList<Object>;
    };
```

Esta subclase se utilizará para controlar los recorridos de la lista.

Contiene un constructor público default, un puntero privado a un nodo y un segundo constructor de iterador, el cual es privado y toma un puntero a un nodo como parámetro. También se declara como clase amiga (friend) lo cual le permitirá accesar los miembros privados y protegidos de la clase SLLList.

Además de esto, se declarán 5 sobrecargas de operadores públicas.

+ `Object &operator*();`: Es una sobrecarga del operador de dereferenciación; se utiliza para obtener el objeto dentro del nodo al que apunta el iterador. Se llama de la siguiente forma `*iterador`.
+ `iterator &operator++();`: Es una sobrecarga del operador de pre-incremento; se utiliza para incrementar el iterador pero retornar una referencia al iterador previa a la incrementación. Se llama de la siguiente forma `++iterador`.
+ `const iterator operator++(int);`: Es una sobrecarga del operador de post-incremento; se utiliza para incrementar el iterador y retornar el valor incrementado. Se llama de la siguiente forma `iterador++`.
+ `bool operator==(const iterator &rhs) const;`: Es una sobrecarga del operador de igualdad; retorna verdadero si el objeto a comparar es igual al objeto comparado. Se llama de la siguiente forma `iterador1 == iterador2`. 
+ `bool operator!=(const iterator &rhs) const;`: Es una sobrecarga del operador de desigualdad; retorna verdadero si el objeto a comparar es diferente al objeto comparado. Se llama de la siguiente forma `iterador1 == iterador2`.  

Los dos últimos dos operadores toman una referencia de lvalue a otro iterador como parámetro (el iterador a comparar). El operador de post-incremento toma un entero como parámetro, este entero no sirve ningún propósito programático en el lenguaje como tal, sin embargo es necesario ya que en C++ no existe una forma de diferenciar dos sobrecargas de la misma función, método u operador basado simplemente en el tipo de dato que retorna. Por lo tanto, el compilador necesita ese parámetro "falso" para diferenciar ambas sobrecargas.

La siguiente sección declara todos los métodos públicos de nuestra clase.
Primero los constructores y el destructor:

```C++
SLList();

SLList(std::initializer_list <Object> init_list);

~SLList();
```

Se declara un constructor default, un constructor parámetrico el cual toma como parámetro un `std::initializer_list` de tipo Object, el cual simplemente provee accesso a un arreglo de objetos de tipo Object que se utilizará para inicializar nuestra lista; y el destructor default.

Después declaramos nuestros métodos:

```C++
iterator begin();

iterator end();
```

Los métodos `iterator begin();` y `iterator end();` se utilizarán para retornar los iteradores al primer y último elemento de la lista respectivamente.

```C++
int size() const;
```

Se utiliza para retornar el tamaño de la lista.

```C++
bool empty() const;
```

Retorna verdadero si la lista esta vacía.

```C++
void clear();
```

Desaloja todos los nodos de la lista y los destruye, efectivamente "limpiando" la lista.

```C++
Object &front();
```

Retorna una referencia al objeto al frente de la lista.

```C++
void push_front(const Object &x);
```

Toma como parámetro una referencia de lvalue a un objeto de tipo Object y pone una copia al frente de la lista.

```C++
void push_front(Object &&x);
```

Toma como parámetro una referencia de rvalue a un objeto de tipo Object y lo mueve al frente de la lista.

```C++
void pop_front();
```

Destruye el primer elemento de la lista.

```C++
iterator insert(iterator itr, const Object &x);

iterator insert(iterator itr, Object &&x);
```

Se utilizan para insertar el objeto dado por el segundo parámetro en algún punto de la lista que será dado por el parámetro `iterator itr`. El primer método inserta una copia al objeto dado y el segundo mueve el objeto.

```C++
iterator erase(iterator itr);
```

Se utiliza para eliminar el objeto al que apunta el iterador dado por el parámetro.

```C++
void print();
```

Se utiliza para imprimir la lista.

---
Por último se declaran los elementos privados de SLLList.

```C++
private:
    Node *head;
    Node *tail;
    int theSize;

    void init();
};
```

Dos nodos, head y tail, los cuales contienen al primer y último objeto en la lista respectivamente, el tamaño de la lista guardado en `int theSize;` y un método privado llamado `init()` que se utilizará para inicializar nuestra lista.

Las últimas dos líneas son directivas del compilador:

```C++
#include "SLList.cpp"
#endif
```

La primera simplemente incluye dentro del programa el cpp con la implementación de nuestra clase y la segunda termina el bloque de implmentación iniciado por `#ifndef SLLLIST_H` al inicio del archivo.

Es importante mencionar, que incluir explicitamente el archivo de implementación dentro de nuestra interfaz es considerado una mala práctica por las siguientes razones: 
+ **Separación de intereses:** Separar nuestra implementación de nuestra interfaz en primer lugar se hace con el propósito de permitir utilizar distintas implementaciones facilmente dependiendo del ambiente. Incluir explicitamente la implementación tiene la posibilidad de romper con este principio.
+ **Legibilidad:** A no ser que cambiemos el código de nuestro archivo de interfaz cada vez que lo compilemos con una implementación distinta, esto limita nuestras implementaciones a el mismo nombre. Incluso en situaciones en las que solo una implementación es necesaria, el proceso de obtener dicha implementación en primer lugar se dificulta cuando todas las implementaciones tienen el mismo nombre.
+ **Mantenimiento:** Como principio se debe minimizar la cantidad de veces que se cambia una interfaz. En otras palabras, debe estar abierta a extension pero cerradad a modificación. No es ideal tener que modificar el código cuando se desee escribir una implementación alternativa.
+ **Posible Error de Compilación:** Es posible que el linker encuentre conflictos, debido a que al usar implementaciones en distintos archivos pero incluirla explicitamente se pueden generar multiples definiciones de los mismos elementos declarados lo cual no permitirá la compilación.
+ **Eficacia de Compilación:** Es posible que en situaciones en las que no existan errores de compilación, siga representando un gasto innecesario de recursos al obligar al compilador a procesar datos repetidos.

Con los archivos dados para la tarea, el programa no compila (revisado utilizando g++ en wsl con openSUSE-Tumbleweed) debido a errores de redefinición.

Remover la directiva arregla el problema.

### Implementación

---

La primera línea, `#include "SLLList.h"` incluye en nuestro código la interfaz. Siguiente a esto se definen los métodos y sobrecargas declaradas en nuestro header.

La primer definición es para el constructor de copia de nuestra estructura nodo.
Es un templete con typename Object. Utiliza la sintáxis de lista de inicialización para asignar los parámetros del constructor a los miembros de nuestra estructura.

```C++
template<typename Object>
SLList<Object>::Node::Node(const Object &d, Node *n)
        : data{d}, next{n} {}
```

La siguiente definición es para el constructor de movimiento de nuestra estructura nodo.
Es un templete con typename Object. Utiliza la sintáxis de lista de inicialización para asignar los parámetros del constructor a los miembros de nuestra estructura de igual forma que el constructor de copia, pero en lugar de simplemente asignar el valor de nuestro dato, lo mueve completamente con `std::move`.

```C++
template<typename Object>
SLList<Object>::Node::Node(Object &&d, Node *n)
        : data{std::move(d)}, next{n} {}
```

El próximo es el constructor default de nuestra subclase iterator. Utiliza la sintáxis de lista de inicialización para declarar el puntero actual como `nullptr`.

```C++
template<typename Object>
SLList<Object>::iterator::iterator() : current{nullptr} {}
```

A continuación nuestra primer sobrecarga de operador. El operador de dereferenciación de nuestra subclase iterator. Simplemente retorna el dato al que apunta nuestro puntero actual. Pero antes revisa si el puntero esta vacío (nullptr) para lanzar un error en su lugar que nos indique que el puntero esta vacío.

```C++
template<typename Object>
Object &SLList<Object>::iterator::operator*() {
    if(current == nullptr)
        throw std::logic_error("Trying to dereference a null pointer.");
    return current->data;
}
```

El siguiente es el operador de pre-incremento. Recordemos que `current` guarda un puntero al nodo actual; si `current` no contiene un puntero al siguiente nodo, o en otras palabras, si no existe un siguiente nodo en nuestra lista, queremos arrojar otro error que nos indique que ya estamos en el último elemento y no se puede incrementar. Por tanto debemos revisar si existe un nodo siguiente al que podamos movernos. Para este propósito podemos utilizar `current->next`, si este valor retorna nullptr (que se considera un "falsy value" o valor que se trata como `false`) entonces nuestro if no moverá el iterador al siguiente puntero, y en su lugar nos arrojará nuestro error.

Actualmente el código contiene un `if` que revisa si el valor de `current` es "falsy", esto muy posiblemente no es la implementación planeada, en lugar de eso, `if(current->next)` es probablemente la implementación deseada (`print()` no funciona apropiadamente de otra forma (probado con g++ en wsl-tumbleweed)). 

El operador retorna el iterador mediante el uso de `*this` derreferenciado (this es un puntero al objeto actual, por lo que esto retorna el objeto actual).

```C++
template<typename Object>
typename SLList<Object>::iterator &SLList<Object>::iterator::operator++() {
    if(current)
        current = current->next;
    else
        throw std::logic_error("Trying to increment past the end.");
    return *this;
}
```

A continuación el operador de post-incremento. Este simplemente utiliza el operador que ya habíamos declarado previamente para incrementar nuestro iterador. Antes de eso se copia el iterador anterior a un nuevo objeto y se retorna después de la incrementación.

```C++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
}
```

Las siguientes dos sobrecargas van de la mano, la primera sobrecarga el operador `==` para regresar verdadero si los punteros actuales del objeto a comparar y el objecto comparado son iguales. El segundo regresa falso en dicho caso, pero utiliza el operador ya definido.

```C++
template<typename Object>
bool SLList<Object>::iterator::operator==(const iterator &rhs) const {
    return current == rhs.current;
}

template<typename Object>
bool SLList<Object>::iterator::operator!=(const iterator &rhs) const {
    return !(*this == rhs);
}
```

El siguiente es el constructor paramétrico del iterador:

```C++
template<typename Object>
SLList<Object>::iterator::iterator(Node *p) : current{p} {}
```

Toma un puntero a un nodo como parámetro y construye el iterador asignando dicho puntero a `current`.

Después vienen los constructores y el destructor de SLList:

```C++
template<typename Object>
SLList<Object>::SLList() : head(new Node()), tail(new Node()), theSize(0) {
    head->next = tail;
}

template<typename Object>
SLList<Object>::SLList(std::initializer_list <Object> init_list) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    theSize = 0;
    for(const auto& x : init_list) {
        push_front(x);
    }
}

template<typename Object>
SLList<Object>::~SLList() {
    clear();
    delete head;
    delete tail;
}
```

El primer constructor no toma parámetros, y simplemente crea nuevos nodos para el primer y segundo elementos. Y asigna el último elemento `tail` al segundo elemento `head->next`.

El segundo constructor toma como parámetro una lista de inicialización. Se crean los nodos como en el constructor default, y se llama al método push_front para llenar el resto de elementos de la lista.

El destructor llama el método `clear()` para limpiar la lista y después elmina head y tail para destruir el arreglo sin pérdida de memoria.

A continuación algunos métodos misceláneos:

```C++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::begin() { return {head->next}; }

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::end() { return {tail}; }

template<typename Object>
int SLList<Object>::size() const { return theSize; }

template<typename Object>
bool SLList<Object>::empty() const { return size() == 0; }

template<typename Object>
void SLList<Object>::clear() { while (!empty()) pop_front(); }
```

+ El primer método, `begin()` retorna `head->next`, el primer nodo que contiene un dato debido a que head y tail siempre estan vacíos.
+ El segundo, `end()`, retorna tail para propósitos de iteración externa. 
+ El siguiente, `size()` simplemente retorna el tamaño (guardado en el miembro `theSize`) y `empty()` retorna verdadero si `size()` es igual a 0.
+ Por último `clear()` simplemente llama `pop_front()` hasta que `empty()` sea verdadero.

El siguiente método es `front()`:

```C++
template<typename Object>
Object &SLList<Object>::front() {
    if(empty())
        throw std::logic_error("List is empty.");
    return *begin();
}
```

Como se puede observar, si el arreglo no esta vacío, retorna el primer elemento dereferenciado.

Los siguientes dos métodos nuevamente van de la mano:

```C++
template<typename Object>
void SLList<Object>::push_front(const Object &x) { insert(begin(), x); }

template<typename Object>
void SLList<Object>::push_front(Object &&x) { insert(begin(), std::move(x)); }
```

Utilizan el método `insert()` para insertar un elemento en el nodo retornado por `begin()`. La diferencia entre los dos nuevamente, es que el primero lo hace copiando el valor del objeto que se esta pasando mientras que el segundo lo hace moviendo el objeto directamente.

De igual manera `pop_front()` hace uso del método `erase()` para eleminar el primer elemento de la lista (dado por `begin()`):

```C++
template<typename Object>
void SLList<Object>::pop_front() {
    if(empty())
        throw std::logic_error("List is empty.");
    erase(begin());
}
```

Los próximos dos métodos nuevamente son sobrecargas del mismo método:

```C++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, const Object &x) {
    Node *p = itr.current;
    Node *newNode = new Node{x, p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, Object &&x) {
    Node *p = itr.current;
    Node *newNode = new Node{std::move(x), p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}
```

El método `insert()` crea un nuevo puntero para guardar el actual, crea un nuevo nodo utilizando el constructor de nodo paramétrico y le asigna tanto "x" (el nuevo objeto) como el puntero al siguiente nodo. Después cambia el valor de next del nodo actual al puntero al nuevo nodo; aumenta `theSize` para mantener registro del tamaño de la lista y retorna como resultado un iterador que apunta al nuevo nodo.

La diferencia principal entre estos dos métodos es simplemente que el método `insert()` por copia, copia el valor del objeto, mientras que el método por movimiento lo mueve con std::move.

Es importante mencionar que este método de inserción no funciona correctamente cuando se utiliza `push_front()` en un arreglo nuevo (o en cualquier situación en que tail es igual a `p`), esto debido a que si el iterador que se le da apunta a tail, se estará agregando un nuevo nodo a la lista que sigue después de tail, ya que tail es `p` pero a pesar de que se ajusta su valor de next `p->next = newNode` no se ajusta el valor tail. Esto significa que los elementos nuevos se añanden enseguida de tail y por tanto el resto de métodos, los cuales asumen que tail es el último nodo de la lista, no funcionarán apropiadamente.

Para mitigar esto una posible solución puede ser la siguiente:

```C++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, const Object &x) {
    Node *p = itr.current;
    Node *newNode;
    newNode = new Node{p->data, p->next};

    if(itr == end()) 
        this->tail = newNode;
    p->data = x;
    p->next = newNode;

    theSize++;
    return iterator(newNode);
}
```

La diferencia es que el nuevo nodo toma el lugar del nodo actual completamente (incluyendo el dato guardado) y el nodo actual toma el nuevo dato y apunta al nodo nuevo. Si el nodo actual era tail, el nuevo nodo (que tomo el lugar del nodo actual) ahora se convierte en el nuevo tail.

A continuación el método `erase()`:

```C++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::erase(iterator itr) {
    if (itr == end())
        throw std::logic_error("Cannot erase at end iterator");
    Node *p = head;
    while (p->next != itr.current) p = p->next;
    Node *toDelete = itr.current;
    p->next = itr.current->next;
    delete toDelete;
    theSize--;
    return iterator(p->next);
}
```

Primero revisa que el iterador actual no sea tail, esto porque tail no es un nodo real que guarda datos, es un nodo posicional usado para estructurar la lista y marcar el fin de la iteración. Si el iterador no apunta a tail, se crea un nodo que se asigna a head.  Después se recorre el arreglo hasta que se llegue a la posición justo antes del iterador actual, esto ya que en una lista ligada no tenemos acceso directo a todos elementos de la lista aleatoriamente, para encontrar elemento antes de nuestro iterador, tenemos que recorrer la lista desde el principio. Una vez que `p->next` sea el iterador que queremos eliminar, simplemente asignamos el valor de `p->next` al valor de `next` del nodo al que apunta nuestro iterador actual, efectivamente eliminando el nodo de la lista. Antes de eso, sin embargo, debemos eliminar el nodo actual, para esto guardamos el puntero al nodo actual y usamos `delete` para eliminarlo (llamando el destructor). Por último recortamos el tamaño que guardamos en `theSize` y retornamos un iterador apuntando al nodo siguiente.

El siguiente método es el método `print()` que se utiliza para imprimir los elementos de la lista:

```C++
template<typename Object>
void SLList<Object>::print() {
    iterator itr = begin();
    while (itr != end()) {
        std::cout << *itr << " ";
        ++itr;
    }
    std::cout << std::endl;
}
```

Como se puede observar, se utiliza un ciclo `while` para iterar nuestra lista (por medio del operador de incremento) y por cada iterador se imprime el valor asignado (mediante el operador de dereferenciación).
Por último se usa `std::endl` para hacer un salto de línea.

El último método, `init()`, inicializa el valor de `theSize` a 0 y el valor de `head->next` a tail.

```C++
template<typename Object>
void SLList<Object>::init() {
    theSize = 0;
    head->next = tail;
}
```

Este método posiblemente fue creado para simplificar la lógica de inicialización en los constructores, pero actualmente no esta en uso.
