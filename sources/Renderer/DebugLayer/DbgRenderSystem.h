/*
 * DbgRenderSystem.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __LLGL_DBG_RENDER_SYSTEM_H__
#define __LLGL_DBG_RENDER_SYSTEM_H__


#include <LLGL/RenderSystem.h>
#include "DbgRenderContext.h"

#include "DbgVertexBuffer.h"
#include "DbgIndexBuffer.h"
#include "DbgConstantBuffer.h"
#include "DbgStorageBuffer.h"
#include "DbgGraphicsPipeline.h"
#include "DbgTexture.h"
#include "DbgRenderTarget.h"
#include "DbgShader.h"
#include "DbgShaderProgram.h"
#include "DbgQuery.h"

#include "../ContainerTypes.h"


namespace LLGL
{


class DbgRenderSystem : public RenderSystem
{

    public:

        /* ----- Common ----- */

        DbgRenderSystem(const std::shared_ptr<RenderSystem>& instance, RenderingProfiler* profiler, RenderingDebugger* debugger);
        ~DbgRenderSystem();

        std::map<RendererInfo, std::string> QueryRendererInfo() const override;

        RenderingCaps QueryRenderingCaps() const override;

        ShadingLanguage QueryShadingLanguage() const override;

        void SetConfiguration(const RenderSystemConfiguration& config) override;

        /* ----- Render Context ------ */

        RenderContext* CreateRenderContext(const RenderContextDescriptor& desc, const std::shared_ptr<Window>& window = nullptr) override;

        void Release(RenderContext& renderContext) override;

        /* ----- Hardware Buffers ------ */

        VertexBuffer* CreateVertexBuffer() override;
        IndexBuffer* CreateIndexBuffer() override;
        ConstantBuffer* CreateConstantBuffer() override;
        StorageBuffer* CreateStorageBuffer() override;

        void Release(VertexBuffer& vertexBuffer) override;
        void Release(IndexBuffer& indexBuffer) override;
        void Release(ConstantBuffer& constantBuffer) override;
        void Release(StorageBuffer& storageBuffer) override;

        void SetupVertexBuffer(VertexBuffer& vertexBuffer, const void* data, std::size_t dataSize, const BufferUsage usage, const VertexFormat& vertexFormat) override;
        void SetupIndexBuffer(IndexBuffer& indexBuffer, const void* data, std::size_t dataSize, const BufferUsage usage, const IndexFormat& indexFormat) override;
        void SetupConstantBuffer(ConstantBuffer& constantBuffer, const void* data, std::size_t dataSize, const BufferUsage usage) override;
        void SetupStorageBuffer(StorageBuffer& storageBuffer, const void* data, std::size_t dataSize, const BufferUsage usage) override;

        void WriteVertexBuffer(VertexBuffer& vertexBuffer, const void* data, std::size_t dataSize, std::size_t offset) override;
        void WriteIndexBuffer(IndexBuffer& indexBuffer, const void* data, std::size_t dataSize, std::size_t offset) override;
        void WriteConstantBuffer(ConstantBuffer& constantBuffer, const void* data, std::size_t dataSize, std::size_t offset) override;
        void WriteStorageBuffer(StorageBuffer& storageBuffer, const void* data, std::size_t dataSize, std::size_t offset) override;

        /* ----- Textures ----- */

        Texture* CreateTexture(const TextureDescriptor& textureDesc, const ImageDescriptor* imageDesc = nullptr) override;

        void Release(Texture& texture) override;

        TextureDescriptor QueryTextureDescriptor(const Texture& texture) override;
        
        void WriteTexture(Texture& texture, const SubTextureDescriptor& subTextureDesc, const ImageDescriptor& imageDesc) override;

        void ReadTexture(const Texture& texture, int mipLevel, ImageFormat dataFormat, DataType dataType, void* data) override;

        /* ----- Sampler States ---- */

        Sampler* CreateSampler(const SamplerDescriptor& desc) override;

        void Release(Sampler& sampler) override;

        /* ----- Render Targets ----- */

        RenderTarget* CreateRenderTarget(unsigned int multiSamples = 0) override;

        void Release(RenderTarget& renderTarget) override;

        /* ----- Shader ----- */

        Shader* CreateShader(const ShaderType type) override;
        ShaderProgram* CreateShaderProgram() override;

        void Release(Shader& shader) override;
        void Release(ShaderProgram& shaderProgram) override;

        /* ----- Pipeline States ----- */

        GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineDescriptor& desc) override;
        ComputePipeline* CreateComputePipeline(const ComputePipelineDescriptor& desc) override;
        
        void Release(GraphicsPipeline& graphicsPipeline) override;
        void Release(ComputePipeline& computePipeline) override;

        /* ----- Queries ----- */

        Query* CreateQuery(const QueryDescriptor& desc) override;

        void Release(Query& query) override;

    private:

        void DetermineRenderer(const std::string& rendererName);

        bool OnMakeCurrent(RenderContext* renderContext) override;

        void DebugBufferSize(std::size_t bufferSize, std::size_t dataSize, std::size_t dataOffset, const std::string& source);
        void DebugMipLevelLimit(int mipLevel, int mipLevelCount, const std::string& source);

        void ErrWriteUninitializedResource(const std::string& source);

        void DebugTextureDescriptor(const TextureDescriptor& desc, const std::string& source);
        void DebugTextureSize(int size, const std::string& source);
        void WarnTextureLayersGreaterOne(const std::string& source);
        void ErrTextureLayersEqualZero(const std::string& source);

        template <typename T, typename TBase>
        void ReleaseDbg(std::set<std::unique_ptr<T>>& cont, TBase& entry);

        DbgTexture& GetInitializedTexture(Texture& texture, const std::string& source);

        /* ----- Common objects ----- */

        std::shared_ptr<RenderSystem>           instance_;

        RenderingProfiler*                      profiler_   = nullptr;
        RenderingDebugger*                      debugger_   = nullptr;

        RenderingCaps                           caps_;

        struct Renderer
        {
            bool isOpenGL   = false;
            bool isDirect3D = false;
            bool isVulkan   = false;
        }
        renderer_;

        /* ----- Hardware object containers ----- */

        HWObjectContainer<DbgRenderContext>     renderContexts_;
        
        HWObjectContainer<DbgVertexBuffer>      vertexBuffers_;
        HWObjectContainer<DbgIndexBuffer>       indexBuffers_;
        HWObjectContainer<DbgConstantBuffer>    constantBuffers_;
        HWObjectContainer<DbgStorageBuffer>     storageBuffers_;

        HWObjectContainer<DbgTexture>           textures_;
        HWObjectContainer<DbgRenderTarget>      renderTargets_;

        HWObjectContainer<DbgShader>            shaders_;
        HWObjectContainer<DbgShaderProgram>     shaderPrograms_;

        HWObjectContainer<DbgGraphicsPipeline>  graphicsPipelines_;
        //HWObjectContainer<DbgComputePipeline>   computePipelines_;
        //HWObjectContainer<DbgSampler>           samplers_;
        HWObjectContainer<DbgQuery>             queries_;

};


} // /namespace LLGL


#endif



// ================================================================================
