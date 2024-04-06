#include "decoder_error.h"

void dop() {
	std::vector<bool> polynome = { 1, 1, 0, 1 }; //g(x) = x^n+ ... + x^2 + 1
	unsigned int r = degree(polynome);

	for (unsigned int len = 5; len < 10; len++) {

		std::cout << "Lenght: " << len << std::endl;

		//Создание кодовой книги
		std::cout << "Code words: " << std::endl;
		std::vector<std::vector<bool>> code_words = create_code_words(polynome, len);
		std::cout << std::endl;

		//Вычисление расстояния Хемминга
		unsigned int d = count_hemming(code_words);
		std::cout << "Hemming: " << d << std::endl;

		//Вычисление весов по кодовой книге
		std::cout << "Weights: " << std::endl;
		std::vector<unsigned int> weights = count_weights(code_words);
		for (size_t i = 0; i < weights.size(); i++)
			std::cout << i << ") " << weights[i] << std::endl;

		std::cout << std::endl;

		std::vector<double> upper_ass;
		std::vector<double> accur_error;

		for (double p = 0.1; p < 0.4; p += 0.1) {
			upper_ass.push_back(count_upper_assessment(len, r, d, p));
			accur_error.push_back(count_accurate_error(weights, len, r, d, p));
		}

		std::cout << "upper = [" << std::endl;
		for (size_t i = 0; i < upper_ass.size(); i++) {
			std::cout << upper_ass[i];
			if (i < upper_ass.size() - 1)
				std::cout << ",";
			std::cout << std::endl;
		}
		std::cout << "]" << std::endl;

		std::cout << "accurate = [" << std::endl;
		for (size_t i = 0; i < accur_error.size(); i++) {
			std::cout << accur_error[i];
			if (i < accur_error.size() - 1)
				std::cout << ",";
			std::cout << std::endl;
		}
		std::cout << "]" << std::endl;

	}
}

int main() {
	std::vector<bool> polynome = {1, 1, 0, 1}; //g(x) = x^n+ ... + x^2 + 1

	unsigned int l = 4;

	unsigned int r = degree(polynome);
	unsigned int len = l + r;

	//Создание кодовой книги
	std::cout << "Code words: " << std::endl;
	std::vector<std::vector<bool>> code_words = create_code_words(polynome, len);
	std::cout << std::endl;

	//Вычисление расстояния Хемминга
	unsigned int d = count_hemming(code_words);
	std::cout << "Hemming: " << d << std::endl;

	//Вычисление весов по кодовой книге
	std::cout << "Weights: " << std::endl;
	std::vector<unsigned int> weights = count_weights(code_words);
	for (size_t i = 0; i < weights.size(); i++)
		std::cout << i << ") " << weights[i] << std::endl;

	std::cout << std::endl;

	std::cout << "Upper assessment: [" << std::endl;

	for (double p = 0.0; p < 1.01; p += 0.01) {
		//Вычисление верхней оценки ошибки
		std::cout << count_upper_assessment(len, r, d, p);
		if (p < 1.0)
			std::cout << ",";
		std::cout << std::endl;
	}

	std::cout << "]" << std::endl;
	std::cout << "Accurate error: [" << std::endl;

	for (double p = 0.0; p < 1.01; p += 0.01) {
		//Вычисление точного значения ошибки
		std::cout << count_accurate_error(weights, len, r, d, p);
		if (p < 1.0)
			std::cout << ",";
		std::cout << std::endl;
	}
	std::cout << "]" << std::endl;
}