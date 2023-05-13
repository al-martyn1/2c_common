@set FLAGS_CMN=--enum-flags=type-decl,serialize,deserialize,lowercase,enum-class,extra
@set FLAGS_KEYSIZE=--enum-flags=0 %FLAGS_CMN% --enum-flags=integers
@set FLAGS_KEYSEED=--enum-flags=0 %FLAGS_CMN%
umba-enum-gen --underlaying-type=std::uint8_t ^
--override-template-parameter=EnumNameFormat:E$(ENAMNAME) ^
--target-language=cpp --overwrite=Y ^
--base-indent=0 --indent-increment=4 ^
--namespace=_2c --namespace-style=CppStyle --enum-name-style=PascalStyle ^
--enum-values-style=PascalStyle --enum-serialize-style=All ^
%FLAGS_KEYSIZE% -E=KeySize -F=Invalid,Unknown=-1;NoKey,NoEncryption,No=0;Byte=1;Short=2;Random,Rnd,Rand=3;Int,Unsigned=4 ^
%FLAGS_KEYSEED% -E=KeySeed -F=Invalid,Unknown=-1;Random,Rnd,Rand=0 ^
..\_2c_xor_encrypt_enum.h
