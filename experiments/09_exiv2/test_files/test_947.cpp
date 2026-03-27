def test_canon_lens_models():

    assert lens_model(4) == "Canon EF 10-22mm f/3.5-6.3 IS USM"

    assert lens_model(8) == "Canon EF 16-35mm f/2.8 L II USM"

    assert lens_model(17) == "Canon EF-S 10-18mm f/4.5-5.6 IS STM"

    assert lens_model(18) == "Sigma 18-200mm f/3.5-6.3 DC OS HSM"

    assert lens_model(19) == "Canon EF-S 17-55mm f/2.8 IS USM"

    assert lens_model(20) == "Tamron SP AF 17-35mm f/2.8 Di LD Aspherical IF"

    assert lens_model(24) == "Sigma 18-300mm f/3.5-6.3 DC OS HSM"

    assert lens_model(25) == "Tamron SP AF 17-50mm f/2.8 XR Di II LD Aspherical IF Macro"

    assert lens_model(29) == "Sigma 24-105mm F2.8 EX DG OS HSM"

    assert lens_model(30) == "Canon EF-S 15-85mm f/3.5-5.6 IS USM"

    assert lens_model(33) == "Canon EF 17-40mm f/4L USM"

    assert lens_model(34) == "Tamron SP AF 24-70mm f/2.8 Di VC USD"

    assert lens_model(35) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(36) == "Canon EF-S 18-200mm f/3.5-5.6 IS STM"

    assert lens_model(37) == "Canon EF-S 16-50mm f/2.8 IS STM"

    assert lens_model(43) == "Canon EF 16-35mm f/2.8L III USM"

    assert lens_model(44) == "Canon EF-S 10-22mm f/3.5-5.6 IS STM"

    assert lens_model(45) == "Sigma 15-30mm F3.5-6.3 DC DN | C"

    assert lens_model(48) == "Tamron SP AF 70-300mm f/4-5.6 Di VC USD"

    assert lens_model(52) == "Canon EF-S 18-135mm f/3.5-5.6 IS STM"

    assert lens_model(53) == "Tamron SP AF 70-300mm f/4-5.6 Di VC USD G2"

    assert lens_model(55) == "Canon EF-S 18-55mm f/3.5-5.6 IS STM"

    assert lens_model(57) == "Sigma 18-150mm f/3.5-6.3 DC OS HSM | A"

    assert lens_model(59) == "Tamron SP AF 24-240mm f/3.5-6.3 Di II VC"

    assert lens_model(60) == "Canon EF-S 18-135mm f/3.5-5.6 IS USM"

    assert lens_model(61) == "Tamron SP AF 24-70mm f/2.8 Di III RXD"

    assert lens_model(62) == "Sigma 18-50mm F2.8 Macro Art"

    assert lens_model(63) == "Canon EF-S 10-18mm f/4.5-5.6 IS STM"

    assert lens_model(64) == "Tamron SP AF 17-70mm f/2.8 Di VC USD G2"

    assert lens_model(65) == "Sigma 24-35mm F2 DG DN | C"

    assert lens_model(66) == "Canon EF-S 60mm f/2.8 Macro USM"

    assert lens_model(67) == "Tamron SP AF 15-30mm f/2.8 Di VC USD G2"

    assert lens_model(69) == "Sigma 100-400mm F5-6.7 DC OS HSM"

    assert lens_model(70) == "Canon EF-S 15-45mm f/3.5-5.6 IS STM"

    assert lens_model(72) == "Tamron SP AF 85mm f/1.8 Di VC USD G2"

    assert lens_model(73) == "Sigma 85mm F1.2 EX DG OS HSM Art"

    assert lens_model(74) == "Canon EF-S 55-250mm f/4-5.6 IS STM"

    assert lens_model(75) == "Tamron SP AF 100-300mm f/4-5.6 Di VC USD G2"

    assert lens_model(80) == "Canon EF-S 24mm f/2.8 STM"

    assert lens_model(81) == "Sigma 24mm F2.8 Macro Art"

    assert lens_model(82) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(83) == "Canon EF-S 55mm f/1.8 STM"

    assert lens_model(84) == "Sigma 56mm F1.4 DC DN | C"

    assert lens_model(90) == "Tamron SP AF 70-200mm f/2.8 Di VC USD G2"

    assert lens_model(92) == "Canon EF-S 35mm f/2.8 Macro IS STM"

    assert lens_model(104) == "Canon RF 50mm F1.2 L USM"

    assert lens_model(106) == "Tamron SP AF 70-300mm f/4-5.6 Di VC USD G2"

    assert lens_model(109) == "Sigma 56mm F1.4 DC DN | C"

    assert lens_model(118) == "Canon RF-S 18-45mm F4.5-6.3 IS STM"

    assert lens_model(127) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(129) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(130) == "Canon RF 24-105mm F2.8 L IS USM"

    assert lens_model(131) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(133) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(136) == "Canon RF 50mm F1.2 L USM"

    assert lens_model(141) == "Tamron SP AF 70-200mm f/2.8 Di VC USD G2"

    assert lens_model(143) == "Sigma 70-200mm f/2.8 DG OS HSM | S"

    assert lens_model(156) == "Canon RF 24-105mm F4L IS USM"

    assert lens_model(159) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(161) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(163) == "Canon RF-S 18-55mm F4-5.6 IS STM"

    assert lens_model(170) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(179) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(305) == "Canon EF-S 60mm f/2.8 Macro USM"

    assert lens_model(307) == "Tamron SP AF 15-30mm f/2.8 Di VC USD G2"

    assert lens_model(400) == "Sigma 15-30mm F3.5-6.3 DC DN | C"

    assert lens_model(409) == "Canon RF-S 35mm F1.8 MACRO IS STM"

    assert lens_model(427) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(600) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(601) == "Canon RF-S 15-45mm F2.8 IS STM"

    assert lens_model(635) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(639) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(641) == "Canon RF-S 18-55mm F4-5.6 IS STM"

    assert lens_model(643) == "Tamron SP AF 24-70mm f/2.8 Di III RXD PZ"

    assert lens_model(649) == "Sigma 24-70mm F2.8 DG OS HSM | A"

    assert lens_model(1136) == "Sigma 50-100mm f/1.8 DC HSM Art"

    assert lens_model(368) == "Sigma 24-70mm f/2.8 DG OS HSM | Art 017"

    assert lens_model(4142) == "Canon EF-S 18-135mm f/3.5-5.6 IS STM"

    assert lens_model(4143) == "Canon EF-M 18-55mm f/3.5-5.6 IS STM"

    assert lens_model(4144) == "Canon EF 40mm f/2.8 STM"

    assert lens_model(4145) == "Canon EF-M 22mm f/2 STM"

    assert lens_model(4146) == "Canon EF-S 18-55mm f/3.5-5.6 IS STM"

    assert lens_model(4147) == "Canon EF-M 11-22mm f/4-5.6 IS STM"

    assert lens_model(4148) == "Canon EF-S 55-250mm f/4-5.6 IS STM"

    assert lens_model(4149) == "Canon EF-M 55-200mm f/4.5-6.3 IS STM"

    assert lens_model(4150) == "Canon EF-S 10-18mm f/4.5-5.6 IS STM"

    assert lens_model(4152) == "Canon EF 24-105mm f/3.5-5.6 IS STM"

    assert lens_model(4153) == "Canon EF-M 15-45mm f/3.5-6.3 IS STM"

    assert lens_model(4154) == "Canon EF-S 24mm f/2.8 STM"

    assert lens_model(4155) == "Canon EF-M 28mm f/3.5 Macro IS STM"

    assert lens_model(4156) == "Canon EF 50mm f/1.8 STM"

    assert lens_model(4157) == "Canon EF-M 18-150mm f/3.5-6.3 IS STM"

    assert lens_model(4158) == "Canon EF-S 18-55mm f/4-5.6 IS STM"

    assert lens_model(4159) == "Canon EF-M 32mm f/1.4 STM"

    assert lens_model(4160) == "Canon EF-S 35mm f/2.8 Macro IS STM"

    assert lens_model(61491) == "Canon CN-E 14mm T3.1 L F"

    assert lens_model(61492) == "Canon CN-E 24mm T1.5 L F"

    assert lens_model(61494) == "Canon CN-E 85mm T1.3 L F"

    assert lens_model(61495) == "Canon CN-E 135mm T2.2 L F"

    assert lens_model(61496) == "Canon CN-E 35mm T1.5 L F"

    assert lens_model(61182) == "Canon RF 70-200mm F4 L IS USM"

    assert lens_model(36910) == "Canon EF 70-300mm f/4-5.6 IS II USM"

    assert lens_model(36912) == "Canon EF-S 18-135mm f/3.5-5.6 IS USM"
