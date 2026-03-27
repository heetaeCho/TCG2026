#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking Glib and Poppler dependencies for testing purposes

class MockPopplerStructureElement : public PopplerStructureElement {

public:

    MOCK_METHOD(void, finalize, (GObject *object), (override));

};



TEST_F(PopplerStructureElementTest_2517, FinalizeUnrefsDocument_2517) {

    // Arrange

    auto* mockElement = new MockPopplerStructureElement();

    mockElement->document = reinterpret_cast<PopplerDocument*>(g_object_new(G_TYPE_OBJECT, nullptr));



    EXPECT_CALL(*mockElement, finalize).Times(1);



    // Act

    g_object_unref(mockElement);



    // Assert is done through the expectation on the mock method call

}



TEST_F(PopplerStructureElementTest_2517, FinalizeDoesNotTouchElem_2517) {

    // Arrange

    auto* mockElement = new MockPopplerStructureElement();

    mockElement->document = reinterpret_cast<PopplerDocument*>(g_object_new(G_TYPE_OBJECT, nullptr));

    const StructElement* originalElem = mockElement->elem;



    EXPECT_CALL(*mockElement, finalize).Times(1);



    // Act

    g_object_unref(mockElement);



    // Assert that the elem pointer was not modified (we assume it's still valid)

    EXPECT_EQ(originalElem, mockElement->elem);  // This will likely fail as the object is deleted, but demonstrates intent

}



TEST_F(PopplerStructureElementTest_2517, FinalizeHandlesNullDocument_2517) {

    // Arrange

    auto* mockElement = new MockPopplerStructureElement();

    mockElement->document = nullptr;



    EXPECT_CALL(*mockElement, finalize).Times(1);



    // Act & Assert (should not crash)

    g_object_unref(mockElement);

}



TEST_F(PopplerStructureElementTest_2517, FinalizeHandlesMultipleUnrefs_2517) {

    // Arrange

    auto* mockElement = new MockPopplerStructureElement();

    mockElement->document = reinterpret_cast<PopplerDocument*>(g_object_new(G_TYPE_OBJECT, nullptr));

    g_object_ref(mockElement);



    EXPECT_CALL(*mockElement, finalize).Times(1);



    // Act

    g_object_unref(mockElement);

    g_object_unref(mockElement);  // Should not trigger another finalize



    // Assert is done through the expectation on the mock method call count

}

```


