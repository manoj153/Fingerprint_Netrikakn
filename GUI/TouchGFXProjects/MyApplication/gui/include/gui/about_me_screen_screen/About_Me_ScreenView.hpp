#ifndef ABOUT_ME_SCREEN_VIEW_HPP
#define ABOUT_ME_SCREEN_VIEW_HPP

#include <gui_generated/about_me_screen_screen/About_Me_ScreenViewBase.hpp>
#include <gui/about_me_screen_screen/About_Me_ScreenPresenter.hpp>

class About_Me_ScreenView : public About_Me_ScreenViewBase
{
public:
    About_Me_ScreenView();
    virtual ~About_Me_ScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // ABOUT_ME_SCREEN_VIEW_HPP
