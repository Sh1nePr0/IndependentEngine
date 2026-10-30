#include "Platform/Direct3D12/include/Direct3D12Device.h"

#ifdef _WIN32

#include "Platform/Direct3D12/include/Direct3D12Error.h"

#include <d3d12sdklayers.h>

#include <stdexcept>
#include <limits>

namespace Independent {

	using D3D12::CheckHRESULT;

	Direct3D12Device::Direct3D12Device()
	{
#if defined(IDPD_DEBUG)
		Microsoft::WRL::ComPtr<ID3D12Debug> debugController;

		CheckHRESULT(
			D3D12GetDebugInterface(
				IID_PPV_ARGS(debugController.GetAddressOf())),
			"D3D12GetDebugInterface");

		debugController->EnableDebugLayer();
#endif

		CheckHRESULT(
			CreateDXGIFactory2(
				0,
				IID_PPV_ARGS(m_Factory.GetAddressOf())),
			"CreateDXGIFactory2");

		for (UINT index = 0; ; ++index)
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;

			const HRESULT enumerationResult =
				m_Factory->EnumAdapters1(
					index,
					adapter.GetAddressOf());

			if (enumerationResult == DXGI_ERROR_NOT_FOUND)
				break;

			CheckHRESULT(
				enumerationResult,
				"IDXGIFactory::EnumAdapters1");

			DXGI_ADAPTER_DESC1 description{};

			CheckHRESULT(
				adapter->GetDesc1(&description),
				"IDXGIAdapter::GetDesc1");

			if (description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				continue;

			const HRESULT supportResult = D3D12CreateDevice(
				adapter.Get(),
				D3D_FEATURE_LEVEL_11_0,
				__uuidof(ID3D12Device),
				nullptr);
			

			if (SUCCEEDED(supportResult))
			{
				m_Adapter = adapter;
				break;
			}
		}

		if (!m_Adapter.Get())
		{
			throw std::runtime_error(
				"No hardware adapter supporting Direct 3D 12 was found.");
		}

		CheckHRESULT(
			D3D12CreateDevice(
				m_Adapter.Get(),
				D3D_FEATURE_LEVEL_11_0,
				IID_PPV_ARGS(m_Device.GetAddressOf())),
			"D3D12CreateDevice");

		D3D12_COMMAND_QUEUE_DESC queueDescription{};

		queueDescription.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDescription.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		queueDescription.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDescription.NodeMask = 0;

		CheckHRESULT(
			m_Device->CreateCommandQueue(
				&queueDescription,
				IID_PPV_ARGS(m_GraphicsQueue.GetAddressOf())),
			"ID3D12Device::CreateCommandQueue");

		CheckHRESULT(
			m_GraphicsQueue->SetName(L"Independent Graphics Queue"),
			"ID3D12CommandQueue::SetName");

		CheckHRESULT(
			m_Device->CreateFence(
				0,
				D3D12_FENCE_FLAG_NONE,
				IID_PPV_ARGS(m_GraphicsFence.GetAddressOf())),
			"ID3D12Device::CreateFence");

		CheckHRESULT(
			m_GraphicsFence->SetName(L"Independent Graphics Fence"),
			"ID3D12Fence::SetName");


	}

	void Direct3D12Device::WaitForGraphicsQueue()
	{
		const UINT64 reservedValue =
			(std::numeric_limits<UINT64>::max)();

		if (m_NextGraphicsFenceValue == reservedValue)
		{
			throw std::overflow_error(
				"Graphics fence value range exhausted.");
		}

		const UINT64 valueToWaitFor = m_NextGraphicsFenceValue;

		CheckHRESULT(
			m_GraphicsQueue->Signal(
				m_GraphicsFence.Get(),
				valueToWaitFor),
			"ID3D12CommandQueue::Signal");

		++m_NextGraphicsFenceValue;

		CheckHRESULT(
			m_GraphicsFence->SetEventOnCompletion(
				valueToWaitFor,
				nullptr),
			"ID3D12Fence::SetEventOnCompletion");

		CheckHRESULT(
			m_Device->GetDeviceRemovedReason(),
			"ID3D12Device::GetDeviceRemovedReason()");
	}
}

#endif