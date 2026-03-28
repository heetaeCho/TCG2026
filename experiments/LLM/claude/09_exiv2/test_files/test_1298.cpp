#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

// Test that Xmpdatum::copy throws an error as expected
TEST(XmpdatumTest_1298, CopyThrowsError_1298) {
    Xmpdatum datum;
    byte buf[256];
    EXPECT_THROW(datum.copy(buf, littleEndian), Error);
}

TEST(XmpdatumTest_1298, CopyThrowsErrorBigEndian_1298) {
    Xmpdatum datum;
    byte buf[256];
    EXPECT_THROW(datum.copy(buf, bigEndian), Error);
}

TEST(XmpdatumTest_1298, CopyThrowsWithNullBuffer_1298) {
    Xmpdatum datum;
    EXPECT_THROW(datum.copy(nullptr, littleEndian), Error);
}

TEST(XmpdatumTest_1298, CopyThrowsCorrectErrorCode_1298) {
    Xmpdatum datum;
    byte buf[64];
    try {
        datum.copy(buf, littleEndian);
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerFunctionNotSupported);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but caught a different exception";
    }
}

TEST(XmpdatumTest_1298, CopyErrorMessageContainsCopy_1298) {
    Xmpdatum datum;
    byte buf[64];
    try {
        datum.copy(buf, bigEndian);
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        std::string what = e.what();
        // The error message should reference "copy" since that's the function name passed
        EXPECT_NE(what.find("copy"), std::string::npos);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but caught a different exception";
    }
}

// Test default construction of Xmpdatum if accessible
TEST(XmpdatumTest_1298, DefaultConstruction_1298) {
    EXPECT_NO_THROW(Xmpdatum datum);
}

// Test copy construction if available
TEST(XmpdatumTest_1298, CopyConstruction_1298) {
    Xmpdatum datum1;
    EXPECT_NO_THROW(Xmpdatum datum2(datum1));
}

// Test that copy throws regardless of byte order
TEST(XmpdatumTest_1298, CopyThrowsForInvalidByteOrder_1298) {
    Xmpdatum datum;
    byte buf[32];
    EXPECT_THROW(datum.copy(buf, invalidByteOrder), Error);
}
