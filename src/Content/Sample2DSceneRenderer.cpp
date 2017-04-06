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
	MakeScenery();
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Initializes view parameters when the window size changes.
void Sample2DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;

	auto dc = m_deviceResources->GetD2DDeviceContext();
	float dpiX, dpiY;
	dc->GetDpi(&dpiX, &dpiY);
	auto size = dc->GetSize();
	auto pxSize = dc->GetPixelSize();
	TIF(dc->CreateBitmap(D2D1::SizeU(static_cast<UINT32>(pxSize.width), static_cast<UINT32>(pxSize.height)),
		D2D1::BitmapProperties(dc->GetPixelFormat(), dpiX, dpiY),
		&m_sceneBitmap));

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

void Hello2D::Sample2DSceneRenderer::Zoom(bool zoomIn)
{
	m_scaleFactor += (zoomIn ? 1.0f : -1.0f) * m_scaleDelta;
}

void Hello2D::Sample2DSceneRenderer::ToggleRenderingMode()
{
	if (m_renderingMode == RenderingMode::Vector)
		m_renderingMode = RenderingMode::Raster;
	else
		m_renderingMode = RenderingMode::Vector;
}

// Renders one frame using the vertex and pixel shaders.
void Sample2DSceneRenderer::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	if ((m_renderingMode == RenderingMode::Raster) && !m_rasterized)
	{
		CacheRendering();
	}

	auto context = m_deviceResources->GetD2DDeviceContext();
	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::PapayaWhip));
	context->SetTransform(D2D1::Matrix3x2F::Scale(m_scaleFactor, m_scaleFactor));

	if (m_renderingMode == RenderingMode::Vector)
		RenderScene(context);
	else
	{
		auto dstSize = context->GetSize();
		D2D1_RECT_F dstRect{0.0f, 0.0f, static_cast<float>(dstSize.width), static_cast<float>(dstSize.height)};
		context->DrawBitmap(m_sceneBitmap.Get(), dstRect);
	}

	context->SetTransform(D2D1::Matrix3x2F::Identity());
	TIF(context->EndDraw());
}

void Sample2DSceneRenderer::CacheRendering()
{
	// draw at identity scale
	auto context = m_deviceResources->GetD2DDeviceContext();
	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::PapayaWhip));
	RenderScene(context);
	TIF(context->EndDraw());

	// copy bitmap
	auto srcBitmap = m_deviceResources->GetD2DTargetBitmap();
	auto size = srcBitmap->GetPixelSize();
	D2D_POINT_2U dstPt{};
	D2D_RECT_U srcRect{ 0, 0, size.width, size.height };
	TIF(m_sceneBitmap->CopyFromBitmap(&dstPt, srcBitmap, &srcRect));
	m_rasterized = true;
}

void Sample2DSceneRenderer::RenderScene(ID2D1DeviceContext2 *context)
{
	context->FillGeometry(m_pathSun.Get(), m_radialGradBrush.Get());

	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	context->DrawGeometry(m_pathSun.Get(), m_solidBrush.Get());

	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::OliveDrab));
	context->FillGeometry(m_pathLeftMountain.Get(), m_solidBrush.Get());

	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	context->DrawGeometry(m_pathLeftMountain.Get(), m_solidBrush.Get());

	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::LightSkyBlue));
	context->FillGeometry(m_pathRiver.Get(), m_solidBrush.Get());

	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	context->DrawGeometry(m_pathRiver.Get(), m_solidBrush.Get());

	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	context->FillGeometry(m_pathRightMountain.Get(), m_solidBrush.Get());

	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	context->DrawGeometry(m_pathRightMountain.Get(), m_solidBrush.Get());

	DrawPhotoFrame(context);
}

void Hello2D::Sample2DSceneRenderer::DrawPhotoFrame(ID2D1DeviceContext2 *context)
{
	auto size = m_deviceResources->GetOutputSize();
	context->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), m_pathPhotoFrame.Get()), m_clipLayer.Get());
	m_solidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::SaddleBrown));
	context->FillRectangle(D2D1::RectF(0.0f, 0.0f, size.Width, size.Height), m_solidBrush.Get());
	context->PopLayer();
}

void Sample2DSceneRenderer::CreateDeviceDependentResources()
{
	auto dc = m_deviceResources->GetD2DDeviceContext();
	TIF(dc->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Coral), &m_solidBrush));
	// Create an array of gradient stops to put in the gradient stop
	// collection that will be used in the gradient brush.
	ComPtr<ID2D1GradientStopCollection> gradientStopsColl;
	D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::OrangeRed);
	gradientStops[1].position = 1.0f;
	TIF(dc->CreateGradientStopCollection(gradientStops, ARRAYSIZE(gradientStops), &gradientStopsColl));
	auto radialBrushprops = D2D1::RadialGradientBrushProperties(m_sunCenter, D2D1::Point2F(), m_sunRadius, m_sunRadius);
	dc->CreateRadialGradientBrush(radialBrushprops, gradientStopsColl.Get(), &m_radialGradBrush);
	dc->CreateLayer(&m_clipLayer);
	m_loadingComplete = true;
}

