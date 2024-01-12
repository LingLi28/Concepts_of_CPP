/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "hw10.h"
#include <string>

TEST_CASE("Quadruple_mixed_1_test")
{
    Quadruple<int, int, int, std::string> quadruple{1, 2, 3, std::string("abc")};
    CHECK_EQ(quadruple.get_first(), 1);
    CHECK_EQ(quadruple.get_second(), 2);
    CHECK_EQ(quadruple.get_third(), 3);
    CHECK_EQ(quadruple.get_fourth(), std::string("abc"));
}

TEST_CASE("Quadruple_mixed_2_test")
{
    Quadruple<int, double, double, std::string> quadruple{1, 2.0, 3.0,
        std::string("abc")};
    CHECK_EQ(quadruple.get_first(), 1);
    CHECK_EQ(quadruple.get_second(), 2.0);
    CHECK_EQ(quadruple.get_third(), 3.0);
    CHECK_EQ(quadruple.get_fourth(), std::string("abc"));
}

TEST_CASE("Quadruple_custom_type_test")
{
    struct rolf {
        int lol;
        auto operator<=>(const rolf&) const = default;
    };
    Quadruple<rolf, double, double, rolf> quadruple{rolf{42}, 7.0, 28.0,
        rolf{1337}};
    CHECK_EQ(quadruple.get_first(), rolf{42});
    CHECK_EQ(quadruple.get_second(), 7.0);
    CHECK_EQ(quadruple.get_third(), 28.0);
    CHECK_EQ(quadruple.get_fourth(), rolf{1337});
}

TEST_CASE("Quadruple_partial_specialization_test")
{
    Quadruple<int, int, int, int> quadruple(1, 2, 3, 4);
    CHECK_EQ(quadruple.get_first(), 1);
    CHECK_EQ(quadruple.get_second(), 2);
    CHECK_EQ(quadruple.get_third(), 3);
    CHECK_EQ(quadruple.get_fourth(), 4);

    // check if member was created
    CHECK_EQ(quadruple.members.size(), 4);
    CHECK_EQ(quadruple.members[3], 4);
}

TEST_CASE("Quadruple_full_specialization_test")
{
    Quadruple<float, float, float, float> quadruple(3.0, 4.0, 5.0, 80.0);
    CHECK_EQ(quadruple.get_first(), 3.0);
    CHECK_EQ(quadruple.get_second(), 4.0);
    CHECK_EQ(quadruple.get_third(), 5.0);
    CHECK_EQ(quadruple.get_fourth(), 80.0);

    // check if member was created
    CHECK_EQ(quadruple.members.size(), 4);
    CHECK_EQ(quadruple.members[3], 80.0);
}

TEST_CASE("Quadruple_full_specialization_customtype_test")
{
    struct rolf {
        auto operator<=>(const rolf&) const = default;
        int stuff;
    };
    Quadruple<rolf, rolf, rolf, rolf> quadruple{rolf{1}, {2}, {4}, {8}};
    CHECK_EQ(quadruple.get_first(), rolf{1});
    CHECK_EQ(quadruple.get_second(), rolf{2});
    CHECK_EQ(quadruple.get_third(), rolf{4});
    CHECK_EQ(quadruple.get_fourth(), rolf{8});

    CHECK_EQ(quadruple.members.size(), 4);
    CHECK_EQ(quadruple.members[0].stuff, 1);
    CHECK_EQ(quadruple.members[1].stuff, 2);
    CHECK_EQ(quadruple.members[2].stuff, 4);
    CHECK_EQ(quadruple.members[3].stuff, 8);
}

