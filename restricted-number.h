#pragma once

#include <cassert>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <ostream>

template <class T>
struct restricted_number final {
    restricted_number(T minimum, T maximum, T current) noexcept {
        assert(minimum <= maximum);

        _minimum = minimum;
        _maximum = maximum;
        set(current);
    }

    restricted_number(T minimum, T maximum) noexcept {
        assert(minimum <= maximum);

        _minimum = minimum;
        _maximum = maximum;
        _current = maximum;
    }

    restricted_number& set(T num) noexcept {
        num = std::min(num, _maximum);
        num = std::max(num, _minimum);
        _current = num;
        return *this;
    }

    restricted_number& set_maximum(T maximum) noexcept {
        assert(_minimum <= maximum);

        _maximum = maximum;
        _current = std::min(_current, maximum);
        return *this;
    }

    restricted_number& set_minimum(T minimum) noexcept {
        assert(minimum <= _maximum);

        _minimum = minimum;
        _current = std::max(_current, _minimum);
        return *this;
    }

    restricted_number& add(T num) noexcept {
        return set(_current + num);
    }

    restricted_number& sub(T num) noexcept {
        return add(-num);
    }

    restricted_number& add_over_maximum(T num) noexcept {
        _maximum += num;
        return add(num);
    }

    restricted_number& sub_under_minimum(T num) noexcept {
        _minimum -= num;
        return sub(num);
    }

    restricted_number& to_maximum() noexcept {
        return set(_maximum);
    }

    restricted_number& to_minimum() noexcept {
        return set(_minimum);
    }

    bool at_maximum() const noexcept {
        return _current == _maximum;
    }

    bool at_minimum() const noexcept {
        return _current == _minimum;
    }

    bool gt(T num) const noexcept {
        return _current > num;
    }

    bool gte(T num) const noexcept {
        return _current >= num;
    }

    bool lt(T num) const noexcept {
        return _current < num;
    }

    bool lte(T num) const noexcept {
        return _current <= num;
    }

    restricted_number& set_to_percent(T perc) noexcept {
        return set(perc * ((_maximum - _minimum) / 100));
    }

    restricted_number& add_percent(T perc) noexcept {
        return add(perc * ((_maximum - _minimum) / 100));
    }

    restricted_number& sub_percent(T perc) noexcept {
        return add_percent(-perc);
    }

    T as_percent() const noexcept {
        if(std::numeric_limits<T>::is_integer) {
            return std::floor((static_cast<float>(_current) / static_cast<float>(_maximum)) * 100.f);
        }
        return std::floor((_current / _maximum) * static_cast<T>(100));
    }

    T minimum() const noexcept {
        return _minimum;
    }

    T maximum() const noexcept {
        return _maximum;
    }

    T current() const noexcept {
        return _current;
    }

    bool gt_percent(T perc) const noexcept {
        auto p = as_percent();
        return as_percent() > perc;
    }

    bool gte_percent(T perc) const noexcept {
        return as_percent() >= perc;
    }

    bool lt_percent(T perc) const noexcept {
        return as_percent() < perc;
    }

    bool lte_percent(T perc) const noexcept {
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
        set(_current/other);
    }

    void operator*=(const T& other) noexcept {
        set(_current*other);
    }

    bool operator>(const T& other) const noexcept {
        return gt(other);
    }

    bool operator>=(const T& other) const noexcept {
        return gte(other);
    }

    bool operator<(const T& other) const noexcept {
        return lt(other);
    }

    bool operator==(const T& rhs) const noexcept {
        return _current == rhs;
    }

    bool operator<=(const T& other) const noexcept {
        return lte(other);
    }

    restricted_number& operator=(const T& other) noexcept {
        set(other);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const restricted_number<T>& rn) noexcept {
        os << "(" << rn.minimum() << ", " << rn.maximum() << ", " << rn.current() << ")";
        return os;
    }

private:
    T _minimum, _maximum, _current;
};
