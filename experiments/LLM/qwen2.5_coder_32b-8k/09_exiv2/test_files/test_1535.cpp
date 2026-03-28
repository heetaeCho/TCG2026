#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"  // Assuming this file contains the NikonArrayIdx and Key definitions



namespace Exiv2 {

namespace Internal {



struct MockKey : public Key {

    MockKey(const char* ver, int tag = 0, int size = 0) : Key{ver}, tag_{tag}, size_{size} {}

    int tag_;

    int size_;

};



TEST(NikonArrayIdxTest_1535, EqualityOperatorSameTagAndVersion_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = "abc";

    nikonIdx.size_ = 0;



    MockKey key("abc", 123);



    EXPECT_TRUE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorDifferentTag_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = "abc";

    nikonIdx.size_ = 0;



    MockKey key("abc", 456);



    EXPECT_FALSE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorDifferentVersion_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = "abc";

    nikonIdx.size_ = 0;



    MockKey key("def", 123);



    EXPECT_FALSE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorSameTagAndVersionNonZeroSize_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = "abc";

    nikonIdx.size_ = 7;



    MockKey key("abc", 123, 7);



    EXPECT_TRUE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorSameTagAndVersionDifferentSize_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = "abc";

    nikonIdx.size_ = 7;



    MockKey key("abc", 123, 8);



    EXPECT_FALSE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorNullVersion_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = nullptr;

    nikonIdx.size_ = 0;



    MockKey key(nullptr, 123);



    EXPECT_TRUE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorNullVersionDifferentTag_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = nullptr;

    nikonIdx.size_ = 0;



    MockKey key(nullptr, 456);



    EXPECT_FALSE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorEmptyVersion_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = "";

    nikonIdx.size_ = 0;



    MockKey key("", 123);



    EXPECT_TRUE(nikonIdx == key);

}



TEST(NikonArrayIdxTest_1535, EqualityOperatorEmptyVersionDifferentTag_1535) {

    NikonArrayIdx nikonIdx;

    nikonIdx.tag_ = 123;

    nikonIdx.ver_ = "";

    nikonIdx.size_ = 0;



    MockKey key("", 456);



    EXPECT_FALSE(nikonIdx == key);

}



}  // namespace Internal

}  // namespace Exiv2
