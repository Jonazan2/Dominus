# Dominus

Dominus is an opensource strategy game developed from scratch using C++ and OpenGL.

# Goal
Dominus has started been developed for MAC OS but will be released in Windows and Linux as well.
  
# Code style conventions

Dominu's code must follow the next code style:

* _Braces_
  * Braces must be use in every statement that needs them: if, else, functions, structures, typedefs, classes and enums.
  * Braces start at the end of the method's signature.
  * The else statement starts on the same line as the last closing brace.
  
```cpp
if ( value ) {
  ...
} else {
  ...
}

void Class::function() {
  ...
  ...
}
```
  
* _Spacing_
  * Use real tabs that equal four spaces.
  * Parenthesis must have an space before and after their declaration.

```cpp
if ( value > 10 ) {
  value = ( ( value * 3 ) / 6 );
}

void Class::function( int ) {
  ...
  ...
}
```

* _Naming conventions_
  * Functions must always start with a lower case.
  * Classes must always start with a capital case. The files that contains them must have the same name.
  * Enums start with a capital case and enum members are always capital separated by underscores.
  * Variables start with a lower case.
  * Constants must be always capital separated by underscores.
  * In case of multiple words for a name, it should follow camel case.
  
```cpp

#define MIN_SIZE = 3;
const short MAX_SIZE = 10;

class Point {
  ...
  ...
};

void Class::anotherFunction() {
  int variable;
  ...
}

enum Flags {
  ZERO_FLAG,
  NULL_FLAG,
  ...
}
```

* _Const_
  * Use const always that is possible.
  * All methods that don't change their object state must be followed by const.

```cpp

class Point {
  ...
  ...
};

void Point::anotherFunction( const int x, int x2 ) {
  // x2 will not be change inside this function
  ...
}

void Point::example( int x, int x2 ) const {
  // All members of this object will remain the same
  ...
}
```

* _Class order_
  1. List of associated classes
  2. public variables
  3. public methods
  4. protected variables
  5. protected methods
  6. private variables
  7. private methods

* _Documentation and comments_
  * Avoid useless comments in getters, setters and small methods.
  * Use doxygen compatible headers for classes that must include: date of last change, contributors and description. This documentation will be located in the header file.
  * Use doxygen compatible headers for functions that must include: description, parameters and return explanation. This documentation will be located in the implementation file.


```cpp  
/** 
 *  \brief     Pretty nice class.
 *  
 *  \author    John Doe
 *  \author    Jan Doe
 *  \date      26/01/2016
 */
class Point {
  ...
};

/**
 * Copies bytes from a source memory area to a destination memory area,
 * where both areas may not overlap.
 
 * @param[out] dest The memory area to copy to.
 * @param[in]  src  The memory area to copy from.
 * @param[in]  n    The number of bytes to copy
 */
void Point::memoryCopy( void *dest, const void *src, size n );
```

* Namespaces
  * Don´t use global using
  * Use namespace::method for clarity

```cpp  
~Foo() {
   std::cout << "static destructor\n";
}
```

# Dependencies

Dominus is using *OpenGL* (ver 4.1.x) and *GLFW*. While OpenGL is included in Xcode development kit, we need to install GLFW for Mac OS manually.

### How to install GLFW

GLFW can be installed using brew with the next commands:

```shell
brew tap homebrew/versions
brew install glfw
```

After this the project will look for the library at /usr/local/ which is already included in the build path.

### How to install GLM

GLM can be installed using brew with the next commands:

```shell
brew tap homebrew/versions
brew install glm
```

After this the project will look for the library at /usr/local/ which is already included in the build path.
