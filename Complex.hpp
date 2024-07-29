//ID: 207826694
//GMAIL: didooron@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>

class Complex{
    private:
        double real;
        double img;

    public:
        Complex(double real, double img) : real(real), img(img) {}
        double get_real() const { return real; }
        double get_imag() const { return img; }

        double magnitude() const { return sqrt(real * real + img * img); }
        
        Complex operator+(const Complex &other) const {
            return Complex(real + other.real, img + other.img);
        }

        Complex operator-(const Complex &other) const {
            return Complex(real - other.real, img - other.img);
        }

        Complex operator*(const Complex &other) const {
            return Complex(real * other.real - img * other.img, real * other.img + img * other.real);
        }

        Complex operator/(const Complex &other) const {
            double denominator = other.real * other.real + other.img * other.img;
            return Complex((real * other.real + img * other.img) / denominator, (img * other.real - real * other.img) / denominator);
        }
        
        friend std::ostream &operator<<(std::ostream &os, const Complex &other) {
            os << other.real << "+" << other.img << "i";
            return os;
        }

        bool operator==(const Complex &other) const {
            return real == other.real && img == other.img;
        }

        bool operator!=(const Complex &other) const {
            return !(*this == other);
        }
        
        Complex operator-() const {
            return Complex(-real, -img);
        }

        Complex operator+=(const Complex &other) {
            real += other.real;
            img += other.img;
            return *this;
        }

        Complex operator-=(const Complex &other) {
            real -= other.real;
            img -= other.img;
            return *this;
        }

        Complex operator*=(const Complex &other) {
            double temp = real;
            real = real * other.real - img * other.img;
            img = temp * other.img + img * other.real;
            return *this;
        }
        
        Complex operator/=(const Complex &c) {
            double denominator = c.real * c.real + c.img * c.img;
            double temp = real;
            real = (real * c.real + img * c.img) / denominator;
            img = (img * c.real - temp * c.img) / denominator;
            return *this;
        }

        bool operator<(const Complex &other) const {
            return magnitude() < other.magnitude();
        }

        bool operator<=(const Complex &other) const {
            return magnitude() <= other.magnitude();
        }

        bool operator>(const Complex &other) const {
            return magnitude() > other.magnitude();
        }

        bool operator>=(const Complex &other) const {
            return magnitude() >= other.magnitude();
        }

}; //end class

#endif