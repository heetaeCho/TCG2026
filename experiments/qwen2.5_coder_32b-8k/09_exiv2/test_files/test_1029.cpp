#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>



namespace Exiv2 {

namespace Internal {



std::ostream& printMinoltaSonyAFAreaMode(std::ostream& os, const Value& value, const ExifData* metadata);



} // namespace Internal

} // namespace Exiv2



using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(typeId, Exiv2::TypeId());

    MOCK_CONST_METHOD1(toInt64, int64_t(size_t n));

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD1(findKey, Exiv2::ExifData::const_iterator(const Exiv2::ExifKey& key)) const;

};



TEST_F(WriteBatchTest_1029, PrintMinoltaSonyAFAreaMode_Wide_1029) {

    NiceMock<MockValue> mockValue;

    EXPECT_CALL(mockValue, toInt64(_)).WillOnce(Return(0));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyAFAreaMode(os, mockValue, nullptr);



    EXPECT_EQ("Wide", os.str());

}



TEST_F(WriteBatchTest_1029, PrintMinoltaSonyAFAreaMode_Local_1029) {

    NiceMock<MockValue> mockValue;

    EXPECT_CALL(mockValue, toInt64(_)).WillOnce(Return(1));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyAFAreaMode(os, mockValue, nullptr);



    EXPECT_EQ("Local", os.str());

}



TEST_F(WriteBatchTest_1029, PrintMinoltaSonyAFAreaMode_Spot_1029) {

    NiceMock<MockValue> mockValue;

    EXPECT_CALL(mockValue, toInt64(_)).WillOnce(Return(2));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyAFAreaMode(os, mockValue, nullptr);



    EXPECT_EQ("Spot", os.str());

}



TEST_F(WriteBatchTest_1029, PrintMinoltaSonyAFAreaMode_OutOfBounds_1029) {

    NiceMock<MockValue> mockValue;

    EXPECT_CALL(mockValue, toInt64(_)).WillOnce(Return(3));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyAFAreaMode(os, mockValue, nullptr);



    EXPECT_EQ("", os.str());

}



TEST_F(WriteBatchTest_1029, PrintMinoltaSonyAFAreaMode_NegativeIndex_1029) {

    NiceMock<MockValue> mockValue;

    EXPECT_CALL(mockValue, toInt64(_)).WillOnce(Return(-1));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyAFAreaMode(os, mockValue, nullptr);



    EXPECT_EQ("", os.str());

}
