/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen1ViewBase::Screen1ViewBase()  :
    buttonCallback(this, &Screen1ViewBase::buttonCallbackHandler)
{
    U_construction.setBitmap(Bitmap(BITMAP_UNDER_CONSTRUCTION_PNG_ID));
    U_construction.setPosition(0, -5, 480, 277);
    U_construction.setScalingAlgorithm(ScalableImage::NEAREST_NEIGHBOR);

    Header_Background.setPosition(0,0,480,50);
    Header_Background.setColor(touchgfx::Color::getColorFrom24BitRGB(0,0,0));

    Heading_Title.setXY(54, 6);
    Heading_Title.setColor(touchgfx::Color::getColorFrom24BitRGB(255,255,255));
    Heading_Title.setLinespacing(0);
    Heading_Title.setTypedText(TypedText(T_TEXTID5));

    FingerprintAcess_Button.setPosition(0, 63, 170, 60);
    FingerprintAcess_Button.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID), Bitmap(BITMAP_BLUE_ICONS_USER_48_ID), Bitmap(BITMAP_BLUE_ICONS_USER_48_ID));
    FingerprintAcess_Button.setIconXY(62, 7);

    Fingerprint_Acess.setXY(0, 124);
    Fingerprint_Acess.setColor(touchgfx::Color::getColorFrom24BitRGB(58,106,166));
    Fingerprint_Acess.setLinespacing(0);
    Fingerprint_Acess.setTypedText(TypedText(T_TEXTID6));

    modalWindow1.setXY(0,0);
    modalWindow1.setBackground(BitmapId(BITMAP_DARK_ICONS_ALERT_32_ID),216, 116);
    modalWindow1.setShadeColor(touchgfx::Color::getColorFrom24BitRGB( 255 , 87, 87));
    modalWindow1.setShadeAlpha(150);
    modalWindow1.hide();


    textArea1.setXY(0, 249);
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(255,255,255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(TypedText(T_TEXTID7));

    AboutMe_button.setPosition(336, 212, 60, 60);
    AboutMe_button.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_ICON_BUTTON_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID), Bitmap(BITMAP_BLUE_ICONS_NEWS_32_ID), Bitmap(BITMAP_BLUE_ICONS_NEWS_32_ID));
    AboutMe_button.setIconXY(15, 17);
    AboutMe_button.setAction(buttonCallback);

    AboutMe_Manoj.setXY(393, 231);
    AboutMe_Manoj.setColor(touchgfx::Color::getColorFrom24BitRGB(81,211,255));
    AboutMe_Manoj.setLinespacing(0);
    AboutMe_Manoj.setTypedText(TypedText(T_TEXTID9));
    add(U_construction);
    add(Header_Background);
    add(Heading_Title);
    add(FingerprintAcess_Button);
    add(Fingerprint_Acess);
    add(modalWindow1);
    add(textArea1);
    add(AboutMe_button);
    add(AboutMe_Manoj);
}

void Screen1ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &FingerprintAcess_Button)
    {

    }
    else if (&src == &AboutMe_button)
    {
        //Interaction2
        //When AboutMe_button clicked change screen to About_Me_Screen
        //Go to About_Me_Screen with slide screen transition towards East
        application().gotoAbout_Me_ScreenScreenSlideTransitionEast();
    }
}
