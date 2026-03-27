#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "convert.cpp" // Assuming the convert function is in this file or included properly



namespace Exiv2 {

    bool convertStringCharsetIconv([[maybe_unused]] std::string& str, const char* from, const char* to);

    bool convertStringCharsetWindows([[maybe_unused]] std::string& str, const char* from, const char* to);

}



using namespace testing;

using namespace Exiv2;



class ConvertTest_1864 : public Test {

protected:

    std::string testStr;

};



TEST_F(ConvertTest_1864, SameCharsetReturnsTrue_1864) {

    testStr = "test";

    EXPECT_TRUE(convertStringCharset(testStr, "UTF-8", "UTF-8"));

}



#ifdef EXV_HAVE_ICONV

TEST_F(ConvertTest_1864, DifferentCharsetIconvAvailable_1864) {

    testStr = "test";

    EXPECT_CALL(*this, convertStringCharsetIconv(_, "UTF-8", "ISO-8859-1")).WillOnce(Return(true));

    EXPECT_TRUE(convertStringCharset(testStr, "UTF-8", "ISO-8859-1"));

}

#endif



#ifdef _WIN32

TEST_F(ConvertTest_1864, DifferentCharsetWindowsAvailable_1864) {

    testStr = "test";

    EXPECT_CALL(*this, convertStringCharsetWindows(_, "UTF-8", "ISO-8859-1")).WillOnce(Return(true));

    EXPECT_TRUE(convertStringCharset(testStr, "UTF-8", "ISO-8859-1"));

}

#endif



#ifndef EXV_HAVE_ICONV

#ifndef _WIN32

TEST_F(ConvertTest_1864, DifferentCharsetNoConversionAvailable_1864) {

    testStr = "test";

    EXPECT_FALSE(convertStringCharset(testStr, "UTF-8", "ISO-8859-1"));

}

#endif

#endif



// Mocking internal functions is not allowed, so we cannot directly test the failure cases of iconv or Windows conversion.

// However, we can test the boundary conditions and normal operation as shown above.



```


