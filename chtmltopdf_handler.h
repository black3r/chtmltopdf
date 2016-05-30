#ifndef CEF_CHTMLTOPDFHANDLER_H
#define CEF_CHTMLTOPDFHANDLER_H

#include <list>

#include "include/cef_client.h"

class CHtmlToPdfHandler : public CefClient,
                          public CefDisplayHandler,
                          public CefLifeSpanHandler,
                          public CefLoadHandler,
                          public CefPdfPrintCallback,
                          public CefRenderHandler {


public:
    // Provide access to the single global instance of this object.
    static CHtmlToPdfHandler* GetInstance();

    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;
    virtual void OnPdfPrintFinished(const CefString &path, bool ok);

    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects,
                         const void *buffer, int width, int height);

    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);

    void setFileName(std::string str);

    CHtmlToPdfHandler();
    ~CHtmlToPdfHandler();

    virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode,
                             const CefString &errorText, const CefString &failedUrl) override;

    virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) override;

    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;

    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    void CloseAllBrowsers(bool force_close);

    void setPageSize(int height, int width);

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler();
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler();
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler();
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler();

    void PrintStart(CefRefPtr<CefBrowser> browser);
    void setPrintOnLoad(bool printOnLoad);


    virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString &message, const CefString &source,
                                  int line) override;

private:
    typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
    BrowserList browser_list_;
    int page_height;
    int page_width;

    bool is_closing_;

    CefRefPtr<CefBrowser> browser_;
    std::string pdf_file_name;
    bool printOnLoad;

    IMPLEMENT_REFCOUNTING(CHtmlToPdfHandler);
};


#endif //CEF_CHTMLTOPDFHANDLER_H
