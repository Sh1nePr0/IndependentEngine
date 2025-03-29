#pragma once

#include "Independent/SystemFiles/include/Core.h"
#include "Layer.h"

#include "Independent/Core/include/containers/Vector.h"


namespace Independent {

	class INDEPENDENT_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		Vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		Vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		Vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}