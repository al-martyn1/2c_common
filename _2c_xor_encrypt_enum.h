#pragma once

#include "marty_cpp/marty_enum.h"

#include <exception>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>



namespace _2c{

enum class EKeySize : std::uint8_t
{
    Invalid        = (std::uint8_t)(-1),
    Unknown        = (std::uint8_t)(-1),
    NoKey          = 0,
    NoEncryption   = 0,
    No             = 0,
    Byte           = 1,
    Short          = 2,
    Random         = 3,
    Rnd            = 3,
    Rand           = 3,
    Int            = 4,
    Unsigned       = 4

}; // enum class EKeySize : std::uint8_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EKeySize, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySize::Invalid  , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySize::NoKey    , "NoKey"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySize::Byte     , "Byte"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySize::Short    , "Short"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySize::Random   , "Random"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySize::Int      , "Int"     );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EKeySize, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EKeySize, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Invalid  , "invalid"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Invalid  , "-1"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Invalid  , "unknown"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "no-encryption" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "no-key"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "no_key"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "nokey"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "noencryption"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "0"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "no"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::NoKey    , "no_encryption" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Byte     , "byte"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Byte     , "1"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Short    , "short"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Short    , "2"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Random   , "random"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Random   , "3"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Random   , "rnd"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Random   , "rand"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Int      , "unsigned"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Int      , "int"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySize::Int      , "4"             );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EKeySize, std::map, 1 )

MARTY_CPP_ENUM_CLASS_SERIALIZE_SET(EKeySize, std::set)

MARTY_CPP_ENUM_CLASS_DESERIALIZE_SET(EKeySize, std::set)


enum class EKeySeed : std::uint8_t
{
    Invalid   = (std::uint8_t)(-1),
    Unknown   = (std::uint8_t)(-1),
    Random    = 0,
    Rnd       = 0,
    Rand      = 0

}; // enum class EKeySeed : std::uint8_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EKeySeed, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySeed::Invalid  , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EKeySeed::Random   , "Random"  );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EKeySeed, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EKeySeed, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySeed::Invalid  , "invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySeed::Invalid  , "unknown" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySeed::Random   , "random"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySeed::Random   , "rnd"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EKeySeed::Random   , "rand"    );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EKeySeed, std::map, 1 )

MARTY_CPP_ENUM_CLASS_SERIALIZE_SET(EKeySeed, std::set)

MARTY_CPP_ENUM_CLASS_DESERIALIZE_SET(EKeySeed, std::set)

} // namespace _2c

