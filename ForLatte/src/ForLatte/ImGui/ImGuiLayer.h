#pragma once

#include "ForLatte/Layer.h"

#include "ForLatte/Events/KeyEvent.h"
#include "ForLatte/Events/ApplicationEvent.h"
#include "ForLatte/Events/MouseEvent.h"

namespace ForLatte {
	class ForLatte_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;


		void Begin();
		void End();

	private:
		float m_Time = 0;
	};
}
