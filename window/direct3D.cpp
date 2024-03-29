#include "direct3D.h"

namespace _direct3D{

	HRESULT Direct3D::initDirect3D(HWND hwnd,int width,int height)
	{
		wnd_width = width;
		wnd_height = height;

		//创建direct3d接口
		LPDIRECT3D9 pD3D=NULL;
		pD3D=Direct3DCreate9(D3D_SDK_VERSION);
		if(pD3D==NULL)
			return E_FAIL;
		
		//获取硬件设备信息
		D3DCAPS9 caps;
		int vp=0;
		pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps);
		vp=D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		
		//创建direct3d设备接口
		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp.BackBufferWidth            = width;
		d3dpp.BackBufferHeight           = height;
		d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount            = 1;
		d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality         = 0;
		d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow              = hwnd;
		d3dpp.Windowed                   = TRUE;
		d3dpp.EnableAutoDepthStencil     = true;
		d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
		d3dpp.Flags                      = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
		
		pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,vp,&d3dpp,&g_pd3dDevice);
		pD3D->Release();
		
		g_pd3dDevice->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pd3dSurface, 0);
		return S_OK;
	}
	
	Direct3D::~Direct3D()
	{
		if(g_pd3dSurface!=NULL)
			g_pd3dSurface->Release();
		g_pd3dSurface=NULL;
		if(g_pd3dDevice!=NULL)
			g_pd3dDevice->Release();
		g_pd3dDevice=NULL;
	}
	
	int Direct3D::LockSurface()
	{
		memset(&lockedRect, 0, sizeof(lockedRect));
		g_pd3dSurface->LockRect(&lockedRect,NULL,D3DLOCK_DISCARD);
		//将背景初始化为白色
		memset(lockedRect.pBits,0xff,wnd_width*wnd_height*sizeof(int));
		return 1;
	}
	
	int Direct3D::UnlockSurface()
	{
		g_pd3dSurface->UnlockRect();
		return 1;
	}
	
	void Direct3D::FlipSurface()
	{
		// 获取后台缓存
		IDirect3DSurface9* backBuffer = 0;
		g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
		
		// 使用自定义表面填充后台缓存
		g_pd3dDevice->StretchRect(g_pd3dSurface, 0, backBuffer, 0, D3DTEXF_NONE);
		
		// GetBackBuffer所得的缓存需要被释放，否则会内存泄露
		backBuffer->Release();
		
		// 将交换链中的后台缓存显示
		g_pd3dDevice->Present(0, 0, 0, 0);
	}

}
