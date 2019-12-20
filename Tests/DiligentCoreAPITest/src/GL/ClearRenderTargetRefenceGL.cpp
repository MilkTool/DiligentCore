/*     Copyright 2019 Diligent Graphics LLC
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

#include "GL/TestingEnvironmentGL.h"
#include "GL/TestingSwapChainGL.h"

namespace Diligent
{

namespace Testing
{

void ClearRenderTargetReferenceGL(ISwapChain* pSwapChain)
{
    auto* pEnv                = TestingEnvironmentGL::GetInstance();
    auto* pContext            = pEnv->GetDeviceContext();
    auto* pTestingSwapChainGL = ValidatedCast<TestingSwapChainGL>(pSwapChain);

    const auto& SCDesc = pTestingSwapChainGL->GetDesc();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDisable(GL_SCISSOR_TEST);
    pTestingSwapChainGL->BindFramebuffer();
    glViewport(0, 0, SCDesc.Width, SCDesc.Height);
    glClearColor(0.25, 0.5f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Make sure Diligent Engine will reset all GL states
    pContext->InvalidateState();
}

} // namespace Testing

} // namespace Diligent
