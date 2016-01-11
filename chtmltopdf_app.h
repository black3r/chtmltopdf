#ifndef CEF_CHTMLTOPDF_H
#define CEF_CHTMLTOPDF_H

#include "include/cef_app.h"


class CHtmlToPdfApp : public CefApp,
                      public CefBrowserProcessHandler {

public:
    CHtmlToPdfApp();

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE { return this; }
    virtual void OnContextInitialized() OVERRIDE;

private:
    IMPLEMENT_REFCOUNTING(CHtmlToPdfApp);

};


#endif //CEF_CHTMLTOPDF_H
