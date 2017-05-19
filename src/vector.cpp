/**  
 * @file vector.cpp  
 * @version 1.0  
 * @date 16/05/2017  
 * @author Edivânia Pontes de Oliveira  
 * @title Vector program  
 * @brief Contains the implementation of Vector's functions.  
 */

#include "vector.h"

using namespace ls;
// [I] SPECIAL MEMBERS
template <typename T>
vector<T>::vector( size_t sz_ ) 
{
	m_len  = 0;
	m_size = sz_;
	m_data = new T[sz_ + 1 ]; //+1 en necessário para posicao extra end()
}

template <typename T>
vector<T>::vector( ) 
{
	m_len  = 0;
	m_size = DEFAULT_SIZE;
	m_data = new T[ DEFAULT_SIZE + 1 ]; //+1 en necessário para posicao extra end()
}	

template <typename T>
vector<T>::~vector()
{
	delete [] m_data;
}

template <typename T>
vector<T>::vector( const vector<T> & vector_ )
{
	m_len  = vector_.m_len;
	m_size = vector_.m_size;
	m_data = new T[ vector_.m_size + 1 ];

	for (auto i = 0u; i < m_len; ++i)
		m_data[i] = vector_.m_data[i];
}

template <typename T>
vector<T>::vector( std::initializer_list<T> ilist )
{
	m_len  = ilist.size();
	m_size = ilist.size();
	m_data = new T[ ilist.size() + 1 ];

	for (auto i = 0u; i < m_len; ++i)
		m_data[i] = *(ilist.begin()+i);
}

// [II] ITERATORS

// [III] CAPACITY
template <typename T>
size_t vector<T>::size( void ) const
{
	return m_len;
}

template <typename T>
size_t vector<T>::capacity( void ) const
{
	return m_size;
}

template <typename T>
bool vector<T>::empty( void ) const
{
	return m_len == 0;
}

template <typename T>
bool vector<T>::full( void ) const
{
	return m_len == m_size;
}

// [IV] MODIFIERS
template <typename T>
void vector<T>::clear( void )
{
	delete [] m_data;
	m_len = 0;
	m_size = DEFAULT_SIZE;
	m_data = new T[ DEFAULT_SIZE + 1 ];
}

template <typename T>
void vector<T>::push_back( const T & value_ ) 
{
	if( full() )
		reserve( 1 + 2 * m_size );
		//throw std::length_error( "[push_back()]: Cannot add a new element, the vector is full!");
	m_data[m_len++] = value_;
}	

template <typename T>
void vector<T>::push_front( const T & value_ ) 
{
	if( full() )
		reserve( 1 + 2 * m_size );

	//mover elementos do vetor para frente
	for (auto i = m_len; i > 0; --i)
		m_data[i] = m_data[i-1];

	m_data[0] = value_;
	m_len++;
}	

template <typename T>
void vector<T>::pop_back( void )
{
	if( empty() )
		throw std::out_of_range("[pop_back()]: Cannot recover an element from an empty vector!");
	--m_len;
}

template <typename T>
void vector<T>::pop_front( void )
{
	if( empty() )
		throw std::out_of_range("[pop_back()]: Cannot recover an element from an empty vector!");
	
	//mover elementos do vetor para trás, eliminando o primeiro
	for (auto i = 0u; i < m_len-1; ++i)
		m_data[i] = m_data[i+1];

	m_len--;
}

template <typename T>
void vector<T>::reserve( size_t new_cap )
{
	if( new_cap <= m_size ) return; //não fazer nada se novo tam for menor ou igual ao atual

	T * temp = m_data;

    m_size = new_cap;
	m_data = new T[ new_cap + 1 ];

	for (auto i = 0u; i < m_len; ++i)
		m_data[i] = temp[i];

	delete [] temp;
}

/*! @brief Requests the removal of unused capacity. It is a non-binding request to reduce capacity() to size().*/
template <typename T>
void vector<T>::shrink_to_fit( void )
{
	T * temp = m_data;

    m_size = m_len; //capacity now is equal to current size
	m_data = new T[ m_len + 1 ];

	for (auto i = 0u; i < m_len; ++i)
		m_data[i] = temp[i];

	delete [] temp;
}

template <typename T>
void vector<T>::assign( const T & value_ )
{
	for (auto i = 0u; i < m_len; ++i)
		m_data[i] = value_;
}

// [V] ELEMENT ACCESS
template <typename T>
const T & vector<T>::back ( void ) const
{
	if( empty() )
		throw std::out_of_range("[back()]: Cannot recover an element from an empty vector!");
	return m_data[m_len-1];
}

template <typename T>
const T & vector<T>::front ( void ) const
{
	if( empty() )
		throw std::out_of_range("[front()]: Cannot recover an element from an empty vector!");
	return m_data[0];
}

template <typename T>
const T & vector<T>::operator[]( size_t pos ) const
{
	return m_data[pos];
}

template <typename T>
T & vector<T>::operator[]( size_t pos )
{
	return m_data[pos];
}

template <typename T>
const T & vector<T>::at( size_t pos ) const
{
	if( pos < 0 or pos > m_len-1 )
		throw std::out_of_range("[at()]: Position required is not within the range of the vector!");
	return m_data[pos];
}

template <typename T>
T & vector<T>::at( size_t pos )
{
	if( pos < 0 or pos > m_len-1 )
		throw std::out_of_range("[at()]: Position required is not within the range of the vector!");
	return m_data[pos];
}

template <typename T>
T * vector<T>::data( void )
{
	return m_data;
}

template <typename T>
const T & vector<T>::data( void ) const
{
	return m_data;
}

template <typename T>
void vector<T>::print( void ) const
{
    std::cout << ">>> [ ";
    std::copy( &m_data[0], &m_data[m_len],
               std::ostream_iterator< T >(std::cout, " ") );
    std::cout << "], len: " << m_len << ", capacity: " << m_size << ".\n";
}

// [VI] OPERATORS
template <typename T>
bool vector<T>::operator==( const vector<T> & vector_ ) const
{
	if( m_len != vector_.m_len )
		return false; //if current size are different, the vectors are different

	for (auto i = 0u; i < m_len; ++i)
		if( m_data[i] != vector_.m_data[i] ) //if one of elements in the same position are different, the vectors are different
			return false;

	return true;
}

template <typename T>
bool vector<T>::operator!=( const vector<T> & vector_ ) const
{
	return not operator==( vector_ );
}

