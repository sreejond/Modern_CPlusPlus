// user defined literals
// constexpr will force user defined literal to compute in compile time
constexpr long double operator"" _cm(long double x) {return x * 10;}
constexpr long double operator"" _m(long double x) {return x * 1000;}
constexpr long double operator"" _mm(long double x) {return x;}

int main ()
{
	long double height = 3.4_cm;
	cout << height << endl;
	cout <<  height + 13.0_m << endl;
	cout << 130.0_mm / 13.0_m << endl;
}


int operator"" _bin(const char* str, size_t l)
{
	int ret = 0;
	for (int i = 0; i < l; i++)
	{
		ret = ret << 1;
		if (str[i] == '1')	ret += 1;
	}
	return ret;
}

int main()
{
	cout << "110"_bin << endl;
	cout << "1100110"_bin << endl;
	cout << "11010010101011001001"_bin << endl;
}

// C++ went a long way to make user defined types (classes) to behave same as build-in types
// user defined literals pushes this effort even further