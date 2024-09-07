#ifndef IMZOOMABLEIMAGE_H
#define IMZOOMABLEIMAGE_H

#define IMGUI_DEFINE_MATH_OPERATORS
#include "vcpkg_installed/arm64-osx/include/imgui.h"
#include "vcpkg_installed/arm64-osx/include/imgui_internal.h"
#include "vcpkg_installed/arm64-osx/include/imgui_impl_glfw.h"
#include "vcpkg_installed/arm64-osx/include/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include "vcpkg_installed/arm64-osx/include/GLFW/glfw3.h"

namespace ImGui {
	// - Custom widget that is identical to ImGui::Image width but allows you to zoom and pan the image
	// - Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
    // - 'uv0' and 'uv1' are texture coordinates. Read about them from the same link above.
	void Z_Image(ImTextureID user_texture_id, const ImVec2& image_size, ImVec2& uv0, ImVec2& uv1, const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0)); 
}

#endif
