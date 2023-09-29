#include <d3dcompiler.h>
#include "Direct3D.h"
#include "Global.h"
#include "Transform.h"

//��ʂ̕`��Ɋւ��鏈��
namespace Direct3D
{
	ID3D11Texture2D* pDepthTexture = nullptr;			//�[�x���������ރe�N�X�`��
	ID3D11RenderTargetView* pDepthTargetView = nullptr;	//���̃r���[
	XMMATRIX lightView_;
	XMMATRIX clipToUV_;
	ID3D11ShaderResourceView* pDepthSRV_ = nullptr;
	ID3D11SamplerState* pDepthSampler_ = nullptr;

	//�y�X���b�v�`�F�[���z
	//��p����2���p�����Ă����A�Е�����ʂɉf���Ă���Ԃɂ�������ɕ`��B
	//1�t���[�����̊G���o���オ�������p���������B����ɂ���ʂ�������Ȃ��B
	//���̕ӂ��i��̂��X���b�v�`�F�[��
	IDXGISwapChain*         pSwapChain_ = nullptr;

	//�y�����_�[�^�[�Q�b�g�r���[�z
	//�`�悵�������̂ƁA�`���i��ł�����p���j�̋��n�����������
	ID3D11RenderTargetView* pRenderTargetView_ = nullptr;

	//�y�f�v�X�X�e���V���z
	//Z�o�b�t�@�@��p���āA3D���̂̑O��֌W�𐳂����\�����邽�߂̂���
	ID3D11Texture2D*		pDepthStencil;

	//�y�f�v�X�X�e���V���r���[�z
	//�f�v�X�X�e���V���̏����V�F�[�_�[�ɓn�����߂̂���
	ID3D11DepthStencilView* pDepthStencilView;
	ID3D11DepthStencilState* pDepthStencilState[BLEND_MAX];

	//�y�u�����h�X�e�[�g�z
	//�������̂��̂��ǂ̂悤�ɕ\�����邩
	ID3D11BlendState* pBlendState[BLEND_MAX];


	bool		isDrawCollision_ = true;	//�R���W������\�����邩
	bool		_isLighting = false;		//���C�e�B���O���邩

	DWORD vectorSize = sizeof(XMFLOAT3);

	//�r���[�|�[�g
	D3D11_VIEWPORT vp;
	D3D11_VIEWPORT vp_left;
	D3D11_VIEWPORT vp_right;

	//extern�錾�����ϐ��̏�����
	ID3D11Device*           pDevice_ = nullptr;
	ID3D11DeviceContext*    pContext_ = nullptr;
	SHADER_BUNDLE			shaderBundle[SHADER_MAX] = { 0 };
	int						screenWidth_ = 0;
	int						screenHeight_ = 0;

	SHADER_TYPE shaderType_;

	//����������
	HRESULT Direct3D::Initialize(HWND hWnd, int screenWidth, int screenHeight)
	{
		///////////////////////////���낢�돀�����邽�߂̐ݒ�///////////////////////////////
		//���낢��Ȑݒ荀�ڂ��܂Ƃ߂��\����
		DXGI_SWAP_CHAIN_DESC scDesc;

		//�Ƃ肠�����S��0
		ZeroMemory(&scDesc, sizeof(scDesc));

		//�`���̃t�H�[�}�b�g
		scDesc.BufferDesc.Width = screenWidth;		//��ʕ�
		scDesc.BufferDesc.Height = screenHeight;		//��ʍ���
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

		//FPS�i1/60�b��1��j
		scDesc.BufferDesc.RefreshRate.Numerator = 60;
		scDesc.BufferDesc.RefreshRate.Denominator = 1;

		//���̑�
		scDesc.Windowed = TRUE;				//�E�B���h�E���[�h���t���X�N���[����
		scDesc.OutputWindow = hWnd;			//�E�B���h�E�n���h��
		scDesc.BufferCount = 1;				//����ʂ̖���
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//��ʂɕ`�悷�邽�߂Ɏg��
		scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
		scDesc.SampleDesc.Quality = 0;		//�@�V



		///////////////////////////��L�ݒ�����ƂɃf�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C�����쐬///////////////////////////////
		D3D_FEATURE_LEVEL level;
		HRESULT  hr;
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,					// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
			D3D_DRIVER_TYPE_HARDWARE,	// �h���C�o�̃^�C�v��n���B����ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA�ǂ����Ă��Ƃ�������f�o�O�p�ɗp����ׂ�.
			nullptr,					// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n��.
			0,							// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
			nullptr,					// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ��Ή\�Ȍ��荂�����x���ɂ��Ă����
			0,							// ��̈����Ń��x�������w�肵����
			D3D11_SDK_VERSION,			// SDK�̃o�[�W�����B�K�����̒l
			&scDesc,					// ��ł��낢��ݒ肵���\����
			&pSwapChain_,				// ������������SwapChain�̃A�h���X���Ԃ��Ă���
			&pDevice_,					// ������������Device�A�h���X���Ԃ��Ă���
			&level,						// ������������Device�AContext�̃��x�����Ԃ��Ă���
			&pContext_);				// ������������Context�̃A�h���X���Ԃ��Ă���

