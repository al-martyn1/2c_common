#pragma once

#include "_2c_xor_encrypt_enum.h"
#include <cstdint>

#include <random>
#include <string>

#if defined(WIN32) || defined(_WIN32)

    #include <winsock2.h>
    #include <windows.h>

#else

    #include <ctime>
    // #include <chrono>

#endif

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
#if !defined(DISABLE_CUSTOM_UMBA_RCFS_RC_FILENAME_DEFS)

    #if !defined(CUSTOM_UMBA_RCFS_RC_FILENAME)
        #define CUSTOM_UMBA_RCFS_RC_FILENAME(filename, filenameSize) \
                                    std::string( (const char*)(filename), (filenameSize) )
    #endif

    #if !defined(CUSTOM_UMBA_RCFS_RC_FILENAME_XORED)
        #define CUSTOM_UMBA_RCFS_RC_FILENAME_XORED(filename, filenameSize, filenameXorSize, filenameXorSeed, filenameXorInc) \
                                                                                                                             \
                _2c::xorDecryptCopy( std::string( (const char*)(filename), (filenameSize) ) \
                                   , (_2c::EKeySize)(filenameXorSize)                       \
                                   , (filenameXorSeed)                                      \
                                   , (filenameXorInc)                                       \
                                   )
    #endif
