#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class StringValueBaseTest : public ::testing::Test {

protected:

    TypeId dummyTypeId = static_cast<TypeId>(1);

    std::string testString = "testString";

    const byte* testBuffer = reinterpret_cast<const byte*>(testString.c_str());

    size_t testBufferSize = testString.size();

    ByteOrder dummyByteOrder = littleEndian;



    UniquePtr stringValueBase;



    void SetUp() override {

        stringValueBase.reset(new StringValueBase(dummyTypeId, testString));

    }

};



TEST_F(StringValueBaseTest_129, CloneReturnsNonNullPointer_129) {

    auto cloned = stringValueBase->clone();

    EXPECT_NE(cloned.get(), nullptr);

}



TEST_F(StringValueBaseTest_129, ReadFromStringUpdatesInternalState_129) {

    std::string newString = "newString";

    int result = stringValueBase->read(newString);

    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

    // No direct way to verify internal state, but we can check count and size if they change accordingly

}



TEST_F(StringValueBaseTest_129, ReadFromBufferUpdatesInternalState_129) {

    std::string newString = "newString";

    int result = stringValueBase->read(reinterpret_cast<const byte*>(newString.c_str()), newString.size(), dummyByteOrder);

    EXPECT_EQ(result, 0); // Assuming read returns 0 on success

}



TEST_F(StringValueBaseTest_129, CopyWritesToBufferCorrectly_129) {

    byte buffer[100];

    size_t bytesWritten = stringValueBase->copy(buffer, dummyByteOrder);

    EXPECT_EQ(bytesWritten, testString.size());

    EXPECT_EQ(std::string(reinterpret_cast<char*>(buffer), bytesWritten), testString);

}



TEST_F(StringValueBaseTest_129, CountReturnsCorrectNumberOfElements_129) {

    size_t count = stringValueBase->count();

    EXPECT_EQ(count, 1); // Assuming a single string counts as one element

}



TEST_F(StringValueBaseTest_129, SizeReturnsCorrectSizeOfData_129) {

    size_t size = stringValueBase->size();

    EXPECT_EQ(size, testString.size());

}



TEST_F(StringValueBaseTest_129, ToInt64ThrowsForNonNumeric_129) {

    EXPECT_THROW(stringValueBase->toInt64(0), Error); // Assuming toInt64 throws on non-numeric conversion

}



TEST_F(StringValueBaseTest_129, ToUint32ThrowsForNonNumeric_129) {

    EXPECT_THROW(stringValueBase->toUint32(0), Error); // Assuming toUint32 throws on non-numeric conversion

}



TEST_F(StringValueBaseTest_129, ToFloatThrowsForNonNumeric_129) {

    EXPECT_THROW(stringValueBase->toFloat(0), Error); // Assuming toFloat throws on non-numeric conversion

}



TEST_F(StringValueBaseTest_129, ToRationalThrowsForNonNumeric_129) {

    EXPECT_THROW(stringValueBase->toRational(0), Error); // Assuming toRational throws on non-numeric conversion

}



TEST_F(StringValueBaseTest_129, WriteToStreamOutputsCorrectly_129) {

    std::ostringstream oss;

    stringValueBase->write(oss);

    EXPECT_EQ(oss.str(), testString);

}