TEST_CASE("GCD_test")
{
    SUBCASE("gcd(1, 100)")
    {
        static constinit auto val = gcd(1, 100);
        CHECK_EQ(val, 1);
    }

    SUBCASE("gcd(100, 10)")
    {
        static constinit auto val = gcd(100, 10);
        CHECK_EQ(val, 10);
    }

    SUBCASE("gcd(60, 42)")
    {
        static constinit auto val = gcd(60, 42);
        CHECK_EQ(val, 6);
    }

    SUBCASE("gcd(42, 60)")
    {
        static constinit auto val = gcd(42, 60);
        CHECK_EQ(val, 6);
    }

    SUBCASE("gcd(35, 36)")
    {
        static constinit auto val = gcd(35, 36);
        CHECK_EQ(val, 1);
    }

    SUBCASE("gcd(36, 35)")
    {
        static constinit auto val = gcd(36, 35);
        CHECK_EQ(val, 1);
    }

    SUBCASE("gcd(20, 30, 40)")
    {
        static constinit auto val = gcd(20, 30, 40);
        CHECK_EQ(val, 10);
    }

    SUBCASE("gcd(20, 30, 40, 50)")
    {
        static constinit auto val = gcd(20, 30, 40, 50);
        CHECK_EQ(val, 10);
    }

    SUBCASE("gcd(20, 30, 40, 50, 60)")
    {
        static constinit auto val = gcd(20, 30, 40, 50, 60);
        CHECK_EQ(val, 10);
    }

    SUBCASE("gcd(30, 60, 45, 90)")
    {
        static constinit auto val = gcd(30, 60, 45, 90);
        CHECK_EQ(val, 15);
    }

    SUBCASE("gcd(1001, 715, 2145)")
    {
        static constinit auto val = gcd(1001, 715, 2145);
        CHECK_EQ(val, 143);
    }

    SUBCASE("gcd(1001, 143, 715, 2145)")
    {
        static constinit auto val = gcd(1001, 143, 715, 2145);
        CHECK_EQ(val, 143);
    }
}

TEST_CASE("MCM_test")
{
    SUBCASE("mcm(1, 100)")
    {
        static constinit auto val = mcm(1, 100);
        CHECK_EQ(val, 100);
    }
    SUBCASE("mcm(100, 10)")
    {
        static constinit auto val = mcm(100, 10);
        CHECK_EQ(val, 100);
    }
    SUBCASE("mcm(60, 42)")
    {
        static constinit auto val = mcm(60, 42);
        CHECK_EQ(val, 420);
    }
    SUBCASE("mcm(42, 60)")
    {
        static constinit auto val = mcm(42, 60);
        CHECK_EQ(val, 420);
    }
    SUBCASE("mcm(35, 36)")
    {
        static constinit auto val = mcm(35, 36);
        CHECK_EQ(val, 1260);
    }
    SUBCASE("mcm(36, 35)")
    {
        static constinit auto val = mcm(36, 35);
        CHECK_EQ(val, 1260);
    }
    SUBCASE("mcm(20, 30, 40)")
    {
        static constinit auto val = mcm(20, 30, 40);
        CHECK_EQ(val, 120);
    }
    SUBCASE("mcm(20, 30, 40, 50)")
    {
        static constinit auto val = mcm(20, 30, 40, 50);
        CHECK_EQ(val, 600);
    }
    SUBCASE("mcm(20, 30, 40, 50, 60)")
    {
        static constinit auto val = mcm(20, 30, 40, 50, 60);
        CHECK_EQ(val, 600);
    }
    SUBCASE("mcm(30, 60, 45, 90)")
    {
        static constinit auto val = mcm(30, 60, 45, 90);
        CHECK_EQ(val, 180);
    }
    SUBCASE("mcm(1001, 715, 2145)")
    {
        static constinit auto val = mcm(1001, 715, 2145);
        CHECK_EQ(val, 15015);
    }
    SUBCASE("mcm(1001, 143, 715, 2145)")
    {
        static constinit auto val = mcm(1001, 143, 715, 2145);
        CHECK_EQ(val, 15015);
    }
}

