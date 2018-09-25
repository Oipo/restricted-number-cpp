#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include "../restricted-number.h"

using namespace std;

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);

    int result = Catch::Session().run( argc, argv );

    // global clean-up...

    return ( result < 0xff ? result : 0xff );
}


TEST_CASE("constructor") {
    restricted_number<int> num(0, 100, 55);
    REQUIRE(num.minimum == 0);
    REQUIRE(num.maximum == 100);
    REQUIRE(num.current == 55);

    restricted_number<float> numf(0, 100, 55);
    REQUIRE(numf.minimum == 0);
    REQUIRE(numf.maximum == 100);
    REQUIRE(numf.current == 55);
}

TEST_CASE("constructor without current") {
    restricted_number<int> num(0, 100);
    REQUIRE(num.minimum == 0);
    REQUIRE(num.maximum == 100);
    REQUIRE(num.current == 100);

    restricted_number<float> numf(0, 100);
    REQUIRE(numf.minimum == 0);
    REQUIRE(numf.maximum == 100);
    REQUIRE(numf.current == 100);
}

// Catch2 doesn't support REQUIRE_ABORT yet see https://github.com/catchorg/Catch2/issues/853
//TEST_CASE("constructor should assert when min > max") {
//    REQUIRE_ABORT(restricted_number<int> num(100, 0, 0));
//    REQUIRE_ABORT(restricted_number<int> num(100, 0));
//}

TEST_CASE("constructor should cap values") {
    restricted_number<int> num(0, 100, 101);
    REQUIRE(num.minimum == 0);
    REQUIRE(num.maximum == 100);
    REQUIRE(num.current == 100);

    restricted_number<int> num2(0, 100, -1);
    REQUIRE(num2.minimum == 0);
    REQUIRE(num2.maximum == 100);
    REQUIRE(num2.current == 0);
}

TEST_CASE("Bounds checking should work") {
    restricted_number<int> num(0, 100, 101);
    REQUIRE(num.at_maximum());

    restricted_number<int> num2(0, 100, -1);
    REQUIRE(num2.at_minimum());
}

TEST_CASE("Simple value comparisons should all make sense") {
    restricted_number<int> num(0, 100, 60);

    REQUIRE(num.gt(59));
    REQUIRE(!num.gt(60));
    REQUIRE(!num.gt(61));

    REQUIRE(!num.lt(59));
    REQUIRE(!num.lt(60));
    REQUIRE(num.lt(61));

    REQUIRE(num.gte(59));
    REQUIRE(num.gte(60));
    REQUIRE(!num.gte(61));

    REQUIRE(!num.lte(59));
    REQUIRE(num.lte(60));
    REQUIRE(num.lte(61));

    restricted_number<float> num2(0, 100, 60);

    REQUIRE(num2.gt(59));
    REQUIRE(!num2.gt(60));
    REQUIRE(!num2.gt(61));

    REQUIRE(!num2.lt(59));
    REQUIRE(!num2.lt(60));
    REQUIRE(num2.lt(61));

    REQUIRE(num2.gte(59));
    REQUIRE(num2.gte(60));
    REQUIRE(!num2.gte(61));

    REQUIRE(!num2.lte(59));
    REQUIRE(num2.lte(60));
    REQUIRE(num2.lte(61));
}

TEST_CASE("Percentage value comparisons should all make sense") {
    restricted_number<int> num(0, 100, 60);

    REQUIRE(num.gt_percent(59));
    REQUIRE(!num.gt_percent(60));
    REQUIRE(!num.gt_percent(61));

    REQUIRE(!num.lt_percent(59));
    REQUIRE(!num.lt_percent(60));
    REQUIRE(num.lt_percent(61));

    REQUIRE(num.gte_percent(59));
    REQUIRE(num.gte_percent(60));
    REQUIRE(!num.gte_percent(61));

    REQUIRE(!num.lte_percent(59));
    REQUIRE(num.lte_percent(60));
    REQUIRE(num.lte_percent(61));

    restricted_number<float> num2(0, 100, 60);

    REQUIRE(num2.gt_percent(59));
    REQUIRE(!num2.gt_percent(60));
    REQUIRE(!num2.gt_percent(61));

    REQUIRE(!num2.lt_percent(59));
    REQUIRE(!num2.lt_percent(60));
    REQUIRE(num2.lt_percent(61));

    REQUIRE(num2.gte_percent(59));
    REQUIRE(num2.gte_percent(60));
    REQUIRE(!num2.gte_percent(61));

    REQUIRE(!num2.lte_percent(59));
    REQUIRE(num2.lte_percent(60));
    REQUIRE(num2.lte_percent(61));
}

