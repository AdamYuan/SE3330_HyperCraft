#pragma once

class WorkerBase {
public:
	virtual void Run() = 0;
	virtual ~WorkerBase() = default;
};
