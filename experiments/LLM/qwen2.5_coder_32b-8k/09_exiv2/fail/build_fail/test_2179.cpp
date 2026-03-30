#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpdatumImplTest : public ::testing::Test {

protected:

    void SetUp() override {

        key = std::make_unique<XmpKey>("Xmp.dc.title");

        value = std::make_unique<Value>(Value::string);

        impl = std::make_unique<Xmpdatum::Impl>(*key, value.get());

    }



    XmpKey::UniquePtr key;

    Value::UniquePtr value;

    std::unique_ptr<Xmpdatum::Impl> impl;

};



TEST_F(XmpdatumImplTest_2179, ConstructorWithValidKeyAndValue_2179) {

    EXPECT_EQ(impl->key_->key(), "Xmp.dc.title");

    EXPECT_NE(impl->value_.get(), nullptr);

}



TEST_F(XmpdatumImplTest_2179, ConstructorWithNullValue_2179) {

    auto impl_with_null_value = std::make_unique<Xmpdatum::Impl>(*key, nullptr);

    EXPECT_EQ(impl_with_null_value->key_->key(), "Xmp.dc.title");

    EXPECT_EQ(impl_with_null_value->value_.get(), nullptr);

}



TEST_F(XmpdatumImplTest_2179, CopyConstructor_ShouldCopyKeyAndValue_2179) {

    auto impl_copy = std::make_unique<Xmpdatum::Impl>(*impl);

    EXPECT_EQ(impl_copy->key_->key(), "Xmp.dc.title");

    EXPECT_NE(impl_copy->value_.get(), nullptr);

}



TEST_F(XmpdatumImplTest_2179, AssignmentOperator_ShouldCopyKeyAndValue_2179) {

    Xmpdatum::Impl impl2(*key, value.get());

    impl2 = *impl;

    EXPECT_EQ(impl2.key_->key(), "Xmp.dc.title");

    EXPECT_NE(impl2.value_.get(), nullptr);

}



TEST_F(XmpdatumImplTest_2179, KeyClone_ShouldReturnUniquePtrToKey_2179) {

    auto cloned_key = impl->key_->clone();

    EXPECT_EQ(cloned_key->key(), "Xmp.dc.title");

}



TEST_F(XmpdatumImplTest_2179, ValueClone_ShouldReturnUniquePtrToValue_2179) {

    auto cloned_value = impl->value_->clone();

    EXPECT_NE(cloned_value.get(), nullptr);

}



TEST_F(XmpdatumImplTest_2179, Destructor_ShouldNotCrash_2179) {

    // The destructor is tested by letting the unique_ptr go out of scope

}
