#include <gtest/gtest.h>

#include <pybind11/pytypes.h>

#include <string>



namespace py = pybind11;

using namespace re2_python;



TEST_F(RE2QuoteMetaShimTest_60, NormalOperation_60) {

    py::bytes input("hello.world");

    py::bytes expected_output("hello\\.world");

    EXPECT_EQ(RE2QuoteMetaShim(input), expected_output);

}



TEST_F(RE2QuoteMetaShimTest_60, EmptyString_60) {

    py::bytes input("");

    py::bytes expected_output("");

    EXPECT_EQ(RE2QuoteMetaShim(input), expected_output);

}



TEST_F(RE2QuoteMetaShimTest_60, SpecialCharacters_60) {

    py::bytes input(".*+?^${}()|[]\\");

    py::bytes expected_output("\\.\\*\\+\\?\\^\\$\\{\\}\\(\\)\\|\\[\\]\\\\");

    EXPECT_EQ(RE2QuoteMetaShim(input), expected_output);

}



TEST_F(RE2QuoteMetaShimTest_60, NoSpecialCharacters_60) {

    py::bytes input("abc123");

    py::bytes expected_output("abc123");

    EXPECT_EQ(RE2QuoteMetaShim(input), expected_output);

}



TEST_F(RE2QuoteMetaShimTest_60, LongString_60) {

    std::string long_string(1000, 'a');

    py::bytes input(long_string.c_str());

    py::bytes expected_output(long_string.c_str());

    EXPECT_EQ(RE2QuoteMetaShim(input), expected_output);

}



TEST_F(RE2QuoteMetaShimTest_60, MixedContent_60) {

    py::bytes input("abc.def123(g[h]{i}j|k\\l)m$n");

    py::bytes expected_output("abc\\.def123\\(g\\[h\\]\\{i\\}j\\|k\\\\l\\\)m\\$n");

    EXPECT_EQ(RE2QuoteMetaShim(input), expected_output);

}
