#pragma once

#include "Independent/SystemFiles/include/Core.h"
#include "Independent/SystemFiles/include/Events/Event.h"
#include "Independent/Core/include/containers/String.h"
#include "Independent/Core/include/utils/Timestep.h"

namespace Independent {

	class INDEPENDENT_API Layer
	{
	public:
		Layer(const String& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRenderer() {}
		virtual void OnEvent(Event& event) {}

		inline const String& GetName() const { return m_DebugName; }

	protected:
		String m_DebugName;
	};
}