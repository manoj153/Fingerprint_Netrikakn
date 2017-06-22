#ifndef FINGERPRINT_VIEW_HPP
#define FINGERPRINT_VIEW_HPP

#include <gui_generated/fingerprint_screen/FingerPrintViewBase.hpp>
#include <gui/fingerprint_screen/FingerPrintPresenter.hpp>

class FingerPrintView : public FingerPrintViewBase
{
public:
    FingerPrintView();
    virtual ~FingerPrintView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // FINGERPRINT_VIEW_HPP
