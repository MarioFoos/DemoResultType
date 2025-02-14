#include <iostream>
#include <type_traits>
#include <utility>
#include <functional>	// invoke

using namespace std;

class CSumar
{
	public:
		int operator()(int a, int b) const
		{
			return a + b;
		}
};

class Persona
{
	private:
		string nombre;
	public:
		Persona(string nombre) : nombre(nombre){};

		string getNombre() const
		{
			return nombre;
		}
};

int doble(int num)
{
	return 2 * num;
}

auto triple(float num)
{
	return 3 * num;
}

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	test9();

	return 0;
}

void test9()
{
    Persona p{"Carlos"};

    // Puntero a miembro a la función
    auto ptrGetNombre = &Persona::getNombre;

    // Deducimos el tipo de retorno
    using Resultado = std::invoke_result_t<decltype(ptrGetNombre), Persona>;

    // La invocación se hace usando std::invoke
    Resultado res = invoke(ptrGetNombre, p);

    cout << res << endl;
}

void test8()
{
    CSumar sumar;

    // Deducimos el tipo de retorno al invocar el functor
    using Resultado = invoke_result_t<CSumar, int, int>;

    Resultado resultado = sumar(11, 7);
    cout << "Resultado del functor: " << resultado << endl;
}

void test7()
{
	auto producto = [](double x, double y)
	{
		return x*y;
	};
	// Deducimos el tipo de retorno de la lambda con dos argumentos double
	using ResProdT = invoke_result_t<decltype(producto), double, double>;

	ResProdT res = producto(3.0, 4.0);
	cout << "Producto: " << res << endl;
}

void test6()
{
	// Usamos invoke_result_t para deducir el tipo de retorno de las funciones
	// y definimos los tipos de resultados con using
	using ResDobleT = invoke_result_t<decltype(doble), int>;
	using ResTripleT = invoke_result_t<decltype(triple), float>;

	// 'Resultado' es int, porque suma(int, int) devuelve un int
	ResDobleT numx2 = doble (5);
	ResTripleT numx3 = triple (7);

	cout << "numx2: " << numx2 << endl << "numx3: " << numx3 << endl;
}

void test5()
{
    CSumar sumar;

    // Deducimos el tipo de retorno al invocar el functor
    using Resultado = result_of<CSumar(int, int)>::type ;

    Resultado resultado = sumar(11, 7);
    cout << "Resultado del functor: " << resultado << endl;
}

void test4()
{
	auto producto = [](double x, double y)
	{
		return x*y;
	};
	// Deducimos el tipo de retorno de la lambda con dos argumentos double
	using ResProdT = result_of<decltype(producto)& (double, double)>::type;

	ResProdT res = producto(3.0, 4.0);
	cout << "Producto: " << res << endl;
}
void test3()
{
	auto producto = [](double x, double y)
	{
		return x*y;
	};
	// Deducimos el tipo de retorno de la lambda con dos argumentos double
	typedef result_of<decltype(producto)& (double, double)>::type ResProdT;

	ResProdT res = producto(3.0, 4.0);
	cout << "Producto: " << res << endl;
}

void test2()
{
	// Usamos result_of para deducir el tipo de retorno de las funciones
	// 'doble' y 'triple' y definimos los tipos de resultados
	// de forma introducida en C++, o sea, con using
	using ResDobleT = result_of<decltype(doble)&(int)>::type;
	using ResTripleT = result_of<decltype(triple)&(float)>::type;

	ResDobleT numx2 = doble(5);
	ResTripleT numx3 = triple(7);
	cout << "numx2: " << numx2 << endl << "numx3: " << numx3 << endl;
}

void test1()
{
	// Usamos result_of para deducir el tipo de retorno de las funciones
	// 'doble' y 'triple' y definimos los tipos de resultados
	// de forma tradicional con typedef
	typedef result_of<decltype(doble)& (int)>::type ResDobleT;
	typedef result_of<decltype(triple)& (float)>::type ResTripleT;

	ResDobleT numx2 = doble(5);
	ResTripleT numx3 = triple(7);
	cout << "numx2: " << numx2 << endl << "numx3: " << numx3 << endl;
}
