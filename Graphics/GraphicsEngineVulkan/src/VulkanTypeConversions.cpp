/*     Copyright 2015-2018 Egor Yusov
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF ANY PROPRIETARY RIGHTS.
 *
 *  In no event and under no legal theory, whether in tort (including negligence), 
 *  contract, or otherwise, unless required by applicable law (such as deliberate 
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental, 
 *  or consequential damages of any character arising as a result of this License or 
 *  out of the use or inability to use the software (including but not limited to damages 
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and 
 *  all other commercial damages or losses), even if such Contributor has been advised 
 *  of the possibility of such damages.
 */

#include "pch.h"
#include <unordered_map>
#include <array>

#include "VulkanTypeConversions.h"
#include "VulkanTypeDefinitions.h"

namespace Diligent
{

class TexFormatToVkFormatMapper
{
public:
    TexFormatToVkFormatMapper()
    {
        m_FmtToVkFmtMap[TEX_FORMAT_UNKNOWN] = VK_FORMAT_UNDEFINED;

        m_FmtToVkFmtMap[TEX_FORMAT_RGBA32_TYPELESS] = VK_FORMAT_R32G32B32A32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA32_FLOAT]    = VK_FORMAT_R32G32B32A32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA32_UINT]     = VK_FORMAT_R32G32B32A32_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA32_SINT]     = VK_FORMAT_R32G32B32A32_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_RGB32_TYPELESS] = VK_FORMAT_R32G32B32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGB32_FLOAT]    = VK_FORMAT_R32G32B32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGB32_UINT]     = VK_FORMAT_R32G32B32_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGB32_SINT]     = VK_FORMAT_R32G32B32_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_RGBA16_TYPELESS] = VK_FORMAT_R16G16B16A16_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA16_FLOAT]    = VK_FORMAT_R16G16B16A16_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA16_UNORM]    = VK_FORMAT_R16G16B16A16_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA16_UINT]     = VK_FORMAT_R16G16B16A16_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA16_SNORM]    = VK_FORMAT_R16G16B16A16_SNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA16_SINT]     = VK_FORMAT_R16G16B16A16_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_RG32_TYPELESS] = VK_FORMAT_R32G32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RG32_FLOAT]    = VK_FORMAT_R32G32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RG32_UINT]     = VK_FORMAT_R32G32_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_RG32_SINT]     = VK_FORMAT_R32G32_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_R32G8X24_TYPELESS]        = VK_FORMAT_D32_SFLOAT_S8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_D32_FLOAT_S8X24_UINT]     = VK_FORMAT_D32_SFLOAT_S8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_R32_FLOAT_X8X24_TYPELESS] = VK_FORMAT_D32_SFLOAT_S8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_X32_TYPELESS_G8X24_UINT]  = VK_FORMAT_UNDEFINED;

        m_FmtToVkFmtMap[TEX_FORMAT_RGB10A2_TYPELESS] = VK_FORMAT_A2R10G10B10_UNORM_PACK32;
        m_FmtToVkFmtMap[TEX_FORMAT_RGB10A2_UNORM]    = VK_FORMAT_A2R10G10B10_UNORM_PACK32;
        m_FmtToVkFmtMap[TEX_FORMAT_RGB10A2_UINT]     = VK_FORMAT_A2R10G10B10_UINT_PACK32;
        m_FmtToVkFmtMap[TEX_FORMAT_R11G11B10_FLOAT]  = VK_FORMAT_B10G11R11_UFLOAT_PACK32;

        m_FmtToVkFmtMap[TEX_FORMAT_RGBA8_TYPELESS]   = VK_FORMAT_R8G8B8A8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA8_UNORM]      = VK_FORMAT_R8G8B8A8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA8_UNORM_SRGB] = VK_FORMAT_R8G8B8A8_SRGB;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA8_UINT]       = VK_FORMAT_R8G8B8A8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA8_SNORM]      = VK_FORMAT_R8G8B8A8_SNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RGBA8_SINT]       = VK_FORMAT_R8G8B8A8_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_RG16_TYPELESS] = VK_FORMAT_R16G16_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RG16_FLOAT]    = VK_FORMAT_R16G16_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_RG16_UNORM]    = VK_FORMAT_R16G16_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RG16_UINT]     = VK_FORMAT_R16G16_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_RG16_SNORM]    = VK_FORMAT_R16G16_SNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RG16_SINT]     = VK_FORMAT_R16G16_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_R32_TYPELESS] = VK_FORMAT_R32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_D32_FLOAT]    = VK_FORMAT_D32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_R32_FLOAT]    = VK_FORMAT_R32_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_R32_UINT]     = VK_FORMAT_R32_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_R32_SINT]     = VK_FORMAT_R32_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_R24G8_TYPELESS]        = VK_FORMAT_D24_UNORM_S8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_D24_UNORM_S8_UINT]     = VK_FORMAT_D24_UNORM_S8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_R24_UNORM_X8_TYPELESS] = VK_FORMAT_D24_UNORM_S8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_X24_TYPELESS_G8_UINT]  = VK_FORMAT_UNDEFINED;

        m_FmtToVkFmtMap[TEX_FORMAT_RG8_TYPELESS] = VK_FORMAT_R8G8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RG8_UNORM]    = VK_FORMAT_R8G8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RG8_UINT]     = VK_FORMAT_R8G8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_RG8_SNORM]    = VK_FORMAT_R8G8_SNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_RG8_SINT]     = VK_FORMAT_R8G8_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_R16_TYPELESS] = VK_FORMAT_R16_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_R16_FLOAT]    = VK_FORMAT_R16_SFLOAT;
        m_FmtToVkFmtMap[TEX_FORMAT_D16_UNORM]    = VK_FORMAT_D16_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_R16_UNORM]    = VK_FORMAT_R16_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_R16_UINT]     = VK_FORMAT_R16_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_R16_SNORM]    = VK_FORMAT_R16_SNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_R16_SINT]     = VK_FORMAT_R16_SINT;

        m_FmtToVkFmtMap[TEX_FORMAT_R8_TYPELESS] = VK_FORMAT_R8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_R8_UNORM]    = VK_FORMAT_R8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_R8_UINT]     = VK_FORMAT_R8_UINT;
        m_FmtToVkFmtMap[TEX_FORMAT_R8_SNORM]    = VK_FORMAT_R8_SNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_R8_SINT]     = VK_FORMAT_R8_SINT;
        m_FmtToVkFmtMap[TEX_FORMAT_A8_UNORM]    = VK_FORMAT_UNDEFINED;

        m_FmtToVkFmtMap[TEX_FORMAT_R1_UNORM]    = VK_FORMAT_UNDEFINED;

        m_FmtToVkFmtMap[TEX_FORMAT_RGB9E5_SHAREDEXP] = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;
        m_FmtToVkFmtMap[TEX_FORMAT_RG8_B8G8_UNORM]   = VK_FORMAT_UNDEFINED;
        m_FmtToVkFmtMap[TEX_FORMAT_G8R8_G8B8_UNORM]  = VK_FORMAT_UNDEFINED;

        // http://www.g-truc.net/post-0335.html
        // http://renderingpipeline.com/2012/07/texture-compression/
        m_FmtToVkFmtMap[TEX_FORMAT_BC1_TYPELESS]   = VK_FORMAT_BC1_RGB_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC1_UNORM]      = VK_FORMAT_BC1_RGB_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC1_UNORM_SRGB] = VK_FORMAT_BC1_RGB_SRGB_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC2_TYPELESS]   = VK_FORMAT_BC2_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC2_UNORM]      = VK_FORMAT_BC2_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC2_UNORM_SRGB] = VK_FORMAT_BC2_SRGB_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC3_TYPELESS]   = VK_FORMAT_BC3_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC3_UNORM]      = VK_FORMAT_BC3_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC3_UNORM_SRGB] = VK_FORMAT_BC3_SRGB_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC4_TYPELESS]   = VK_FORMAT_BC4_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC4_UNORM]      = VK_FORMAT_BC4_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC4_SNORM]      = VK_FORMAT_BC4_SNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC5_TYPELESS]   = VK_FORMAT_BC5_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC5_UNORM]      = VK_FORMAT_BC5_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC5_SNORM]      = VK_FORMAT_BC5_SNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_B5G6R5_UNORM]   = VK_FORMAT_B5G6R5_UNORM_PACK16;
        m_FmtToVkFmtMap[TEX_FORMAT_B5G5R5A1_UNORM] = VK_FORMAT_B5G5R5A1_UNORM_PACK16;
        m_FmtToVkFmtMap[TEX_FORMAT_BGRA8_UNORM]    = VK_FORMAT_B8G8R8A8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_BGRX8_UNORM]    = VK_FORMAT_B8G8R8A8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_R10G10B10_XR_BIAS_A2_UNORM] = VK_FORMAT_UNDEFINED;
        m_FmtToVkFmtMap[TEX_FORMAT_BGRA8_TYPELESS]   = VK_FORMAT_B8G8R8A8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_BGRA8_UNORM_SRGB] = VK_FORMAT_B8G8R8A8_SRGB;
        m_FmtToVkFmtMap[TEX_FORMAT_BGRX8_TYPELESS]   = VK_FORMAT_B8G8R8A8_UNORM;
        m_FmtToVkFmtMap[TEX_FORMAT_BGRX8_UNORM_SRGB] = VK_FORMAT_B8G8R8A8_SRGB;
        m_FmtToVkFmtMap[TEX_FORMAT_BC6H_TYPELESS] = VK_FORMAT_BC6H_UFLOAT_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC6H_UF16]     = VK_FORMAT_BC6H_UFLOAT_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC6H_SF16]     = VK_FORMAT_BC6H_SFLOAT_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC7_TYPELESS]   = VK_FORMAT_BC7_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC7_UNORM]      = VK_FORMAT_BC7_UNORM_BLOCK;
        m_FmtToVkFmtMap[TEX_FORMAT_BC7_UNORM_SRGB] = VK_FORMAT_BC7_SRGB_BLOCK;
    }

    VkFormat operator[](TEXTURE_FORMAT TexFmt)const
    {
        VERIFY_EXPR(TexFmt < _countof(m_FmtToVkFmtMap));
        return m_FmtToVkFmtMap[TexFmt];
    }

