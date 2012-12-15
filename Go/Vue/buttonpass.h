#ifndef BUTTONPASS_H
#define BUTTONPASS_H

#include<irrlicht/irrlicht.h>

namespace Go
{
    class ServerGo;

    class ButtonPass : public irr::gui::IGUIButton
    {
    public:
        ButtonPass(ServerGo * server, irr::gui::IGUIEnvironment * gui,
                   irr::core::rect<irr::s32> area, const wchar_t *text,
                   irr::gui::IGUIElement *parent);
        bool OnEvent(const irr::SEvent &event);

        void setOverrideFont(irr::gui::IGUIFont *font){}
        void setImage(irr::video::ITexture *image){}
        void setImage(irr::video::ITexture *, const irr::core::rect<irr::s32> &){}
        void setPressedImage(irr::video::ITexture *image, const irr::core::rect<irr::s32> &pos){}
        void setPressedImage(irr::video::ITexture *){}
        void setSpriteBank(irr::gui::IGUISpriteBank *bank){}
        void setSprite(irr::gui::EGUI_BUTTON_STATE state, irr::s32 index, irr::video::SColor color, bool loop = true){}
        void setIsPushButton(bool isPushButton){}
        void setPressed(bool pressed) const{}
        void setUseAlphaChannel(bool useAlphaChannel){}
        bool isAlphaChannelUsed(void) const { return true; }
        bool isPushButton(void) const { return true; }
        void setDrawBorder(bool border){}
        bool isDrawingBorder(void) const{ return false; }
        void setScaleImage(bool scaleImage){}
        bool isScalingImage(void) const { return false; }
        void setPressed(bool pressed){}
        bool isPressed(void) const { return false; }

    private :
        ServerGo * m_server;
    };
}

#endif // BUTTONPASS_H
