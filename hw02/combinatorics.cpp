#include "combinatorics.h"


uint64_t factorial(uint64_t val) {
    // TODO
    if (val== 0) return 1;
    return val * factorial(val - 1);
}


uint64_t permutation(uint64_t val, uint64_t val2) {
    // TODO
    if (val < val2) return 0;
    return factorial(val) / factorial(val - val2);
}


uint64_t combination(uint64_t val, uint64_t val2) {
    // TODO
    if (val < val2) return 0;
    return factorial(val) / (factorial(val2) * factorial(val - val2));
}
