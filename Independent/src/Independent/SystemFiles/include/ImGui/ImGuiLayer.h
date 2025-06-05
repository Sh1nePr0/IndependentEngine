#pragma once

#include "Independent/SystemFiles/include/Layer.h"
#include "Independent/SystemFiles/include/Events/ApplicationEvent.h"
#include "Independent/SystemFiles/include/Events/KeyEvent.h"
#include "Independent/SystemFiles/include/Events/MouseEvent.h"

namespace Independent {

	class INDEPENDENT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}