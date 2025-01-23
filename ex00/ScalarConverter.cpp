#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string &literal) {
	if (literal.empty()) {
		std::cout << "Error: Empty input" << std::endl;
		return;
	}

	if (literal == "nan" || literal == "nanf" ||
		literal == "+inf" || literal == "+inff" ||
		literal == "-inf" || literal == "-inff" ||
		literal == "inf" || literal == "inff") {
		handleWordLits(literal);
		return;
	}

	if (literal.length() == 1 && !isdigit(literal[0])) {
		convertFromChar(literal[0]);
		return;
	}

	if (isInt(literal)) {
		char *end;
		long long tmp = std::strtoll(literal.c_str(), &end, 10);
		if (*end != '\0' || tmp > std::numeric_limits<int>::max() ||
			tmp < std::numeric_limits<int>::min()) {
			std::cout << "Error: Integer overflow" << std::endl;
			return;
		}
		convertFromInt(static_cast<int>(tmp));
		return;
	}

	if (isFloat(literal)) {
		float value = std::atof(literal.c_str());
		convertFromFloat(value);
		return;
	}

	size_t firstDot = literal.find('.');
	size_t lastDot = literal.rfind('.');
	if (firstDot != std::string::npos && firstDot == lastDot && literal[literal.length() - 1] != 'f') {
		double value = std::atof(literal.c_str());
		convertFromDouble(value);
		return;
	}

	std::cout << "Error: Invalid input" << std::endl;
}

bool ScalarConverter::isChar(const std::string &literal) {
	return (literal.length() == 1 && !isdigit(literal[0]));
}

bool ScalarConverter::isInt(const std::string &literal) {
	size_t i = 0;
	if (literal[0] == '+' || literal[0] == '-')
		i++;
	for (; i < literal.length(); i++) {
		if (!isdigit(literal[i]))
			return false;
	}
	return true;
}

bool ScalarConverter::isFloat(const std::string &literal) {
	if (literal[literal.length() - 1] != 'f')
		return false;

	std::string numPart = literal.substr(0, literal.length() - 1);
	size_t pos = 0;

	try {
		std::stod(numPart, &pos);
		return pos == numPart.length();
	} catch (...) {
		return false;
	}
}

bool ScalarConverter::isDouble(const std::string &literal) {
	if (literal == "-inf" || literal == "+inf" || literal == "inf" || literal == "nan")
		return true;

	size_t pos = 0;
	try {
		std::stod(literal, &pos);
		return pos == literal.length();
	} catch (...) {
		return false;
	}
}

void ScalarConverter::convertFromChar(const char value) {
	std::cout << "char: '" << value << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(value) << std::endl;
	std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void ScalarConverter::convertFromInt(const int value) {
	if (value >= 32 && value <= 126)
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << value << std::endl;

	std::cout << "float: ";
	if (std::abs(static_cast<double>(value)) >= 1e6)
		std::cout << std::scientific << std::setprecision(5) << static_cast<float>(value) << "f";
	else
		std::cout << value << ".0f";
	std::cout << std::endl;

	std::cout << "double: ";
	if (std::abs(static_cast<double>(value)) >= 1e6)
		std::cout << std::scientific << std::setprecision(5) << static_cast<double>(value);
	else
		std::cout << value << ".0";
	std::cout << std::endl;
}

void ScalarConverter::convertFromFloat(const float value) {
	if (value >= 32 && value <= 126 && value == static_cast<int>(value))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	if (value > std::numeric_limits<int>::max() ||
		value < std::numeric_limits<int>::min() ||
		std::isnan(value))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;

	std::cout << "float: ";
	if (std::abs(value) < 1000000) {
		std::cout << value;
		if (value == static_cast<int>(value))
			std::cout << ".0";
	} else {
		std::cout.precision(6);
		std::cout << std::scientific;
		std::cout << value;
		std::cout.unsetf(std::ios::scientific);
	}
	std::cout << "f" << std::endl;

	std::cout << "double: " << static_cast<double>(value);
	if (value == static_cast<int>(value))
		std::cout << ".0";
	std::cout << std::endl;
}

void ScalarConverter::convertFromDouble(const double value) {
	if (value >= 32 && value <= 126 && value == static_cast<int>(value))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	if (value > std::numeric_limits<int>::max() ||
		value < std::numeric_limits<int>::min() ||
		std::isnan(value))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;

	std::cout << "float: ";
	if (std::isnan(value)) std::cout << "nanf";
	else if (std::isinf(value)) std::cout << (value < 0 ? "-inff" : "+inff");
	else if (value == 0.0) std::cout << "0.0f";
	else {
		const bool useScientific = std::abs(value) >= 1e6 || (value != 0 && std::abs(value) < 1e-3);
		if (useScientific) {
			std::cout << std::scientific << std::setprecision(5) << static_cast<float>(value) << "f";
		} else {
			std::string strValue = std::to_string(value);
			size_t decimalPos = strValue.find('.');
			size_t precision = 1;
			if (decimalPos != std::string::npos) {
				size_t lastNonZero = strValue.find_last_not_of('0');
				if (lastNonZero > decimalPos) {
					precision = lastNonZero - decimalPos;
				}
			}
			std::cout << std::fixed << std::setprecision(precision) << static_cast<float>(value) << "f";
		}
	}
	std::cout << std::endl;

	std::cout << "double: ";
	if (std::isnan(value)) std::cout << "nan";
	else if (std::isinf(value)) std::cout << (value < 0 ? "-inf" : "+inf");
	else if (value == 0.0) std::cout << "0.0";
	else {
		const bool useScientific = std::abs(value) >= 1e6 || (value != 0 && std::abs(value) < 1e-3);
		if (useScientific) {
			std::cout << std::scientific << std::setprecision(5) << value;
		} else {
			std::string strValue = std::to_string(value);
			size_t decimalPos = strValue.find('.');
			size_t precision = 1;
			if (decimalPos != std::string::npos) {
				size_t lastNonZero = strValue.find_last_not_of('0');
				if (lastNonZero > decimalPos) {
					precision = lastNonZero - decimalPos;
				}
			}
			std::cout << std::fixed << std::setprecision(precision) << value;
		}
	}
	std::cout << std::endl;
}

void ScalarConverter::handleWordLits(const std::string &literal) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;

	if (literal == "nan" || literal == "nanf") {
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	} else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff") {
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	} else {
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}