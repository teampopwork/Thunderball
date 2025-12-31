#ifndef __BUTTONLISTENER_H__
#define __BUTTONLISTENER_H__

namespace Sexy
{

// VTABLE: POPCAPGAME1 0x005d26e4
class ButtonListener
{	
public:
    // FUNCTION: POPCAPGAME1 0x00497dc0
	virtual void			ButtonPress(int theId) {}
    // FUNCTION: POPCAPGAME1 0x00401fe0
	virtual void			ButtonPress(int theId, int theClickCount) { ButtonPress(theId); }
    // FUNCTION: POPCAPGAME1 0x00401fe0
	virtual void			ButtonDepress(int theId) {}
    // FUNCTION: POPCAPGAME1 0x00401fe0
	virtual void			ButtonDownTick(int theId) {}
    // FUNCTION: POPCAPGAME1 0x00401fe0
	virtual void			ButtonMouseEnter(int theId) {}
    // FUNCTION: POPCAPGAME1 0x00401fe0
	virtual void			ButtonMouseLeave(int theId) {}
    // FUNCTION: POPCAPGAME1 0x0054b790
	virtual void			ButtonMouseMove(int theId, int theX, int theY) {}
};

}

#endif //__BUTTONLISTENER_H__