#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat {
	private:
		std::string const _name;
		int _grade;
	public:
		Bureaucrat();
		Bureaucrat(std::string const & name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat & operator=(const Bureaucrat& other);
		~Bureaucrat();

		std::string getName() const;
		int getGrade() const;

		void incrementGrade();
		void decrementGrade();
		void signForm();

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Grade is too high! Maximum grade is 1.";
				}
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Grade is too low! Minimum grade is 150.";
				} 
		};
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif