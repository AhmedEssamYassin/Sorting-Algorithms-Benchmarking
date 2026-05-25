#pragma once
#include <vector>
#include <string>
#include <random>
#include <cstdint>
using namespace std;
#define ll long long

class Sort
{

public:
    static std::mt19937 rnd;
    static constexpr int INSERTION_THRESHOLD = 32;
    static constexpr int HYBRID_INSERTION_THRESHOLD = 64;

    static int64_t getRandomNumber(int64_t l, int64_t r) {
        return std::uniform_int_distribution<int64_t>(l, r)(rnd);
    }

    // Pure virtual functions
    virtual void sort(vector<ll> &arr) = 0;
    virtual string getName() const = 0;
    virtual ~Sort() {}
};