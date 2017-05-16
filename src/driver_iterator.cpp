#include <iostream>  // cout, endl
#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
#include <cstddef>   // std::ptrdiff_t

/*!
 * A template class representing a biderectional iterator defines
 * over a dynamic array.
 * 
 * \note
 * This iterator only works for traversing elements inside the same array.
 *
 * This class is incomplete and it is provided "as is".
 * 
 * \date May, 2nd 2017.
 * \author Selan R. dos Santos
 */

template <typename T>
class MyBidirectionalIterator
{
    // =============================================================
    // Some aliases to help writing a clearer code.
    // =============================================================
    public:
        using self_type = MyBidirectionalIterator;  
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        /*!
         * \brief std::ptrdiff_t is the signed integer type of the result of subtracting two pointers.
         *
         * std::ptrdiff_t is used for pointer arithmetic and array indexing,
         * if negative values are possible. Programs that use other types, such
         * as int, **may fail** on, e.g. 64-bit systems when the index exceeds
         * INT_MAX or if it relies on 32-bit modular arithmetic.
         *
         * When working with the C++ container library, the proper type for the
         * difference between iterators is the member typedef difference_type,
         * which is often synonymous with std::ptrdiff_t.
         * Only pointers to elements of the same array (including the pointer
         * one past the end of the array) may be subtracted from each other.
         */
        using difference_type = std::ptrdiff_t;
        /*!
         * Defines the category of an iterator.
         * Iterator category tags carry information that can be used
         * to select the most efficient algorithms for the specific
         * requirement set that is implied by the category.
         */
        using iterator_category = std::bidirectional_iterator_tag;

        // =============================================================
        // The raw pointer we want to encapsulate.
        // =============================================================
    private:
        T * m_ptr;

        // =============================================================
        // Public interface that mimics the behaviour of a regular pointer.
        // =============================================================
    public:
        // Constructor
        MyBidirectionalIterator( T * ptr_ = nullptr )
            : m_ptr ( ptr_ )
        { /* empty */ }

        // Special methods. Default versions.
        ~MyBidirectionalIterator() = default;
        MyBidirectionalIterator( const self_type & ) = default;
        self_type & operator=( const self_type & ) = default;

        /*! The  *it operator.
         *  Supports: *it = XXXX or XXXX = *it.
         *  \return A reference to the object this iterator points to.
         */
        reference operator*()
        {
            assert( m_ptr != nullptr );
            return *m_ptr;
        }

        /*! The ++it operator.
         *  \return The calling object.
         */
        self_type operator++()
        {
            m_ptr++;
            return *this;
        }

        /*! The it++ operator.
         *  \return The calling object.
         */
        self_type operator++(int)
        {
            self_type temp = *this;
            m_ptr++;
            return temp;
        }

        /*! The --it operator.
         *  \return The calling object.
         */
        self_type operator--()
        {
            m_ptr--;
            return *this;
        }

        /*! The it-- operator.
         *  \return The calling object.
         */
        self_type operator--(int)
        {
            self_type temp = *this;
            m_ptr--;
            return temp;
        }

        /// The it == it2 operator.
        bool operator==( const self_type & rhs_ ) const
        {
            return m_ptr == rhs_.m_ptr;
        }

        /// The it != it2 operator.
        bool operator!=( const self_type & rhs_ ) const
        {
            return m_ptr != rhs_.m_ptr;
        }

        // ==================================================
        /* Other methods that you might wanto to implement. */
        // ==================================================

        /// it += 3; // Go back  3 positions within the container. 
        self_type operator+=( difference_type step_ ) ;

        /// it -= 3; // Go back  3 positions within the container. 
        self_type operator-=(  difference_type step_ ) ;

        /// it->method()
        pointer operator->( void ) const ;

        /// it1 - it2
        difference_type operator-( const self_type & rhs_ ) const ;

};

/// A simple version of a dynamic array that stores integers.
class VectorInt
{
    // The iterator classes.
    public:
        using iterator = MyBidirectionalIterator<int>;
        using const_iterator = MyBidirectionalIterator<const int>;

    // Internal data information.
    private:
        size_t m_len;
        size_t m_capacity;
        int * m_data;

        // Public interface.
    public:
        VectorInt( size_t sz_=0 )
            : m_len(0)
            , m_capacity(sz_)
            , m_data( new int[sz_] )
        { /* empty */ }

        ~VectorInt( void )
        { delete [] m_data; }


        // Iterator-linking methods.
        iterator begin( void ) const
        { return iterator( &m_data[0] ) ; }

        iterator  end( void ) const
        { return iterator( &m_data[m_len] ) ; }

        const_iterator cbegin( void ) const
        { return const_iterator( &m_data[0] ) ; }

        const_iterator  cend( void ) const
        { return const_iterator( &m_data[m_len] ) ; }


        bool full( void ) const
        { return m_len==m_capacity; }

        void reserve( size_t new_cap_ )
        {
            // Is the requested capacity smaller than the current one?
            if ( new_cap_ <= m_capacity )  return; // Nothing to do here.

            // (1) Creates the new storage area.
            int * temp = new int[ new_cap_ ];

            // (2) Backups the data into the new storage area.
            for( auto i(0u) ; i < m_capacity ; ++i )
                temp[i] = m_data[i];

            // (3) Delete the old storage area.
            delete [] m_data;

            // (4) Reassigns the storage area.
            m_data = temp;

            // (5) Updates the vector's storage capacity.
            m_capacity = new_cap_;
        }

        void push_back( int e_ )
        {
            if ( full() )
                reserve( 2 * m_capacity );

            m_data[m_len++] = e_;
        }
};

// The vector/iterator driver.
int main( void )
{
    VectorInt v(10); // Criar um vector com 10 elementos
    VectorInt::iterator it = v.begin();

    for( auto i(0) ; i < 10 ; ++i )
        v.push_back( i+1 );

    for ( auto cit (v.cbegin()); cit != v.cend() ; ++cit )
        std::cout << *cit << " ";
    std::cout << std::endl;

    std::cout << ">>> begin() = " << *it << "\n";

    std::cout << ">>> Array: [";
    std::copy( v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ") );
    std::cout << "]\n";

    it++;
    std::cout << ">>> begin()+1 = " << *it << "\n";
    /*
     // THIS DOES NOT WORK!!
     int * ptr = v.m_data;
     *ptr = 10;
     ptr++;
    */
    return 0;
}
