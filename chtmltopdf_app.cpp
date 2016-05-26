#include "chtmltopdf_app.h"
#include "include/wrapper/cef_helpers.h"
#include "chtmltopdf_handler.h"
#include <iostream>

void CHtmlToPdfApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  CefWindowInfo window_info;
  window_info.SetAsWindowless(0, 0);

  CefRefPtr<CHtmlToPdfHandler> handler(new CHtmlToPdfHandler());
  this->handler = handler;
  CefBrowserSettings browser_settings;
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

  std::string url;
  std::string target;
  std::string waitprint;
  std::string page_size;
  bool printOnLoad = false;

  url = command_line->GetSwitchValue("url");
  target = command_line->GetSwitchValue("output");
  waitprint = command_line->GetSwitchValue("waitprint");
  page_size = command_line->GetSwitchValue("page-size");

  if (url.empty()) {
    url = "http://www.google.com";
  }

  if (target.empty()) {
    target = "/tmp/output.pdf";
  }

  if (waitprint.empty()) {
    printOnLoad = true;
  }

  if (page_size == "A4")
    handler->setPageSize(297000, 210000);
  else if (page_size == "Letter")
    handler->setPageSize(279400, 215900);
  else
    // A4 is the default
    handler->setPageSize(297000, 210000);
  handler->setPrintOnLoad(printOnLoad);

  handler->setFileName(target);

  CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, NULL);

}

CHtmlToPdfApp::CHtmlToPdfApp() {

}

CefRefPtr<CefPrintHandler> CHtmlToPdfApp::GetPrintHandler() {
  return this;
}

void CHtmlToPdfApp::OnPrintStart(CefRefPtr<CefBrowser> browser) {
  std::cout << "Print Start" << std::endl;
  this->handler->PrintStart(browser);
  // Try to print to pdf from around here...
}

void CHtmlToPdfApp::OnPrintSettings(CefRefPtr<CefPrintSettings> settings, bool get_defaults) {
  std::cout << "Print Settings" << std::endl;
}

bool CHtmlToPdfApp::OnPrintDialog(bool has_selection, CefRefPtr<CefPrintDialogCallback> callback) {
  std::cout << "Print dialog!" << std::endl;
  return false;
}

bool CHtmlToPdfApp::OnPrintJob(const CefString &document_name, const CefString &pdf_file_path,
                               CefRefPtr<CefPrintJobCallback> callback) {
  std::cout << "Print Job" << std::endl;
  return false;
}

void CHtmlToPdfApp::OnPrintReset() {

}

CefSize CHtmlToPdfApp::GetPdfPaperSize(int device_units_per_inch) {
  return CefSize(800, 600);
}
