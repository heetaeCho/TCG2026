#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"



using namespace testing;



class MockGAsyncReadyCallback {

public:

    MOCK_METHOD5(Call, void(GObject*, GAsyncResult*, gpointer));

};



void mock_callback_wrapper(GObject* source_object, GAsyncResult* res, gpointer user_data) {

    static_cast<MockGAsyncReadyCallback*>(user_data)->Call(source_object, res, nullptr);

}



class PopplerFormFieldSignatureValidateTest_2323 : public Test {

protected:

    PopplerFormField field;

    MockGAsyncReadyCallback mock_callback;



    GCancellable* cancellable = nullptr;

};



TEST_F(PopplerFormFieldSignatureValidateTest_2323, ValidateAsyncWithNormalFlags_2323) {

    poppler_form_field_signature_validate_async(&field, POPPLER_SIGNATURE_VALIDATION_NONE, cancellable, 

                                               reinterpret_cast<GAsyncReadyCallback>(mock_callback_wrapper), &mock_callback);

    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);

}



TEST_F(PopplerFormFieldSignatureValidateTest_2323, ValidateAsyncWithAllFlags_2323) {

    poppler_form_field_signature_validate_async(&field, POPPLER_SIGNATURE_VALIDATION_ALL, cancellable, 

                                               reinterpret_cast<GAsyncReadyCallback>(mock_callback_wrapper), &mock_callback);

    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);

}



TEST_F(PopplerFormFieldSignatureValidateTest_2323, ValidateAsyncWithNullCancellable_2323) {

    poppler_form_field_signature_validate_async(&field, POPPLER_SIGNATURE_VALIDATION_NONE, nullptr, 

                                               reinterpret_cast<GAsyncReadyCallback>(mock_callback_wrapper), &mock_callback);

    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);

}



TEST_F(PopplerFormFieldSignatureValidateTest_2323, ValidateAsyncWithNullField_2323) {

    poppler_form_field_signature_validate_async(nullptr, POPPLER_SIGNATURE_VALIDATION_NONE, cancellable, 

                                               reinterpret_cast<GAsyncReadyCallback>(mock_callback_wrapper), &mock_callback);

    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);

}



TEST_F(PopplerFormFieldSignatureValidateTest_2323, ValidateAsyncWithNullCallback_2323) {

    poppler_form_field_signature_validate_async(&field, POPPLER_SIGNATURE_VALIDATION_NONE, cancellable, nullptr, &mock_callback);

    // No expectation as callback is null

}



TEST_F(PopplerFormFieldSignatureValidateTest_2323, ValidateAsyncWithUserData_2323) {

    gpointer user_data = reinterpret_cast<gpointer>(new int(42));

    poppler_form_field_signature_validate_async(&field, POPPLER_SIGNATURE_VALIDATION_NONE, cancellable, 

                                               reinterpret_cast<GAsyncReadyCallback>(mock_callback_wrapper), user_data);

    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);



    delete reinterpret_cast<int*>(user_data); // Cleanup user data

}
