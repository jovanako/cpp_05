#include "Bureaucrat.hpp"
#include "Colors.hpp"

void testBureaucrat(const std::string& name, int grade) {
	std::cout << CYAN << "\n--- Testing creation of " << name << " with grade " << grade << " ---" << RESET << std::endl;
	try {
		Bureaucrat b(name, grade);
		std::cout << GREEN << "Successfully created: " << b << RESET << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << RED << "Exception caught during construction: " << e.what() << RESET << std::endl;
	}
}

int main() {
	// 1. Valid Instantiations
	std::cout << BOLD_WHITE << "\n--- Testing Valid Instantiations ---" << RESET << std::endl;
	testBureaucrat("Alice", 1);
	testBureaucrat("Bob", 150);
	testBureaucrat("Charlie", 75);

	// 2. Invalid Instantiations (Exceptions expected)
	std::cout << BOLD_WHITE << "\n--- Testing Invalid Instantiations ---" << RESET << std::endl;
	testBureaucrat("B Too High", 0);
	testBureaucrat("B Too Low", 151);

	// 3. Testing Increments & Decrements
	std::cout << BOLD_WHITE << "\n--- Testing Increment Exception ---" << RESET << std::endl;
	try {
		Bureaucrat high("Best", 1);
		std::cout << GREEN << high << RESET << std::endl;
		std::cout << YELLOW << "Attempting to increment grade..." << RESET << std::endl;
		high.incrementGrade(); // Should throw GradeTooHighException
	}
	catch (const std::exception& e) {
		std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
	}

	std::cout << BOLD_WHITE << "\n--- Testing Decrement Exception ---" << RESET << std::endl;
	try {
		Bureaucrat low("Worst", 150);
		std::cout << GREEN << low << RESET << std::endl;
		std::cout << YELLOW << "Attempting to decrement grade..." << RESET << std::endl;
		low.decrementGrade(); // Should throw GradeTooHighException
	}
	catch (const std::exception& e) {
		std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
	}

	// 4. Orthodox Canonical Form Testing
	std::cout << BOLD_WHITE << "\n--- Testing Copy & Assignment ---" << RESET << std::endl;
	Bureaucrat original("Original", 42);
	std::cout << GREEN << original << RESET << std::endl;

	Bureaucrat copy(original);
	std::cout << GREEN << copy << RESET << std::endl;
	
	Bureaucrat assigned("Assigned", 100);

	std::cout << YELLOW << "Before assignment: " << RESET << GREEN << assigned << RESET << std::endl;
	assigned = original;
	std::cout << YELLOW << "After assignment: " << RESET << GREEN << assigned << RESET << std::endl;

	return 0;
}