#include "pch.h"
#include "Sample2DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"

using namespace Hello2D;

using namespace DirectX;
using namespace Windows::Foundation;

using Microsoft::WRL::ComPtr;

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
	context->Clear(D2D1::ColorF(D2D1::ColorF::PapayaWhip));
	m_strokeBrush->SetColor(D2D1::ColorF(D2D1::ColorF::OliveDrab, 1.f));
	context->FillGeometry(m_pathLeftMountain.Get(), m_strokeBrush.Get());
	context->EndDraw();
}

void Sample2DSceneRenderer::CreateDeviceDependentResources()
{
	TIF(m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Coral), &m_strokeBrush));
	MakeScenery();
	m_loadingComplete = true;
}

// heartily lifted from https://msdn.microsoft.com/en-us/library/windows/desktop/ee264309(v=vs.85).aspx
void Sample2DSceneRenderer::MakeScenery()
{
	TIF(m_deviceResources->GetD2DFactory()->CreatePathGeometry(&m_pathLeftMountain));
	ComPtr<ID2D1GeometrySink> pathCmds;
	m_pathLeftMountain->Open(&pathCmds);

	pathCmds->SetFillMode(D2D1_FILL_MODE_WINDING);
	pathCmds->BeginFigure(
		D2D1::Point2F(346, 255),
		D2D1_FIGURE_BEGIN_FILLED        // also has HOLLOW a.k.a stroked
	);
	D2D1_POINT_2F points[5] = {
		D2D1::Point2F(267, 177),
		D2D1::Point2F(236, 192),
		D2D1::Point2F(212, 160),
		D2D1::Point2F(156, 255),
		D2D1::Point2F(346, 255),
	};
	pathCmds->AddLines(points, ARRAYSIZE(points));
	pathCmds->EndFigure(D2D1_FIGURE_END_CLOSED);     // also has OPEN; leaves it open to append further figures to the geometry
	TIF(pathCmds->Close());
}

void Sample2DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
}