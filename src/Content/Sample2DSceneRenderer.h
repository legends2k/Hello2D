#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace Hello2D
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample2DSceneRenderer
	{
	public:
		Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }

	private:
		void MakeScenery();
		void MakeLeftMountain();
		void MakeRightMountain();
		void MakeSun();
		void MakeRiver();
		void MakePhotoFrame();

		void RenderScene(ID2D1DeviceContext2 *context);
		void DrawPhotoFrame(ID2D1DeviceContext2 *context);

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources>             m_deviceResources;
														 
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>     m_solidBrush;
		Microsoft::WRL::ComPtr<ID2D1RadialGradientBrush> m_radialGradBrush;
														 
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathLeftMountain;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathRightMountain;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathSun;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathRiver;
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_pathPhotoFrame;
		
		Microsoft::WRL::ComPtr<ID2D1Layer>               m_clipLayer;
														 
		// Variables used with the rendering loop.		 
		bool	                                         m_loadingComplete;
		bool	                                         m_tracking;

		constexpr static auto                            m_sunRadius = 85.0f;
		constexpr static D2D1_POINT_2F                   m_sunCenter { 355.0f, 255.0f };
	};
}

