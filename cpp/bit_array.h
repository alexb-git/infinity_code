/****************************************************************************
** Filename:    - bit_array.h
** Code Author: - Alex B
** Mail:        - aether.Alex@gmail.com
** Purpose:     - bits array data structure implementation
** Date:        - 31/1/2018
** Version:     - 1
*****************************************************************************/
 #ifndef __BITSARRAY_CPP__
 #define __BITSARRAY_CPP__

#include <iostream>  /* ostream, istream */
#include <vector>    /* vector */
#include <algorithm> /* for_each, transform */

namespace ilrd
{
using std::size_t;
static const size_t BITS_IN_WORD = 64;
static const size_t ASCII_INDEX  = 256;
static const unsigned char count_set_in_byte[ASCII_INDEX] = {
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8 };

inline size_t Modulu64(size_t val)
{
    return val & ((1 << 6) - 1); // val % 64
}

/*===========================  Class BitsArray  ===========================*/
template <size_t SIZE>
class BitsArray
{
private:
    class BitProxy;
    struct Counter;
    struct Shift;

public:
    explicit inline BitsArray();
    inline void SetBit(const size_t index, bool state);
    inline bool GetBit(const size_t index) const;
    inline void FlipBit(const size_t index);
    inline void FlipAll();
    inline size_t CountSetBit() const;
    inline bool operator==(const BitsArray& other) const;
    inline bool operator!=(const BitsArray& other) const;

    inline void operator|=(const BitsArray& other);
    inline void operator&=(const BitsArray& other);
    inline void operator^=(const BitsArray& other);

    // to support operation m_bits_array[index] = 1;
    inline BitProxy operator[](size_t index);

    // when BitsArray is const, we want to prevent m_bits_array[index]='a'
    inline const bool operator[](size_t index) const;

    inline void operator>>=(size_t n_shifts);
    inline void operator<<=(size_t n_shifts);


private:
    static const size_t  calc_size = ( (SIZE) / (BITS_IN_WORD + 1) + 1 );
    std::vector<size_t>  m_bits_array;
};


/*=============  Class BitProxy, nested in class BitsArray  ===============*/
template <size_t SIZE>
class BitsArray<SIZE>::BitProxy
{
public:
    explicit BitProxy(BitsArray<SIZE> &bits_array,size_t index);
    BitProxy operator=(bool bit);             // ((BitsArray[0] = '1') = '0')
    BitProxy operator=(const BitProxy& bp);   // BitsArray[0] = BitsArray[1]
    bool operator==(const BitProxy& other);
    operator bool() const;

private:
  size_t            m_bit_index;
  BitsArray<SIZE>  &m_bit_arr_ref;
};


/*==============================  operator<<  ==============================*/
template <size_t SIZE>
inline std::ostream& operator<<( std::ostream& os,
                                 const BitsArray<SIZE> &m_bits_array)
{
    for (int i = SIZE - 1 ; i >= 0 ; --i )
    {
        // std::cout << m_bits_array[i];
        std::cout << m_bits_array.GetBit(i);
    }

    return os;
}

/****************************************************************************
                ==========  Class BitsArray  ==========
*****************************************************************************/
/*
        ######             #
        #     # # #####   # #   #####  #####    ##   #   #
        #     # #   #    #   #  #    # #    #  #  #   # #
        ######  #   #   #     # #    # #    # #    #   #
        #     # #   #   ####### #####  #####  ######   #
        #     # #   #   #     # #   #  #   #  #    #   #
        ######  #   #   #     # #    # #    # #    #   #
*/
/*============================  BitsArray ctor  ============================*/
template <size_t SIZE>
BitsArray<SIZE>::BitsArray() : m_bits_array (calc_size, 0)
{}

/*===============================  SetBit  =================================*/
template <size_t SIZE>
inline void BitsArray<SIZE>::SetBit(const size_t index, bool state)
{
    if ( index < SIZE )
    {
        size_t cell = calc_size - 1 - index / BITS_IN_WORD;

        /* nullyfy the bit (mask e.x 1111110111111) */
        size_t mask = ~0lu - (1lu << Modulu64(index)); // index % 64
        m_bits_array[cell] &= mask;

        m_bits_array[cell] |= (size_t)state << Modulu64(index); // index % 64
    }
}

/*=================================  GetBit  ===============================*/
template <size_t SIZE>
inline bool BitsArray<SIZE>::GetBit(const size_t index) const
{
    size_t cell = calc_size - 1 - index / BITS_IN_WORD;

    return m_bits_array[cell] & (1lu << Modulu64(index)); //index % 64
}

/*================================  FlipBit  ================================*/
template <size_t SIZE>
inline void BitsArray<SIZE>::FlipBit(const size_t index)
{
    size_t cell = calc_size - 1 - index / BITS_IN_WORD;

    /* nullyfy the bit */
    m_bits_array[cell] ^= 1lu << Modulu64(index); // index % 64
}

/*==============================  FlipSizeT  ================================*/
inline size_t FlipSizeT(size_t &ref)
{
    return ~ref;
}

/*================================  FlipAll  ================================*/
template <size_t SIZE>
inline void BitsArray<SIZE>::FlipAll()
{
    /* Applies op to each of the elements in the range [first1,last1)
       and stores the value returned by each operation in the range
       that begins at result. */
    transform( m_bits_array.begin(), m_bits_array.end(),
               m_bits_array.begin(), FlipSizeT );

    m_bits_array[0] &= ~0lu >> (BITS_IN_WORD - Modulu64(SIZE)); // index % 64
}

/*==============  The Functor (used in CountSetBit method)  ================*/
template <size_t SIZE>
struct BitsArray<SIZE>::Counter
{
    inline Counter( ) : m_sum(0)
    {}