private:
    VkFormat m_FmtToVkFmtMap[TEX_FORMAT_NUM_FORMATS] = {};
};

VkFormat TexFormatToVkFormat(TEXTURE_FORMAT TexFmt)
{
    static const TexFormatToVkFormatMapper FmtMapper;
    return FmtMapper[TexFmt];
}



class VkFormatToTexFormatMapper
{
public:
    VkFormatToTexFormatMapper()
    {
        m_VkFmtToTexFmtMap[VK_FORMAT_UNDEFINED]                 = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R4G4_UNORM_PACK8]          = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R4G4B4A4_UNORM_PACK16]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B4G4R4A4_UNORM_PACK16]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R5G6B5_UNORM_PACK16]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B5G6R5_UNORM_PACK16]       = TEX_FORMAT_B5G6R5_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R5G5B5A1_UNORM_PACK16]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B5G5R5A1_UNORM_PACK16]     = TEX_FORMAT_B5G5R5A1_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_A1R5G5B5_UNORM_PACK16]     = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R8_UNORM]                  = TEX_FORMAT_R8_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8_SNORM]                  = TEX_FORMAT_R8_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8_USCALED]                = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8_SSCALED]                = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8_UINT]                   = TEX_FORMAT_R8_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8_SINT]                   = TEX_FORMAT_R8_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8_SRGB]                   = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8_UNORM]                = TEX_FORMAT_RG8_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8_SNORM]                = TEX_FORMAT_RG8_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8_USCALED]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8_SSCALED]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8_UINT]                 = TEX_FORMAT_RG8_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8_SINT]                 = TEX_FORMAT_RG8_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8_SRGB]                 = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8_UNORM]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8_SNORM]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8_USCALED]            = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8_SSCALED]            = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8_UINT]               = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8_SINT]               = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8_SRGB]               = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8_UNORM]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8_SNORM]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8_USCALED]            = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8_SSCALED]            = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8_UINT]               = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8_SINT]               = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8_SRGB]               = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8A8_UNORM]            = TEX_FORMAT_RGBA8_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8A8_SNORM]            = TEX_FORMAT_RGBA8_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8A8_USCALED]          = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8A8_SSCALED]          = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8A8_UINT]             = TEX_FORMAT_RGBA8_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8A8_SINT]             = TEX_FORMAT_RGBA8_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R8G8B8A8_SRGB]             = TEX_FORMAT_RGBA8_UNORM_SRGB;

        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8A8_UNORM]            = TEX_FORMAT_BGRA8_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8A8_SNORM]            = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8A8_USCALED]          = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8A8_SSCALED]          = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8A8_UINT]             = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8A8_SINT]             = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_B8G8R8A8_SRGB]             = TEX_FORMAT_BGRA8_UNORM_SRGB;

        m_VkFmtToTexFmtMap[VK_FORMAT_A8B8G8R8_UNORM_PACK32]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A8B8G8R8_SNORM_PACK32]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A8B8G8R8_USCALED_PACK32]   = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A8B8G8R8_SSCALED_PACK32]   = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A8B8G8R8_UINT_PACK32]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A8B8G8R8_SINT_PACK32]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A8B8G8R8_SRGB_PACK32]      = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_A2R10G10B10_UNORM_PACK32]  = TEX_FORMAT_RGB10A2_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2R10G10B10_SNORM_PACK32]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2R10G10B10_USCALED_PACK32]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2R10G10B10_SSCALED_PACK32]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2R10G10B10_UINT_PACK32]       = TEX_FORMAT_RGB10A2_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2R10G10B10_SINT_PACK32]       = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_A2B10G10R10_UNORM_PACK32]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2B10G10R10_SNORM_PACK32]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2B10G10R10_USCALED_PACK32]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2B10G10R10_SSCALED_PACK32]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2B10G10R10_UINT_PACK32]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_A2B10G10R10_SINT_PACK32]       = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R16_UNORM]             = TEX_FORMAT_R16_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16_SNORM]             = TEX_FORMAT_R16_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16_USCALED]           = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16_SSCALED]           = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16_UINT]              = TEX_FORMAT_R16_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16_SINT]              = TEX_FORMAT_R16_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16_SFLOAT]            = TEX_FORMAT_R16_FLOAT;

        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16_UNORM]          = TEX_FORMAT_RG16_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16_SNORM]          = TEX_FORMAT_RG16_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16_USCALED]        = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16_SSCALED]        = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16_UINT]           = TEX_FORMAT_RG16_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16_SINT]           = TEX_FORMAT_RG16_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16_SFLOAT]         = TEX_FORMAT_RG16_FLOAT;

        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16_UNORM]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16_SNORM]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16_USCALED]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16_SSCALED]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16_UINT]        = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16_SINT]        = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16_SFLOAT]      = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16A16_UNORM]    = TEX_FORMAT_RGBA16_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16A16_SNORM]    = TEX_FORMAT_RGBA16_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16A16_USCALED]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16A16_SSCALED]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16A16_UINT]     = TEX_FORMAT_RGBA16_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16A16_SINT]     = TEX_FORMAT_RGBA16_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R16G16B16A16_SFLOAT]   = TEX_FORMAT_RGBA16_FLOAT;

        m_VkFmtToTexFmtMap[VK_FORMAT_R32_UINT]              = TEX_FORMAT_R32_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32_SINT]              = TEX_FORMAT_R32_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32_SFLOAT]            = TEX_FORMAT_R32_FLOAT;

        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32_UINT]           = TEX_FORMAT_RG32_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32_SINT]           = TEX_FORMAT_RG32_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32_SFLOAT]         = TEX_FORMAT_RG32_FLOAT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32B32_UINT]        = TEX_FORMAT_RGB32_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32B32_SINT]        = TEX_FORMAT_RGB32_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32B32_SFLOAT]      = TEX_FORMAT_RGB32_FLOAT;

        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32B32A32_UINT]     = TEX_FORMAT_RGBA32_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32B32A32_SINT]     = TEX_FORMAT_RGBA32_SINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_R32G32B32A32_SFLOAT]   = TEX_FORMAT_RGBA32_FLOAT;

        m_VkFmtToTexFmtMap[VK_FORMAT_R64_UINT]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64_SINT]              = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64_SFLOAT]            = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64_UINT]           = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64_SINT]           = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64_SFLOAT]         = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64B64_UINT]        = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64B64_SINT]        = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64B64_SFLOAT]      = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64B64A64_UINT]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64B64A64_SINT]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_R64G64B64A64_SFLOAT]   = TEX_FORMAT_UNKNOWN;

        m_VkFmtToTexFmtMap[VK_FORMAT_B10G11R11_UFLOAT_PACK32]   = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_E5B9G9R9_UFLOAT_PACK32]    = TEX_FORMAT_RGB9E5_SHAREDEXP;
        m_VkFmtToTexFmtMap[VK_FORMAT_D16_UNORM]                 = TEX_FORMAT_D16_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_X8_D24_UNORM_PACK32]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_D32_SFLOAT]                = TEX_FORMAT_D32_FLOAT;
        m_VkFmtToTexFmtMap[VK_FORMAT_S8_UINT]                   = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_D16_UNORM_S8_UINT]         = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_D24_UNORM_S8_UINT]         = TEX_FORMAT_D24_UNORM_S8_UINT;
        m_VkFmtToTexFmtMap[VK_FORMAT_D32_SFLOAT_S8_UINT]        = TEX_FORMAT_D32_FLOAT_S8X24_UINT;

        m_VkFmtToTexFmtMap[VK_FORMAT_BC1_RGB_UNORM_BLOCK]       = TEX_FORMAT_BC1_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC1_RGB_SRGB_BLOCK]        = TEX_FORMAT_BC1_UNORM_SRGB;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC1_RGBA_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC1_RGBA_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC2_UNORM_BLOCK]           = TEX_FORMAT_BC2_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC2_SRGB_BLOCK]            = TEX_FORMAT_BC2_UNORM_SRGB;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC3_UNORM_BLOCK]           = TEX_FORMAT_BC3_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC3_SRGB_BLOCK]            = TEX_FORMAT_BC3_UNORM_SRGB;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC4_UNORM_BLOCK]           = TEX_FORMAT_BC4_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC4_SNORM_BLOCK]           = TEX_FORMAT_BC4_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC5_UNORM_BLOCK]           = TEX_FORMAT_BC5_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC5_SNORM_BLOCK]           = TEX_FORMAT_BC5_SNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC6H_UFLOAT_BLOCK]         = TEX_FORMAT_BC6H_UF16;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC6H_SFLOAT_BLOCK]         = TEX_FORMAT_BC6H_SF16;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC7_UNORM_BLOCK]           = TEX_FORMAT_BC7_UNORM;
        m_VkFmtToTexFmtMap[VK_FORMAT_BC7_SRGB_BLOCK]            = TEX_FORMAT_BC7_UNORM_SRGB;

        m_VkFmtToTexFmtMap[VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK]   = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_EAC_R11_UNORM_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_EAC_R11_SNORM_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_EAC_R11G11_UNORM_BLOCK]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_EAC_R11G11_SNORM_BLOCK]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_4x4_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_4x4_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_5x4_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_5x4_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_5x5_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_5x5_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_6x5_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_6x5_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_6x6_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_6x6_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_8x5_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_8x5_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_8x6_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_8x6_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_8x8_UNORM_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_8x8_SRGB_BLOCK]       = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x5_UNORM_BLOCK]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x5_SRGB_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x6_UNORM_BLOCK]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x6_SRGB_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x8_UNORM_BLOCK]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x8_SRGB_BLOCK]      = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x10_UNORM_BLOCK]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_10x10_SRGB_BLOCK]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_12x10_UNORM_BLOCK]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_12x10_SRGB_BLOCK]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_12x12_UNORM_BLOCK]    = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMap[VK_FORMAT_ASTC_12x12_SRGB_BLOCK]     = TEX_FORMAT_UNKNOWN;



        m_VkFmtToTexFmtMapExt[VK_FORMAT_G8B8G8R8_422_UNORM] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_B8G8R8G8_422_UNORM] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G8_B8R8_2PLANE_420_UNORM]   = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G8_B8R8_2PLANE_422_UNORM]   = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_R10X6_UNORM_PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_R10X6G10X6_UNORM_2PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16]     = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_R12X4_UNORM_PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_R12X4G12X4_UNORM_2PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G16B16G16R16_422_UNORM] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_B16G16R16G16_422_UNORM] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G16_B16R16_2PLANE_420_UNORM]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G16_B16R16_2PLANE_422_UNORM]  = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
        m_VkFmtToTexFmtMapExt[VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG] = TEX_FORMAT_UNKNOWN;
    }

    TEXTURE_FORMAT operator[](VkFormat VkFmt)const
    {
        if(VkFmt < VK_FORMAT_RANGE_SIZE)
        {
            return m_VkFmtToTexFmtMap[VkFmt];
        }
        else
        {
            auto it = m_VkFmtToTexFmtMapExt.find(VkFmt);
            return it != m_VkFmtToTexFmtMapExt.end() ? it->second : TEX_FORMAT_UNKNOWN;
        }
    }

