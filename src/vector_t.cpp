#include <iostream> // cin, cout
#include <cstdlib> // size_t
#include <exception> // out_of_range
#include <algorithm> // copy
#include <iterator>  // ostream_iterator
#include <cassert>  // assert

namespace ls
{
	template <typename T>
	class vector
	{
	private:
		//!< Default size for the vector
		static constexpr size_t DEFAULT_SIZE{ 1 };
		size_t m_len;
		size_t m_size;
		T *  m_data;

	public:
		vector( size_t sz_ = DEFAULT_SIZE ) 
		{
			m_len = 0;
			m_size = sz_;
			m_data = new T[sz_ + 1 ]; //+1 en necessário para posicao extra end()
		}	

		~vector()
		{
			delete [] m_data;
		}

		void clear( void )
		{
			m_len = 0;
		}

		size_t capacity ( void ) const
		{
			return m_size;
		}

		bool empty( void )
		{
			return m_len == 0;
		}

		void resize ( size_t sz_ )
        {
        	T * temp = m_data;

            m_size = sz_;
        	m_data = new T[sz_ + 1 ];

        	for (auto i = 0u; i < m_len; ++i)
        		m_data[i] = temp[i];

        	delete [] temp;
        }

		bool full( void )
		{
			return m_len == m_size;
		}

		T front ( void )
		{
			if( empty() )
				throw std::out_of_range("[front()]: Cannot recover an element from an empty vector!");
			return m_data[0];
		}

		T back ( void )
		{
			if( empty() )
				throw std::out_of_range("[back()]: Cannot recover an element from an empty vector!");
			return m_data[m_len-1];
		}
		
		void print( void ) const
        {
            std::cout << ">>> [ ";
            std::copy( &m_data[0], &m_data[m_len],
                       std::ostream_iterator< T >(std::cout, " ") );
            std::cout << "], len: " << m_len << ", capacity: " << m_size << ".\n";
        }
		
		void push_back( const T & value_ ) 
		{
			if( full() )
				resize( 2 * m_size );
				//throw std::length_error( "[push_back()]: Cannot add a new element, the vector is full!");
			m_data[m_len++] = value_;
		}	

		T pop_back( void )
		{
			if( empty() )
				throw std::out_of_range("[pop_back()]: Cannot recover an element from an empty vector!");
			return m_data[--m_len];
		}
		
		void push_front( const T & value_ ) 
		{
			if( full() )
				resize( 2 * m_size );

			//mover elementos do vetor para frente
			for (auto i = m_len; i > 0; --i)
        		m_data[i] = m_data[i-1];

			m_data[0] = value_;
			m_len++;
		}	

		void pop_front( void )
		{
			if( empty() )
				throw std::out_of_range("[pop_back()]: Cannot recover an element from an empty vector!");
			
			//mover elementos do vetor para trás, eliminando o primeiro
			for (auto i = 0u; i < m_len-1; ++i)
        		m_data[i] = m_data[i+1];

        	m_len--;
		}
	};
};

int main()
{
	ls::vector<int> v1(100);
	ls::vector<std::string> v2;

	// Testando excecao no front()
    {
        auto deu_certo{ false };
        try {
            std::cout << v2.front() << std::endl;
        }
        catch( const std::out_of_range & e )
        {
            deu_certo = true;
        }
        assert( deu_certo );
    }
    // Testando excecao no back()
    {
        auto deu_certo{ false };
        try {
            std::cout << v2.back() << std::endl;
        }
        catch( const std::out_of_range & e )
        {
            deu_certo = true;
        }
        assert( deu_certo );
    }

    // Testando metodo emtpy()
    {
        assert( v1.empty() == true );
        assert( v2.empty() == true );
    }

    // Testando push_back e pop_back
    {
    	std::cout << "\n\t>>>testando push_back e pop_back (vet com capacity definido)\n";
        for( auto i(0) ; i < 10 ; ++i )
            v1.push_back( i+1 );

        std::cout << "v1 antes pop_back: \n";
        v1.print();

        std::cout << "poping back v1: ";
        while( not v1.empty() )
            std::cout << v1.pop_back() << " ";
        std::cout << std::endl;

        std::cout << "v1 após pop_back: \n";
        v1.print();
    }

	// Testanto vetor com string
    {
    	std::cout << "\n\t>>>testando vetor com string (vet com capacity NAO definido)\n";
        ls::vector< std::string > ss;

        ss.print();
        ss.push_back( "one" );
        ss.print();
        ss.push_back( "two" );
        ss.print();
        ss.push_back( "three" );
        ss.print();
        ss.push_back( "four" );
        ss.print();
        ss.push_back( "five" );
        ss.print();
    }

    // Testando push_front e pop_front
    {
    	std::cout << "\n\t>>>testando push_front e pop_front (vet com capacity NAO definido)\n";

    	ls::vector<int> v3;
    	v3.push_front(8);
    	v3.push_front(9);
    	v3.push_front(0);
    	v3.push_back(1);
    	v3.push_front(5);

    	v3.print(); // esperado: 5 0 9 8 1

    	v3.pop_front();
    	v3.pop_front();

    	v3.print(); // esperado: 9 8 1

    }
}