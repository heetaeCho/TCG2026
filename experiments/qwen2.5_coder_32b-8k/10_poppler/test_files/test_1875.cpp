def test_unique_elements():

    assert unique_elements([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

    assert unique_elements([1, 1, 2, 2, 3, 3, 4, 4, 5, 5]) == [1, 2, 3, 4, 5]

    assert unique_elements([]) == []

    assert unique_elements([5, 4, 3, 2, 1]) == [1, 2, 3, 4, 5]

    assert unique_elements([10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    assert unique_elements([1, 2, 3, 4, 5, 1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

    assert unique_elements([1]) == [1]

    assert unique_elements([1, 1, 1, 1, 1]) == [1]

    assert unique_elements([10, 20, 30, 40, 50]) == [10, 20, 30, 40, 50]

    assert unique_elements([50, 40, 30, 20, 10]) == [10, 20, 30, 40, 50]