private:
    TEXTURE_FORMAT m_VkFmtToTexFmtMap[VK_FORMAT_RANGE_SIZE] = {};
    std::unordered_map<VkFormat, TEXTURE_FORMAT> m_VkFmtToTexFmtMapExt;
};

TEXTURE_FORMAT VkFormatToTexFormat(VkFormat VkFmt)
{
    static const VkFormatToTexFormatMapper FmtMapper;
    return FmtMapper[VkFmt];
}



VkFormat TypeToVkFormat(VALUE_TYPE ValType, Uint32 NumComponents, Bool bIsNormalized)
{
    switch (ValType)
    {
    case VT_FLOAT16:
    {
        VERIFY(!bIsNormalized, "Floating point formats cannot be normalized");
        switch (NumComponents)
        {
        case 1: return VK_FORMAT_R16_SFLOAT;
        case 2: return VK_FORMAT_R16G16_SFLOAT;
        case 4: return VK_FORMAT_R16G16B16A16_SFLOAT;
        default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
        }
    }

    case VT_FLOAT32:
    {
        VERIFY(!bIsNormalized, "Floating point formats cannot be normalized");
        switch (NumComponents)
        {
        case 1: return VK_FORMAT_R32_SFLOAT;
        case 2: return VK_FORMAT_R32G32_SFLOAT;
        case 3: return VK_FORMAT_R32G32B32_SFLOAT;
        case 4: return VK_FORMAT_R32G32B32A32_SFLOAT;
        default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
        }
    }

    case VT_INT32:
    {
        VERIFY(!bIsNormalized, "32-bit UNORM formats are not supported. Use R32_FLOAT instead");
        switch (NumComponents)
        {
        case 1: return VK_FORMAT_R32_SINT;
        case 2: return VK_FORMAT_R32G32_SINT;
        case 3: return VK_FORMAT_R32G32B32_SINT;
        case 4: return VK_FORMAT_R32G32B32A32_SINT;
        default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
        }
    }

    case VT_UINT32:
    {
        VERIFY(!bIsNormalized, "32-bit UNORM formats are not supported. Use R32_FLOAT instead");
        switch (NumComponents)
        {
        case 1: return VK_FORMAT_R32_UINT;
        case 2: return VK_FORMAT_R32G32_UINT;
        case 3: return VK_FORMAT_R32G32B32_UINT;
        case 4: return VK_FORMAT_R32G32B32A32_UINT;
        default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
        }
    }

    case VT_INT16:
    {
        if (bIsNormalized)
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R16_SNORM;
            case 2: return VK_FORMAT_R16G16_SNORM;
            case 4: return VK_FORMAT_R16G16B16A16_SNORM;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
        else
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R16_SINT;
            case 2: return VK_FORMAT_R16G16_SINT;
            case 4: return VK_FORMAT_R16G16B16A16_SINT;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
    }

    case VT_UINT16:
    {
        if (bIsNormalized)
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R16_UNORM;
            case 2: return VK_FORMAT_R16G16_UNORM;
            case 4: return VK_FORMAT_R16G16B16A16_UNORM;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
        else
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R16_UINT;
            case 2: return VK_FORMAT_R16G16_UINT;
            case 4: return VK_FORMAT_R16G16B16A16_UINT;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
    }

    case VT_INT8:
    {
        if (bIsNormalized)
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R8_SNORM;
            case 2: return VK_FORMAT_R8G8_SNORM;
            case 4: return VK_FORMAT_R8G8B8A8_SNORM;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
        else
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R8_SINT;
            case 2: return VK_FORMAT_R8G8_SINT;
            case 4: return VK_FORMAT_R8G8B8A8_SINT;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
    }

    case VT_UINT8:
    {
        if (bIsNormalized)
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R8_UNORM;
            case 2: return VK_FORMAT_R8G8_UNORM;
            case 4: return VK_FORMAT_R8G8B8A8_UNORM;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
        else
        {
            switch (NumComponents)
            {
            case 1: return VK_FORMAT_R8_UINT;
            case 2: return VK_FORMAT_R8G8_UINT;
            case 4: return VK_FORMAT_R8G8B8A8_UINT;
            default: UNEXPECTED("Unusupported number of components"); return VK_FORMAT_UNDEFINED;
            }
        }
    }

    default: UNEXPECTED("Unusupported format"); return VK_FORMAT_UNDEFINED;
    }
}

