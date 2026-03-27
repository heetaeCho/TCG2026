#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPUtils.cpp"

#include "XMPMeta.hpp"



using namespace std;

using testing::_;

using testing::Return;



class XMPMetaMock : public XMPMeta {

public:

    MOCK_METHOD8(GetProperty, bool(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_StringPtr * propValue, XMP_StringLen * valueSize, XMP_OptionBits * options));

    MOCK_METHOD14(SetProperty, void(XMP_StringPtr schemaNS, XMP_StringPtr propName, XMP_StringPtr propValue, XMP_OptionBits options));

    MOCK_METHOD7(DoesPropertyExist, bool(XMP_StringPtr schemaNS, XMP_StringPtr propName));

};



class MoveLargestPropertyTest_1986 : public ::testing::Test {

protected:

    XMPMetaMock stdXMP;

    XMPMetaMock extXMP;

    PropSizeMap propSizes;



    void SetUp() override {

        // Initialize the properties for testing

        auto* schemaURI = new XMP_VarString("http://example.com/schema");

        auto* propName1 = new XMP_VarString("Property1");

        auto* propName2 = new XMP_VarString("Property2");



        propSizes.insert({100, {schemaURI, propName1}});

        propSizes.insert({200, {schemaURI, propName2}});

    }



    void TearDown() override {

        // Clean up the allocated memory

        for (auto& pair : propSizes) {

            delete pair.second.first;

            delete pair.second.second;

        }

        propSizes.clear();

    }

};



TEST_F(MoveLargestPropertyTest_1986, NormalOperation_1986) {

    EXPECT_CALL(stdXMP, DoesPropertyExist("http://example.com/schema", "Property2")).WillOnce(Return(true));

    EXPECT_CALL(extXMP, SetProperty("http://example.com/schema", "Property2", _, _)).Times(1);

    

    size_t result = MoveLargestProperty(stdXMP, &extXMP, propSizes);



    ASSERT_EQ(result, 200);

    EXPECT_TRUE(propSizes.find(200) == propSizes.end());

}



TEST_F(MoveLargestPropertyTest_1986, BoundaryCondition_EmptyPropSizeMap_1986) {

    PropSizeMap emptyPropSizes;

    ASSERT_THROW(MoveLargestProperty(stdXMP, &extXMP, emptyPropSizes), XMP_Error);

}



TEST_F(MoveLargestPropertyTest_1986, PropertyDoesNotExist_1986) {

    EXPECT_CALL(stdXMP, DoesPropertyExist("http://example.com/schema", "Property2")).WillOnce(Return(false));

    

    size_t result = MoveLargestProperty(stdXMP, &extXMP, propSizes);



    ASSERT_EQ(result, 200);

    EXPECT_TRUE(propSizes.find(200) != propSizes.end()); // Property should not be moved

}



TEST_F(MoveLargestPropertyTest_1986, ExternalXMPLNull_1986) {

    XMPMeta* extXMPNull = nullptr;

    EXPECT_CALL(stdXMP, DoesPropertyExist("http://example.com/schema", "Property2")).WillOnce(Return(true));

    

    size_t result = MoveLargestProperty(stdXMP, extXMPNull, propSizes);



    ASSERT_EQ(result, 200);

    EXPECT_TRUE(propSizes.find(200) != propSizes.end()); // Property should not be moved

}
