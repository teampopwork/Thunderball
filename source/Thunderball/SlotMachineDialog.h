#ifndef __SLOTMACHINEDIALOG_H__
#define __SLOTMACHINEDIALOG_H__

#include "ThunderDialog.h"

#include <SexyAppFramework/SmartPtr.h>

namespace Sexy {
class Board;
class Graphics;
class Ball;
class PhysObj;
class DataSync;
class ThunderballApp;

class SlotMachineDialog : public ThunderDialog {
public:
    ThunderballApp* mApp; // +0x178
    Board* mBoard; // +0x17c
    int mUnk0x180; // +0x180
    int mUnk0x184; // +0x184
    SmartPtr<Ball> mBall; // +0x188
    SmartPtr<PhysObj> mPhysObj; // +0x18c
    float mUnk0x190; // +0x190
    float mUnk0x194; // +0x194
    int mUnk0x198; // +0x198
    int mUnk0x19c[40]; // +0x19c
    int mUnk0x23c; // +0x23c
    int mUnk0x240; // +0x240
    int mUnk0x244; // +0x244
    int mUnk0x248; // +0x248

    SlotMachineDialog(Board* param_1);
    virtual ~SlotMachineDialog();

    virtual void Resize(int param_1, int param_2, int param_3, int param_4);
    virtual int GetPreferredHeight(int param_1);
    virtual void Draw(Graphics* param_1);
    void CalcCurLight();
    virtual void UpdatePointer(bool param_1);
    virtual void Update();
    virtual void MouseDown(int param_1, int param_2, int param_3);

    void Init(Ball* param_1, PhysObj* param_2);
    void SyncState(DataSync& param_1);
};

} // namespace Sexy

#endif // __SLOTMACHINEDIALOG_H__
