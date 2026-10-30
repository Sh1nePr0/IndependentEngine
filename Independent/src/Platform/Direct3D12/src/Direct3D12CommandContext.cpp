#include "Platform/Direct3D12/include/Direct3D12CommandContext.h"

#ifdef _WIN32

#include "Platform/Direct3D12/include/Direct3D12Device.h"
#include "Platform/Direct3D12/include/Direct3D12Error.h"

#include <stdexcept>

namespace Independent {

	Direct3D12CommandContext::Direct3D12CommandContext(
		const Direct3D12Device& device)
	{
		D3D12::CheckHRESULT(
			device.GetDevice()->CreateCommandAllocator(
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				IID_PPV_ARGS(m_Allocator.GetAddressOf())),
			"ID3D12Device::CreateCommandAllocator");

		D3D12::CheckHRESULT(
			m_Allocator->SetName(L"Independent Command Allocator"),
			"ID3D12CommandAllocator::SetName");

		D3D12::CheckHRESULT(
			device.GetDevice()->CreateCommandList(
				0,
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				m_Allocator.Get(),
				nullptr,
				IID_PPV_ARGS(m_CommandList.GetAddressOf())),
			"ID3D12Device::CreateCommandList");

		D3D12::CheckHRESULT(
			m_CommandList->SetName(L"Independent Graphics Command List"),
			"ID3D12GraphicsCommandList::SetName");

		D3D12::CheckHRESULT(
			m_CommandList->Close(),
			"ID3D12GraphicsCommandList::Close");
	}

	void Direct3D12CommandContext::BeginRecording()
	{
		if (m_IsRecording)
		{
			throw std::logic_error(
				"Command context is already recording.");
		}

		D3D12::CheckHRESULT(
			m_Allocator->Reset(),
			"ID3D12CommandAllocator::Reset");

		D3D12::CheckHRESULT(
			m_CommandList->Reset(
				m_Allocator.Get(),
				nullptr),
			"ID3D12GraphicsCommandList::Reset");

		m_IsRecording = true;
	}

	void Direct3D12CommandContext::EndRecording()
	{
		if (!m_IsRecording)
		{
			throw std::logic_error(
				"Command context is not recording.");
		}

		D3D12::CheckHRESULT(
			m_CommandList->Close(),
			"ID3D12GraphicsCommandList::Close");

		m_IsRecording = false;
	}
}

#endif