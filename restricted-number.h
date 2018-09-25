#pragma once

#include <cassert>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <ostream>

template <class T>
struct restricted_number {
    T minimum, maximum, current;

    restricted_number(T minimum, T maximum, T current) {
        assert(minimum < maximum);

        this->minimum = minimum;
        this->maximum = maximum;
        set(current);
    }


    restricted_number(T minimum, T maximum) {
        assert(minimum < maximum);

        this->minimum = minimum;
        this->maximum = maximum;
        this->current = maximum;
    }

    restricted_number* set(T num) {
        num = std::min(num, maximum);
        num = std::max(num, minimum);
        current = num;
        return this;
    }

    restricted_number* add(T num) {
        return set(current + num);
    }

    restricted_number* sub(T num) {
        return add(-num);
    }

    restricted_number* add_over_maximum(T num) {
        maximum += num;
        return add(num);
    }

    restricted_number* sub_under_minimum(T num) {
        minimum -= num;
        return sub(num);
    }

    restricted_number* to_maximum() {
        return set(maximum);
    }

    restricted_number* to_minimum() {
        return set(minimum);
    }

    bool at_maximum() {
        return current == maximum;
    }

    bool at_minimum() {
        return current == minimum;
    }

    bool gt(T num) {
        return current > num;
    }

    bool gte(T num) {
        return current >= num;
    }

    bool lt(T num) {
        return current < num;
    }

    bool lte(T num) {
        return current <= num;
    }

    restricted_number* set_to_percent(T perc) {
        return set(perc * ((this->maximum - this->minimum) / 100));
    }

    restricted_number* add_percent(T perc) {
        return add(perc * ((this->maximum - this->minimum) / 100));
    }

    restricted_number* sub_percent(T perc) {
        return add_percent(-perc);
    }

    T as_percent() {
        if(std::numeric_limits<T>::is_integer) {
            return std::floor((static_cast<float>(current) / static_cast<float>(maximum)) * 100.f);
        }
        return std::floor((current / maximum) * static_cast<T>(100));
    }

    bool gt_percent(T perc) {
        auto p = as_percent();
        return as_percent() > perc;
    }

    bool gte_percent(T perc) {
        return as_percent() >= perc;
    }

    bool lt_percent(T perc) {
        return as_percent() < perc;
    }

    bool lte_percent(T perc) {
        return as_percent() <= perc;
    }

    // operators

    void operator+=(const T& other) {
        add(other);
    }

    void operator-=(const T& other) {
        sub(other);
    }

    void operator/=(const T& other) {
        set(current/other);
    }

    void operator*=(const T& other) {
        set(current*other);
    }

    bool operator>(const T& other) {
        return gt(other);
    }

    bool operator>=(const T& other) {
        return gte(other);
    }

    bool operator<(const T& other) {
        return lt(other);
    }

    bool operator<=(const T& other) {
        return lte(other);
    }

    restricted_number& operator=(const T& other) {
        set(other);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const restricted_number<T>& rn) {
        os << "(" << rn.minimum << ", " << rn.maximum << ", " << rn.current << ")";
    }
};