VkPolygonMode FillModeToVkPolygonMode(FILL_MODE FillMode)
{
    switch(FillMode)
    {
        case FILL_MODE_UNDEFINED: 
            UNEXPECTED("Undefined fill mode"); 
            return VK_POLYGON_MODE_FILL;

        case FILL_MODE_SOLID:     return VK_POLYGON_MODE_FILL;
        case FILL_MODE_WIREFRAME: return VK_POLYGON_MODE_LINE;

        default:
            UNEXPECTED("Unexpected fill mode");
            return VK_POLYGON_MODE_FILL;
    }
}

VkCullModeFlagBits CullModeToVkCullMode(CULL_MODE CullMode)
{
    switch(CullMode)
    {
        case CULL_MODE_UNDEFINED:
            UNEXPECTED("Undefined cull mode");
            return VK_CULL_MODE_NONE;

        case CULL_MODE_NONE:  return VK_CULL_MODE_NONE;
        case CULL_MODE_FRONT: return VK_CULL_MODE_FRONT_BIT;
        case CULL_MODE_BACK:  return VK_CULL_MODE_BACK_BIT;

        default:
            UNEXPECTED("Unexpected cull mode");
            return VK_CULL_MODE_NONE;
    }
}

VkPipelineRasterizationStateCreateInfo RasterizerStateDesc_To_VkRasterizationStateCI(const RasterizerStateDesc &RasterizerDesc)
{
    VkPipelineRasterizationStateCreateInfo RSStateCI = {};
    RSStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    RSStateCI.pNext = nullptr;
    RSStateCI.flags = 0; // Reserved for future use.
    RSStateCI.depthClampEnable = RasterizerDesc.DepthClipEnable ? VK_FALSE : VK_TRUE; // whether to clamp the fragment�s depth 
                                                // values instead of clipping primitives to the z planes of the frustum.
                                                // This value is the opposite of clip enable
    RSStateCI.rasterizerDiscardEnable = VK_FALSE; // Whether primitives are discarded immediately before the rasterization stage.
    RSStateCI.polygonMode = FillModeToVkPolygonMode(RasterizerDesc.FillMode);
    RSStateCI.cullMode = CullModeToVkCullMode(RasterizerDesc.CullMode);
    RSStateCI.frontFace = RasterizerDesc.FrontCounterClockwise ? VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE;
    RSStateCI.depthBiasEnable = (RasterizerDesc.DepthBias != 0 || RasterizerDesc.SlopeScaledDepthBias != 0.f) ? VK_TRUE : VK_FALSE;
    RSStateCI.depthBiasConstantFactor = static_cast<float>(RasterizerDesc.DepthBias); // a scalar factor controlling the constant depth value added to each fragment.
    RSStateCI.depthBiasClamp = RasterizerDesc.DepthBiasClamp; // maximum (or minimum) depth bias of a fragment.
    RSStateCI.depthBiasSlopeFactor = RasterizerDesc.SlopeScaledDepthBias; //  a scalar factor applied to a fragment�s slope in depth bias calculations.
    RSStateCI.lineWidth = 1.f;

    return RSStateCI;
}

