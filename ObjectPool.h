#pragma once
#include <array>
#include <vector>
#include <functional>

//El tamaño del pool es estatico y es dado por el parametro del template. Tambien se puede pasar por el constructor.
template<typename T, int SIZE>
class ObjectPool {
public:
	//f es un lambda que usamos para chequear si un objeto esta en uso
	ObjectPool(std::function<bool(T*)> f) {
		inUseF_ = f;
		for (auto &b : objs_) {
			objsPtrs_.push_back(&b);
		}
	}

	virtual ~ObjectPool() {
	}

	T* getObj() {
		for (auto &o : objs_) {
			if (!inUseF_(&o))
				return &o;
		}
		return nullptr;
	}

	const std::vector<T*>& getPool() {
		return objsPtrs_;
	}

private:
	std::function<bool(T*)> inUseF_;
	std::array<T, SIZE> objs_;
	std::vector<T*> objsPtrs_;
};