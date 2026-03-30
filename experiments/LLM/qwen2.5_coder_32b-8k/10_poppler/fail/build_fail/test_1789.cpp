#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    typedef int SECStatus;

    typedef struct PLArenaPool PLArenaPool;



    static SECStatus my_NSS_CMSArray_Add(PLArenaPool *poolp, void ***array, void *obj);

}



class NSSCryptoSignBackendTest_1789 : public ::testing::Test {

protected:

    PLArenaPool pool;

    void **array = nullptr;

};



TEST_F(NSSCryptoSignBackendTest_1789, AddSingleElementSuccessfully_1789) {

    void *obj = reinterpret_cast<void *>(0x1);

    EXPECT_EQ(my_NSS_CMSArray_Add(&pool, &array, obj), SECSuccess);

    ASSERT_NE(array, nullptr);

    EXPECT_EQ(array[0], obj);

    EXPECT_EQ(array[1], nullptr);

}



TEST_F(NSSCryptoSignBackendTest_1789, AddMultipleElementsSuccessfully_1789) {

    void *obj1 = reinterpret_cast<void *>(0x1);

    void *obj2 = reinterpret_cast<void *>(0x2);



    EXPECT_EQ(my_NSS_CMSArray_Add(&pool, &array, obj1), SECSuccess);

    EXPECT_EQ(my_NSS_CMSArray_Add(&pool, &array, obj2), SECSuccess);



    ASSERT_NE(array, nullptr);

    EXPECT_EQ(array[0], obj1);

    EXPECT_EQ(array[1], obj2);

    EXPECT_EQ(array[2], nullptr);

}



TEST_F(NSSCryptoSignBackendTest_1789, AddElementToNonEmptyArraySuccessfully_1789) {

    void *obj1 = reinterpret_cast<void *>(0x1);

    array = static_cast<void **>(::operator new(2 * sizeof(void *)));

    array[0] = obj1;

    array[1] = nullptr;



    void *obj2 = reinterpret_cast<void *>(0x2);

    EXPECT_EQ(my_NSS_CMSArray_Add(&pool, &array, obj2), SECSuccess);



    ASSERT_NE(array, nullptr);

    EXPECT_EQ(array[0], obj1);

    EXPECT_EQ(array[1], obj2);

    EXPECT_EQ(array[2], nullptr);



    ::operator delete(array);

}



TEST_F(NSSCryptoSignBackendTest_1789, HandleNullPoolPointer_1789) {

    void *obj = reinterpret_cast<void *>(0x1);

    PLArenaPool *null_pool = nullptr;

    EXPECT_EQ(my_NSS_CMSArray_Add(null_pool, &array, obj), SECFailure);

}



TEST_F(NSSCryptoSignBackendTest_1789, HandleNullArrayPointer_1789) {

    void *obj = reinterpret_cast<void *>(0x1);

    void ***null_array = nullptr;

    EXPECT_EQ(my_NSS_CMSArray_Add(&pool, null_array, obj), SECFailure);

}



TEST_F(NSSCryptoSignBackendTest_1789, HandleNullObjectPointer_1789) {

    void *obj = nullptr;

    EXPECT_EQ(my_NSS_CMSArray_Add(&pool, &array, obj), SECSuccess);

    ASSERT_NE(array, nullptr);

    EXPECT_EQ(array[0], obj);

    EXPECT_EQ(array[1], nullptr);

}