    // This operator overloading enables calling
    // operator function () on objects of Counter
    inline void operator () (size_t curr_sizet)
    {
        unsigned char *ch_ptr = reinterpret_cast<unsigned char*>(&curr_sizet);

        for (size_t i = 0 ; i < 8 ; ++i )
        {
            m_sum += count_set_in_byte[*ch_ptr];

            ++ch_ptr;
        }
    }

    size_t m_sum;
};


/*==============================  CountSetBit  ==============================*/
template <size_t SIZE>
inline size_t BitsArray<SIZE>::CountSetBit() const
{
    Counter counter;

    counter= std::for_each( m_bits_array.begin(),
                            m_bits_array.end()  ,
                            counter             );
    return counter.m_sum;
}

/*=================================  '=='  ==================================*/
template <size_t SIZE>
inline bool BitsArray<SIZE>::operator==(const BitsArray& other) const
{
    return m_bits_array == other.m_bits_array;
}

/*=================================  '!='  ==================================*/
template <size_t SIZE>
inline bool BitsArray<SIZE>::operator!=(const BitsArray& other) const
{
    return !(*this == other);
}

/*=================================  '|='  ==================================*/
template <size_t SIZE>
inline void BitsArray<SIZE>::operator|=(const BitsArray& other)
{
    std::vector<size_t>::iterator this_itr        = m_bits_array.begin();
    std::vector<size_t>::const_iterator other_itr = other.m_bits_array.begin();

    for (  ; this_itr != m_bits_array.end(); ++this_itr, ++other_itr )
    {
        *this_itr |= *other_itr;
    }
}

/*=================================  '&='  ==================================*/
template <size_t SIZE>
inline void BitsArray<SIZE>::operator&=(const BitsArray& other)
{
    for ( size_t i = 0 ; i < calc_size ; ++i )
    {
        this->m_bits_array[i] &= other.m_bits_array[i];
    }
}

/*=================================  '^='  ==================================*/
static inline size_t XOROp(size_t des, size_t src)
{
    return des ^ src;
}

template <size_t SIZE>
inline void BitsArray<SIZE>::operator^=(const BitsArray& other)
{
    transform( m_bits_array.begin()        ,  /* 1st start */
               m_bits_array.end()          ,  /* 1st end */
               other.m_bits_array.begin()  ,  /* 2nd start */
               m_bits_array.begin()        ,  /* result destination */
               XOROp                       ); /* function to apply */
}


/*==============  The Functor (used in CountSetBit method)  ================*/
template <size_t SIZE>
struct BitsArray<SIZE>::Shift
{
    inline Shift( ) :
                    m_shift(0),
                    m_curr_rmdr(0),
                    m_prev_rmdr(0)
    {}

