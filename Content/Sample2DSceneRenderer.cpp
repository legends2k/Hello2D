#include "pch.h"
#include "Sample2DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"

using namespace Hello2D;

using namespace DirectX;
using namespace Windows::Foundation;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample2DSceneRenderer::Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Initializes view parameters when the window size changes.
void Sample2DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
	}
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample2DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
	}
}

void Sample2DSceneRenderer::StartTracking()
{
	m_tracking = true;
}

void Sample2DSceneRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
	}
}

void Sample2DSceneRenderer::StopTracking()
{
	m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample2DSceneRenderer::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD2DDeviceContext();
	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::IndianRed));
	context->EndDraw();
}

void Sample2DSceneRenderer::CreateDeviceDependentResources()
{
	DX::ThrowIfFailed(
		m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AliceBlue), &m_blueBrush)
	);
	m_loadingComplete = true;
}

void Sample2DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
}