#pragma once

#ifdef _WIN32

#include <d3d12.h>
#include <wrl/client.h>

namespace Independent {

	class Direct3D12Device;

	class Direct3D12CommandContext final
	{
	public:
		explicit Direct3D12CommandContext(
			const Direct3D12Device& device);

		~Direct3D12CommandContext() = default;

		Direct3D12CommandContext(
			const Direct3D12CommandContext&) = delete;

		Direct3D12CommandContext& operator=(
			const Direct3D12CommandContext&) = delete;

		ID3D12GraphicsCommandList* GetCommandList() const noexcept
		{
			return m_CommandList.Get();
		}

		void BeginRecording();
		void EndRecording();

	private:
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_Allocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		bool m_IsRecording = false;
	};
}

#endif