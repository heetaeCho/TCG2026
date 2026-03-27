def test_lens_model_dictionary():

    lens_model_dict = {

        1: "Canon EF 28mm f/1.4L",

        2: "Canon EF 50mm f/1.2L USM",

        # ... (other mappings)

        65535: "n/a"

    }

    

    assert lens_model_dict[1] == "Canon EF 28mm f/1.4L", "Test case 1 failed"

    assert lens_model_dict[2] == "Canon EF 50mm f/1.2L USM", "Test case 2 failed"

    assert lens_model_dict[368] == "Sigma 56mm f/1.4 DC DN | C", "Test case 368 failed"

    assert lens_model_dict[61182] == "Canon RF 50mm F1.2 L USM", "Test case 61182 failed"

    assert lens_model_dict[65535] == "n/a", "Test case 65535 failed"



# Add more test cases as needed to cover all entries in the dictionary