VkCompareOp ComparisonFuncToVkCompareOp(COMPARISON_FUNCTION CmpFunc)
{
    switch(CmpFunc)
    {
        case COMPARISON_FUNC_UNKNOWN: 
            UNEXPECTED("Comparison function is not specified" ); 
            return VK_COMPARE_OP_ALWAYS;

        case COMPARISON_FUNC_NEVER:         return VK_COMPARE_OP_NEVER;
        case COMPARISON_FUNC_LESS:          return VK_COMPARE_OP_LESS;
        case COMPARISON_FUNC_EQUAL:         return VK_COMPARE_OP_EQUAL;
        case COMPARISON_FUNC_LESS_EQUAL:    return VK_COMPARE_OP_LESS_OR_EQUAL;
        case COMPARISON_FUNC_GREATER:       return VK_COMPARE_OP_GREATER;
        case COMPARISON_FUNC_NOT_EQUAL:     return VK_COMPARE_OP_NOT_EQUAL;
        case COMPARISON_FUNC_GREATER_EQUAL: return VK_COMPARE_OP_GREATER_OR_EQUAL;
        case COMPARISON_FUNC_ALWAYS:        return VK_COMPARE_OP_ALWAYS;

        default: 
            UNEXPECTED("Unknown comparison function" ); 
            return VK_COMPARE_OP_ALWAYS;
    }
}

VkStencilOp StencilOpToVkStencilOp(STENCIL_OP StencilOp)
{
    switch(StencilOp)
    {
        case STENCIL_OP_UNDEFINED:
            UNEXPECTED("Undefined stencil operation");
            return VK_STENCIL_OP_KEEP;

        case STENCIL_OP_KEEP:       return VK_STENCIL_OP_KEEP;
        case STENCIL_OP_ZERO:       return VK_STENCIL_OP_ZERO;
        case STENCIL_OP_REPLACE:    return VK_STENCIL_OP_REPLACE;
        case STENCIL_OP_INCR_SAT:   return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
        case STENCIL_OP_DECR_SAT:   return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
        case STENCIL_OP_INVERT:     return VK_STENCIL_OP_INVERT;
        case STENCIL_OP_INCR_WRAP:  return VK_STENCIL_OP_INCREMENT_AND_WRAP;
        case STENCIL_OP_DECR_WRAP:  return VK_STENCIL_OP_DECREMENT_AND_WRAP;

        default:
            UNEXPECTED("Unknown stencil operation");
            return VK_STENCIL_OP_KEEP;
    }
}

VkStencilOpState StencilOpDescToVkStencilOpState(const StencilOpDesc& desc, Uint8 StencilReadMask, Uint8 StencilWriteMask)
{
    VkStencilOpState StencilState = {};
    StencilState.failOp = StencilOpToVkStencilOp(desc.StencilFailOp);
    StencilState.passOp = StencilOpToVkStencilOp(desc.StencilPassOp);
    StencilState.depthFailOp = StencilOpToVkStencilOp(desc.StencilDepthFailOp);
    StencilState.compareOp = ComparisonFuncToVkCompareOp(desc.StencilFunc);
    StencilState.compareMask = StencilReadMask;
    StencilState.writeMask = StencilWriteMask;
    StencilState.reference = 0;

    return StencilState;
}


VkPipelineDepthStencilStateCreateInfo  DepthStencilStateDesc_To_VkDepthStencilStateCI(const DepthStencilStateDesc &DepthStencilDesc)
{
    VkPipelineDepthStencilStateCreateInfo DSStateCI = {};
    DSStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    DSStateCI.pNext = nullptr;
    DSStateCI.flags = 0; // reserved for future use
    DSStateCI.depthTestEnable = DepthStencilDesc.DepthEnable ? VK_TRUE : VK_FALSE;
    DSStateCI.depthWriteEnable = DepthStencilDesc.DepthWriteEnable ? VK_TRUE : VK_FALSE;
    DSStateCI.depthCompareOp = ComparisonFuncToVkCompareOp(DepthStencilDesc.DepthFunc);
    DSStateCI.depthBoundsTestEnable = VK_FALSE;
    DSStateCI.stencilTestEnable = DepthStencilDesc.StencilEnable;
    DSStateCI.front = StencilOpDescToVkStencilOpState(DepthStencilDesc.FrontFace, DepthStencilDesc.StencilReadMask, DepthStencilDesc.StencilWriteMask);
    DSStateCI.back = StencilOpDescToVkStencilOpState(DepthStencilDesc.BackFace, DepthStencilDesc.StencilReadMask, DepthStencilDesc.StencilWriteMask);
    DSStateCI.minDepthBounds = -FLT_MAX;
    DSStateCI.maxDepthBounds = +FLT_MAX;

    return DSStateCI;
}

