# `std::exception`

In C++, `std::exception` is the standard base class for all standard exceptions
thrown by C++ runtime operations and the standard library. It is defined in the
`<exception>` header.

Understanding `std::exception` is essential for writing robust, fail-safe code
and implementing good error-handling design in C++.


## What is `std::exception`?

When a runtime error occurs (e.g. failing to allocate memory, out-of-bounds
array access, or a custom logical error), C++ uses the exception handling 
mechanism (`try`, `catch`, `throw`) to deal with it.

`std::exception` serves as the root class for standard exceptions. Because C++
supports polymorphism, you can catch any standard exception - or custom
exceptions derived from it - by catching a reference to `std::exception`.

```
try {
	// Code that might throw an exception
}
catch (const std::exception& e) {
	// Catches std::bad_alloc, std::out_of_range, or any custom derived exception
	std::cerr << "Caught exception: " << e.what() << '\n';
}
```


## The `what()` Member Function

The core method provided by `std::exception` is `what()`.

`virtual const char* what() const throw();`

-	Purpose: Returns a null-terminated C-string (`const char*`) that describes the error.
-	`const`: Calling `what()` does not modify the exception object.
-	`throw()`: Guarantees that `what()` itself will never throw an exception while 
	reporting an error.


## The C++ Exception Hierarchy

The standard library builds a whole family of exception types on top of `std::exception`.
Here are some of the most common standard subclasses:

```
std::exception
	|---std::logic_error	(Errors detectable before runtime, e.g. invalid arguments)
	|	|---std::invalid_argument
	|	|---std::out_of_range
	|	|---std::length_error
	|
	|---std::runtime_error	(Errors detectable only at runtime)
		|---std::overflow_error
		|---std::underflow_error
		|---std::range_error
```

Other notable exceptions directly inheriting from `std::exception`:

-	`std::bad_alloc`: Thrown by `new` when memory allocation fails.
-	`std::bad_cast`: Thrown by `dynamic_cast` on reference types when a cast fails.


## Creating Custom Exceptions

When building your own classes, you create custom exception classes by inheriting
from `std::exception` and overriding the `what()` method.

Example:

```
#include <iostream>
#include <exception>

class GradeTooLowException : public std::exception {
	public:
		//Override the what() function
		virtual const char* what() const throw() {
			return "Grade is too low! Minimum grade is 150.";
		}
};

int main() {
	try {
		throw GradeTooLowException();
	}
	catch (const std::exception& e) {
		// Polymorphism allows us to catch GradeTooLowException as std::exception
		std::cout << "Error: " << e.what() << std::endl;
	}
	return 0;
}
```

`virtual const char* what() const throw();`
// throw(): an exception specification promising that this what() function itself will never throw an exception when called


## Best Practices

1.	**Catch by Reference (`const std::exception&`):**
	Always catch exceptions by `const` reference. Catching by value causes object slicing, 
	which destroys the derived class information and prevents polymorphic behavior
	(calling the wrong `what()`).

2.	**Never throw in `what()`:**
	Overriden `what()` methods should strictly avoid throwing new exceptions.

3.	**Inherit when appropriate:**
	When creating custom domain exceptions for your applications, deriving from
	`std::exception` (or `std::runtime_error`) ensures seamless integration with
	standard exception handling code.


## What is `throw`?

In C++, the `throw` keyword is the signal that launches an exception.

When you write:

`throw GradeTooLowException();`

Two distinct actions happen in a single line:

### 1.	Object Creation (GradeTooLowException())
The second half of the statement, `GradeTooLowException()`, invokes the constructor of your custom class to create a temporary object (an instance) of `GradeTooLowException`.

### 2. Execution Interruption & Transfer (`throw`)
The `throw` keyword takes that temporary object and immediately:
1. **Halts Normal Flow:** Stops the execution of the current function right at that exact line. No subsequent lines of code in that function or block will execute.

2. **Begins Stack Unwinding:** The runtime unwinds the call stack, destroying local variables in reverse order of their creation until it finds a matching `catch` block up the chain.

3. **Passes the Payload:** Handshakes the created `GradeTooLowException` object to the matching `catch` block (e.g., `catch (const std::exception& e)`), allowing you to handle the error gracefully.

## Visual Analogy

Think of `GradeTooLowException()` as **filling out an incident report**, and `throw` as **pulling the fire alarm** while handling that report to emergency responders.

- Without `throw`: You just create an object in memory that sits there doing nothing:
```
GradeTooLowException();
// Creates an object, then immediately destroys it. No error is triggered.
```

- With `throw`: You trigger the C++ exception-handling mechanism using that object as the error details.

# Why Copy Assignment Operator copies only `_grade` and not `_name`

## 1. `const` Variables Cannot Be Reassigned

In C++, a variable marked `const` is strictly read-only once constructed. The copy assignment operator (`operator=`) is called on an object that **already exists in memory**:

```
Bureaucrat a("Alice", 10);
Bureaucrat b("Bob", 50);

a=b; // 'a' already exists; its '_name' is already "Alice"
``` 

If you try to write:

`this->_name = other._name; // COMPILATION ERROR`

The compiler will reject the code because `std::string::operator=` cannot be invoked on a `const` object.

## 2. Constructors vs. Assignment Operator

- **In Constructors (and Copy Constructor)**: The object is being created for the first time. You can initialize `_name` using the **member initializer list** (`: _name(other._name)`).

- **In Assignment Operator** (`operator=`): The object is already fully constructed. You are modifying existing values, so `const` members cannot be changed.

## 3. The Conceptual Meaning in the Exercise

From the design perspective, a `Bureaucrat` represents an individual whose **identity** (`_name`) **is fixed for life**, while their **rank** (`_grade`) **can change**. When you assign one bureaucrat to another, you are copying their status/grade, not overriding their personal identity.


# Why is `what()` defined in the `.hpp` file?

## 1. Header-only Exception Inline Definition

In C++, methods whose implementations are written directly inside the class definition (inside the `.hpp` file) are **automatically treated as** `inline` **functions** by the compiler.

Because `what()` in this context is extremely simple - it just returns a hardcoded string literal - inlining it allows the compiler to insert that string pointer directly where called, avoiding the minor overhead of a function call.

## 2. Avoiding Linker Redundancy (ODR Compliance)

If you declare a function in a header without `inline` or without implementing it inside the class body, and then put its definition in a `.cpp` file, you must compile and link that `.cpp` file.

When defined inside the `.hpp` class body, multiple `.cpp` files can `#include "Bureaucrat.hpp"` without violating the **One Definition Rule(ODR)**, because inline functions defined inside class bodies are explicitly permitted across translation units.

## 3. C++ Module 05 Exception Exemption

The C++ Module 05 specification explicitly states:

>"Please note that exception classes do not have to be designed in Orthodox Canonical Form."

While standard classes in the 42 curriculum generally mandate separating declarations (`.hpp`) from implementations (`.cpp`), exception classes are specifically granted an exemption.  
Keeping lightweight, self-contained exception classes entirely in the header is standard C++ practice because it keeps error definitions self-contained and clean.