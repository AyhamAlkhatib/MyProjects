// "Copyright 2023 Ayham Alkhatib"
#include <string>
#include <iostream>
#include <exception>
#include "RandWriter.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
// Test the orderK, textSize.
BOOST_AUTO_TEST_CASE(testStepInstr1) {
    RandWriter ex("abc", 2);
    int k = ex.orderK();
    int size = ex.textSize();
    BOOST_REQUIRE_EQUAL(k, 2);
    BOOST_REQUIRE_EQUAL(size, 3);
}
// Testing both frequency functions and kgramSize() return the correct value.
BOOST_AUTO_TEST_CASE(testStepInstr2) {
    std::string str = "abcabc";
    RandWriter ex(str, 2);
    int occurance = ex.freq("ab");
    BOOST_REQUIRE_EQUAL(occurance, 2);
    occurance = ex.freq("bc", 'a');
    BOOST_REQUIRE_EQUAL(occurance, 2);
    int size = ex.kgramSize("abc");
    BOOST_REQUIRE_EQUAL(size, 3);
}
// Testing kRand generates the correct letter based on the frequency
// b always comes after a because in the string b always comes after a.
BOOST_AUTO_TEST_CASE(testStepInstr3) {
    std::string str = "abcabc";
    RandWriter ex(str, 1);
    char ch = ex.kRand("a");
    BOOST_REQUIRE_EQUAL(ch, 'b');
}
// Check that generate() generates the expected string.
BOOST_AUTO_TEST_CASE(testStepInstr4) {
    std::string str = "abcdefg";
    RandWriter ex(str, 1);
    std::string sol = ex.generate("a", str.size());
    BOOST_REQUIRE_EQUAL(sol, str);
}
// Checking that exceptions are thrown when reaonable
// (when orderK has a weird k value and kgram.size() != orderK).
// Testing for all functions
BOOST_AUTO_TEST_CASE(testStepInstr5) {
    RandWriter ex("abc", 2);
    BOOST_REQUIRE_THROW(ex.freq("abcde"), std::invalid_argument);
    BOOST_REQUIRE_THROW(RandWriter ex("abc", -1), std::invalid_argument);
    BOOST_REQUIRE_THROW(ex.freq("abcde", 'a'),  std::invalid_argument);
    BOOST_REQUIRE_THROW(ex.generate("PS6 was interisting", 4), std::invalid_argument);
}
