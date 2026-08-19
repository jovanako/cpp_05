#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class Form {
	private:
		std::string const _name;
		bool _isSigned;
		int const _gradeToSign;
		int const _gradeToExecute;
	public:
		Form();
		Form(std::string const & name, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		Form & operator=(const Form& other);
		~Form();

		std::string getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		void beSigned(Bureaucrat const & bureaucrat);

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

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif