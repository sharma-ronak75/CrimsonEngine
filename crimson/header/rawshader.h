#pragma once
#include "pch.h"
#include "program_id.h"

namespace Crimson
{
	class RawShader
	{
		fs::path shader_path;
	public:
		std::shared_ptr<ProgramID> program;
		RawShader() = default;
		~RawShader() = default;

		void use() const;
		static void use_none();
		static RawShader load(const fs::path location, bool strict = true);
		static RawShader load_from_raw_sources(const std::string& vertex, const std::string& fragment, bool strict);
		static std::string load_shader_recursive(const std::string& presource, fs::path location);
		static unsigned int compile_shader(unsigned int shader_type, const char* shader_source, bool strict);
		int get_uniform_location(const char* name) const;
		void set_uniform(const char* name, int value) const;
		void set_uniform(const char* name, glm::ivec2 value) const;
		void set_uniform(const char* name, glm::ivec3 value) const;
		void set_uniform(const char* name, glm::ivec4 value) const;
		void set_uniform(const char* name, float value) const;
		void set_uniform(const char* name, glm::vec2 value) const;
		void set_uniform(const char* name, glm::vec3 value) const;
		void set_uniform(const char* name, glm::vec4 value) const;
		void set_uniform(const char* name, glm::mat4 value) const;
		template <typename T> void uniform(const char* name, T value) const;
		void recompile();

		unsigned int get_program_id() const noexcept { return program == nullptr ? 0 : program->id; };
	};
}