class BlendFactorToVkBlendFactorMapper
{
public:
    BlendFactorToVkBlendFactorMapper()
    {
        m_Map[BLEND_FACTOR_ZERO]            = VK_BLEND_FACTOR_ZERO;
        m_Map[BLEND_FACTOR_ONE]             = VK_BLEND_FACTOR_ONE;
        m_Map[BLEND_FACTOR_SRC_COLOR]       = VK_BLEND_FACTOR_SRC_COLOR;
        m_Map[BLEND_FACTOR_INV_SRC_COLOR]   = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
        m_Map[BLEND_FACTOR_SRC_ALPHA]       = VK_BLEND_FACTOR_SRC_ALPHA;
        m_Map[BLEND_FACTOR_INV_SRC_ALPHA]   = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        m_Map[BLEND_FACTOR_DEST_ALPHA]      = VK_BLEND_FACTOR_DST_ALPHA;
        m_Map[BLEND_FACTOR_INV_DEST_ALPHA]  = VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
        m_Map[BLEND_FACTOR_DEST_COLOR]      = VK_BLEND_FACTOR_DST_COLOR;
        m_Map[BLEND_FACTOR_INV_DEST_COLOR]  = VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
        m_Map[BLEND_FACTOR_SRC_ALPHA_SAT]   = VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
        m_Map[BLEND_FACTOR_BLEND_FACTOR]    = VK_BLEND_FACTOR_CONSTANT_COLOR;
        m_Map[BLEND_FACTOR_INV_BLEND_FACTOR] = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
        m_Map[BLEND_FACTOR_SRC1_COLOR]      = VK_BLEND_FACTOR_SRC1_COLOR;
        m_Map[BLEND_FACTOR_INV_SRC1_COLOR]  = VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
        m_Map[BLEND_FACTOR_SRC1_ALPHA]      = VK_BLEND_FACTOR_SRC1_ALPHA;
        m_Map[BLEND_FACTOR_INV_SRC1_ALPHA]  = VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
    }
    
    VkBlendFactor operator[](BLEND_FACTOR bf)const
    {
        VERIFY_EXPR(bf > BLEND_FACTOR_UNDEFINED && bf < BLEND_FACTOR_NUM_FACTORS);
        return m_Map[static_cast<int>(bf)];
    }

private:
    std::array<VkBlendFactor, BLEND_FACTOR_NUM_FACTORS> m_Map = {};
};


class LogicOperationToVkLogicOp
{
public:
    LogicOperationToVkLogicOp()
    {
        m_Map[ LOGIC_OP_CLEAR		   ]  = VK_LOGIC_OP_CLEAR;
        m_Map[ LOGIC_OP_SET			   ]  = VK_LOGIC_OP_SET;
        m_Map[ LOGIC_OP_COPY		   ]  = VK_LOGIC_OP_COPY;
        m_Map[ LOGIC_OP_COPY_INVERTED  ]  = VK_LOGIC_OP_COPY_INVERTED;
        m_Map[ LOGIC_OP_NOOP		   ]  = VK_LOGIC_OP_NO_OP;
        m_Map[ LOGIC_OP_INVERT		   ]  = VK_LOGIC_OP_INVERT;
        m_Map[ LOGIC_OP_AND			   ]  = VK_LOGIC_OP_AND;
        m_Map[ LOGIC_OP_NAND		   ]  = VK_LOGIC_OP_NAND;
        m_Map[ LOGIC_OP_OR			   ]  = VK_LOGIC_OP_OR;
        m_Map[ LOGIC_OP_NOR			   ]  = VK_LOGIC_OP_NOR;
        m_Map[ LOGIC_OP_XOR			   ]  = VK_LOGIC_OP_XOR;
        m_Map[ LOGIC_OP_EQUIV		   ]  = VK_LOGIC_OP_EQUIVALENT;
        m_Map[ LOGIC_OP_AND_REVERSE	   ]  = VK_LOGIC_OP_AND_REVERSE;
        m_Map[ LOGIC_OP_AND_INVERTED   ]  = VK_LOGIC_OP_AND_INVERTED;
        m_Map[ LOGIC_OP_OR_REVERSE	   ]  = VK_LOGIC_OP_OR_REVERSE;
        m_Map[ LOGIC_OP_OR_INVERTED	   ]  = VK_LOGIC_OP_OR_INVERTED;
    }

    VkLogicOp operator[](LOGIC_OPERATION op)const
    {
        VERIFY_EXPR(op >= LOGIC_OP_CLEAR && op < LOGIC_OP_NUM_OPERATIONS);
        return m_Map[static_cast<int>(op)];
    }

private:
    std::array<VkLogicOp, LOGIC_OP_NUM_OPERATIONS> m_Map = {};
};

class BlendOperationToVkBlendOp
{
public:
    BlendOperationToVkBlendOp()
    {
        m_Map[ BLEND_OPERATION_ADD          ] = VK_BLEND_OP_ADD;
        m_Map[ BLEND_OPERATION_SUBTRACT     ] = VK_BLEND_OP_SUBTRACT;
        m_Map[ BLEND_OPERATION_REV_SUBTRACT ] = VK_BLEND_OP_REVERSE_SUBTRACT;
        m_Map[ BLEND_OPERATION_MIN          ] = VK_BLEND_OP_MIN;
        m_Map[ BLEND_OPERATION_MAX          ] = VK_BLEND_OP_MAX;
    }

    VkBlendOp operator[](BLEND_OPERATION op)const
    {
        VERIFY_EXPR(op > BLEND_OPERATION_UNDEFINED && op < BLEND_OPERATION_NUM_OPERATIONS);
        return m_Map[static_cast<int>(op)];
    }

private:
    std::array<VkBlendOp, BLEND_OPERATION_NUM_OPERATIONS> m_Map = {};
};

VkPipelineColorBlendAttachmentState RenderTargetBlendDescToVkColorBlendAttachmentState(const RenderTargetBlendDesc &RTBlendDesc)
{
    static const BlendFactorToVkBlendFactorMapper BFtoVKBF;
    static const BlendOperationToVkBlendOp BOtoVKBO;
    VkPipelineColorBlendAttachmentState AttachmentBlendState = {};
    AttachmentBlendState.blendEnable         = RTBlendDesc.BlendEnable;
    AttachmentBlendState.srcColorBlendFactor = BFtoVKBF[RTBlendDesc.SrcBlend];
    AttachmentBlendState.dstColorBlendFactor = BFtoVKBF[RTBlendDesc.DestBlend];
    AttachmentBlendState.colorBlendOp        = BOtoVKBO[RTBlendDesc.BlendOp];
    AttachmentBlendState.srcAlphaBlendFactor = BFtoVKBF[RTBlendDesc.SrcBlendAlpha];
    AttachmentBlendState.dstAlphaBlendFactor = BFtoVKBF[RTBlendDesc.DestBlendAlpha];
    AttachmentBlendState.alphaBlendOp        = BOtoVKBO[RTBlendDesc.BlendOpAlpha];
    AttachmentBlendState.colorWriteMask      = 
        ((RTBlendDesc.RenderTargetWriteMask & COLOR_MASK_RED)   ? VK_COLOR_COMPONENT_R_BIT : 0) |
        ((RTBlendDesc.RenderTargetWriteMask & COLOR_MASK_GREEN) ? VK_COLOR_COMPONENT_G_BIT : 0) |
        ((RTBlendDesc.RenderTargetWriteMask & COLOR_MASK_BLUE)  ? VK_COLOR_COMPONENT_B_BIT : 0) |
        ((RTBlendDesc.RenderTargetWriteMask & COLOR_MASK_ALPHA) ? VK_COLOR_COMPONENT_A_BIT : 0);

    return AttachmentBlendState;
}

