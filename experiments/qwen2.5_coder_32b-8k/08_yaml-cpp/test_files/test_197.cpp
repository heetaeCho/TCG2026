#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/iterator.h"



using namespace YAML::detail;



class IteratorBaseTest_197 : public ::testing::Test {

protected:

    struct DummyType {

        int value;

        explicit DummyType(int v) : value(v) {}

    };



    iterator_base::proxy<DummyType> proxy_instance_;

    

    IteratorBaseTest_197() : proxy_instance_(DummyType(42)) {}

};



TEST_F(IteratorBaseTest_197, ArrowOperatorReturnsAddressOfMRef_197) {

    EXPECT_EQ(&proxy_instance_.m_ref, proxy_instance_.operator->());

}



TEST_F(IteratorBaseTest_197, ConversionOperatorReturnsPointerToMRef_197) {

    V* ptr = static_cast<V*>(&proxy_instance_.m_ref);

    EXPECT_EQ(ptr, static_cast<V*>(proxy_instance_));

}
