#include "../includes/windowTest.hpp"

using namespace GeoFrame;

void window_generation_test(unsigned const &width, unsigned const &height,
                            Str const &title) {
    GeoFrameContext context = GeoFrameContext();
    Kernel::RawWindow window =
        Kernel::RawWindow(width, height, title, Kernel::WindowSettings());

    while (!window.IsClosed()) {
        context.PollEvents();
        window.Swap();
    }
}