TEST_CASE("Simple value mutators should all work correctly") {
    restricted_number<int> RN1(0, 100, 50);

    REQUIRE(RN1.add(10)->current == 60);
    REQUIRE(RN1.add(50)->current == 100);

    restricted_number<int> RN2(0, 100, 50);

    REQUIRE(RN2.sub(10)->current == 40);
    REQUIRE(RN2.sub(50)->current == 0);

    restricted_number<int> RN3(0, 100, 50);

    REQUIRE(RN3.to_minimum()->current == 0);

    restricted_number<int> RN4(0, 100, 50);

    REQUIRE(RN4.to_maximum()->current == 100);
}

TEST_CASE("Simple float value mutators should all work correctly") {
    restricted_number<float> RN1(0, 100, 50);

    REQUIRE(RN1.add(10)->current == 60);
    REQUIRE(RN1.add(50)->current == 100);

    restricted_number<float> RN2(0, 100, 50);

    REQUIRE(RN2.sub(10)->current == 40);
    REQUIRE(RN2.sub(50)->current == 0);

    restricted_number<float> RN3(0, 100, 50);

    REQUIRE(RN3.to_minimum()->current == 0);

    restricted_number<float> RN4(0, 100, 50);

    REQUIRE(RN4.to_maximum()->current == 100);
}

TEST_CASE("Percentage value mutators should all work correctly") {
    restricted_number<int> RN1(0, 100, 50);

    REQUIRE(RN1.add_percent(10)->current == 60);
    REQUIRE(RN1.add_percent(50)->current == 100);

    restricted_number<int> RN2(0, 100, 50);

    REQUIRE(RN2.sub_percent(10)->current == 40);
    REQUIRE(RN2.sub_percent(50)->current == 0);

    restricted_number<int> RN3(0, 100, 50);

    REQUIRE(RN3.set_to_percent(10)->current == 10);
}

TEST_CASE("Percentage float value mutators should all work correctly") {
    restricted_number<float> RN1(0, 100, 50);

    REQUIRE(RN1.add_percent(10)->current == 60);
    REQUIRE(RN1.add_percent(50)->current == 100);

    restricted_number<float> RN2(0, 100, 50);

    REQUIRE(RN2.sub_percent(10)->current == 40);
    REQUIRE(RN2.sub_percent(50)->current == 0);

    restricted_number<float> RN3(0, 100, 50);

    REQUIRE(RN3.set_to_percent(10)->current == 10);
}

TEST_CASE("Complex value mutators should all work correctly") {
    restricted_number<int> RN1(0, 100, 50);

    REQUIRE(RN1.add_over_maximum(10)->current == 60);
    REQUIRE(RN1.maximum == 110);

    restricted_number<int> RN2(0, 100, 50);

    REQUIRE(RN2.sub_under_minimum(10)->current == 40);
    REQUIRE(RN2.minimum == -10);
}

TEST_CASE("Complex float value mutators should all work correctly") {
    restricted_number<float> RN1(0, 100, 50);

    REQUIRE(RN1.add_over_maximum(10)->current == 60);
    REQUIRE(RN1.maximum == 110);

    restricted_number<float> RN2(0, 100, 50);

    REQUIRE(RN2.sub_under_minimum(10)->current == 40);
    REQUIRE(RN2.minimum == -10);
}

TEST_CASE("+= operator overloads work") {
    restricted_number<int> num(0, 100, 50);

    num += 10;

    REQUIRE(num.current == 60);

    num += 100;

    REQUIRE(num.current == 100);

    restricted_number<float> numf(0, 100, 50);

    numf += 10.5;

    REQUIRE(numf.current == 60.5f);

    numf += 100;

    REQUIRE(numf.current == 100);
}

TEST_CASE("-= operator overloads work") {
    restricted_number<int> num(0, 100, 50);

    num -= 10;

    REQUIRE(num.current == 40);

    num -= 100;

    REQUIRE(num.current == 0);

    restricted_number<float> numf(0, 100, 50);

    numf -= 10.5;

    REQUIRE(numf.current == 39.5f);

    numf -= 100;

    REQUIRE(numf.current == 0);
}

TEST_CASE("/= operator overloads work") {
    restricted_number<int> num(0, 100, 50);

    num /= 10;

    REQUIRE(num.current == 5);

    restricted_number<float> numf(0, 100, 50);

    numf /= 10;

    REQUIRE(numf.current == 5);
}

TEST_CASE("*= operator overloads work") {
    restricted_number<int> num(0, 100, 20);

    num *= 2;

    REQUIRE(num.current == 40);

    num *= 10;

    REQUIRE(num.current == 100);

    restricted_number<float> numf(0, 100, 20.5);

    numf *= 2;

    REQUIRE(numf.current == 41.f);

    numf *= 10;

    REQUIRE(numf.current == 100);
}