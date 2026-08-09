#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>

class Bureaucrat {
	private:
		std::string const _name;
		int _grade;
	public:
		Bureaucrat();
		Bureaucrat(std::string const name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat & operator=(const Bureaucrat& other);
		~Bureaucrat();

		std::string const getName() const;
		int getGrade() const;
		int incrementGrade(int grade);
		int decrementGrade(int grade);
};

#endif