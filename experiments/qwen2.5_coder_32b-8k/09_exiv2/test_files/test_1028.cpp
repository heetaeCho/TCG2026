#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include <sstream>



namespace Exiv2 {

    namespace Internal {

        std::ostream& printMinoltaSonyBoolInverseValue(std::ostream& os, const Value& value, const ExifData* metadata);

    }

}



using ::testing::_;

using ::testing::Return;

using ::testing::MockFunction;



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD1(operator[], Exiv2::Exifdatum&(const std::string& key));

    MOCK_METHOD1(findKey, Exiv2::ExifData::iterator(const Exiv2::ExifKey& key));

    MOCK_METHOD0(begin, Exiv2::ExifData::iterator());

    MOCK_METHOD0(end, Exiv2::ExifData::iterator());

    MOCK_CONST_METHOD0(empty, bool());

    MOCK_CONST_METHOD0(count, size_t());

    MOCK_METHOD1(add, void(const Exiv2::ExifKey& key, const Exiv2::Value* pValue));

    MOCK_METHOD1(add, void(const Exiv2::Exifdatum& exifdatum));

    MOCK_METHOD1(erase, Exiv2::ExifData::iterator(Exiv2::ExifData::iterator pos));

    MOCK_METHOD2(erase, Exiv2::ExifData::iterator(Exiv2::ExifData::iterator beg, Exiv2::ExifData::iterator end));

    MOCK_METHOD0(clear, void());

    MOCK_METHOD0(sortByKey, void());

    MOCK_METHOD0(sortByTag, void());

};



class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD1(write, std::ostream&(std::ostream& os));

    MOCK_CONST_METHOD1(toString, std::string(size_t n));

    MOCK_CONST_METHOD0(count, size_t());

    MOCK_CONST_METHOD0(typeId, Exiv2::TypeId());

};



TEST_F(MockExifDataTest_1028, PrintMinoltaSonyBoolInverseValue_NormalCase_1028) {

    MockValue mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, toString(_)).WillOnce(Return("0"));



    std::ostringstream oss;

    Exiv2::Internal::printMinoltaSonyBoolInverseValue(oss, mockValue, &mockMetadata);



    ASSERT_EQ(oss.str(), "Off");

}



TEST_F(MockExifDataTest_1028, PrintMinoltaSonyBoolInverseValue_BoundaryCase_1028) {

    MockValue mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, toString(_)).WillOnce(Return("1"));



    std::ostringstream oss;

    Exiv2::Internal::printMinoltaSonyBoolInverseValue(oss, mockValue, &mockMetadata);



    ASSERT_EQ(oss.str(), "On");

}



TEST_F(MockExifDataTest_1028, PrintMinoltaSonyBoolInverseValue_OutOfBoundsCase_1028) {

    MockValue mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(mockValue, toString(_)).WillOnce(Return("2"));



    std::ostringstream oss;

    Exiv2::Internal::printMinoltaSonyBoolInverseValue(oss, mockValue, &mockMetadata);



    ASSERT_EQ(oss.str(), "Unknown");

}



TEST_F(MockExifDataTest_1028, PrintMinoltaSonyBoolInverseValue_ExceptionalCase_1028) {

    MockValue mockValue;

    MockExifData mockMetadata;



    EXPECT_CALL(mockValue, count()).WillRepeatedly(Return(0));



    std::ostringstream oss;

    Exiv2::Internal::printMinoltaSonyBoolInverseValue(oss, mockValue, &mockMetadata);



    ASSERT_EQ(oss.str(), "Unknown");

}
