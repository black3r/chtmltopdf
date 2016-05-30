#include <iostream>

#include "include/cef_app.h"
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_helpers.h"
#include "include/wrapper/cef_closure_task.h"

#include "chtmltopdf_handler.h"

void CHtmlToPdfHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) {
    CefLoadHandler::OnLoadEnd(browser, frame, httpStatusCode);
    std::cout << "Load finished!" << std::endl;
    if (this->printOnLoad) {
        std::cout << "Print on load!" << std::endl;
        this->PrintStart(browser);
    }
}

void CHtmlToPdfHandler::PrintStart(CefRefPtr<CefBrowser> browser) {
    CefPdfPrintSettings settings;
    settings.header_footer_enabled = true;
    settings.backgrounds_enabled = true;
    settings.margin_type = PDF_PRINT_MARGIN_NONE;
    settings.page_height = this->page_height;
    settings.page_width = this->page_width;
    settings.landscape = false;

    browser->GetHost()->PrintToPDF(this->pdf_file_name, settings, this);
    this->browser_ = browser;
}


void CHtmlToPdfHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) {
    CefLoadHandler::OnLoadStart(browser, frame);
}

void CHtmlToPdfHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode,
                                    const CefString &errorText, const CefString &failedUrl) {
    CEF_REQUIRE_UI_THREAD();

    if (errorCode == ERR_ABORTED)
        return;

    frame->LoadString("error", failedUrl);
}

void CHtmlToPdfHandler::OnPdfPrintFinished(const CefString &path, bool ok) {
    std::cout << "Print finished!" << std::endl;
    this->browser_->GetHost()->CloseBrowser(true);
}

// Required CEF handlers below....

namespace {
    CHtmlToPdfHandler* g_instance = NULL;
}  // namespace

bool CHtmlToPdfHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
    rect.x = 0;
    rect.y = 0;
    rect.width = 1920;
    rect.height = 1080;
    return true;
}

void CHtmlToPdfHandler::OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type,
                                const CefRenderHandler::RectList &dirtyRects, const void *buffer, int width,
                                int height) {

}

void CHtmlToPdfHandler::setFileName(std::string str) {
    this->pdf_file_name = str;
}

CHtmlToPdfHandler::CHtmlToPdfHandler() : is_closing_(false) {
    DCHECK(!g_instance);
    g_instance = this;
}

CHtmlToPdfHandler::~CHtmlToPdfHandler() {
    g_instance = NULL;
}

void CHtmlToPdfHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browser_list_.push_back(browser);
}

bool CHtmlToPdfHandler::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    if (browser_list_.size() == 1) {
        is_closing_ = true;
    }

    return false;
}


void CHtmlToPdfHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browser_list_.erase(bit);
            break;
        }
    }

    if (browser_list_.empty()) {
        CefQuitMessageLoop();
    }
}

CefRefPtr<CefRenderHandler> CHtmlToPdfHandler::GetRenderHandler() {
    return this;
}

void CHtmlToPdfHandler::CloseAllBrowsers(bool force_close) {
    CEF_REQUIRE_UI_THREAD();

    if (browser_list_.empty())
        return;

    BrowserList::const_iterator it = browser_list_.begin();
    for (int i = 0; it != browser_list_.end(); ++it, i++) {
        std::cout << "Closing window " << i << std::endl;
        (*it)->GetHost()->CloseBrowser(force_close);
    }
}

CHtmlToPdfHandler *CHtmlToPdfHandler::GetInstance() {
    return g_instance;
}

CefRefPtr<CefDisplayHandler> CHtmlToPdfHandler::GetDisplayHandler() {
    return this;
}

CefRefPtr<CefLifeSpanHandler> CHtmlToPdfHandler::GetLifeSpanHandler() {
    return this;
}

CefRefPtr<CefLoadHandler> CHtmlToPdfHandler::GetLoadHandler() {
    return this;
}

void CHtmlToPdfHandler::setPageSize(int height, int width) {
    this->page_height = height;
    this->page_width = width;
}

void CHtmlToPdfHandler::setPrintOnLoad(bool printOnLoad) {
    this->printOnLoad = printOnLoad;
}

bool CHtmlToPdfHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString &message,
                                         const CefString &source, int line) {
    bool result = CefDisplayHandler::OnConsoleMessage(browser, message, source, line);
    std::cout << "Console: " << message.ToString() << std::endl;
    return result;
}

bool CHtmlToPdfHandler::GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int &screenX,
                                       int &screenY) {
    screenX = viewX;
    screenY = viewY;
    return true;
}

bool CHtmlToPdfHandler::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
    rect.x = 0;
    rect.y = 0;
    rect.width = 1920;
    rect.height = 1080;
    return true;
}
