#pragma once

#include "Independent/Layer.h"
#include "Independent/Events/ApplicationEvent.h"
#include "Independent/Events/KeyEvent.h"
#include "Independent/Events/MouseEvent.h"

namespace Independent {

	class INDEPENDENT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRenderer() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}