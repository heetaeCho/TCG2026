#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class IptcdatumTest_684 : public ::testing::Test {

protected:

    Value::UniquePtr mockValue;

    IptcKey key{"IPTC", 0x1, 0x5, "ObjectName"};

    Iptcdatum iptcdatum{key, mockValue.get()};



    void SetUp() override {

        mockValue = std::make_unique<Value>(typeid(StringValue));

    }

};



TEST_F(IptcdatumTest_684, GetValue_ReturnsClonedValue_684) {

    Value::UniquePtr value = iptcdatum.getValue();

    EXPECT_NE(value.get(), mockValue.get());

    EXPECT_EQ(value->typeId(), mockValue->typeId());

}



TEST_F(IptcdatumTest_684, GetValue_ReturnsNullptrWhenNoValueSet_684) {

    Iptcdatum noValueIptc{key, nullptr};

    Value::UniquePtr value = noValueIptc.getValue();

    EXPECT_EQ(value.get(), nullptr);

}



TEST_F(IptcdatumTest_684, Key_ReturnsExpectedKeyString_684) {

    std::string expectedKey = "IPTC.Envelope.ObjectName";

    EXPECT_EQ(iptcdatum.key(), expectedKey);

}



TEST_F(IptcdatumTest_684, RecordName_ReturnsExpectedRecordName_684) {

    std::string expectedRecordName = "Envelope";

    EXPECT_EQ(iptcdatum.recordName(), expectedRecordName);

}



TEST_F(IptcdatumTest_684, Record_ReturnsExpectedRecordNumber_684) {

    uint16_t expectedRecord = 1;

    EXPECT_EQ(iptcdatum.record(), expectedRecord);

}



TEST_F(IptcdatumTest_684, FamilyName_ReturnsExpectedFamilyName_684) {

    const char* expectedFamilyName = "IPTC";

    EXPECT_STREQ(iptcdatum.familyName(), expectedFamilyName);

}



TEST_F(IptcdatumTest_684, GroupName_ReturnsExpectedGroupName_684) {

    std::string expectedGroupName = "Envelope";

    EXPECT_EQ(iptcdatum.groupName(), expectedGroupName);

}



TEST_F(IptcdatumTest_684, TagName_ReturnsExpectedTagName_684) {

    std::string expectedTagName = "ObjectName";

    EXPECT_EQ(iptcdatum.tagName(), expectedTagName);

}



TEST_F(IptcdatumTest_684, TypeId_ReturnsExpectedTypeId_684) {

    TypeId expectedTypeId = typeid(StringValue);

    EXPECT_EQ(iptcdatum.typeId(), expectedTypeId);

}