#endif

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace _2c {

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
union UXorEncryptionKey
{
    unsigned char      k1;
    unsigned short     k2;
    unsigned int       k4;

}; // UXorEncryptionKey

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
UXorEncryptionKey xorEncryptionKeyAdd( EKeySize ks, const UXorEncryptionKey &k, const UXorEncryptionKey &a)
{
    UXorEncryptionKey res = k;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // warning C4061: enumerator in switch of enum is not explicitly handled by a case label
#endif

    switch(ks)
    {
        case EKeySize::Unsigned: res.k4 += a.k4; break;
        case EKeySize::Short   : res.k2 += a.k2; break;
        default                : res.k1 += a.k1;
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
    return res;
}

//----------------------------------------------------------------------------
inline
std::size_t xorEncryptionKeyToBytes( EKeySize ks
                                   , const UXorEncryptionKey &k
                                   , char *pData // must be enough to hold at least 4 bytes
                                   )
{
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // warning C4061: enumerator in switch of enum is not explicitly handled by a case label
#endif
    switch(ks)
    {
        case EKeySize::Unsigned:
             {
                 pData[0] = (char)(unsigned char)( k.k4      & 0xFF);
                 pData[1] = (char)(unsigned char)((k.k4>> 8) & 0xFF);
                 pData[2] = (char)(unsigned char)((k.k4>>16) & 0xFF);
                 pData[3] = (char)(unsigned char)((k.k4>>24) & 0xFF);
                 return 4;
             }

        case EKeySize::Short   :
             {
                 pData[0] = (char)(unsigned char)( k.k2      & 0xFF);
                 pData[1] = (char)(unsigned char)((k.k2>> 8) & 0xFF);
                 return 2;
             }

        default                :
             {
                 *pData = (char)k.k1;
                 return 1;
             }
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}

//----------------------------------------------------------------------------
inline
std::size_t xorEncryptionKeySize( EKeySize ks )
{
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // warning C4061: enumerator in switch of enum is not explicitly handled by a case label
#endif
    switch(ks)
    {
        case EKeySize::Unsigned:
                 return 4;

        case EKeySize::Short   :
                 return 2;

        case EKeySize::Byte    :
                 return 1;

        default                :
                 return 0;
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
}

//----------------------------------------------------------------------------
inline
void xorEncryptionKeyAssign( EKeySize ks
                           , UXorEncryptionKey &k
                           , unsigned v
                           )
{
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // warning C4061: enumerator in switch of enum is not explicitly handled by a case label
#endif
    switch(ks)
    {
        case EKeySize::Unsigned:
             {
                 k.k4 = (unsigned int)(v&0xFFFFFFFF);
                 break;
             }

        case EKeySize::Short   :
             {
                 k.k2 = (unsigned short)(v&0xFFFF);
                 break;
             }

        default                :
             {
                 k.k1 = (unsigned char)(v&0xFF);
             }
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}

//----------------------------------------------------------------------------
inline
unsigned xorEncryptionKeyToUnsigned( EKeySize ks, UXorEncryptionKey k )
{
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // warning C4061: enumerator in switch of enum is not explicitly handled by a case label
#endif
    switch(ks)
    {
        case EKeySize::Unsigned:
                 return (unsigned)k.k4;

        case EKeySize::Short   :
                 return (unsigned)k.k2;

        default                :
                 return (unsigned)k.k1;
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
}


//----------------------------------------------------------------------------
template<typename IteratorType>
void xorEncrypt(IteratorType iterBegin, IteratorType iterEnd, EKeySize ks, unsigned seed, unsigned incVal)
{
    std::size_t keySize = xorEncryptionKeySize(ks);

    if (!keySize)
        return;


    UXorEncryptionKey key;
    xorEncryptionKeyAssign(ks, key   , seed);

    UXorEncryptionKey keyInc;
    xorEncryptionKeyAssign(ks, keyInc, incVal);


    char keyBytes[4] = {0};
    

    for(IteratorType it=iterBegin; it!=iterEnd; )
    {
        xorEncryptionKeyToBytes( ks, key, &keyBytes[0] );
        for(std::size_t i=0; i!=keySize && it!=iterEnd; ++i, ++it)
        {
            *it = (typename IteratorType::value_type)(*it ^ keyBytes[i]);
        }

        key = xorEncryptionKeyAdd( ks, key, keyInc);
    }

}

//----------------------------------------------------------------------------
inline
std::string xorEncryptCopy(const std::string &data, EKeySize ks, unsigned seed, unsigned incVal)
{
    std::string dataCopy = data; 
    xorEncrypt(dataCopy.begin(), dataCopy.end(), ks, seed, incVal);
    return dataCopy;
}

//----------------------------------------------------------------------------
template <typename CharType> inline
std::vector<CharType> xorEncryptCopy(const std::vector<CharType> &data, EKeySize ks, unsigned seed, unsigned incVal)
{
    std::vector<CharType> dataCopy = data; 
    xorEncrypt(dataCopy.begin(), dataCopy.end(), ks, seed, incVal);
    return dataCopy;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename IteratorType>
void xorDecrypt(IteratorType iterBegin, IteratorType iterEnd, EKeySize ks, unsigned seed, unsigned incVal)
{
    xorEncrypt(iterBegin, iterEnd, ks, seed, incVal);
}

//----------------------------------------------------------------------------
inline
std::string xorDecryptCopy(const std::string &data, EKeySize ks, unsigned seed, unsigned incVal)
{
    std::string dataCopy = data; 
    xorDecrypt(dataCopy.begin(), dataCopy.end(), ks, seed, incVal);
    return dataCopy;
}

//----------------------------------------------------------------------------
template <typename CharType> inline
std::vector<CharType> xorDecryptCopy(const std::vector<CharType> &data, EKeySize ks, unsigned seed, unsigned incVal)
{
    std::vector<CharType> dataCopy = data; 
    xorDecrypt(dataCopy.begin(), dataCopy.end(), ks, seed, incVal);
    return dataCopy;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
std::mt19937 xorEncryptionGetRandomGenerator()
{
    #if defined(WIN32) || defined(_WIN32)

        return std::mt19937((unsigned)GetTickCount());
    
    #else

       // std::mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
       return std::mt19937((unsigned)std::time());
    
    #endif
}

inline
unsigned xorEncryptionSeedFromString(EKeySize ksz, const std::string &str, std::mt19937 &rng, bool *pValid = 0)
{
    if (str.empty())
    {
        if (pValid)
           *pValid = true;
        return 0;
    }

    EKeySeed ekSeed = enum_deserialize(str, EKeySeed::Unknown);

    unsigned key = 0;

    if (ekSeed==EKeySeed::Random)
    {
        key = (unsigned)rng();
    }
    else
    {
        // key
        std::size_t pos = 0;
        long long intVal = std::stoll(str, &pos, 0 /* base */ );
        if (str.size()!=pos)
        {
            // Conversion error
            if (pValid)
               *pValid = false;
            return 0;
        }
            
        key = (unsigned)intVal;
    }

    if (pValid)
       *pValid = true;

    UXorEncryptionKey xek;
    xorEncryptionKeyAssign(ksz, xek, key);
    return xorEncryptionKeyToUnsigned(ksz, xek);

}

//----------------------------------------------------------------------------
inline
EKeySize xorEncryptionKeySizeFromString(const std::string &str, std::mt19937 &rng /* , bool *pValid = 0 */ )
{
    if (str.empty())
    {
        // if (pValid)
        //    *pValid = false;
        return EKeySize::Invalid;
    }

    EKeySize ekSize = enum_deserialize(str, EKeySize::Invalid);
    if (ekSize==EKeySize::Invalid)
        return ekSize;

    if (ekSize!=EKeySize::Random)
    {
        std::size_t sz = xorEncryptionKeySize( ekSize );
        if (sz==0 || sz==1 || sz==2 || sz==4)
            return ekSize;
    }


    unsigned uesz = (unsigned)rng();
    uesz = uesz%3;

    switch(uesz)
    {
        case 0 : return EKeySize::Byte;
        case 1 : return EKeySize::Short;
        case 2 : return EKeySize::Int;
        default: return EKeySize::Invalid;
    }

}


//----------------------------------------------------------------------------




} // namespace _2c