void BlendStateDesc_To_VkBlendStateCI(const BlendStateDesc &BSDesc, 
                                      VkPipelineColorBlendStateCreateInfo &ColorBlendStateCI,
                                      std::vector<VkPipelineColorBlendAttachmentState> &ColorBlendAttachments)
{
    static const LogicOperationToVkLogicOp LogicOpToVkLogicOp;
    ColorBlendStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlendStateCI.pNext = nullptr;
    ColorBlendStateCI.flags = 0; // reserved for future use
    ColorBlendStateCI.logicOpEnable = BSDesc.RenderTargets[0].LogicOperationEnable;
    ColorBlendStateCI.logicOp = LogicOpToVkLogicOp[BSDesc.RenderTargets[0].LogicOp];
    ColorBlendStateCI.blendConstants[0] = 0.f;
    ColorBlendStateCI.blendConstants[1] = 0.f;
    ColorBlendStateCI.blendConstants[2] = 0.f;
    ColorBlendStateCI.blendConstants[3] = 0.f;
    for(uint32_t attachment = 0; attachment < ColorBlendStateCI.attachmentCount; ++attachment)
    {
        const auto& RTBlendState = BSDesc.IndependentBlendEnable ? BSDesc.RenderTargets[attachment] : BSDesc.RenderTargets[0];
        ColorBlendAttachments[attachment] = RenderTargetBlendDescToVkColorBlendAttachmentState(RTBlendState);
    }
}


#if 0
D3D12_COMPARISON_FUNC ComparisonFuncToD3D12ComparisonFunc(COMPARISON_FUNCTION Func)
{
    return ComparisonFuncToD3DComparisonFunc<D3D12_COMPARISON_FUNC>(Func);
}

D3D12_FILTER FilterTypeToD3D12Filter(FILTER_TYPE MinFilter, FILTER_TYPE MagFilter, FILTER_TYPE MipFilter)
{
    return FilterTypeToD3DFilter<D3D12_FILTER>(MinFilter, MagFilter, MipFilter);
}

D3D12_TEXTURE_ADDRESS_MODE TexAddressModeToD3D12AddressMode(TEXTURE_ADDRESS_MODE Mode)
{
    return TexAddressModeToD3DAddressMode<D3D12_TEXTURE_ADDRESS_MODE>(Mode);
}

void DepthStencilStateDesc_To_D3D12_DEPTH_STENCIL_DESC(const DepthStencilStateDesc &DepthStencilDesc, D3D12_DEPTH_STENCIL_DESC &d3d12DSSDesc)
{
    DepthStencilStateDesc_To_D3D_DEPTH_STENCIL_DESC<D3D12_DEPTH_STENCIL_DESC, D3D12_DEPTH_STENCILOP_DESC, D3D12_STENCIL_OP, D3D12_COMPARISON_FUNC>(DepthStencilDesc, d3d12DSSDesc);
}

void RasterizerStateDesc_To_D3D12_RASTERIZER_DESC(const RasterizerStateDesc &RasterizerDesc, D3D12_RASTERIZER_DESC &d3d12RSDesc)
{
    RasterizerStateDesc_To_D3D_RASTERIZER_DESC<D3D12_RASTERIZER_DESC, D3D12_FILL_MODE, D3D12_CULL_MODE>(RasterizerDesc, d3d12RSDesc);

    // The sample count that is forced while UAV rendering or rasterizing. 
    // Valid values are 0, 1, 2, 4, 8, and optionally 16. 0 indicates that 
    // the sample count is not forced.
    d3d12RSDesc.ForcedSampleCount     = 0;

    d3d12RSDesc.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
}



D3D12_LOGIC_OP LogicOperationToD3D12LogicOp( LOGIC_OPERATION lo )
{
    // Note that this code is safe for multithreaded environments since
    // bIsInit is set to true only AFTER the entire map is initialized.
    static bool bIsInit = false;
    static D3D12_LOGIC_OP D3D12LogicOp[LOGIC_OP_NUM_OPERATIONS] = {};
    if( !bIsInit )
    {
        // In a multithreaded environment, several threads can potentially enter
        // this block. This is not a problem since they will just initialize the 
        // memory with the same values more than once
        
        bIsInit = true;
    }
    if( lo >= LOGIC_OP_CLEAR && lo < LOGIC_OP_NUM_OPERATIONS )
    {
        auto d3dlo = D3D12LogicOp[lo];
        return d3dlo;
    }
    else
    {
        UNEXPECTED("Incorrect blend factor (", lo, ")" );
        return static_cast<D3D12_LOGIC_OP>( 0 );
    }
}


void BlendStateDesc_To_D3D12_BLEND_DESC(const BlendStateDesc &BSDesc, D3D12_BLEND_DESC &d3d12BlendDesc)
{
    BlendStateDescToD3DBlendDesc<D3D12_BLEND_DESC, D3D12_BLEND, D3D12_BLEND_OP>(BSDesc, d3d12BlendDesc);

    for( int i = 0; i < 8; ++i )
    {
        const auto& SrcRTDesc = BSDesc.RenderTargets[i];
        auto &DstRTDesc = d3d12BlendDesc.RenderTarget[i];

        // The following members only present in D3D_RENDER_TARGET_BLEND_DESC
        DstRTDesc.LogicOpEnable = SrcRTDesc.LogicOperationEnable ? TRUE : FALSE;
        DstRTDesc.LogicOp = LogicOperationToD3D12LogicOp(SrcRTDesc.LogicOp);
    }
}

void LayoutElements_To_D3D12_INPUT_ELEMENT_DESCs(const std::vector<LayoutElement, STDAllocatorRawMem<LayoutElement>> &LayoutElements, 
                                                 std::vector<D3D12_INPUT_ELEMENT_DESC, STDAllocatorRawMem<D3D12_INPUT_ELEMENT_DESC> > &d3d12InputElements)
{
    LayoutElements_To_D3D_INPUT_ELEMENT_DESCs<D3D12_INPUT_ELEMENT_DESC>(LayoutElements, d3d12InputElements);
}

D3D12_PRIMITIVE_TOPOLOGY TopologyToD3D12Topology(PRIMITIVE_TOPOLOGY Topology)
{
    return TopologyToD3DTopology<D3D12_PRIMITIVE_TOPOLOGY>(Topology);
}



