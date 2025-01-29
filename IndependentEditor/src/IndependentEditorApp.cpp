#include <Independent.h>

class IndependentEditor : public Independent::Application
{
public:
	IndependentEditor()
	{

	}

	~IndependentEditor()
	{

	}


};

Independent::Application* Independent::CreateApplication()
{
	return new IndependentEditor();
}
