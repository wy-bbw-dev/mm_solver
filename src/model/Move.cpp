//
// Created by ich on 4/2/23.
//
#include <algorithm>
#include <model/Move.h>



template<typename T>
std::ostream &operator<<(std::ostream& os, const std::pair<T, T>& t) {
    os << t.first << ", " << t.second;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << "Move{" << move.to << "}";
    return os;
}