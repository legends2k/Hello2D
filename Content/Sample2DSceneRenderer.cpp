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
	RenderScene(context);
	context->EndDraw();
}

void Sample2DSceneRenderer::RenderScene(ID2D1DeviceContext2 *context)
{
	context->FillGeometry(m_pathSun.Get(), m_radialGradBrush.Get());
}

void Sample2DSceneRenderer::CreateDeviceDependentResources()
{
	auto dc = m_deviceResources->GetD2DDeviceContext();
	// https://msdn.microsoft.com/en-us/library/windows/desktop/dd756651(v=vs.85).aspx
	// Create an array of gradient stops to put in the gradient stop
	// collection that will be used in the gradient brush.
	ComPtr<ID2D1GradientStopCollection> gradientStopsColl;
	D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::OrangeRed);
	gradientStops[1].position = 1.0f;
	DX::ThrowIfFailed(dc->CreateGradientStopCollection(gradientStops, ARRAYSIZE(gradientStops), &gradientStopsColl));
	auto radialBrushprops = D2D1::RadialGradientBrushProperties(m_sunCenter, D2D1::Point2F(), m_sunRadius, m_sunRadius);
	dc->CreateRadialGradientBrush(radialBrushprops, gradientStopsColl.Get(), &m_radialGradBrush);
	MakeScenery();
	m_loadingComplete = true;
}

// heartily lifted from https://msdn.microsoft.com/en-us/library/windows/desktop/ee264309(v=vs.85).aspx
void Sample2DSceneRenderer::MakeScenery()
{
	MakeSun();
}

void Hello2D::Sample2DSceneRenderer::MakeSun()
{
	DX::ThrowIfFailed(m_deviceResources->GetD2DFactory()->CreatePathGeometry(&m_pathSun));
	ComPtr<ID2D1GeometrySink> pathCmds;
	DX::ThrowIfFailed(m_pathSun->Open(&pathCmds));
	pathCmds->SetFillMode(D2D1_FILL_MODE_WINDING);

	pathCmds->BeginFigure(
		D2D1::Point2F(m_sunCenter.x - m_sunRadius, m_sunCenter.y),
		D2D1_FIGURE_BEGIN_FILLED
	);
	pathCmds->AddArc(
		D2D1::ArcSegment(
			D2D1::Point2F(m_sunCenter.x + m_sunRadius, m_sunCenter.y), // end point
			D2D1::SizeF(m_sunRadius, m_sunRadius),
			0.0f, // rotation angle
			D2D1_SWEEP_DIRECTION_CLOCKWISE,
			D2D1_ARC_SIZE_SMALL
		));
	pathCmds->EndFigure(D2D1_FIGURE_END_CLOSED);

	pathCmds->BeginFigure(
		D2D1::Point2F(299, 182),
		D2D1_FIGURE_BEGIN_HOLLOW
	);
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(299, 182),
			D2D1::Point2F(294, 176),
			D2D1::Point2F(285, 178)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(276, 179),
			D2D1::Point2F(272, 173),
			D2D1::Point2F(272, 173)
		));
	pathCmds->EndFigure(D2D1_FIGURE_END_OPEN);

	pathCmds->BeginFigure(
		D2D1::Point2F(354, 156),
		D2D1_FIGURE_BEGIN_HOLLOW
	);
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(354, 156),
			D2D1::Point2F(358, 149),
			D2D1::Point2F(354, 142)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(349, 134),
			D2D1::Point2F(354, 127),
			D2D1::Point2F(354, 127)
		));
	pathCmds->EndFigure(D2D1_FIGURE_END_OPEN);

	pathCmds->BeginFigure(
		D2D1::Point2F(322, 164),
		D2D1_FIGURE_BEGIN_HOLLOW
	);
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(322, 164),
			D2D1::Point2F(322, 156),
			D2D1::Point2F(314, 152)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(306, 149),
			D2D1::Point2F(305, 141),
			D2D1::Point2F(305, 141)
		));
	pathCmds->EndFigure(D2D1_FIGURE_END_OPEN);

	pathCmds->BeginFigure(
		D2D1::Point2F(385, 164),
		D2D1_FIGURE_BEGIN_HOLLOW
	);
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(385, 164),
			D2D1::Point2F(392, 161),
			D2D1::Point2F(394, 152)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(395, 144),
			D2D1::Point2F(402, 141),
			D2D1::Point2F(402, 142)
		));
	pathCmds->EndFigure(D2D1_FIGURE_END_OPEN);

	pathCmds->BeginFigure(
		D2D1::Point2F(408, 182),
		D2D1_FIGURE_BEGIN_HOLLOW
	);
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(408, 182),
			D2D1::Point2F(416, 184),
			D2D1::Point2F(422, 178)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(428, 171),
			D2D1::Point2F(435, 173),
			D2D1::Point2F(435, 173)
		));
	pathCmds->EndFigure(D2D1_FIGURE_END_OPEN);
	DX::ThrowIfFailed(pathCmds->Close());
}

void Sample2DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
}
