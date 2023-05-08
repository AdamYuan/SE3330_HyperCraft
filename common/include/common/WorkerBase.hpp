#pragma once

namespace common {

class WorkerBase {
public:
	virtual void Run() = 0;
	virtual ~WorkerBase() = default;
};

} // namespace common
