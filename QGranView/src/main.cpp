#include "application.hpp"
#include "command_buffer.hpp"
#include "device.hpp"
#include "os_filesystem.hpp"
#include "muglm/muglm_impl.hpp"

using namespace Granite;
using namespace Vulkan;

struct QGranViewApplication : Granite::Application
{
	void render_frame(double, double elapsed_time)
	{
		auto &wsi = get_wsi();
		auto &device = wsi.get_device();

		auto cmd = device.request_command_buffer();

		cmd->begin_render_pass(device.get_swapchain_render_pass(SwapchainRenderPass::ColorOnly));
		cmd->set_program("assets://shaders/triangle.vert", "assets://shaders/triangle.frag");
		cmd->set_opaque_state();
		cmd->set_primitive_topology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP);

		vec2 vertices[] = {
			vec2(-0.5f, -0.5f),
			vec2(-0.5f, +0.5f),
			vec2(+0.5f, -0.5f),
		};

		auto c = float(muglm::cos(elapsed_time * 2.0));
		auto s = float(muglm::sin(elapsed_time * 2.0));
		mat2 m{vec2(c, -s), vec2(s, c)};
		for (auto &v : vertices)
			v = m * v;

		static const vec4 colors[] = {
			vec4(1.0f, 0.0f, 0.0f, 1.0f),
			vec4(0.0f, 1.0f, 0.0f, 1.0f),
			vec4(0.0f, 0.0f, 1.0f, 1.0f),
		};

		auto *verts = static_cast<vec2 *>(cmd->allocate_vertex_data(0, sizeof(vertices), sizeof(vec2)));
		auto *col = static_cast<vec4 *>(cmd->allocate_vertex_data(1, sizeof(colors), sizeof(vec4)));
		memcpy(verts, vertices, sizeof(vertices));
		memcpy(col, colors, sizeof(colors));
		cmd->set_vertex_attrib(0, 0, VK_FORMAT_R32G32_SFLOAT, 0);
		cmd->set_vertex_attrib(1, 1, VK_FORMAT_R32G32B32A32_SFLOAT, 0);
		cmd->draw(3);
		cmd->end_render_pass();
		device.submit(cmd);
	}

	ImageHandle render_target;
};

namespace Granite
{
Application *application_create(int, char **)
{
    GRANITE_APPLICATION_SETUP_FILESYSTEM();

    try
    {
        auto *app = new QGranViewApplication();
        return app;
    }
    catch (const std::exception &e)
    {
        LOGE("application_create() threw exception: %s\n", e.what());
        return nullptr;
    }
}
}
