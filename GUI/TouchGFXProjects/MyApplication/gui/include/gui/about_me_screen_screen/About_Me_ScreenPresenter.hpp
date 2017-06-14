#ifndef ABOUT_ME_SCREEN_PRESENTER_HPP
#define ABOUT_ME_SCREEN_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class About_Me_ScreenView;

class About_Me_ScreenPresenter : public Presenter, public ModelListener
{
public:
    About_Me_ScreenPresenter(About_Me_ScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~About_Me_ScreenPresenter() {};

private:
    About_Me_ScreenPresenter();

    About_Me_ScreenView& view;
};


#endif // ABOUT_ME_SCREEN_PRESENTER_HPP
