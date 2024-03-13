//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include "stdafx.h"
#include "DXHelper.h"
#include "Win32Application.h"
#include "Modeldata.h"
#include <stdexcept>

using namespace DirectX;

using Microsoft::WRL::ComPtr;

struct Transform 
{
    XMMATRIX World; // ���[���h�s��
    XMMATRIX View; // �r���[�s��
    XMMATRIX Proj; // ���e�s��
    float padding[16]; // Padding so the constant buffer is 256-byte aligned.
};
static_assert((sizeof(Transform) % 256) == 0, "Constant Buffer size must be 256-byte aligned");



class D3D12Application 
{
public:

    D3D12Application(UINT width, UINT height, std::wstring name);
    ~D3D12Application();

    virtual void OnInit();
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnDestroy();

    virtual void OnKeyDown(UINT8) {}
    virtual void OnKeyUp(UINT8) {}

    // Accessors.
    UINT GetWidth() const { return m_width; }
    UINT GetHeight() const { return m_height; }
    const WCHAR* GetTitle() const { return m_title.c_str(); }
    ID3D12Device* D3D12Application::GetDevice() {return m_device.Get();}
    ID3D12GraphicsCommandList* D3D12Application::GetCommandList(){return m_commandList.Get();}
    UINT D3D12Application::GetframeIndex(){return m_frameIndex;}

    void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);

private:
    static const UINT FrameCount = 2;

    // Root assets path.
    std::wstring m_assetsPath;

    // Window title.
    std::wstring m_title;

    std::wstring GetAssetFullPath(LPCWSTR assetName);

    void GetHardwareAdapter(
        _In_ IDXGIFactory1* pFactory,
        _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter,
        bool requestHighPerformanceAdapter = false);

    void SetCustomWindowText(LPCWSTR text);

    // Viewport dimensions.
    UINT m_width;
    UINT m_height;
    float m_aspectRatio;

    // Adapter info.
    bool m_useWarpDevice;

    // Pipeline objects.
    CD3DX12_VIEWPORT m_viewport;
    CD3DX12_RECT m_scissorRect;
    ComPtr<IDXGISwapChain3> m_swapChain;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator[FrameCount];
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<ID3D12RootSignature> m_rootSignature;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    ComPtr<ID3D12DescriptorHeap> m_cbvHeap;
    ComPtr<ID3D12PipelineState> m_pipelineState;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    UINT m_rtvDescriptorSize;
    UINT m_dsvDescriptorSize;

    // App resources.
    ComPtr<ID3D12Resource> m_vertexBuffer;
    ComPtr<ID3D12Resource> m_indexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
    D3D12_INDEX_BUFFER_VIEW m_indexBufferView;
    ComPtr<ID3D12Resource> m_depthStencilBuffer;
    ComPtr<ID3D12DescriptorHeap> m_dsvHeap;
    ComPtr<ID3D12Resource> m_constantBuffer[FrameCount];
    Transform m_constantBufferData[FrameCount];
    UINT8* m_pCbvDataBegin[FrameCount];

    // Synchronization objects.
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue[FrameCount];

    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void WaitForGpu();
    void MoveToNextFrame();
};

