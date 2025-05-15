// "Copyright 2023 Ayham Alkhatib"

#include <iostream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testStepInstr1) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testStepInstr2) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.generate(9), 51);
}
BOOST_AUTO_TEST_CASE(testStepInstr3) {
  FibLFSR l1("1011011000110110");
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l1.generate(5), l2.generate(5));
}
// Test step() outputs correctly
BOOST_AUTO_TEST_CASE(testStepInstr4) {
  FibLFSR l1("1011011000110110");
  l1.step();
  l1.step();
  l1.step();
  l1.step();
  l1.step();
  l1.step();
  l1.step();
  BOOST_REQUIRE_EQUAL(l1.getStr(), "0001101100001100");
}

BOOST_AUTO_TEST_CASE(testStepInstr5) {
  FibLFSR l1("1011011000110110");
  l1.step();
  FibLFSR l2("1011011000110110");
  l2.step();
  BOOST_REQUIRE_EQUAL(l1.getStr(), l2.getStr());
}


BOOST_AUTO_TEST_CASE(testStepInstr6) {
  FibLFSR l1("1011011000110110");
  FibLFSR l2("0001101100001100");
  BOOST_REQUIRE_NE(l1.generate(5), l2.generate(5));
}



