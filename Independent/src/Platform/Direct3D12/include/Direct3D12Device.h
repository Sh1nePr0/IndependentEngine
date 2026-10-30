#pragma once

#ifdef _WIN32

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

namespace Independent {

	class Direct3D12Device final
	{
	public:
		Direct3D12Device();
		~Direct3D12Device() = default;

		Direct3D12Device(const Direct3D12Device&) = delete;
		Direct3D12Device& operator=(const Direct3D12Device&) = delete;

		ID3D12Device* GetDevice() const noexcept
		{
			return m_Device.Get();
		}

		IDXGIFactory4* GetFactory() const noexcept
		{
			return m_Factory.Get();
		}

		ID3D12CommandQueue* GetGraphicsQueue() const noexcept
		{
			return m_GraphicsQueue.Get();
		}

		void WaitForGraphicsQueue();

	private:
		Microsoft::WRL::ComPtr<IDXGIFactory4> m_Factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter1> m_Adapter;
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_GraphicsQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_GraphicsFence;
		UINT64 m_NextGraphicsFenceValue = 1;
	};
}

#endif