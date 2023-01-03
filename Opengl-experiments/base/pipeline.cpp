#include "pipeline.hpp"

#include <GL/glew.h>

Pipeline::Pipeline() noexcept {
	glCreateProgramPipelines(1, &m_Handle);
}

Pipeline::~Pipeline() {
	glDeleteProgramPipelines(1, &m_Handle);
}

void Pipeline::useProgramStage(GLbitfield stage, const Program& program) {
	glUseProgramStages(m_Handle, stage, program.getHandle());
}

void Pipeline::bind() {
	glBindProgramPipeline(m_Handle);
}
