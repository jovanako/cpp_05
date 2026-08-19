#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
	: _name("Unknown"),
	  _isSigned(false),
	  _gradeToSign(150),
	  _gradeToExecute(150) {
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw Form::GradeTooLowException();
}

Form::Form(std::string const & name, int gradeToSign, int gradeToExecute)
	: _name(name),
	  _isSigned(false),
	  _gradeToSign(gradeToSign),
	  _gradeToExecute(gradeToExecute)
{
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form& other)
	: _name(other._name),
	  _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign),
	  _gradeToExecute(other._gradeToExecute) {}

Form & Form::operator=(const Form& other) {
	if (this != &other)
		this->_isSigned = other._isSigned;
	return *this;
}

Form::~Form() {}

std::string Form::getName() const {
	return _name;
}

bool Form::getIsSigned() const {
	return _isSigned;
}

int Form::getGradeToSign() const {
	return _gradeToSign;
}

int Form::getGradeToExecute() const {
	return _gradeToExecute;
}

void Form::beSigned(Bureaucrat const & bureaucrat) {
	if (bureaucrat.getGrade() <= _gradeToSign)
		_isSigned = true;
	else
		throw Form::GradeTooLowException();
}

std::ostream& operator<<(std::ostream& os, const Form& form) {
	os << "Form: " << form.getName()
	   << ", Signed: " << (form.getIsSigned() ? "yes" : "no")
	   << ", Grade required to sign: " << form.getGradeToSign()
	   << ", Grade required to execute: " << form.getGradeToExecute() << ".";
	return os;
}