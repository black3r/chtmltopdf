#include <X11/Xlib.h>
#include "tests/chtmltopdf/chtmltopdf_app.h"
#include "include/base/cef_logging.h"

namespace {
    int XErrorHandlerImpl(Display *display, XErrorEvent *event) {
        LOG(WARNING)
        << "X error received: "
        << "type " << event->type << ", "
        << "serial " << event->serial << ", "
        << "error_code " << static_cast<int>(event->error_code) << ", "
        << "request_code " << static_cast<int>(event->request_code) << ", "
        << "minor_code " << static_cast<int>(event->minor_code);
        return 0;
    }

    int XIOErrorHandlerImpl(Display *display) {
        return 0;
    }
} // namespace

// Entry point
int main(int argc, char* argv[]) {
    CefMainArgs main_args(argc, argv);

    // This forks itself and does some chrome multi-process magic.
    int exit_code = CefExecuteProcess(main_args, NULL, NULL);
    if (exit_code >= 0) {
        // This sub-process has completed.
        return exit_code;
    }

    // Install xlib error handlers
    XSetErrorHandler(XErrorHandlerImpl);
    XSetIOErrorHandler(XIOErrorHandlerImpl);

    // Specify global CEF settings here.
    CefSettings settings;
    CefRefPtr<CHtmlToPdfApp> app(new CHtmlToPdfApp);
    CefInitialize(main_args, settings, app.get(), NULL);
    CefRunMessageLoop();
    CefShutdown();

    return 0;
}
