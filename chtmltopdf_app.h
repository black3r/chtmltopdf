#ifndef CEF_CHTMLTOPDF_H
#define CEF_CHTMLTOPDF_H

#include "include/cef_app.h"


class CHtmlToPdfApp : public CefApp,
                      public CefPrintHandler,
                      public CefBrowserProcessHandler {

public:
    CHtmlToPdfApp();

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE { return this; }

    virtual CefRefPtr<CefPrintHandler> GetPrintHandler() override;

    virtual void OnContextInitialized() OVERRIDE;

    virtual void OnPrintStart(CefRefPtr<CefBrowser> browser);

    virtual void OnPrintSettings(CefRefPtr<CefPrintSettings> settings, bool get_defaults);

    virtual bool OnPrintDialog(bool has_selection, CefRefPtr<CefPrintDialogCallback> callback);

    virtual bool OnPrintJob(const CefString &document_name, const CefString &pdf_file_path,
                            CefRefPtr<CefPrintJobCallback> callback);

    virtual void OnPrintReset();


    virtual CefSize GetPdfPaperSize(int device_units_per_inch) override;

private:
    IMPLEMENT_REFCOUNTING(CHtmlToPdfApp);

};


#endif //CEF_CHTMLTOPDF_H
