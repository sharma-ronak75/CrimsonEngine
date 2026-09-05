#include "../header/rawshader.h"
#include "../header/file.h"
#include <functional>
#include <stdexcept>

namespace Crimson{
void RawShader::use() const
{
	if(program == nullptr)
	{
		printf("Shader::use() -> warning! shader not initialized.\n");
	}
	glUseProgram(get_program_id());
}

void RawShader::use_none()
{
	glUseProgram(0);
}

RawShader RawShader::load(fs::path location, bool strict)
{
	std::string raw_source = File::read(location);

	std::string line;
	std::string vertex;
	std::string fragment;
	char type = 0;
	for(unsigned int i = 0; i < raw_source.size(); i++)
	{
		if(raw_source[i] != '\n')
		{
			line += raw_source[i];
			continue;
		}

		if(line.rfind("#vertex", 0) == 0)
		{
			type = 1;
			line.clear();
			continue;
		}
		else if(line.rfind("#fragment", 0) == 0)
		{
			type = 2;
			line.clear();
			continue;
		}

		if(type == 1)
		{
			vertex += line + '\n';
		}
		else if(type == 2)
		{
			fragment += line + '\n';
		}
		
		line.clear();
	}

	if(!line.empty())
	{
		if(type == 1)
		{
			vertex += line + '\n';
		}
		else if(type == 2)
		{
			fragment += line + '\n';
		}
	}

	vertex = "#version 420 core\n" + load_shader_recursive(vertex, location);
	fragment = "#version 420 core\n" + load_shader_recursive(fragment, location);
	
	auto shader = load_from_raw_sources(vertex, fragment, strict);
	shader.shader_path = location;
	return shader;
}

RawShader RawShader::load_from_raw_sources(const std::string& vertex, const std::string& fragment, bool strict)
{
	unsigned int vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex.c_str(), strict);
	unsigned int fragment_shader = 0;
	try
	{
		fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment.c_str(), strict);
	}
	catch(...)
	{
		glDeleteShader(vertex_shader);
		throw;
	}

	RawShader shader;
	shader.program = std::shared_ptr<ProgramID>(new ProgramID{glCreateProgram()}, [](ProgramID* program)
	{
		if(program != nullptr)
		{
			glDeleteProgram(program->id);
			delete program;
		}
	});
	glAttachShader(shader.get_program_id(), vertex_shader);
	glAttachShader(shader.get_program_id(), fragment_shader);
	glLinkProgram(shader.get_program_id());

	GLint linked;
	glGetProgramiv(shader.get_program_id(), GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLint infoLen;
		glGetProgramiv(shader.get_program_id(), GL_INFO_LOG_LENGTH, &infoLen);
		std::string infoLog(infoLen > 0 ? infoLen : 1, '\0');
		if(infoLen > 0) glGetProgramInfoLog(shader.get_program_id(), infoLen, NULL, infoLog.data());
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		glDeleteProgram(shader.get_program_id());
		shader.program.reset();
		throw std::runtime_error("Failed to link shader program.\n" + infoLog);
	}
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader;
}

std::string RawShader::load_shader_recursive(const std::string& presource, fs::path location)
{
	fs::path folder_path = location.parent_path();

	std::string line;
	std::string new_source;
	for(unsigned int i = 0; i < presource.size(); i++)
	{
		if(presource[i] != '\n')
		{
			line += presource[i];
			continue;
		}

		if(line.rfind("#include ", 0) == 0)
		{
			new_source += load_shader_recursive(File::read(folder_path.string() + line.substr(9)), location.string()) + '\n';
			line.clear();
			continue;
		}

		new_source += line + '\n';
		line.clear();
	}

	if(!line.empty())
	{
		if(line.rfind("#include ", 0) == 0)
		{
			new_source += load_shader_recursive(File::read(folder_path.string() + line.substr(9)), location.string()) + '\n';
		}
		else
		{
			new_source += line + '\n';
		}
	}

	return new_source;
}

unsigned int RawShader::compile_shader(unsigned int shader_type, const char* shader_source, bool strict)
{
	unsigned int shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(!compiled)
	{
		GLint infoLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		std::vector<char> infoLog(infoLen > 0 ? infoLen : 1);
		glGetShaderInfoLog(shader, infoLen, NULL, infoLog.data());
		printf("Failed to compile shader.\n");
		printf("%s\n", infoLog.data());
		glDeleteShader(shader);
		if(strict) throw std::runtime_error("Failed to compile shader");
	}

	return shader;
}

int RawShader::get_uniform_location(const char* name) const
{
	if(program == nullptr) return -1;
	int uniform = glGetUniformLocation(get_program_id(), name);
	// if(uniform == -1)
	// {
	// 	printf("Uniform \"%s\" does not exist or is unused.\n", name);
	// 	exit(1);
	// }
	
	return uniform;
}

void RawShader::set_uniform(const char* name, int value) const
{
	glUniform1i(get_uniform_location(name), value);
}

void RawShader::set_uniform(const char* name, glm::ivec2 value) const
{
	glUniform2i(get_uniform_location(name), value.x, value.y);
}

void RawShader::set_uniform(const char* name, glm::ivec3 value) const
{
	glUniform3i(get_uniform_location(name), value.x, value.y, value.z);
}

void RawShader::set_uniform(const char* name, glm::ivec4 value) const
{
	glUniform4i(get_uniform_location(name), value.x, value.y, value.z, value.w);
}

void RawShader::set_uniform(const char* name, float value) const
{
	glUniform1f(get_uniform_location(name), value);
}

void RawShader::set_uniform(const char* name, glm::vec2 value) const
{
	glUniform2f(get_uniform_location(name), value.x, value.y);
}

void RawShader::set_uniform(const char* name, glm::vec3 value) const
{
	glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
}

void RawShader::set_uniform(const char* name, glm::vec4 value) const
{
	glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
}

void RawShader::set_uniform(const char* name, glm::mat4 value) const
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

template <typename T> void RawShader::uniform(const char* name, T value) const
{
	set_uniform(name, value);
}

void RawShader::recompile()
{
	if(program == nullptr) return;
	if(shader_path.empty()) throw std::bad_function_call();
	auto new_shader = load(shader_path, false);

	if (program->id != 0) glDeleteProgram(program->id);
    program->id = new_shader.program->id;
    new_shader.program->id = 0;
}

} // namespace Crimson
