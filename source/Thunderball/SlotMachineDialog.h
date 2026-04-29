#ifndef __SLOTMACHINEDIALOG_H__
#define __SLOTMACHINEDIALOG_H__

#include <SexyAppFramework/Widget.h>

namespace Sexy {
class Board;
class Graphics;
class Ball;
class PhysObj;
class DataSync;

class SlotMachineDialog : public Widget {
public:
    SlotMachineDialog(Board* param_1);
    virtual ~SlotMachineDialog();

    virtual void Resize(int param_1, int param_2, int param_3, int param_4);
    virtual int GetPreferredHeight(int param_1);
    virtual void Draw(Graphics* param_1);
    void CalcCurLight();
    virtual bool UpdatePointer(bool param_1);
    virtual void Update();
    virtual void MouseDown(int param_1, int param_2, int param_3);

    void Init(Ball* param_1, PhysObj* param_2);
    void SyncState(DataSync* param_1);
};

} // namespace Sexy

#endif // __SLOTMACHINEDIALOG_H__
