#pragma once

// For use by Independent applications

#include <stdio.h>
#include "Independent/Application.h"

// --System Files-------------------------
#include "Independent/SystemFiles/include/Layer.h"
#include "Independent/SystemFiles/include/Log.h"

#include "Independent/SystemFiles/include/Input.h"
#include "Independent/SystemFiles/include/MouseButtonCodes.h"
#include "Independent/SystemFiles/include/KeyCodes.h"

#include "Independent/SystemFiles/include/ImGui/ImGuiLayer.h"
// ---------------------------------------

// --Render------------------------------
#include "Independent/Render/include/Renderer.h"
#include "Independent/Render/include/Renderer2D.h"
#include "Independent/Render/include/RenderCommand.h"

#include "Independent/Render/include/shader/Shader.h"
#include "Independent/Render/include/texture/Texture.h"
#include "Independent/Render/include/buffer/Buffer.h"
#include "Independent/Render/include/vertex_array/VertexArray.h"

#include "Independent/Render/include/camera/OrthographicCamera.h"
#include "Independent/Render/include/camera/OrthographicCameraController.h"
// --------------------------------------

// --Core--------------------------------
#include "Independent/Core/include/utils/Timestep.h"

#include "Independent/Core/include/containers/UniquePtr.h"
#include "Independent/Core/include/containers/SharedPtr.h"
// --------------------------------------
