#pragma once

#include <cassert>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <ostream>

template <class T>
struct restricted_number final {
    T minimum, maximum, current;

    restricted_number(T minimum, T maximum, T current) noexcept {
        assert(minimum < maximum);

        this->minimum = minimum;
        this->maximum = maximum;
        set(current);
    }


    restricted_number(T minimum, T maximum) noexcept {
        assert(minimum < maximum);

        this->minimum = minimum;
        this->maximum = maximum;
        this->current = maximum;
    }

    restricted_number* set(T num) noexcept {
        num = std::min(num, maximum);
        num = std::max(num, minimum);
        current = num;
        return this;
    }

    restricted_number* add(T num) noexcept {
        return set(current + num);
    }

    restricted_number* sub(T num) noexcept {
        return add(-num);
    }

    restricted_number* add_over_maximum(T num) noexcept {
        maximum += num;
        return add(num);
    }

    restricted_number* sub_under_minimum(T num) noexcept {
        minimum -= num;
        return sub(num);
    }

    restricted_number* to_maximum() noexcept {
        return set(maximum);
    }

    restricted_number* to_minimum() noexcept {
        return set(minimum);
    }

    bool at_maximum() noexcept {
        return current == maximum;
    }

    bool at_minimum() noexcept {
        return current == minimum;
    }

    bool gt(T num) noexcept {
        return current > num;
    }

    bool gte(T num) noexcept {
        return current >= num;
    }

    bool lt(T num) noexcept {
        return current < num;
    }

    bool lte(T num) noexcept {
        return current <= num;
    }

    restricted_number* set_to_percent(T perc) noexcept {
        return set(perc * ((this->maximum - this->minimum) / 100));
    }

    restricted_number* add_percent(T perc) noexcept {
        return add(perc * ((this->maximum - this->minimum) / 100));
    }

    restricted_number* sub_percent(T perc) noexcept {
        return add_percent(-perc);
    }

    T as_percent() noexcept {
        if(std::numeric_limits<T>::is_integer) {
            return std::floor((static_cast<float>(current) / static_cast<float>(maximum)) * 100.f);
        }
        return std::floor((current / maximum) * static_cast<T>(100));
    }

    bool gt_percent(T perc) noexcept {
        auto p = as_percent();
        return as_percent() > perc;
    }

    bool gte_percent(T perc) noexcept {
        return as_percent() >= perc;
    }

    bool lt_percent(T perc) noexcept {
        return as_percent() < perc;
    }

    bool lte_percent(T perc) noexcept {
        return as_percent() <= perc;
    }

    // operators

    void operator+=(const T& other) noexcept {
        add(other);
    }

    void operator-=(const T& other) noexcept {
        sub(other);
    }

    void operator/=(const T& other) noexcept {
        set(current/other);
    }

    void operator*=(const T& other) noexcept {
        set(current*other);
    }

    bool operator>(const T& other) noexcept {
        return gt(other);
    }

    bool operator>=(const T& other) noexcept {
        return gte(other);
    }

    bool operator<(const T& other) noexcept {
        return lt(other);
    }

    bool operator<=(const T& other) noexcept {
        return lte(other);
    }

    restricted_number& operator=(const T& other) noexcept {
        set(other);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const restricted_number<T>& rn) noexcept {
        os << "(" << rn.minimum << ", " << rn.maximum << ", " << rn.current << ")";
        return os;
    }
};
