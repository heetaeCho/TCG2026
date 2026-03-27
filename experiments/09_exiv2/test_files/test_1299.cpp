#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/xmp.hpp>



namespace Exiv2 {

    class MockExifData : public ExifData {

    public:

        MOCK_METHOD(void, dummyMethod, (), (const));

    };

}



class XmpdatumTest_1299 : public ::testing::Test {

protected:

    Exiv2::Xmpdatum xmpDatum;

    std::ostringstream oss;

    Exiv2::MockExifData mockExifData;

};



TEST_F(XmpdatumTest_1299, WriteToStream_1299) {

    // Assuming key() and value() are properly set in Xmpdatum

    std::string expectedOutput = "Key: Value"; // This is a placeholder. Actual output depends on key() and value().

    EXPECT_CALL(mockExifData, dummyMethod()).Times(0); // Ensure no interaction with mockExifData



    xmpDatum.write(oss, &mockExifData);

    EXPECT_EQ(expectedOutput, oss.str());

}



TEST_F(XmpdatumTest_1299, WriteWithNullExifDataPointer_1299) {

    std::string expectedOutput = "Key: Value"; // This is a placeholder. Actual output depends on key() and value().

    

    xmpDatum.write(oss, nullptr);

    EXPECT_EQ(expectedOutput, oss.str());

}



TEST_F(XmpdatumTest_1299, BoundaryConditionEmptyKeyAndValue_1299) {

    std::string expectedOutput = ": "; // This is a placeholder. Actual output depends on key() and value().

    

    xmpDatum.write(oss, &mockExifData);

    EXPECT_EQ(expectedOutput, oss.str());

}



// Assuming there are no exceptional or error cases observable through the interface based on the provided code.

```


