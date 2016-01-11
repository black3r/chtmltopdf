#include "chtmltopdf_app.h"
#include "include/wrapper/cef_helpers.h"
#include "chtmltopdf_handler.h"
#include <iostream>

void CHtmlToPdfApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  CefWindowInfo window_info;
  window_info.SetAsWindowless(-1, 0);

  CefRefPtr<CHtmlToPdfHandler> handler(new CHtmlToPdfHandler());
  CefBrowserSettings browser_settings;
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

  std::string url;
  std::string target;

  url = command_line->GetSwitchValue("url");
  target = command_line->GetSwitchValue("output");

  if (url.empty()) {
    url = "http://www.google.com";
  }

  if (target.empty()) {
    target = "/tmp/output.pdf";
  }

  handler->setFileName(target);

  CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, NULL);
}

CHtmlToPdfApp::CHtmlToPdfApp() {

}