TEST_CASE("Power_test")
{
    static_assert(Power<1, 0, 1>::value == 0);

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<1, 0, 1>::value;
        CHECK_EQ(val, 0);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<1, 0, 2>::value;
        CHECK_EQ(val, 1);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<2, 0, 42>::value;
        CHECK_EQ(val, 1);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<5, 1, 42>::value;
        CHECK_EQ(val, 5);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<5, 2, 42>::value;
        CHECK_EQ(val, 25);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<5, 3, 42>::value;
        CHECK_EQ(val, 41);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<5, 4, 42>::value;
        CHECK_EQ(val, 37);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<5, 5, 42>::value;
        CHECK_EQ(val, 17);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<5, 6, 42>::value;
        CHECK_EQ(val, 1);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<12, 9, 123>::value;
        CHECK_EQ(val, 93);
    }

    SUBCASE("Power<1, 0, 1>")
    {
        static constinit auto val = Power<42, 437, 10403>::value;
        CHECK_EQ(val, 3891);
    }
}

TEST_CASE("Bencode parse ints")
{
    SUBCASE("decode i42e")
    {
        static constinit auto value = bencode::parse_int("i42e");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), 42);
    }

    SUBCASE("decode i42e")
    {
        static constinit auto value = bencode::parse_int("i-42e");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), -42);
    }

    SUBCASE("decode i12345e")
    {
        static constinit auto value = bencode::parse_int("i12345e");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), 12345);
    }

    SUBCASE("decode i-12345e")
    {
        static constinit auto value = bencode::parse_int("i-12345e");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), -12345);
    }

    SUBCASE("fail to decode 420")
    {
        static constinit auto value = bencode::parse_int("420");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode i420")
    {
        static constinit auto value = bencode::parse_int("i420");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode 420e")
    {
        static constinit auto value = bencode::parse_int("420e");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode ie")
    {
        static constinit auto value = bencode::parse_int("ie");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode i4f20e")
    {
        static constinit auto value = bencode::parse_int("i4f20e");
        CHECK_UNARY_FALSE(value.has_value());
    }
}

TEST_CASE("Bencode parse byte string")
{
    SUBCASE("decode 4:yolo")
    {
        static constinit auto value = bencode::parse_byte_string("4:yolo");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), "yolo");
    }

    SUBCASE("decode '10:c++ is fun'")
    {
        static constinit auto value = bencode::parse_byte_string("10:c++ is fun");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), "c++ is fun");
    }

    SUBCASE("decode '10:compile-time programming is fun fun fun!'")
    {
        static constinit auto value = bencode::parse_byte_string("40:compile-time programming is fun fun fun!");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), "compile-time programming is fun fun fun!");
    }

    SUBCASE("decode '12:compile-time programming is fun fun fun!'")
    {
        static constinit auto value = bencode::parse_byte_string("12:compile-time programming is fun fun fun!");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), "compile-time");
    }

    SUBCASE("decode '21:announcement: success'")
    {
        static constinit auto value = bencode::parse_byte_string("21:announcement: success");
        CHECK_UNARY(value.has_value());
        CHECK_EQ(value.value(), "announcement: success");
    }

    SUBCASE("fail to decode '4:' (empty)")
    {
        static constinit auto value = bencode::parse_byte_string("4:");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode '' (empty)")
    {
        static constinit auto value = bencode::parse_byte_string("");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode '14whereisthecolon'")
    {
        static constinit auto value = bencode::parse_byte_string("14whereisthecolon");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode 'nonumbernocolumn'")
    {
        static constinit auto value = bencode::parse_byte_string("nonumbernocolumn");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode 'a14:mixedalphanum'")
    {
        static constinit auto value = bencode::parse_byte_string("a14:mixedalphanum");
        CHECK_UNARY_FALSE(value.has_value());
    }

    SUBCASE("fail to decode '14:short'")
    {
        static constinit auto value = bencode::parse_byte_string("14:short");
        CHECK_UNARY_FALSE(value.has_value());
    }
}
