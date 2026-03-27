#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "./TestProjects/exiv2/src/image_int.hpp"



namespace Exiv2 { namespace Internal {



template <typename T>

class BinaryToStringHelperTest : public ::testing::Test {

protected:

    binaryToStringHelper<T> helper_;

};



using TestTypes = ::testing::Types<std::vector<char>, std::string>;

TYPED_TEST_SUITE(BinaryToStringHelperTest, TestTypes);



TYPED_TEST(BinaryToStringHelperTest_62, EmptyBufferOutputsNothing_62) {

    std::ostringstream oss;

    oss << this->helper_;

    EXPECT_EQ(oss.str(), "");

}



TYPED_TEST(BinaryToStringHelperTest_62, SinglePrintableCharOutputsSameChar_62) {

    char data[] = {'A'};

    this->helper_.buf_ = TypeParam(data, data + 1);

    std::ostringstream oss;

    oss << this->helper_;

    EXPECT_EQ(oss.str(), "A");

}



TYPED_TEST(BinaryToStringHelperTest_62, SingleNonPrintableCharOutputsDot_62) {

    char data[] = {'\x01'};

    this->helper_.buf_ = TypeParam(data, data + 1);

    std::ostringstream oss;

    oss << this->helper_;

    EXPECT_EQ(oss.str(), ".");

}



TYPED_TEST(BinaryToStringHelperTest_62, MultiplePrintableCharsOutputsSameChars_62) {

    char data[] = {'H', 'e', 'l', 'l', 'o'};

    this->helper_.buf_ = TypeParam(data, data + 5);

    std::ostringstream oss;

    oss << this->helper_;

    EXPECT_EQ(oss.str(), "Hello");

}



TYPED_TEST(BinaryToStringHelperTest_62, MultipleCharsWithNonPrintableOutputsDotsAndChars_62) {

    char data[] = {'H', '\x01', 'l', '\x7F', 'o'};

    this->helper_.buf_ = TypeParam(data, data + 5);

    std::ostringstream oss;

    oss << this->helper_;

    EXPECT_EQ(oss.str(), "H.l.o");

}



TYPED_TEST(BinaryToStringHelperTest_62, BufferWithTrailingNullDoesNotOutputExtraDot_62) {

    char data[] = {'A', '\0'};

    this->helper_.buf_ = TypeParam(data, data + 2);

    std::ostringstream oss;

    oss << this->helper_;

    EXPECT_EQ(oss.str(), "A");

}



TYPED_TEST(BinaryToStringHelperTest_62, BufferWithNullInMiddleOutputsDot_62) {

    char data[] = {'H', '\0', 'l'};

    this->helper_.buf_ = TypeParam(data, data + 3);

    std::ostringstream oss;

    oss << this->helper_;

    EXPECT_EQ(oss.str(), "H.l");

}



}} // namespace Exiv2::Internal
