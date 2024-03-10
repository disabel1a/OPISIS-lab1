#pragma once
#include <math.h>
#include <vector>
#include <iostream>

unsigned long long combinations(unsigned int n, unsigned int k) {
    if (k == 0 || k == n)
        return 1;
    else
        return combinations(n - 1, k - 1) + combinations(n - 1, k);
}

int degree(const std::vector<bool>& polynome) {
    for (size_t i = 0; i < polynome.size(); ++i) {
        if (polynome[i]) {
            return polynome.size() - 1 - i;
        }
    }
    return -1;
}

std::vector<bool> xor_polynoms(const std::vector<bool>& _dividend, const std::vector<bool>& _divisor, const int shift) {
    if (shift < 0)
        return _dividend;

    std::vector<bool> result(_dividend.size(), 0);
    std::vector<bool> divisor = _divisor;

    for (size_t i = 0; i < shift; i++)
        divisor.push_back(0);

    for (size_t i = 0; i < _dividend.size(); i++)
        result[i] = _dividend[i] ^ divisor[i];

    while (result[0] == 0 && result.size() > 1)
        result.erase(result.begin());

    return result;
}

std::vector<bool> mod(const std::vector<bool>& dividend, const std::vector<bool>& divisor) {
    unsigned int pos = 0;
    for (bool bit : dividend) {
        if (bit) {
            break;
        }
        pos++;
    }

    std::vector<bool> remainder;
    for (unsigned int i = pos; i < dividend.size(); i++)
        remainder.push_back(dividend[i]);

    int divisor_degree = degree(divisor);

    while (degree(remainder) >= divisor_degree) {
        int shift = degree(remainder) - divisor_degree;
        remainder = xor_polynoms(remainder, divisor, shift);
    }

    while (remainder.size() < divisor_degree)
        remainder.insert(remainder.begin(), 0);

    return remainder;
}

unsigned int count_hemming(std::vector<std::vector<bool>>& code_words) {
    unsigned int min_distance = UINT32_MAX;
    unsigned int current_distance = 0;

    for (unsigned int i = 0; i < code_words.size(); ++i)
        for (unsigned int j = 0; j < code_words.size(); ++j) {
            if (i == j)
                continue;
            std::vector<bool> xored_vector = xor_polynoms(code_words[i], code_words[j], 0);

            for (bool bit : xored_vector)
                if (bit)
                    current_distance++;

            if (min_distance > current_distance)
                min_distance = current_distance;

            current_distance = 0;
        }

    return min_distance;
}

void increase_vector(std::vector<bool>& vector) {
    bool overflow = 1;
    for (int i = vector.size() - 1; i >= 0; i--) {
        if (vector[i]) {
            vector[i] = 0;
        }
        else {
            vector[i] = overflow;
            overflow = 0;
        }
        if (!overflow)
            return;
    }
}

std::vector<bool> merge_vectors(std::vector<bool>& first, std::vector<bool>& second) {
    std::vector<bool> result;
    for (bool bit : first)
        result.push_back(bit);
    for (bool bit : second)
        result.push_back(bit);
    return result;
}

std::vector<bool> mult_vector_with_var(std::vector<bool>& vector, unsigned int& deg) {
    std::vector<bool> result = vector;
    for (unsigned int i = 0; i < deg; i++)
        result.push_back(0);
    return result;
}

void print_vector(std::vector<bool>& vector) {
    std::cout << "[";
    for (bool bit : vector) {
        if (bit)
            std::cout << 1;
        else
            std:: cout << 0;
    }
    std::cout << "]";
}

std::vector<std::vector<bool>> create_code_words(std::vector<bool> polynome, unsigned int len) {
    unsigned int r, k = 0;
    double result = 0.0;

    r = degree(polynome);
    k = len - r;

    std::vector<bool> message(k);
    std::vector<std::vector<bool>> code_words;

    for (unsigned int i = 0; i < pow(2, k); i++) {
        std::vector<bool> control_sum = mod(mult_vector_with_var(message, r), polynome);
        std::vector<bool> code_word = merge_vectors(message, control_sum);

        print_vector(message);
        print_vector(control_sum);
        std::cout << std::endl;

        code_words.push_back(code_word);
        increase_vector(message);
    }
    return code_words;
}

unsigned int count_weight(std::vector<bool>& code_word) {
    unsigned int counter = 0;
    for (bool bit : code_word)
        if (bit)
            counter++;
    return counter;
}

std::vector<unsigned int> count_weights(std::vector<std::vector<bool>>& code_words) {
    std::vector<unsigned int> weights(code_words[0].size() + 1, 0);
    for (std::vector<bool> code_word : code_words)
        weights[count_weight(code_word)]++;
    return weights;
}

double count_upper_assessment(unsigned int len, unsigned int r, unsigned int d, double p) {
    unsigned int k = len - r;
    double result = 0.0;

    for (unsigned int i = 0; i < d; i++)
        result += (combinations(len, i) * pow(p, i) * pow((1 - p), (len - i)));

    return 1 - result;
}

double count_accurate_error(std::vector<unsigned int>& weights, unsigned int len, unsigned int r, unsigned int d, double p) {
    unsigned int k = len - r;
    double result = 0.0;
    
    for (unsigned int i = d; i < len; i++)
        result += weights[i] * pow(p, i) * pow((1 - p), (len - i));

    return result;
}

//double count_upper_assessment(std::vector<bool> polynome, unsigned int len, double p) {
//    unsigned int r, k = 0;
//    double result = 0.0;
//
//    r = degree(polynome);
//    k = len - r;
//
//    std::vector<bool> message(k);
//    std::vector<std::vector<bool>> code_words;
//
//    for (unsigned int i = 0; i < pow(2, k); i++) {
//        //print_vector(message);
//
//        std::vector<bool> control_sum = mod(mult_vector_with_var(message, r), polynome);
//        std::vector<bool> code_word = merge_vectors(message, control_sum);
//
//        //print_vector(control_sum);
//        //std::cout << std::endl;
//
//        code_words.push_back(code_word);
//        increase_vector(message);
//    }
//
//    unsigned int d = count_hemming(code_words);
//    //std::cout << "Hemming: " << d << std::endl;
//
//    for (unsigned int i = 0; i < d; i++) {
//        result += (combinations(len, i) * pow(p, i) * pow((1 - p), (len - i)));
//    }
//
//    //std::cout << "Upper assessment: " << 1 - result << std::endl;
//    return 1 - result;
//}
//
//double count_accurate_error(std::vector<bool> polynome, unsigned int len, double p) {
//    unsigned int r, k = 0;
//    double result = 0.0;
//
//    r = degree(polynome);
//    k = len - r;
//
//    std::vector<bool> message(k);
//    std::vector<std::vector<bool>> code_words;
//
//    for (unsigned int i = 0; i < pow(2, k); i++) {
//        //print_vector(message);
//
//        std::vector<bool> control_sum = mod(mult_vector_with_var(message, r), polynome);
//        std::vector<bool> code_word = merge_vectors(message, control_sum);
//
//        //print_vector(control_sum);
//        //std::cout << std::endl;
//
//        code_words.push_back(code_word);
//        increase_vector(message);
//    }
//
//    unsigned int d = count_hemming(code_words);
//    //std::cout << "Hemming: " << d << std::endl;
//}