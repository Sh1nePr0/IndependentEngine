#pragma once


namespace Independent {

	class Timestep
	{
	public:
		Timestep(float time)
			: m_Time(time)
		{

		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.f; }
	private:
		float m_Time;
	};

}