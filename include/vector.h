/**  
 * @file vector.h  
 * @version 1.0  
 * @date 16/05/2017  
 * @author Edivânia Pontes de Oliveira  
 * @title Class ls::vector  
 * @brief Class for ls::vector configuration  
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream> // cin, cout
#include <cstdlib> // size_t
#include <exception> // out_of_range
#include <algorithm> // copy
#include <iterator>  // ostream_iterator
#include <cassert>  // assert
#include <initializer_list> //initializer_list

namespace ls
{
	template <typename T>
	class vector
	{
	private:
		const static size_t DEFAULT_SIZE = 0; //!< Default size for the vector
		size_t m_len; //<! Current list size (or index past-last valid elemen>
		size_t m_size; //<! List’s storage capacity.
		T *  m_data; //<! Data storage area for the dynamic array.

	public:
		// [I] SPECIAL MEMBERS
		/*! @brief Constructs the list with logical size setted. 
			@param sz_ Size that the vector should have. */
		vector( size_t sz_ );

		/*! @brief Default constructor that creates an empty list. */
		vector( );

		/*! @brief Destructs the list. */
		~vector();

		/*! @brief Copy constructor. Constructs the list with the deep copy of the contents of other vector. 
			@param vector_ vector that will be copyed. */
		vector( const vector<T> & vector_ );

		/*! @brief Constructs the list with the contents of the initializer list. 
			@param ilist initializer list. */
		vector( std::initializer_list<T> ilist );

		/* ---------- missing ----------
		vector( vector<T> && vector_ );
		template < typename InputItr >
		vector( InputItr, InputItr );
		vector & operator=( const vector<T> & vector_ );
		vector & operator=( vector<T> && vector_ );
		vector & operator=( std::initializer_list<T> ilist );*/

		// [II] ITERATORS
		/* ---------- missing ----------
		iterator begin( void );
		iterator end( void );
		const_iterator cbegin( void ) const;
		const_iterator cend( void ) const;*/

		// [III] CAPACITY
		/*! @brief Informs the current list size.
			@return The number of elements in the container. */
		size_t size( void ) const;
		
		/*! @brief Informs the list’s storage capacity.
			@return The internal storage capacity of the array. */
		size_t capacity( void ) const;

		/*! @brief Informs if the vector is empty or not.
			@return True if the container contains no elements, and false otherwise. */
		bool empty( void ) const;
		
		/*! @brief Informs if the vector is full or not.
			@return True if the container has reached its capacity, and false otherwise. */
		bool full( void ) const;


		// [IV] MODIFIERS
		/* ---------- missing ----------
		iterator insert( iterator , const_reference );
		template < typename InputItr >
		iterator insert( iterator , InputItr , InputItr );
		iterator insert( iterator, std::initializer_list< value_type > );
		void assign( std::initializer_list<T> );
		template < typename InputItr >
		void assign( InputItr, InputItr );
		iterator erase( iterator, iterator );
		iterator erase( iterator );*/

		/*! @brief Remove (either logically or physically) all elements from the container. */
		void clear( void );
		
		/*! @brief Adds value to the front of the list. 
			@param value_ The value to add. */
		void push_back( const T & value_ );	

		/*! @brief Adds value to the end of the list. 
			@param value_ The value to add. */
		void push_front( const T & value_ );	

		/*! @brief Removes the object at the end of the list. */
		void pop_back( void );

		/*! @brief Removes the object at the front of the list. */
		void pop_front( void );

		/*! @brief Increase the storage capacity of the array to a value that’s is greater or equal to new_cap. */
		void reserve( size_t new_cap );

		/*! @brief Requests the removal of unused capacity. It is a non-binding request to reduce capacity() to size().*/
		void shrink_to_fit( void );

		/*! @brief replaces the content of the list with copies of value_.
			@param value_ The value to be replaced. */
		void assign( const T & value_ );

		// [V] ELEMENT ACCESS

		/*! @return The object at the end of the list.*/
		const T & back ( void ) const;

		/*! @return The object at the beginning of the list.*/
		const T & front ( void ) const;

		/*! @return The const object at the index pos in the array, with no bounds-checking. */
		const T & operator[]( size_t pos ) const;

		/*! @return The object at the index pos in the array, with no bounds-checking. */
		T & operator[]( size_t pos );
		
		/*! @return The const object at the index pos in the array, with bounds-checking. */
		const T & at( size_t pos ) const;

		/*! @return The object at the index pos in the array, with bounds-checking. */
		T & at( size_t pos );

		/*! @return A pointer to the first element in the array used internally by the vector. */
		T * data( void );

		/*! @return A const pointer to the first element in the array used internally by the vector. */
		const T & data( void ) const;

		/*! @brief Prints the vector, your length and capacity. */
		void print( void ) const;

		// [VI] OPERATORS
		bool operator==( const vector<T> & vector_ ) const;
		bool operator!=( const vector<T> & vector_ ) const;

		// [VII] FRIEND FUNCTIONS
		/* ---------- missing ----------
		friend std::ostream & operator<<( std::ostream & os_, const vector<T> & v_ );
		friend void swap( vector<T> & first_, vector<T> & second_ );*/

	};
}

#endif
