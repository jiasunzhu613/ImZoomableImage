#include "ImZoomableImage.h"
namespace ImGui {
    void Z_Image(ImTextureID user_texture_id, const ImVec2& image_size, ImVec2& uv0, ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col) 
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return;
        
        ImGuiIO& IO = ImGui::GetIO();
        ImDrawList* drawlist = ImGui::GetWindowDrawList();
        
        //NOTE: make sure to use GetCursorScreenPos here instead of GetCursorPos, GetCursorScreenPos returns the cursor in window
        ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        //TODO: add border rect
        drawlist->AddImage((void*)(intptr_t)user_texture_id, cursor_pos, cursor_pos + image_size, ImVec2(uv0[0], uv0[1]), ImVec2(uv1[0], uv1[1]), ImGui::GetColorU32(tint_col));
        ImGui::InvisibleButton("image", image_size);
        
        const bool is_hovered = ImGui::IsItemHovered();
        const bool is_held = ImGui::IsItemActive();

        //UV texture coordinates in decimal form allows it to be used as a zoom ratio to find how much we've zoomed in to the image
        float zoom_ratio = (uv1[0] - uv0[0]) * 1.5f; // 1.5f factor applied just to make the zoom drag speed a little faster 
        //TODO: probably need a scale factor for one dimension of the image

        // Move zoomed image on drag
        if (is_held) {
            float x_dist = uv1[0] - uv0[0];
            float y_dist = uv1[1] - uv0[1];
            ImVec2 mouse_delta = IO.MouseDelta * 0.002f * zoom_ratio;
            // cout << mouse_delta[0] << " " << mouse_delta[1] << endl;
            
            uv0[0] = fmax(0.0f, fmin(1.0f - x_dist, uv0[0] - mouse_delta.x));
            uv0[1] = fmax(0.0f, fmin(1.0f - y_dist, uv0[1] - mouse_delta.y));
            uv1[0] = fmin(1.0f, fmax(0.0f + x_dist, uv1[0] - mouse_delta.x)); 
            uv1[1] = fmin(1.0f, fmax(0.0f + y_dist, uv1[1] - mouse_delta.y)); 
        }
        
        // Zoom in/out on image on scroll
        if (is_hovered) {
            float mouse_wheel_delta = IO.MouseWheel * 0.005f;
            
            // clamp uv0 and uv1 final position so that image does not flip
            float x_clamp = (uv0[0] + uv1[0]) / 2.0f;
            float y_clamp = (uv0[1] + uv1[1]) / 2.0f;
            // uv0 reached a border, so we wait for uv1 to reach a border as well (therefore we only increment uv1)
            if ((uv0[0] == 0.0f || uv0[1] == 0.0f) && (uv1[0] != 1.0f && uv1[1] != 1.0f)) { 
                uv1[0] = fmin(1.0f, fmax(x_clamp, uv1[0] + mouse_wheel_delta));
                uv1[1] = fmin(1.0f, fmax(y_clamp, uv1[1] + mouse_wheel_delta));
            } 
            //uv1 reached a border, so we wait for uv0 to reach a border as well (therefore we only increment uv0)
            else if ((uv1[0] == 1.0f || uv1[1] == 1.0f) && (uv0[0] != 0.0f && uv0[1] != 0.0f)) {
                uv0[0] = fmax(0.0f, fmin(x_clamp, uv0[0] - mouse_wheel_delta));
                uv0[1] = fmax(0.0f, fmin(y_clamp, uv0[1] - mouse_wheel_delta));
            }
            else {
                uv0[0] = fmax(0.0f, fmin(x_clamp, uv0[0] - mouse_wheel_delta));
                uv0[1] = fmax(0.0f, fmin(y_clamp, uv0[1] - mouse_wheel_delta));
                uv1[0] = fmin(1.0f, fmax(x_clamp, uv1[0] + mouse_wheel_delta));
                uv1[1] = fmin(1.0f, fmax(y_clamp, uv1[1] + mouse_wheel_delta));
            }
        }
    }
}
