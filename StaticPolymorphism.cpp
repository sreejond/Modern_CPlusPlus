/*
		Static Polymorphism
*/

// (Dynamic) Polymorphism

struct TreeNode {TreeNode *left, * right;};

class GenericParser {
public:
	void parsePreorder(TreeNode* node)
	{
		if (node)
		{
			processNode(node);
			parsePreorder(node->left);
			parsePreorder(node->right);
		}
	}

private:
	virtual void processNode(TreeNode* node) {}
};

class EmployeeChartParser : public GenericParser
{
private:
	void processNode(TreeNode* node)
	{
		cout << "Customized processNode() for EmployeeChartParser\n";
	}
};

int main ()
{
	EmployeeChartParser ep;
	ep.parsePreorder(root);
	...
}

/*
1. is-a relationship between base class and derived class
2. base class defines a "generic" algorithm that's used by derived class
3. the "generic" algorithm is customized by the derived class
*/


// TMP: Template Metaprogramming
template <typename T> 
class GenericParser
{
public:
	void parsePreorder(TreeNode* node)
	{
		if (node)
		{
			processNode(node);
			parsePreorder(node->left);
			parsePreorder(node->right);
		}
	}

private:
	virtual void processNode(TreeNode* node) 
	{
		static_cast<T*>(this)->processNode(node);
	}
};

class EmployeeChartParser: public GenericParser<EmployeeChartParser>
{
public:
	void processNode(TreeNode* node)
	{
		cout << "Customized processNode() for EmployeeChartParser\n";
	}
};

int main()
{
	EmployeeChartParser ep;
	ep.parsePreorder(root);
	...
}

// This is called Curiously Recurring Template Pattern (static polymorphism, simulated polymorphism)



// Generalized Static Polymorphism
template<typename T>
T Max(vector<T> v)
{
	T max = v[0];
	for (typename vector<T>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (*it > max)
			ret = *it;
	}

	return max;
}