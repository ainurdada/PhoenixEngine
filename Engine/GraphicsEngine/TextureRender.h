#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <string>

class TextureRender
{
public:
    template<class T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    TextureRender() = default;
    ~TextureRender() = default;
    // Do not allow copy, allow mobile
    TextureRender(const TextureRender&) = delete;
    TextureRender& operator=(const TextureRender&) = delete;
    TextureRender(TextureRender&&) = default;
    TextureRender& operator=(TextureRender&&) = default;


    HRESULT InitResource(ID3D11Device* device,
                         int texWidth,
                         int texHeight,
                         bool shadowMap = false,
                         bool generateMips = false);

    // Start rendering the current texture
    // Shadow map No need to provide background color
    void Begin(ID3D11DeviceContext* deviceContext, const FLOAT backgroundColor[4]);
    // End the rendering of the current texture, restore state
    void End(ID3D11DeviceContext* deviceContext);
    // Get a coloring material view of the rendering of good texture
        // The shadow map returns a depth buffer
        // The number of references does not increase, only for transmission
        ID3D11ShaderResourceView * GetOutputTexture();

    // Set the debug object name
    void SetDebugObjectName(const std::string& name);

private:
    ComPtr<ID3D11ShaderResourceView> m_poutputtexturesrv; // Output texture (or shadow map) Corresponding shades resource view
    ComPtr<ID3D11RenderTargetView> m_poutputtexturertv; // Output texture Corresponding to the target view
    ComPtr<ID3D11DepthStencilView> M_POUTPUTTEXTUREDSV; // Outputs Depth / Template View (or Shadow Map)
    D3D11_VIEWPORT m_outputviewport = {}; // The viewport used to output

    ComPtr<ID3D11RenderTargetView> m_pCacheRTV; // temporarily buffered backup buffer
    ComPtr<ID3D11DepthStencilView> m_pCacheDSV; // Temporary Cache Depth / Template Buffer
    D3D11_VIEWPORT M_CacheViewPort = {}; // Temporary Cache Vision

    BOOL M_GENERATEMIPS = false; // Do you generate a MIPMAP chain?
    BOOL M_SHADOWMAP = false; // Is it a shadow map
};

