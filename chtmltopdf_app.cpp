#include "chtmltopdf_app.h"
#include "include/wrapper/cef_helpers.h"
#include "chtmltopdf_handler.h"
#include <iostream>

void CHtmlToPdfApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  CefWindowInfo window_info;
  window_info.SetAsWindowless(NULL, 0);

  CefRefPtr<CHtmlToPdfHandler> handler(new CHtmlToPdfHandler());
  CefBrowserSettings browser_settings;
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

  std::string url;
  std::string target;
  std::string page_size;

  url = command_line->GetSwitchValue("url");
  target = command_line->GetSwitchValue("output");
  page_size = command_line->GetSwitchValue("page-size");

  if (url.empty()) {
    url = "http://www.google.com";
  }

  if (target.empty()) {
    target = "/tmp/output.pdf";
  }

  if (page_size == "A4")
    handler->setPageSize(297000, 210000);
  else if (page_size == "Letter")
    handler->setPageSize(279400, 215900);
  else
    // A4 is the default
    handler->setPageSize(297000, 210000);

  handler->setFileName(target);

  CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, NULL);

}

CHtmlToPdfApp::CHtmlToPdfApp() {

}

CefRefPtr<CefPrintHandler> CHtmlToPdfApp::GetPrintHandler() {
  return this;
}

void CHtmlToPdfApp::OnPrintStart(CefRefPtr<CefBrowser> browser) {

}

void CHtmlToPdfApp::OnPrintSettings(CefRefPtr<CefPrintSettings> settings, bool get_defaults) {

}

bool CHtmlToPdfApp::OnPrintDialog(bool has_selection, CefRefPtr<CefPrintDialogCallback> callback) {
  return false;
}

bool CHtmlToPdfApp::OnPrintJob(const CefString &document_name, const CefString &pdf_file_path,
                               CefRefPtr<CefPrintJobCallback> callback) {
  return false;
}

void CHtmlToPdfApp::OnPrintReset() {

}

CefSize CHtmlToPdfApp::GetPdfPaperSize(int device_units_per_inch) {
  return CefSize(800, 600);
}
