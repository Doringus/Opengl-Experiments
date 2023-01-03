#pragma once

#include <cstdint>

#include "program.hpp"

class Pipeline final {
public:
	Pipeline() noexcept;
	~Pipeline();

	void useProgramStage(GLbitfield stage, const Program& program);
	void bind();

private:
	uint32_t m_Handle {0};
};