#include "../includes/manager.hpp"

namespace GeoFrame {
WindowManager::~WindowManager() { this->ReleaseObjects(); }

void WindowManager::ReleaseObjects() {
    for (auto &window : mWindows) {
        window->Close();
        delete window.release();
    }
}

void WindowManager::Create(unsigned width, unsigned height, Str const &title) {
    Kernel::RawWindow *rawWindow =
        new Kernel::RawWindow(width, height, title, Kernel::WindowSettings());
    mWindows.push_back(Unique<Kernel::RawWindow>(rawWindow));
}
} // namespace GeoFrame
