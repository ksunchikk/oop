#pragma once
#include <cstdio>
#include <malloc.h>
#include <iostream>
#include "bigNumber.h"
namespace Stack1 {
    using namespace Prog3a;
    class Stack {
        bigDecNum* number;
        int SZ;
        int ptr;
    public:
        Stack(int size) {
            SZ = size;
            number = (bigDecNum*)malloc(SZ * sizeof(bigDecNum));
            ptr = 0;
        };
        ~Stack() {
            free(number);
        };
        bigDecNum pop(void) {
            if (ptr)
                return number[--ptr];
            else {
                bigDecNum a;
                return a;
            }
        };
        void push(const char* str) {
            if (ptr >= SZ - 1) {
                SZ++;
                number = (bigDecNum*)realloc(number, SZ * sizeof(bigDecNum));
            }
            try {
                number[ptr++].Set(str);
            }
            catch (const std::exception& msg) {

                std::cout << msg.what() << std::endl;
            }
        };
        void push1(bigDecNum x) {
            if (ptr >= SZ - 1) {
                SZ++;
                number = (bigDecNum*)realloc(number, SZ * sizeof(bigDecNum));
            }
            number[ptr++] = x;
        };
        int empty() {
            return (ptr == 0);
        }
        int PrinstStack() {
            number->Print();
            return 0;
        }
    };
}
