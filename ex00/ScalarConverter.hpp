#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>
#include <sstream>

#define MAX_INPUT_LENGTH 20

	class ScalarConverter {
		private:
			ScalarConverter();
			ScalarConverter(const ScalarConverter &other);
			ScalarConverter &operator=(const ScalarConverter &other);
			~ScalarConverter();

			static bool isChar(const std::string &literal);
			static bool isInt(const std::string &literal);
			static bool isFloat(const std::string &literal);
			static bool isDouble(const std::string &literal);

			static void convertFromChar(const char value);
			static void convertFromInt(const int value);
			static void convertFromFloat(const float value);
			static void convertFromDouble(const double value);
			static void handleWordLits(const std::string &literal);

		public:
			static void convert(const std::string &literal);
	};

#endif