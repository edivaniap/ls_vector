/**  
 * @file main.cpp  
 * @version 1.0  
 * @date 16/05/2017  
 * @author Edivânia Pontes de Oliveira  
 * @title Main program  
 * @brief The Main program contains the tests of Vector's functions.  
 */

#include "vector.cpp"

int main()
{
	ls::vector<int> v1(100);
	ls::vector<std::string> v2;

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

        std::cout << "poping back v1... ";
        while( not v1.empty() )
            v1.pop_back();
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

    // Testando assign(T) and clear()
    {
        std::cout << "\n\t>>>testando assign(T) and clear()\n";

        ls::vector<int> v;
        v.push_front(8);
        v.push_front(9);
        v.push_front(0);
        v.push_back(1);
        v.push_front(5);

        v.print(); // esperado: 5 0 9 8 1

        v.assign(4);

        v.print(); // esperado: 4 4 4 4 4
        
        v.clear();

        v.print(); // esperado: []

    }

    // Testando at() and operator[]() and shrink_to_fit()
    {
        std::cout << "\n\t>>>testando at() and operator[]()\n";

        ls::vector<std::string> v;
        v.push_back("me");
        v.push_back("you");
        v.push_back("he");
        v.push_back("she");

        v.print();
        v[1] = "change1";
        v.at(2) = "change2";
        std::cout << "Elemento na posição 0 = " << v[0] << std::endl; 
        std::cout << "Elemento na posição 1 = " << v.at(1) << std::endl; 
        std::cout << "Elemento na posição 2 = " << v[2] << std::endl; 
        std::cout << "Elemento na posição 3 = " << v.at(3) << std::endl; 
        //OK std::cout << "Elemento na posição 4 = " << v.at(4) << std::endl; 

        std::cout << "\n\t>>>testando shrink_to_fit()\n";
        v.shrink_to_fit();
        std::cout << "vetor removeu as posições não usadas... agora capacity = len\n";
        v.print();
    }

    // Testando operator== e operator[]
    {
        std::cout << "\n\t>>>testando operator== and operator[]()\n";
        std::cout << "\n\t>>>inicializando v2 com initializer_list\n";

        ls::vector<float> v1;
        ls::vector<float> v2 = { 0.1, 2.3, 0.8 };

        v1.push_back(0.1);
        v1.push_back(2.3);
        v1.push_back(0.8);

        std::cout << "vetor 1: ";
        v1.print();
        std::cout << "vetor 2: ";
        v2.print();

        assert( v1 == v2 );
        if( v1 == v2 )
            std::cout << "vetor 1 e 2 são iguais.\n\n";
        else
            std::cout << "vetor 1 e 2 são diferentes.\n\n";

        v2[1] = 4.1;
        std::cout << "vetor 1: ";
        v1.print();
        std::cout << "vetor 2: ";
        v2.print();

        assert( v1 != v2 );
        if( v1 == v2 )
            std::cout << "vetor 1 e 2 são iguais.\n\n";
        else
            std::cout << "vetor 1 e 2 são diferentes.\n\n";

        v1[1] = 4.1;
        v1.push_back(2.0);

        std::cout << "vetor 1: ";
        v1.print();
        std::cout << "vetor 2: ";
        v2.print();

        assert( v1 != v2 );
        if( v1 == v2 )
            std::cout << "vetor 1 e 2 são iguais.\n\n";
        else
            std::cout << "vetor 1 e 2 são diferentes.\n\n";
    }

    //Testando constructors
    {
        ls::vector<char> A = { 'a', 'b', 'c' };
        ls::vector<char> B(A);
        ls::vector<char> C = A;

        assert( A == B );
        assert( A == C );

        A.print();
        B.print();
        C.print();
    }
}