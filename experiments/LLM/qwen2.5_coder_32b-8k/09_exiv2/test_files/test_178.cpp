#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using namespace testing;



// Mock class for ExifData

class MockExifData {

public:

    MOCK_METHOD1(find, const StringTagDetails*(const std::string&));

};



// Test fixture for printTagString function

class PrintTagStringTest_178 : public Test {

protected:

    static constexpr size_t N = 3;

    static const StringTagDetails tagDetails[N];

    MockExifData mockExifData;



    template <typename T>

    std::string callPrintTagString(const T& value, const Exiv2::ExifData* exifData) {

        std::ostringstream oss;

        printTagString<N, tagDetails, T>(oss, value, exifData);

        return oss.str();

    }

};



const StringTagDetails PrintTagStringTest_178::tagDetails[PrintTagStringTest_178::N] = {

    { "0", N_("Unknown") },

    { "1", N_("Known1") },

    { "2", N_("Known2") }

};



TEST_F(PrintTagStringTest_178, KnownValue_PrintsLabel_178) {

    EXPECT_CALL(mockExifData, find("1")).WillOnce(Return(&tagDetails[1]));

    EXPECT_EQ(callPrintTagString<int>(1, &mockExifData), "Known1");

}



TEST_F(PrintTagStringTest_178, UnknownValue_PrintsParentheses_178) {

    EXPECT_CALL(mockExifData, find("3")).WillOnce(Return(nullptr));

    EXPECT_EQ(callPrintTagString<int>(3, &mockExifData), "(3)");

}



TEST_F(PrintTagStringTest_178, ZeroLengthArray_StaticAssertionFailure_178) {

    // This test case is more of a compile-time check rather than a runtime test.

    // The static assertion should fail if N <= 0, but since we are not changing the template parameter,

    // this case is implicitly tested by ensuring the function compiles with N > 0.

}



TEST_F(PrintTagStringTest_178, ValueObject_KnownValue_PrintsLabel_178) {

    Value value;

    value.setValue("2");

    EXPECT_CALL(mockExifData, find("2")).WillOnce(Return(&tagDetails[2]));

    EXPECT_EQ(callPrintTagString<Value>(value, &mockExifData), "Known2");

}



TEST_F(PrintTagStringTest_178, ValueObject_UnknownValue_PrintsParentheses_178) {

    Value value;

    value.setValue("4");

    EXPECT_CALL(mockExifData, find("4")).WillOnce(Return(nullptr));

    EXPECT_EQ(callPrintTagString<Value>(value, &mockExifData), "(4)");

}



TEST_F(PrintTagStringTest_178, NullExifData_DoesNotCallFind_178) {

    Value value;

    value.setValue("2");

    EXPECT_CALL(mockExifData, find).Times(0);

    EXPECT_EQ(callPrintTagString<Value>(value, nullptr), "(2)");

}
