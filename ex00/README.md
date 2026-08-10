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

-	Purpose: Returns a null-terminated C-string (const char*) that describes the error.
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