		//���s������I��
		if (FAILED(hr))	return hr;


		///////////////////////////�`��̂��߂̏���///////////////////////////////
		//�X���b�v�`�F�[������o�b�N�o�b�t�@���擾�i�o�b�N�o�b�t�@ �� ����� �� �`���j
		ID3D11Texture2D* pBackBuffer;
		hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		//���s������I��
		if (FAILED(hr))	return hr;

		//�����_�[�^�[�Q�b�g�r���[���쐬
		hr = pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_);

		//���s������I��
		if (FAILED(hr))	return hr;

		//�ꎞ�I�Ƀo�b�N�o�b�t�@���擾���������Ȃ̂ŁA���
		pBackBuffer->Release();

		//��
		// �r���[�|�[�g�̐ݒ�
		//�����_�����O���ʂ�\������͈�
		//����ʗp
		{
			vp_left.Width = (float)screenWidth / 2;			//��
			vp_left.Height = (float)screenHeight;		//����
			vp_left.MinDepth = 0.0f;		//��O
			vp_left.MaxDepth = 1.0f;		//��
			vp_left.TopLeftX = 0;		//��
			vp_left.TopLeftY = 0;		//��
		}

		//�E��ʗp
		{
			vp_right.Width = (float)screenWidth / 2;			//��
			vp_right.Height = (float)screenHeight;		//����
			vp_right.MinDepth = 0.0f;		//��O
			vp_right.MaxDepth = 1.0f;		//��
			vp_right.TopLeftX = (float)screenWidth / 2;		//��
			vp_right.TopLeftY = 0;		//��
		}




		/////////////////////////////////////////////////////////////////////////////////////////////


		// �r���[�|�[�g�̐ݒ�
		//�����_�����O���ʂ�\������͈�
		vp.Width = (float)screenWidth;			//��
		vp.Height = (float)screenHeight;		//����
		vp.MinDepth = 0.0f;		//��O
		vp.MaxDepth = 1.0f;		//��
		vp.TopLeftX = 0;		//��
		vp.TopLeftY = 0;		//��


		//�e�p�^�[���̃V�F�[�_�[�Z�b�g����
		InitShader();
		Direct3D::SetShader(Direct3D::SHADER_3D);

		//�[�x�X�e���V���r���[�̍쐬
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = screenWidth;
		descDepth.Height = screenHeight;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		pDevice_->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
		pDevice_->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);


		//�[�x�e�X�g���s���[�x�X�e���V���X�e�[�g�̍쐬
		{
			//�f�t�H���g
			D3D11_DEPTH_STENCIL_DESC desc = {};
			desc.DepthEnable = true;
			desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			desc.StencilEnable = true;
			pDevice_->CreateDepthStencilState(&desc, &pDepthStencilState[BLEND_DEFAULT]);
			pContext_->OMSetDepthStencilState(pDepthStencilState[BLEND_DEFAULT], 0);

			//���Z�����p�i�������݂Ȃ��j
			desc.StencilEnable = false;
			pDevice_->CreateDepthStencilState(&desc, &pDepthStencilState[BLEND_ADD]);
		}


		//�u�����h�X�e�[�g
		{
			//�ʏ�
			D3D11_BLEND_DESC BlendDesc;
			ZeroMemory(&BlendDesc, sizeof(BlendDesc));
			BlendDesc.AlphaToCoverageEnable = FALSE;
			BlendDesc.IndependentBlendEnable = FALSE;
			BlendDesc.RenderTarget[0].BlendEnable = TRUE;

			BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

			BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			pDevice_->CreateBlendState(&BlendDesc, &pBlendState[BLEND_DEFAULT]);
			float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
			pContext_->OMSetBlendState(pBlendState[BLEND_DEFAULT], blendFactor, 0xffffffff);

			//���Z�����i�d�Ȃ�قǌ����Č�������ʁj
			BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			pDevice_->CreateBlendState(&BlendDesc, &pBlendState[BLEND_ADD]);
		}

		//�p�C�v���C���̍\�z
		//�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�
		pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // �f�[�^�̓��͎�ނ��w��
		pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView);            // �`����ݒ�i����̓����_�[�^�[�Q�b�g�r���[����ĕ`�悵�Ăˁj
		pContext_->RSSetViewports(1, &vp);                                      // �r���[�|�[�g�̃Z�b�g






		//�R���W�����\�����邩
		isDrawCollision_ = GetPrivateProfileInt("DEBUG", "ViewCollider", 0, ".\\setup.ini") != 0;


		screenWidth_ = screenWidth;
		screenHeight_ = screenHeight;


		// �V�F�[�_���\�[�X�r���[(�e�N�X�`���p)�̐ݒ�
		D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
		srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv.Texture2D.MipLevels = 1;
		Direct3D::pDevice_->CreateShaderResourceView(pDepthTexture, &srv, &pDepthSRV_);


		// �e�N�X�`���[�p�T���v���[�쐬
		D3D11_SAMPLER_DESC  SamDesc;
		ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
		SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		Direct3D::pDevice_->CreateSamplerState(&SamDesc, &pDepthSampler_);

		//�J�������猩������_���A���C�g���猩�����ǂ̈ʒu�ɂȂ邩�����߂邽�߂ɕK�v�ȍs��
		XMFLOAT4X4 clip;
		ZeroMemory(&clip, sizeof(XMFLOAT4X4));
		clip._11 = 0.5;
		clip._22 = -0.5;
		clip._33 = 1;
		clip._41 = 0.5;
		clip._42 = 0.5;
		clip._44 = 1;

		clipToUV_ = XMLoadFloat4x4(&clip);

		return S_OK;
	}


	//�V�F�[�_�[�֘A�ŕK�v�ȃZ�b�g����
	HRESULT InitShader()
	{
		if (FAILED(InitShader3D()))
		{
			return E_FAIL;
		}
		if (FAILED(InitShader2D()))
		{
			return E_FAIL;
		}
		if (FAILED(InitShaderUnlit()))
		{
			return E_FAIL;
		}
		if (FAILED(InitShaderBillBoard()))
		{
			return E_FAIL;
		}


		//�e
		{	
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Shadow.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_SHADOW].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Shadow.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_SHADOW].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_SHADOW].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_SHADOW].pRasterizerState);
		}


		//OutLine
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/OutLine.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_OUTLINE].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/OutLine.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_OUTLINE].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
			};
			pDevice_->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_OUTLINE].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = FALSE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_OUTLINE].pRasterizerState);
		}

		//�m�[�}���}�b�v
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/WaterShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_NORMALMAP].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/WaterShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_NORMALMAP].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
				{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 } //�ڐ�
			};
			pDevice_->CreateInputLayout(layout, 4, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_NORMALMAP].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_NORMALMAP].pRasterizerState);
		}

		//FadeIn
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_IN].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "PS_FadeIn", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_IN].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_FADE_IN].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_FADE_IN].pRasterizerState);
		}

		//FadeOut
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_OUT].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob* pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Fade.hlsl", nullptr, nullptr, "PS_FadeOut", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_FADE_OUT].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_FADE_OUT].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_FADE_OUT].pRasterizerState);
		}

		return S_OK;
	}

	HRESULT InitShader3D()
	{
		// ���_�V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompileVS = NULL;
		D3DCompileFromFile(L"Shader/Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
		pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pVertexShader);


		// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompilePS = NULL;
		D3DCompileFromFile(L"Shader/Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
		pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pPixelShader);


		// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
		};
		pDevice_->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_3D].pVertexLayout);


		//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
		pCompileVS->Release();
		pCompilePS->Release();

		//���X�^���C�U�쐬
		D3D11_RASTERIZER_DESC rdc = {};
		rdc.CullMode = D3D11_CULL_BACK;
		rdc.FillMode = D3D11_FILL_SOLID;
		rdc.FrontCounterClockwise = TRUE;
		pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_3D].pRasterizerState);

		return S_OK;
	}

	HRESULT InitShader2D()
	{
		// ���_�V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompileVS = NULL;
		D3DCompileFromFile(L"Shader/Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
		pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pVertexShader);


		// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompilePS = NULL;
		D3DCompileFromFile(L"Shader/Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
		pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pPixelShader);


		// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_2D].pVertexLayout);


		//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
		pCompileVS->Release();
		pCompilePS->Release();

		//���X�^���C�U�쐬
		D3D11_RASTERIZER_DESC rdc = {};
		rdc.CullMode = D3D11_CULL_BACK;
		rdc.FillMode = D3D11_FILL_SOLID;
		rdc.FrontCounterClockwise = TRUE;
		pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_2D].pRasterizerState);

		return S_OK;
	}

	HRESULT InitShaderUnlit()
	{
		// ���_�V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompileVS = NULL;
		D3DCompileFromFile(L"Shader/Debug3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
		pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_UNLIT].pVertexShader);


		// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompilePS = NULL;
		D3DCompileFromFile(L"Shader/Debug3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
		pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_UNLIT].pPixelShader);


		// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		pDevice_->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_UNLIT].pVertexLayout);


		//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
		pCompileVS->Release();
		pCompilePS->Release();

		//���X�^���C�U�쐬
		D3D11_RASTERIZER_DESC rdc = {};
		rdc.CullMode = D3D11_CULL_NONE;
		rdc.FillMode = D3D11_FILL_WIREFRAME;
		rdc.FrontCounterClockwise = TRUE;
		pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_UNLIT].pRasterizerState);

		return S_OK;
	}

	HRESULT InitShaderBillBoard()
	{
		//BillBoard

		// ���_�V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompileVS = NULL;
		D3DCompileFromFile(L"Shader/BillBoard.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
		pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_BILLBOARD].pVertexShader);


		// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
		ID3DBlob* pCompilePS = NULL;
		D3DCompileFromFile(L"Shader/BillBoard.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
		pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_BILLBOARD].pPixelShader);


		// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_BILLBOARD].pVertexLayout);


		//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
		pCompileVS->Release();
		pCompilePS->Release();

		//���X�^���C�U�쐬
		D3D11_RASTERIZER_DESC rdc = {};
		rdc.CullMode = D3D11_CULL_NONE;
		rdc.FillMode = D3D11_FILL_SOLID;
		rdc.FrontCounterClockwise = TRUE;
		pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_BILLBOARD].pRasterizerState);

		return S_OK;
	}

	SHADER_TYPE GetShader()
	{
		return shaderType_;
	}

	//������`�悷��ShaderBundle��ݒ�
	void SetShader(SHADER_TYPE type)
	{
		shaderType_ = type;
		pContext_->RSSetState(shaderBundle[type].pRasterizerState);
		pContext_->VSSetShader(shaderBundle[type].pVertexShader, NULL, 0);                         // ���_�V�F�[�_���Z�b�g
		pContext_->PSSetShader(shaderBundle[type].pPixelShader, NULL, 0);                          // �s�N�Z���V�F�[�_���Z�b�g
		pContext_->IASetInputLayout(shaderBundle[type].pVertexLayout);
	}

	//�u�����h���[�h�̕ύX
	void SetBlendMode(BLEND_MODE blendMode)
	{
		//���Z����
		float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
		pContext_->OMSetBlendState(pBlendState[blendMode], blendFactor, 0xffffffff);

		//Z�o�b�t�@�ւ̏�������
		pContext_->OMSetDepthStencilState(pDepthStencilState[blendMode], 0);
	}

	void BeginDrawToTexture()
	{
		pContext_->OMSetRenderTargets(1, &pDepthTargetView, pDepthStencilView);

		//�w�i�̐F
		float clearColor[4] = { 0.8f, 0.8f, 0.95f, 1.0f };

		//��ʂ��N���A
		pContext_->ClearRenderTargetView(pDepthTargetView, clearColor);


		//�[�x�o�b�t�@�N���A
		pContext_->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		SetShader(SHADER_SHADOW);
	}

	//�`��J�n
	void BeginDraw()
	{
		//���������ł��ĂȂ����̂�����������߂�
		if (NULL == pDevice_) return;
		if (NULL == pContext_) return;
		if (NULL == pRenderTargetView_) return;
		if (NULL == pSwapChain_) return;

		//�w�i�̐F
		//float clearColor[4] = { 0.1f, 0.5f, 0.5f, 1.0f };//R,G,B,A
		float clearColor[4] = { 0.8f, 0.8f, 0.95f, 1.0f };

		//��ʂ��N���A
		pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

		//�[�x�o�b�t�@�N���A
		pContext_->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);	
	}


	//�`��I��
	void EndDraw()
	{
		//�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
		pSwapChain_->Present(0, 0);
	}

	//�J������
	void Release()
	{
		SAFE_RELEASE(pDepthStencil);
		SAFE_RELEASE(pDepthStencilView);
		for (int i = 0; i < BLEND_MAX; i++)
		{
			SAFE_RELEASE(pBlendState[i]);
			SAFE_RELEASE(pDepthStencilState[i]);
		}
		SAFE_RELEASE(pRenderTargetView_);
		SAFE_RELEASE(pSwapChain_);

		for (int i = 0; i < SHADER_MAX; i++)
		{
			SAFE_RELEASE(shaderBundle[i].pRasterizerState);
			SAFE_RELEASE(shaderBundle[i].pVertexLayout);
			SAFE_RELEASE(shaderBundle[i].pVertexShader);
			SAFE_RELEASE(shaderBundle[i].pPixelShader);
		}

		if (pContext_)
		{
			pContext_->ClearState();
		}

		SAFE_RELEASE(pRenderTargetView_);
		SAFE_RELEASE(pSwapChain_);
		SAFE_RELEASE(pContext_);
		SAFE_RELEASE(pDevice_);
	}


	//�O�p�`�Ɛ����̏Փ˔���i�Փ˔���Ɏg�p�j
	//https://pheema.hatenablog.jp/entry/ray-triangle-intersection
	bool Intersect(XMFLOAT3 & start, XMFLOAT3 & direction, XMFLOAT3 & v0, XMFLOAT3 & v1, XMFLOAT3 & v2, float* distance)
	{
		// �����Ȓ萔([M?ller97] �ł̒l)
		constexpr float kEpsilon = 1e-6f;

		//�O�p�`�̂Q��
		XMVECTOR edge1 = XMVectorSet(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z, 0.0f);
		XMVECTOR edge2 = XMVectorSet(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z, 0.0f);

		XMVECTOR alpha = XMVector3Cross(XMLoadFloat3(&direction), edge2);
		float det = XMVector3Dot(edge1, alpha).m128_f32[0];

		// �O�p�`�ɑ΂��āA���C�����s�ɓ��˂���悤�ȏꍇ det = 0 �ƂȂ�B
		// det ������������� 1/det ���傫���Ȃ肷���Đ��l�I�ɕs����ɂȂ�̂�
		// det ? 0 �̏ꍇ�͌������Ȃ����ƂƂ���B
		if (-kEpsilon < det && det < kEpsilon) 
		{
			return false;
		}

		float invDet = 1.0f / det;
		XMFLOAT3 r = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);

		// u �� 0 <= u <= 1 �𖞂����Ă��邩�𒲂ׂ�B
		float u = XMVector3Dot(alpha, XMLoadFloat3(&r)).m128_f32[0] * invDet;
		if (u < 0.0f || u > 1.0f)
		{
			return false;
		}

		XMVECTOR beta = XMVector3Cross(XMLoadFloat3(&r), edge1);

		// v �� 0 <= v <= 1 ���� u + v <= 1 �𖞂������Ƃ𒲂ׂ�B
		// ���Ȃ킿�Av �� 0 <= v <= 1 - u ���݂����Ă��邩�𒲂ׂ��OK�B
		float v_ = XMVector3Dot(XMLoadFloat3(&direction), beta).m128_f32[0] * invDet;
		if (v_ < 0.0f || u + v_ > 1.0f) 
		{
			return false;
		}

		// t �� 0 <= t �𖞂������Ƃ𒲂ׂ�B
		float t = XMVector3Dot(edge2, beta).m128_f32[0] * invDet;
		if (t < 0.0f) 
		{
			return false;
		}

		*distance = t;
		return true;
	}

	//Z�o�b�t�@�ւ̏�������ON/OFF
	void SetDepthBafferWriteEnable(bool isWrite)
	{
		//ON
		if (isWrite)
		{
			//Z�o�b�t�@�i�f�v�X�X�e���V�����w�肷��j
			pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView);
		}

		//OFF
		else
		{
			pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);
		}
	}

	//�Q���
	void SetViewPort(SCREEN_SPLIT scr)
	{
		switch (scr)
		{
		case SCREEN_FULL:
			pContext_->RSSetViewports(1, &vp);
			break;
		case SCREEN_RIGHT:
			pContext_->RSSetViewports(1, &vp_right);
			break;
		case SCREEN_LEFT:
			pContext_->RSSetViewports(1, &vp_left);
			break;
		}
	}

	//���݂̃X�N���[���T�C�Y������
	void NowScrSize(int screenWidth, int screenHeight)
	{
		screenWidth_ = screenWidth;
		screenHeight_ = screenHeight;
	}
}