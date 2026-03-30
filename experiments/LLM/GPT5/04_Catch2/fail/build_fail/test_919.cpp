// File: tests/detail_convert_range_919_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include <initializer_list>

// Include the amalgamated header that provides the function under test
// and the public StringMaker interface we use as oracle.
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

using ::Catch::StringMaker;

// NOTE: We never rely on internal/private state or re-implement logic.
// We only check the observable output string against Catch's public
// StringMaker<T>::convert for the same input.

TEST(DetailConvertTest_919, VectorInt_Normal_919) {
    std::vector<int> v{1, 2, 3};

    const std::string via_detail =
        ::Catch::Catch::Detail::convert(v);  // function under test
    const std::string via_public =
        StringMaker<decltype(v)>::convert(v); // public reference behavior

    EXPECT_EQ(via_detail, via_public);
}

TEST(DetailConvertTest_919, VectorInt_Empty_919) {
    std::vector<int> v;

    const std::string via_detail =
        ::Catch::Catch::Detail::convert(v);
    const std::string via_public =
        StringMaker<decltype(v)>::convert(v);

    EXPECT_EQ(via_detail, via_public);
}

TEST(DetailConvertTest_919, VectorString_WithSpacesAndEmpty_919) {
    std::vector<std::string> v{"alpha", "beta gamma", ""};

    const std::string via_detail =
        ::Catch::Catch::Detail::convert(v);
    const std::string via_public =
        StringMaker<decltype(v)>::convert(v);

    EXPECT_EQ(via_detail, via_public);
}

TEST(DetailConvertTest_919, CArray_Int_919) {
    const int arr[3] = {4, 5, 6};

    const std::string via_detail =
        ::Catch::Catch::Detail::convert(arr);
    const std::string via_public =
        StringMaker<decltype(arr)>::convert(arr);

    EXPECT_EQ(via_detail, via_public);
}

TEST(DetailConvertTest_919, StdArray_Char_919) {
    const std::array<char, 3> a{{'x', 'y', 'z'}};

    const std::string via_detail =
        ::Catch::Catch::Detail::convert(a);
    const std::string via_public =
        StringMaker<decltype(a)>::convert(a);

    EXPECT_EQ(via_detail, via_public);
}

TEST(DetailConvertTest_919, VectorBool_919) {
    // vector<bool> has a specialized proxy reference; ensure behavior matches.
    std::vector<bool> vb;
    vb.push_back(true);
    vb.push_back(false);
    vb.push_back(true);

    const std::string via_detail =
        ::Catch::Catch::Detail::convert(vb);
    const std::string via_public =
        StringMaker<decltype(vb)>::convert(vb);

    EXPECT_EQ(via_detail, via_public);
}

TEST(DetailConvertTest_919, InitializerList_Int_919) {
    const std::initializer_list<int> il = {7, 8, 9};

    const std::string via_detail =
        ::Catch::Catch::Detail::convert(il);
    const std::string via_public =
        StringMaker<decltype(il)>::convert(il);

    EXPECT_EQ(via_detail, via_public);
}

} // namespace