void TextureViewDesc_to_D3D12_SRV_DESC(const TextureViewDesc& SRVDesc, D3D12_SHADER_RESOURCE_VIEW_DESC &D3D12SRVDesc, Uint32 SampleCount)
{
    TextureViewDesc_to_D3D_SRV_DESC(SRVDesc, D3D12SRVDesc, SampleCount);
    D3D12SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    switch (SRVDesc.TextureDim)
    {
        case RESOURCE_DIM_TEX_1D:
            D3D12SRVDesc.Texture1D.ResourceMinLODClamp = 0;
        break;

        case RESOURCE_DIM_TEX_1D_ARRAY:
            D3D12SRVDesc.Texture1DArray.ResourceMinLODClamp = 0;
        break;

        case RESOURCE_DIM_TEX_2D:
            if( SampleCount > 1 )
            {
            }
            else
            {
                D3D12SRVDesc.Texture2D.PlaneSlice = 0;
                D3D12SRVDesc.Texture2D.ResourceMinLODClamp = 0;
            }
        break;

        case RESOURCE_DIM_TEX_2D_ARRAY:
            if( SampleCount > 1 )
            {
            }
            else
            {
                D3D12SRVDesc.Texture2DArray.PlaneSlice = 0;
                D3D12SRVDesc.Texture2DArray.ResourceMinLODClamp = 0;
            }
        break;

        case RESOURCE_DIM_TEX_3D:
            D3D12SRVDesc.Texture3D.ResourceMinLODClamp = 0;
        break;

        case RESOURCE_DIM_TEX_CUBE:
            D3D12SRVDesc.TextureCube.ResourceMinLODClamp = 0;
        break;

        case RESOURCE_DIM_TEX_CUBE_ARRAY:
            D3D12SRVDesc.TextureCubeArray.ResourceMinLODClamp = 0;
        break;

        default:
            UNEXPECTED( "Unexpected view type" );
    }
}

void TextureViewDesc_to_D3D12_RTV_DESC(const TextureViewDesc& RTVDesc, D3D12_RENDER_TARGET_VIEW_DESC &D3D12RTVDesc, Uint32 SampleCount)
{
    TextureViewDesc_to_D3D_RTV_DESC(RTVDesc, D3D12RTVDesc, SampleCount);
    switch (RTVDesc.TextureDim)
    {
        case RESOURCE_DIM_TEX_1D:
        break;

        case RESOURCE_DIM_TEX_1D_ARRAY:
        break;

        case RESOURCE_DIM_TEX_2D:
            if( SampleCount > 1 )
            {
            }
            else
            {
                D3D12RTVDesc.Texture2D.PlaneSlice = 0;
            }
        break;

        case RESOURCE_DIM_TEX_2D_ARRAY:
            if( SampleCount > 1 )
            {
            }
            else
            {
                D3D12RTVDesc.Texture2DArray.PlaneSlice = 0;
            }
        break;

        case RESOURCE_DIM_TEX_3D:
        break;

        default:
            UNEXPECTED( "Unexpected view type" );
    }
}

void TextureViewDesc_to_D3D12_DSV_DESC(const TextureViewDesc& DSVDesc, D3D12_DEPTH_STENCIL_VIEW_DESC &D3D12DSVDesc, Uint32 SampleCount)
{
    TextureViewDesc_to_D3D_DSV_DESC(DSVDesc, D3D12DSVDesc, SampleCount);
    D3D12DSVDesc.Flags = D3D12_DSV_FLAG_NONE;
}

void TextureViewDesc_to_D3D12_UAV_DESC(const TextureViewDesc& UAVDesc, D3D12_UNORDERED_ACCESS_VIEW_DESC &D3D12UAVDesc)
{
    TextureViewDesc_to_D3D_UAV_DESC(UAVDesc, D3D12UAVDesc);
    switch (UAVDesc.TextureDim)
    {
        case RESOURCE_DIM_TEX_1D:
        break;

        case RESOURCE_DIM_TEX_1D_ARRAY:
        break;

        case RESOURCE_DIM_TEX_2D:
            D3D12UAVDesc.Texture2D.PlaneSlice = 0;
        break;

        case RESOURCE_DIM_TEX_2D_ARRAY:
            D3D12UAVDesc.Texture2DArray.PlaneSlice = 0;
        break;

        case RESOURCE_DIM_TEX_3D:
        break;

        default:
            UNEXPECTED( "Unexpected view type" );
    }
}


void BufferViewDesc_to_D3D12_SRV_DESC(const BufferDesc &BuffDesc, const BufferViewDesc& SRVDesc, D3D12_SHADER_RESOURCE_VIEW_DESC &D3D12SRVDesc)
{
    BufferViewDesc_to_D3D_SRV_DESC(BuffDesc, SRVDesc, D3D12SRVDesc);
    D3D12SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    D3D12SRVDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
    VERIFY_EXPR(BuffDesc.BindFlags & BIND_SHADER_RESOURCE);
    if (BuffDesc.Mode == BUFFER_MODE_STRUCTURED)
        D3D12SRVDesc.Buffer.StructureByteStride = BuffDesc.ElementByteStride; 
}

void BufferViewDesc_to_D3D12_UAV_DESC(const BufferDesc &BuffDesc, const BufferViewDesc& UAVDesc, D3D12_UNORDERED_ACCESS_VIEW_DESC &D3D12UAVDesc)
{
    BufferViewDesc_to_D3D_UAV_DESC(BuffDesc, UAVDesc, D3D12UAVDesc);
    D3D12UAVDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
    VERIFY_EXPR(BuffDesc.BindFlags & BIND_UNORDERED_ACCESS);
    if (BuffDesc.Mode == BUFFER_MODE_STRUCTURED)
        D3D12UAVDesc.Buffer.StructureByteStride = BuffDesc.ElementByteStride; 
}

D3D12_STATIC_BORDER_COLOR BorderColorToD3D12StaticBorderColor(const Float32 BorderColor[])
{
    D3D12_STATIC_BORDER_COLOR StaticBorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
    if(BorderColor[0] == 0 && BorderColor[1] == 0 && BorderColor[2] == 0 && BorderColor[3] == 0)
        StaticBorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
    else if(BorderColor[0] == 0 && BorderColor[1] == 0 && BorderColor[2] == 0 && BorderColor[3] == 1)
        StaticBorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
    else if(BorderColor[0] == 1 && BorderColor[1] == 1 && BorderColor[2] == 1 && BorderColor[3] == 0)
        StaticBorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
    else
    {
        LOG_ERROR_MESSAGE("Static samplers only allow transparent black (0,0,0,1), opaque black (0,0,0,0) or opaque white (1,1,1,0) as border colors.");
    }
    return StaticBorderColor;
}
#endif
}