    // This operator overloading enables calling
    // operator function () on objects of Shift
    inline void operator () (size_t curr_word)
    {
        m_curr_rmdr  = curr_word >> (64 - m_shift);
        curr_word  <<= m_shift;
        curr_word   |= m_prev_rmdr;
        m_prev_rmdr  = m_curr_rmdr;
    }

    size_t m_shift;
    size_t m_curr_rmdr;
    size_t m_prev_rmdr;
};

/*=================================  '<<='  ==================================*/
template <size_t SIZE>
inline void BitsArray<SIZE>::operator<<=(size_t n_shifts)
{
}

/*========================  const BitsArray::operator[]  ======================*/
template <size_t SIZE>
inline const bool BitsArray<SIZE>::operator[](size_t index) const
{
    // std::cout << "const BitsArray::operator[]" << std::endl;
    return GetBit(index);
}

/****************************************************************************
    ==========  Class BitProxy, nested in class BitsArray  ==========
*****************************************************************************/
/*
        ######          ######
        #     # # ##### #     # #####   ####  #    # #   #
        #     # #   #   #     # #    # #    #  #  #   # #
        ######  #   #   ######  #    # #    #   ##     #
        #     # #   #   #       #####  #    #   ##     #
        #     # #   #   #       #   #  #    #  #  #    #
        ######  #   #   #       #    #  ####  #    #   #
*/

/*======================  nested proxy class, ctor  =========================*/
template <size_t SIZE>
BitsArray<SIZE>::BitProxy::BitProxy(BitsArray<SIZE> &bits_array, size_t index):
        m_bit_index(index),
        m_bit_arr_ref(bits_array)
{
    // std::cout << "BitProxy ctor" << std::endl;
}

/*=========================  'BitsArray::operator[]'  =========================*/
template <size_t SIZE>
inline typename BitsArray<SIZE>::BitProxy BitsArray<SIZE>::operator[]
        (size_t index)
{
    // std::cout << "BitsArray::operator[]" << std::endl;
    BitProxy local(*this, index);
    return local;
}

/*=========================  nested proxy class, '=bit'  ====================*/
template <size_t SIZE>
typename BitsArray<SIZE>::BitProxy BitsArray<SIZE>::BitProxy::operator=
        (bool bit)
{
    // std::cout << "BitProxy::operator=(bool bit)" << std::endl;
    m_bit_arr_ref.SetBit(m_bit_index, bit);

    return *this;
}

/*=========================  nested proxy class, '=BitProxy'  ===============*/
template <size_t SIZE>
typename BitsArray<SIZE>::BitProxy BitsArray<SIZE>::BitProxy::operator=
        (const BitProxy& bp)
{
    // std::cout << "BitProxy::operator=" << std::endl;
    m_bit_arr_ref.SetBit(m_bit_index, bp);

    return *this;
}

/*=========================  nested proxy class, '=='  ======================*/
template <size_t SIZE>
bool BitsArray<SIZE>::BitProxy::operator==(const BitProxy& other)
{
    // std::cout << "BitProxy::operator==" << std::endl;
    return (m_bit_arr_ref.GetBit(m_bit_index) == other);
}

/*=========================  nested proxy class, 'defined conversion'  ======*/
template <size_t SIZE>
BitsArray<SIZE>::BitProxy::operator bool() const
{
    // std::cout << "BitProxy::operator bool()" << std::endl;
    return m_bit_arr_ref.GetBit(m_bit_index);
}


} // namespace ilrd

#endif /* __BITSARRAY_CPP__ */
