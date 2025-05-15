// "Copyright 2023 Ayham Alkhatib"

#include <iostream>
#include <string>
#include <fstream>
#include "EDistance.hpp"
#include <SFML/Graphics.hpp>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testStepInstr1) {
    std::string s1 = "TACAGTTACCA";
    std::string s2 = "TAAGGTCAA";
    EDistance dis(s1, s2);
    BOOST_REQUIRE_EQUAL(dis.optDistance(), 6);
}

BOOST_AUTO_TEST_CASE(testStepInstr2) {
    std::string s1 = "TACAGTTACCA";
    std::string s2 = "TAAGGTCAA";
    int a = 3, b = 6, c = 5;
    EDistance dis(s1, s2);
    int x = dis.min3(a, b, c);
    BOOST_REQUIRE_EQUAL(x, a);
}
// Testing
BOOST_AUTO_TEST_CASE(testStepInstr3) {
    std::string s1 = "TAAGGTCAA";
    std::string s2 = "TACAGTTACCA";
    EDistance dis(s1, s2);
    BOOST_REQUIRE_EQUAL(dis.optDistance(), 6);
}

BOOST_AUTO_TEST_CASE(testStepInstr4) {
    std::string s1 = "TAAGGTCAA";
    std::string s2 = "TACAGTTACCA";
    EDistance dis(s1, s2);
    int x = dis.penalty(s1[0], s2[0]);
     BOOST_REQUIRE_EQUAL(x, 0);
}
