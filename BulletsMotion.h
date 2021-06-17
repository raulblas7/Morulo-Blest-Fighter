#pragma once
#include "Component.h"
#include "BulletsPool.h"

class BulletsMotion : public Component {
private:
	BulletsPool* pool_;
public:
	BulletsMotion();
	virtual ~BulletsMotion() {}
	void init() override;
	void update() override;
};
