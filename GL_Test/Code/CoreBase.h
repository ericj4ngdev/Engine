#pragma once

class CoreBase {
public:
	CoreBase() = default;

	virtual void Init() = 0;
	virtual void Update() {};

	virtual ~CoreBase() = default;
};