// heartily lifted from https://msdn.microsoft.com/en-us/library/windows/desktop/ee264309(v=vs.85).aspx
void Sample2DSceneRenderer::MakeScenery()
{
	MakeLeftMountain();
	MakeRightMountain();
	MakeSun();
	MakeRiver();
	MakePhotoFrame();
}

void Sample2DSceneRenderer::MakeLeftMountain()
{
	TIF(m_deviceResources->GetD2DFactory()->CreatePathGeometry(&m_pathLeftMountain));
	ComPtr<ID2D1GeometrySink> pathCmds;
	TIF(m_pathLeftMountain->Open(&pathCmds));

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

void Sample2DSceneRenderer::MakeRightMountain()
{
	TIF(m_deviceResources->GetD2DFactory()->CreatePathGeometry(&m_pathRightMountain));
	ComPtr<ID2D1GeometrySink> pathCmds;
	TIF(m_pathRightMountain->Open(&pathCmds));

	pathCmds->SetFillMode(D2D1_FILL_MODE_WINDING);
	pathCmds->BeginFigure(
		D2D1::Point2F(575, 263),
		D2D1_FIGURE_BEGIN_FILLED        // also has HOLLOW a.k.a stroked
	);
	D2D1_POINT_2F points[] = {
		D2D1::Point2F(481, 146),
		D2D1::Point2F(449, 181),
		D2D1::Point2F(433, 159),
		D2D1::Point2F(401, 214),
		D2D1::Point2F(381, 199),
		D2D1::Point2F(323, 263),
		D2D1::Point2F(575, 263)
	};
	pathCmds->AddLines(points, ARRAYSIZE(points));
	pathCmds->EndFigure(D2D1_FIGURE_END_CLOSED);     // also has OPEN; leaves it open to append further figures to the geometry
	TIF(pathCmds->Close());                          // fill still works as though CLOSED; it's only strokes that're affected
}

void Hello2D::Sample2DSceneRenderer::MakeSun()
{
	TIF(m_deviceResources->GetD2DFactory()->CreatePathGeometry(&m_pathSun));
	ComPtr<ID2D1GeometrySink> pathCmds;
	TIF(m_pathSun->Open(&pathCmds));
	pathCmds->SetFillMode(D2D1_FILL_MODE_WINDING);

	pathCmds->BeginFigure(
		D2D1::Point2F(m_sunCenter.x - m_sunRadius, m_sunCenter.y),
		D2D1_FIGURE_BEGIN_FILLED
	);
	pathCmds->AddArc(
		D2D1::ArcSegment(
			D2D1::Point2F(440, 255), // end point
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
	TIF(pathCmds->Close());
}

void Hello2D::Sample2DSceneRenderer::MakeRiver()
{
	TIF(m_deviceResources->GetD2DFactory()->CreatePathGeometry(&m_pathRiver));
	ComPtr<ID2D1GeometrySink> pathCmds;
	TIF(m_pathRiver->Open(&pathCmds));
	pathCmds->SetFillMode(D2D1_FILL_MODE_WINDING);

	pathCmds->BeginFigure(
		D2D1::Point2F(183, 392),
		D2D1_FIGURE_BEGIN_FILLED
	);
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(238, 284),
			D2D1::Point2F(472, 345),
			D2D1::Point2F(356, 303)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(237, 261),
			D2D1::Point2F(333, 256),
			D2D1::Point2F(333, 256)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(335, 257),
			D2D1::Point2F(241, 261),
			D2D1::Point2F(411, 306)
		));
	pathCmds->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(574, 350),
			D2D1::Point2F(288, 324),
			D2D1::Point2F(296, 392)
		));
	pathCmds->EndFigure(D2D1_FIGURE_END_OPEN);
	TIF(pathCmds->Close());
}

void Hello2D::Sample2DSceneRenderer::MakePhotoFrame()
{
	TIF(m_deviceResources->GetD2DFactory()->CreatePathGeometry(&m_pathPhotoFrame));
	ComPtr<ID2D1GeometrySink> pathCmds;
	TIF(m_pathPhotoFrame->Open(&pathCmds));
	pathCmds->SetFillMode(D2D1_FILL_MODE_ALTERNATE);

	// Inner rect: 140, 120 -> 600, 416
	pathCmds->BeginFigure(D2D1::Point2F(140.0f, 120.0f), D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F corners1[] = { { 140.0f, 416.0f }, { 600.0f, 416.0f }, { 600.0f, 120.0f } };
	pathCmds->AddLines(corners1, ARRAYSIZE(corners1));
	pathCmds->EndFigure(D2D1_FIGURE_END_CLOSED);

	// Outer rect: 120, 100 -> 620, 436
	pathCmds->BeginFigure(D2D1::Point2F(120.0f, 100.0f), D2D1_FIGURE_BEGIN_FILLED);
	D2D1_POINT_2F corners2[] = { { 120.0f, 436.0f },{ 620.0f, 436.0f },{ 620.0f, 100.0f } };
	pathCmds->AddLines(corners2, ARRAYSIZE(corners2));
	pathCmds->EndFigure(D2D1_FIGURE_END_CLOSED);

	TIF(pathCmds->Close());
}

void Sample2DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
}