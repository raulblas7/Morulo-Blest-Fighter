#pragma once
#include <ctime>

namespace ecs {

using CmpIdType = std::size_t;

//enum de los componentes
enum CmpId : CmpIdType {
	Transform = 0,
	FighterMotion,
	StopOnBorders,
	Rectangle,
	ScoreManager,
	ScoreViewer,
	FighterCtrl,
	VelocityVectorViewer,
	GameCtrl,
	GameLogic,
	FighterViewer,
	Heart,
	Gun,
	BulletsPool,
	BulletsMotion,
	BulletsViewer,
	//
	// don't touch the rest of this enum, it is to identify the max
	// number of components
	_LastCmptId_
};

constexpr std::size_t maxComponents = _LastCmptId_;

// these two should be used to get a component via the field
// entity_
#define GETCMP2_(id,type)  GETCMP3(entity_,id,type)
#define GETCMP1_(type)     GETCMP3(entity_,ecs::type,type)

// these two should be used to get a component via an
// entity e provided as a parameter
#define GETCMP2(e,type) GETCMP3(e,ecs::type,type)
#define GETCMP3(e,id,type) e->getComponent<type>(id)

}
