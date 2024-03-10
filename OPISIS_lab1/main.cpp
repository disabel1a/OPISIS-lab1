#include "decoder_error.h"

int main() {
	std::vector<bool> polynome = {1, 1, 0, 1};
	unsigned int len = 7;

	unsigned int r = degree(polynome);

	//Создание кодовой книги
	std::cout << "Code words: " << std::endl;
	std::vector<std::vector<bool>> code_words = create_code_words(polynome, len);
	std::cout << std::endl;

	//Вычисление расстояния Хемминга
	unsigned int d = count_hemming(code_words);

	std::vector<unsigned int> weights = count_weights(code_words);

	for (double p = 0.01; p < 1.0; p += 0.01) {
		std::cout << "p = " << p << std::endl;

		//Вычисление верхней оценки ошибки
		std::cout << "Upper assessment: " << count_upper_assessment(len, r, d, p) << std::endl;

		//Вычисление точного значения ошибки
		std::cout << "Upper assessment: " << count_accurate_error(weights, len, r, d, p) << std::endl;

		std::cout << std::endl;
	}
}